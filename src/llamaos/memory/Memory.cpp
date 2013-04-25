/*
Copyright (c) 2012, William Magato
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

   1. Redistributions of source code must retain the above copyright notice,
      this list of conditions and the following disclaimer.

   2. Redistributions in binary form must reproduce the above copyright notice,
      this list of conditions and the following disclaimer in the documentation
      and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDER(S) AND CONTRIBUTORS ''AS IS''
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER(S) OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

The views and conclusions contained in the software and documentation are those
of the authors and should not be interpreted as representing official policies,
either expressed or implied, of the copyright holder(s) or contributors.
*/

#include <llamaos/memory/Memory.h>

#include <llamaos/memory/Entry.h>
#include <llamaos/memory/PTE.h>
#include <llamaos/memory/PDE.h>
#include <llamaos/memory/PDPE.h>
#include <llamaos/memory/PML4E.h>

#include <llamaos/memory/PT.h>
#include <llamaos/memory/PD.h>
#include <llamaos/memory/PDP.h>
#include <llamaos/memory/PML4.h>

#include <llamaos/llamaOS.h>
#include <llamaos/Trace.h>

namespace llamaos {
namespace memory {

static uint64_t CR3_virtual_address = 0UL;
static uint64_t total_pages = 0UL;

static uint64_t start_pseudo_page = 0UL;
static uint64_t end_pseudo_page = 0UL;

static uint64_t start_virtual_address = 0UL;
static uint64_t end_virtual_address = 0UL;

static uint64_t start_reserved_virtual_address = 0UL;
static uint64_t next_reserved_virtual_address = 0UL;
static uint64_t reserved_pages = 0UL;

static void *program_break = nullptr;

/*
 * This is from xen.h:
 *
 * Start-of-day memory layout:
 *  1. The domain is started within contiguous virtual-memory region.
 *  2. The contiguous region ends on an aligned 4MB boundary.
 *  3. This the order of bootstrap elements in the initial virtual region:
 *      a. relocated kernel image
 *      b. initial ram disk              [mod_start, mod_len]
 *      c. list of allocated page frames [mfn_list, nr_pages]
 *         (unless relocated due to XEN_ELFNOTE_INIT_P2M)
 *      d. start_info_t structure        [register ESI (x86)]
 *      e. bootstrap page tables         [pt_base, CR3 (x86)]
 *      f. bootstrap stack               [register ESP (x86)]
 *  4. Bootstrap elements are packed together, but each is 4kB-aligned.
 *  5. The initial ram disk may be omitted.
 *  6. The list of page frames forms a contiguous 'pseudo-physical' memory
 *     layout for the domain. In particular, the bootstrap virtual-memory
 *     region is a 1:1 mapping to the first section of the pseudo-physical map.
 *  7. All bootstrap elements are mapped read-writable for the guest OS. The
 *     only exception is the bootstrap page table, which is mapped read-only.
 *  8. There is guaranteed to be at least 512kB padding after the final
 *     bootstrap element. If necessary, the bootstrap virtual region is
 *     extended by an extra 4MB to ensure this.
 *
 * find the end of the 4MB end of bootstrap elements
 *
 */
static uint64_t find_start_page (uint64_t CR3_virtual_address)
{
   uint64_t start_pseudo_page = address_to_page (virtual_to_pseudo (CR3_virtual_address));

   // Page-Map Level-4, root of page table hierarchy
   PML4 pml4 (CR3_virtual_address);

   // loop over top level entries
   for (uint64_t i = pml4.get_index (pseudo_to_virtual (page_to_address (start_pseudo_page))); i < 512UL; i++)
   {
      if (pml4 [i].empty ())
      {
         // stopped on a 256T boundary
         return start_pseudo_page;
      }

      // Page-Directory-Pointer
      PDP pdp (pml4 [i]);

      // loop over next level entries
      for (uint64_t j = pdp.get_index (pseudo_to_virtual (page_to_address (start_pseudo_page))); j < 512UL; j++)
      {
         if (pdp [j].empty ())
         {
            // stopped on a 512G boundary
            return start_pseudo_page;
         }

         // Page-Directory
         PD pd (pdp [j]);

         // loop over next level entries
         for (uint64_t k = pd.get_index (pseudo_to_virtual (page_to_address (start_pseudo_page))); k < 512UL; k++)
         {
            if (pd [k].empty ())
            {
               // stopped on a 2G boundary
               return start_pseudo_page;
            }

            // Page-Directory
            PT pt (pd [k]);

            // loop over next level entries
            for (uint64_t l = pt.get_index (pseudo_to_virtual (page_to_address (start_pseudo_page))); l < 512UL; l++)
            {
               if (pt [l].empty ())
               {
                  // stopped on a 4K boundary
                  return start_pseudo_page;
               }

               // increase to skip over this entry
               start_pseudo_page++;
            }
         }
      }
   }

   trace ("Memory: failed to find start_page\n");
   return 0UL;
}

static uint64_t find_start_address (uint64_t CR3_virtual_address,
                                    uint64_t start_pseudo_page,
                                    uint64_t end_pseudo_page,
                                    uint64_t total_pages)
{
   // begin installing new tables in the reserved 512kb padding
   uint64_t table_pseudo_page = start_pseudo_page - 128;

   PML4 pml4 (CR3_virtual_address);

   // loop over pages, mapping PDP, PD & PT along the way
   for (uint64_t i = start_pseudo_page; i < total_pages; i++)
   {
      // address at this page number
      uint64_t virtual_address = pseudo_to_virtual (page_to_address (i));
      PML4E pml4e (pml4.get_entry (virtual_address));

      if (pml4e.empty ())
      {
         trace ("currently not supporting table additions to PML4\n");
         return 0UL;
      }

      // note: we have to recall the entry methods because the values may have changed above
      PDP pdp (pml4.get_entry (virtual_address));
      PDPE pdpe (pdp.get_entry (virtual_address));

      if (pdpe.empty ())
      {
         uint64_t table_virtual_address = pseudo_to_virtual (page_to_address (table_pseudo_page));
         uint64_t table_machine_address = page_to_address (pseudo_page_to_machine_page (table_pseudo_page++));

         create_table_entry (CR3_virtual_address, table_virtual_address, table_machine_address);
         update_table_entry (pdpe.machine_address, table_machine_address);
      }

      // note: we have to recall the entry methods because the values may have changed above
      PD pd (pdp.get_entry (virtual_address));
      PDE pde (pd.get_entry (virtual_address));

      if (pde.empty ())
      {
         uint64_t table_virtual_address = pseudo_to_virtual (page_to_address (table_pseudo_page));
         uint64_t table_machine_address = page_to_address (pseudo_page_to_machine_page (table_pseudo_page++));

         create_table_entry (CR3_virtual_address, table_virtual_address, table_machine_address);
         update_table_entry (pde.machine_address, table_machine_address);
      }

      // note: we have to recall the entry methods because the values may have changed above
      PT pt (pd.get_entry (virtual_address));
      PTE pte (pt.get_entry (virtual_address));

      // do not try to map the reserved pages
      if (i < end_pseudo_page)
      {
         update_table_entry (pte.machine_address, page_to_address (pseudo_page_to_machine_page (i)));
      }
   }

   if (table_pseudo_page > start_pseudo_page)
   {
      // there were more tables than would fit in 512kb area
      start_pseudo_page = table_pseudo_page;
   }

   return pseudo_to_virtual (page_to_address (start_pseudo_page));
}

bool initialize (uint64_t CR3_virtual_address, uint64_t total_pages, uint64_t reserved_pages)
{
   memory::CR3_virtual_address = CR3_virtual_address;
   memory::total_pages = total_pages;
   memory::start_pseudo_page = find_start_page (CR3_virtual_address);
   memory::end_pseudo_page = total_pages;

   memory::start_virtual_address = find_start_address (CR3_virtual_address, start_pseudo_page, end_pseudo_page, total_pages + reserved_pages);
   memory::end_virtual_address = pseudo_to_virtual (page_to_address(end_pseudo_page));

   memory::start_reserved_virtual_address = memory::end_virtual_address;
   memory::next_reserved_virtual_address = memory::end_virtual_address;
   memory::reserved_pages = reserved_pages;

   program_break = address_to_pointer<void>(start_virtual_address);

//   trace ("memory initialized\n");
//   trace ("      start_pseudo_page: %lx\n", start_pseudo_page);
//   trace ("        end_pseudo_page: %lx\n", end_pseudo_page);
//   trace ("  start_virtual_address: %lx\n", start_virtual_address);
//   trace ("    end_virtual_address: %lx\n", end_virtual_address);
//   trace ("\n");

   return true;
}

uint64_t get_reserved_virtual_address (uint64_t pages)
{
   uint64_t next_address = memory::next_reserved_virtual_address;
   memory::next_reserved_virtual_address += (pages * PAGE_SIZE);

   trace("calling get_reserved_virtual_address(%lu) = %lu\n", pages, next_address);
   return next_address;
}

uint64_t get_reserved_size ()
{
   return memory::reserved_pages * PAGE_SIZE;
}

void *set_program_break (void *address)
{
   if (   (pointer_to_address (address) >= start_virtual_address)
       && (pointer_to_address (address) < end_virtual_address))
   {
      program_break = address;
   }

   return program_break;
}

} }

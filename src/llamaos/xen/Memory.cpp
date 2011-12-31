/*
Copyright (c) 2011, William Magato
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

#include <cstdint>
#include <cstdio>

#include <xen/xen.h>

#include <llamaos/xen/Hypercall.h>
#include <llamaos/xen/Memory.h>
#include <llamaos/trace.h>

uint64_t *mfn_to_pfn_map = reinterpret_cast <uint64_t *>(MACH2PHYS_VIRT_START);
uint64_t mfn_to_pfn_map_size = MACH2PHYS_NR_ENTRIES;

// assigned by start logic
uint64_t *pfn_to_mfn_map = 0;
uint64_t pfn_to_mfn_map_size = 0;

namespace llamaos {
namespace xen {

/**
 * @brief Convert a machine page frame to a pseudo page frame.
 *
 */
uint64_t machine_to_pseudo_page (uint64_t page)
{
   if (page < mfn_to_pfn_map_size)
   {
      return mfn_to_pfn_map [page];
   }

   // throw exception
   return 0UL;
}

/**
 * @brief Convert a pseudo page frame to a machine page frame.
 *
 */
uint64_t pseudo_to_machine_page (uint64_t page)
{
   if (page < pfn_to_mfn_map_size)
   {
      return pfn_to_mfn_map [page];
   }

   // throw exception
   return 0UL;
}

} }

using namespace llamaos;
using namespace llamaos::xen;

// This is from xen.h:

/*
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
 */

// find the end of the 4MB end of bootstrap elements
static uint64_t get_start_page (const PML4 &pml4)
{
   uint64_t start_page = 0UL;

   for (uint64_t i = 0UL; i < 512UL; i++)
   {
      PML4E pml4e (pml4 [i]);

      if (pml4e.empty ())
      {
         // stopped on a 256T boundary
         return start_page;
      }

      PDP pdp (pml4e);

      for (uint64_t j = 0UL; j < 512UL; j++)
      {
         PDPE pdpe (pdp [i]);

         if (pdpe.empty ())
         {
            // stopped on a 512G boundary
            return start_page;
         }

         PD pd (pdpe);

         for (uint64_t k = 0UL; k < 512UL; k++)
         {
            PDE pde (pd [k]);

            if (pde.empty ())
            {
               // stopped on a 1G boundary
               return start_page;
            }

            start_page += 512UL;
         }
      }      
   }

   // !BAM throw exception
   return 0UL;
}

static void initialize_table (const PML4 &pml4, uint64_t psuedo_page)
{
   uint64_t address = page_to_address(psuedo_page);

   PML4E pml4e (pml4.get_entry (address));
   PDP pdp (pml4e);
   PDPE pdpe (pdp.get_entry (address));
   PD pd (pdpe);
   PDE pde (pd.get_entry (address));
   PT pt (pde);
   PTE pte (pt.get_entry (address));

   xen::Hypercall::mmu_update (virtual_to_machine (pt.get_entry_address (pte.index)),
                               page_to_address (pseudo_to_machine_page(psuedo_page)) | Page_entry::A | Page_entry::US | Page_entry::P);
}

static void update_entry (uint64_t address, uint64_t psuedo_page)
{
   xen::Hypercall::mmu_update (address,
                               page_to_address (pseudo_to_machine_page(psuedo_page)) | Page_entry::A | Page_entry::US | Page_entry::RW | Page_entry::P);
}

static uint64_t get_start_address (const PML4 &pml4, uint64_t start_page, uint64_t end_page)
{
   // install tables in the 512kb padding
   uint64_t table_page = start_page - 128;

   trace ("get_start_address (start_page = %lx, end_page = %lx, table_page = %lx)\n", start_page, end_page, table_page);

   // loop over pages, mapping PDP, PD & PT along the way
   for (uint64_t i = start_page; i < end_page; i++)
   {
      PML4E pml4e (pml4.get_entry (page_to_address (i)));

      if (pml4e.empty ())
      {
         trace ("create PDP at PML4 [%lx]\n", pml4e.index);
         initialize_table (pml4, table_page);
         update_entry (virtual_to_machine (pml4.get_entry_address (pml4e.index)), table_page++);
      }

      PDP pdp (pml4.get_entry (page_to_address (i)));
      PDPE pdpe (pdp.get_entry (page_to_address (i)));

      if (pdpe.empty ())
      {
         trace ("create PD at PDP [%lx]\n", pdpe.index);
         initialize_table (pml4, table_page);
         update_entry (virtual_to_machine (pdp.get_entry_address (pdpe.index)), table_page++);
      }

      PD pd (pdp.get_entry (page_to_address (i)));
      PDE pde (pd.get_entry (page_to_address(i)));

      if (pde.empty ())
      {
         trace ("create PT at PD [%lx]\n", pde.index);
         initialize_table (pml4, table_page);
         update_entry (virtual_to_machine (pd.get_entry_address (pde.index)), table_page++);
      }

      PT pt (pd.get_entry (page_to_address(i)));
      PTE pte (pt.get_entry (page_to_address(i)));
      update_entry (virtual_to_machine (pt.get_entry_address (pte.index)), i);
   }

   if (table_page > start_page)
   {
      // there were more tables than would fit in 512kb area
      start_page = table_page;
   }

   return pseudo_to_virtual (page_to_address(start_page));
}

const uint64_t Page_entry::P   = 0x01UL;
const uint64_t Page_entry::RW  = 0x02UL;
const uint64_t Page_entry::US  = 0x04UL;
const uint64_t Page_entry::PWT = 0x08UL;
const uint64_t Page_entry::PCD = 0x10UL;
const uint64_t Page_entry::A   = 0x20UL;
const uint64_t Page_entry::ADDR_MASK = 0xffffffffff000UL;

Page_entry::Page_entry (uint64_t index, uint64_t value)
   :  index(index),
      value(value)
{

}

Page_entry::Page_entry (const Page_entry & pe)
   :  index(pe.index),
      value(pe.value)
{

}

Page_entry::~Page_entry ()
{

}

const char *Page_entry::to_string () const
{
   static char text [32] = { '\0' };

   sprintf (text,
            "0x%016lx %c %c %c %c %c %c",
            value & ADDR_MASK,
            (value & A) ? 'A' : ' ',
            (value & PCD) ? '1' : '0',
            (value & PWT) ? '1' : '0',
            (value & US) ? 'S' : 'U',
            (value & RW) ? 'W' : 'R',
            (value & P) ? 'P' : ' ');

   return text;
}

PTE::PTE (uint64_t index, uint64_t value)
   :  Page_entry(index, value)
{

}

PTE::~PTE ()
{

}

PDE::PDE (uint64_t index, uint64_t value)
   :  Page_entry(index, value)
{

}

PDE::~PDE ()
{

}

PDE::operator PT ()
{
   return PT (*this);
}

PDPE::PDPE (uint64_t index, uint64_t value)
   :  Page_entry(index, value)
{

}

PDPE::~PDPE ()
{

}

PDPE::operator PD ()
{
   return PD (*this);
}

PML4E::PML4E (uint64_t index, uint64_t value)
   :  Page_entry(index, value)
{

}

PML4E::~PML4E ()
{

}

PML4E::operator PDP ()
{
   return PDP (*this);
}

PT::PT (const PDE &entry)
   :  entry(entry),
      pointer (reinterpret_cast<uint64_t *> (machine_to_virtual (entry.address ())))
{

}

PT::PT (const PT &pt)
   :  entry(pt.entry),
      pointer(pt.pointer)
{

}

PT::~PT ()
{

}

PTE PT::operator[] (uint64_t index) const
{
   return PTE (index, pointer [index]);
}

PTE PT::get_entry (uint64_t address) const
{
   uint64_t index = (address & 0x1FF000) >> 12;

   return (*this) [index];
}

PD::PD (const PDPE &entry)
   :  entry(entry),
      pointer (reinterpret_cast<uint64_t *> (machine_to_virtual (entry.address ())))
{

}

PD::PD (const PD &pd)
   :  entry(pd.entry),
      pointer(pd.pointer)
{

}

PD::~PD ()
{

}

PDE PD::operator[] (uint64_t index) const
{
   return PDE (index, pointer [index]);
}

PDE PD::get_entry (uint64_t address) const
{
   uint64_t index = (address & 0x3FE00000) >> 21;

   return (*this) [index];
}

PDP::PDP (const PML4E &entry)
   :  entry(entry),
      pointer (reinterpret_cast<uint64_t *> (machine_to_virtual (entry.address ())))
{

}

PDP::PDP (const PDP &pdp)
   :  entry(pdp.entry),
      pointer(pdp.pointer)
{

}

PDP::~PDP ()
{

}

PDPE PDP::operator[] (uint64_t index) const
{
   return PDPE (index, pointer [index]);
}

PDPE PDP::get_entry (uint64_t address) const
{
   uint64_t index = (address & 0x7FC0000000) >> 30;

   return (*this) [index];
}

PML4::PML4 (uint64_t address)
   :  pointer(reinterpret_cast<uint64_t *>(address))
{

}

PML4::PML4 (const PML4 &pml4)
   :  pointer(pml4.pointer)
{

}

PML4::~PML4 ()
{

}

PML4E PML4::operator[] (uint64_t index) const
{
   return PML4E (index, pointer [index]);
}

PML4E PML4::get_entry (uint64_t address) const
{
   uint64_t index = (address & 0xFF8000000000) >> 39;

   return (*this) [index];
}

Memory::Memory (uint64_t CR3, uint64_t total_pages)
   :  pml4(CR3),
      start_page(get_start_page (pml4)),
      end_page(total_pages),
      start_address(get_start_address (pml4, start_page, end_page)),
      end_address(pseudo_to_virtual (page_to_address(end_page)))
{
   trace ("Memory start page: %lx\n", start_page);
   trace ("Memory   end page: %lx\n", end_page);

   trace ("Memory start address: %lx\n", start_address);
   trace ("Memory   end address: %lx\n", end_address);

   trace ("testing memory...\n");
   uint64_t *first = address_to_pointer<uint64_t>(start_address);
   uint64_t *last = address_to_pointer<uint64_t>(end_address);

   while (first < last)
   {
      *first = pointer_to_address (first);
      first++;
   }

   first = address_to_pointer<uint64_t>(start_address);
   last = address_to_pointer<uint64_t>(end_address);

   while (first < last)
   {
      if (*first != pointer_to_address (first))
      {
         trace ("  error at %lx\n", first);
      }

      first++;
   }

   trace ("testing memory...done\n");
}

Memory::~Memory ()
{

}

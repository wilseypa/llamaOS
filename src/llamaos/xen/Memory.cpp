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

#include <cstdio>

#include <stdexcept>
#include <sstream>

#include <xen/xen.h>

#include <llamaos/xen/Hypercall.h>
#include <llamaos/xen/Memory.h>
#include <llamaos/trace.h>

namespace llamaos {
namespace xen {
namespace memory {

// !BAM For whatever reason, this constructor will not run. The compiler says nothing and the object will exist
//      with zero for the data fields.
//static Page_converter machine_converter (to_pointer<uint64_t>(MACH2PHYS_VIRT_START), MACH2PHYS_NR_ENTRIES);

static uint64_t address_to_page (uint64_t address)
{
   return address >> 12;
}

static uint64_t page_to_address (uint64_t page)
{
   return page << 12;
}

static uint64_t machine_to_pseudo (uint64_t address)
{
   uint64_t offset = address & 0xFFF;
   uint64_t page = address_to_page (address);

   // for now create a local object each time. Static object above does not work.
   Page_converter machine_converter (to_pointer<uint64_t>(MACH2PHYS_VIRT_START), MACH2PHYS_NR_ENTRIES);

   return ((page_to_address (machine_converter [page])) | offset);
}

static uint64_t pseudo_to_virtual (uint64_t address)
{
   return address;
}

static uint64_t virtual_to_pseudo (uint64_t address)
{
   return address;
}

uint64_t machine_to_virtual (uint64_t address)
{
   return pseudo_to_virtual (machine_to_pseudo (address));
}

// Assume 64-bit/long mode operation only (for now)

// Page-Map Level-4 (PML4)              bits 39-47
// Page-Directory-Pointer (PDP)         bits 30-38
// Page-directory (PD)                  bits 21-29
// Page-Table (PT)                      bits 12-20
// Physical-Page Offset                 bits 0-11

class Entry
{
public:
   // Present bit.
   static const uint64_t P;

   // Read/Write bit.
   static const uint64_t RW;

   // User/Supervisor bit.
   static const uint64_t US;

   // Page-level write-through bit.
   static const uint64_t PWT;

   // Page-level cache disable bit.
   static const uint64_t PCD;

   // Accessed bit.
   static const uint64_t A;

   // Address mask.
   static const uint64_t ADDR_MASK;

   Entry (uint64_t machine_address, uint64_t value)
      :  machine_address(machine_address),
         value(value)
   {

   }

   virtual ~Entry ()
   {

   }

   // Test for present bit (P).
   bool present () const { return value & P; }

   // Test for read/write bit (RW).
   bool writable () const { return value & RW; }

   // Test for user/supervisor bit (US).
   bool user () const { return value & US; }

   // Test for page-level write-through bit (PWT).
   bool page_level_write_through () const { return value & PWT; }

   // Test for page-level cache diable bit (PCD).
   bool page_level_cache_disable () const { return value & PCD; }

   // Test for accessed bit (A).
   bool accessed () const { return value & A; }

   // Compute entry address.
   uint64_t address () const { return value & ADDR_MASK; }

   // Returns True if the entry is empty (null).
   bool empty () const { return (0 == value); }

   // Get a formatted string of the value.
   const char *to_string () const
   {
      static char text [32] = { '\0' };

      std::sprintf (text,
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

   // address of the entry (needed for mmu updates)
   const uint64_t machine_address;

   // Entry value.
   const uint64_t value;

private:
   Entry ();
   Entry (const Entry &);
   Entry &operator= (const Entry &);

};

const uint64_t Entry::P   = 0x01UL;
const uint64_t Entry::RW  = 0x02UL;
const uint64_t Entry::US  = 0x04UL;
const uint64_t Entry::PWT = 0x08UL;
const uint64_t Entry::PCD = 0x10UL;
const uint64_t Entry::A   = 0x20UL;
const uint64_t Entry::ADDR_MASK = 0xffffffffff000UL;

class PTE : public Entry
{
public:
   PTE (uint64_t machine_address, uint64_t value)
      :  Entry(machine_address, value)
   {

   }

   PTE (const PTE &entry)
      :  Entry(entry.machine_address, entry.value)
   {

   }

   ~PTE ()
   {

   }

private:
   PTE ();
   PTE &operator= (const PTE &);

};

class PDE : public Entry
{
public:
   PDE (uint64_t machine_address, uint64_t value)
      :  Entry(machine_address, value)
   {

   }

   PDE (const PDE &entry)
      :  Entry(entry.machine_address, entry.value)
   {

   }

   ~PDE ()
   {

   }

private:
   PDE ();
   PDE &operator= (const PDE &);

};

class PDPE : public Entry
{
public:
   PDPE (uint64_t machine_address, uint64_t value)
      :  Entry(machine_address, value)
   {

   }

   PDPE (const PDPE &entry)
      :  Entry(entry.machine_address, entry.value)
   {

   }

   ~PDPE ()
   {

   }

private:
   PDPE ();
   PDPE &operator= (const PDPE &);

};

class PML4E : public Entry
{
public:
   PML4E (uint64_t machine_address, uint64_t value)
      :  Entry(machine_address, value)
   {

   }

   PML4E (const PML4E &entry)
      :  Entry(entry.machine_address, entry.value)
   {

   }

   ~PML4E ()
   {

   }

private:
   PML4E ();
   PML4E &operator= (const PML4E &);

};

class PT
{
public:
   PT (PDE parent)
      :  parent(parent),
         table(to_pointer<uint64_t> (machine_to_virtual (parent.address ())))
   {

   }

   ~PT ()
   {

   }

   PTE operator[] (uint64_t index) const
   {
      return PTE (parent.machine_address + index, table [index]);
   }

   uint64_t get_index (uint64_t address) const
   {
      return (address & 0x1FF000) >> 12;
   }

   PTE get_entry (uint64_t address) const
   {
      uint64_t index = get_index (address);
      return PTE (parent.machine_address + index, table [index]);
   }

private:
   PT ();
   PT (const PT &);
   PT &operator= (const PT &);

   const PDE parent;
   const uint64_t *const table;

};

class PD
{
public:
   PD (PDPE parent)
      :  parent(parent),
         table(to_pointer<uint64_t> (machine_to_virtual (parent.address ())))
   {

   }

   ~PD ()
   {

   }

   PDE operator[] (uint64_t index) const
   {
      return PDE (parent.machine_address + index, table [index]);
   }

   uint64_t get_index (uint64_t address) const
   {
      return (address & 0x3FE00000) >> 21;
   }

   PDE get_entry (uint64_t address) const
   {
      uint64_t index = get_index (address);
      return PDE (parent.machine_address + index, table [index]);
   }

private:
   PD ();
   PD (const PD &);
   PD &operator= (const PD &);

   const PDPE parent;
   const uint64_t *const table;

};

class PDP
{
public:
   PDP (PML4E parent)
      :  parent(parent),
         table(to_pointer<uint64_t> (machine_to_virtual (parent.address ())))
   {

   }

   ~PDP ()
   {

   }

   PDPE operator[] (uint64_t index) const
   {
      return PDPE (parent.machine_address + index, table [index]);
   }

   uint64_t get_index (uint64_t address) const
   {
      return (address & 0x7FC0000000) >> 30;
   }

   PDPE get_entry (uint64_t address) const
   {
      uint64_t index = get_index (address);
      return PDPE (parent.machine_address + index, table [index]);
   }

private:
   PDP ();
   PDP (const PDP &);
   PDP &operator= (const PDP &);

   const PML4E parent;
   const uint64_t *const table;

};

class PML4
{
public:
   PML4 (uint64_t virtual_address)
      :  machine_address (0UL),
         table(to_pointer<uint64_t>(virtual_address))
   {

   }

   ~PML4 ()
   {

   }

   PML4E operator[] (uint64_t index) const
   {
      return PML4E (machine_address + index, table [index]);
   }

   uint64_t get_index (uint64_t address) const
   {
      return (address & 0xFF8000000000) >> 39;
   }

   PML4E get_entry (uint64_t address) const
   {
      uint64_t index = get_index (address);
      return PML4E (machine_address + index, table [index]);
   }

private:
   PML4 ();
   PML4 (const PML4 &);
   PML4 &operator= (const PML4 &);

   const uint64_t machine_address;
   const uint64_t *const table;

};

} } }

using namespace llamaos;
using namespace llamaos::xen;
using namespace llamaos::xen::memory;

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

   throw std::runtime_error ("Memory: failed to find start_page");
}

static void create_table_entry (uint64_t CR3_virtual_address,
                                uint64_t table_virtual_address,
                                uint64_t table_machine_address)
{
   trace ("create_table_entry (CR3_virtual_address: %lx, table_virtual_address: %lx, table_machine_address: %lx)\n",
            CR3_virtual_address,
            table_virtual_address,
            table_machine_address);

   // verify this page is already mapped
   PML4 pml4 (CR3_virtual_address);
   PML4E pml4e (pml4.get_entry (table_virtual_address));

   if (pml4e.empty ())
   {
      throw std::runtime_error ("calling create_table_entry() on unmapped page");
   }

   PDP pdp (pml4e);
   PDPE pdpe (pdp.get_entry (table_virtual_address));

   if (pdpe.empty ())
   {
      throw std::runtime_error ("calling create_table_entry() on unmapped page");
   }

   PD pd (pdpe);
   PDE pde (pd.get_entry (table_virtual_address));

   if (pde.empty ())
   {
      throw std::runtime_error ("calling create_table_entry() on unmapped page");
   }

   PT pt (pde);
   PTE pte (pt.get_entry (table_virtual_address));

   if (pte.empty ())
   {
      throw std::runtime_error ("calling create_table_entry() on unmapped page");
   }

   // clear the contents of this page
   uint64_t *table = to_pointer<uint64_t> (table_virtual_address);
   std::fill (table, table + 512, 0UL);

   // update the mmu to clear the RW flag
   Hypercall::mmu_update (pte.machine_address, table_machine_address | Entry::A | Entry::US | Entry::P);
}

static void update_table_entry (uint64_t entry_machine_address, uint64_t page_machine_address)
{
   trace ("update_table_entry (entry_machine_address: %lx, page_machine_address: %lx)\n",
          entry_machine_address, page_machine_address);

   Hypercall::mmu_update (entry_machine_address,
                          page_machine_address | Entry::A | Entry::US | Entry::RW | Entry::P);
}

static uint64_t find_start_address (uint64_t CR3_virtual_address, uint64_t start_pseudo_page, uint64_t end_pseudo_page, const Page_converter &pseudo_converter)
{
   trace ("starting find_start_address...\n");
   trace ("  CR3_virtual_address: %lx, start_pseudo_page: %lx, end_pseudo_page: %lx\n", CR3_virtual_address, start_pseudo_page, end_pseudo_page);

   // begin installing new tables in the reserved 512kb padding
   uint64_t table_pseudo_page = start_pseudo_page - 128;

   PML4 pml4 (CR3_virtual_address);

   // loop over pages, mapping PDP, PD & PT along the way
   for (uint64_t i = start_pseudo_page; i < end_pseudo_page; i++)
   {
      // address at this page number
      uint64_t virtual_address = pseudo_to_virtual (page_to_address (i));
      PML4E pml4e (pml4.get_entry (virtual_address));

      if (pml4e.empty ())
      {
         throw std::runtime_error ("currently not supporting table additions to PML4");
         // uint64_t table_virtual_address = pseudo_to_virtual (page_to_address (table_pseudo_page));
         // uint64_t table_machine_address = page_to_address (pseudo_converter [table_pseudo_page++]);

         // create_table_entry (CR3_virtual_address, table_virtual_address, table_machine_address);
         // update_table_entry (pml4e.machine_address, table_machine_address);
      }

      // note: we have to recall the entry methods because the values may have changed above
      PDP pdp (pml4.get_entry (virtual_address));
      PDPE pdpe (pdp.get_entry (virtual_address));

      if (pdpe.empty ())
      {
         uint64_t table_virtual_address = pseudo_to_virtual (page_to_address (table_pseudo_page));
         uint64_t table_machine_address = page_to_address (pseudo_converter [table_pseudo_page++]);

         create_table_entry (CR3_virtual_address, table_virtual_address, table_machine_address);
         update_table_entry (pdpe.machine_address, table_machine_address);
      }

      // note: we have to recall the entry methods because the values may have changed above
      PD pd (pdp.get_entry (virtual_address));
      PDE pde (pd.get_entry (virtual_address));

      if (pde.empty ())
      {
         uint64_t table_virtual_address = pseudo_to_virtual (page_to_address (table_pseudo_page));
         uint64_t table_machine_address = page_to_address (pseudo_converter [table_pseudo_page++]);

         create_table_entry (CR3_virtual_address, table_virtual_address, table_machine_address);
         update_table_entry (pde.machine_address, table_machine_address);
      }

      // note: we have to recall the entry methods because the values may have changed above
      PT pt (pd.get_entry (virtual_address));
      PTE pte (pt.get_entry (virtual_address));

      update_table_entry (pte.machine_address, page_to_address (pseudo_converter [i]));
   }

   if (table_pseudo_page > start_pseudo_page)
   {
      // there were more tables than would fit in 512kb area
      start_pseudo_page = table_pseudo_page;
   }

   return pseudo_to_virtual (page_to_address (start_pseudo_page));
}

Page_converter::Page_converter (const uint64_t *table, uint64_t size)
   :  table(table),
      size(size)
{

}

Page_converter::~Page_converter ()
{

}

uint64_t Page_converter::operator[] (uint64_t page) const
{
   if (page >= size)
   {
      std::stringstream ss;
      ss << "Page_converter[]: invalid page index (" << page << ")";

      throw std::runtime_error (ss.str ());
   }

   return table [page];
}

Memory::Memory (uint64_t CR3_virtual_address, uint64_t total_pages, uint64_t pseudo_converter_virtual_address)
   :  CR3_virtual_address(CR3_virtual_address),
      total_pages(total_pages),
      pseudo_converter(to_pointer<uint64_t> (pseudo_converter_virtual_address), total_pages),
      start_pseudo_page(find_start_page (CR3_virtual_address)),
      end_pseudo_page(total_pages),
      start_virtual_address(find_start_address (CR3_virtual_address, start_pseudo_page, end_pseudo_page, pseudo_converter)),
      end_virtual_address(pseudo_to_virtual (page_to_address(end_pseudo_page))),
      curbrk(to_pointer<void>(start_virtual_address))
{
   trace ("Hypervisor Memory created.\n");
}

Memory::~Memory ()
{

}

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

#include <cstdint>
#include <cstring>

#include <xen/xen.h>

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

#include <llamaos/xen/Hypercall.h>
#include <llamaos/Trace.h>
#include <llamaos/llamaOS.h>

namespace llamaos {
namespace memory {

uint64_t *machine_table = 0UL;
uint64_t  machine_table_size = 0UL;

// needs initialized by startup logic
uint64_t *pseudo_table = 0UL;
uint64_t  pseudo_table_size = 0UL;

uint64_t machine_page_to_pseudo_page (uint64_t page)
{
   if (page < machine_table_size)
   {
      return machine_table [page];
   }

   trace ("Invalid machine page frame %lx >= %lx\n", page, machine_table_size);
   return 0UL;
}

uint64_t pseudo_page_to_machine_page (uint64_t page)
{
   if (page < pseudo_table_size)
   {
      return pseudo_table [page];
   }

   trace ("Invalid pseudo page frame %lx >= %lx\n", page, pseudo_table_size);
   return 0UL;
}

void create_table_entry (uint64_t CR3_virtual_address,
                         uint64_t table_virtual_address,
                         uint64_t table_machine_address)
{
   // verify this page is already mapped
   PML4 pml4 (CR3_virtual_address);
   PML4E pml4e (pml4.get_entry (table_virtual_address));

   if (pml4e.empty ())
   {
      trace ("calling create_table_entry() on unmapped page\n");
      return;
   }

   PDP pdp (pml4e);
   PDPE pdpe (pdp.get_entry (table_virtual_address));

   if (pdpe.empty ())
   {
      trace ("calling create_table_entry() on unmapped page\n");
      return;
   }

   PD pd (pdpe);
   PDE pde (pd.get_entry (table_virtual_address));

   if (pde.empty ())
   {
      trace ("calling create_table_entry() on unmapped page\n");
      return;
   }

   PT pt (pde);
   PTE pte (pt.get_entry (table_virtual_address));

   if (pte.empty ())
   {
      trace ("calling create_table_entry() on unmapped page\n");
      return;
   }

   // clear the contents of this page
   uint64_t *table = address_to_pointer<uint64_t> (table_virtual_address);
   memset (table, 0, PAGE_SIZE);

   // update the mmu to clear the RW flag
   xen::Hypercall::mmu_update (pte.machine_address, table_machine_address | Entry::A | Entry::US | Entry::P);
}

void update_table_entry (uint64_t entry_machine_address, uint64_t page_machine_address)
{
   xen::Hypercall::mmu_update (entry_machine_address,
                               page_machine_address | Entry::A | Entry::US | Entry::RW | Entry::P);
}

} }

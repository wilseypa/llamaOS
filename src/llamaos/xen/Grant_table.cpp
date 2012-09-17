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

#include <malloc.h>
#include <stdexcept>

#include <llamaos/memory/Memory.h>
#include <llamaos/xen/Grant_table.h>
#include <llamaos/xen/Hypercall-macros.h>
#include <llamaos/xen/Hypercall.h>
#include <llamaos/llamaOS.h>
#include <llamaos/Trace.h>

using namespace std;
using namespace llamaos;
using namespace llamaos::memory;
using namespace llamaos::xen;

// for now just map a single page for the table
Grant_table::Grant_table ()
   :  size(PAGE_SIZE / sizeof(grant_entry_v1_t)),
      entries(address_to_pointer<grant_entry_v1_t> (get_reserved_virtual_address (1))),
      avail(),
      inuse()
{
   trace ("Grant_table constructor...\n");
   trace (" size: %x\n", size);
   trace (" entries: %lx\n", entries);

   unsigned long frame_list [1] = { 0 };

   trace ("calling grant_table_setup_table...\n");
   if (!Hypercall::grant_table_setup_table (1, frame_list))
   {
      trace ("failed to create grant table\n");
      throw runtime_error ("failed to create grant table");
   }

   trace ("calling update_va_mapping...\n");
   if (!Hypercall::update_va_mapping (pointer_to_address(entries), page_to_address (frame_list [0])))
   {
      trace("failed to map grant table\n");
      throw runtime_error ("failed to map grant table");
   }
   trace ("calling update_va_mapping returned.\n");

   for (grant_ref_t i = 0; i < size; i++)
   {
      avail.push_back(i);
   }

   trace ("Grant_table constructor ended.\n");
}

Grant_table::~Grant_table ()
{
   Hypercall::grant_table_setup_table(0, nullptr);
}

grant_ref_t Grant_table::grant_access (domid_t domid, void *address)
{
   grant_ref_t ref = avail.back ();
   avail.pop_back ();
   inuse.push_back (ref);

   entries [ref].domid = domid;
   entries [ref].frame = virtual_pointer_to_machine_page(address);

   trace ("grant_access - ref: %u, domid: %u, virtual address: %lu, machine address: %lu\n", ref, entries [ref].domid, address, entries [ref].frame);
   wmb();
   entries [ref].flags = GTF_permit_access | GTF_reading | GTF_writing;

   return ref;
}

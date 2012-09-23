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

#ifndef llamaos_xen_grant_map_h_
#define llamaos_xen_grant_map_h_

#include <xen/grant_table.h>
#include <xen/xen.h>

#include <llamaos/memory/Memory.h>
#include <llamaos/xen/Hypercall.h>

namespace llamaos {
namespace xen {

template <typename T>
class Grant_map
{
public:
   Grant_map (domid_t domid, grant_ref_t ref, bool readonly = false)
      :  address(memory::get_reserved_virtual_address (1)),
         handle(0)
   {
      gnttab_map_grant_ref_t map_grant_ref;

      map_grant_ref.dom = domid;
      map_grant_ref.ref = ref;
      map_grant_ref.host_addr = address;

      map_grant_ref.flags = (readonly) ? GNTMAP_host_map | GNTMAP_readonly
                                       : GNTMAP_host_map;

      Hypercall::grant_table_map_grant_ref (map_grant_ref);

      if (map_grant_ref.status == GNTST_okay)
      {
         handle = map_grant_ref.handle;
      }
   }

   virtual ~Grant_map ()
   {
      gnttab_unmap_grant_ref unmap_grant_ref;

      unmap_grant_ref.host_addr = address;
      unmap_grant_ref.handle = handle;

      Hypercall::grant_table_unmap_grant_ref (unmap_grant_ref);
   }

   const uint64_t address;

   // dereference operator when pointer
   T *get_pointer () { return memory::address_to_pointer<T>(address); }

   // dereference operator when pointer
   T *operator-> () { return memory::address_to_pointer<T>(address); }

   // index operator when array
   T &operator[] (int index) { return memory::address_to_pointer<T>(address) [index]; }

private:
   Grant_map (const Grant_map &);
   Grant_map &operator= (const Grant_map &);

   grant_handle_t handle;

};

} }

#endif  // llamaos_xen_grant_map_h_

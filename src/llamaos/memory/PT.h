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

#ifndef llamaos_memory_pt_h_
#define llamaos_memory_pt_h_

#include <cstdint>

#include <llamaos/memory/memory.h>
#include <llamaos/memory/PTE.h>

namespace llamaos {
namespace memory {

class PT
{
public:
   PT (PDE parent)
      :  parent(parent),
         table(machine_address_to_virtual_pointer<uint64_t>(parent.address ()))
   {

   }

   ~PT ()
   {

   }

   PTE operator[] (uint64_t index) const
   {
      return PTE (parent.address () + (index * sizeof(uint64_t)), table [index]);
   }

   uint64_t get_index (uint64_t address) const
   {
      return (address & 0x1FF000) >> 12;
   }

   PTE get_entry (uint64_t address) const
   {
      uint64_t index = get_index (address);
      return PTE (parent.address () + (index * sizeof(uint64_t)), table [index]);
   }

private:
   PT ();
   PT (const PT &);
   PT &operator= (const PT &);

   const PDE parent;
   const uint64_t *const table;

};

} }

#endif  // llamaos_memory_pt_h_


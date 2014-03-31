/*
Copyright (c) 2014, William Magato
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

#include <cstring>
#include <cstdint>

#include <iostream>

#include <llamaos/memory/Memory.h>
#include <llamaos/xen/Hypercall.h>
#include <llamaos/xen/Hypervisor.h>
#include <llamaos/llamaOS.h>

using namespace std;
using namespace llamaos;
using namespace llamaos::memory;

int main (int argc, char *argv [])
{
   cout << "starting mpich shared memory resources..." << endl;

   // create shared memory area
   const unsigned int shmem_size = 1024 * PAGE_SIZE;
   char *shmem = static_cast<char *>(aligned_alloc (PAGE_SIZE, shmem_size));

   memset(static_cast<void *>(shmem), 0, shmem_size);

   // allow access to the interface
   xen::Hypervisor *hypervisor = xen::Hypervisor::get_instance ();

   domid_t self_id = hypervisor->domid;
   cout << "self_id: " << self_id << endl;

//   grant_ref_t ref;
   int nodes = atoi(hypervisor->argv [2];

   for (int i = 0; i < nodes; i++)
   {
      for (int j = 0; j < 1024; j++)
      {
         hypervisor->grant_table.grant_access (self_id + 1 + i, &shmem [j * PAGE_SIZE]);
//      ref = hypervisor->grant_table.grant_access (self_id + 1 + i, shmem);
//      cout << "node " << self_id + 1 + i << " shmem ref: " << ref << endl;
      }
   }

   cout << "sleep forever..." << endl;

   for (;;)
   {
      xen::Hypercall::sched_op_yield();
   }

   return 0;
}

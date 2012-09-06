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

#include <ios>

#include <xen/xen.h>

#include <llamaos/memory/Memory.h>
#include <llamaos/xen/Entry-llamaOS.h>
#include <llamaos/llamaOS.h>
#include <llamaos/Trace.h>

using namespace std;
using namespace llamaos;
//using namespace llamaos::xen;

namespace llamaos {
namespace memory {

// needs initialized by startup logic
extern uint64_t *machine_table;
extern uint64_t  machine_table_size;
extern uint64_t *pseudo_table;
extern uint64_t  pseudo_table_size;

} }

static void initialize_mmu (start_info_t *start_info)
{
   // initialize memory management
   memory::machine_table = memory::address_to_pointer<uint64_t>(MACH2PHYS_VIRT_START);
   memory::machine_table_size = MACH2PHYS_NR_ENTRIES;
   memory::pseudo_table = memory::address_to_pointer<uint64_t> (start_info->mfn_list);
   memory::pseudo_table_size = start_info->nr_pages;

   memory::initialize (start_info->pt_base, start_info->nr_pages, 1024);
}

static void register_gcc_exports ()
{
}

typedef void (*func_ptr) (void);
extern func_ptr __CTOR_LIST__[];
extern func_ptr __DTOR_LIST__[];

static void exe_ctors ()
{
   uint64_t ctor_size = reinterpret_cast<uint64_t>(__CTOR_LIST__[0]);

   trace ("__CTOR_LIST__[0]: %lx\n", ctor_size);

   for (uint64_t i = ctor_size; i >= 1; i--)
   {
      __CTOR_LIST__[i] ();
   }
}

static void exe_dtors ()
{
   uint64_t dtor_size = reinterpret_cast<uint64_t>(__DTOR_LIST__[0]);

   trace ("__DTOR_LIST__[0]: %lx\n", dtor_size);

   for (uint64_t i = dtor_size; i >= 1; i--)
   {
      __DTOR_LIST__[i] ();
   }
}

extern "C"
void entry_gcc (start_info_t *start_info)
{
   trace ("registering llamaOS gcc exports...\n");
   register_gcc_exports ();

   // initialize memory management
   initialize_mmu (start_info);

   exe_ctors ();

   // initialize libstdc++
   ios_base::Init ios_base_init;

   entry_llamaOS (start_info);

   exe_dtors ();
}

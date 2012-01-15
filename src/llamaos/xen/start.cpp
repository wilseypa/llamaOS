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
#include <stdexcept>

#include <xen/xen.h>
#include <xen/features.h>
#include <xen/version.h>

#include <llamaos/memory/memory.h>
#include <llamaos/xen/Hypercall.h>
#include <llamaos/xen/Hypervisor.h>
#include <llamaos/config.h>
#include <llamaos/trace.h>

using namespace std;
using namespace llamaos;
using namespace llamaos::xen;

namespace llamaos {
namespace memory {

// needs initialized by startup logic
extern uint64_t *machine_table;
extern uint64_t  machine_table_size;
extern uint64_t *pseudo_table;
extern uint64_t  pseudo_table_size;

} }

// runtime stack memory
char RUNTIME_STACK [2 * llamaos::STACK_SIZE];

// used in entry assembler
shared_info_t *HYPERVISOR_shared_info = 0;

uint8_t xen_features [XENFEAT_NR_SUBMAPS * 32];


extern "C"
void do_hypervisor_callback (struct pt_regs * /* regs */)
{

}

static bool verify_magic (const start_info_t *start_info)
{
   if (   (nullptr != start_info)
       && (0 == strncmp (start_info->magic, "xen-", 4)))
   {
      return true;
   }

   return false;
}

static void trace_startup (const start_info_t *start_info)
{
   trace ("\n\n\n*********************************\n");
   trace (      "****  starting llamaOS (Xen)  ***\n");
   trace (      "*********************************\n\n\n");

   trace ("%s\n\n", VERSION_TEXT);

   trace ("=== start_info ===\n");
   trace ("  magic: %s\n", start_info->magic);
   trace ("  nr_pages: %x\n", start_info->nr_pages);
   trace ("  shared_info: %x\n", start_info->shared_info);
   trace ("  flags: %x\n", start_info->flags);
   trace ("  store_mfn: %x\n", start_info->store_mfn);
   trace ("  store_evtchn: %x\n", start_info->store_evtchn);
   trace ("  console.domU.mfn: %x\n", start_info->console.domU.mfn);
   trace ("  console.domU.evtchn: %x\n", start_info->console.domU.evtchn);
   trace ("  pt_base: %x\n", start_info->pt_base);
   trace ("  nr_pt_frames: %x\n", start_info->nr_pt_frames);
   trace ("  mfn_list: %x\n", start_info->mfn_list);
   trace ("  mod_start: %x\n", start_info->mod_start);
   trace ("  mod_len: %x\n", start_info->mod_len);
   trace ("  cmd_line: %s\n", start_info->cmd_line);
   trace ("  first_p2m_pfn: %x\n", start_info->first_p2m_pfn);
   trace ("  nr_p2m_frames: %x\n", start_info->nr_p2m_frames);
   trace ("\n");
}

extern int main (int, char*[]);

void register_glibc_exports ();

typedef void (*func_ptr) (void);
extern func_ptr __CTOR_LIST__[];
extern func_ptr __DTOR_LIST__[];

static const char *program_name = "llamaOS";

extern "C"
void start (start_info_t *start_info)
{
   if (verify_magic (start_info))
   {
      trace_startup (start_info);

      // initialize memory management
      memory::machine_table = memory::address_to_pointer<uint64_t>(MACH2PHYS_VIRT_START);
      memory::machine_table_size = MACH2PHYS_NR_ENTRIES;
      memory::pseudo_table = memory::address_to_pointer<uint64_t> (start_info->mfn_list);
      memory::pseudo_table_size = start_info->nr_pages;
      memory::initialize (start_info->pt_base, start_info->nr_pages);

      // register callbacks to the glibc library
      register_glibc_exports ();

      try
      {
         uint64_t ctor_size = reinterpret_cast<uint64_t>(__CTOR_LIST__[0]);
         trace ("__CTOR_LIST__[0]: %lx\n", ctor_size);
         for (uint64_t i = ctor_size; i >= 1; i--)
         {
            __CTOR_LIST__[i] ();
         }

         // create the one and only hypervisor object
         trace ("Creating Hypervisor...\n");
         Hypervisor hypervisor (start_info);

         // initialize libstdc++
         ios_base::Init ios_base_init;

         // start the application
         char *argv [2];
         argv [0] = const_cast<char *>(program_name);
         argv [1] = 0;
         main (1, argv);

         trace ("ending llamaOS...\n");

         uint64_t dtor_size = reinterpret_cast<uint64_t>(__DTOR_LIST__[0]);
         trace ("__DTOR_LIST__[0]: %lx\n", dtor_size);
         for (uint64_t i = dtor_size; i >= 1; i--)
         {
            __DTOR_LIST__[i] ();
         }
      }
      catch (const std::runtime_error &e)
      {
         trace ("*** runtime_error: %s ***\n", e.what ());
      }
      catch (...)
      {
         trace ("*** unknown exception ***\n");
      }

      for (;;);
      Hypercall::sched_op_shutdown ();
   }
   // else
   // something terrible is wrong and nothing can be done about it!
}

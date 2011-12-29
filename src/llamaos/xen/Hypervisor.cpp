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
#include <cstring>

#include <stdexcept>

#include <xen/xen.h>
#include <xen/features.h>
#include <xen/version.h>

#include <llamaos/config.h>
#include <llamaos/xen/Hypercall.h>
#include <llamaos/xen/Hypervisor.h>
#include <llamaos/trace.h>

using namespace llamaos;
using namespace llamaos::xen;

// runtime stack memory
char RUNTIME_STACK [2 * llamaos::STACK_SIZE];

// used in entry assembler
shared_info_t *HYPERVISOR_shared_info = 0;

uint8_t xen_features [XENFEAT_NR_SUBMAPS * 32];

extern "C"
void do_simd_coprocessor_error(struct pt_regs * /* regs */)
{

}

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

#include <xen/sched.h>
// include the hypercall macros from mini-os
typedef struct { unsigned long pte; } pte_t;
extern char hypercall_page [__PAGE_SIZE];
#include <llamaos/xen/hypercall-x86_64.h>

extern "C"
void guest_entry (start_info_t *start_info)
{
   if (verify_magic (start_info))
   {
      HYPERVISOR_console_io (CONSOLEIO_write, 11, "booting...\n");

      trace ("starting ucguest...\n");

      trace ("\n=== start_info ===\n");
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

   for (;;);

      try
      {
         // ucguest::Hypervisor hypervisor (start_info);
         // throw std::runtime_error ("default error");
      }
      catch (const std::runtime_error &e)
      {
         trace ("*** runtime_error: %s ***\n", e.what ());
      }
      catch (...)
      {
         trace ("*** unknown exception ***\n");
      }

      trace ("ending ucguest...\n");
      Hypercall::sched_op_shutdown ();
   }
   // else
   // something terrible is wrong and nothing can be done about it!
}

#include <string>

#include <vector>
#include <deque>
#include <list>

#include <stack>
#include <queue>

#include <set>
#include <map>
#include <bitset>

#include <memory>

#include <sstream>

using namespace std;

Hypervisor::Hypervisor (const start_info_t *start_info)
   :  start_info(*start_info)
{
   vector<int> int_vec;
   deque<int> int_deq;
   list<int> int_list;

   stack<int> int_stack;
   queue<int> int_queue;
   priority_queue<int> int_pqueue;

   set<int> int_set;
   multiset<int> int_mset;

   map<int, int> int_map;
   multimap<int, int> int_mmap;

   bitset<32> bitset_32;

   string s ("hello");

   int *dynint = new int;
   delete dynint;

   int *dyninta = new int [10];
   delete[] dyninta;

   shared_ptr<int> p;

   stringstream ss;
   ss << "compound string #" << 1;
   string final_string = ss.str ();
}

Hypervisor::~Hypervisor ()
{
   
}

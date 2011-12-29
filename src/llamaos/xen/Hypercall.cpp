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

#include <xen/xen.h>
#include <xen/sched.h>
#include <xen/version.h>

#include <llamaos/xen/Hypercall.h>
#include <llamaos/config.h>
#include <llamaos/trace.h>

// include the hypercall macros from mini-os
typedef struct { unsigned long pte; } pte_t;
extern char hypercall_page [__PAGE_SIZE];
#include <llamaos/xen/hypercall-x86_64.h>

using namespace llamaos;
using namespace llamaos::xen;

bool Hypercall::set_trap_table (const trap_info_t *table)
{
   if (0 != HYPERVISOR_set_trap_table(const_cast<trap_info_t *>(table)))
   {
      trace ("HYPERVISOR_set_trap_table (%lx) FAILED\n", table);
      return false;
   }

   return true;
}

bool Hypercall::mmu_update (const mmu_update_t &req)
{
   int success_count = 0;

   if (0 != HYPERVISOR_mmu_update(const_cast<mmu_update_t *>(&req), 1, &success_count, DOMID_SELF))
   {
      trace ("HYPERVISOR_mmu_update (ptr: %lx, val: %lx) FAILED\n", req.ptr, req.val);
      return false;
   }
   else if (1 != success_count)
   {
      trace ("HYPERVISOR_mmu_update () FAILED: invalid success_count (%d != 1)\n", success_count);
      return false;
   }

   return true;
}

bool Hypercall::mmu_update (const mmu_update_t *req, unsigned int count)
{
   int request_count = count;
   int success_count = 0;

   if (0 != HYPERVISOR_mmu_update(const_cast<mmu_update_t *>(req), request_count, &success_count, DOMID_SELF))
   {
      trace ("HYPERVISOR_mmu_update (req: %lx, count: %d) FAILED\n", req, request_count);
      return false;
   }
   else if (success_count != request_count)
   {
      trace ("HYPERVISOR_mmu_update () FAILED: invalid success_count (%d != %d\n", success_count, request_count);
      return false;
   }

   return true;
}

bool Hypercall::set_callbacks (uint64_t event_address, uint64_t failsafe_address)
{
   if (0 != HYPERVISOR_set_callbacks (event_address, failsafe_address, 0UL))
   {
      trace ("HYPERVISOR_set_callbacks (event_address: %lx, failsafe_address: %lx) FAILED\n", event_address, failsafe_address);
      return false;
   }

   return true;
}

bool Hypercall::update_va_mapping (uint64_t pseudo_page, uint64_t machine_page)
{
   pte_t val;
   val.pte = machine_page | 7;

   if (0 != HYPERVISOR_update_va_mapping (pseudo_page, val, UVMF_INVLPG))
   {
      trace ("HYPERVISOR_update_va_mapping (pseudo_page: %lx, machine_page: %lx) FAILED\n", pseudo_page, machine_page);
      return false;
   }

   return true;
}

void Hypercall::xen_version (int &major, int &minor)
{
   uint32_t version = HYPERVISOR_xen_version (XENVER_version, 0);

   major = version >> 16;
   minor = version & 0xFFFF;
}

bool Hypercall::console_io (const char *str)
{
   if (0 != HYPERVISOR_console_io (CONSOLEIO_write, strlen (str), const_cast<char *>(str)))
   {
      // probably nothing can be done here since trace would just recall console_io
      // trace ("HYPERVISOR_console_io (%s) FAILED\n", str);
      return false;
   }

   return true;
}

bool Hypercall::grant_table_op ()
{
   return true;
}

bool Hypercall::sched_op_yield ()
{
   if (0 != HYPERVISOR_sched_op (SCHEDOP_yield, 0))
   {
      trace ("HYPERVISOR_sched_op (SCHEDOP_yield) FAILED\n");
      return false;
   }

   return true;
}

bool Hypercall::sched_op_block ()
{
   if (0 != HYPERVISOR_sched_op (SCHEDOP_block, 0))
   {
      trace ("HYPERVISOR_sched_op (SCHEDOP_block) FAILED\n");
      return false;
   }

   return true;
}

bool Hypercall::sched_op_shutdown (unsigned int reason)
{
   sched_shutdown_t arg;
   arg.reason = reason;

   if (0 != HYPERVISOR_sched_op (SCHEDOP_shutdown, &arg))
   {
      trace ("HYPERVISOR_sched_op (SCHEDOP_shutdown, reason: %u) FAILED\n", reason);
      return false;
   }

   return true;
}

bool Hypercall::event_channel_op ()
{
   return true;
}
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

#ifndef __XEN_INTERFACE_VERSION__
#error __XEN_INTERFACE_VERSION__ not defined!!!
#endif

#include <xen/xen.h>
#include <xen/grant_table.h>
#include <xen/sched.h>

#include <llamaos/xen/Hypercall-macros.h>
#include <llamaos/xen/Hypercall.h>
#include <llamaos/llamaOS.h>
#include <llamaos/Trace.h>

using namespace llamaos;
using namespace llamaos::xen;

#if 0
// it would be nice to use these templates but they don't seem to work?

template <typename T> 
static T hypercall (uint64_t index)
{
   register uint64_t result asm("rax");

   asm volatile ("call hypercall_page + %c[offset]"
                 : "=r"(result)
                 : [offset] "i" (index * 32)
                 : "rdi", "rsi", "rdx", "r10", "r8" "memory"
                );

   return static_cast<T>(result);
}

template <typename T> 
static T hypercall (uint64_t index,
                    uint64_t a1)
{
   register uint64_t result asm("rax");
   register uint64_t arg1 asm("rdi") = a1;

   asm volatile ("call hypercall_page + %c[offset]"
                 : "=r"(result), "+r"(arg1)
                 : [offset] "i" (index * 32)
                 : "rsi", "rdx", "r10", "r8", "memory"
                );

   return static_cast<T>(result);
}

template <typename T> 
static T hypercall (uint64_t index,
                    uint64_t a1,
                    uint64_t a2)
{
   register uint64_t result asm("rax");
   register uint64_t arg1 asm("rdi") = a1;
   register uint64_t arg2 asm("rsi") = a2;

   asm volatile ("call hypercall_page + %c[offset]"
                 : "=r"(result), "+r"(arg1), "+r"(arg2)
                 : [offset] "i" (index * 32)
                 : "rdx", "r10", "r8", "memory"
                );

   return static_cast<T>(result);
}

template <typename T> 
T hypercall3(int index, unsigned long a1, unsigned long a2, unsigned long a3)
{
   register unsigned long __res  asm("rax");
   register uint64_t arg1 asm("rdi") = a1;
   register uint64_t arg2 asm("rsi") = a2;
   register uint64_t arg3 asm("rdx") = a3;

   asm volatile ("call hypercall_page + %c[offset]"
                 : "=r"(result), "+r"(arg1), "+r"(arg2), "+r"(arg3)
                 : [offset] "i" (index * 32)
                 : "r10", "r8", "memory"
                );

   return (T)__res;
}

template <typename T> 
static inline T hypercall (uint64_t index,
                           uint64_t a1,
                           uint64_t a2,
                           uint64_t a3,
                           uint64_t a4)
{
   register uint64_t result asm("rax");
   register uint64_t arg1 asm("rdi") = a1;
   register uint64_t arg2 asm("rsi") = a2;
   register uint64_t arg3 asm("rdx") = a3;
   register uint64_t arg4 asm("r10") = a4;

   asm volatile ("call hypercall_page + %c[offset]"
                 : "=r"(result), "+r"(arg1), "+r"(arg2), "+r"(arg3), "+r"(arg4)
                 : [offset] "i" (index * 32)
                 : "r8", "memory"
                );

   return static_cast<T>(result);
}

template <typename T> 
static inline T hypercall (uint64_t index,
                           uint64_t a1,
                           uint64_t a2,
                           uint64_t a3,
                           uint64_t a4,
                           uint64_t a5)
{
   register uint64_t result asm("rax");
   register uint64_t arg1 asm("rdi") = a1;
   register uint64_t arg2 asm("rsi") = a2;
   register uint64_t arg3 asm("rdx") = a3;
   register uint64_t arg4 asm("r10") = a4;
   register uint64_t arg5 asm("r8")  = a5;

   asm volatile ("call hypercall_page + %c[offset]"
                 : "=r"(result), "+r"(arg1), "+r"(arg2), "+r"(arg3), "+r"(arg4), "+r"(arg5)
                 : [offset] "i" (index * 32)
                 : "memory"
                );

   return static_cast<T>(result);
}
#endif

bool Hypercall::set_trap_table (const trap_info_t *table)
{
   // __HYPERVISOR_set_trap_table        0
   int result = HYPERVISOR_set_trap_table(const_cast<trap_info_t *>(table));

   if (0 != result)
   {
      trace ("HYPERVISOR_set_trap_table (%lx) FAILED\n", table);
      trace ("   error code: %d\n", result);
      return false;
   }

   return true;
}

bool Hypercall::mmu_update (uint64_t ptr, uint64_t val)
{
   mmu_update_t req;
   req.ptr = ptr;
   req.val = val;

   return mmu_update (&req, 1);
}

bool Hypercall::mmu_update (const mmu_update_t *req, unsigned int count)
{
   int request_count = count;
   int success_count = 0;

   // __HYPERVISOR_mmu_update            1
   int result = HYPERVISOR_mmu_update(const_cast<mmu_update_t *>(req), request_count, &success_count, DOMID_SELF);

   if (0 != result)
   {
      trace ("HYPERVISOR_mmu_update (count: %d) FAILED\n", request_count);
      trace ("   error code: %d\n", result);

      for (unsigned int i = 0; i < count; i++)
      {
         trace ("   [%u] ptr: %lx, val: %lx\n", i, req [i].ptr, req [i].val);
      }

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
   // __HYPERVISOR_set_callbacks         4
   int result = HYPERVISOR_set_callbacks (event_address, failsafe_address, 0UL);

   if (0 != result)
   {
      trace ("HYPERVISOR_set_callbacks (event_address: %lx, failsafe_address: %lx) FAILED\n", event_address, failsafe_address);
      trace ("   error code: %d\n", result);
      return false;
   }

   return true;
}

bool Hypercall::update_va_mapping (uint64_t virtual_address, uint64_t machine_address)
{
   pte_t val;
   val.pte = machine_address | 0x7;
//   machine_address |= 7;

   // __HYPERVISOR_update_va_mapping    14
   int result = HYPERVISOR_update_va_mapping (virtual_address, val, UVMF_INVLPG);
 
   if (0 != result)
   {
      trace ("HYPERVISOR_update_va_mapping (pseudo_page: %lx, machine_page: %lx) FAILED\n", virtual_address, machine_address);
      trace ("   error code: %d\n", result);
      return false;
   }

   return true;
}

bool Hypercall::update_va_mapping_nocache (uint64_t virtual_address, uint64_t machine_address)
{
   pte_t val;
   val.pte = machine_address | 0x17;
//   machine_address |= 0x17;

   // __HYPERVISOR_update_va_mapping    14
   int result = HYPERVISOR_update_va_mapping (virtual_address, val, UVMF_INVLPG);
 
   if (0 != result)
   {
      trace ("HYPERVISOR_update_va_mapping (pseudo_page: %lx, machine_page: %lx) FAILED\n", virtual_address, machine_address);
      trace ("   error code: %d\n", result);
      return false;
   }

   return true;
}

void Hypercall::xen_version (int &major, int &minor)
{
   // __HYPERVISOR_xen_version          17
   uint32_t version = HYPERVISOR_xen_version (XENVER_version, 0);

   major = version >> 16;
   minor = version & 0xFFFF;
}

bool Hypercall::console_io (const char *text)
{
   int count = strlen(text);

   // __HYPERVISOR_console_io           18
   int result = HYPERVISOR_console_io (CONSOLEIO_write,
                                       count,
				       const_cast<char *>(text));

   if (0 != result)
   {
      // probably nothing can be done here since trace would just recall this
      return false;
   }

   return true;
}

bool Hypercall::grant_table_setup_table (unsigned int pages, unsigned long *frame_list)
{
   gnttab_setup_table_t setup_table;

   setup_table.dom = DOMID_SELF;
   setup_table.nr_frames = pages;
   set_xen_guest_handle(setup_table.frame_list, frame_list);

   // __HYPERVISOR_grant_table_op       20
   int result = HYPERVISOR_grant_table_op (GNTTABOP_setup_table, &setup_table, 1);

   if (0 != result)
   {
      trace ("HYPERVISOR_grant_table_op (GNTTABOP_setup_table) FAILED\n");
      trace ("   error code: %d\n", result);
      return false;
   }
   else if (setup_table.status != GNTST_okay)
   {
      trace ("HYPERVISOR_grant_table_op (GNTTABOP_setup_table) FAILED (status: %d)\n", setup_table.status);
      return false;
   }

   return true;
}

bool Hypercall::grant_table_query_size (uint32_t &frames, uint32_t &max_frames, int16_t &status)
{
   gnttab_query_size_t query_size;
   query_size.dom = DOMID_SELF;

   // __HYPERVISOR_grant_table_op       20
   int result = HYPERVISOR_grant_table_op (GNTTABOP_query_size, &query_size, 1);

   if (0 != result)
   {
      trace ("HYPERVISOR_grant_table_op (GNTTABOP_query_size) FAILED\n");
      trace ("   error code: %d\n", result);
      return false;
   }

   frames = query_size.nr_frames;
   max_frames = query_size.max_nr_frames;
   status = query_size.status;
   return true;
}

// needs __XEN_INTERFACE_VERSION__=0x0003020a
//bool Hypercall::grant_table_get_version (uint32_t &version)
//{
//   gnttab_get_version_t get_version;
//   get_version.dom = DOMID_SELF;
//
//   if (0 != HYPERVISOR_grant_table_op (GNTTABOP_get_version, &get_version, 1))
//   {
//      trace ("HYPERVISOR_grant_table_op (GNTTABOP_get_version) FAILED\n");
//      return false;
//   }
//
//   version = get_version.version;
//   return true;
//}

bool Hypercall::sched_op_yield ()
{
   // __HYPERVISOR_sched_op             29
   int result = HYPERVISOR_sched_op (SCHEDOP_yield, 0);

   if (0 != result)
   {
      trace ("HYPERVISOR_sched_op (SCHEDOP_yield) FAILED\n");
      trace ("   error code: %d\n", result);
      return false;
   }

   return true;
}

bool Hypercall::sched_op_block ()
{
   // __HYPERVISOR_sched_op             29
   int result = HYPERVISOR_sched_op (SCHEDOP_block, 0);

   if (0 != result)
   {
      trace ("HYPERVISOR_sched_op (SCHEDOP_block) FAILED\n");
      trace ("   error code: %d\n", result);
      return false;
   }

   return true;
}

bool Hypercall::sched_op_shutdown (unsigned int reason)
{
   sched_shutdown_t arg;
   arg.reason = reason;

   // __HYPERVISOR_sched_op             29
   int result = HYPERVISOR_sched_op (SCHEDOP_shutdown, &arg);

   if (0 != result)
   {
      trace ("HYPERVISOR_sched_op (SCHEDOP_shutdown, reason: %u) FAILED\n", reason);
      trace ("   error code: %d\n", result);
      return false;
   }

   return true;
}

bool Hypercall::event_channel_send (evtchn_port_t port)
{
   evtchn_send_t op;
   op.port = port;

   // __HYPERVISOR_event_channel_op     32
   int result = HYPERVISOR_event_channel_op (EVTCHNOP_send, &op);

   if (0 != result)
   {
      trace ("HYPERVISOR_event_channel_op (EVTCHNOP_send, port: %u) FAILED\n", port);
      trace ("   error code: %d\n", result);
      return false;
   }

   return true;
}

bool Hypercall::event_channel_bind_virq (uint32_t virq, evtchn_port_t &port)
{
   evtchn_bind_virq_t op;
   op.virq = virq;
   op.vcpu = 0;

   // __HYPERVISOR_event_channel_op     32
   int result = HYPERVISOR_event_channel_op (EVTCHNOP_bind_virq, &op);

   if (0 != result)
   {
      trace ("HYPERVISOR_event_channel_op (EVTCHNOP_bind_virq, virq: %u) FAILED\n", virq);
      trace ("   error code: %d\n", result);
      return false;
   }

   port = op.port;
   return true;
}

bool Hypercall::event_channel_alloc_unbound (domid_t dom, evtchn_port_t &port)
{
   evtchn_alloc_unbound_t op;
   op.dom = DOMID_SELF;
   op.remote_dom = dom;

   // __HYPERVISOR_event_channel_op     32
   int result = HYPERVISOR_event_channel_op (EVTCHNOP_alloc_unbound, &op);

   if (0 != result)
   {
      trace ("HYPERVISOR_event_channel_op (EVTCHNOP_alloc_unbound) FAILED\n");
      trace ("   error code: %d\n", result);
      return false;
   }

   port = op.port;
   return true;
}

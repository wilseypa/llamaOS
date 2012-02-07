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
#include <xen/version.h>

#include <llamaos/xen/Hypercall.h>
#include <llamaos/config.h>
#include <llamaos/trace.h>

// include the hypercall macros from mini-os
typedef struct { unsigned long pte; } pte_t;
extern char hypercall_page [LLAMAOS_PAGE_SIZE];
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

   if (0 != HYPERVISOR_mmu_update(const_cast<mmu_update_t *>(req), request_count, &success_count, DOMID_SELF))
   {
      trace ("HYPERVISOR_mmu_update (count: %d) FAILED\n", request_count);

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
   if (0 != HYPERVISOR_set_callbacks (event_address, failsafe_address, 0UL))
   {
      trace ("HYPERVISOR_set_callbacks (event_address: %lx, failsafe_address: %lx) FAILED\n", event_address, failsafe_address);
      return false;
   }

   return true;
}

bool Hypercall::update_va_mapping (uint64_t virtual_address, uint64_t machine_address)
{
   pte_t val;
   val.pte = machine_address | 7;

   if (0 != HYPERVISOR_update_va_mapping (virtual_address, val, UVMF_INVLPG))
   {
      trace ("HYPERVISOR_update_va_mapping (pseudo_page: %lx, machine_page: %lx) FAILED\n", virtual_address, machine_address);
      return false;
   }

   return true;
}

bool Hypercall::update_va_mapping_nocache (uint64_t virtual_address, uint64_t machine_address)
{
   pte_t val;
   val.pte = machine_address | 0x17;

   if (0 != HYPERVISOR_update_va_mapping (virtual_address, val, UVMF_INVLPG))
   {
      trace ("HYPERVISOR_update_va_mapping (pseudo_page: %lx, machine_page: %lx) FAILED\n", virtual_address, machine_address);
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

bool Hypercall::grant_table_setup_table (unsigned int pages, unsigned long *frame_list)
{
   gnttab_setup_table_t setup_table;

   setup_table.dom = DOMID_SELF;
   setup_table.nr_frames = pages;
   set_xen_guest_handle(setup_table.frame_list, frame_list);

   if (0 != HYPERVISOR_grant_table_op (GNTTABOP_setup_table, &setup_table, 1))
   {
      trace ("HYPERVISOR_grant_table_op (GNTTABOP_setup_table) FAILED\n");
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

   if (0 != HYPERVISOR_grant_table_op (GNTTABOP_query_size, &query_size, 1))
   {
      trace ("HYPERVISOR_grant_table_op (GNTTABOP_query_size) FAILED\n");
      return false;
   }

   frames = query_size.nr_frames;
   max_frames = query_size.max_nr_frames;
   status = query_size.status;
   return true;
}

#if 0
// needs __XEN_INTERFACE_VERSION__=0x0003020a
bool Hypercall::grant_table_get_version (uint32_t &version)
{
   gnttab_get_version_t get_version;
   get_version.dom = DOMID_SELF;

   if (0 != HYPERVISOR_grant_table_op (GNTTABOP_get_version, &get_version, 1))
   {
      trace ("HYPERVISOR_grant_table_op (GNTTABOP_get_version) FAILED\n");
      return false;
   }

   version = get_version.version;
   return true;
}
#endif

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

bool Hypercall::event_channel_send (evtchn_port_t port)
{
   evtchn_send_t op;
   op.port = port;

   if (0 != HYPERVISOR_event_channel_op (EVTCHNOP_send, &op))
   {
      trace ("HYPERVISOR_event_channel_op (EVTCHNOP_send, port: %u) FAILED\n", port);
      return false;
   }

   return true;
}

bool Hypercall::event_channel_bind_virq (uint32_t virq, evtchn_port_t &port)
{
   evtchn_bind_virq_t op;
   op.virq = virq;
   op.vcpu = 0;

   if (0 != HYPERVISOR_event_channel_op (EVTCHNOP_bind_virq, &op))
   {
      trace ("HYPERVISOR_event_channel_op (EVTCHNOP_bind_virq, virq: %u) FAILED\n", virq);
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

   if (0 != HYPERVISOR_event_channel_op (EVTCHNOP_alloc_unbound, &op))
   {
      trace ("HYPERVISOR_event_channel_op (EVTCHNOP_alloc_unbound) FAILED\n");
      return false;
   }

   port = op.port;
   return true;
}



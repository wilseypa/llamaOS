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

#ifndef llamaos_xen_hypercall_h_
#define llamaos_xen_hypercall_h_

#include <cstdint>

#include <xen/xen.h>
#include <xen/event_channel.h>

namespace llamaos {
namespace xen {

/**
 * @brief C++ wrapper to Xen hypercall interface.
 *
 */
class Hypercall
{
public:

   /**
    * @brief
    *
    * @param table
    *
    */
   static bool set_trap_table (const trap_info_t *table);

   /**
    * @brief
    *
    * @param ptr Machine address of PTE.
    * @param val New contents of PTE.
    *
    */
   static bool mmu_update (uint64_t ptr, uint64_t val);

   /**
    * @brief
    *
    * @param req
    * @param count
    *
    */
   static bool mmu_update (const mmu_update_t *req, unsigned int count);

   // llamaOS UNSUPPORTED CALLS
   //   __HYPERVISOR_set_gdt               2
   //   __HYPERVISOR_stack_switch          3

   /**
    * @brief
    *
    * @param event_address
    * @param failsafe_address
    *
    */
   static bool set_callbacks (uint64_t event_address, uint64_t failsafe_address);

   // llamaOS UNSUPPORTED CALLS
   //   __HYPERVISOR_fpu_taskswitch        5
   //   __HYPERVISOR_sched_op_compat       6 /* compat since 0x00030101 */
   //   __HYPERVISOR_platform_op           7
   //   __HYPERVISOR_set_debugreg          8
   //   __HYPERVISOR_get_debugreg          9
   //   __HYPERVISOR_update_descriptor    10
   //   __HYPERVISOR_memory_op            12
   //   __HYPERVISOR_multicall            13

   /**
    * @brief
    *
    * @param pseudo_page
    * @param machine_page
    *
    */
   static bool update_va_mapping (uint64_t virtual_address, uint64_t machine_address);

   // llamaOS UNSUPPORTED CALLS
   //   __HYPERVISOR_set_timer_op         15
   //   __HYPERVISOR_event_channel_op_compat 16 /* compat since 0x00030202 */

   /**
    * @brief
    *
    * @param[out] major
    * @param[out] minor
    * 
    */
   static void xen_version (int &major, int &minor);

   /**
    * @brief
    *
    * @param string
    *
    */
   static bool console_io (const char *string);

   // llamaOS UNSUPPORTED CALLS
   //   __HYPERVISOR_physdev_op_compat    19 /* compat since 0x00030202 */

   /**
    * @brief Grant table operations.
    *
    */
   static bool grant_table_setup_table (unsigned int pages, unsigned long *frame_list);

   static bool grant_table_query_size (uint32_t &frames, uint32_t &max_frames, int16_t &status);

   // needs __XEN_INTERFACE_VERSION__=0x00030205
   // static bool grant_table_get_version (uint32_t &version);

   // llamaOS UNSUPPORTED CALLS
   //   __HYPERVISOR_vm_assist            21
   //   __HYPERVISOR_update_va_mapping_otherdomain 22
   //   __HYPERVISOR_iret                 23 /* x86 only */
   //   __HYPERVISOR_vcpu_op              24
   //   __HYPERVISOR_set_segment_base     25 /* x86/64 only */
   //   __HYPERVISOR_mmuext_op            26
   //   __HYPERVISOR_xsm_op               27
   //   __HYPERVISOR_nmi_op               28

   /**
    * @brief Voluntarily yield the CPU.
    *
    */
   static bool sched_op_yield ();

   /**
    * @brief Block execution of this VCPU until an event is received for processing.
    *
    */
   static bool sched_op_block ();

   /**
    * @brief Halt execution of this domain (all VCPUs) and notify the system controller.
    *
    * @param reason
    *
    */
   static bool sched_op_shutdown (unsigned int reason = 0);

   // llamaOS UNSUPPORTED CALLS
   //   __HYPERVISOR_callback_op          30
   //   __HYPERVISOR_xenoprof_op          31

   /**
    * @brief Event channel operations.
    *
    */
   static bool event_channel_send (evtchn_port_t port);

   static bool event_channel_bind_virq (uint32_t virq, evtchn_port_t &port);

   // llamaOS UNSUPPORTED CALLS
   //   __HYPERVISOR_physdev_op           33
   //   __HYPERVISOR_hvm_op               34
   //   __HYPERVISOR_sysctl               35
   //   __HYPERVISOR_domctl               36
   //   __HYPERVISOR_kexec_op             37
   //   __HYPERVISOR_tmem_op              38

};

} }

#endif  // llamaos_xen_hypercall_h_

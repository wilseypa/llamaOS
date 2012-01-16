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

#include <llamaos/memory/memory.h>
#include <llamaos/xen/Events.h>
#include <llamaos/xen/Hypercall.h>
#include <llamaos/xen/Hypervisor.h>
#include <llamaos/trace.h>

#define xchg(ptr,v) ((__typeof__(*(ptr)))__xchg((unsigned long)(v),(ptr),sizeof(*(ptr))))
#define __xg(x) ((volatile long *)(x))
static inline unsigned long __xchg(unsigned long x, volatile void * ptr, int size)
{
        switch (size) {
                case 1:
                        __asm__ __volatile__("xchgb %b0,%1"
                                :"=q" (x)
                                :"m" (*__xg(ptr)), "0" (x)
                                :"memory");
                        break;
                case 2:
                        __asm__ __volatile__("xchgw %w0,%1"
                                :"=r" (x)
                                :"m" (*__xg(ptr)), "0" (x)
                                :"memory");
                        break;
                case 4:
                        __asm__ __volatile__("xchgl %k0,%1"
                                :"=r" (x)
                                :"m" (*__xg(ptr)), "0" (x)
                                :"memory");
                        break;
                case 8:
                        __asm__ __volatile__("xchgq %0,%1"
                                :"=r" (x)
                                :"m" (*__xg(ptr)), "0" (x)
                                :"memory");
                        break;
        }
        return x;
}

using namespace llamaos;
using namespace llamaos::memory;
using namespace llamaos::xen;

extern "C"
void hypervisor_callback (void);

extern "C"
void do_hypervisor_callback (struct pt_regs * /* regs */)
{
   Hypervisor::get_instance ()->events.callback ();
}

extern "C"
void failsafe_callback (void);

Events::Events (shared_info_t *shared_info)
   :  shared_info(shared_info),
      vcpu_info(&shared_info->vcpu_info [0])
{
   Hypercall::set_callbacks (pointer_to_address (hypervisor_callback),
                             pointer_to_address (failsafe_callback));

   evtchn_port_t port = 0;
   Hypercall::event_channel_bind_virq (VIRQ_TIMER, port);
   trace ("VIRQ_TIMER port: %x\n", port);

   vcpu_info->evtchn_upcall_mask = 0;
}

Events::~Events ()
{
   Hypercall::set_callbacks (0UL, 0UL);
}

void Events::callback ()
{
//   trace ("Events callback...\n");
//   trace ("  evtchn_upcall_pending: %lx\n", vcpu_info->evtchn_upcall_pending);
//   trace ("     evtchn_upcall_mask: %lx\n", vcpu_info->evtchn_upcall_mask);
//   trace ("     evtchn_pending_sel: %lx\n", vcpu_info->evtchn_pending_sel);

   vcpu_info->evtchn_upcall_pending = 0;
///   vcpu_info->evtchn_pending_sel = 0;
   xchg(&vcpu_info->evtchn_pending_sel, 0);

   for (unsigned int i = 0; i < 64; i++)
   {
      if (0 != shared_info->evtchn_pending [i])
      {
//         trace ("  evtchn_pending [%u]: %lx\n", i, shared_info->evtchn_pending [i]);
         shared_info->evtchn_pending [i] = 0;
      }
   }
}

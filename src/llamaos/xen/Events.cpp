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

using namespace llamaos;
using namespace llamaos::memory;
using namespace llamaos::xen;

// pulled from mini-os x86/os.h
#define ADDR (*(volatile long *) addr)
static __inline__ void synch_clear_bit(int nr, volatile void * addr)
{
    __asm__ __volatile__ (
        "lock btrl %1,%0"
        : "=m" (ADDR) : "Ir" (nr) : "memory" );
}

extern "C"
void hypervisor_callback (void);

extern "C"
void do_hypervisor_callback (struct pt_regs * /* regs */)
{
   Hypervisor::get_instance ()->events.callback ();
}

extern "C"
void failsafe_callback (void);

static const unsigned int PENDING_SIZE = (sizeof(unsigned long) * 8);
static const unsigned int MASK_SIZE = (sizeof(unsigned long) * 8);

Events::Events (shared_info_t *shared_info)
   :  shared_info(shared_info),
      vcpu_info(&shared_info->vcpu_info [0]),
      handlers()
{
   Hypercall::set_callbacks (pointer_to_address (hypervisor_callback),
                             pointer_to_address (failsafe_callback));

   for (unsigned int i = 0; i < PENDING_SIZE; i++)
   {
      shared_info->evtchn_mask [i] = ~0UL;
   }

   vcpu_info->evtchn_upcall_mask = 0;
}

Events::~Events ()
{
   Hypercall::set_callbacks (0UL, 0UL);
}

void Events::alloc (domid_t domid, evtchn_port_t &port)
{

}

void Events::bind (unsigned int /* port */, event_handler_t /* handler */, void * /* data */)
{

}

void Events::unbind (unsigned int /* port */)
{

}

void Events::bind_virq (unsigned int virq, event_handler_t handler, void *data)
{
   evtchn_port_t port = 0;

   Hypercall::event_channel_bind_virq (virq, port);

   handlers [port] = std::pair<event_handler_t, void *> (handler, data);
   trace ("bind_virq: %x\n", port);

   shared_info->evtchn_mask [port / sizeof(unsigned long)] &= ~(1 << (port % sizeof(unsigned long)));
}

void Events::unbind_virq (unsigned int /* virq */)
{

}

void Events::bind_irq (unsigned int /* irq */, event_handler_t /* handler */, void * /* data */)
{

}

void Events::unbind_irq (unsigned int /* irq */)
{

}

void Events::callback () const
{
//   trace ("Events callback...\n");
//   trace ("  evtchn_upcall_pending: %lx\n", vcpu_info->evtchn_upcall_pending);
//   trace ("     evtchn_upcall_mask: %lx\n", vcpu_info->evtchn_upcall_mask);
//   trace ("     evtchn_pending_sel: %lx\n", vcpu_info->evtchn_pending_sel);
//   trace ("      evtchn_pending[0]: %lx\n", shared_info->evtchn_pending [0]);
//   trace ("      evtchn_pending[1]: %lx\n", shared_info->evtchn_pending [1]);

   vcpu_info->evtchn_upcall_pending = 0;
   vcpu_info->evtchn_pending_sel = 0;

   for (unsigned int i = 0; i < PENDING_SIZE; i++)
   {
      if (0UL != shared_info->evtchn_pending [i])
      {
         for (unsigned int j = 0; j < sizeof(unsigned long); j++)
         {
            if (shared_info->evtchn_pending [i] & (1 << j))
            {
               call_handler ((i * sizeof(unsigned long)) + j);
               synch_clear_bit(j, &shared_info->evtchn_pending [i]);
            }
         }
      }
   }
}

void Events::call_handler (evtchn_port_t port) const
{
   handler_map_t::const_iterator iter = handlers.find (port);

   if (iter == handlers.end ())
   {
      trace ("ignoring invalid handler: %x\n", port);
      return;
   }

   iter->second.first (iter->second.second);
}

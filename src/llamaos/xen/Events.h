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

#ifndef llamaos_xen_events_h_
#define llamaos_xen_events_h_

#include <cstdint>

#include <map>

#include <xen/xen.h>
#include <xen/event_channel.h>

struct shared_info;
namespace llamaos {
namespace xen {

typedef void (*event_handler_t)(void *);
typedef std::map<evtchn_port_t, std::pair<event_handler_t, void *> > handler_map_t;

class Events
{
public:
   Events (shared_info_t *shared_info);
   virtual ~Events ();

   void bind (evtchn_port_t port, event_handler_t handler, void *data);
   void unbind (evtchn_port_t port);

   void bind_virq (unsigned int virq, event_handler_t handler, void *data);
   void unbind_virq (unsigned int virq);

   void bind_irq (unsigned int irq, event_handler_t handler, void *data);
   void unbind_irq (unsigned int irq);

   void callback () const;

private:
   Events ();
   Events (const Events &);
   Events &operator= (const Events &);

   void call_handler (evtchn_port_t port) const;

   shared_info_t *const shared_info;
   vcpu_info_t *const vcpu_info;

   handler_map_t handlers;

};

} }

#endif  // llamaos_xen_events_h_

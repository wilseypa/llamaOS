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

#include <llamaos/memory/Memory.h>
#include <llamaos/xen/Console.h>
#include <llamaos/xen/Hypercall.h>
#include <llamaos/Trace.h>

using namespace llamaos::xen;

Console::Console (xencons_interface *interface, evtchn_port_t port)
   :  interface(interface),
      port(port)
{
   if (interface->in_cons != interface->in_prod)
   {
      trace ("Console in queue not initialized: %x, %x\n", interface->in_cons, interface->in_prod);
      interface->in_cons = interface->in_prod;
   }

   if (interface->out_cons != interface->out_prod)
   {
      trace ("Console out queue not initialized: %x, %x\n", interface->out_cons, interface->out_prod);
   }
}

Console::~Console ()
{

}

void Console::event_handler (void *data)
{
   Console *console = static_cast<Console *>(data);

   // ensure write is processed
   mb();

   while ((console->interface->in_prod - console->interface->in_cons) > 0)
   {
      // ensure write is processed
      wmb();

      // increment index
      console->interface->in_cons++;

      mb();
   }
}

void Console::write (char data) const
{
   XENCONS_RING_IDX cons, prod;

   cons = interface->out_cons;
   prod = interface->out_prod;

   if ((prod - cons) > sizeof(interface->out))
   {
      trace ("Console out queue corrupted: %x, %x\n", cons, prod);
      // throw
      return;
   }

   while ((prod - cons) == sizeof(interface->out))
   {
      Hypercall::event_channel_send (port);
      Hypercall::sched_op_yield ();

      cons = interface->out_cons;
      prod = interface->out_prod;
   }

   XENCONS_RING_IDX index = MASK_XENCONS_IDX(prod, interface->out);

   mb ();
   interface->out [index] = data;

   wmb();
   interface->out_prod = prod + 1;

   Hypercall::event_channel_send (port);
}

void Console::write (const char *data, unsigned int length) const
{
   // loop over entire data array
   for (unsigned int i = 0; i < length; i++)
   {
      // console needs a CR when only an LF is seen
      if ('\n' == data [i])
      {
         this->write ('\r');
      }

      this->write (data [i]);
   }
}

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

#include <llamaos/xen/Console.h>
#include <llamaos/xen/Hypercall.h>

using namespace llamaos::xen;

#define mb()  __asm__ __volatile__ ( "mfence" : : : "memory")
#define wmb() __asm__ __volatile__ ( "" : : : "memory")

Console::Console (xencons_interface *interface, evtchn_port_t port)
   :  interface(interface),
      port(port)
{

}

Console::~Console ()
{

}

#include <llamaos/trace.h>
void Console::write (char data) const
{
   // ensure write is processed
   mb();

   // check for space in the ring
   if ((interface->out_prod - interface->out_cons) >= sizeof(interface->out))
   {
      // tell dom0 to consume some data
      Hypercall::event_channel_send (port);

      // yield cpu to dom0
      llamaos::xen::Hypercall::sched_op_yield ();
      mb();
   }

   // get current index into ring and write data
   XENCONS_RING_IDX index = MASK_XENCONS_IDX(interface->out_prod, interface->out);
   interface->out [index] = data;

   // ensure write is processed
   wmb();

   // increment index
   interface->out_prod++;
}

void Console::write (const char *data, unsigned int length) const
{
   // loop over entire data array
   for (unsigned int i = 0; i < length; i++)
   {
      // console needs a CR when only an LF is seen
      if ('\n' == data [i])
      {
         write ('\r');
      }

      this->write (data [i]);
   }

   Hypercall::event_channel_send (port);
}

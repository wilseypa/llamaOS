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
#include <cstdarg>
#include <cstdio>
#include <cstring>

#include <llamaos/xen/Hypercall.h>

#if 0
#include <xen/event_channel.h>
#include <xen/io/console.h>

#define mb()  __asm__ __volatile__ ( "mfence" : : : "memory")
#define rmb() __asm__ __volatile__ ( "lfence" : : : "memory")
#define wmb() __asm__ __volatile__ ( "" : : : "memory")

static xencons_interface *interface = nullptr;
static uint32_t event_channel = 0;

void llamaos_init_console (xencons_interface *cons_interface, uint32_t evtchn)
{
   interface = cons_interface;
   event_channel = evtchn;
}

static void console_write (const char *s)
{
   if (nullptr != interface)
   {
      const char *data = s;
      unsigned len = strlen (s);

      unsigned sent = 0;

      XENCONS_RING_IDX cons, prod;

      cons = interface->out_cons;
      prod = interface->out_prod;
      mb();

      while ((sent < len) && ((prod - cons) < sizeof(interface->out)))
      {
         while ((prod - cons) > sizeof(interface->out))
         {
            llamaos::xen::Hypercall::sched_op_yield ();
            mb();
         }

         if (data [sent] == '\n')
         {
            interface->out[MASK_XENCONS_IDX(prod++, interface->out)] = '\r';
         }

         interface->out[MASK_XENCONS_IDX(prod++, interface->out)] = data[sent++];
      }

      wmb();
      interface->out_prod = prod;

      llamaos::xen::Hypercall::event_channel_send (event_channel);
   }
}
#endif

namespace llamaos {

int trace (const char *format, ...)
{
   // prep variable arguments
   va_list arg;
   va_start (arg, format);

   // copy formatted output to buffer
   char buffer [256] = { '\0' };
   int count = vsnprintf (buffer, sizeof(buffer)-1, format, arg);

   // term variable arguments
   va_end (arg);

   // write buffer to system output/log
   xen::Hypercall::console_io (buffer);

//   console_write (buffer);

   // return the number characters written
   return count;
}

}

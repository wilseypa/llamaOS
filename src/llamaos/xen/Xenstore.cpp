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

Some of this file's content copied from Chisnall, The Definitive Guide to the
Xen Hypervisor. Copyright statement is as follows:

Copyright (c) 2007 David Chisnall

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/

#include <cstring>

#include <stdexcept>

#include <llamaos/xen/Hypercall.h>
#include <llamaos/xen/Xenstore.h>
#include <stdlib.h>

using namespace std;
using namespace llamaos::xen;

extern char _text;

static uint32_t req_id = 0;

#define mb()  __asm__ __volatile__ ( "mfence" : : : "memory")
#define rmb() __asm__ __volatile__ ( "lfence" : : : "memory")
#define wmb() __asm__ __volatile__ ( "" : : : "memory")

#define NOTIFY() \
   do {\
      Hypercall::event_channel_send(port);\
   } while(0)

#define IGNORE(n) \
   do {\
      char buffer[XENSTORE_RING_SIZE];\
      read_response(buffer, n);\
   } while(0)

static void write_request (xenstore_domain_interface *interface,
                           const char *request,
                           unsigned int request_length)
{
   /* Check that the message will fit */
   if (request_length > XENSTORE_RING_SIZE)
   {
      throw runtime_error ("Xenstore write_request: message too long");
   }

   unsigned int i = interface->req_prod;
   unsigned int j = 0;

   while (j < request_length)
   {
      /* Wait for the back end to clear enough space in the buffer */
      XENSTORE_RING_IDX data;

      do
      {
         data = i - interface->req_cons;
         mb();
      } while (data >= sizeof(interface->req));

      /* Copy the byte */
      int ring_index = MASK_XENSTORE_IDX (i++);
      interface->req [ring_index] = request [j++];
   }

   /* Ensure that the data really is in the ring before continuing */
   wmb();
   interface->req_prod = i;
}

static void write_request (xenstore_domain_interface *interface,
                           const struct xsd_sockmsg &sockmsg)
{
   write_request (interface, reinterpret_cast<const char *>(&sockmsg), sizeof(struct xsd_sockmsg));
}

static void write_request (xenstore_domain_interface *interface, const string &message)
{
   write_request (interface, message.c_str (), message.size () + 1);
}

static void read_response (xenstore_domain_interface *interface,
                           struct xsd_sockmsg &sockmsg)
{
   char *message = &sockmsg;

   unsigned int i = interface->rsp_cons;
   unsigned int j = 0;

   while (j < sizeof(struct xsd_sockmsg))
   {
      /* Wait for the back end put data in the buffer */
      XENSTORE_RING_IDX data;

      do
      {
         data = interface->rsp_prod - i;
         mb();
      } while (data == 0);

      /* Copy the byte */
      int ring_index = MASK_XENSTORE_IDX(i++);
      message [j++] = interface->rsp[ring_index];
   }

   interface->rsp_cons = i;
}

Xenstore::Xenstore (xenstore_domain_interface *interface, evtchn_port_t port)
   :  interface(interface),
      port(port)
{

}

string Xenstore::read (const string &key) const
{
   int key_length = strlen (key.c_str ());

   struct xsd_sockmsg msg;
   msg.type = XS_READ;
   msg.req_id = req_id;
   msg.tx_id = 0;
   msg.len = key_length + 1;

   write_request (interface, msg);
   write_request (interface, key);

//   write_request ((const char*)&msg, sizeof(msg));
//   write_request (key, key_length + 1);

   /* Notify the back end */
   NOTIFY();

   read_response ((char*)&msg, sizeof(msg));

   if (msg.req_id != req_id++)
   {
      IGNORE(msg.len);
      return false;
   }

   /* If we have enough space in the buffer */
   if (length >= msg.len)
   {
      read_response (value, msg.len);
      return true;
   }

   /* Truncate */
   read_response (value, length);
   IGNORE(msg.len - length);
   return false;
}

#if 0
/* Write a request to the back end */
bool Xenstore::write_request (const char *message, int length) const
{
   /* Check that the message will fit */
   if (length > XENSTORE_RING_SIZE)
   {
      return false;
   }

   int i;

   for(i = domain_interface->req_prod; length > 0; i++, length--)
   {
      /* Wait for the back end to clear enough space in the buffer */
      XENSTORE_RING_IDX data;

      do
      {
         data = i - domain_interface->req_cons;
         mb();
      } while (data >= sizeof(domain_interface->req));

      /* Copy the byte */
      int ring_index = MASK_XENSTORE_IDX(i);
      domain_interface->req[ring_index] = *message;
      message++;
   }

   /* Ensure that the data really is in the ring before continuing */
   wmb();
   domain_interface->req_prod = i;

   return true;
}

/* Read a response from the response ring */
bool Xenstore::read_response (char *message, int length) const
{
   int i;

   for(i = domain_interface->rsp_cons; length > 0; i++, length--)
   {
      /* Wait for the back end put data in the buffer */
      XENSTORE_RING_IDX data;

      do
      {
         data = domain_interface->rsp_prod - i;
         mb();
      } while (data == 0);

      /* Copy the byte */
      int ring_index = MASK_XENSTORE_IDX(i);
      *message = domain_interface->rsp[ring_index];
      message++;
   }

   domain_interface->rsp_cons = i;
   return true;
}
#endif

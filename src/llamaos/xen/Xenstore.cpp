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

#include <cstring>
#include <cstdlib>

#include <stdexcept>
#include <sstream>

#include <llamaos/xen/Hypercall.h>
#include <llamaos/xen/Xenstore.h>

using namespace std;
using namespace llamaos::xen;

#define mb()  __asm__ __volatile__ ( "mfence" : : : "memory")
#define wmb() __asm__ __volatile__ ( "" : : : "memory")

#if 0
namespace xenstore {

void write (xenstore_domain_interface *interface, char data)
{
   // ensure write is processed
   mb();

   // check for space in the ring
   if ((interface->req_prod - interface->req_cons) >= sizeof(interface->req))
   {
      // tell dom0 to consume some data
      Hypercall::event_channel_send (port);

      // yield cpu to dom0
      llamaos::xen::Hypercall::sched_op_yield ();
      mb();
   }

   // get current index into ring and write data
   XENSTORE_RING_IDX index = MASK_XENSTORE_IDX(interface->req_prod, interface->req);
   interface->req [index] = data;

   // ensure write is processed
   wmb();

   // increment index
   interface->req_prod++;
}

static void write (xenstore_domain_interface *interface, const char *data, unsigned int length)
{
   /* Check that the message will fit */
   if (length > XENSTORE_RING_SIZE)
   {
      throw runtime_error ("Xenstore write: message too long");
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

static void write (xenstore_domain_interface *interface,
                   const struct xsd_sockmsg &sockmsg)
{
   write_request (interface, reinterpret_cast<const char *>(&sockmsg), sizeof(struct xsd_sockmsg));
}

}





static void write_request (xenstore_domain_interface *interface, const string &message)
{
   write_request (interface, message.c_str (), message.size () + 1);
}

static void read_response (xenstore_domain_interface *interface,
                           struct xsd_sockmsg &sockmsg)
{
   char *message = static_cast<char *>(&sockmsg);

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
#endif



static uint32_t xenstore_req_id = 1;

Xenstore::Xenstore (xenstore_domain_interface *interface, evtchn_port_t port)
   :  interface(interface),
      port(port)
{

}

Xenstore::~Xenstore ()
{

}

void Xenstore::write_request (const char *data, unsigned int length) const
{
   if (length > XENSTORE_RING_SIZE)
   {
      throw runtime_error ("Xenstore write: message too long");
   }

   // check for space in the ring
   if ((interface->req_prod - interface->req_cons) < length)
   {
      // tell dom0 to consume some data
      Hypercall::event_channel_send (port);

      // yield cpu to dom0
      llamaos::xen::Hypercall::sched_op_yield ();
      mb();
   }

   for (unsigned int i = 0; i < length; i++)
   {
      // get current index into ring and write data
      XENSTORE_RING_IDX index = MASK_XENSTORE_IDX(interface->req_prod);
      interface->req [index] = data [i];
   }

   // ensure write is processed
   wmb();

   // increment index
   interface->req_prod += length;
}

void Xenstore::write_request (const std::string &key) const
{
   struct xsd_sockmsg msg;

   msg.type = XS_READ;
   msg.req_id = xenstore_req_id;
   msg.tx_id = 0;
   msg.len = key.size () + 1;

   write_request (reinterpret_cast<const char *>(&msg), sizeof(msg));
   write_request (key.c_str (), key.size () + 1);
}

void Xenstore::read_response (char *data, unsigned int length) const
{
   if (length > XENSTORE_RING_SIZE)
   {
      throw runtime_error ("Xenstore write: message too long");
   }

   for (unsigned int i = 0; i < length; i++)
   {
      while (0 == (interface->rsp_prod - interface->rsp_cons))
      {
         // yield cpu to dom0
         llamaos::xen::Hypercall::sched_op_yield ();
         mb ();
      }

      // get current index into ring and read data
      XENSTORE_RING_IDX index = MASK_XENSTORE_IDX(interface->rsp_cons);
      data [i] = interface->rsp [index];
   }

   interface->rsp_cons += length;
}

string Xenstore::read_response (unsigned int length) const
{
   stringstream sstream;

   for (unsigned int i = 0; i < length; i++)
   {
      while (0 == (interface->rsp_prod - interface->rsp_cons))
      {
         // yield cpu to dom0
         llamaos::xen::Hypercall::sched_op_yield ();
         mb ();
      }

      // get current index into ring and read data
      XENSTORE_RING_IDX index = MASK_XENSTORE_IDX(interface->rsp_cons);
      sstream << interface->rsp [index];
   }

   interface->rsp_cons += length;

   return sstream.str ();
}

string Xenstore::read_response () const
{
   struct xsd_sockmsg msg;
   read_response (reinterpret_cast<char *>(&msg), sizeof(msg));

   if (msg.req_id != xenstore_req_id++)
   {
      throw runtime_error ("Xenstore read: returned invalid request id");
   }

   return read_response (msg.len);
}

string Xenstore::read (const string &key) const
{
   // write request to Xenstore
   write_request (key);

   // alert Xenstore of our message
   Hypercall::event_channel_send (port);

   // reasponse from Xenstore
   return read_response ();
#if 0

   write_request (msg, key);

   /* Notify the back end */
   Hypercall::event_channel_send (port);

   return read_response ();

//   msg = read_response ();

//   if (msg.req_id != req_id++)
//   {
//      throw runtime_error ("Xenstore read: returned invalid request id");
//   }

//   return read_response (msg.len);
#endif
}

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
#include <iostream>
#include <sstream>

#include <llamaos/xen/Hypercall.h>
#include <llamaos/xen/Xenstore.h>
#include <llamaos/Trace.h>

using namespace std;
using namespace llamaos::xen;

#define mb()  __asm__ __volatile__ ( "mfence" : : : "memory")
#define wmb() __asm__ __volatile__ ( "" : : : "memory")

static uint32_t xenstore_req_id = 1;

Xenstore::Xenstore (xenstore_domain_interface *interface, evtchn_port_t port)
   :  interface(interface),
      port(port)
{

}

Xenstore::~Xenstore ()
{

}

void Xenstore::start_transaction (uint32_t id)
{
   struct xsd_sockmsg msg;

   msg.type = XS_TRANSACTION_START;
   msg.req_id = xenstore_req_id;
   msg.tx_id = id;
   msg.len = 1;

   write_request (reinterpret_cast<const char *>(&msg), sizeof(msg));
   write_request ("", 1);

   // alert Xenstore of our message
   Hypercall::event_channel_send (port);

   // read response from Xenstore
   read_response ();
}

void Xenstore::end_transaction (uint32_t id)
{
   struct xsd_sockmsg msg;

   msg.type = XS_TRANSACTION_END;
   msg.req_id = xenstore_req_id;
   msg.tx_id = id;
   msg.len = 1;

   write_request (reinterpret_cast<const char *>(&msg), sizeof(msg));
   write_request ("", 1);

   // alert Xenstore of our message
   Hypercall::event_channel_send (port);

   // read response from Xenstore
   read_response ();
}

string Xenstore::read (const string &key) const
{
   // write request to Xenstore
   write_read_request (key);

   // alert Xenstore of our message
   Hypercall::event_channel_send (port);

   // read response from Xenstore
   return read_response ();
}

void Xenstore::write (const std::string &key, const std::string &value) const
{
   // write request to Xenstore
   write_write_request (key, value);

   // alert Xenstore of our message
   Hypercall::event_channel_send (port);

   // read response from Xenstore
   read_response ();
}

void Xenstore::write_request (const char *data, unsigned int length) const
{
   if (length > XENSTORE_RING_SIZE)
   {
      cout << "Xenstore write: message too long" << endl;
      // throw runtime_error ("Xenstore write: message too long");
      return;
   }

   for (unsigned int i = 0; i < length; i++)
   {
      // check for space in the ring
      while ((interface->req_prod - interface->req_cons) >= XENSTORE_RING_SIZE)
      {
         // tell dom0 to consume some data
         Hypercall::event_channel_send (port);

         // yield cpu to dom0
         // llamaos::xen::Hypercall::sched_op_yield ();
         mb();
      }

      // get current index into ring and write data
      XENSTORE_RING_IDX index = MASK_XENSTORE_IDX(interface->req_prod);
      interface->req [index] = data [i];

      // ensure write is processed
      wmb();

      // increment index
      interface->req_prod++;
   }

#if 0
   // check for space in the ring
   if ((interface->req_prod - interface->req_cons) < length)
   {
      // tell dom0 to consume some data
      Hypercall::event_channel_send (port);

      // yield cpu to dom0
      // llamaos::xen::Hypercall::sched_op_yield ();
      mb();
   }

   XENSTORE_RING_IDX req_prod = interface->req_prod;

   for (unsigned int i = 0; i < length; i++)
   {
      // get current index into ring and write data
      XENSTORE_RING_IDX index = MASK_XENSTORE_IDX(req_prod++);
      interface->req [index] = data [i];
   }

   // ensure write is processed
   wmb();

   // increment index
   interface->req_prod += length;
#endif
}

void Xenstore::write_read_request (const std::string &key) const
{
   struct xsd_sockmsg msg;

   msg.type = XS_READ;
   msg.req_id = xenstore_req_id;
   msg.tx_id = 0;
   msg.len = key.size () + 1;

   write_request (reinterpret_cast<const char *>(&msg), sizeof(msg));
   write_request (key.c_str (), key.size () + 1);
}

void Xenstore::write_write_request (const std::string &key, const std::string &value) const
{
   struct xsd_sockmsg msg;

   msg.type = XS_WRITE;
   msg.req_id = xenstore_req_id;
   msg.tx_id = 0;
   msg.len = key.size () + 1 + value.size () + 1;

   write_request (reinterpret_cast<const char *>(&msg), sizeof(msg));
   write_request (key.c_str (), key.size () + 1);
   write_request (value.c_str (), value.size () + 1);
}

void Xenstore::read_response (char *data, unsigned int length) const
{
   if (length > XENSTORE_RING_SIZE)
   {
      cout << "Xenstore write: message too long" << endl;
      // throw runtime_error ("Xenstore write: message too long");
      return;
   }

//   XENSTORE_RING_IDX rsp_cons = interface->rsp_cons;

   for (unsigned int i = 0; i < length; i++)
   {
//      while (0 == (interface->rsp_prod - rsp_cons))
      while (0 == (interface->rsp_prod - interface->rsp_cons))
      {
         // yield cpu to dom0
         // llamaos::xen::Hypercall::sched_op_yield ();
         mb ();
      }

      // get current index into ring and read data
//      XENSTORE_RING_IDX index = MASK_XENSTORE_IDX(rsp_cons++);
      XENSTORE_RING_IDX index = MASK_XENSTORE_IDX(interface->rsp_cons);
      data [i] = interface->rsp [index];
      interface->rsp_cons++;
   }

//   interface->rsp_cons += length;
}

string Xenstore::read_response (unsigned int length) const
{
   stringstream sstream;
//   XENSTORE_RING_IDX rsp_cons = interface->rsp_cons;

   for (unsigned int i = 0; i < length; i++)
   {
//      while (0 == (interface->rsp_prod - rsp_cons))
      while (0 == (interface->rsp_prod - interface->rsp_cons))
      {
         // yield cpu to dom0
         // llamaos::xen::Hypercall::sched_op_yield ();
         mb ();
      }

      // get current index into ring and read data
      // XENSTORE_RING_IDX index = MASK_XENSTORE_IDX(rsp_cons++);
      XENSTORE_RING_IDX index = MASK_XENSTORE_IDX(interface->rsp_cons);
      sstream << interface->rsp [index];
      interface->rsp_cons++;
   }

//   interface->rsp_cons += length;

   return sstream.str ();
}

string Xenstore::read_response () const
{
   struct xsd_sockmsg msg;
   read_response (reinterpret_cast<char *>(&msg), sizeof(msg));

   if (msg.req_id != xenstore_req_id++)
   {
      // !BAM lets not do this now since throw is unreliable
      // throw runtime_error ("Xenstore read: returned invalid request id");
      std::cout << "wrong xenstore msg id detected: " << msg.req_id << " != " << (xenstore_req_id - 1) << std::endl;
   }

   return read_response (msg.len);
}

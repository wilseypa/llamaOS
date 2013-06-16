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

#include <llamaos/memory/Memory.h>
#include <llamaos/xen/Hypercall.h>
#include <llamaos/xen/Xenstore.h>
#include <llamaos/Trace.h>

using namespace std;
using namespace llamaos::memory;
using namespace llamaos::xen;

Xenstore::Xenstore (xenstore_domain_interface *interface, evtchn_port_t port)
   :  interface(interface),
      port(port),
      req_id(1)
{
   if (interface->req_cons != interface->req_prod)
   {
      trace ("Xenstore request queue not initialized: %x, %x\n", interface->req_cons, interface->req_prod);
   }

   if (interface->rsp_cons != interface->rsp_prod)
   {
      trace ("Xenstore response queue not initialized: %x, %x\n", interface->rsp_cons, interface->rsp_prod);
      interface->rsp_cons = interface->rsp_prod;
   }
}

Xenstore::~Xenstore ()
{

}

void Xenstore::start_transaction (uint32_t id)
{
   struct xsd_sockmsg msg;

   msg.type = XS_TRANSACTION_START;
   msg.req_id = req_id;
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
   msg.req_id = req_id;
   msg.tx_id = id;
   msg.len = 1;

   write_request (reinterpret_cast<const char *>(&msg), sizeof(msg));
   write_request ("", 1);

   // alert Xenstore of our message
   Hypercall::event_channel_send (port);

   // read response from Xenstore
   read_response ();
}

string Xenstore::read_string (const string &key) const
{
   // write request to Xenstore
   write_read_request (key);

   // alert Xenstore of our message
   Hypercall::event_channel_send (port);

   // read response from Xenstore
   return read_response ();
}

void Xenstore::write_string (const std::string &key, const std::string &value) const
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
   unsigned long wd = 0;
   XENSTORE_RING_IDX cons, prod;

   // logic from Linux kernel
   while (length > 0)
   {
      cons = interface->req_cons;
      prod = interface->req_prod;

      if ((prod - cons) > XENSTORE_RING_SIZE)
      {
         trace ("Xenstore request queue corrupted: %x, %x\n", cons, prod);
         // throw
         return;
      }
      else if ((prod - cons) != XENSTORE_RING_SIZE)
      {
         XENSTORE_RING_IDX index = MASK_XENSTORE_IDX(prod);

         mb ();
         interface->req [index] = *data;

//         trace ("write_request: (%d), %d, %d\n", (int)*data, length, prod);
         data++;
         length--;

         wmb();
         interface->req_prod = prod + 1;
         wd = 0;
      }

      Hypercall::event_channel_send (port);

      if (++wd > 10000000)
      {
         cout << "stuck in write_request" << endl;
         break;
      }
   }
}

void Xenstore::write_read_request (const std::string &key) const
{
   struct xsd_sockmsg msg;

   msg.type = XS_READ;
   msg.req_id = req_id;
   msg.tx_id = 0;
   msg.len = key.size () + 1;

   write_request (reinterpret_cast<const char *>(&msg), sizeof(msg));
   write_request (key.c_str (), key.size ());
   write_request ("", 1);
}

void Xenstore::write_write_request (const std::string &key, const std::string &value) const
{
   struct xsd_sockmsg msg;

   msg.type = XS_WRITE;
   msg.req_id = req_id;
   msg.tx_id = 0;
// even though I read this is needed, it isn't?
// trying it makes weird values like "2\000", "2" without
//   msg.len = key.size () + 1 + value.size () + 1;
   msg.len = key.size () + 1 + value.size ();

   write_request (reinterpret_cast<const char *>(&msg), sizeof(msg));
   write_request (key.c_str (), key.size () + 1);
//   write_request (value.c_str (), value.size () + 1);
   write_request (value.c_str (), value.size ());
}

void Xenstore::read_response (char *data, unsigned int length) const
{
   unsigned long wd = 0;
   XENSTORE_RING_IDX cons, prod;

   // logic from Linux kernel
   while (length > 0)
   {
      cons = interface->rsp_cons;
      prod = interface->rsp_prod;

      if ((prod - cons) > XENSTORE_RING_SIZE)
      {
         trace ("Xenstore response queue corrupted: %x, %x\n", cons, prod);
         interface->rsp_cons = interface->rsp_prod;
         // throw
         return;
      }
      else if ((prod - cons) != 0)
      {
         XENSTORE_RING_IDX index = MASK_XENSTORE_IDX(cons);

         rmb();
         *data = interface->rsp [index];

//         trace ("read_response: %d\n", (int)*data);

         data++;
         length--;

         mb();
         interface->rsp_cons = cons + 1;
         wd = 0;
      }

      Hypercall::event_channel_send (port);

      if (++wd > 10000000)
      {
         cout << "stuck in read_response2" << endl;
         break;
      }
   }
}

string Xenstore::read_response (unsigned int length) const
{
   unsigned long wd = 0;
   XENSTORE_RING_IDX cons, prod;
   stringstream sstream;

   // logic from Linux kernel
   while (length > 0)
   {
      cons = interface->rsp_cons;
      prod = interface->rsp_prod;

      if ((prod - cons) > XENSTORE_RING_SIZE)
      {
         trace ("Xenstore response queue corrupted: %x, %x\n", cons, prod);
         interface->rsp_cons = interface->rsp_prod;
         // throw
         return "error response queue corrupted";
      }
      else if ((prod - cons) != 0)
      {
         XENSTORE_RING_IDX index = MASK_XENSTORE_IDX(cons);

         rmb();
         sstream << interface->rsp [index];

//         trace ("read_response: %s\n", sstream.str().c_str());
         length--;

         mb();
         interface->rsp_cons = cons + 1;
         wd = 0;
      }

      Hypercall::event_channel_send (port);

      if (++wd > 10000000)
      {
         cout << "stuck in read_response1" << endl;
         break;
      }
   }

   return sstream.str ();
}

string Xenstore::read_response () const
{
   struct xsd_sockmsg msg;
   read_response (reinterpret_cast<char *>(&msg), sizeof(msg));

//   cout << "   read xsd message:" << endl;
//   cout << "               type:" << msg.type << endl;
//   cout << "             req_id:" << msg.req_id << endl;
//   cout << "              tx_id:" << msg.tx_id << endl;
//   cout << "                len:" << msg.len << endl;

   if (msg.req_id != req_id++)
   {
      // !BAM lets not do this now since throw is unreliable
      // throw runtime_error ("Xenstore read: returned invalid request id");
      std::cout << "wrong xenstore msg id detected: " << msg.req_id << " != " << (req_id - 1) << std::endl;
      cout.flush();
      for (;;);
   }

   return read_response (msg.len);
}

static vector<string> split (const string &input)
{
   vector<string> tokens;

   if (input != "ENOENT")
   {
      string::const_iterator first = input.begin ();
      string::const_iterator mark = input.begin ();
      string::const_iterator last = input.end ();

      while (first != last)
      {
   //      if (isspace (*first))
         if ('\0' == *first)
         {
            string token = string (mark, first);

            if (token.length () > 0)
            {
               tokens.push_back (token);
            }

            mark = first + 1;
         }

         first++;
      }

      string token = string (mark, first);

      if (token.length () > 0)
      {
         tokens.push_back (token);
      }
   }

   return tokens;
}

vector<string> Xenstore::list (const string &key) const
{
   // write request to Xenstore
   // write_read_request (key);
   struct xsd_sockmsg msg;

   msg.type = XS_DIRECTORY;
   msg.req_id = req_id;
   msg.tx_id = 0;
   msg.len = key.size () + 1;

   write_request (reinterpret_cast<const char *>(&msg), sizeof(msg));
   write_request (key.c_str (), key.size ());
   write_request ("", 1);

   // alert Xenstore of our message
   Hypercall::event_channel_send (port);

   // read response from Xenstore
   return split (read_response ());
}

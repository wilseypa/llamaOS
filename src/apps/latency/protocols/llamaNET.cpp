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

#include <iostream>

#include <latency/protocols/llamaNET.h>
#include <latency/parse_args.cpp>
#include <latency/verify.h>
#include <llamaos/api/sleep.h>
#include <llamaos/xen/Hypervisor.h>

using namespace std;
using namespace latency;
using namespace latency::protocols;
using namespace llamaos;
using namespace llamaos::xen;

Protocol *Protocol::create (int argc, char *argv [])
{
   return new llamaNET (argc, argv);
}

static uint32_t seq = 1;

static domid_t get_domd_id (int node)
{
   // for now it's just self minus node % 6
   domid_t self_id = Hypervisor::get_instance ()->domid;

   return (self_id - 1 - (node / 2));
}

llamaNET::llamaNET (int argc, char *argv [])
   :  node(parse<uint32_t>(argc, argv, "--node", 0U)),
      client((node % 2) == 0),
      interface(get_domd_id (node), (node / 2))
{
   cout << "latency-llamaNET" << endl
        << "  node: " << node << endl;
}

llamaNET::~llamaNET ()
{

}

bool llamaNET::root_node ()
{
   return client;
}

bool llamaNET::startup (unsigned long max_msg_size)
{
   return true;
}

bool llamaNET::cleanup ()
{
   api::sleep (2);

   // release interface ?
   return true;
}

bool llamaNET::run_verify (unsigned long msg_size)
{
   // TCP doesn't send anything for a zero length message, so make it 8 bytes
   msg_size = max (8UL, msg_size);

   // llamaNET is configured for 1 page max message and has a 36 byte header, so make it 4060 bytes
   msg_size = min (4060UL, msg_size);

   net::llamaNET::Protocol_header *header;
   unsigned char *data;

   // dalai initiates the trial
   if (client)
   {
      header = interface.get_send_buffer ();
      header->dest = (node % 2) ? (node - 1) : (node + 1);
      header->src = node;
      header->type = 1;
      header->seq = seq++;
      header->len = msg_size;

      // get pointer to data section of buffer
      data = reinterpret_cast<unsigned char *>(header + 1);

      // marks all bytes with alpha chars (a,b,c,...)
      mark_data_alpha (data, msg_size);

      // send/recv and verify the data has been changed to numerals (1,2,3,...)
      interface.send (header);
      header = interface.recv (node);

      // get pointer to data section of buffer
      data = reinterpret_cast<unsigned char *>(header + 1);

      if (verify_data_numeric (data, msg_size))
      {
         interface.release_recv_buffer (header);

         return true;
      }
   }
   else
   {
      header = interface.recv (node);

      // get pointer to data section of buffer
      data = reinterpret_cast<unsigned char *>(header + 1);

      if (verify_data_alpha (data, msg_size))
      {
         interface.release_recv_buffer (header);

         header = interface.get_send_buffer ();
         header->dest = (node % 2) ? (node - 1) : (node + 1);
         header->src = node;
         header->type = 1;
         header->seq = seq++;
         header->len = msg_size;

         // get pointer to data section of buffer
         data = reinterpret_cast<unsigned char *>(header + 1);

         // marks all bytes with numerals and send
         mark_data_numeric (data, msg_size);

         interface.send (header);
         return true;
      }
   }

   return false;
}

bool llamaNET::run_trial (unsigned long msg_size, unsigned long trial_number)
{
   // TCP doesn't send anything for a zero length message, so make it 8 bytes
   msg_size = max (8UL, msg_size);

   // llamaNET is configured for 1 page max message and has a 36 byte header, so make it 4060 bytes
   msg_size = min (4060UL, msg_size);

   net::llamaNET::Protocol_header *header;
   unsigned char *data;

   // dalai initiates the trial
   if (client)
   {
      header = interface.get_send_buffer ();
      header->dest = (node % 2) ? (node - 1) : (node + 1);
      header->src = node;
      header->type = 1;
      header->seq = seq++;
      header->len = msg_size;

      interface.send (header);

      header = interface.recv (node);

      // get pointer to data section of buffer
      data = reinterpret_cast<unsigned char *>(header + 1);

      if (*(reinterpret_cast<unsigned long *>(data)) != trial_number)
      {
         cout << "data error: " << *(reinterpret_cast<unsigned long *>(data))  << " == " << trial_number << endl;
         interface.release_recv_buffer (header);
         return false;
      }

      interface.release_recv_buffer (header);
      return true;
   }
   else
   {
      header = interface.recv (node);
      interface.release_recv_buffer (header);

      header = interface.get_send_buffer ();
      header->dest = (node % 2) ? (node - 1) : (node + 1);
      header->src = node;
      header->type = 1;
      header->seq = seq++;
      header->len = msg_size;

      // get pointer to data section of buffer
      data = reinterpret_cast<unsigned char *>(header + 1);

      // place trial number in first "int" for master to verify
      *(reinterpret_cast<unsigned long *>(data)) = trial_number++;

      interface.send (header);
      return true;
   }

   return false;
}

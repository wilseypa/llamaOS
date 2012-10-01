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

#include <llamaos/api/sleep.h>
#include <llamaos/apps/latency/protocols/llamaNET.h>
#include <llamaos/memory/Memory.h>
#include <llamaos/xen/Hypercall-macros.h>
#include <llamaos/xen/Hypervisor.h>
#include <llamaos/llamaOS.h>

using namespace std;

using namespace latency;
using namespace latency::protocols;

using namespace llamaos;
using namespace llamaos::memory;
using namespace llamaos::xen;

static uint32_t seq = 1;

static uint32_t parse_node (int argc, char **argv)
{
   if (   (argc > 4)
       && (nullptr != argv [4]))
   {
      stringstream ss (argv [4]);
      int node;
      ss >> node;

      if (!ss.fail ())
      {
         return node;
      }
   }

   cout << "FAILED TO GET NODE INDEX FROM ARGV!!!!!!!!!!!!!!!!!!!!" << endl;
   return -1;
}

static domid_t get_domd_id (int node)
{
   // for now it's just self minus node % 6
   domid_t self_id = Hypervisor::get_instance ()->domid;

   return (self_id - 1 - (node % 6));
}

llamaNET::llamaNET (int argc, char **argv)
   :  Experiment(argc, argv),
      node(parse_node (argc, argv)),
      interface(get_domd_id (node), (node % 6))
{
   // dalai 0-5 always starts the experiments
   client = (node < 6);

   cout << "llamaNET running as node " << dec << node << endl;

   cout << "sleep 2 seconds..." << endl;
   api::sleep(2);
}

llamaNET::~llamaNET ()
{
   cout << "sleep 2 seconds..." << endl;
   api::sleep(2);

   // release interface
}

bool llamaNET::verify ()
{
   net::llamaNET::Protocol_header *header;
   unsigned char *data;

   cout << "calling verify..." << endl;

   // dalai initiates the trial
   if (client)
   {
      header = interface.get_send_buffer ();
      header->dest = (node >= 6) ? (node - 6) : (node + 6);;
      header->src = node;
      header->type = 1;
      header->seq = seq++;
      header->len = length;

      // get pointer to data section of buffer
      data = reinterpret_cast<unsigned char *>(header + 1);

      // marks all bytes with alpha chars (a,b,c,...)
      mark_data_alpha (data, length);

      cout << "dalai sending packet..." << endl;

      // send/recv and verify the data has been changed to numerals (1,2,3,...)
      interface.send (header);
      header = interface.recv (node);

      // get pointer to data section of buffer
      data = reinterpret_cast<unsigned char *>(header + 1);

      if (verify_data_numeric (data, length))
      {
         interface.release_recv_buffer (header);

         cout << "dalai recv'ed packet..." << endl;
         return true;
      }
   }
   else
   {
      cout << "redpj waiting packet..." << endl;
      header = interface.recv (node);

      // get pointer to data section of buffer
      data = reinterpret_cast<unsigned char *>(header + 1);

      if (verify_data_alpha (data, length))
      {
         interface.release_recv_buffer (header);

         header = interface.get_send_buffer ();
         header->dest = (node >= 6) ? (node - 6) : (node + 6);;
         header->src = node;
         header->type = 1;
         header->seq = seq++;
         header->len = length;

         // get pointer to data section of buffer
         data = reinterpret_cast<unsigned char *>(header + 1);

         // marks all bytes with numerals and send
         mark_data_numeric (data, length);

         cout << "redpj sending packet..." << endl;
         interface.send (header);
         return true;
      }
   }

   return false;
}

bool llamaNET::run_trial (unsigned long trial)
{
   net::llamaNET::Protocol_header *header;
   unsigned char *data;

   // dalai initiates the trial
   if (client)
   {
      header = interface.get_send_buffer ();
      header->dest = (node >= 6) ? (node - 6) : (node + 6);;
      header->src = node;
      header->type = 1;
      header->seq = seq++;
      header->len = length;

      interface.send (header);
      header = interface.recv (node);

      // get pointer to data section of buffer
      data = reinterpret_cast<unsigned char *>(header + 1);

      if (*(reinterpret_cast<unsigned long *>(data)) == trial)
      {
         interface.release_recv_buffer (header);
         return true;
      }
      else
      {
         interface.release_recv_buffer (header);
         return false;
      }
   }
   else
   {
      header = interface.recv (node);
      interface.release_recv_buffer (header);

      header = interface.get_send_buffer ();
      header->dest = (node >= 6) ? (node - 6) : (node + 6);;
      header->src = node;
      header->type = 1;
      header->seq = seq++;
      header->len = length;

      // get pointer to data section of buffer
      data = reinterpret_cast<unsigned char *>(header + 1);

      // place trial number in first "int" for master to verify
      *(reinterpret_cast<unsigned long *>(data)) = trial;

      interface.send (header);
      return true;
   }

   return false;
}

Experiment *Experiment_factory::create (int argc, char **argv)
{
   return new llamaNET (argc, argv);
}

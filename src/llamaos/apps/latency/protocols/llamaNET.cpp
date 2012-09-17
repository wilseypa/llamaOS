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

static net::llamanet::llamaNET_interface *get_llamaNET_interface ()
{
   // also a hack, get an open address in the second half of the reserved area
   uint64_t reserved_virtual_address = get_reserved_virtual_address (1);

   // get access to the interface
   domid_t self_id = Hypervisor::get_instance ()->xenstore.read<domid_t>("domid");
   cout << "self_id: " << self_id << endl;

   gnttab_map_grant_ref_t map_grant_ref;
   map_grant_ref.host_addr = reserved_virtual_address;
   map_grant_ref.flags = GNTMAP_host_map;
   map_grant_ref.ref = 510;
   map_grant_ref.dom = self_id - 1;

   cout << "Calling GNTMAP_host_map with ref: " << 510 << " and host_addr: " << reserved_virtual_address << endl;
   cout << "hypercall: " << HYPERVISOR_grant_table_op(GNTTABOP_map_grant_ref, &map_grant_ref, 1) << endl;

   if (map_grant_ref.status == GNTST_okay)
   {
      cout << "access granted: " << map_grant_ref.status << endl;
      cout << "  ref: " << dec << 510 << ", virtual address: " << hex << reserved_virtual_address << ", machine address: " << memory::virtual_pointer_to_machine_page (memory::address_to_pointer<net::llamanet::Protocol_header>(reserved_virtual_address)) << endl;
      cout << "sleep 5 seconds..." << endl;
      api::sleep(5);

      return memory::address_to_pointer<net::llamanet::llamaNET_interface>(reserved_virtual_address);
   }

   cout << "failed to get access: " << map_grant_ref.status << endl;
   return nullptr;
}

static unsigned char *get_buffer (grant_ref_t ref)
{
   // also a hack, get an open address in the second half of the reserved area
   uint64_t reserved_virtual_address = get_reserved_virtual_address (1);

   // get access to the interface
   domid_t self_id = Hypervisor::get_instance ()->xenstore.read<domid_t>("domid");

   gnttab_map_grant_ref_t map_grant_ref;
   map_grant_ref.host_addr = reserved_virtual_address;
   map_grant_ref.flags = GNTMAP_host_map;
   map_grant_ref.ref = ref;
   map_grant_ref.dom = self_id - 1;

   cout << "Calling GNTMAP_host_map with ref: " << dec << ref << " and host_addr: " << hex << reserved_virtual_address << endl;
   cout << "hypercall: " << HYPERVISOR_grant_table_op(GNTTABOP_map_grant_ref, &map_grant_ref, 1) << endl;

   if (map_grant_ref.status == GNTST_okay)
   {
      cout << "access granted: " << map_grant_ref.status << endl;
//      cout << "  ref: " << ref << ", virtual address: " << reserved_virtual_address << ", machine address: " << memory::virtual_pointer_to_machine_page (memory::address_to_pointer<net::llamanet::Protocol_header>(reserved_virtual_address)) << endl;
      cout.flush();

      return memory::address_to_pointer<unsigned char>(reserved_virtual_address);
   }

   cout << "failed to get access: " << map_grant_ref.status << endl;
   return nullptr;
}

static int parse_node (int argc, char **argv)
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

   return -1;
}

llamaNET::llamaNET (int argc, char **argv)
   :  Experiment(argc, argv),
      node(parse_node (argc, argv)),
      interface(get_llamaNET_interface())
{

      cout << "driver.online: " << interface->driver.online << endl;
      cout << "llamaNET running as node " << dec << node << endl;

      cout << "mapping tranmit buffers..." << endl;
      for (int i = 0; i < 8; i++)
      {
         cout << "mapping tx_buffers [" << dec << i << "]" << endl;
         tx_buffers [i] = get_buffer (509 - i);
      }

      cout << "mapping receive buffers..." << endl;
      for (int i = 0; i < 8; i++)
      {
         cout << "mapping rx_buffers [" << dec << i << "]" << endl;
         rx_buffers [i] = get_buffer (501 - i);;
      }

      cout << "sizeof(HEADER_LENGTH): " << net::llamanet::HEADER_LENGTH << endl;
      cout << "sleep 5 seconds..." << endl;
      api::sleep(5);
}

llamaNET::~llamaNET ()
{
   // release interface
}

bool llamaNET::verify ()
{
cout << "calling verify..." << endl;
   // dalai initiates the trial
   if (node == 0)
   {
      net::llamanet::Protocol_header *header = reinterpret_cast<net::llamanet::Protocol_header *>(tx_buffers [interface->app [0].tx_head]);
      memset((void *)header, 0, net::llamanet::HEADER_LENGTH);
      header->src = 0;
      header->dest = 1;
      header->type = 1;
      header->len = length;

      unsigned char *data = tx_buffers [interface->app [0].tx_head] + net::llamanet::HEADER_LENGTH;

      // marks all bytes with alpha chars (a,b,c,...)
      mark_data_alpha (data, length);

cout << "dalai sending packet..." << endl;
      // send/recv and verify the data has been changed to numerals (1,2,3,...)
      if (   (send_buffer ())
          && (recv_buffer ()))
      {
         data = rx_buffers [interface->app [0].rx_tail] + net::llamanet::HEADER_LENGTH;

         if (verify_data_numeric (data, length))
         {
            unsigned int tail = interface->app [0].rx_tail;
            tail++;
            tail %= 8;
            interface->app [0].rx_tail = tail;
            return true;
         }
      }
   }
   else
   {
cout << "redpj waiting packet..." << endl;
      // wait for mesg and verify alpha chars
      if (recv_buffer ())
      {
         unsigned char *data = rx_buffers [interface->app [0].rx_tail] + net::llamanet::HEADER_LENGTH;

         if (verify_data_alpha (data, length))
         {
            unsigned int tail = interface->app [0].rx_tail;
            tail++;
            tail %= 8;
            interface->app [0].rx_tail = tail;

            net::llamanet::Protocol_header *header = reinterpret_cast<net::llamanet::Protocol_header *>(tx_buffers [interface->app [0].tx_head]);
            data = tx_buffers [interface->app [0].tx_head] + net::llamanet::HEADER_LENGTH;
            header->src = 1;
            header->dest = 0;
            header->type = 1;
            header->len = length;

            // marks all bytes with numerals and send
            mark_data_numeric (data, length);
cout << "redpj sending packet..." << endl;
            return send_buffer ();
         }
      }
   }

   return false;
}

bool llamaNET::run_trials ()
{
   if (node == 0)
   {
      struct timeval tv1;
      struct timeval tv2;
      unsigned long usec1;
      unsigned long usec2;
      bool result;

      // run timed trials
      for (unsigned long i = 0; i < trials; i++)
      {
         gettimeofday (&tv1, 0);
         result = run (i);
         gettimeofday (&tv2, 0);

         if (!result)
         {
            cout << "failed to complete trial " << i << endl;
            return false;
         }

         usec1 = (tv1.tv_sec*1000000) + tv1.tv_usec;
         usec2 = (tv2.tv_sec*1000000) + tv2.tv_usec;

         results [i] = (usec2 >= usec1) ? usec2 - usec1 : 0xFFFFFFFF;
      }

      compute_statistics ();
   }
   else
   {
      for (unsigned long i = 0; i < trials; i++)
      {
         if (!run (i))
         {
            cout << "failed to complete trial " << i << endl;
            return false;
         }
      }
   }

   return true;
}

bool llamaNET::run (unsigned long trial)
{
   // dalai initiates the trial
   if (node == 0)
   {
      net::llamanet::Protocol_header *header = reinterpret_cast<net::llamanet::Protocol_header *>(tx_buffers [interface->app [0].tx_head]);
      unsigned char *data = tx_buffers [interface->app [0].tx_head] + net::llamanet::HEADER_LENGTH;
      header->src = 0;
      header->dest = 1;
      header->type = 1;
      header->len = length;

      // send/recv mesg, check first "int" in buffer is the trial number just
      // as a low cost sanity check to verify both machines are in sync
      if (   (send_buffer ())
          && (recv_buffer ()))
      {
         data = rx_buffers [interface->app [0].rx_tail] + net::llamanet::HEADER_LENGTH;

         if (*(reinterpret_cast<unsigned long *>(data)) == trial)
         {
            unsigned int tail = interface->app [0].rx_tail;
            tail++;
            tail %= 8;
            interface->app [0].rx_tail = tail;

            return true;
         }
      }
   }
   else
   {
      // wait for message to arrive
      if (recv_buffer ())
      {
         unsigned char *data = rx_buffers [interface->app [0].rx_tail] + net::llamanet::HEADER_LENGTH;

         unsigned int tail = interface->app [0].rx_tail;
         tail++;
         tail %= 8;
         interface->app [0].rx_tail = tail;

         net::llamanet::Protocol_header *header = reinterpret_cast<net::llamanet::Protocol_header *>(tx_buffers [interface->app [0].tx_head]);
         data = tx_buffers [interface->app [0].tx_head] + net::llamanet::HEADER_LENGTH;
         header->src = 1;
         header->dest = 0;
         header->type = 1;
         header->len = length;

         // place trial number in first "int" for master to verify
         *(reinterpret_cast<unsigned long *>(data)) = trial;

         return send_buffer ();
      }
   }

   return false;
}

bool llamaNET::stop ()
{
   net::llamanet::Protocol_header *header = reinterpret_cast<net::llamanet::Protocol_header *>(tx_buffers [interface->app [0].tx_head]);
   header->src = 0;
   header->dest = 0;
   header->type = 0xDEAD;
   header->len = 0;

   send_buffer ();

   return true;
}

bool llamaNET::recv_buffer ()
{
   while (interface->app [0].rx_head == interface->app [0].rx_tail);

   // ensure write is processed
   rmb();

   return true;
}

bool llamaNET::send_buffer ()
{
   // ensure write is processed
   wmb();

   unsigned int head = interface->app [0].tx_head;
   head++;
   head %= 8;
   interface->app [0].tx_head = head;

   return true;
}

Experiment *Experiment_factory::create (int argc, char **argv)
{
   return new llamaNET (argc, argv);
}

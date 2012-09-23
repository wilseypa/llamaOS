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

#include <llamaos/api/sleep.h>
#include <llamaos/memory/Memory.h>
#include <llamaos/net/llamaNET.h>
#include <llamaos/xen/Hypervisor.h>

// using namespace std;

using namespace llamaos;
using namespace llamaos::memory;
using namespace llamaos::net;
using namespace llamaos::xen;

const unsigned int llamaNET::HEADER_LENGTH = sizeof(llamaNET::Protocol_header);

llamaNET::llamaNET (int domd_id, int index)
   :  domd_id(domd_id),
      index(index),
      control(domd_id, 510),    // hardcoded 510 for now, eventually use the xenstore
      rx_buffers(),
      tx_buffers()
{
   for (unsigned int i = 0; i < control->tx_buffer_size; i++)
   {
      tx_buffers.push_back (new Grant_map<Protocol_header>(domd_id, control->tx_refs [i]));
   }

   for (unsigned int i = 0; i < control->rx_buffer_size; i++)
   {
      rx_buffers.push_back (new Grant_map<Protocol_header>(domd_id, control->rx_refs [i], true));
   }
}

llamaNET::~llamaNET ()
{
   Protocol_header *header = reinterpret_cast<Protocol_header *>(get_send_buffer ());
   header->src = 0;
   header->dest = 0;
   header->type = 0xDEAD;
   header->seq = 0;
   header->len = 0;

   send ();

   // pause to make sure driver gets this message
   api::sleep (2);

   for (unsigned int i = 0; i < tx_buffers.size (); i++)
   {
      delete tx_buffers [i];
   }

   for (unsigned int i = 0; i < rx_buffers.size (); i++)
   {
      delete rx_buffers [i];
   }
}

bool llamaNET::recv_poll ()
{
   // only check for message arrival
   return (control->app [0].rx_head != control->app [0].rx_tail);
}

llamaNET::Protocol_header *llamaNET::recv ()
{
   // spin until message arrives
   while (control->app [0].rx_head == control->app [0].rx_tail);

   return rx_buffers [control->app [0].rx_tail]->get_pointer ();
}

void llamaNET::release_recv_buffer ()
{
   unsigned int tail = control->app [0].rx_tail;
   tail++;
   tail %= control->rx_buffer_size;
   control->app [0].rx_tail = tail;
}

llamaNET::Protocol_header *llamaNET::get_send_buffer ()
{
   // need atomic increment before this works with multiple llamaNET instances
   return tx_buffers [control->app [index].tx_head]->get_pointer ();
}

void llamaNET::send ()
{
   Protocol_header *header = reinterpret_cast<Protocol_header *>(get_send_buffer ());

   // !BAM get these in a config soon
   // dalai node 0 mac 00-1b-21-d5-66-ef
   // redpj node 1 mac 68-05-ca-01-f7-db
   if (   (header->dest >= 1)
       && (header->dest <= 6))
   {
      // sending to redpj
      header->eth_dest [0] = 0x68;
      header->eth_dest [1] = 0x05;
      header->eth_dest [2] = 0xca;
      header->eth_dest [3] = 0x01;
      header->eth_dest [4] = 0xf7;
      header->eth_dest [5] = 0xdb;
   }
   else if (   (header->dest >= 7)
            && (header->dest <= 12))
   {
      // sending to dalai
      header->eth_dest [0] = 0x00;
      header->eth_dest [1] = 0x1b;
      header->eth_dest [2] = 0x21;
      header->eth_dest [3] = 0xd5;
      header->eth_dest [4] = 0x66;
      header->eth_dest [5] = 0xef;
   }
   else
   {
      // throw exception?
   }

   if (   (header->src >= 1)
       && (header->src <= 6))
   {
      // sending from dalai
      header->eth_src [6] = 0x00;
      header->eth_src [7] = 0x1b;
      header->eth_src [8] = 0x21;
      header->eth_src [9] = 0xd5;
      header->eth_src [10] = 0x66;
      header->eth_src [11] = 0xef;
   }
   else if (   (header->src >= 7)
            && (header->src <= 12))
   {
      // sending from redpj
      header->eth_src [6] = 0x68;
      header->eth_src [7] = 0x05;
      header->eth_src [8] = 0xca;
      header->eth_src [9] = 0x01;
      header->eth_src [10] = 0xf7;
      header->eth_src [11] = 0xdb;
   }
   else
   {
      // throw exception?
   }

   header->eth_type = 0x0C09;

   // ensure write is processed
   wmb();

   unsigned int head = control->app [0].tx_head;
   head++;
   head %= control->tx_buffer_size;
   control->app [0].tx_head = head;
}

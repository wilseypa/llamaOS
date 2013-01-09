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
#include <llamaos/memory/Memory.h>
#include <llamaos/net/llamaNET.h>
#include <llamaos/xen/Hypervisor.h>

using namespace std;
using namespace llamaos;
using namespace llamaos::memory;
using namespace llamaos::net;
using namespace llamaos::xen;

const unsigned int llamaNET::HEADER_LENGTH = sizeof(llamaNET::Protocol_header);

llamaNET::llamaNET (int domd_id, int index)
   :  domd_id(domd_id),
      index(index),
      control(domd_id, 510 - index),    // hardcoded 510 for now, eventually use the xenstore
      rx_buffers(),
      tx_buffers()
{
   for (unsigned int i = 0; i < control->tx_buffer_size; i++)
   {
      tx_buffers.push_back (new Grant_map<Protocol_header>(domd_id, control->app [index].tx_refs [i]));
   }

   for (unsigned int i = 0; i < control->rx_buffer_size; i++)
   {
      rx_buffers.push_back (new Grant_map<Protocol_header>(domd_id, control->app [index].rx_refs [i], true));
   }
}

llamaNET::~llamaNET ()
{
   control->close_driver = 1;

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
   return (   (control->driver.rx_head != control->app [index].rx_tail)
           || (control->driver.tx_head != control->app [index].tx_tail));
}

llamaNET::Protocol_header *llamaNET::recv ()
{
   // spin until message arrives
   for (;;)
   {
      if (control->driver.rx_head != control->app [index].rx_tail)
      {
         return rx_buffers [control->app [index].rx_tail]->get_pointer ();
      }

      if (control->driver.tx_head != control->app [index].tx_tail)
      {
         return tx_buffers [control->app [index].tx_tail]->get_pointer ();
      }
   }
//      while (!recv_poll ());

//   return rx_buffers [control->app [index].rx_tail]->get_pointer ();
}

llamaNET::Protocol_header *llamaNET::recv (uint32_t node)
{
   llamaNET::Protocol_header *header;

   for (;;)
   {
      header = recv ();

      if (header->dest == node)
      {
         return header;
      }

      release_recv_buffer (header);
   }
}

void llamaNET::release_recv_buffer (Protocol_header *header)
{
   if (header == rx_buffers [control->app [index].rx_tail]->get_pointer ())
   {
      unsigned int tail = control->app [index].rx_tail;
      tail++;
      tail %= control->rx_buffer_size;
      control->app [index].rx_tail = tail;
   }
   else if (header == tx_buffers [control->app [index].tx_tail]->get_pointer ())
   {
      unsigned int tail = control->app [index].tx_tail;
      tail++;
      tail %= control->tx_buffer_size;
      control->app [index].tx_tail = tail;
   }
}

llamaNET::Protocol_header *llamaNET::get_send_buffer ()
{
   // wait for last buffer to send
   while (control->app [index].tx_request);

   // get next index
   control->app [index].tx_index = __sync_fetch_and_add (&control->driver.next_tx_index, 1) & 7;

   // need atomic increment before this works with multiple llamaNET instances
   return tx_buffers [control->app [index].tx_index]->get_pointer ();
}

void llamaNET::send (Protocol_header *header)
{
//   Protocol_header *header = reinterpret_cast<Protocol_header *>(get_send_buffer ());

   // !BAM get these in a config soon
   // dalai node 0 mac 00-1b-21-d5-66-ef
   // redpj node 1 mac 68-05-ca-01-f7-db
#if 0
   if (   (header->dest >= 0)
       && (header->dest < 6))
   {
      // sending to redpj
      header->eth_dest [0] = 0x68;
      header->eth_dest [1] = 0x05;
      header->eth_dest [2] = 0xca;
      header->eth_dest [3] = 0x01;
      header->eth_dest [4] = 0xf7;
      header->eth_dest [5] = 0xdb;
   }
   else if (   (header->dest >= 6)
            && (header->dest < 12))
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

   if (   (header->src >= 0)
       && (header->src < 6))
   {
      // sending from dalai
      header->eth_src [0] = 0x00;
      header->eth_src [1] = 0x1b;
      header->eth_src [2] = 0x21;
      header->eth_src [3] = 0xd5;
      header->eth_src [4] = 0x66;
      header->eth_src [5] = 0xef;
   }
   else if (   (header->src >= 6)
            && (header->src < 12))
   {
      // sending from redpj
      header->eth_src [0] = 0x68;
      header->eth_src [1] = 0x05;
      header->eth_src [2] = 0xca;
      header->eth_src [3] = 0x01;
      header->eth_src [4] = 0xf7;
      header->eth_src [5] = 0xdb;
   }
   else
   {
      // throw exception?
   }
#else
   // !BAM get these in a config soon
   // dalai node 0 (even) mac 00-1b-21-d5-66-ef
   // redpj node 1 (odd)  mac 68-05-ca-01-f7-db

   if ((header->dest % 2) == 0)
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
      // sending to redpj
      header->eth_dest [0] = 0x68;
      header->eth_dest [1] = 0x05;
      header->eth_dest [2] = 0xca;
      header->eth_dest [3] = 0x01;
      header->eth_dest [4] = 0xf7;
      header->eth_dest [5] = 0xdb;
   }

   if ((header->src % 2) == 0)
   {
      // sending from dalai
      header->eth_src [0] = 0x00;
      header->eth_src [1] = 0x1b;
      header->eth_src [2] = 0x21;
      header->eth_src [3] = 0xd5;
      header->eth_src [4] = 0x66;
      header->eth_src [5] = 0xef;
   }
   else
   {
      // sending from redpj
      header->eth_src [0] = 0x68;
      header->eth_src [1] = 0x05;
      header->eth_src [2] = 0xca;
      header->eth_src [3] = 0x01;
      header->eth_src [4] = 0xf7;
      header->eth_src [5] = 0xdb;
   }

#endif

   header->eth_type = 0x0C09;

//   unsigned int head = control->app [0].tx_head;
//   control->app [0].tx_length [head] = HEADER_LENGTH + header->len;
   control->app [index].tx_length = HEADER_LENGTH + header->len;

   // ensure write is processed
   wmb();

   control->app [index].tx_request = true;

//   head++;
//   head %= control->tx_buffer_size;
//   control->app [0].tx_head = head;
}

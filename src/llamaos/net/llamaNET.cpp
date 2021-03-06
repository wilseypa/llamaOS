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

#include <unistd.h>
#include <iostream>
#include <string.h>

#include <llamaos/api/sleep.h>
#include <llamaos/memory/Memory.h>
#include <llamaos/net/llamaNET.h>
#include <llamaos/xen/Hypervisor.h>

using namespace std;
using namespace llamaos;
using namespace llamaos::memory;
using namespace llamaos::net;
using namespace llamaos::xen;

// #define HARD_CODED_MACS
// #define DALAI_REDPJ
// #define BEOWULF1

const unsigned int llamaNET::HEADER_LENGTH = sizeof(llamaNET::Protocol_header);

llamaNET::llamaNET (int domd_id, int index)
   :  domd_id(domd_id),
      index(index),
//      control(domd_id, 510 - index),    // hardcoded 510 for now, eventually use the xenstore
//      control(domd_id, 1022 - index),    // hardcoded 1022 for now, eventually use the xenstore
//      control(domd_id, 3070 - index),    // hardcoded 3070 for now, eventually use the xenstore
      control(domd_id, 16382 - index),    // hardcoded 16382 for now, eventually use the xenstore
      rx_buffers(),
      tx_buffers()
{
   cout << "creating llamaNET interface..." << endl;

   xen::Grant_map<grant_ref_t> tx_refs (domd_id, 16376 - index);

   for (unsigned int i = 0; i < TX_BUFFERS; i++)
   {
      tx_buffers.push_back (new Grant_map<Protocol_header>(domd_id, tx_refs.get_pointer () [i]));
   }

   xen::Grant_map<grant_ref_t> rx_refs (domd_id, 16370 - index);

   for (unsigned int i = 0; i < RX_BUFFERS; i++)
   {
      rx_buffers.push_back (new Grant_map<Protocol_header>(domd_id, rx_refs.get_pointer () [i], true));
   }

   control->app [index].online = true;
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
//         cout << "*** llamaNET::recv rx_tail: " << control->app [index].rx_tail << endl;
         return rx_buffers [control->app [index].rx_tail]->get_pointer ();
      }

      if (control->driver.tx_head != control->app [index].tx_tail)
      {
//   cout << "recv " << control->app [index].tx_tail << endl;
//         cout << "*** llamaNET::recv tx_tail: " << control->app [index].tx_tail << endl;
         return tx_buffers [control->app [index].tx_tail]->get_pointer ();
      }

      mb ();
   }
}

llamaNET::Protocol_header *llamaNET::recv (uint32_t node)
{
   const unsigned char BROADCAST_MAC[6] = {0xff, 0xff, 0xff, 0xff, 0xff, 0xff};
   llamaNET::Protocol_header *header;

   for (;;)
   {
      header = recv ();

      if (   (header->eth_type == 0x0C09) && (node != header->src)
          && (header->dest == node || memcmp(header->eth_dest, BROADCAST_MAC, 6) == 0))
      {
         return header;
      }

      release_recv_buffer (header);
   }
}

llamaNET::Protocol_header *llamaNET::recvNB (uint32_t node)
{
   const unsigned char BROADCAST_MAC[6] = {0xff, 0xff, 0xff, 0xff, 0xff, 0xff};
   llamaNET::Protocol_header *header;

   while (recv_poll ())
   {
      header = recv ();

      if (   (header->eth_type == 0x0C09) && (node != header->src)
          && (header->dest == node || memcmp(header->eth_dest, BROADCAST_MAC, 6) == 0))
      {
         return header;
      }

      release_recv_buffer (header);
   }

   return NULL;
}

void llamaNET::release_recv_buffer (Protocol_header *header)
{
   if (header == rx_buffers [control->app [index].rx_tail]->get_pointer ())
   {
      unsigned int tail = control->app [index].rx_tail;
      tail++;
      tail %= RX_BUFFERS;
      control->app [index].rx_tail = tail;
   }
   else if (header == tx_buffers [control->app [index].tx_tail]->get_pointer ())
   {
      unsigned int tail = control->app [index].tx_tail;
      tail++;
      tail %= TX_BUFFERS;
      control->app [index].tx_tail = tail;
   }
}

static llamaNET::Protocol_header *recv_headerv [256];

llamaNET::Protocol_header **llamaNET::recvv (uint32_t node, uint32_t &count)
{
   llamaNET::Protocol_header *header;
   uint32_t max_count = min(256U, count);

   unsigned int rx_head = control->driver.rx_head;
   unsigned int tx_head = control->driver.tx_head;
   unsigned int rx_tail = control->app [index].rx_tail;
   unsigned int tx_tail = control->app [index].tx_tail;

//   if (count > 8)
//   {
//      cout << "count is " << count << endl;
//      cout << "rx_head is " << rx_head << endl;
//      cout << "tx_head is " << tx_head << endl;
//      cout << "rx_tail is " << rx_tail << endl;
//      cout << "tx_tail is " << tx_tail << endl;
//   }

//   uint32_t _count = count;
   count = 0;

   // find the first one (if exists) while moving tails along
   for (;;)
   {
      // find buffers like normal
      if (rx_head != control->app [index].rx_tail)
      {
         header = rx_buffers [control->app [index].rx_tail]->get_pointer ();

         if (   (header->eth_type == 0x0C09)
             && (header->dest == node))
         {
            // this is the first one
            recv_headerv [count++] = header;

            // create local tail states
            rx_tail = control->app [index].rx_tail;
            rx_tail++;
            rx_tail %= RX_BUFFERS;
            break;
         }
      }
      else if (tx_head != control->app [index].tx_tail)
      {
         header = tx_buffers [control->app [index].tx_tail]->get_pointer ();

         if (   (header->eth_type == 0x0C09)
             && (header->dest == node))
         {
            // this is the first one
            recv_headerv [count++] = header;

            // create local tail states
            tx_tail = control->app [index].tx_tail;
            tx_tail++;
            tx_tail %= TX_BUFFERS;
            break;
         }
      }
      else
      {
         break;
      }

      release_recv_buffer (header);
   }

   // find more (if exists) while leaving shared tails as is
   if (count > 0)
   {
      while (count < max_count)
      {
         // find buffers inside head/tails but do not release anything
         if (rx_head != rx_tail)
         {
            header = rx_buffers [rx_tail]->get_pointer ();

            if (   (header->eth_type == 0x0C09)
                && (header->dest == node))
            {
               recv_headerv [count++] = header;
            }

            rx_tail++;
            rx_tail %= RX_BUFFERS;
         }
         else if (tx_head != tx_tail)
         {
            header = tx_buffers [tx_tail]->get_pointer ();

            if (   (header->eth_type == 0x0C09)
                && (header->dest == node))
            {
               recv_headerv [count++] = header;
            }

            tx_tail++;
            tx_tail %= TX_BUFFERS;
         }
         else
         {
            break;
            // rx_head = control->driver.rx_head;
            // tx_head = control->driver.tx_head;
         }
      }
   }

//   if (_count > 8)
//   {
//      cout << "count is " << count << endl;
//      for (;;);
//   }

   return recv_headerv;
}

void llamaNET::release_recv_bufferv (uint32_t count)
{
   unsigned int rx_head = control->driver.rx_head;
   unsigned int tx_head = control->driver.tx_head;

   unsigned int new_rx_tail = control->app [index].rx_tail;
   unsigned int new_tx_tail = control->app [index].tx_tail;

   for (uint32_t i = 0; i < count; i++)
   {
      llamaNET::Protocol_header *header = recv_headerv [i];

      unsigned int rx_tail = control->app [index].rx_tail;
      unsigned int tx_tail = control->app [index].tx_tail;

      for (;;)
      {
         if (rx_head != rx_tail)
         {
            if (header == rx_buffers [rx_tail]->get_pointer ())
            {
               rx_tail++;
               rx_tail %= RX_BUFFERS;
               new_rx_tail = rx_tail;
               break;
            }

            rx_tail++;
            rx_tail %= RX_BUFFERS;
         }
         else if (tx_head != tx_tail)
         {
            if (header == tx_buffers [tx_tail]->get_pointer ())
            {
               tx_tail++;
               tx_tail %= TX_BUFFERS;
               new_tx_tail = tx_tail;
               break;
            }

            tx_tail++;
            tx_tail %= TX_BUFFERS;
         }
      }
   }

   control->app [index].rx_tail = new_rx_tail;
   control->app [index].tx_tail = new_tx_tail;
}

llamaNET::Protocol_header *llamaNET::get_send_buffer ()
{
   // get next index
   unsigned long tx_next_index = __sync_fetch_and_add (&control->driver.tx_next_index, 1);

   // wait to use if other indexes are behind
   while ((tx_next_index - control->driver.tx_done_index) > (TX_BUFFERS - 64))
   {
      if (control->app [index].tx_tail == control->driver.tx_done_index)
      {
         cout << "stuck on self..." << endl;
//         for (;;);
//         control->app [index].tx_tail++;
//         control->app [index].tx_tail %= TX_BUFFERS;
      }
   }

   control->app [index].tx_index = tx_next_index % TX_BUFFERS;

//   cout << "*** llamaNET::get_send_buffer tx_index: " << control->app [index].tx_index << endl;
   return tx_buffers [control->app [index].tx_index]->get_pointer ();
}

llamaNET::Protocol_header *llamaNET::get_send_buffer (uint32_t node)
{
   // get next index
   unsigned long tx_next_index = __sync_fetch_and_add (&control->driver.tx_next_index, 1);

   // wait to use if other indexes are behind
   while ((tx_next_index - control->driver.tx_done_index) > (TX_BUFFERS - 64))
   {
      // purge out unneeded messages to move the shared tail pointers forward,
      // otherwise, send can fill the buffer and deadlock with itself
      purge_buffers (node);

      if (control->app [index].tx_tail == control->driver.tx_done_index)
      {
         cout << "stuck on self..." << endl;
         cout << "tx_next_index: " << tx_next_index << endl;
         cout << "control->driver.tx_next_index " << control->driver.tx_next_index << endl;
         cout << "control->driver.tx_last_index " << control->driver.tx_last_index << endl;
         cout << "control->driver.tx_done_index " << control->driver.tx_done_index << endl;
         cout << "index " << index << endl;
         cout << "control->app [0].tx_tail " << control->app [0].tx_tail << endl;
         cout << "control->app [1].tx_tail " << control->app [1].tx_tail << endl;
         cout << "control->app [2].tx_tail " << control->app [2].tx_tail << endl;
      }
   }

   control->app [index].tx_index = tx_next_index % TX_BUFFERS;

//   cout << "get_send_buffer " << control->app [index].tx_index << endl;
//   cout << "*** llamaNET::get_send_buffer tx_index: " << control->app [index].tx_index << endl;
   return tx_buffers [control->app [index].tx_index]->get_pointer ();
}

#ifdef HARD_CODED_MACS
static void hardcoded_macs (llamaNET::Protocol_header *header)
{
   // !BAM get these in a config soon
   // dalai node 0 mac 00-1b-21-d5-66-ef
   // redpj node 1 mac 68-05-ca-01-f7-db
#ifdef DALAI_REDPJ
   if ((header->dest % 2) == 0)
   {
      // sending to redpj
      header->eth_dest [0] = 0x68;
      header->eth_dest [1] = 0x05;
      header->eth_dest [2] = 0xca;
      header->eth_dest [3] = 0x01;
      header->eth_dest [4] = 0xf7;
      header->eth_dest [5] = 0xdb;
   }
   else
   {
      // sending to dalai
      header->eth_dest [0] = 0x00;
      header->eth_dest [1] = 0x1b;
      header->eth_dest [2] = 0x21;
      header->eth_dest [3] = 0xd5;
      header->eth_dest [4] = 0x66;
      header->eth_dest [5] = 0xef;
   }

   if ((header->src % 2) == 0)
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
      // sending from dalai
      header->eth_src [0] = 0x00;
      header->eth_src [1] = 0x1b;
      header->eth_src [2] = 0x21;
      header->eth_src [3] = 0xd5;
      header->eth_src [4] = 0x66;
      header->eth_src [5] = 0xef;
   }
#endif

#ifdef THOR_WILEY
   // !BAM get these in a config soon
   // dalai node 0 (even) mac 00-1b-21-d5-66-ef
   // redpj node 1 (odd)  mac 68-05-ca-01-f7-db

   if ((header->dest % 2) == 0)
   {
      // sending to thor
      header->eth_dest [0] = 0x68;
      header->eth_dest [1] = 0x05;
      header->eth_dest [2] = 0xca;
      header->eth_dest [3] = 0x06;
      header->eth_dest [4] = 0xde;
      header->eth_dest [5] = 0xc0;
   }
   else
   {
      // sending to wiley
      header->eth_dest [0] = 0x68;
      header->eth_dest [1] = 0x05;
      header->eth_dest [2] = 0xca;
      header->eth_dest [3] = 0x06;
      header->eth_dest [4] = 0xf7;
      header->eth_dest [5] = 0x72;
   }

   if ((header->src % 2) == 0)
   {
      // sending from thor
      header->eth_src [0] = 0x68;
      header->eth_src [1] = 0x05;
      header->eth_src [2] = 0xca;
      header->eth_src [3] = 0x06;
      header->eth_src [4] = 0xde;
      header->eth_src [5] = 0xc0;
   }
   else
   {
      // sending from wiley
      header->eth_src [0] = 0x68;
      header->eth_src [1] = 0x05;
      header->eth_src [2] = 0xca;
      header->eth_src [3] = 0x06;
      header->eth_src [4] = 0xf7;
      header->eth_src [5] = 0x72;
   }
#endif

#ifdef BEOWULF1
   // n021 = even = 00:1e:8c:7e:d4:1b
   // n022 = odd  = 00:1e:8c:91:a4:45
   // n026 = 00:1d:60:b1:a0:4b
   // n027 = 00:1e:8c:91:a4:47
   if ((header->dest % 2) == 0)
   {
      // sending to n021
      header->eth_dest [0] = 0x00;
      header->eth_dest [1] = 0x1e;
      header->eth_dest [2] = 0x8c;
      header->eth_dest [3] = 0x91;  // 0x7e;
      header->eth_dest [4] = 0xa4;  // 0xd4;
      header->eth_dest [5] = 0x47;  // 0x1b;
   }
   else
   {
      // sending to n022
      header->eth_dest [0] = 0x00;
      header->eth_dest [1] = 0x1e;
      header->eth_dest [2] = 0x8c;
      header->eth_dest [3] = 0xb1;  // 0x91;
      header->eth_dest [4] = 0xa0;  // 0xa4;
      header->eth_dest [5] = 0x4b;  // 0x45;
   }

   if ((header->src % 2) == 0)
   {
      // sending from n021
      header->eth_src [0] = 0x00;
      header->eth_src [1] = 0x1e;
      header->eth_src [2] = 0x8c;
      header->eth_src [3] = 0x91;  // 0x7e;
      header->eth_src [4] = 0xa4;  // 0xd4;
      header->eth_src [5] = 0x47;  // 0x1b;
   }
   else
   {
      // sending from n022
      header->eth_src [0] = 0x00;
      header->eth_src [1] = 0x1e;
      header->eth_src [2] = 0x8c;
      header->eth_src [3] = 0xb1;  // 0x91;
      header->eth_src [4] = 0xa0;  // 0xa4;
      header->eth_src [5] = 0x4b;  // 0x45;
   }
#endif
}
#endif

void llamaNET::send (Protocol_header *header)
{
#ifdef HARD_CODED_MACS
   hardcoded_macs (header);
#endif

   header->eth_type = 0x0C09;
//cout << "sending tx_index " << control->app [index].tx_index << endl;
   // ensure write is processed
   wmb();

   __sync_fetch_and_or(&control->driver.tx_mask [control->app [index].tx_index / 32], (1 << (control->app [index].tx_index % 32)));
}

static llamaNET::Protocol_header *headerv [32];

llamaNET::Protocol_header **llamaNET::get_send_bufferv (uint32_t node, unsigned int tx_count)
{
   // get next index
   unsigned long tx_next_index = __sync_fetch_and_add (&control->driver.tx_next_index, tx_count);

   // wait to use if other indexes are behind
   while (((tx_next_index + tx_count) - control->driver.tx_done_index) > (TX_BUFFERS - 64))
   {
      // purge out unneeded messages to move the shared tail pointers forward,
      // otherwise, send can fill the buffer and deadlock with itself
      purge_buffers (node);

//      if (control->app [index].tx_tail == control->driver.tx_done_index)
      {
//         cout << "stuck on self..." << endl;
//         control->app [index].tx_tail++;
//         control->app [index].tx_tail %= TX_BUFFERS;
      }

//      cout << "stuck on other..." << endl;
   }

   for (unsigned int i = 0; i < tx_count; i++)
   {
      headerv [i] = tx_buffers [(tx_next_index + i) % TX_BUFFERS]->get_pointer ();
   }

   control->app [index].tx_index = tx_next_index % TX_BUFFERS;
   return headerv;
}

void llamaNET::sendv (llamaNET::Protocol_header **headerv, unsigned int tx_count)
{
   llamaNET::Protocol_header *header;

   for (unsigned int i = 0; i < tx_count; i++)
   {
      header = headerv [i];

#ifdef HARD_CODED_MACS
      hardcoded_macs (header);
#endif

      header->eth_type = 0x0C09;
   }

   // ensure write is processed
   wmb();

   // write the mask backwards to allow driver to batch send packets
   uint64_t tx_index = control->app [index].tx_index + tx_count - 1;
   tx_index %= TX_BUFFERS;

   uint32_t byte_index = tx_index / 32;
   uint32_t tx_mask = 0;

   for (unsigned int i = 0; i < tx_count; i++)
   {
      if ((tx_index / 32) != byte_index)
      {
         __sync_fetch_and_or(&control->driver.tx_mask [byte_index], tx_mask);

         byte_index = tx_index / 32;
         tx_mask = 0;
      }

      tx_mask |= (1 << (tx_index % 32));
      tx_index--;
      tx_index %= TX_BUFFERS;
   }

   __sync_fetch_and_or(&control->driver.tx_mask [byte_index], tx_mask);
}

void llamaNET::purge_buffers (uint32_t node)
{
   llamaNET::Protocol_header *header;

   // move rx_tail ahead as far as possible (until a message destined for node is found)
   unsigned int rx_head = control->driver.rx_head;
   unsigned int rx_tail = control->app [index].rx_tail;

   while (rx_head != rx_tail)
   {
      header = rx_buffers [rx_tail]->get_pointer ();

      if (   (header->eth_type == 0x0C09)
          && (header->dest == node))
      {
         break;
      }

      rx_tail++;
      rx_tail %= RX_BUFFERS;
   }

   // update shared rx_tail with (possibly) new value
   control->app [index].rx_tail = rx_tail;

   // move tx_tail ahead as far as possible (until a message destined for node is found)
   unsigned int tx_head = control->driver.tx_head;
   unsigned int tx_tail = control->app [index].tx_tail;

   while (tx_head != tx_tail)
   {
      header = tx_buffers [tx_tail]->get_pointer ();

      if (   (header->eth_type == 0x0C09)
          && (header->dest == node))
      {
         break;
      }

      // cout << "purging tx_tail " << tx_tail << endl;
      tx_tail++;
      tx_tail %= TX_BUFFERS;
   }

   // update shared tx_tail with (possibly) new value
   control->app [index].tx_tail = tx_tail;
   mb();
}

void llamaNET::wait_for_send_complete ()
{
   while (control->driver.tx_last_index != control->driver.tx_next_index);
}

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

#ifndef llamaos_net_llamanet_h_
#define llamaos_net_llamanet_h_

#include <cstdint>
#include <vector>

#include <llamaos/xen/Grant_map.h>

// do not exceed 942 or control structure spills out of grant ref
// also running out of grant id when running all 6 guests
// #define TX_BUFFERS 48
// #define RX_BUFFERS 96

// !BAM
// buffer grant reference numbers are now in their own pages
// so we can allocate huge sizes provided the grant framelist
// and reserved memory space is big enough
#define TX_BUFFERS 1024
#define RX_BUFFERS 1024

namespace llamaos {
namespace net {

class llamaNET
{
public:
#pragma pack(1)
   class Protocol_header
   {
   public:
      uint8_t eth_dest [6];
      uint8_t eth_src [6];
      uint16_t eth_type;
      uint32_t dest;
      uint32_t src;
      uint16_t type;
      uint32_t seq;
      uint32_t ack;
      uint32_t len;

   };
#pragma pack()

   static const unsigned int HEADER_LENGTH;

   class Driver_state
   {
   public:
      volatile bool online;

      volatile unsigned int rx_head;
      volatile unsigned int tx_head;
      volatile unsigned int next_tx_index;

   };

   class App_state
   {
   public:
      volatile bool online;

      volatile unsigned int rx_tail;
      volatile unsigned int tx_tail;

      volatile bool tx_request;
      volatile unsigned int tx_index;
      volatile unsigned int tx_length;

//      volatile grant_ref_t rx_refs [RX_BUFFERS];
//      volatile grant_ref_t tx_refs [TX_BUFFERS];

   };

   class Control
   {
   public:
      Driver_state driver;
      App_state app [6];

      volatile unsigned int close_driver;

   };

   llamaNET (int domd_id, int index);
   virtual ~llamaNET ();

   bool recv_poll ();
   Protocol_header *recv ();
   Protocol_header *recv (uint32_t node);
   Protocol_header *recvNB (uint32_t node);
   void release_recv_buffer (Protocol_header *header);

   Protocol_header *get_send_buffer ();
   void send (Protocol_header *header);

   const int domd_id;
   const int index;

private:
   llamaNET ();
   llamaNET (const llamaNET &);
   llamaNET &operator= (const llamaNET &);

   xen::Grant_map<Control> control;
   std::vector<xen::Grant_map<Protocol_header> *> rx_buffers;
   std::vector<xen::Grant_map<Protocol_header> *> tx_buffers;

};

} }

#endif	// llamaos_net_llamanet_h_

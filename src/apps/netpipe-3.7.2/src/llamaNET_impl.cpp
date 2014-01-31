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

#include <cstdint>
#include <cstring>
#include <iostream>

#include <llamaos/net/llamaNET.h>
#include <llamaos/xen/Hypervisor.h>

using namespace std;
using namespace llamaos::net;
using namespace llamaos::xen;

static uint32_t node = 0;
static llamaNET *interface = nullptr;
static uint32_t seq = 1;

static domid_t get_domd_id (int node)
{
   domid_t self_id = Hypervisor::get_instance ()->domid;

   return (self_id - 1 - (node / 2));
}

extern "C"
void llamaNET_setup (int _node)
{
   cout << "calling llamaNET_setup " << _node << endl;
   node = _node;
   interface = new llamaNET (get_domd_id (node), (node / 2));
}

extern "C"
void llamaNET_sync ()
{
   static bool first_sync = true;
   static const char *sync_string = "SyncMe";

   llamaNET::Protocol_header *header;
   char *data;

   if (first_sync)
   {
      first_sync = false;

      if (node % 2)
//      if (node == 3)
      {
cout << "3 is get_send_buffer..." << endl;         
         header = interface->get_send_buffer (node);
         header->dest = (node % 2) ? (node - 1) : (node + 1);
//         header->dest = (node == 1) ? 3 : 1;
         header->src = node;
         header->type = 1;
         header->seq = seq++;
         header->len = strlen(sync_string);

         // get pointer to data section of buffer
         data = reinterpret_cast<char *>(header + 1);
         strcpy (data, sync_string);

         // send/recv and verify the data has been changed
cout << "3 is send..." << endl;         
         interface->send (header);

         for (;;)
         {
cout << "3 is recv..." << endl;         
            header = interface->recv (node);

            // get pointer to data section of buffer
            data = reinterpret_cast<char *>(header + 1);

            if (0 == strncmp (data, sync_string, strlen(sync_string)))
            {
               interface->release_recv_buffer (header);
               break;
            }

            cout << "found wrong data in sync..." << endl;
            interface->release_recv_buffer (header);
         }
      }
      else
      {
         for (;;)
         {
cout << "1 is recv..." << endl;         
            header = interface->recv (node);

            // get pointer to data section of buffer
            data = reinterpret_cast<char *>(header + 1);

            if (0 == strncmp (data, sync_string, strlen(sync_string)))
            {
               interface->release_recv_buffer (header);
               break;
            }

            cout << "found wrong data in sync..." << endl;
            interface->release_recv_buffer (header);
         }

cout << "1 is get_send_buffer..." << endl;         
         header = interface->get_send_buffer (node);
         header->dest = (node % 2) ? (node - 1) : (node + 1);
//         header->dest = (node == 1) ? 3 : 1;
         header->src = node;
         header->type = 1;
         header->seq = seq++;
         header->len = strlen(sync_string);

         // get pointer to data section of buffer
         data = reinterpret_cast<char *>(header + 1);
         strcpy (data, sync_string);

         // send/recv and verify the data has been changed
cout << "1 is send..." << endl;         
         interface->send (header);
      }
   }
   else
   {
      header = interface->get_send_buffer (node);
      header->dest = (node % 2) ? (node - 1) : (node + 1);
//      header->dest = (node == 1) ? 3 : 1;
      header->src = node;
      header->type = 1;
      header->seq = seq++;
      header->len = strlen(sync_string);

      // get pointer to data section of buffer
      data = reinterpret_cast<char *>(header + 1);
      strcpy (data, sync_string);

      // send/recv and verify the data has been changed
      interface->send (header);

      for (;;)
      {
         header = interface->recv (node);

         // get pointer to data section of buffer
         data = reinterpret_cast<char *>(header + 1);

         if (0 == strncmp (data, sync_string, strlen(sync_string)))
         {
            interface->release_recv_buffer (header);
            break;
         }

         cout << "found wrong data in sync..." << endl;
         interface->release_recv_buffer (header);
      }
   }
}


// 1500 - 64
#define MAX_MESSAGE_LENGTH 1436U

// 4096 - 64
// #define MAX_MESSAGE_LENGTH 4032U

//#include <sys/time.h>
//#include <stdlib.h>

extern "C"
void llamaNET_send_data (const char *_data, unsigned int length)
{
   char *data;
//   unsigned int _length = length;

//   cout << "start sending " << length << " message" << endl;

   if (length < MAX_MESSAGE_LENGTH)
   {
      // purge out unneeded messages to move the shared tail pointers forward,
      // otherwise, send can fill the buffer and deadlock with itself
      interface->purge_buffers (node);

      llamaNET::Protocol_header *header = interface->get_send_buffer (node);

      header->dest = (node % 2) ? (node - 1) : (node + 1);
//      header->dest = (node == 1) ? 3 : 1;
      header->src = node;
      header->type = 1;
      header->seq = seq++;
      header->len = length;

      // get pointer to data section of buffer
      data = reinterpret_cast<char *>(header + 1);

      // !BAM can I loose this?
      memcpy (data, _data, length);

      interface->send (header);
      return;
   }

   unsigned int current_length;
   unsigned int tx_count;
   llamaNET::Protocol_header **headerv;

   unsigned int i;

   while (length > 0)
   {
      tx_count = ((length + MAX_MESSAGE_LENGTH) / MAX_MESSAGE_LENGTH);
      tx_count = min(32U, tx_count);

      // purge out unneeded messages to move the shared tail pointers forward,
      // otherwise, send can fill the buffer and deadlock with itself
      interface->purge_buffers (node);

      headerv = interface->get_send_bufferv (node, tx_count);

      for (i = 0; i < tx_count; i++)
      {
         current_length = min(length, MAX_MESSAGE_LENGTH);

         headerv [i]->dest = (node % 2) ? (node - 1) : (node + 1);
//         headerv [i]->dest = (node == 1) ? 3 : 1;
         headerv [i]->src = node;
         headerv [i]->type = 1;
         headerv [i]->seq = seq++;
         headerv [i]->len = current_length;

         // get pointer to data section of buffer
         data = reinterpret_cast<char *>(headerv [i] + 1);

         // !BAM can I loose this?
         memcpy (data, _data, current_length);

         _data += current_length;
         length -= current_length;
      }

      interface->sendv (headerv, tx_count);
   }

//   if (_length > 1572860)
//   {
//      cout << "done sending " << _length << " message" << endl;
//      interface->wait_for_send_complete ();
//      cout << "done waiting for send " << _length << " message" << endl;
//   }

//   cout << "done sending " << length << " message" << endl;
}

extern "C"
void llamaNET_recv_data (char *_data, unsigned int length)
{
   char *data;
//   unsigned int _length = length;

//   cout << "start recving " << length << " message" << endl;

   if (length < MAX_MESSAGE_LENGTH)
   {
      llamaNET::Protocol_header *header = interface->recv(node);

      // get pointer to data section of buffer
      data = reinterpret_cast<char *>(header + 1);

      // !BAM can I loose this?
      memcpy (_data, data, length);

      interface->release_recv_buffer (header);
      return;
   }

   unsigned int current_length;
   uint32_t rx_count;//, needed_count;

   llamaNET::Protocol_header **headerv;

   while (length > 0)
   {
//      if (_length > 1572860)
//      {
//         cout << "start recving " << length << " message" << endl;
//      }
      rx_count = min(256U, ((length + MAX_MESSAGE_LENGTH) / MAX_MESSAGE_LENGTH));

      headerv = interface->recvv(node, rx_count);

      for (uint32_t i = 0; i < rx_count; i++)
      {
         current_length = headerv [i]->len;
//cout << "   recv'ed " << current_length << endl;
         // get pointer to data section of buffer
         data = reinterpret_cast<char *>(headerv [i] + 1);

         // !BAM can I loose this?
         memcpy (_data, data, current_length);

         _data += current_length;
         length -= current_length;
      }

      interface->release_recv_bufferv(rx_count);
   }

//   if (_length > 1572860)
//   {
//      cout << "done recving " << _length << " message" << endl;
//   }

//   cout << "done recving " << length << " message" << endl;
}

extern "C"
void llamaNET_send_time (double t)
{
//   cout << "calling llamaNET_send_time..." << endl;
   /*
      Multiply the number of seconds by 1e8 to get time in 0.01 microseconds
      and convert value to an unsigned 32-bit integer.
    */

   llamaNET::Protocol_header *header;
   header = interface->get_send_buffer (node);
   header->dest = (node % 2) ? (node - 1) : (node + 1);
//   header->dest = (node == 1) ? 3 : 1;
   header->src = node;
   header->type = 1;
   header->seq = seq++;
   header->len = 4;

   // get pointer to data section of buffer
   uint32_t *data = reinterpret_cast<uint32_t *>(header + 1);

   *data = static_cast<uint32_t>(t * 1.e8);

   // send/recv and verify the data has been changed
   interface->send (header);
}

extern "C"
double llamaNET_recv_time ()
{
//   cout << "calling llamaNET_recv_time..." << endl;

   llamaNET::Protocol_header *header;

   header = interface->recv (node);

   // get pointer to data section of buffer
   uint32_t *data = reinterpret_cast<uint32_t *>(header + 1);

   /* Result is ltime (in microseconds) divided by 1.0e8 to get seconds */
   double t = *data / 1.0e8;

   interface->release_recv_buffer (header);

   return t;
}

extern "C"
void llamaNET_send_repeat (int rpt)
{
//   cout << "calling llamaNET_send_repeat..." << endl;

   llamaNET::Protocol_header *header;
   header = interface->get_send_buffer (node);
   header->dest = (node % 2) ? (node - 1) : (node + 1);
//   header->dest = (node == 1) ? 3 : 1;
   header->src = node;
   header->type = 1;
   header->seq = seq++;
   header->len = 4;

   // get pointer to data section of buffer
   uint32_t *data = reinterpret_cast<uint32_t *>(header + 1);

   *data = static_cast<uint32_t>(rpt);

   // send/recv and verify the data has been changed
   interface->send (header);
}

extern "C"
int llamaNET_recv_repeat (void)
{
//   cout << "calling llamaNET_recv_repeat..." << endl;

   llamaNET::Protocol_header *header;

   header = interface->recv (node);

   // get pointer to data section of buffer
   uint32_t *data = reinterpret_cast<uint32_t *>(header + 1);

   int rpt = static_cast<int>(*data);

   interface->release_recv_buffer (header);

   return rpt;
}

extern "C"
void llamaNET_cleanup (int client)
{
   const char *quit = "QUIT";

   llamaNET::Protocol_header *header;
   char *data;

   cout << "calling llamaNET_cleanup..." << endl;

   if (client)
   {
      header = interface->get_send_buffer (node);
      header->dest = (node % 2) ? (node - 1) : (node + 1);
//      header->dest = (node == 1) ? 3 : 1;
      header->src = node;
      header->type = 1;
      header->seq = seq++;
      header->len = strlen(quit);

      // get pointer to data section of buffer
      data = reinterpret_cast<char *>(header + 1);
      strcpy (data, quit);

      // send/recv and verify the data has been changed
      interface->send (header);

      for (;;)
      {
         header = interface->recv (node);

         // get pointer to data section of buffer
         data = reinterpret_cast<char *>(header + 1);

         if (0 == strncmp (data, quit, strlen(quit)))
         {
            cout << "QUIT RECVED!!!!" << endl;
            interface->release_recv_buffer (header);
            break;
         }
      }
   }
   else
   {
      for (;;)
      {
         header = interface->recv (node);

         // get pointer to data section of buffer
         data = reinterpret_cast<char *>(header + 1);

         if (0 == strcmp (data, quit))
         {
            cout << "QUIT RECVED!!!!" << endl;
            interface->release_recv_buffer (header);
            break;
         }
      }

      header = interface->get_send_buffer (node);
      header->dest = (node % 2) ? (node - 1) : (node + 1);
//      header->dest = (node == 1) ? 3 : 1;
      header->src = node;
      header->type = 1;
      header->seq = seq++;
      header->len = strlen(quit);

      // get pointer to data section of buffer
      data = reinterpret_cast<char *>(header + 1);
      strcpy (data, quit);

      // send/recv and verify the data has been changed
      interface->send (header);
   }

   delete interface;
   interface = nullptr;
}

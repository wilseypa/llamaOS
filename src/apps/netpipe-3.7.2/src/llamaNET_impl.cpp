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
void llamaNET_sync (int client)
{
//   cout << "calling llamaNET_sync..." << endl;

   const char *sync_string = "SyncMe";

   llamaNET::Protocol_header *header;
   char *data;

   if (client)
   {
//      cout << "syncing client..." << endl;
      header = interface->get_send_buffer ();
      header->dest = (node % 2) ? (node - 1) : (node + 1);
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
   else
   {
//      cout << "syncing server..." << endl;
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

      header = interface->get_send_buffer ();
      header->dest = (node % 2) ? (node - 1) : (node + 1);
      header->src = node;
      header->type = 1;
      header->seq = seq++;
      header->len = strlen(sync_string);

      // get pointer to data section of buffer
      data = reinterpret_cast<char *>(header + 1);
      strcpy (data, sync_string);

      // send/recv and verify the data has been changed
      interface->send (header);
   }
}

#define MAX_MESSAGE_LENGTH 3968

extern "C"
void llamaNET_send_data (const char *_data, unsigned int length)
{
//   cout << "sending " << length << " in " << (double)length / MAX_MESSAGE_LENGTH << " messaged" << endl;
   unsigned int current_length;

   while (length > 0)
   {
      current_length = (length > MAX_MESSAGE_LENGTH) ? MAX_MESSAGE_LENGTH : length;

      llamaNET::Protocol_header *header;
      char *data;

      header = interface->get_send_buffer ();
      header->dest = (node % 2) ? (node - 1) : (node + 1);
      header->src = node;
      header->type = 1;
      header->seq = seq++;
      header->len = current_length;

      // get pointer to data section of buffer
      data = reinterpret_cast<char *>(header + 1);

      // !BAM can I loose this?
      memcpy (data, _data, current_length);

//      cout << "   sending " << current_length << endl;
      // send/recv and verify the data has been changed
      interface->send (header);
//      cout << "   sent " << current_length << endl;

      _data += current_length;
      length -= current_length;
   }

#if 0
   if (length < (4096 - llamaNET::HEADER_LENGTH))
   {
      llamaNET::Protocol_header *header;
      char *data;

      header = interface->get_send_buffer ();
      header->dest = (node % 2) ? (node - 1) : (node + 1);
      header->src = node;
      header->type = 1;
      header->seq = seq++;
      header->len = length;

      // get pointer to data section of buffer
      data = reinterpret_cast<char *>(header + 1);

      // !BAM can I loose this?
      memcpy (data, _data, length);

      // send/recv and verify the data has been changed
      interface->send (header);
   }
#endif
}

extern "C"
void llamaNET_recv_data (char *_data, unsigned int length)
{
//   cout << "receiving " << length << endl;
   unsigned int current_length;

   while (length > 0)
   {
      llamaNET::Protocol_header *header;
      char *data;

//      cout << "  waiting..." << endl;
      header = interface->recv (node);

      current_length = header->len;
//      cout << "   received " << current_length << endl;

      // get pointer to data section of buffer
      data = reinterpret_cast<char *>(header + 1);

      // !BAM can I loose this?
      memcpy (_data, data, current_length);

      interface->release_recv_buffer (header);

      _data += current_length;
      length -= current_length;
   }

#if 0

   if (length < (4096 - llamaNET::HEADER_LENGTH))
   {
      llamaNET::Protocol_header *header;
      char *data;

      header = interface->recv (node);

      // get pointer to data section of buffer
      data = reinterpret_cast<char *>(header + 1);

      // !BAM can I loose this?
      memcpy (_data, data, length);

      interface->release_recv_buffer (header);
   }
#endif
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
   header = interface->get_send_buffer ();
   header->dest = (node % 2) ? (node - 1) : (node + 1);
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
   header = interface->get_send_buffer ();
   header->dest = (node % 2) ? (node - 1) : (node + 1);
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
      header = interface->get_send_buffer ();
      header->dest = (node % 2) ? (node - 1) : (node + 1);
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

      header = interface->get_send_buffer ();
      header->dest = (node % 2) ? (node - 1) : (node + 1);
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

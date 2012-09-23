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
   // for now it's just self minus node % 6
   domid_t self_id = Hypervisor::get_instance ()->xenstore.read<domid_t>("domid");

   return (self_id - (node % 6));
}

extern "C"
void llamaNET_setup (int _node)
{
   node = _node;
   interface = new llamaNET (get_domd_id (_node), (node % 6));
}

extern "C"
void llamaNET_sync ()
{
   const char *sync_string = "SyncMe";

   llamaNET::Protocol_header *header;
   char *data;

   header = interface->get_send_buffer ();
   header->dest = (node > 6) ? (node - 6) : (node + 6);
   header->src = node;
   header->type = 1;
   header->seq = seq++;
   header->len = strlen(sync_string);

   // get pointer to data section of buffer
   data = reinterpret_cast<char *>(header + 1);
   strcpy (data, sync_string);

   // send/recv and verify the data has been changed
   interface->send ();

   for (;;)
   {
      header = interface->recv ();

      if (header->dest == node)
      {
         // get pointer to data section of buffer
         data = reinterpret_cast<char *>(header + 1);

         if (0 == strcmp (data, sync_string))
         {
            interface->release_recv_buffer ();
            break;
         }
      }

      interface->release_recv_buffer ();
   }
}

extern "C"
void llamaNET_send_data (const char *_data, unsigned int length)
{
   if (length < (4096 - llamaNET::HEADER_LENGTH))
   {
      llamaNET::Protocol_header *header;
      char *data;

      header = interface->get_send_buffer ();
      header->dest = (node > 6) ? (node - 6) : (node + 6);
      header->src = node;
      header->type = 1;
      header->seq = seq++;
      header->len = length;

      // get pointer to data section of buffer
      data = reinterpret_cast<char *>(header + 1);

      // !BAM can I loose this?
      memcpy (data, _data, length);

      // send/recv and verify the data has been changed
      interface->send ();
   }
}

extern "C"
void llamaNET_recv_data (char *_data, unsigned int length)
{
   if (length < (4096 - llamaNET::HEADER_LENGTH))
   {
      llamaNET::Protocol_header *header;
      char *data;

      for (;;)
      {
         header = interface->recv ();

         if (header->dest == node)
         {
            // get pointer to data section of buffer
            data = reinterpret_cast<char *>(header + 1);

            // !BAM can I loose this?
            memcpy (_data, data, length);

            interface->release_recv_buffer ();
            break;
         }

         interface->release_recv_buffer ();
      }
   }
}

extern "C"
void llamaNET_send_time (double t)
{
   /*
      Multiply the number of seconds by 1e8 to get time in 0.01 microseconds
      and convert value to an unsigned 32-bit integer.
    */

   llamaNET::Protocol_header *header;
   header = interface->get_send_buffer ();
   header->dest = (node > 6) ? (node - 6) : (node + 6);
   header->src = node;
   header->type = 1;
   header->seq = seq++;
   header->len = 4;

   // get pointer to data section of buffer
   uint32_t *data = reinterpret_cast<uint32_t *>(header + 1);

   *data = static_cast<uint32_t>(t * 1.e8);

   // send/recv and verify the data has been changed
   interface->send ();
}

extern "C"
double llamaNET_recv_time ()
{
   llamaNET::Protocol_header *header;

   for (;;)
   {
      header = interface->recv ();

      if (header->dest == node)
      {
         // get pointer to data section of buffer
         uint32_t *data = reinterpret_cast<uint32_t *>(header + 1);

         /* Result is ltime (in microseconds) divided by 1.0e8 to get seconds */
         double t = *data / 1.0e8;

         interface->release_recv_buffer ();

         return t;
      }

      interface->release_recv_buffer ();
   }
}

extern "C"
void llamaNET_send_repeat (int rpt)
{
   llamaNET::Protocol_header *header;
   header = interface->get_send_buffer ();
   header->dest = (node > 6) ? (node - 6) : (node + 6);
   header->src = node;
   header->type = 1;
   header->seq = seq++;
   header->len = 4;

   // get pointer to data section of buffer
   uint32_t *data = reinterpret_cast<uint32_t *>(header + 1);

   *data = static_cast<uint32_t>(rpt);

   // send/recv and verify the data has been changed
   interface->send ();
}

extern "C"
int llamaNET_recv_repeat (void)
{
   llamaNET::Protocol_header *header;

   for (;;)
   {
      header = interface->recv ();

      if (header->dest == node)
      {
         // get pointer to data section of buffer
         uint32_t *data = reinterpret_cast<uint32_t *>(header + 1);

         int rpt = static_cast<int>(*data);

         interface->release_recv_buffer ();

         return rpt;
      }

      interface->release_recv_buffer ();
   }
}

extern "C"
void llamaNET_cleanup (int client)
{
   const char *quit = "QUIT";

   llamaNET::Protocol_header *header;
   char *data;

   if (client)
   {
      header = interface->get_send_buffer ();
      header->dest = (node > 6) ? (node - 6) : (node + 6);
      header->src = node;
      header->type = 1;
      header->seq = seq++;
      header->len = strlen(quit);

      // get pointer to data section of buffer
      data = reinterpret_cast<char *>(header + 1);
      strcpy (data, quit);

      // send/recv and verify the data has been changed
      interface->send ();

      for (;;)
      {
         header = interface->recv ();

         if (header->dest == node)
         {
            // get pointer to data section of buffer
            data = reinterpret_cast<char *>(header + 1);

            if (0 == strcmp (data, quit))
            {
               cout << "QUIT RECVED!!!!" << endl;
               interface->release_recv_buffer ();
               break;
            }
         }

         interface->release_recv_buffer ();
      }
   }
   else
   {
      for (;;)
      {
         header = interface->recv ();

         if (header->dest == node)
         {
            // get pointer to data section of buffer
            data = reinterpret_cast<char *>(header + 1);

            if (0 == strcmp (data, quit))
            {
               cout << "QUIT RECVED!!!!" << endl;
               interface->release_recv_buffer ();
               break;
            }
         }

         interface->release_recv_buffer ();
      }

      header = interface->get_send_buffer ();
      header->dest = (node > 6) ? (node - 6) : (node + 6);
      header->src = node;
      header->type = 1;
      header->seq = seq++;
      header->len = strlen(quit);

      // get pointer to data section of buffer
      data = reinterpret_cast<char *>(header + 1);
      strcpy (data, quit);

      // send/recv and verify the data has been changed
      interface->send ();
   }

   delete interface;
   interface = nullptr;
}

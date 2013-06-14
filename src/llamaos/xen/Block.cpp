/*
Copyright (c) 2013, William Magato
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

#include <malloc.h>
#include <cstdlib>

#include <iostream>
#include <sstream>

#include <llamaos/api/sleep.h>
#include <llamaos/memory/Memory.h>
#include <llamaos/xen/Block.h>
#include <llamaos/xen/Hypercall.h>
#include <llamaos/xen/Hypervisor.h>
#include <llamaos/xen/Xenstore.h>
#include <llamaos/Trace.h>
#include <xen/io/xenbus.h>
#include <llamaos/llamaOS.h>

using namespace std;
using namespace llamaos::xen;

Block::Block (const string &key)
   :  frontend_key(key),
      shared(static_cast<blkif_sring_t *>(memalign (PAGE_SIZE, PAGE_SIZE))),
      port(0),
      name(""),
      dev(""),
      size(0),
      position(0)
{
//   cout << "frontend: " << frontend_key << endl;
   Xenstore &xenstore = Hypervisor::get_instance ()->xenstore;

   // find the backend location
   string backend_key = xenstore.read_string(frontend_key + "/backend");
//   cout << "backend: " << backend_key << endl;
   domid_t backend_id = xenstore.read<domid_t>(frontend_key + "/backend-id");
//   cout << "backend-id: " << backend_id << endl;

   // wait for backend to initialize
   cout << "waiting for block backend init..." << endl;
   while (   (xenstore.read_string(backend_key + "/state") != "2")
          && (xenstore.read_string(backend_key + "/state") != "3"));

   // setup resources and share with backend
   memset (shared, 0, PAGE_SIZE);
   SHARED_RING_INIT(shared);
   blkif_front_ring_t _private;
   FRONT_RING_INIT(&_private, shared, PAGE_SIZE);

   grant_ref_t ref = Hypervisor::get_instance ()->grant_table.grant_access (backend_id, shared);
//   cout << "grant ref: " << ref << endl;

//   cout << "calling event_channel_alloc_unbound..." << endl;
   Hypercall::event_channel_alloc_unbound (0, port);
//   cout << "event_channel_alloc_unbound resulted in port " << port << endl;

   xenstore.write<grant_ref_t> (frontend_key + "/ring-ref", ref);
   xenstore.write<evtchn_port_t> (frontend_key + "/event-channel", port);

   // make this device's state XenbusStateInitWait
   xenstore.write_string(frontend_key + "/state", "3");

   // wait for backend to connect
   cout << "waiting for block backend connect..." << endl;
   while (xenstore.read_string(backend_key + "/state") != "4");

   // read block properties
   name = xenstore.read_string(backend_key + "/params").substr(4);
   dev = xenstore.read_string(backend_key + "/dev");

   unsigned int sector_size = xenstore.read<unsigned int>(backend_key + "/sector-size");
   unsigned int sectors = xenstore.read<unsigned int>(backend_key + "/sectors");
   blkif_vdev_t vdev = xenstore.read<blkif_vdev_t>(frontend_key + "/virtual-device");

   cout << "sector size: " << sector_size << endl;
   cout << "sectors: " << sectors << endl;

   // files less than sector_size have zero sectors?
   size = sectors * sector_size;

   // make this device's state connected
   xenstore.write_string(frontend_key + "/state", "4");

   char *buffer = static_cast<char *>(memalign (PAGE_SIZE, PAGE_SIZE));
   ref = Hypervisor::get_instance ()->grant_table.grant_access (backend_id, buffer);
//   cout << "grant ref: " << ref << endl;

   stringstream ss;

   // read them 1 sector at a time for now?
   for (unsigned int i = 0; i < sectors; i++)
   {
      blkif_request_t *request = RING_GET_REQUEST(&_private, _private.req_prod_pvt++);
      request->operation = BLKIF_OP_READ;
      request->handle = vdev;
      request->id = 0;
      request->nr_segments = 1;//sectors;
      request->sector_number = i;//0;
      request->seg [0].gref = ref;
      request->seg [0].first_sect = 0;
      request->seg [0].last_sect = 0;

      RING_PUSH_REQUESTS(&_private);
      Hypercall::event_channel_send (port);

      api::sleep (2);

      blkif_response_t *response = RING_GET_RESPONSE(&_private, _private.rsp_cons++);
   //   cout << "response->id: " << response->id << endl;
   //   cout << "response->status: " << response->status << endl;

   //   stringstream ss;

      if (response->status == BLKIF_RSP_OKAY)
      {
         for (unsigned int i = 0; i < PAGE_SIZE; i++)
         {
            if (   (   (buffer [i] < ' ')
                  || (buffer [i] > '~'))
               && (buffer [i] != 9)
               && (buffer [i] != 10)
               && (buffer [i] != 13))
            {
//               cout << "break on this char: " << (unsigned int)buffer [i] << " at " << i << endl;
               break;
            }

            ss << buffer [i];
         }
   //      cout << "data: " << data << endl;
//         cout << "found and read block device " << name << endl;
      }
      else
      {
         cout << "error reading block device " << name << endl;
      }
   }

   data = ss.str ();

}

Block::~Block ()
{

}

ssize_t Block::read (void *buf, size_t nbytes)
{
//      cout << "reading " << nbytes << " of " << (data.size () - position) << endl;
   nbytes = min(nbytes, (data.size () - position));

   if (nbytes > 0)
   {
      memcpy (buf, &data.c_str()[position], nbytes);
      position += nbytes;

//      cout << "reading " << nbytes << ": " << *(char *)buf << endl;
   }

   return nbytes;
}

off64_t Block::lseek64 (off64_t offset, int whence)
{
   switch (whence)
   {
      default:
      case SEEK_SET:
         position = static_cast<unsigned int>(offset);
         break;

      case SEEK_CUR:
         position += static_cast<unsigned int>(offset);
         break;

      case SEEK_END:
         position = static_cast<unsigned int>(data.size());
         break;
   }

   position = min(static_cast<unsigned int>(data.size()), position);
   return position;
}

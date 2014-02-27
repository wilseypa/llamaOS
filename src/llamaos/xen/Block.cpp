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

#include <llamaos/memory/Memory.h>
#include <llamaos/xen/Block.h>
#include <llamaos/xen/Hypercall.h>
#include <llamaos/xen/Hypervisor.h>
#include <llamaos/xen/Xenstore.h>
#include <llamaos/Trace.h>
#include <xen/io/xenbus.h>
#include <llamaos/llamaOS.h>

// using namespace std;
using std::string;
using std::min;
using std::cout;
using std::endl;
using std::vector;

using namespace llamaos::xen;

Block::Block (const string &key)
   :  frontend_key(key),
      shared_ring(static_cast<blkif_sring_t *>(memalign (PAGE_SIZE, PAGE_SIZE))),
      _private(),
      shared_buffer(static_cast<char *>(memalign (PAGE_SIZE, PAGE_SIZE))),
      shared_ring_ref(0),
      shared_buffer_ref(0),
      port(0),
      name(""),
      dev(""),
      vdev(0),
      sector_size(0),
      sectors(0),
      size(0),
      position(0)
{
   Xenstore &xenstore = Hypervisor::get_instance ()->xenstore;

   // find the backend location
   string backend_key = xenstore.read_string(frontend_key + "/backend");
   domid_t backend_id = xenstore.read<domid_t>(frontend_key + "/backend-id");

   // wait for backend to initialize
   cout << "waiting for block backend init..." << endl;
   while (   (xenstore.read_string(backend_key + "/state") != "2")
          && (xenstore.read_string(backend_key + "/state") != "3"));

   // setup resources and share with backend
   memset (shared_ring, 0, PAGE_SIZE);
   SHARED_RING_INIT(shared_ring);
   FRONT_RING_INIT(&_private, shared_ring, PAGE_SIZE);

   shared_ring_ref = Hypervisor::get_instance ()->grant_table.grant_access (backend_id, shared_ring);

   Hypercall::event_channel_alloc_unbound (0, port);
   xenstore.write<grant_ref_t> (frontend_key + "/ring-ref", shared_ring_ref);
   xenstore.write<evtchn_port_t> (frontend_key + "/event-channel", port);

   // make this device's state XenbusStateInitWait
   xenstore.write_string(frontend_key + "/state", "3");

   // wait for backend to connect
   cout << "waiting for block backend connect..." << endl;
   while (xenstore.read_string(backend_key + "/state") != "4");

   // read block properties
   name = xenstore.read_string(backend_key + "/params").substr(4);
   dev = xenstore.read_string(backend_key + "/dev");
   vdev = xenstore.read<blkif_vdev_t>(frontend_key + "/virtual-device");
   sector_size = xenstore.read<unsigned int>(backend_key + "/sector-size");
   sectors = xenstore.read<unsigned int>(backend_key + "/sectors");
   size = sectors * sector_size;

   cout << "Block: " << name << ", " << dev << endl;
   cout << "  sector size: " << sector_size << endl;
   cout << "  sectors: " << sectors << endl;
   cout << "  total: " << size << endl;

   // make this device's state connected
   xenstore.write_string(frontend_key + "/state", "4");

   shared_buffer_ref = Hypervisor::get_instance ()->grant_table.grant_access (backend_id, shared_buffer);
}

Block::~Block ()
{

}

ssize_t Block::read (void *buf, size_t nbytes)
{
   if (nbytes < size)
   {
      cout << "buf passed to Block::read is too small." << endl;
      return -1;
   }

   for (unsigned int i = 0; i < sectors; i += 8)
   {
      blkif_request_t *request = RING_GET_REQUEST(&_private, _private.req_prod_pvt++);
      request->operation = BLKIF_OP_READ;
      request->handle = vdev;
      request->id = 0;
      request->nr_segments = 1;
      request->sector_number = i;
      request->seg [0].gref = shared_buffer_ref;
      request->seg [0].first_sect = 0;
      request->seg [0].last_sect = 7;

      RING_PUSH_REQUESTS(&_private);
      Hypercall::event_channel_send (port);

      // spin unitl response
      do { rmb(); } while (!RING_HAS_UNCONSUMED_RESPONSES(&_private));

      blkif_response_t *response = RING_GET_RESPONSE(&_private, _private.rsp_cons++);

      if (response->status == BLKIF_RSP_OKAY)
      {
         char *char_buf = static_cast<char *>(buf);
         memcpy(&char_buf[position], shared_buffer, 4096);
         position += 4096;
      }
      else
      {
         cout << response->status << " error reading block device " << name << ", sector " << i << endl;
         return -1;
      }
   }

   return size;
}

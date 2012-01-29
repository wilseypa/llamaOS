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

#include <cstring>
#include <malloc.h>
#include <sys/time.h>

#include <iostream>

#include <xen/io/pciif.h>
#include <xen/io/xenbus.h>

#include <llamaos/memory/memory.h>
#include <llamaos/xen/Hypercall.h>
#include <llamaos/xen/Hypervisor.h>
#include <llamaos/config.h>
#include <llamaos/trace.h>

using namespace std;
using namespace llamaos;
using namespace llamaos::memory;
using namespace llamaos::xen;

#define mb()  __asm__ __volatile__ ( "mfence" : : : "memory")
#define wmb() __asm__ __volatile__ ( "" : : : "memory")

static uint32_t pci_read (struct xen_pci_sharedinfo *pci_sharedinfo, evtchn_port_t port, uint32_t offset, uint32_t size)
{
   struct xen_pci_op op;
   memset(&op, 0, sizeof(op));

   op.cmd = XEN_PCI_OP_conf_read;
   op.domain = 0;
   op.bus = 0;
   op.devfn = 0;
   op.offset = offset;
   op.size = size;
   op.value = 0;

   pci_sharedinfo->op = op;
   wmb();
   pci_sharedinfo->flags |= XEN_PCIF_active;
   Hypercall::event_channel_send(port);

   mb();

   while (pci_sharedinfo->flags & XEN_PCIF_active)
   {
//      Hypercall::sched_op_block ();
      mb();
   }

   mb();

   return pci_sharedinfo->op.value;
}

int main (int /* argc */, char ** /* argv [] */)
{
   cout << "running e1000e llamaNET domain...\n" << endl;

   cout << "waiting..." << endl;
   timeval tv, tv1, tv2;
   gettimeofday (&tv1, nullptr);
   tv = tv1;

   for (;;)
   {
      gettimeofday (&tv2, nullptr);

      if ((tv2.tv_sec - tv1.tv_sec) > 3)
      {
         break;
      }
   }

   cout << "setup pci device xenbus..." << endl;
   Xenstore &xenstore = Hypervisor::get_instance ()->xenstore;

   domid_t backend_id = Hypervisor::get_instance ()->xenstore.read<domid_t>("device/pci/0/backend-id");
   cout << "backend-id: " << backend_id << endl;

   // char *buffer = new char [sizeof(struct xen_pci_sharedinfo) + PAGE_SIZE];

   struct xen_pci_sharedinfo *pci_sharedinfo = 0;//address_to_pointer<struct xen_pci_sharedinfo> (pointer_to_address (buffer + PAGE_SIZE) & ~(PAGE_SIZE-1));

   pci_sharedinfo = (struct xen_pci_sharedinfo *)memalign (PAGE_SIZE, sizeof(struct xen_pci_sharedinfo));

   cout << "pci_sharedinfo: " << pci_sharedinfo << endl;
   cout << "pci_sharedinfo: " << pointer_to_address (pci_sharedinfo) << endl;
   memset (pci_sharedinfo, 0, sizeof(struct xen_pci_sharedinfo));
   grant_ref_t ref = Hypervisor::get_instance ()->grant_table.grant_access (backend_id, pci_sharedinfo);
   cout << "grant ref: " << ref << endl;

   evtchn_port_t port = 0;
   Hypercall::event_channel_alloc_unbound (0, port);

   xenstore.start_transaction (1);
   xenstore.write ("device/pci/0/pci-op-ref", ref);
   xenstore.write ("device/pci/0/event-channel", port);
   xenstore.write ("device/pci/0/magic", XEN_PCI_MAGIC);
   xenstore.write ("device/pci/0/state", XenbusStateInitialised);
   xenstore.end_transaction (1);

   gettimeofday (&tv1, nullptr);

   for (;;)
   {
      gettimeofday (&tv2, nullptr);

      if ((tv2.tv_sec - tv1.tv_sec) > 3)
      {
         break;
      }
   }

   xenstore.write ("device/pci/0/state", XenbusStateConnected);

   gettimeofday (&tv1, nullptr);

   for (;;)
   {
      gettimeofday (&tv2, nullptr);

      if ((tv2.tv_sec - tv1.tv_sec) > 3)
      {
         break;
      }
   }

   string backend = xenstore.read("device/pci/0/backend");
   cout << "backend: " << backend << endl;
   cout << "backend state: " << xenstore.read(backend+"/state") << endl;
   cout << "frontend state: " << xenstore.read("device/pci/0/state") << endl;

   cout << "num-devs: " << xenstore.read(backend+"/num_devs") << endl;

   string bus_address = xenstore.read(backend+"/dev-0");
   cout << "bus_address: " << bus_address << endl;

   cout << "Vendor ID:           " << hex << pci_read (pci_sharedinfo, port,  0, 2) << endl;
   cout << "Device ID:           " << hex << pci_read (pci_sharedinfo, port,  2, 2) << endl;
   cout << "Command:             " << hex << pci_read (pci_sharedinfo, port,  4, 2) << endl;
   cout << "Status:              " << hex << pci_read (pci_sharedinfo, port,  6, 2) << endl;
   cout << "Rev ID:              " << hex << pci_read (pci_sharedinfo, port,  8, 1) << endl;
   cout << "Class Code [0]:      " << hex << pci_read (pci_sharedinfo, port,  9, 1) << endl;
   cout << "Class Code [1]:      " << hex << pci_read (pci_sharedinfo, port, 10, 1) << endl;
   cout << "Class Code [2]:      " << hex << pci_read (pci_sharedinfo, port, 11, 1) << endl;
   cout << "Cache line:          " << hex << pci_read (pci_sharedinfo, port, 12, 1) << endl;
   cout << "Lat timer:           " << hex << pci_read (pci_sharedinfo, port, 13, 1) << endl;
   cout << "Header type:         " << hex << pci_read (pci_sharedinfo, port, 14, 1) << endl;
   cout << "BIST:                " << hex << pci_read (pci_sharedinfo, port, 15, 1) << endl;
   cout << "BAR0:                " << hex << pci_read (pci_sharedinfo, port, 16, 4) << endl;
   cout << "BAR1:                " << hex << pci_read (pci_sharedinfo, port, 20, 4) << endl;
   cout << "BAR2:                " << hex << pci_read (pci_sharedinfo, port, 24, 4) << endl;
   cout << "BAR3:                " << hex << pci_read (pci_sharedinfo, port, 28, 4) << endl;
   cout << "BAR4:                " << hex << pci_read (pci_sharedinfo, port, 32, 4) << endl;
   cout << "BAR5:                " << hex << pci_read (pci_sharedinfo, port, 36, 4) << endl;
   cout << "Cardbus CIS:         " << hex << pci_read (pci_sharedinfo, port, 40, 4) << endl;
   cout << "Subsystem Vendor ID: " << hex << pci_read (pci_sharedinfo, port, 44, 2) << endl;
   cout << "Subsystem ID:        " << hex << pci_read (pci_sharedinfo, port, 46, 2) << endl;
   cout << "Expansion ROM:       " << hex << pci_read (pci_sharedinfo, port, 48, 4) << endl;
   cout << "Cap. Pointer:        " << hex << pci_read (pci_sharedinfo, port, 52, 1) << endl;
   cout << "Interrupt line:      " << hex << pci_read (pci_sharedinfo, port, 60, 1) << endl;
   cout << "Interrupt pin:       " << hex << pci_read (pci_sharedinfo, port, 61, 1) << endl;
   cout << "Min Gnt:             " << hex << pci_read (pci_sharedinfo, port, 62, 1) << endl;
   cout << "Max lat:             " << hex << pci_read (pci_sharedinfo, port, 63, 1) << endl;

   uint64_t memory_machine_address = pci_read (pci_sharedinfo, port, 16, 4);
   uint64_t memory_virtual_address = get_reserved_virtual_address () + (512 * PAGE_SIZE);
   memory_virtual_address = memory_virtual_address & ~(PAGE_SIZE-1);

   for (uint64_t i = 0; i < (128 * 1024); i += PAGE_SIZE)
   {
      Hypercall::update_va_mapping (memory_virtual_address, memory_machine_address);
      memory_machine_address += PAGE_SIZE;
      memory_virtual_address += PAGE_SIZE;
   }

   cout << "front of memory: " << address_to_pointer<uint64_t>(memory_virtual_address) << endl;

   return 0;
}

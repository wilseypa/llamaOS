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
#include <llamaos/net/e1000e/CSR.h>
#include <llamaos/xen/Hypercall.h>
#include <llamaos/xen/Hypervisor.h>
#include <llamaos/config.h>
#include <llamaos/trace.h>

using namespace std;
using namespace llamaos;
using namespace llamaos::memory;
using namespace llamaos::net::e1000e;
using namespace llamaos::xen;

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
      rmb();
   }

   rmb();

   // the backend only returns valid bits from zero to size of value
   switch (size)
   {
   default:
   case 1:
      pci_sharedinfo->op.value &= 0xFF;
      break;

   case 2:
      pci_sharedinfo->op.value &= 0xFFFF;
      break;

   case 4:
      pci_sharedinfo->op.value &= 0xFFFFFFFF;
      break;
   }

   return pci_sharedinfo->op.value;
}

static void pci_write (struct xen_pci_sharedinfo *pci_sharedinfo, evtchn_port_t port, uint32_t offset, uint32_t value, uint32_t size)
{
   struct xen_pci_op op;
   memset(&op, 0, sizeof(op));

   op.cmd = XEN_PCI_OP_conf_write;
   op.domain = 0;
   op.bus = 0;
   op.devfn = 0;
   op.offset = offset;
   op.size = size;
   op.value = value;

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

   cout << endl << "iterate through cap pointers..." << endl;

   uint32_t next_pointer = pci_read (pci_sharedinfo, port, 52, 1);

   while (0 != next_pointer)
   {
      uint32_t cap_id = pci_read (pci_sharedinfo, port, next_pointer, 1);

      switch (cap_id)
      {
      default:
         cout << "Unknown capability id: " << cap_id << endl;
         cout << endl;
         break;

      case 0x01:
         cout << "Power management" << endl;
         cout << "Cap ID:              " << pci_read (pci_sharedinfo, port, next_pointer +  0, 1) << endl;
         cout << "Next pointer:        " << pci_read (pci_sharedinfo, port, next_pointer +  1, 1) << endl;
         cout << "PMC:                 " << pci_read (pci_sharedinfo, port, next_pointer +  2, 2) << endl;
         cout << "PMCR:                " << pci_read (pci_sharedinfo, port, next_pointer +  4, 2) << endl;
         cout << "PMCR_BSE:            " << pci_read (pci_sharedinfo, port, next_pointer +  6, 1) << endl;
         cout << "Data:                " << pci_read (pci_sharedinfo, port, next_pointer +  8, 1) << endl;
         cout << endl;
         break;

      case 0x05:
         cout << endl << "MSI configuration" << endl;
         cout << "Cap ID:              " << pci_read (pci_sharedinfo, port, next_pointer +  0, 1) << endl;
         cout << "Next pointer:        " << pci_read (pci_sharedinfo, port, next_pointer +  1, 1) << endl;
         cout << "Message control:     " << pci_read (pci_sharedinfo, port, next_pointer +  2, 2) << endl;
         cout << "Message addr:        " << pci_read (pci_sharedinfo, port, next_pointer +  4, 4) << endl;
         cout << "Message upper addr:  " << pci_read (pci_sharedinfo, port, next_pointer +  8, 4) << endl;
         cout << "Message data:        " << pci_read (pci_sharedinfo, port, next_pointer + 12, 2) << endl;
         cout << endl;
         break;

      case 0x10:
         cout << endl << "PCIe configuration" << endl;
         cout << "Cap ID:              " << pci_read (pci_sharedinfo, port, next_pointer +  0, 1) << endl;
         cout << "Next pointer:        " << pci_read (pci_sharedinfo, port, next_pointer +  1, 1) << endl;
         cout << "Capability register: " << pci_read (pci_sharedinfo, port, next_pointer +  2, 2) << endl;
         cout << "Device capability:   " << pci_read (pci_sharedinfo, port, next_pointer +  4, 4) << endl;
         cout << "Device control:      " << pci_read (pci_sharedinfo, port, next_pointer +  8, 2) << endl;
         cout << "Device status:       " << pci_read (pci_sharedinfo, port, next_pointer + 10, 2) << endl;
         cout << "Link capability:     " << pci_read (pci_sharedinfo, port, next_pointer + 12, 4) << endl;
         cout << "Link control:        " << pci_read (pci_sharedinfo, port, next_pointer + 16, 2) << endl;
         cout << "Link status:         " << pci_read (pci_sharedinfo, port, next_pointer + 18, 2) << endl;
         cout << endl;
         break;

      case 0x11:
         cout << endl << "MSI-X configuration" << endl;
         cout << "Cap ID:              " << pci_read (pci_sharedinfo, port, next_pointer +  0, 1) << endl;
         cout << "Next pointer:        " << pci_read (pci_sharedinfo, port, next_pointer +  1, 1) << endl;
         cout << "Message control:     " << pci_read (pci_sharedinfo, port, next_pointer +  2, 2) << endl;
         cout << "Table offset:        " << pci_read (pci_sharedinfo, port, next_pointer +  4, 4) << endl;
         cout << "PBA offset:          " << pci_read (pci_sharedinfo, port, next_pointer +  8, 4) << endl;
         cout << endl;
         break;
      }

      next_pointer = pci_read (pci_sharedinfo, port, next_pointer + 1, 1);
   }

   uint16_t Command = pci_read (pci_sharedinfo, port,  4, 2);

   // enable PCIe memory
   Command |= 0x2;

   // enable bus master
   Command |= 0x4;

   cout << endl << "writing command..." << endl;
   pci_write (pci_sharedinfo, port, 4, Command, 2);
   cout << "Command:             " << hex << pci_read (pci_sharedinfo, port,  4, 2) << endl;

   // map the 128k PCIe memory
   uint64_t memory_machine_address = pci_read (pci_sharedinfo, port, 16, 4);
   memory_machine_address &= ~0xF;

   uint64_t memory_virtual_address = get_reserved_virtual_address () + (512 * PAGE_SIZE);
   memory_virtual_address &= ~(PAGE_SIZE-1);

   CSR csr (memory_machine_address, memory_virtual_address);

   Device_control CTRL = csr.read_CTRL ();
   Device_status STATUS = csr.read_STATUS ();

   cout << "CSR CTRL: " << hex << CTRL << endl;
   cout << "CSR STATUS: " << hex << STATUS << endl;

   cout << "setting GIO_master_disable..." << endl;
   CTRL.set_GIO_master_disable (true);
   csr.write_CTRL (CTRL);

   cout << "waiting for GIO_master_disable..." << endl;
   STATUS = csr.read_STATUS ();
   while (STATUS.get_GIO_MASTER_ENABLED())
   {
      STATUS = csr.read_STATUS ();
   }

   cout << "masking interrupts..." << endl;
   csr.write (0x000D8, 0x1FFFFFF);

   cout << "disable receiver..." << endl;
   csr.write (0x00100, 0);

   cout << "disable transmitter..." << endl;
   csr.write (0x00400, (1 << 3));

   STATUS = csr.read_STATUS ();

   gettimeofday (&tv1, nullptr);

   for (;;)
   {
      gettimeofday (&tv2, nullptr);

      if ((tv2.tv_sec - tv1.tv_sec) > 2)
      {
         break;
      }
   }

   cout << "getting hw semaphore..." << csr.read (0x00F00) << endl;
   uint32_t extcnf_ctrl = csr.read (0x00F00);
   extcnf_ctrl |= 0x20;
   csr.write(0x00F00, extcnf_ctrl);

   extcnf_ctrl = csr.read (0x00F00);
   cout << "getting hw semaphore..." << csr.read (0x00F00) << endl;

   while (!(extcnf_ctrl & 0x20))
   {
      extcnf_ctrl |= 0x20;

   gettimeofday (&tv1, nullptr);

   for (;;)
   {
      gettimeofday (&tv2, nullptr);

      if ((tv2.tv_sec - tv1.tv_sec) > 1)
      {
         break;
      }
   }

      csr.write(0x00F00, extcnf_ctrl);
      extcnf_ctrl = csr.read (0x00F00);
   cout << "getting hw semaphore..." << csr.read (0x00F00) << endl;
   break;
   }


   cout << "reseting..." << endl;
   CTRL.set_RST (true);
   csr.write_CTRL (CTRL);

   cout << "release hw semaphore..." << endl;
   extcnf_ctrl = csr.read (0x00F00);
   extcnf_ctrl &= ~0x20;
   csr.write(0x00F00, extcnf_ctrl);

   gettimeofday (&tv1, nullptr);

   for (;;)
   {
      gettimeofday (&tv2, nullptr);

      if ((tv2.tv_sec - tv1.tv_sec) > 2)
      {
         break;
      }
   }

   cout << "reset EEPROM..." << endl;
   uint32_t ctrl_ext = csr.read (0x00018);
   ctrl_ext |= 0x2000;
   csr.write(0x00018, ctrl_ext);
   STATUS = csr.read_STATUS ();

   gettimeofday (&tv1, nullptr);

   for (;;)
   {
      gettimeofday (&tv2, nullptr);

      if ((tv2.tv_sec - tv1.tv_sec) > 2)
      {
         break;
      }
   }

   cout << "waiting for EEPROM read..." << endl;
   while (!(csr.read(0x00010) & 0x200));

   gettimeofday (&tv1, nullptr);

   for (;;)
   {
      gettimeofday (&tv2, nullptr);

      if ((tv2.tv_sec - tv1.tv_sec) > 2)
      {
         break;
      }
   }

   CTRL = csr.read_CTRL ();
   STATUS = csr.read_STATUS ();

   cout << "CSR CTRL: " << hex << CTRL << endl;
   cout << "CSR STATUS: " << hex << STATUS << endl;

   cout << "masking interrupts..." << endl;
   csr.write (0x000D8, 0x1FFFFFF);
   csr.read(0x000C0);


   return 0;
}

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
#include <cstdint>
#include <cstdlib>
#include <malloc.h>

#include <iostream>

#include <xen/io/pciif.h>
#include <xen/io/xenbus.h>
#include <xen/event_channel.h>

#include <llamaos/api/PCI.h>
#include <llamaos/api/sleep.h>
#include <llamaos/memory/memory.h>
#include <llamaos/xen/Hypercall.h>
#include <llamaos/xen/Hypervisor.h>
#include <llamaos/xen/Xenstore.h>
#include <llamaos/config.h>

namespace llamaos {
namespace api {

class PCI_impl
{
public:
   PCI_impl ();
   ~PCI_impl ();

   uint8_t read_config_byte (uint64_t offset) const;
   uint16_t read_config_word (uint64_t offset) const;
   uint32_t read_config_dword (uint64_t offset) const;

   void write_config_byte (uint64_t offset, uint8_t value) const;
   void write_config_word (uint64_t offset, uint16_t value) const;
   void write_config_dword (uint64_t offset, uint32_t value) const;

private:
   PCI_impl (const PCI_impl&);
   PCI_impl &operator= (const PCI_impl&);

   uint32_t read_config (uint32_t offset, uint32_t size) const;
   void write_config (uint32_t offset, uint32_t value, uint32_t size) const;

   struct xen_pci_sharedinfo *const pci_sharedinfo;
   evtchn_port_t port;

};

} }

using namespace std;
using namespace llamaos;
using namespace llamaos::api;
using namespace llamaos::memory;
using namespace llamaos::xen;

PCI::PCI ()
   :  impl(new PCI_impl())
{

}

PCI::~PCI ()
{
   delete impl;
}

uint8_t PCI::read_config_byte (uint64_t offset) const
{
   return impl->read_config_byte (offset);
}

uint16_t PCI::read_config_word (uint64_t offset) const
{
   return impl->read_config_word (offset);
}

uint32_t PCI::read_config_dword (uint64_t offset) const
{
   return impl->read_config_dword (offset);
}

void PCI::write_config_byte (uint64_t offset, uint8_t value) const
{
   impl->write_config_byte (offset, value);
}

void PCI::write_config_word (uint64_t offset, uint16_t value) const
{
   impl->write_config_word (offset, value);
}

void PCI::write_config_dword (uint64_t offset, uint32_t value) const
{
   impl->write_config_dword (offset, value);
}

PCI_impl::PCI_impl ()
   :  pci_sharedinfo(static_cast<xen_pci_sharedinfo *>(memalign (PAGE_SIZE, sizeof(xen_pci_sharedinfo)))),
      port()
{
   cout << "setup pci device xenbus..." << endl;
   Xenstore &xenstore = Hypervisor::get_instance ()->xenstore;

   domid_t backend_id = Hypervisor::get_instance ()->xenstore.read<domid_t>("device/pci/0/backend-id");
   cout << "backend-id: " << backend_id << endl;

   cout << "pci_sharedinfo: " << pci_sharedinfo << endl;
   cout << "pci_sharedinfo: " << pointer_to_address (pci_sharedinfo) << endl;
   memset (pci_sharedinfo, 0, sizeof(struct xen_pci_sharedinfo));
   grant_ref_t ref = Hypervisor::get_instance ()->grant_table.grant_access (backend_id, pci_sharedinfo);
   cout << "grant ref: " << ref << endl;

   Hypercall::event_channel_alloc_unbound (0, port);

   xenstore.start_transaction (1);
   xenstore.write ("device/pci/0/pci-op-ref", ref);
   xenstore.write ("device/pci/0/event-channel", port);
   xenstore.write ("device/pci/0/magic", XEN_PCI_MAGIC);
   xenstore.write ("device/pci/0/state", XenbusStateInitialised);
   xenstore.end_transaction (1);

   sleep (3);

   xenstore.write ("device/pci/0/state", XenbusStateConnected);

   sleep (3);

   string backend = xenstore.read("device/pci/0/backend");
   cout << "backend: " << backend << endl;
   cout << "backend state: " << xenstore.read(backend+"/state") << endl;
   cout << "frontend state: " << xenstore.read("device/pci/0/state") << endl;

   cout << "num-devs: " << xenstore.read(backend+"/num_devs") << endl;

   string bus_address = xenstore.read(backend+"/dev-0");
   cout << "bus_address: " << bus_address << endl;
}

PCI_impl::~PCI_impl ()
{
   free(pci_sharedinfo);
}

uint8_t PCI_impl::read_config_byte (uint64_t offset) const
{
   return read_config (offset, 1);
}

uint16_t PCI_impl::read_config_word (uint64_t offset) const
{
   return read_config (offset, 2);
}

uint32_t PCI_impl::read_config_dword (uint64_t offset) const
{
   return read_config (offset, 4);
}

void PCI_impl::write_config_byte (uint64_t offset, uint8_t value) const
{
   write_config (offset, value, 1);
}

void PCI_impl::write_config_word (uint64_t offset, uint16_t value) const
{
   write_config (offset, value, 2);
}

void PCI_impl::write_config_dword (uint64_t offset, uint32_t value) const
{
   write_config (offset, value, 4);
}

uint32_t PCI_impl::read_config (uint32_t offset, uint32_t size) const
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

   do
   {
      mb();

   } while (pci_sharedinfo->flags & XEN_PCIF_active);

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

void PCI_impl::write_config (uint32_t offset, uint32_t value, uint32_t size) const
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

   do
   {
      mb();

   } while (pci_sharedinfo->flags & XEN_PCIF_active);
}

ostream &llamaos::api::operator<< (ostream &out, const PCI &pci)
{
   out << "Vendor ID:           " << hex << pci.read_config_word (0) << endl;
   out << "Device ID:           " << hex << pci.read_config_word (2) << endl;
   out << "Command:             " << hex << pci.read_config_word (4) << endl;
   out << "Status:              " << hex << pci.read_config_word (6) << endl;
   out << "Rev ID:              " << hex << static_cast<int>(pci.read_config_byte (8)) << endl;
   out << "Class Code [0]:      " << hex << static_cast<int>(pci.read_config_byte (9)) << endl;
   out << "Class Code [1]:      " << hex << static_cast<int>(pci.read_config_byte (10)) << endl;
   out << "Class Code [2]:      " << hex << static_cast<int>(pci.read_config_byte (11)) << endl;
   out << "Cache line:          " << hex << static_cast<int>(pci.read_config_byte (12)) << endl;
   out << "Lat timer:           " << hex << static_cast<int>(pci.read_config_byte (13)) << endl;
   out << "Header type:         " << hex << static_cast<int>(pci.read_config_byte (14)) << endl;
   out << "BIST:                " << hex << static_cast<int>(pci.read_config_byte (15)) << endl;
   out << "BAR0:                " << hex << pci.read_config_dword (16) << endl;
   out << "BAR1:                " << hex << pci.read_config_dword (20) << endl;
   out << "BAR2:                " << hex << pci.read_config_dword (24) << endl;
   out << "BAR3:                " << hex << pci.read_config_dword (28) << endl;
   out << "BAR4:                " << hex << pci.read_config_dword (32) << endl;
   out << "BAR5:                " << hex << pci.read_config_dword (36) << endl;
   out << "Cardbus CIS:         " << hex << pci.read_config_dword (40) << endl;
   out << "Subsystem Vendor ID: " << hex << pci.read_config_word (44) << endl;
   out << "Subsystem ID:        " << hex << pci.read_config_word (46) << endl;
   out << "Expansion ROM:       " << hex << pci.read_config_dword (48) << endl;
   out << "Cap. Pointer:        " << hex << static_cast<int>(pci.read_config_byte (52)) << endl;
   out << "Interrupt line:      " << hex << static_cast<int>(pci.read_config_byte (60)) << endl;
   out << "Interrupt pin:       " << hex << static_cast<int>(pci.read_config_byte (61)) << endl;
   out << "Min Gnt:             " << hex << static_cast<int>(pci.read_config_byte (62)) << endl;
   out << "Max lat:             " << hex << static_cast<int>(pci.read_config_byte (63)) << endl;

   out << endl << "iterate through cap pointers..." << endl;

   uint32_t next_pointer = pci.read_config_byte (52);

   while (0 != next_pointer)
   {
      uint32_t cap_id = pci.read_config_byte (next_pointer);

      switch (cap_id)
      {
      default:
         out << "Unknown capability id: " << cap_id << endl;
         out << endl;
         break;

      case 0x01:
         out << "Power management" << endl;
         out << "Cap ID:              " << static_cast<int>(pci.read_config_byte (next_pointer +  0)) << endl;
         out << "Next pointer:        " << static_cast<int>(pci.read_config_byte (next_pointer +  1)) << endl;
         out << "PMC:                 " << pci.read_config_word (next_pointer +  2) << endl;
         out << "PMCR:                " << pci.read_config_word (next_pointer +  4) << endl;
         out << "PMCR_BSE:            " << static_cast<int>(pci.read_config_byte (next_pointer +  6)) << endl;
         out << "Data:                " << static_cast<int>(pci.read_config_byte (next_pointer +  8)) << endl;
         out << endl;
         break;

      case 0x05:
         out << endl << "MSI configuration" << endl;
         out << "Cap ID:              " << static_cast<int>(pci.read_config_byte (next_pointer +  0)) << endl;
         out << "Next pointer:        " << static_cast<int>(pci.read_config_byte (next_pointer +  1)) << endl;
         out << "Message control:     " << pci.read_config_word (next_pointer +  2) << endl;
         out << "Message addr:        " << pci.read_config_dword (next_pointer +  4) << endl;
         out << "Message upper addr:  " << pci.read_config_dword (next_pointer +  8) << endl;
         out << "Message data:        " << pci.read_config_word (next_pointer + 12) << endl;
         out << endl;
         break;

      case 0x10:
         out << endl << "PCIe configuration" << endl;
         out << "Cap ID:              " << static_cast<int>(pci.read_config_byte (next_pointer +  0)) << endl;
         out << "Next pointer:        " << static_cast<int>(pci.read_config_byte (next_pointer +  1)) << endl;
         out << "Capability register: " << pci.read_config_word (next_pointer +  2) << endl;
         out << "Device capability:   " << pci.read_config_dword (next_pointer +  4) << endl;
         out << "Device control:      " << pci.read_config_word (next_pointer +  8) << endl;
         out << "Device status:       " << pci.read_config_word (next_pointer + 10) << endl;
         out << "Link capability:     " << pci.read_config_dword (next_pointer + 12) << endl;
         out << "Link control:        " << pci.read_config_word (next_pointer + 16) << endl;
         out << "Link status:         " << pci.read_config_word (next_pointer + 18) << endl;
         out << endl;
         break;

      case 0x11:
         out << endl << "MSI-X configuration" << endl;
         out << "Cap ID:              " << static_cast<int>(pci.read_config_byte (next_pointer +  0)) << endl;
         out << "Next pointer:        " << static_cast<int>(pci.read_config_byte (next_pointer +  1)) << endl;
         out << "Message control:     " << pci.read_config_word (next_pointer +  2) << endl;
         out << "Table offset:        " << pci.read_config_dword (next_pointer +  4) << endl;
         out << "PBA offset:          " << pci.read_config_dword (next_pointer +  8) << endl;
         out << endl;
         break;
      }

      next_pointer = pci.read_config_byte (next_pointer + 1);
   }

   return out;
}

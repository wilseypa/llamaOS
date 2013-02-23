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

#include <malloc.h>

#include <cstring>
#include <cstdint>
#include <cstdlib>

#include <iostream>

#include <xen/io/pciif.h>
#include <xen/io/xenbus.h>
#include <xen/event_channel.h>

#include <llamaos/api/pci/PCI.h>
#include <llamaos/api/sleep.h>
#include <llamaos/memory/Memory.h>
#include <llamaos/xen/Hypercall.h>
#include <llamaos/xen/Hypervisor.h>
#include <llamaos/xen/Xenstore.h>
#include <llamaos/llamaOS.h>

namespace llamaos {
namespace api {
namespace pci {

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

} } }

using namespace std;
using namespace llamaos;
using namespace llamaos::api;
using namespace llamaos::api::pci;
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

   cout << "calling event_channel_alloc_unbound..." << endl;
   Hypercall::event_channel_alloc_unbound (0, port);
   cout << "event_channel_alloc_unbound resulted in port " << port << endl;

   cout << "starting transaction to initialise xenbus device..." << endl;
   xenstore.start_transaction (1);
   xenstore.write ("device/pci/0/pci-op-ref", ref);
   xenstore.write ("device/pci/0/event-channel", port);
   xenstore.write ("device/pci/0/magic", XEN_PCI_MAGIC);
   xenstore.write ("device/pci/0/state", XenbusStateInitialised);
   xenstore.end_transaction (1);
   cout << "ending transaction to initialise xenbus device..." << endl;

   string backend = xenstore.read("device/pci/0/backend");

   for (int i = 0; i < 10; i++)
   {
      string backend_state = xenstore.read(backend + "/state");

      cout << "waiting for backend state: " << backend_state << endl;

      if (backend_state == "4")
      {
         break;
      }

      sleep (1);
   }

   xenstore.write ("device/pci/0/state", XenbusStateConnected);

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

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

int main (int /* argc */, char ** /* argv [] */)
{
   cout << "running e1000e llamaNET domain...\n" << endl;

   cout << "waiting for 60 secs..." << endl;
   timeval tv, tv1, tv2;
   gettimeofday (&tv1, nullptr);
   tv = tv1;

   for (;;)
   {
      gettimeofday (&tv2, nullptr);

      if ((tv2.tv_sec - tv1.tv_sec) > 60)
      {
         break;
      }
   }

   cout << "setup pci device xenbus..." << endl;

   domid_t backend_id = Hypervisor::get_instance ()->xenstore.read<domid_t>("device/pci/0/backend-id");
   cout << "backend-id: " << backend_id << endl;

   char *buffer = new char [sizeof(struct xen_pci_sharedinfo) + PAGE_SIZE];

   struct xen_pci_sharedinfo *pci_sharedinfo = address_to_pointer<struct xen_pci_sharedinfo> (pointer_to_address (buffer + PAGE_SIZE) & ~(PAGE_SIZE-1));
   grant_ref_t ref = Hypervisor::get_instance ()->grant_table.grant_access (backend_id, pci_sharedinfo);

   evtchn_port_t port = 0;
   Hypercall::event_channel_alloc_unbound (0, port);

   Hypervisor::get_instance ()->xenstore.start_transaction (1);
   Hypervisor::get_instance ()->xenstore.write ("device/pci/0/pci-op-ref", ref);
   Hypervisor::get_instance ()->xenstore.write ("device/pci/0/event-channel", port);
   Hypervisor::get_instance ()->xenstore.write ("device/pci/0/magic", XEN_PCI_MAGIC);
   Hypervisor::get_instance ()->xenstore.write ("device/pci/0/state", XenbusStateInitialised);
   Hypervisor::get_instance ()->xenstore.end_transaction (1);

   return 0;
}

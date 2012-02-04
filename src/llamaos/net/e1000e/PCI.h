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

#ifndef llamaos_net_e1000e_pci_h_
#define llamaos_net_e1000e_pci_h_

#include <cstdint>

#include <xen/io/pciif.h>
#include <xen/event_channel.h>

namespace llamaos {
namespace net {
namespace e1000e {

class PCI
{
public:
   PCI ();
   virtual ~PCI ();

   uint8_t read_config_byte (uint64_t offset);
   uint16_t read_config_word (uint64_t offset);
   uint32_t read_config_dword (uint64_t offset);

   void write_config_byte (uint64_t offset, uint8_t value);
   void write_config_word (uint64_t offset, uint16_t value);
   void write_config_dword (uint64_t offset, uint32_t value);

private:
   PCI (const PCI &);
   PCI &operator= (const PCI &);

   struct xen_pci_sharedinfo *pci_sharedinfo;
   evtchn_port_t port;

};

} } }

#endif  // llamaos_net_e1000e_pci_h_

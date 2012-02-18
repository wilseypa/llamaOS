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

#include <iostream>

#include <llamaos/api/pci/BAR.h>
#include <llamaos/api/pci/Command.h>
#include <llamaos/api/pci/PCI.h>
#include <llamaos/api/pci/Status.h>
#include <llamaos/api/sleep.h>
#include <llamaos/memory/memory.h>
#include <llamaos/config.h>

using namespace std;
using namespace llamaos;
using namespace llamaos::api;
using namespace llamaos::api::pci;
using namespace llamaos::memory;

int main (int /* argc */, char ** /* argv [] */)
{
   cout << "running 82574 llamaNET domain...\n" << endl;
   cout << "waiting..." << endl;
   sleep (3);

   PCI pci;
   sleep (1);
   cout << "PCI config:" << endl;
   cout << pci << endl;

   uint16_t vendor_id = pci.read_config_word (0);
   uint16_t device_id = pci.read_config_word (2);
   uint32_t class_code = (pci.read_config_byte (11) << 16) | (pci.read_config_byte (10) << 8) | pci.read_config_byte(9);
   uint16_t subvendor_id = pci.read_config_word (44);

   if (   (vendor_id != 0x8086)
       || (device_id != 0x10D3)
       || (class_code != 0x020000)
       || (subvendor_id != 0x8086))
   {
      cout << "PCI hardware detected is not 82574" << endl;
      return -1;
   }

   Command command = pci.read_config_word (4);
   Status status =  pci.read_config_word (6);

   cout << command << status << endl;

   command.Interrupt_disable (true);
   command.IO_enable(false);
   command.Mastering_enable(true);
   command.Memory_enable(true);

   cout << "Writing " << command << endl;
   pci.write_config_word (4, command);

   BAR bar0 = pci.read_config_dword (16);
   cout << bar0 << endl;

   uint64_t machine_address = bar0.Address ();

   // also a hack, get an open address in the second half of the reserved area
   uint64_t virtual_address = get_reserved_virtual_address () + (512 * PAGE_SIZE);
   virtual_address &= ~(PAGE_SIZE-1);

   // mapping 128k
   for (uint64_t i = 0; i < 32; i++)
   {
      uint64_t offset = (i * PAGE_SIZE);
      Hypercall::update_va_mapping_nocache (virtual_address + offset, machine_address + offset);
   }

//   CSR csr (virtual_address);

//   CTRL ctrl = csr.read_CTRL ();
//   STATUS status = csr.read_STATUS ();

//   cout << "CSR CTRL: " << hex << ctrl << endl;
//   cout << "CSR STATUS: " << hex << status << endl;

   return 0;
}

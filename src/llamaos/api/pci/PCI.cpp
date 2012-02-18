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

#include <ostream>

#include <llamaos/api/pci/PCI.h>

using namespace std;

ostream &llamaos::api::pci::operator<< (ostream &out, const PCI &pci)
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

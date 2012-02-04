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
#include <llamaos/net/e1000e/PCI.h>
#include <llamaos/xen/Hypercall.h>
#include <llamaos/xen/Hypervisor.h>
#include <llamaos/config.h>
#include <llamaos/trace.h>

using namespace std;
using namespace llamaos;
using namespace llamaos::memory;
using namespace llamaos::net::e1000e;
using namespace llamaos::xen;

// crude sleep function
static void sleep (unsigned int sec)
{
   timeval tv1, tv2;

   gettimeofday (&tv1, nullptr);

   for (;;)
   {
      gettimeofday (&tv2, nullptr);

      if ((tv2.tv_sec - tv1.tv_sec) > sec)
      {
         break;
      }

      Hypercall::sched_op_yield ();
   }
}


int main (int /* argc */, char ** /* argv [] */)
{
   cout << "running e1000e llamaNET domain...\n" << endl;

   cout << "waiting..." << endl;
   sleep (3);

   PCI pci;


   cout << "Vendor ID:           " << hex << pci.read_config_word (0) << endl;
   cout << "Device ID:           " << hex << pci.read_config_word (2) << endl;
   cout << "Command:             " << hex << pci.read_config_word (4) << endl;
   cout << "Status:              " << hex << pci.read_config_word (6) << endl;
   cout << "Rev ID:              " << hex << static_cast<int>(pci.read_config_byte (8)) << endl;
   cout << "Class Code [0]:      " << hex << static_cast<int>(pci.read_config_byte (9)) << endl;
   cout << "Class Code [1]:      " << hex << static_cast<int>(pci.read_config_byte (10)) << endl;
   cout << "Class Code [2]:      " << hex << static_cast<int>(pci.read_config_byte (11)) << endl;
   cout << "Cache line:          " << hex << static_cast<int>(pci.read_config_byte (12)) << endl;
   cout << "Lat timer:           " << hex << static_cast<int>(pci.read_config_byte (13)) << endl;
   cout << "Header type:         " << hex << static_cast<int>(pci.read_config_byte (14)) << endl;
   cout << "BIST:                " << hex << static_cast<int>(pci.read_config_byte (15)) << endl;
   cout << "BAR0:                " << hex << pci.read_config_dword (16) << endl;
   cout << "BAR1:                " << hex << pci.read_config_dword (20) << endl;
   cout << "BAR2:                " << hex << pci.read_config_dword (24) << endl;
   cout << "BAR3:                " << hex << pci.read_config_dword (28) << endl;
   cout << "BAR4:                " << hex << pci.read_config_dword (32) << endl;
   cout << "BAR5:                " << hex << pci.read_config_dword (36) << endl;
   cout << "Cardbus CIS:         " << hex << pci.read_config_dword (40) << endl;
   cout << "Subsystem Vendor ID: " << hex << pci.read_config_word (44) << endl;
   cout << "Subsystem ID:        " << hex << pci.read_config_word (46) << endl;
   cout << "Expansion ROM:       " << hex << pci.read_config_dword (48) << endl;
   cout << "Cap. Pointer:        " << hex << static_cast<int>(pci.read_config_byte (52)) << endl;
   cout << "Interrupt line:      " << hex << static_cast<int>(pci.read_config_byte (60)) << endl;
   cout << "Interrupt pin:       " << hex << static_cast<int>(pci.read_config_byte (61)) << endl;
   cout << "Min Gnt:             " << hex << static_cast<int>(pci.read_config_byte (62)) << endl;
   cout << "Max lat:             " << hex << static_cast<int>(pci.read_config_byte (63)) << endl;

   cout << endl << "iterate through cap pointers..." << endl;

   uint32_t next_pointer = pci.read_config_byte (52);

   while (0 != next_pointer)
   {
      uint32_t cap_id = pci.read_config_byte (next_pointer);

      switch (cap_id)
      {
      default:
         cout << "Unknown capability id: " << cap_id << endl;
         cout << endl;
         break;

      case 0x01:
         cout << "Power management" << endl;
         cout << "Cap ID:              " << static_cast<int>(pci.read_config_byte (next_pointer +  0)) << endl;
         cout << "Next pointer:        " << static_cast<int>(pci.read_config_byte (next_pointer +  1)) << endl;
         cout << "PMC:                 " << pci.read_config_word (next_pointer +  2) << endl;
         cout << "PMCR:                " << pci.read_config_word (next_pointer +  4) << endl;
         cout << "PMCR_BSE:            " << static_cast<int>(pci.read_config_byte (next_pointer +  6)) << endl;
         cout << "Data:                " << static_cast<int>(pci.read_config_byte (next_pointer +  8)) << endl;
         cout << endl;
         break;

      case 0x05:
         cout << endl << "MSI configuration" << endl;
         cout << "Cap ID:              " << static_cast<int>(pci.read_config_byte (next_pointer +  0)) << endl;
         cout << "Next pointer:        " << static_cast<int>(pci.read_config_byte (next_pointer +  1)) << endl;
         cout << "Message control:     " << pci.read_config_word (next_pointer +  2) << endl;
         cout << "Message addr:        " << pci.read_config_dword (next_pointer +  4) << endl;
         cout << "Message upper addr:  " << pci.read_config_dword (next_pointer +  8) << endl;
         cout << "Message data:        " << pci.read_config_word (next_pointer + 12) << endl;
         cout << endl;
         break;

      case 0x10:
         cout << endl << "PCIe configuration" << endl;
         cout << "Cap ID:              " << static_cast<int>(pci.read_config_byte (next_pointer +  0)) << endl;
         cout << "Next pointer:        " << static_cast<int>(pci.read_config_byte (next_pointer +  1)) << endl;
         cout << "Capability register: " << pci.read_config_word (next_pointer +  2) << endl;
         cout << "Device capability:   " << pci.read_config_dword (next_pointer +  4) << endl;
         cout << "Device control:      " << pci.read_config_word (next_pointer +  8) << endl;
         cout << "Device status:       " << pci.read_config_word (next_pointer + 10) << endl;
         cout << "Link capability:     " << pci.read_config_dword (next_pointer + 12) << endl;
         cout << "Link control:        " << pci.read_config_word (next_pointer + 16) << endl;
         cout << "Link status:         " << pci.read_config_word (next_pointer + 18) << endl;
         cout << endl;
         break;

      case 0x11:
         cout << endl << "MSI-X configuration" << endl;
         cout << "Cap ID:              " << static_cast<int>(pci.read_config_byte (next_pointer +  0)) << endl;
         cout << "Next pointer:        " << static_cast<int>(pci.read_config_byte (next_pointer +  1)) << endl;
         cout << "Message control:     " << pci.read_config_word (next_pointer +  2) << endl;
         cout << "Table offset:        " << pci.read_config_dword (next_pointer +  4) << endl;
         cout << "PBA offset:          " << pci.read_config_dword (next_pointer +  8) << endl;
         cout << endl;
         break;
      }

      next_pointer = pci.read_config_byte (next_pointer + 1);
   }

return 0;

   uint16_t Command = pci.read_config_word (4);

   // enable PCIe memory
   Command |= 0x2;

   // enable bus master
   Command |= 0x4;

   cout << endl << "writing command..." << endl;
   pci.write_config_word (4, Command);
   cout << "Command:             " << hex << pci.read_config_word (4) << endl;

   // map the 128k PCIe memory
   uint64_t memory_machine_address = pci.read_config_dword (16);
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

   sleep (2);

   cout << "getting hw semaphore..." << csr.read (0x00F00) << endl;
   uint32_t extcnf_ctrl = csr.read (0x00F00);
   extcnf_ctrl |= 0x20;
   csr.write(0x00F00, extcnf_ctrl);

   extcnf_ctrl = csr.read (0x00F00);
   cout << "getting hw semaphore..." << csr.read (0x00F00) << endl;

   while (!(extcnf_ctrl & 0x20))
   {
      extcnf_ctrl |= 0x20;

      sleep (1);

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

   sleep (2);

   cout << "reset EEPROM..." << endl;
   uint32_t ctrl_ext = csr.read (0x00018);
   ctrl_ext |= 0x2000;
   csr.write(0x00018, ctrl_ext);
   STATUS = csr.read_STATUS ();

   sleep (2);

   cout << "waiting for EEPROM read..." << endl;
   while (!(csr.read(0x00010) & 0x200));

   sleep (2);

   CTRL = csr.read_CTRL ();
   STATUS = csr.read_STATUS ();

   cout << "CSR CTRL: " << hex << CTRL << endl;
   cout << "CSR STATUS: " << hex << STATUS << endl;

   cout << "masking interrupts..." << endl;
   csr.write (0x000D8, 0x1FFFFFF);
   csr.read(0x000C0);


   return 0;
}

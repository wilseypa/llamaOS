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

   pci.print_config ();

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

   // clear the BAR address flags
   memory_machine_address &= ~0xFUL;

   // also a hack, get an open address in the second half of the reserved area
   uint64_t memory_virtual_address = get_reserved_virtual_address () + (512 * PAGE_SIZE);
   memory_virtual_address &= ~(PAGE_SIZE-1);

   CSR csr (memory_machine_address, memory_virtual_address);

   Device_control CTRL = csr.read_CTRL ();
   Device_status STATUS = csr.read_STATUS ();

   cout << "CSR CTRL: " << hex << CTRL << endl;
   cout << "CSR STATUS: " << hex << STATUS << endl;

   cout << "masking interrupts..." << endl;
   csr.write (0x000D8, 0x1FFFFFF);

   cout << "reseting..." << endl;
   csr.write (0x00000, 0x84000000);

   sleep (2);

   cout << "masking interrupts..." << endl;
   csr.write (0x000D8, 0x1FFFFFF);

   STATUS = csr.read_STATUS ();
   cout << "CSR STATUS: " << hex << STATUS << endl;

   cout << "forcing speed and duplex..." << endl;
   csr.write (0x00000, 0x101B01);

   sleep (2);

   STATUS = csr.read_STATUS ();
   cout << "CSR STATUS: " << hex << STATUS << endl;

   cout << "setting link up..." << endl;
   csr.write (0x00000, 0x101B41);

   sleep (2);

   STATUS = csr.read_STATUS ();
   cout << "CSR STATUS: " << hex << STATUS << endl;

   return 0;

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

   cout.flush ();
   return 0;
}

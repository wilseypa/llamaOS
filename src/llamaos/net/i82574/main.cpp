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

#include <iostream>

#include <llamaos/api/pci/BAR.h>
#include <llamaos/api/pci/Command.h>
#include <llamaos/api/pci/PCI.h>
#include <llamaos/api/pci/Status.h>
#include <llamaos/api/sleep.h>
#include <llamaos/memory/memory.h>
#include <llamaos/net/i82574/CSR.h>
#include <llamaos/net/i82574/CTRL.h>
#include <llamaos/net/i82574/EXTCNF_CTRL.h>
#include <llamaos/net/i82574/STATUS.h>
#include <llamaos/config.h>

using namespace std;
using namespace llamaos;
using namespace llamaos::api;
using namespace llamaos::api::pci;
using namespace llamaos::memory;
using namespace llamaos::net::i82574;

struct __attribute__ ((__packed__)) rx_desc_t
{
   uint64_t buffer;
   uint16_t length;
   uint16_t checksum;
   uint8_t status;
   uint8_t error;
   uint16_t vlan;
};

struct __attribute__ ((__packed__)) tx_desc_t
{
   uint64_t buffer;
   uint16_t length;
   uint8_t CSO;
   uint8_t CMD;
   uint8_t STA;
   uint8_t CSS;
   uint16_t VLAN;
};

int main (int /* argc */, char ** /* argv [] */)
{
   cout << "running 82574 llamaNET domain...\n" << endl;
   cout << "waiting..." << endl;
   sleep (3);

   PCI pci;
   sleep (1);
   cout << "PCI config:" << endl;
   //cout << pci << endl;

   sleep (10);
   cout << "checking PCI config for valid 82574..." << endl;
   uint16_t vendor_id = pci.read_config_word (0);
   uint16_t device_id = pci.read_config_word (2);
   uint32_t class_code = (pci.read_config_byte (11) << 16) | (pci.read_config_byte (10) << 8) | pci.read_config_byte(9);
   uint16_t subvendor_id = pci.read_config_word (44);

   if (   (vendor_id != 0x8086)
       || (device_id != 0x10D3)
       || (class_code != 0x020000)
       || (subvendor_id != 0x8086))
   {
      cout << "PCI hardware detected is NOT 82574" << endl;
      return -1;
   }
   cout << "PCI hardware detected is82574" << endl;
   cout.flush ();

   sleep (1);
   cout << "enabling PCI access and creating CSR register class..." << endl;

   Command config_command = pci.read_config_word (4);
   Status config_status =  pci.read_config_word (6);

   cout << config_command << config_status << endl;

   config_command.Interrupt_disable (true);
   config_command.IO_enable(false);
   config_command.Mastering_enable(true);
   config_command.Memory_enable(true);

   cout << "Writing " << config_command << endl;
   pci.write_config_word (4, config_command);

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

   CSR csr (virtual_address);
   CTRL ctrl = csr.read_CTRL ();
   STATUS status = csr.read_STATUS ();

   cout << "CSR CTRL: " << hex << ctrl << endl;
   cout << "CSR STATUS: " << hex << status << endl;

   cout << "setting GIO_master_disable..." << endl;
   ctrl.GIO_MD(true);
   csr.write_CTRL (ctrl);

   cout << "waiting for GIO_master_disable..." << endl;
   status = csr.read_STATUS ();

   while (status.GIO_ME ())
   {
      status = csr.read_STATUS ();
   }

   cout << "masking interrupts..." << endl;
   cout << csr.read_IMS () << endl;
   csr.write_IMC(IMC::ALL);
   cout << csr.read_IMS () << endl;

   EXTCNF_CTRL extcnf_ctrl = csr.read_EXTCNF_CTRL ();
   cout << "getting hw semaphore..." << extcnf_ctrl << endl;
   extcnf_ctrl =- EXTCNF_CTRL(0);
   extcnf_ctrl.SW_OWN (true);
   csr.write_EXTCNF_CTRL (extcnf_ctrl);

   extcnf_ctrl = csr.read_EXTCNF_CTRL ();
   cout << "getting hw semaphore..." << extcnf_ctrl << endl;

   while (!(extcnf_ctrl.SW_OWN ()))
   {
      extcnf_ctrl.SW_OWN (true);

      sleep (1);

      csr.write_EXTCNF_CTRL (extcnf_ctrl);
      extcnf_ctrl = csr.read_EXTCNF_CTRL ();
      cout << "getting hw semaphore..." << extcnf_ctrl << endl;
      break;
   }

   cout << "reseting..." << endl;
   ctrl.RST(true);
   ctrl.PHY_RST(true);
   csr.write_CTRL(ctrl);

   sleep (2);

   cout << "masking interrupts..." << endl;
   cout << csr.read_IMS () << endl;
   csr.write_IMC(IMC::ALL);
   cout << csr.read_IMS () << endl;

   status = csr.read_STATUS ();
   cout << "CSR STATUS: " << hex << status << endl;

   CTRL_EXT ctrl_ext = csr.read_CTRL_EXT ();
   cout << "CSR CTRL_EXT: " << hex << ctrl_ext << endl;
   ctrl_ext.SPD_BYPS (true);
   csr.write_CTRL_EXT (ctrl_ext);
   cout << "CSR CTRL_EXT: " << hex << ctrl_ext << endl;

   cout << "forcing speed and duplex..." << endl;
   ctrl = CTRL (0);
   ctrl.FD (true);
   ctrl.SPEED (CTRL::SPEED_1000MBS);
   ctrl.FRCSPD (true);
   ctrl.FRCDPLX (true);
   ctrl.ADVD3WUC (true);
   csr.write_CTRL (ctrl);

   sleep (2);

   status = csr.read_STATUS ();
   cout << "CSR STATUS: " << hex << status << endl;

   sleep (5);

   cout << "setting link up..." << endl;
   ctrl.SLU (true);
   csr.write_CTRL (ctrl);

   sleep (2);

   status = csr.read_STATUS ();
   cout << "CSR STATUS: " << hex << status << endl;

   // from manual 4.6.2: "GCR bit 22 should be set to 1b by software during initialization."
   GCR gcr = csr.read_GCR ();
   gcr.INITIALIZE (true);
   csr.write_GCR (gcr);
   uint32_t gcr2 = csr.read (0x05B64);
   gcr2 |= 1;
   csr.write (0x05B64, gcr2);

   cout << "initialize receiver..." << endl;
   RXDCTL rxdctl (0);
   rxdctl.GRAN (true);
   rxdctl.WTHRESH (1);
   csr.write_RXDCTL (rxdctl);

   cout.flush();
   cout <<  "RCTL: " << csr.read_RCTL () << endl;
   cout <<  "RXDCTL: " << csr.read_RXDCTL () << endl;
   cout << "setup receive descript table..." << endl;
   cout << "sizeof(rx_desc_t): " << sizeof(rx_desc_t) << endl;
   cout.flush();
   volatile struct rx_desc_t *rx_desc = static_cast<struct rx_desc_t *>(memalign (PAGE_SIZE, PAGE_SIZE));
   uint64_t rx_desc_machine_address = virtual_pointer_to_machine_address(rx_desc);
   Hypercall::update_va_mapping_nocache (pointer_to_address (rx_desc), rx_desc_machine_address);
   csr.write_TDBA (rx_desc_machine_address);
   csr.write_TDLEN (256);
   cout << "RDBA: " << hex << csr.read_RDBA() << ", " << rx_desc_machine_address << endl;

   cout << "inserting receive buffer..." << endl;
   char *rx_buffer = static_cast<char *>(memalign (PAGE_SIZE, PAGE_SIZE));
   uint64_t rx_buffer_machine_address = virtual_pointer_to_machine_address(rx_buffer);
   Hypercall::update_va_mapping_nocache (pointer_to_address (rx_buffer), rx_buffer_machine_address);
   rx_desc->buffer = rx_buffer_machine_address;
   rx_desc->length = 0;
   rx_desc->checksum = 0;
   rx_desc->status = 0;
   rx_desc->error = 0;
   rx_desc->vlan = 0;
   csr.write_RDT (1);

   cout << "enabling receiver..." << endl;
   RCTL rctl (0);
   rctl.MPE(true);
   rctl.UPE(true);
   rctl.EN (true);
   csr.write_RCTL (rctl);

   cout << "waiting for packet arrival..." << endl;
   while (0 == rx_desc->status)
   {
      if (csr.read_RDH() > 0)
      {
         cout << "RDH is non-zero!" << endl;
         break;
      }
   }

   cout << "RD Status: " << static_cast<unsigned int>(rx_desc->status) << endl;
   cout << "RD data[]:";

   for (int i = 0; i < rx_desc->length; i++)
   {
      cout << " " << hex << static_cast<unsigned int>(rx_buffer [i]);
   }

   cout << endl;
   cout << "initialize transmitter..." << endl;
   TXDCTL txdctl (0);
   txdctl.GRAN (true);
   txdctl.WTHRESH (1);
   csr.write_TXDCTL (txdctl);

   TCTL tctl (0);
   tctl.CT (16);
   tctl.COLD (0x3F);
   tctl.PSP (true);
   tctl.EN (true);
   csr.write_TCTL (tctl);

   cout.flush();
   cout <<  "TCTL: " << csr.read_TCTL () << endl;
   cout <<  "TXDCTL: " << csr.read_TXDCTL () << endl;
   cout << "setup transmit descript table..." << endl;
   cout << "sizeof(tx_desc_t): " << sizeof(tx_desc_t) << endl;
   cout.flush();
   struct tx_desc_t *tx_desc = static_cast<struct tx_desc_t *>(memalign (PAGE_SIZE, PAGE_SIZE));
   uint64_t tx_desc_machine_address = virtual_pointer_to_machine_address(tx_desc);
   Hypercall::update_va_mapping_nocache (pointer_to_address (tx_desc), tx_desc_machine_address);
   csr.write_TDBA (tx_desc_machine_address);
   csr.write_TDLEN (256);
   cout << "TDBA: " << hex << csr.read_TDBA() << ", " << tx_desc_machine_address << endl;

   char *buffer = static_cast<char *>(memalign (PAGE_SIZE, PAGE_SIZE));
   uint64_t buffer_machine_address = virtual_pointer_to_machine_address(buffer);
   Hypercall::update_va_mapping_nocache (pointer_to_address (buffer), buffer_machine_address);

   // 00:24:be:45:0a:7d
   buffer [0] = 0x00;
   buffer [1] = 0x24;
   buffer [2] = 0xbe;
   buffer [3] = 0x45;
   buffer [4] = 0x0a;
   buffer [5] = 0x7d;

   buffer [6] = 0x00;
   buffer [7] = 0x01;
   buffer [8] = 0x02;
   buffer [9] = 0x03;
   buffer [10] = 0x04;
   buffer [11] = 0x05;

   buffer [12] = 0x90;
   buffer [13] = 0xcc;

   buffer [14] = 0x00;
   buffer [15] = 0x01;
   buffer [16] = 0x02;
   buffer [17] = 0x03;
   buffer [18] = 0x04;
   buffer [19] = 0x05;
   buffer [20] = 0x06;
   buffer [21] = 0x07;
   buffer [22] = 0x08;
   buffer [23] = 0x09;
   buffer [24] = 0x0a;
   buffer [25] = 0x0b;
   buffer [26] = 0x0c;
   buffer [27] = 0x0d;
   buffer [28] = 0x0e;
   buffer [29] = 0x0f;
   buffer [30] = 0x10;
   buffer [31] = 0x11;
   buffer [32] = 0x12;
   buffer [33] = 0x13;
   buffer [34] = 0x14;
   buffer [35] = 0x15;
   buffer [36] = 0x16;
   buffer [37] = 0x17;
   buffer [38] = 0x18;
   buffer [39] = 0x19;
   buffer [40] = 0x1a;
   buffer [41] = 0x1b;
   buffer [42] = 0x1c;
   buffer [43] = 0x1d;
   buffer [44] = 0x1e;
   buffer [45] = 0x1f;
   buffer [46] = 0x20;
   buffer [47] = 0x21;
   buffer [48] = 0x22;
   buffer [49] = 0x23;
   buffer [50] = 0x24;
   buffer [51] = 0x25;
   buffer [52] = 0x26;
   buffer [53] = 0x27;
   buffer [54] = 0x28;
   buffer [55] = 0x29;
   buffer [56] = 0x2a;
   buffer [57] = 0x2b;
   buffer [58] = 0x2c;
   buffer [59] = 0x2d;

   buffer [60] = 0x00;
   buffer [61] = 0x00;
   buffer [62] = 0x00;
   buffer [63] = 0x00;

   tx_desc->buffer = buffer_machine_address;
   tx_desc->length = 60;
   tx_desc->CSO = 0;
   tx_desc->CMD = 0x0B;
   tx_desc->STA = 0;
   tx_desc->CSS = 0;
   tx_desc->VLAN = 0;

   cout << "buffer is ready to send, incrementing tail now..." << endl;
   cout << "TDH: " << csr.read_TDH () << endl;
   cout << "TDT: " << csr.read_TDT () << endl;
   csr.write_TDT (1);

   cout << "waiting 2 sec..." << endl;
   sleep (2);
   cout << "TDH: " << csr.read_TDH () << endl;
   cout << "TDT: " << csr.read_TDT () << endl;
   cout << "tx_desc->STA: " << static_cast<unsigned int>(tx_desc->STA) << endl;

   cout << "waiting 5 sec, then exit..." << endl;
   cout.flush ();
   sleep (5);

   return 0;
}

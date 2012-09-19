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
#include <string.h>
#include <cstdint>

#include <iostream>
#include <queue>

#include <llamaos/api/pci/BAR.h>
#include <llamaos/api/pci/Command.h>
#include <llamaos/api/pci/PCI.h>
#include <llamaos/api/pci/Status.h>
#include <llamaos/api/sleep.h>
#include <llamaos/memory/Memory.h>
#include <llamaos/net/i82574/CSR.h>
#include <llamaos/net/i82574/CTRL.h>
#include <llamaos/net/i82574/EXTCNF_CTRL.h>
#include <llamaos/net/i82574/STATUS.h>
#include <llamaos/net/llamaNET.h>
#include <llamaos/xen/Hypervisor.h>
#include <llamaos/llamaOS.h>

using namespace std;
using namespace llamaos;
using namespace llamaos::api;
using namespace llamaos::api::pci;
using namespace llamaos::memory;
using namespace llamaos::net::i82574;
using namespace llamaos::net::llamanet;

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

struct buffer_entry
{
   unsigned char *pointer;
   uint64_t address;
};

int main (int /* argc */, char ** /* argv [] */)
{
   cout << "running 82574 llamaNET domain...\n" << endl;
   cout << "waiting..." << endl;
   sleep (3);

   PCI pci;
   sleep (1);
   cout << "PCI config:" << endl;
//   cout << pci << endl;

   sleep (1);
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
   cout << "PCI hardware detected is 82574" << endl;
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
   cout << "Writing " << hex << static_cast<uint16_t>(config_command) << endl;
   pci.write_config_word (4, config_command);

   config_command = pci.read_config_word (4);
   config_status =  pci.read_config_word (6);
   cout << config_command << config_status << endl;

   BAR bar0 = pci.read_config_dword (16);
   cout << bar0 << endl;

   uint64_t machine_address = bar0.Address ();

   uint64_t virtual_address = get_reserved_virtual_address (1);

   cout << "mapping 128K at:" << endl;
   cout << "  machine address: " << machine_address << endl;
   cout << "  virtual address: " << virtual_address << endl;

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

   sleep (1);

   cout << "masking interrupts..." << endl;
   cout << csr.read_IMS () << endl;
   csr.write_IMC(IMC::ALL);
   cout << csr.read_IMS () << endl;

   status = csr.read_STATUS ();
   cout << "CSR STATUS: " << hex << status << endl;

   CTRL_EXT ctrl_ext = csr.read_CTRL_EXT ();
   cout << "CSR CTRL_EXT: " << hex << ctrl_ext << endl;
   ctrl_ext.SPD_BYPS (true);
   ctrl_ext.DRV_LOAD(true);
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

   sleep (1);

   status = csr.read_STATUS ();
   cout << "CSR STATUS: " << hex << status << endl;

   sleep (2);

   cout << "setting link up..." << endl;
   ctrl.SLU (true);
   csr.write_CTRL (ctrl);

   sleep (1);

   status = csr.read_STATUS ();
   cout << "CSR STATUS: " << hex << status << endl;

   // from manual 4.6.2: "GCR bit 22 should be set to 1b by software during initialization."
   GCR gcr = csr.read_GCR ();
   gcr.INITIALIZE (true);
   csr.write_GCR (gcr);
   uint32_t gcr2 = csr.read (0x05B64);
   gcr2 |= 1;
   csr.write (0x05B64, gcr2);

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

   cout << "initialize receiver..." << endl;
   RXDCTL rxdctl (0);
   rxdctl.GRAN (true);
   rxdctl.WTHRESH (1);
   csr.write_RXDCTL (rxdctl);

   cout << "enabling receiver..." << endl;
   RCTL rctl (0);
   rctl.MPE(true);
   rctl.UPE(true);
   rctl.BAM(true);
   rctl.EN (true);
   csr.write_RCTL (rctl);

   cout << "create transmit descriptors..." << endl;

   struct tx_desc_t *tx_desc = static_cast<struct tx_desc_t *>(memalign (PAGE_SIZE, PAGE_SIZE));
   memset(tx_desc, 0, PAGE_SIZE);
   uint64_t tx_desc_machine_address = virtual_pointer_to_machine_address(tx_desc);
   Hypercall::update_va_mapping_nocache (pointer_to_address (tx_desc), tx_desc_machine_address);

   csr.write_TDBA (tx_desc_machine_address);
//   csr.write_TDLEN (1024);    // 64 descriptors
   csr.write_TDLEN (128);       // 8 descriptors
   cout << "TDBA: " << hex << csr.read_TDBA() << ", " << tx_desc_machine_address << endl;

   buffer_entry tx_buffers [8];
   queue<buffer_entry> tx_hw;
   queue<buffer_entry> tx_sw;

   for (unsigned int i = 0; i < 8; i++)
   {
      tx_buffers [i].pointer = static_cast<unsigned char *>(memalign (PAGE_SIZE, PAGE_SIZE));
      tx_buffers [i].address = virtual_pointer_to_machine_address(tx_buffers [i].pointer);
      Hypercall::update_va_mapping_nocache (pointer_to_address (tx_buffers [i].pointer), tx_buffers [i].address);

      tx_sw.push(tx_buffers [i]);
   }

   unsigned int tx_head = 0;
   unsigned int tx_tail = 0;

   cout << "create receiver descriptors..." << endl;

   struct rx_desc_t *rx_desc = static_cast<struct rx_desc_t *>(memalign (PAGE_SIZE, PAGE_SIZE));
   memset(rx_desc, 0, PAGE_SIZE);
   uint64_t rx_desc_machine_address = virtual_pointer_to_machine_address(rx_desc);
   Hypercall::update_va_mapping_nocache (pointer_to_address (rx_desc), rx_desc_machine_address);

   csr.write_RDBA (rx_desc_machine_address);
//   csr.write_RDLEN (1024);    // 64 descriptors
   csr.write_RDLEN (128);       // 8 descriptors
   cout << "RDBA: " << hex << csr.read_RDBA() << ", " << rx_desc_machine_address << endl;

   buffer_entry rx_buffers [8];
   queue<buffer_entry> rx_hw;

   for (unsigned int i = 0; i < 8; i++)
   {
      rx_buffers [i].pointer = static_cast<unsigned char *>(memalign (PAGE_SIZE, PAGE_SIZE));
      rx_buffers [i].address = virtual_pointer_to_machine_address(rx_buffers [i].pointer);
      Hypercall::update_va_mapping_nocache (pointer_to_address (rx_buffers [i].pointer), rx_buffers [i].address);

      rx_desc [i].buffer = rx_buffers [i].address;
      rx_desc [i].status = 0;
      rx_hw.push(rx_buffers [i]);
   }

   uint16_t rx_head = 0;
   uint16_t rx_tail = 8;
   csr.write_RDT (rx_tail);

   // create memory for the interface page
   llamaNET_interface *llamaNET = static_cast<llamaNET_interface *>(memalign (PAGE_SIZE, PAGE_SIZE));
   memset(llamaNET, 0, PAGE_SIZE);

   // allow access to the interface
   domid_t self_id = Hypervisor::get_instance ()->xenstore.read<domid_t>("domid");
   cout << "self_id: " << self_id << endl;
   grant_ref_t llamaNET_ref = Hypervisor::get_instance ()->grant_table.grant_access (self_id+1, llamaNET);
   cout << "llamaNET_ref: " << dec << llamaNET_ref << endl;

   llamaNET->app [0].rx_head = 0;
   llamaNET->app [0].rx_tail = 0;
   llamaNET->app [0].tx_head = 0;
   llamaNET->app [0].tx_tail = 0;

   // allow tx_buffer guest access
//   unsigned char *app_tx_buffer[8];

//   for (int i = 0; i < 8; i++)
//   {
//      app_tx_buffer [i] = static_cast<unsigned char *>(memalign (PAGE_SIZE, PAGE_SIZE));
//      cout << "mapping app_tx_buffer [" << dec << i << "]: " << dec << Hypervisor::get_instance ()->grant_table.grant_access (self_id+1, app_tx_buffer [i]) << endl;
//   }
   for (int i = 0; i < 8; i++)
   {
      cout << "mapping tx_buffers [" << dec << i << "]: " << dec << Hypervisor::get_instance ()->grant_table.grant_access (self_id+1, tx_buffers [i].pointer) << endl;
   }

   // allow rx_buffer guest access
//   unsigned char *app_rx_buffer[8];

//   for (int i = 0; i < 8; i++)
//   {
//      app_rx_buffer [i] = static_cast<unsigned char *>(memalign (PAGE_SIZE, PAGE_SIZE));
//      cout << "mapping app_rx_buffer [" << dec << i << "]: " << dec << Hypervisor::get_instance ()->grant_table.grant_access (self_id+1, app_rx_buffer [i]) << endl;
//   }
   for (int i = 0; i < 8; i++)
   {
      cout << "mapping rx_buffers [" << dec << i << "]: " << dec << Hypervisor::get_instance ()->grant_table.grant_access (self_id+1, rx_buffers [i].pointer) << endl;
   }

   llamaNET->driver.online = true;

   cout << "sizeof(HEADER_LENGTH): " << HEADER_LENGTH << endl;
   cout << "starting forever loop..." << endl;

   for (;;)
   {
      if (rx_head != csr.read_RDH())
      {
         buffer_entry rx_buffer = rx_hw.front();
         rx_hw.pop ();

//         if (   (rx_buffer.pointer [12] == 0x09)
//             && (rx_buffer.pointer [13] == 0x0C))
//         {
            // this is a llamaNET packet
            // for now just forward it into the hard coded guest self+1
//            Protocol_header *header = reinterpret_cast<Protocol_header *>(&rx_buffer.pointer [14]);

//            memcpy (app_rx_buffer [llamaNET->app [0].rx_head], header, HEADER_LENGTH + header->len);

   // ensure write is processed
//   wmb();
            unsigned int head = llamaNET->app [0].rx_head;
            head++;
            head %= 8;
            llamaNET->app [0].rx_head = head;
//         }

         rx_head++;
         rx_head %= 8;

         rx_desc [rx_tail].buffer = rx_buffer.address;
         rx_desc [rx_tail].checksum = 0;
         rx_desc [rx_tail].error = 0;
         rx_desc [rx_tail].length = 0;
         rx_desc [rx_tail].status = 0;
         rx_desc [rx_tail].vlan = 0;
         rx_hw.push(rx_buffer);
         rx_tail++;
         rx_tail %= 8;
         csr.write_RDT (rx_tail);
      }
      else if (llamaNET->app [0].tx_head != llamaNET->app [0].tx_tail)
      {
         buffer_entry tx_buffer = tx_sw.front();
         tx_sw.pop ();
         tx_hw.push(tx_buffer);

//         Protocol_header *header = reinterpret_cast<Protocol_header *>(app_tx_buffer [llamaNET->app [0].tx_tail]);
         Protocol_header *header = reinterpret_cast<Protocol_header *>(tx_buffers [llamaNET->app [0].tx_tail].pointer + 14);
   // ensure write is processed
//   rmb();

         // leave driver is app is done
         if (header->type == 0xDEAD)
         {
            break;
         }

// !BAM get these in a config soon
// dalai node 0 mac 00-1b-21-d5-66-ef
// redpj node 1 mac 68-05-ca-01-f7-db
         if (header->dest == 1)
         {
            // redpj
            tx_buffer.pointer [0] = 0x00;
            tx_buffer.pointer [1] = 0x1b;
            tx_buffer.pointer [2] = 0x21;
            tx_buffer.pointer [3] = 0xd5;
            tx_buffer.pointer [4] = 0x66;
            tx_buffer.pointer [5] = 0xef;
            tx_buffer.pointer [6] = 0x68;
            tx_buffer.pointer [7] = 0x05;
            tx_buffer.pointer [8] = 0xca;
            tx_buffer.pointer [9] = 0x01;
            tx_buffer.pointer [10] = 0xf7;
            tx_buffer.pointer [11] = 0xdb;
         }
         else
         {
            // dalai
            tx_buffer.pointer [0] = 0x68;
            tx_buffer.pointer [1] = 0x05;
            tx_buffer.pointer [2] = 0xca;
            tx_buffer.pointer [3] = 0x01;
            tx_buffer.pointer [4] = 0xf7;
            tx_buffer.pointer [5] = 0xdb;
            tx_buffer.pointer [6] = 0x00;
            tx_buffer.pointer [7] = 0x1b;
            tx_buffer.pointer [8] = 0x21;
            tx_buffer.pointer [9] = 0xd5;
            tx_buffer.pointer [10] = 0x66;
            tx_buffer.pointer [11] = 0xef;
         }

         tx_buffer.pointer [12] = 0x09;
         tx_buffer.pointer [13] = 0x0c;

//         memcpy (&tx_buffer.pointer [14], (void *)header, HEADER_LENGTH + header->len);

         unsigned int tail = llamaNET->app [0].tx_tail;
         tail++;
         tail %= 8;
         llamaNET->app [0].tx_tail = tail;

         tx_desc [tx_tail].buffer = tx_buffer.address;
         tx_desc [tx_tail].length = 14 + HEADER_LENGTH + header->len;
         tx_desc [tx_tail].CSO = 0;
         tx_desc [tx_tail].CMD = 0x0B;
         tx_desc [tx_tail].STA = 0;
         tx_desc [tx_tail].CSS = 0;
         tx_desc [tx_tail].VLAN = 0;

         tx_tail++;
         tx_tail %= 8;
         csr.write_TDT (tx_tail);
      }
      else
      {
         // cleanup tx while waiting
         if (tx_head != csr.read_TDH())
         {
            tx_sw.push(tx_hw.front());
            tx_hw.pop();
            tx_head++;
            tx_head %= 8;
         }
      }
   }

   cout << "waiting 5 sec, then exit..." << endl;
   cout.flush ();
   sleep (5);

   return 0;
}

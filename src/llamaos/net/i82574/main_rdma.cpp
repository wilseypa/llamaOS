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

#include <llamaos/api/io.h>
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

static inline unsigned int rx_desc_index (unsigned int index)
{
   if (index < 256)
   {
      return index + 768;
   }
   else if (index < 512)
   {
      return index + 256;
   }
   else if (index < 768)
   {
      return index - 256;
   }

   return index - 768;
}

#if 1
static inline unsigned int tx_desc_index (unsigned int index)
{
   if (index < 256)
   {
      return index + 512;
   }
   else if (index < 512)
   {
      return index;
   }

   return index - 512;
}
#else
static inline unsigned int tx_desc_index (unsigned int index)
{
   return index;
//   if (index < 256)
//   {
//     return index + 256;
//   }
//
//   return index - 256;
}
#endif

int main (int /* argc */, char ** /* argv [] */)
{
   bool hw_is_82574 = false;

   cout << "running 82574 llamaNET domain...\n" << endl;
   PCI pci;
   sleep (1);
   cout << "PCI config:" << endl;
   cout << pci << endl;

   cout << "checking PCI config for valid 82574..." << endl;
   uint16_t vendor_id = pci.read_config_word (0);
   uint16_t device_id = pci.read_config_word (2);
   uint32_t class_code = (pci.read_config_byte (11) << 16) | (pci.read_config_byte (10) << 8) | pci.read_config_byte(9);
   uint16_t subvendor_id = pci.read_config_word (44);

   if (   (vendor_id == 0x8086)
       && (device_id == 0x10D3)
       && (class_code == 0x020000)
       && (subvendor_id == 0x8086))
   {
      cout << "PCI hardware detected is 82574" << endl;
      hw_is_82574 = true;
   }
   else if (   (vendor_id == 0x8086)
            && (device_id == 0x1096)
            && (class_code == 0x020000))
   {
      cout << "PCI hardware detected is 80003es2lan" << endl;
   }
   else
   {
      cout << "PCI hardware detected is NOT supported by this driver." << endl;
      cout << hex << "   vendor: " << vendor_id << endl;
      cout << hex << "   devide: " << device_id << endl;
      cout << hex << "    class: " << class_code << endl;
      cout << hex << "subvendor: " << subvendor_id << endl << endl;

      cout << "waiting 3 sec, then exit..." << endl;
      cout.flush ();
      sleep (3);
      return -1;
   }

   cout << "enabling PCI access and creating CSR register class..." << endl;
   cout.flush ();

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

   uint32_t RAL = csr.read (0x5400);
   uint32_t RAH = csr.read (0x5404);

   cout << endl;
   cout << "RAL " << hex << RAL << endl;
   cout << "RAH " << hex << RAH << endl;
   cout << endl;

   uint8_t mac_addr [6];
   mac_addr [0] = ((RAL >> 0) & 0xFF);
   mac_addr [1] = ((RAL >> 8) & 0xFF);
   mac_addr [2] = ((RAL >> 16) & 0xFF);
   mac_addr [3] = ((RAL >> 24) & 0xFF);
   mac_addr [4] = ((RAH >> 0) & 0xFF);
   mac_addr [5] = ((RAH >> 8) & 0xFF);

   cout << "MAC address: " << hex << static_cast<int>(mac_addr [0])
                           << ":" << static_cast<int>(mac_addr [1])
                           << ":" << static_cast<int>(mac_addr [2])
                           << ":" << static_cast<int>(mac_addr [3])
                           << ":" << static_cast<int>(mac_addr [4])
                           << ":" << static_cast<int>(mac_addr [5]) << endl << endl; 

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

   if (hw_is_82574)
   {
      EXTCNF_CTRL extcnf_ctrl = csr.read_EXTCNF_CTRL ();
      cout << "getting hw semaphore..." << extcnf_ctrl << endl;
   // !BAM
   // is the "=-" a typo
   //   extcnf_ctrl =- EXTCNF_CTRL(0);
      extcnf_ctrl = EXTCNF_CTRL(0);
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
   }
   else
   {
      SWSM swsm = csr.read_SWSM ();
      cout << "getting hw semaphore..." << swsm << endl;

      while (!(swsm.SWESMBI()))
      {
         swsm.SWESMBI(true);
         csr.write_SWSM(swsm);

         sleep (1);

         swsm = csr.read_SWSM ();
         cout << "getting hw semaphore..." << swsm << endl;
         break;
      }
   }

   cout << "reseting..." << endl;
   ctrl.RST(true);
   ctrl.PHY_RST(true);
   csr.write_CTRL(ctrl);

//   sleep (1);

   cout << "masking interrupts..." << endl;
   cout << csr.read_IMS () << endl;
   csr.write_IMC(IMC::ALL);
   cout << csr.read_IMS () << endl;

   status = csr.read_STATUS ();
   cout << "CSR STATUS: " << hex << status << endl;

   CTRL_EXT ctrl_ext = csr.read_CTRL_EXT ();
   cout << "CSR CTRL_EXT: " << hex << ctrl_ext << endl;
   ctrl_ext.SPD_BYPS (true);
   ctrl_ext.PHY_PDE(false);
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

   // enable flow control, make false to disable
   ctrl.RFCE(true);
   ctrl.TFCE(true);

   csr.write_CTRL (ctrl);

   // flow control header
   csr.write (0x28, 0x00C28001);
   csr.write (0x2c, 0x0100);
   csr.write (0x30, 0x8808);

   // transmit timer value in 512 nanoseconds units
   csr.write (0x170, 100);
   csr.write (0x5f40, 50);

   // high threshold out of 20KB or 0x5000
   csr.write(0x2160, 0x4000|0x80000000);  // 0x4800|0x80000000);
   csr.write(0x2168, 0x2000);
//   sleep (1);

   status = csr.read_STATUS ();
   cout << "CSR STATUS: " << hex << status << endl;

   cout << "setting link up..." << endl;
   ctrl = csr.read_CTRL();
   cout << ctrl << endl;
   ctrl.SLU (true);
   csr.write_CTRL (ctrl);

   status = csr.read_STATUS ();
   cout << "CSR STATUS: " << hex << status << endl;
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
   txdctl.HTHRESH (1);
   txdctl.PTHRESH (31);
   csr.write_TXDCTL (txdctl);

   TCTL tctl (0);
   tctl.CT (16);
   tctl.COLD (0x3F);
   tctl.PSP (true);
   tctl.EN (true);
   tctl.PBE(true);
   tctl.MULR(true);
   tctl.RRTHRESH(TCTL::THREASHOLD_4_LINES);
   csr.write_TCTL (tctl);

   cout << "initialize receiver..." << endl;
   RXDCTL rxdctl (0);
   rxdctl.GRAN (true);
   rxdctl.WTHRESH (4);
   rxdctl.HTHRESH (4);
   rxdctl.PTHRESH (20);
   csr.write_RXDCTL (rxdctl);

   cout << "enabling receiver..." << endl;
   cout << csr.read_RCTL() << endl;

   RCTL rctl (0);
   rctl.MPE(true);
   rctl.UPE(true);
   rctl.BAM(true);
   rctl.EN (true);
   rctl.LPE(true);
   rctl.BSIZE(RCTL::BYTES_256);
   rctl.BSEX(true);
   csr.write_RCTL (rctl);

   cout << csr.read_RCTL() << endl;

   cout << "create transmit descriptors..." << endl;

   const unsigned int tx_desc_size = 3 * PAGE_SIZE;
   const unsigned int tx_desc_max = tx_desc_size / 16;

   struct tx_desc_t *tx_desc = static_cast<struct tx_desc_t *>(memalign (PAGE_SIZE, tx_desc_size));
   memset(tx_desc, 0, tx_desc_size);

//   uint64_t tx_desc_machine_address = virtual_pointer_to_machine_address(tx_desc);
   Hypercall::update_va_mapping_nocache (pointer_to_address (tx_desc), virtual_pointer_to_machine_address(tx_desc));
//   Hypercall::update_va_mapping_nocache (pointer_to_address (tx_desc+256), virtual_pointer_to_machine_address(tx_desc+256));
   Hypercall::update_va_mapping_nocache (pointer_to_address (tx_desc+256+256), virtual_pointer_to_machine_address(tx_desc+256+256));
//   Hypercall::update_va_mapping_nocache (pointer_to_address (tx_desc+256+256+256), virtual_pointer_to_machine_address(tx_desc+256+256+256));

//   csr.write_TDBA (virtual_pointer_to_machine_address(tx_desc+256+256+256));
   csr.write_TDBA (virtual_pointer_to_machine_address(tx_desc+256+256));
//   csr.write_TDBA (virtual_pointer_to_machine_address(tx_desc+256));
//   csr.write_TDBA (virtual_pointer_to_machine_address(tx_desc));
   csr.write_TDLEN (tx_desc_size);

   cout << "TDBA: " << hex << csr.read_TDBA() << ", " << virtual_pointer_to_machine_address(tx_desc+256+256) << endl;
//   cout << "TDBA: " << hex << csr.read_TDBA() << ", " << virtual_pointer_to_machine_address(tx_desc+256) << endl;
//   cout << "TDBA: " << hex << csr.read_TDBA() << ", " << virtual_pointer_to_machine_address(tx_desc) << endl;
   cout << "TDLEN: " << hex << csr.read_TDLEN() << endl;

   buffer_entry tx_buffers [TX_BUFFERS];
   queue<buffer_entry> tx_hw;
   queue<buffer_entry> tx_sw;

   for (unsigned int i = 0; i < TX_BUFFERS; i++)
   {
      tx_buffers [i].pointer = static_cast<unsigned char *>(memalign (PAGE_SIZE, PAGE_SIZE));
      tx_buffers [i].address = virtual_pointer_to_machine_address(tx_buffers [i].pointer);
      Hypercall::update_va_mapping_nocache (pointer_to_address (tx_buffers [i].pointer), tx_buffers [i].address);

      tx_sw.push(tx_buffers [i]);
   }

//   unsigned int tx_head = 0;
   unsigned int tx_tail = 0;

   cout << "create receiver descriptors..." << endl;

   const unsigned int rx_desc_size = 4 * PAGE_SIZE;
   const unsigned int rx_desc_max = rx_desc_size / 16;

   struct rx_desc_t *rx_desc = static_cast<struct rx_desc_t *>(memalign (PAGE_SIZE, rx_desc_size));
   memset(rx_desc, 0, rx_desc_size);

//   uint64_t rx_desc_machine_address = virtual_pointer_to_machine_address(rx_desc);
   Hypercall::update_va_mapping_nocache (pointer_to_address (rx_desc), virtual_pointer_to_machine_address(rx_desc));
   Hypercall::update_va_mapping_nocache (pointer_to_address (rx_desc+256), virtual_pointer_to_machine_address(rx_desc+256));
   Hypercall::update_va_mapping_nocache (pointer_to_address (rx_desc+256+256), virtual_pointer_to_machine_address(rx_desc+256+256));
   Hypercall::update_va_mapping_nocache (pointer_to_address (rx_desc+256+256+256), virtual_pointer_to_machine_address(rx_desc+256+256+256));

   csr.write_RDBA (virtual_pointer_to_machine_address(rx_desc+256+256+256));
   csr.write_RDLEN (rx_desc_size);

   cout << "RDBA: " << hex << csr.read_RDBA() << ", " << virtual_pointer_to_machine_address(rx_desc+256+256+256) << endl;
   cout << "RDLEN: " << hex << csr.read_RDLEN() << endl;

   buffer_entry rx_buffers [RX_BUFFERS];
   queue<buffer_entry> rx_hw;
   queue<buffer_entry> rx_sw;

   uint16_t rx_head = csr.read_RDH ();
   uint16_t rx_tail = rx_head;
   unsigned int rx_buffer_filled = 0;

   for (unsigned int i = 0; i < RX_BUFFERS; i++)
   {
      rx_buffers [i].pointer = static_cast<unsigned char *>(memalign (PAGE_SIZE, PAGE_SIZE));
      rx_buffers [i].address = virtual_pointer_to_machine_address(rx_buffers [i].pointer);
      Hypercall::update_va_mapping_nocache (pointer_to_address (rx_buffers [i].pointer), rx_buffers [i].address);

      if (i < (rx_desc_max - 2))  // !BAM HARDWARE CONSIDERS FULL TO BE 2 OFF INSTEAD OF 1. SUPPORT FOR EXTENDED FRAMES DESCS.
      {
         rx_desc [rx_desc_index(rx_tail)].buffer = rx_buffers [i].address;
         rx_desc [rx_desc_index(rx_tail)].status = 0;
         rx_hw.push(rx_buffers [i]);
         rx_tail++;
         rx_buffer_filled++;
      }
      else
      {
         rx_sw.push(rx_buffers [i]);
      }
   }

   csr.write_RDT (rx_tail);

   // create memory for the control page
   net::llamaNET::Control *llamaNET_control = static_cast<net::llamaNET::Control *>(memalign (PAGE_SIZE, PAGE_SIZE));
   memset(static_cast<void *>(llamaNET_control), 0, PAGE_SIZE);

   // allow access to the interface
   domid_t self_id = Hypervisor::get_instance ()->domid;
   cout << "self_id: " << self_id << endl;
   grant_ref_t llamaNET_ref = Hypervisor::get_instance ()->grant_table.grant_access (self_id+1, llamaNET_control);
   llamaNET_ref = Hypervisor::get_instance ()->grant_table.grant_access (self_id+2, llamaNET_control);
   llamaNET_ref = Hypervisor::get_instance ()->grant_table.grant_access (self_id+3, llamaNET_control);
   llamaNET_ref = Hypervisor::get_instance ()->grant_table.grant_access (self_id+4, llamaNET_control);
   llamaNET_ref = Hypervisor::get_instance ()->grant_table.grant_access (self_id+5, llamaNET_control);
   llamaNET_ref = Hypervisor::get_instance ()->grant_table.grant_access (self_id+6, llamaNET_control);
   cout << "llamaNET_ref after mapping Control[]: " << dec << llamaNET_ref << endl;

   grant_ref_t *tx_refs [6];
   grant_ref_t *rx_refs [6];

   for (int i = 0; i < 6; i++)
   {
      tx_refs [i] = static_cast<grant_ref_t *>(memalign (PAGE_SIZE, PAGE_SIZE));
      memset(static_cast<void *>(tx_refs [i]), 0, PAGE_SIZE);

      llamaNET_ref = Hypervisor::get_instance ()->grant_table.grant_access (self_id + 1 + i, tx_refs [i]);
   }
   cout << "llamaNET_ref after mapping tx_refs[]: " << dec << llamaNET_ref << endl;

   for (int i = 0; i < 6; i++)
   {
      rx_refs [i] = static_cast<grant_ref_t *>(memalign (PAGE_SIZE, PAGE_SIZE));
      memset(static_cast<void *>(rx_refs [i]), 0, PAGE_SIZE);

      llamaNET_ref = Hypervisor::get_instance ()->grant_table.grant_access (self_id + 1 + i, rx_refs [i]);
   }
   cout << "llamaNET_ref after mapping rx_refs[]: " << dec << llamaNET_ref << endl;

   // allow tx_buffer guest access
   for (unsigned int i = 0; i < TX_BUFFERS; i++)
   {
      for (int j = 0; j < 6; j++)
      {
         grant_ref_t *tx_ref = tx_refs [j];
         llamaNET_ref = Hypervisor::get_instance ()->grant_table.grant_access (self_id + 1 + j, tx_buffers [i].pointer);
         tx_ref [i] = llamaNET_ref;
      }
   }
   cout << "llamaNET_ref after mapping tx_buffers: " << dec << llamaNET_ref << endl;

   // allow rx_buffer guest access
   for (unsigned int i = 0; i < RX_BUFFERS; i++)
   {
      for (int j = 0; j < 6; j++)
      {
         grant_ref_t *rx_ref = rx_refs [j];
         llamaNET_ref = Hypervisor::get_instance ()->grant_table.grant_access (self_id + 1 + j, rx_buffers [i].pointer);
         rx_ref [i] = llamaNET_ref;
      }
   }
   cout << "llamaNET_ref after mapping rx_buffers: " << dec << llamaNET_ref << endl;

   llamaNET_control->driver.online = true;
   cout << "starting forever loop..." << endl;

   int cleanup_delay = 0;
   unsigned int head = 0;

   queue<unsigned int> tx_indexes;

   uint16_t rx_tail_global = 0;

   unsigned int send_delay = 0;

   unsigned int rx_count = 0;
   unsigned int tx_tail2 = 0;

//   int stat_delay = 10000;

   cout << "program break: " << (pointer_to_address(get_program_break ()) / 1024.0) / 1024.0 << endl;
   for (;;)
   {
      if (rx_desc [rx_desc_index(rx_head)].status != 0)
      {
//cout << "recv'ed " << rx_head << endl;
         buffer_entry entry;
         entry.address = rx_desc [rx_desc_index(rx_head)].buffer;
         rx_sw.push (entry);

         rx_head++;
         rx_head %= rx_desc_max;

         rx_count++;
         continue;
      }

      if (rx_count > 0)
      {
         head = llamaNET_control->driver.rx_head;
         head += rx_count;
         head %= RX_BUFFERS;
         llamaNET_control->driver.rx_head = head;
         rx_buffer_filled -= rx_count;
         if (rx_buffer_filled < 16)
         {
            cout << "rx buffer low: " << rx_buffer_filled << endl;
         }
//if (rx_count > 2) cout << "rx_count is " << rx_count << endl;
         rx_count = 0;
      }

      if (++send_delay > 0)
      {
         send_delay = 0;

         uint64_t tx_next_index = llamaNET_control->driver.tx_next_index;
         uint64_t tx_last_index = llamaNET_control->driver.tx_last_index;

         if (tx_next_index != tx_last_index)
         {
//cout << "sending..." << endl;         
            uint32_t tx_mask = 0;
            uint32_t tx_count = 0;

            for (uint32_t i = (tx_last_index % 32); i < 32; i++)
            {
//cout << "  sending index " << tx_last_index + tx_count << endl;         
               tx_mask |= (1 << i);
               tx_count++;

               if ((tx_last_index + tx_count) == tx_next_index)
               {
                  break;
               }
            }

            // !BAM can't do this!
            // tx_mask &= __sync_fetch_and_and(&llamaNET_control->driver.tx_mask [(tx_last_index % TX_BUFFERS) / 32], ~tx_mask);
            tx_mask = llamaNET_control->driver.tx_mask [(tx_last_index % TX_BUFFERS) / 32];

   //cout << "  sending tx_mask " << tx_mask << endl;         
   //cout << "  sending tx_count " << tx_count << endl;         
            tx_count = 0;
            for (uint32_t i = (tx_last_index % 32); i < 32; i++)
            {
               if (tx_mask & (1 << i))
               {
//cout << "  sending index " << tx_tail << endl;         
                  llamaos::net::llamaNET::Protocol_header *header =
                     reinterpret_cast<llamaos::net::llamaNET::Protocol_header *> (tx_buffers [(tx_last_index + tx_count) % TX_BUFFERS].pointer);

//                  if (   (header->eth_dest [0] != mac_addr [0])
//                      || (header->eth_dest [1] != mac_addr [1])
//                      || (header->eth_dest [2] != mac_addr [2])
//                      || (header->eth_dest [3] != mac_addr [3])
//                      || (header->eth_dest [4] != mac_addr [4])
//                      || (header->eth_dest [5] != mac_addr [5]))
                  {
                     tx_desc [tx_desc_index(tx_tail)].buffer = tx_buffers [(tx_last_index + tx_count) % TX_BUFFERS].address;
                     tx_desc [tx_desc_index(tx_tail)].length = llamaos::net::llamaNET::HEADER_LENGTH + header->len;
                     tx_desc [tx_desc_index(tx_tail)].CSO = 0;
                     tx_desc [tx_desc_index(tx_tail)].CMD = 0x0B;
                     tx_desc [tx_desc_index(tx_tail)].STA = 0;
                     tx_desc [tx_desc_index(tx_tail)].CSS = 0;
                     tx_desc [tx_desc_index(tx_tail)].VLAN = 0;

                     tx_tail++;
                     tx_tail %= tx_desc_max;

                     tx_tail2 = tx_tail + 1;
                     tx_tail2 %= tx_desc_max;
                     // holding for phys buffer space....
                     while (tx_desc [tx_desc_index(tx_tail2)].CMD == 0x0B && tx_desc [tx_desc_index(tx_tail2)].STA == 0);
//                  cout << "tx_tail " << tx_tail << " ready" << endl;
                  }

                  tx_count++;

                  __sync_fetch_and_and(&llamaNET_control->driver.tx_mask [(tx_last_index % TX_BUFFERS) / 32], ~(1 << i));
               }
               else
               {
   //               cout << "waiting for " << (tx_last_index + tx_count) % TX_BUFFERS << endl;
                  break;
               }
            }

            if (tx_count > 0)
            {
               wmb();
               csr.write_TDT (tx_tail);
//cout << "  next index " << tx_tail << endl;         
//if (tx_count > 2) cout << "tx_count is " << tx_count << endl;

               head = llamaNET_control->driver.tx_head;
               head += tx_count;
               head %= TX_BUFFERS;
               llamaNET_control->driver.tx_head = head;
//cout << "tx_head = " << llamaNET_control->driver.tx_head << endl;

               wmb();
               llamaNET_control->driver.tx_last_index += tx_count;
            }
         }
      }

      if (++cleanup_delay > 100)
      {
         cleanup_delay = 0;
#if 1
         if (llamaNET_control->driver.tx_last_index != llamaNET_control->driver.tx_done_index)
         {
            bool update = true;

            for (int i = 0; i < 6; i++)
            {
               if (   (llamaNET_control->app [i].online)
                  && ((llamaNET_control->driver.tx_done_index % TX_BUFFERS) == llamaNET_control->app [i].tx_tail))
               {
                  update = false;
                  break;
               }
            }

            if (update)
            {
               llamaNET_control->driver.tx_done_index++;
            }
         }

         bool write_rx_tail = false;
         bool move_rx_tail = false;

         while (rx_tail_global != llamaNET_control->driver.rx_head)
         {
            move_rx_tail = true;

            for (int i = 0; i < 6; i++)
            {
               if (   (llamaNET_control->app [i].online)
                   && (rx_tail_global == llamaNET_control->app [i].rx_tail))
               {
                  move_rx_tail = false;
                  break;
               }
            }

            if (move_rx_tail)
            {
               // !bam can't do this until all guest tail is updated
               buffer_entry entry;
               entry = rx_sw.front ();
               rx_sw.pop ();

      //         rx_desc [rx_tail].buffer = rx_desc [rx_head].buffer;
               rx_desc [rx_desc_index(rx_tail)].buffer = entry.address;
               rx_desc [rx_desc_index(rx_tail)].checksum = 0;
               rx_desc [rx_desc_index(rx_tail)].error = 0;
               rx_desc [rx_desc_index(rx_tail)].length = 0;
               rx_desc [rx_desc_index(rx_tail)].status = 0;
               rx_desc [rx_desc_index(rx_tail)].vlan = 0;
               rx_tail++;
               rx_tail %= rx_desc_max;
//cout << "inserted rx_tail " << rx_tail << endl;
//               csr.write_RDT (rx_tail);
               write_rx_tail = true;
      
               rx_tail_global++;
               rx_tail_global %= RX_BUFFERS;
               rx_buffer_filled++;
            }
            else
            {
               break;
            }
         }

         if (write_rx_tail)
         {
            csr.write_RDT (rx_tail);
         }
#endif
         if (llamaNET_control->close_driver)
         {
            cout << "close_driver is: " << llamaNET_control->close_driver << endl;
            // leave driver, app is done
            break;
         }
      }

//      if (++stat_delay > 10000)
//      {
//         stat_delay = 0;
//
//         cout << "Missed Packets Count = " << csr.read (0x4010) << endl;
//      }
   }

   cout << "waiting 3 sec, then exit..." << endl;
   cout.flush ();
   sleep (3);

   return 0;
}

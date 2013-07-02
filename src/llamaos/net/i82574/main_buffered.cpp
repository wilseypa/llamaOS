/*
Copyright (c) 2013, William Magato
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

static const unsigned int rx_desc_pages = 32;
static const unsigned int rx_desc_size = rx_desc_pages * PAGE_SIZE;
static const unsigned int rx_desc_max = rx_desc_size / sizeof(rx_desc_t);
static unsigned int rx_desc_xref [rx_desc_max];

const unsigned int tx_desc_pages = 4;
const unsigned int tx_desc_size = tx_desc_pages * PAGE_SIZE;
const unsigned int tx_desc_max = tx_desc_size / sizeof(tx_desc_t);
static unsigned int tx_desc_xref [tx_desc_max];

static void xref_init (unsigned int *xref, unsigned int max, unsigned int size)
{
   unsigned int delta = PAGE_SIZE / size;
   unsigned int offset = max - delta;

   for (unsigned int i = 0; i < max; i++)
   {
      xref [i] = i + offset;

      if (0 == ((i + 1) % delta))
      {
         offset -= (2 * delta);
      }
   }
}

int main (int /* argc */, char ** /* argv [] */)
{
   bool hw_is_82574 = false;

   xref_init (rx_desc_xref, rx_desc_max, sizeof(rx_desc_t));
   xref_init (tx_desc_xref, tx_desc_max, sizeof(tx_desc_t));

   cout << "running 82574 llamaNET domain...\n" << endl;
   PCI pci;
   sleep (1);
   cout << "PCI config:" << endl;
   cout << pci << endl;

   cout << "checking PCI config for valid 82574..." << endl;
   uint16_t vendor_id = pci.read_config_word (0);
   uint16_t device_id = pci.read_config_word (2);
   uint32_t class_code =   (pci.read_config_byte (11) << 16)
                         | (pci.read_config_byte (10) << 8)
                         | pci.read_config_byte(9);
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
      Hypercall::update_va_mapping_nocache (
               virtual_address + offset, machine_address + offset);
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
                           << ":" << static_cast<int>(mac_addr [5])
                           << endl << endl;

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
   csr.write (0x170, 50);
   csr.write (0x5f40, 50);

   // high threshold out of 20KB or 0x5000
   csr.write(0x2160, 0x4000|0x80000000);
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

   // from manual 4.6.2:
   // "GCR bit 22 should be set to 1b by software during initialization."
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

   // trying to get to contiguous region of heap
   // really need a function to reprogram the mmu
   char *dead_memory =
         static_cast<char *>(memalign (PAGE_SIZE, 4 * PAGE_SIZE));

   cout << "create transmit descriptors..." << endl;
   vector <tx_desc_t *> tx_noncontig;
   tx_desc_t *tx_desc;

   for (;;)
   {
      tx_desc = static_cast<tx_desc_t *>(memalign (PAGE_SIZE, tx_desc_size));

      bool failed = false;
      uint64_t address = virtual_pointer_to_machine_address (tx_desc);

      for (unsigned int i = 1; i < tx_desc_pages; i++)
      {
         uint64_t next_address =
               virtual_pointer_to_machine_address (tx_desc + (i * 256));

         if (next_address != (address - 0x1000))
         {
            cout << "alloc non-contiguous region, trying again..." << endl;
            tx_noncontig.push_back (tx_desc);
            failed = true;
            break;
         }

         address = next_address;
      }

      if (!failed)
      {
         break;
      }
   }

   for (size_t i = 0; i < tx_noncontig.size (); i++)
   {
      free (tx_noncontig [i]);
   }

   memset(tx_desc, 0, tx_desc_size);

   for (unsigned int i = 0; i < tx_desc_pages; i++)
   {
      Hypercall::update_va_mapping_nocache (
               pointer_to_address (tx_desc + (i * 256)),
               virtual_pointer_to_machine_address(tx_desc + (i * 256)));
      cout << "machine address: "
           << hex << virtual_pointer_to_machine_address(tx_desc + (i * 256))
           << endl;
   }

   csr.write_TDBA (
            virtual_pointer_to_machine_address (
               tx_desc + (tx_desc_pages - 1) * 256));
   csr.write_TDLEN (tx_desc_size);

   cout << "TDBA: " << hex << csr.read_TDBA() << endl;
   cout << "TDLEN: " << hex << csr.read_TDLEN() << endl;

   cout << "create receiver descriptors..." << endl;
//   struct rx_desc_t *rx_desc =
//         static_cast<struct rx_desc_t *>(memalign (PAGE_SIZE, rx_desc_size));

   vector <rx_desc_t *> rx_noncontig;
   rx_desc_t *rx_desc;

   for (;;)
   {
      rx_desc = static_cast<rx_desc_t *>(memalign (PAGE_SIZE, rx_desc_size));

      bool failed = false;
      uint64_t address = virtual_pointer_to_machine_address (rx_desc);

      for (unsigned int i = 1; i < rx_desc_pages; i++)
      {
         uint64_t next_address =
               virtual_pointer_to_machine_address (rx_desc + (i * 256));

         if (next_address != (address - 0x1000))
         {
            cout << "alloc non-contiguous region, trying again..." << endl;
            rx_noncontig.push_back (rx_desc);
            failed = true;
            break;
         }

         address = next_address;
      }

      if (!failed)
      {
         break;
      }
   }

   for (size_t i = 0; i < rx_noncontig.size (); i++)
   {
      free (rx_noncontig [i]);
   }

   memset(rx_desc, 0, rx_desc_size);

   for (unsigned int i = 0; i < rx_desc_pages; i++)
   {
      Hypercall::update_va_mapping_nocache (
               pointer_to_address (rx_desc + (i * 256)),
               virtual_pointer_to_machine_address(rx_desc + (i * 256)));
      cout << "machine address: "
           << hex << virtual_pointer_to_machine_address(rx_desc + (i * 256))
           << endl;
   }

   csr.write_RDBA (
            virtual_pointer_to_machine_address (
               rx_desc + (rx_desc_pages - 1) * 256));
   csr.write_RDLEN (rx_desc_size);

   cout << "RDBA: " << hex << csr.read_RDBA() << endl;
   cout << "RDLEN: " << hex << csr.read_RDLEN() << endl;

   buffer_entry rx_hardware_buffers [rx_desc_max];

   for (unsigned int i = 0; i < rx_desc_max; i++)
   {
      rx_hardware_buffers [i].pointer =
            static_cast<unsigned char *>(memalign (PAGE_SIZE, PAGE_SIZE));
      rx_hardware_buffers [i].address =
            virtual_pointer_to_machine_address(rx_hardware_buffers [i].pointer);

      rx_desc [rx_desc_xref [i]].buffer = rx_hardware_buffers [i].address;
      rx_desc [rx_desc_xref [i]].checksum = 0;
      rx_desc [rx_desc_xref [i]].error = 0;
      rx_desc [rx_desc_xref [i]].length = 0;
      rx_desc [rx_desc_xref [i]].status = 0;
      rx_desc [rx_desc_xref [i]].vlan = 0;

      Hypercall::update_va_mapping_nocache (
               pointer_to_address (rx_hardware_buffers [i].pointer),
                                   rx_hardware_buffers [i].address);
   }

   // !BAM HARDWARE CONSIDERS FULL TO BE 2 OFF INSTEAD OF 1.
   // SUPPORT FOR EXTENDED FRAMES DESCS.
   uint16_t rx_tail = (rx_desc_max - 2);
   csr.write_RDT (rx_tail);

   // create memory for the control page
   net::llamaNET::Control *llamaNET_control =
         static_cast<net::llamaNET::Control *>(memalign (PAGE_SIZE, PAGE_SIZE));
   memset(static_cast<void *>(llamaNET_control), 0, PAGE_SIZE);

   // allow access to the interface
   domid_t self_id = Hypervisor::get_instance ()->domid;
   cout << "self_id: " << self_id << endl;

   grant_ref_t llamaNET_ref;

   for (int i = 0; i < 6; i++)
   {
      llamaNET_ref = Hypervisor::get_instance ()->grant_table.grant_access (
                        self_id + 1 + i, llamaNET_control);
   }

   cout << "llamaNET_ref after mapping Control[]: "
        << dec << llamaNET_ref << endl;

   grant_ref_t *tx_refs [6];
   grant_ref_t *rx_refs [6];

   for (int i = 0; i < 6; i++)
   {
      tx_refs [i] = static_cast<grant_ref_t *>(memalign (PAGE_SIZE, PAGE_SIZE));
      memset(static_cast<void *>(tx_refs [i]), 0, PAGE_SIZE);

      llamaNET_ref = Hypervisor::get_instance ()->grant_table.grant_access (
                        self_id + 1 + i, tx_refs [i]);
   }
   cout << "llamaNET_ref after mapping tx_refs[]: "
        << dec << llamaNET_ref << endl;

   for (int i = 0; i < 6; i++)
   {
      rx_refs [i] = static_cast<grant_ref_t *>(memalign (PAGE_SIZE, PAGE_SIZE));
      memset(static_cast<void *>(rx_refs [i]), 0, PAGE_SIZE);

      llamaNET_ref = Hypervisor::get_instance ()->grant_table.grant_access (
                        self_id + 1 + i, rx_refs [i]);
   }
   cout << "llamaNET_ref after mapping rx_refs[]: "
        << dec << llamaNET_ref << endl;

   buffer_entry tx_buffers [TX_BUFFERS];

   // allow tx_buffer guest access
   for (unsigned int i = 0; i < TX_BUFFERS; i++)
   {
      tx_buffers [i].pointer =
            static_cast<unsigned char *>(memalign (PAGE_SIZE, PAGE_SIZE));
      tx_buffers [i].address =
            virtual_pointer_to_machine_address(tx_buffers [i].pointer);
      Hypercall::update_va_mapping_nocache (
               pointer_to_address (tx_buffers [i].pointer),
               tx_buffers [i].address);

      for (int j = 0; j < 6; j++)
      {
         grant_ref_t *tx_ref = tx_refs [j];
         llamaNET_ref = Hypervisor::get_instance ()->grant_table.grant_access (
                           self_id + 1 + j, tx_buffers [i].pointer);
         tx_ref [i] = llamaNET_ref;
      }
   }
   cout << "llamaNET_ref after mapping tx_buffers: "
        << dec << llamaNET_ref << endl;

   unsigned char *rx_shared_buffers [RX_BUFFERS];

   // allow rx_buffer guest access
   for (unsigned int i = 0; i < RX_BUFFERS; i++)
   {
      rx_shared_buffers [i] =
            static_cast<unsigned char *>(memalign (PAGE_SIZE, PAGE_SIZE));

      for (int j = 0; j < 6; j++)
      {
         grant_ref_t *rx_ref = rx_refs [j];
         llamaNET_ref = Hypervisor::get_instance ()->grant_table.grant_access (
                           self_id + 1 + j, rx_shared_buffers [i]);
         rx_ref [i] = llamaNET_ref;
      }
   }
   cout << "llamaNET_ref after mapping rx_buffers: "
        << dec << llamaNET_ref << endl;

   llamaNET_control->driver.online = true;
   cout << "starting forever loop..." << endl;

   queue<unsigned int> hardware_rx_data;
   unsigned int rx_desc_head = 0;
   unsigned int rx_tail_global = 0;

   bool move_rx_tail = false;

   unsigned int rx_head = 0;
   unsigned int rx_next_head = 0;
   unsigned int rx_index = 0;
   unsigned int tx_tail = 0;
   unsigned int tx_tail2 = 0;
   unsigned int head = 0;

   uint64_t tx_next_index = 0;
   uint64_t tx_last_index = 0;
   uint32_t tx_count = 0;
   uint32_t rx_count = 0;

   int rx_limit = 0;
   int tx_limit = 0;

   // endlessly process messages (or until quit signal)
   for (;;)
   {
      rx_head = llamaNET_control->driver.rx_head;
      rx_count = 0;
      rx_limit = 0;

      // check for newly arriving messages on the hardware
      while (rx_desc [rx_desc_xref [rx_desc_head]].status != 0)
      {
         // queue address to be later copied into shared buffer
         hardware_rx_data.push (rx_desc_head);

         // increment head pointer of hardware receive buffer
         rx_desc_head++;
         rx_desc_head %= rx_desc_max;

         if (++rx_limit > 64)
         {
            break;
         }
      }

      // check for entries in the shared receive buffer no longer in use
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

         if (!move_rx_tail)
         {
            break;
         }

         rx_tail_global++;
         rx_tail_global %= RX_BUFFERS;
      }

      rx_head = llamaNET_control->driver.rx_head;
      rx_count = 0;

      // attempt to copy data from the hardware receive buffer
      // to the shared receive buffer
      while (!hardware_rx_data.empty ())
      {
         // check is buffer is full?
         rx_next_head = rx_head;
         rx_next_head++;
         rx_next_head %= RX_BUFFERS;

         if (rx_tail_global == rx_next_head)
         {
            break;
         }

         // copy data to shared buffer
         rx_index = hardware_rx_data.front ();
         hardware_rx_data.pop ();

         memcpy (rx_shared_buffers [rx_head],
                 rx_hardware_buffers [rx_index].pointer,
                 rx_desc [rx_desc_xref [rx_index]].length);

         // signal hardware to reuse buffer
         rx_desc [rx_desc_xref [rx_index]].checksum = 0;
         rx_desc [rx_desc_xref [rx_index]].error = 0;
         rx_desc [rx_desc_xref [rx_index]].length = 0;
         rx_desc [rx_desc_xref [rx_index]].status = 0;
         rx_desc [rx_desc_xref [rx_index]].vlan = 0;

         rx_head = rx_next_head;
         rx_count++;
      }

      if (rx_count > 0)
      {
         wmb();

         rx_tail += rx_count;
         rx_tail %= rx_desc_max;
         csr.write_RDT (rx_tail);

         // move shared head pointer
         rx_next_head = llamaNET_control->driver.rx_head;
         rx_next_head += rx_count;
         rx_next_head %= RX_BUFFERS;
         llamaNET_control->driver.rx_head = rx_next_head;
      }

      // check for requests to send data to the hardware
// !BAM this still does not work properly
// The complications comes from the fact that the masks will not be set in
//      order. The various guest are requesting buffers and sending them
//      async. But I also do not want to process them one at a time because
//      writing to the NIC registers and calling the atomic functions causes
//      has a measurable time delay.
//      For now, process them one at a time to get it working again.
#if 0
      uint64_t tx_next_index = llamaNET_control->driver.tx_next_index;
      uint64_t tx_last_index = llamaNET_control->driver.tx_last_index;

      if (tx_next_index != tx_last_index)
      {
         uint32_t tx_mask = 0;
         uint32_t tx_count = 0;

         for (uint32_t i = (tx_last_index % 32); i < 32; i++)
         {
            tx_mask |= (1 << i);
            tx_count++;

            if ((tx_last_index + tx_count) == tx_next_index)
            {
               break;
            }
         }

         tx_mask =
           llamaNET_control->driver.tx_mask [(tx_last_index % TX_BUFFERS) / 32];

         tx_count = 0;
         for (uint32_t i = (tx_last_index % 32); i < 32; i++)
         {
            if (tx_mask & (1 << i))
            {
               llamaos::net::llamaNET::Protocol_header *header =
                  reinterpret_cast<llamaos::net::llamaNET::Protocol_header *> (
                  tx_buffers [(tx_last_index + tx_count) % TX_BUFFERS].pointer);

               if (   (header->eth_dest [0] != mac_addr [0])
                   || (header->eth_dest [1] != mac_addr [1])
                   || (header->eth_dest [2] != mac_addr [2])
                   || (header->eth_dest [3] != mac_addr [3])
                   || (header->eth_dest [4] != mac_addr [4])
                   || (header->eth_dest [5] != mac_addr [5]))
               {
                  tx_desc [tx_desc_xref [tx_tail]].buffer =
                   tx_buffers [(tx_last_index + tx_count) % TX_BUFFERS].address;
                  tx_desc [tx_desc_xref [tx_tail]].length =
                        llamaos::net::llamaNET::HEADER_LENGTH + header->len;
                  tx_desc [tx_desc_xref [tx_tail]].CSO = 0;
                  tx_desc [tx_desc_xref [tx_tail]].CMD = 0x0B;
                  tx_desc [tx_desc_xref [tx_tail]].STA = 0;
                  tx_desc [tx_desc_xref [tx_tail]].CSS = 0;
                  tx_desc [tx_desc_xref [tx_tail]].VLAN = 0;

                  tx_tail++;
                  tx_tail %= tx_desc_max;

                  tx_tail2 = tx_tail + 2;
                  tx_tail2 %= tx_desc_max;

                  // holding for phys buffer space....
                  while (   (tx_desc [tx_desc_xref [tx_tail2]].CMD == 0x0B)
                         && (tx_desc [tx_desc_xref [tx_tail2]].STA == 0));
               }

               tx_count++;

               __sync_fetch_and_and(
                        &llamaNET_control->driver.tx_mask [
                        (tx_last_index % TX_BUFFERS) / 32], ~(1 << i));
            }
            else
            {
               break;
            }
         }

         if (tx_count > 0)
         {
            wmb();
            csr.write_TDT (tx_tail);
// cout << "send hardware " << tx_tail << endl;

            head = llamaNET_control->driver.tx_head;
            head += tx_count;
            head %= TX_BUFFERS;
            llamaNET_control->driver.tx_head = head;

            wmb();
            llamaNET_control->driver.tx_last_index += tx_count;
         }
      }
#else
      tx_next_index = llamaNET_control->driver.tx_next_index;
      tx_last_index = llamaNET_control->driver.tx_last_index;
      tx_count = 0;
      tx_limit = 0;

      while (tx_next_index != tx_last_index)
      {
         uint32_t tx_mask = __sync_fetch_and_and(
          &llamaNET_control->driver.tx_mask [(tx_last_index % TX_BUFFERS) / 32],
          ~(1 << (tx_last_index % 32)));

         if (tx_mask & (1 << (tx_last_index % 32)))
         {
            llamaos::net::llamaNET::Protocol_header *header =
               reinterpret_cast<llamaos::net::llamaNET::Protocol_header *> (
               tx_buffers [(tx_last_index) % TX_BUFFERS].pointer);

            if (   (header->eth_dest [0] != mac_addr [0])
                || (header->eth_dest [1] != mac_addr [1])
                || (header->eth_dest [2] != mac_addr [2])
                || (header->eth_dest [3] != mac_addr [3])
                || (header->eth_dest [4] != mac_addr [4])
                || (header->eth_dest [5] != mac_addr [5]))
            {
               tx_desc [tx_desc_xref [tx_tail]].buffer =
                tx_buffers [(tx_last_index) % TX_BUFFERS].address;
               tx_desc [tx_desc_xref [tx_tail]].length =
                     llamaos::net::llamaNET::HEADER_LENGTH + header->len;
               tx_desc [tx_desc_xref [tx_tail]].CSO = 0;
               tx_desc [tx_desc_xref [tx_tail]].CMD = 0x0B;
               tx_desc [tx_desc_xref [tx_tail]].STA = 0;
               tx_desc [tx_desc_xref [tx_tail]].CSS = 0;
               tx_desc [tx_desc_xref [tx_tail]].VLAN = 0;

               tx_tail++;
               tx_tail %= tx_desc_max;

               tx_tail2 = tx_tail + 2;
               tx_tail2 %= tx_desc_max;

               // holding for phys buffer space....
               while (   (tx_desc [tx_desc_xref [tx_tail2]].CMD == 0x0B)
                      && (tx_desc [tx_desc_xref [tx_tail2]].STA == 0))
               {
//                  cout << "waiting for hardware buffer..." << endl;
               }
            }

            tx_last_index++;
            tx_last_index %= TX_BUFFERS;
            tx_count++;
         }
         else
         {
            // this bit is not set yet so stop processing sends
            break;
         }

         if (++tx_limit > 64)
         {
            break;
         }
      }

      if (tx_count > 0)
      {
         wmb();
         csr.write_TDT (tx_tail);

         head = llamaNET_control->driver.tx_head;
         head += tx_count;
         head %= TX_BUFFERS;
         llamaNET_control->driver.tx_head = head;

         wmb();
         llamaNET_control->driver.tx_last_index += tx_count;
      }
#endif

      // check for entries in the shared send buffer no longer in use
      while (llamaNET_control->driver.tx_last_index !=
             llamaNET_control->driver.tx_done_index)
      {
         // prevent tx_done from passing the hardware tail
         if (   (tx_desc [tx_desc_xref [llamaNET_control->driver.tx_done_index % TX_BUFFERS]].CMD == 0x0B)
             && (tx_desc [tx_desc_xref [llamaNET_control->driver.tx_done_index % TX_BUFFERS]].STA == 0))
         {
            break;
         }

         bool update = true;

         for (int i = 0; i < 6; i++)
         {
            if (   (llamaNET_control->app [i].online)
                && ((llamaNET_control->driver.tx_done_index % TX_BUFFERS) ==
                    llamaNET_control->app [i].tx_tail))
            {
               update = false;
               break;
            }
         }

         if (!update)
         {
            break;
         }

         llamaNET_control->driver.tx_done_index++;
      }

      // check for quit flag
      if (llamaNET_control->close_driver)
      {
         // leave driver, app is done
         break;
      }

// !BAM reporting missing packet but getting all data in applications
//      uint16_t missed = csr.read (0x4010);
//      if (missed != 0)
//      {
//         cout << "Missed Packets Count = " << missed << endl;
//      }
   }

//   cout << "Missed Packets Count = " << csr.read (0x4010) << endl;
   cout << "close_driver is: " << llamaNET_control->close_driver << endl;
   cout << "waiting 3 sec, then exit..." << endl;
   cout.flush ();
   sleep (3);

   free (dead_memory);
   return 0;
}

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

#define DRIVER 1

#define LATENCY_TRIAL 250000
#define LATENCY_DATA 8
#define LATENCY_SERVER 0
#define LATENCY_CLIENT 0

#define LOOPBACK 0

#if LATENCY_SERVER
static bool verify_data_alpha (const unsigned char *buffer, unsigned long length)
{
   unsigned long j = 0;
   unsigned char c;

   for (unsigned long i = 0; i < length; i++)
   {
      c = 'A' + (++j % 26);

      if (buffer [i] != c)
      {
         cout << "verify alpha failed (" << buffer [i] << " != " << c << ") @ index " << i << endl;
         return false;
      }
   }

   return true;
}

static void mark_data_numeric (unsigned char *buffer, unsigned long length)
{
   unsigned long j = 0;

   // put num data (0 1 2 3 ...)
   for (unsigned long i = 0; i < length; i++)
   {
      buffer [i] = ('0' + (++j % 10));
   }
}
#endif

#if LATENCY_CLIENT
static uint64_t tsc1;
static uint64_t tsc2;
static unsigned long results [LATENCY_TRIAL];

static void mark_data_alpha (unsigned char *buffer, unsigned long length)
{
   unsigned long j = 0;

   // put alpha data (A B C D ...)
   for (unsigned long i = 0; i < length; i++)
   {
      buffer [i] = ('A' + (++j % 26));
   }
}

static bool verify_data_numeric (const unsigned char *buffer, unsigned long length)
{
   unsigned long j = 0;
   unsigned char c;

   for (unsigned long i = 0; i < length; i++)
   {
      c = '0' + (++j % 10);

      if (buffer [i] != c)
      {
         cout << "verify numeric failed (" << buffer [i] << " != " << c << ") @ index " << i << endl;
         return false;
      }
   }

   return true;
}

static void compute_statistics (unsigned long trials, unsigned long *results)
{
   unsigned long mean = 0.0;
   unsigned long variance = 0.0;
   unsigned long latency = 0UL;
   unsigned long sum = 0UL;
   unsigned long min_latency = 0xFFFFFFFFFFFFFFFFUL;
   unsigned long max_latency = 0UL;

   // iterate to compute mean
   for (unsigned long i = 0; i < trials; i++)
   {
      latency = results [i];

      sum += latency;

      min_latency = (latency < min_latency) ? latency : min_latency;
      max_latency = (latency > max_latency) ? latency : max_latency;
   }

   cout << dec;
   cout << "latency sum: " << sum << ", trials: " << trials << endl;
   mean = sum / trials;
   sum = 0UL;

   // iterate to compute variance
   for (unsigned long i = 0; i < trials; i++)
   {
      latency = results [i];

      sum += ((latency - mean) * (latency - mean));
   }

   variance = sum / trials;

   cout << dec;
   cout << "  mean: " << mean << ", var: " << variance << ", [" << min_latency << ", " << max_latency << "]" << endl;
}

static inline uint64_t rdtsc ()
{
   uint32_t lo, hi;

   asm volatile ("rdtsc" : "=a" (lo), "=d" (hi));

   return (static_cast<uint64_t>(hi) << 32) | lo;
}

static inline uint64_t tsc_to_ns (uint64_t tsc)
{
   const vcpu_time_info_t *time_info = &Hypervisor::get_instance()->shared_info->vcpu_info [0].time;
   const uint64_t overflow = UINT64_MAX / time_info->tsc_to_system_mul;
   uint64_t time_ns = 0UL;

   uint64_t stsc = (time_info->tsc_shift < 0)
                 ? (tsc >> -time_info->tsc_shift) : (tsc << time_info->tsc_shift);

   // mul will overflow 64 bits
   while (stsc > overflow)
   {
      time_ns += ((overflow * time_info->tsc_to_system_mul) >> 32);
      stsc -= overflow;
   }

   time_ns += (stsc * time_info->tsc_to_system_mul) >> 32;

   return time_ns;
}
#endif

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
   PCI pci;
   sleep (1);
   cout << "PCI config:" << endl;
//   cout << pci << endl;

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

   cout << "setting link up..." << endl;
   ctrl.SLU (true);
   csr.write_CTRL (ctrl);

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
   tctl.PBE(true);
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
   rctl.LPE(true);
   rctl.BSIZE(RCTL::BYTES_256);
   rctl.BSEX(true);
   csr.write_RCTL (rctl);

   cout << "create transmit descriptors..." << endl;

   struct tx_desc_t *tx_desc = static_cast<struct tx_desc_t *>(memalign (PAGE_SIZE, PAGE_SIZE));
   memset(tx_desc, 0, PAGE_SIZE);
   uint64_t tx_desc_machine_address = virtual_pointer_to_machine_address(tx_desc);
   Hypercall::update_va_mapping_nocache (pointer_to_address (tx_desc), tx_desc_machine_address);

   csr.write_TDBA (tx_desc_machine_address);
//   csr.write_TDLEN (1024);    // 64 descriptors
//   csr.write_TDLEN (128);     // 8 descriptors
   csr.write_TDLEN (PAGE_SIZE); // 256 descriptors
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
//   csr.write_RDLEN (128);     // 8 descriptors
   csr.write_RDLEN (PAGE_SIZE); // 256 descriptors
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
   cout << "llamaNET_ref: " << dec << llamaNET_ref << endl;

   llamaNET_control->rx_buffer_size = 8;
   llamaNET_control->tx_buffer_size = 8;

   // allow tx_buffer guest access
   for (unsigned int i = 0; i < llamaNET_control->rx_buffer_size; i++)
   {
      llamaNET_control->app [0].tx_refs [i] = Hypervisor::get_instance ()->grant_table.grant_access (self_id+1, tx_buffers [i].pointer);
      llamaNET_control->app [1].tx_refs [i] = Hypervisor::get_instance ()->grant_table.grant_access (self_id+2, tx_buffers [i].pointer);
      llamaNET_control->app [2].tx_refs [i] = Hypervisor::get_instance ()->grant_table.grant_access (self_id+3, tx_buffers [i].pointer);
      llamaNET_control->app [3].tx_refs [i] = Hypervisor::get_instance ()->grant_table.grant_access (self_id+4, tx_buffers [i].pointer);
      llamaNET_control->app [4].tx_refs [i] = Hypervisor::get_instance ()->grant_table.grant_access (self_id+5, tx_buffers [i].pointer);
      llamaNET_control->app [5].tx_refs [i] = Hypervisor::get_instance ()->grant_table.grant_access (self_id+6, tx_buffers [i].pointer);
   }

   // allow rx_buffer guest access
   for (unsigned int i = 0; i < llamaNET_control->rx_buffer_size; i++)
   {
      llamaNET_control->app [0].rx_refs [i] = Hypervisor::get_instance ()->grant_table.grant_access (self_id+1, rx_buffers [i].pointer);
      llamaNET_control->app [1].rx_refs [i] = Hypervisor::get_instance ()->grant_table.grant_access (self_id+2, rx_buffers [i].pointer);
      llamaNET_control->app [2].rx_refs [i] = Hypervisor::get_instance ()->grant_table.grant_access (self_id+3, rx_buffers [i].pointer);
      llamaNET_control->app [3].rx_refs [i] = Hypervisor::get_instance ()->grant_table.grant_access (self_id+4, rx_buffers [i].pointer);
      llamaNET_control->app [4].rx_refs [i] = Hypervisor::get_instance ()->grant_table.grant_access (self_id+5, rx_buffers [i].pointer);
      llamaNET_control->app [5].rx_refs [i] = Hypervisor::get_instance ()->grant_table.grant_access (self_id+6, rx_buffers [i].pointer);
   }

   llamaNET_control->driver.online = true;
   cout << "starting forever loop..." << endl;

   int cleanup_delay = 0;
   unsigned int head = 0;

#if DRIVER
   for (;;)
   {
//      if (rx_head != csr.read_RDH())
      if (rx_desc [rx_head].status != 0)
      {
         head = llamaNET_control->driver.rx_head;
         head++;
         head %= 8;
         llamaNET_control->driver.rx_head = head;

         rx_head++;
         rx_head %= 256;

         // !bam can't do this until all guest tail is updated
         buffer_entry rx_buffer = rx_hw.front();
         rx_hw.pop ();

         rx_desc [rx_tail].buffer = rx_buffer.address;
         rx_desc [rx_tail].checksum = 0;
         rx_desc [rx_tail].error = 0;
         rx_desc [rx_tail].length = 0;
         rx_desc [rx_tail].status = 0;
         rx_desc [rx_tail].vlan = 0;
         rx_hw.push(rx_buffer);
         rx_tail++;
         rx_tail %= 256;
         csr.write_RDT (rx_tail);
      }

#if 0
      unsigned int tail = llamaNET_control->app [0].tx_tail;

//      if (llamaNET_control->app [0].tx_head != llamaNET_control->app [0].tx_tail)
      if (llamaNET_control->app [0].tx_head != tail)
      {
//         buffer_entry tx_buffer = tx_sw.front();

//         tx_desc [tx_tail].buffer = tx_buffer.address;
         tx_desc [tx_tail].buffer = tx_buffers [tail].address;
         tx_desc [tx_tail].length = llamaNET_control->app [0].tx_length [tail];
         tx_desc [tx_tail].CSO = 0;
         tx_desc [tx_tail].CMD = 0x0B;
         tx_desc [tx_tail].STA = 0;
         tx_desc [tx_tail].CSS = 0;
         tx_desc [tx_tail].VLAN = 0;

         tx_tail++;
         tx_tail %= 256;
         csr.write_TDT (tx_tail);

//         tx_sw.pop ();
//         tx_hw.push(tx_buffer);

//         unsigned int tail = llamaNET_control->app [0].tx_tail;
         tail++;
         tail %= 8;
         llamaNET_control->app [0].tx_tail = tail;
      }
#endif

      for (int i = 0; i < 6; i++)
      {
         if (llamaNET_control->app [i].tx_request)
         {
            tx_desc [tx_tail].buffer = tx_buffers [llamaNET_control->app [i].tx_index].address;
            tx_desc [tx_tail].length = llamaNET_control->app [i].tx_length;
            tx_desc [tx_tail].CSO = 0;
            tx_desc [tx_tail].CMD = 0x0B;
            tx_desc [tx_tail].STA = 0;
            tx_desc [tx_tail].CSS = 0;
            tx_desc [tx_tail].VLAN = 0;

            tx_tail++;
            tx_tail %= 256;
            csr.write_TDT (tx_tail);

            llamaNET_control->app [i].tx_request = false;
         }
      }

      if (++cleanup_delay > 1000)
      {
         cleanup_delay = 0;

         // cleanup tx while waiting
//         while (tx_head != csr.read_TDH())
//         {
//            tx_sw.push(tx_hw.front());
//            tx_hw.pop();
//            tx_head++;
//            tx_head %= 256;
//         }

         if (llamaNET_control->close_driver)
         {
            cout << "close_driver is: " << llamaNET_control->close_driver << endl;
            // leave driver, app is done
            break;
         }
      }
   }
#endif

#if LATENCY_SERVER
   cout << "waiting for client message..." << endl;
   while (rx_head == csr.read_RDH());

   buffer_entry rx_buffer = rx_hw.front();
   rx_hw.pop ();

   rx_head++;
   rx_head %= 256;

   cout << "received client message..." << endl;
   verify_data_alpha (&rx_buffer.pointer [14], LATENCY_DATA);

   rx_desc [rx_tail].buffer = rx_buffer.address;
   rx_desc [rx_tail].checksum = 0;
   rx_desc [rx_tail].error = 0;
   rx_desc [rx_tail].length = 0;
   rx_desc [rx_tail].status = 0;
   rx_desc [rx_tail].vlan = 0;
   rx_hw.push(rx_buffer);
   rx_tail++;
   rx_tail %= 256;
   csr.write_RDT (rx_tail);

   buffer_entry tx_buffer = tx_sw.front();
   tx_sw.pop ();
   tx_hw.push(tx_buffer);

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
   tx_buffer.pointer [12] = 0x09;
   tx_buffer.pointer [13] = 0x0c;

   // marks all bytes with numerals and send
   mark_data_numeric (&tx_buffer.pointer [14], LATENCY_DATA);

   cout << "sending server message..." << endl;

   tx_desc [tx_tail].buffer = tx_buffer.address;
   tx_desc [tx_tail].length = 14 + LATENCY_DATA;
   tx_desc [tx_tail].CSO = 0;
   tx_desc [tx_tail].CMD = 0x0B;
   tx_desc [tx_tail].STA = 0;
   tx_desc [tx_tail].CSS = 0;
   tx_desc [tx_tail].VLAN = 0;

   tx_tail++;
   tx_tail %= 256;
   csr.write_TDT (tx_tail);

   for (unsigned long i = 0; i < LATENCY_TRIAL; i++)
   {
//      while (rx_head == csr.read_RDH())
      while (rx_desc [rx_head].status == 0)
      {
         // cleanup tx while waiting
         if (tx_head != csr.read_TDH())
         {
            tx_sw.push(tx_hw.front());
            tx_hw.pop();
            tx_head++;
            tx_head %= 256;
         }
      }

      buffer_entry rx_buffer = rx_hw.front();
      rx_hw.pop ();

      rx_head++;
      rx_head %= 256;

      rx_desc [rx_tail].buffer = rx_buffer.address;
      rx_desc [rx_tail].checksum = 0;
      rx_desc [rx_tail].error = 0;
      rx_desc [rx_tail].length = 0;
      rx_desc [rx_tail].status = 0;
      rx_desc [rx_tail].vlan = 0;
      rx_hw.push(rx_buffer);
      rx_tail++;
      rx_tail %= 256;
      csr.write_RDT (rx_tail);

      buffer_entry tx_buffer = tx_sw.front();
      tx_sw.pop ();
      tx_hw.push(tx_buffer);

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
      tx_buffer.pointer [12] = 0x09;
      tx_buffer.pointer [13] = 0x0c;

      // place trial number in first "int" for master to verify
      *(reinterpret_cast<unsigned long *>(&tx_buffer.pointer [14])) = i;

      tx_desc [tx_tail].buffer = tx_buffer.address;
      tx_desc [tx_tail].length = 14 + LATENCY_DATA;
      tx_desc [tx_tail].CSO = 0;
      tx_desc [tx_tail].CMD = 0x0B;
      tx_desc [tx_tail].STA = 0;
      tx_desc [tx_tail].CSS = 0;
      tx_desc [tx_tail].VLAN = 0;

      tx_tail++;
      tx_tail %= 256;
      csr.write_TDT (tx_tail);
   }

#elif LATENCY_CLIENT

   buffer_entry tx_buffer = tx_sw.front();
   tx_sw.pop ();
   tx_hw.push(tx_buffer);

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
   tx_buffer.pointer [12] = 0x09;
   tx_buffer.pointer [13] = 0x0c;

   // marks all bytes with alpha chars (a,b,c,...)
   mark_data_alpha (&tx_buffer.pointer [14], LATENCY_DATA);

   cout << "sending client message..." << endl;

   tx_desc [tx_tail].buffer = tx_buffer.address;
   tx_desc [tx_tail].length = 14 + LATENCY_DATA;
   tx_desc [tx_tail].CSO = 0;
   tx_desc [tx_tail].CMD = 0x0B;
   tx_desc [tx_tail].STA = 0;
   tx_desc [tx_tail].CSS = 0;
   tx_desc [tx_tail].VLAN = 0;

   tx_tail++;
   tx_tail %= 256;
   csr.write_TDT (tx_tail);

   cout << "waiting for server message..." << endl;
   while (rx_head == csr.read_RDH());

   buffer_entry rx_buffer = rx_hw.front();
   rx_hw.pop ();

   rx_head++;
   rx_head %= 256;

   cout << "received server message..." << endl;
   verify_data_numeric (&rx_buffer.pointer [14], LATENCY_DATA);

   rx_desc [rx_tail].buffer = rx_buffer.address;
   rx_desc [rx_tail].checksum = 0;
   rx_desc [rx_tail].error = 0;
   rx_desc [rx_tail].length = 0;
   rx_desc [rx_tail].status = 0;
   rx_desc [rx_tail].vlan = 0;
   rx_hw.push(rx_buffer);
   rx_tail++;
   rx_tail %= 256;
   csr.write_RDT (rx_tail);

   for (unsigned long i = 0; i < LATENCY_TRIAL; i++)
   {
      buffer_entry tx_buffer = tx_sw.front();
      tx_sw.pop ();
      tx_hw.push(tx_buffer);

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
      tx_buffer.pointer [12] = 0x09;
      tx_buffer.pointer [13] = 0x0c;

      tx_desc [tx_tail].buffer = tx_buffer.address;
      tx_desc [tx_tail].length = 14 + LATENCY_DATA;
      tx_desc [tx_tail].CSO = 0;
      tx_desc [tx_tail].CMD = 0x0B;
      tx_desc [tx_tail].STA = 0;
      tx_desc [tx_tail].CSS = 0;
      tx_desc [tx_tail].VLAN = 0;

      tx_tail++;
      tx_tail %= 256;

      // get initial timestamp
      tsc1 = rdtsc ();

      csr.write_TDT (tx_tail);

//      while (rx_head == csr.read_RDH())
      while (rx_desc [rx_head].status == 0)
      {
         // cleanup tx while waiting
         if (tx_head != csr.read_TDH())
         {
            tx_sw.push(tx_hw.front());
            tx_hw.pop();
            tx_head++;
            tx_head %= 256;
         }
      }

      tsc2 = rdtsc ();

      buffer_entry rx_buffer = rx_hw.front();
      rx_hw.pop ();

      rx_head++;
      rx_head %= 256;

      if (*(reinterpret_cast<unsigned long *>(&rx_buffer.pointer[14])) != i)
      {
         cout << "invalid trial number: " << i << " != " << *(reinterpret_cast<unsigned long *>(&rx_buffer.pointer[14])) << endl;
      }

      results [i] = tsc_to_ns(tsc2 - tsc1) / 1000;

      rx_desc [rx_tail].buffer = rx_buffer.address;
      rx_desc [rx_tail].checksum = 0;
      rx_desc [rx_tail].error = 0;
      rx_desc [rx_tail].length = 0;
      rx_desc [rx_tail].status = 0;
      rx_desc [rx_tail].vlan = 0;
      rx_hw.push(rx_buffer);
      rx_tail++;
      rx_tail %= 256;
      csr.write_RDT (rx_tail);
   }

   compute_statistics (LATENCY_TRIAL, results);

#endif

#if LOOPBACK
   for (;;)
   {
      if (rx_head != csr.read_RDH())
      {
         buffer_entry rx_buffer = rx_hw.front();
         rx_hw.pop ();

         unsigned int head = llamaNET_control->app [0].rx_head;
         head++;
         head %= 8;
         llamaNET_control->app [0].rx_head = head;

         rx_head++;
         rx_hw.push(rx_buffer);
      }
      else if (llamaNET_control->app [0].tx_head != llamaNET_control->app [0].tx_tail)
      {
         buffer_entry tx_buffer = tx_sw.front();
         tx_sw.pop ();
         tx_hw.push(tx_buffer);

         unsigned int tail = llamaNET_control->app [0].tx_tail;
         tail++;
         tail %= 8;
         llamaNET_control->app [0].tx_tail = tail;

         // don't send it just put it back in list
         tx_sw.push(tx_hw.front());
         tx_hw.pop();

         // wake up receiver as if frame left and is back
         rx_head--;
      }
      else if (llamaNET_control->close_driver)
      {
         cout << "close_driver is: " << llamaNET_control->close_driver << endl;
         // leave driver, app is done
         break;
      }
   }
#endif

   cout << "waiting 3 sec, then exit..." << endl;
   cout.flush ();
   sleep (3);

   return 0;
}

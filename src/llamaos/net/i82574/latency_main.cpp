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
#include <llamaos/xen/Hypervisor.h>
#include <llamaos/llamaOS.h>

using namespace std;
using namespace llamaos;
using namespace llamaos::api;
using namespace llamaos::api::pci;
using namespace llamaos::memory;
using namespace llamaos::net::i82574;

static void mark_data_alpha (unsigned char *buffer, unsigned long length)
{
   unsigned long j = 0;

   // put alpha data (A B C D ...)
   for (unsigned long i = 0; i < length; i++)
   {
      buffer [i] = ('A' + (++j % 26));
   }
}

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
   double mean = 0.0;
   double variance = 0.0;
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
   mean = static_cast<double>(sum) / trials;
   sum = 0UL;

   // iterate to compute variance
   for (unsigned long i = 0; i < trials; i++)
   {
      latency = results [i];

      sum += ((latency - mean) * (latency - mean));
   }

   variance = sum / trials;

   cout << dec;
   cout << "sizeof(unsigned char): " << sizeof(unsigned char) << ", sizeof(unsigned int): " << sizeof(unsigned int) << ", sizeof(unsigned long): " << sizeof(unsigned long) << endl;
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

static void embedded_latency (CSR &csr)
{
   struct tx_desc_t *tx_desc = static_cast<struct tx_desc_t *>(memalign (PAGE_SIZE, PAGE_SIZE));
   memset(tx_desc, 0, PAGE_SIZE);
   uint64_t tx_desc_machine_address = virtual_pointer_to_machine_address(tx_desc);
   Hypercall::update_va_mapping_nocache (pointer_to_address (tx_desc), tx_desc_machine_address);

   csr.write_TDBA (tx_desc_machine_address);
   csr.write_TDLEN (1024);
   cout << "TDBA: " << hex << csr.read_TDBA() << ", " << tx_desc_machine_address << endl;

   buffer_entry tx_buffers [64];
   queue<buffer_entry> tx_hw;
   queue<buffer_entry> tx_sw;

   for (unsigned int i = 0; i < 64; i++)
   {
      tx_buffers [i].pointer = static_cast<unsigned char *>(memalign (PAGE_SIZE, PAGE_SIZE));
      tx_buffers [i].address = virtual_pointer_to_machine_address(tx_buffers [i].pointer);
      Hypercall::update_va_mapping_nocache (pointer_to_address (tx_buffers [i].pointer), tx_buffers [i].address);

      tx_sw.push(tx_buffers [i]);
   }

   unsigned int tx_head = 0;
   unsigned int tx_tail = 0;

   struct rx_desc_t *rx_desc = static_cast<struct rx_desc_t *>(memalign (PAGE_SIZE, PAGE_SIZE));
   memset(rx_desc, 0, PAGE_SIZE);
   uint64_t rx_desc_machine_address = virtual_pointer_to_machine_address(rx_desc);
   Hypercall::update_va_mapping_nocache (pointer_to_address (rx_desc), rx_desc_machine_address);

   csr.write_RDBA (rx_desc_machine_address);
   csr.write_RDLEN (1024);
   cout << "RDBA: " << hex << csr.read_RDBA() << ", " << rx_desc_machine_address << endl;

   buffer_entry rx_buffers [64];
   queue<buffer_entry> rx_hw;

   for (unsigned int i = 0; i < 64; i++)
   {
      rx_buffers [i].pointer = static_cast<unsigned char *>(memalign (PAGE_SIZE, PAGE_SIZE));
      rx_buffers [i].address = virtual_pointer_to_machine_address(rx_buffers [i].pointer);
      Hypercall::update_va_mapping_nocache (pointer_to_address (rx_buffers [i].pointer), rx_buffers [i].address);

      rx_desc [i].buffer = rx_buffers [i].address;
      rx_desc [i].status = 0;
      rx_hw.push(rx_buffers [i]);
   }

   uint16_t rx_head = 0;
   uint16_t rx_tail = 64;
   csr.write_RDT (rx_tail);

#define TRIALS 100000
#define LENGTH 64
   // struct timeval tv1;
   // struct timeval tv2;
   // unsigned long usec1;
   // unsigned long usec2;
   uint64_t tsc1;
   uint64_t tsc2;
   unsigned long results [TRIALS];

// dalai 00-1b-21-d5-66-ef
// redpj 68-05-ca-01-f7-db
#if 0
// server

   cout << "waiting for client message..." << endl;
   while (rx_head == csr.read_RDH());

   buffer_entry rx_buffer = rx_hw.front();
   rx_hw.pop ();
   rx_head++;
   rx_head %= 64;

   cout << "received client message..." << endl;
   verify_data_alpha (&rx_buffer.pointer [14], LENGTH);

   rx_desc [rx_tail].buffer = rx_buffer.address;
   rx_desc [rx_tail].status = 0;
   rx_hw.push(rx_buffer);
   rx_tail++;
   rx_tail %= 64;
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
   mark_data_numeric (&tx_buffer.pointer [14], LENGTH);

   cout << "sending server message..." << endl;
   tx_desc [tx_tail].buffer = tx_buffer.address;
   tx_desc [tx_tail].length = 14 + LENGTH + 4;
   tx_desc [tx_tail].CSO = 0;
   tx_desc [tx_tail].CMD = 0x0B;
   tx_desc [tx_tail].STA = 0;
   tx_desc [tx_tail].CSS = 0;
   tx_desc [tx_tail].VLAN = 0;

   tx_tail++;
   tx_tail %= 64;
   csr.write_TDT (tx_tail);

   for (unsigned long i = 0; i < TRIALS; i++)
   {
      // wait for message
      while (rx_head == csr.read_RDH())
      {
         // cleanup tx while waiting
         if (tx_head != csr.read_TDH())
         {
            tx_sw.push(tx_hw.front());
            tx_hw.pop();
            tx_head++;
            tx_head %= 64;
         }
      }

      // send response
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
      tx_desc [tx_tail].length = 14 + LENGTH;
      tx_desc [tx_tail].CSO = 0;
      tx_desc [tx_tail].CMD = 0x0B;
      tx_desc [tx_tail].STA = 0;
      tx_desc [tx_tail].CSS = 0;
      tx_desc [tx_tail].VLAN = 0;

      tx_tail++;
      tx_tail %= 64;
      csr.write_TDT (tx_tail);

      // replace the rx buffer
      buffer_entry rx_buffer = rx_hw.front();
      rx_hw.pop ();
      rx_head++;
      rx_head %= 64;

      rx_desc [rx_tail].buffer = rx_buffer.address;
      rx_desc [rx_tail].status = 0;
      rx_hw.push(rx_buffer);
      rx_tail++;
      rx_tail %= 64;
      csr.write_RDT (rx_tail);
   }

#else

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
   mark_data_alpha (&tx_buffer.pointer [14], LENGTH);

   // send/recv and verify the data has been changed to numerals (1,2,3,...)
   tx_desc [tx_tail].buffer = tx_buffer.address;
   tx_desc [tx_tail].length = 14 + LENGTH;
   tx_desc [tx_tail].CSO = 0;
   tx_desc [tx_tail].CMD = 0x0B;
   tx_desc [tx_tail].STA = 0;
   tx_desc [tx_tail].CSS = 0;
   tx_desc [tx_tail].VLAN = 0;

   tx_tail++;
   tx_tail %= 64;
   cout << "sending client message..." << endl;
   csr.write_TDT (tx_tail);

   cout << "waiting for client message..." << endl;
   while (rx_head == csr.read_RDH());

   buffer_entry rx_buffer = rx_hw.front();
   rx_hw.pop ();
   rx_head++;
   rx_head %= 64;

   cout << "received client message..." << endl;
   verify_data_numeric (&rx_buffer.pointer [14], LENGTH);

   rx_desc [rx_tail].buffer = rx_buffer.address;
   rx_desc [rx_tail].checksum = 0;
   rx_desc [rx_tail].error = 0;
   rx_desc [rx_tail].length = 0;
   rx_desc [rx_tail].status = 0;
   rx_desc [rx_tail].vlan = 0;
   rx_hw.push(rx_buffer);
   rx_tail++;
   rx_tail %= 64;
   csr.write_RDT (rx_tail);

   for (unsigned long i = 0; i < TRIALS; i++)
   {
      // send message
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
      tx_desc [tx_tail].length = 14 + LENGTH;
      tx_desc [tx_tail].CSO = 0;
      tx_desc [tx_tail].CMD = 0x0B;
      tx_desc [tx_tail].STA = 0;
      tx_desc [tx_tail].CSS = 0;
      tx_desc [tx_tail].VLAN = 0;

      tx_tail++;
      tx_tail %= 64;

      // get initial timestamp
      tsc1 = rdtsc ();
      csr.write_TDT (tx_tail);

      while (tx_tail != csr.read_TDH())
      tsc2 = rdtsc ();

      // wait for response
      while (rx_head == csr.read_RDH())
      {
         // cleanup tx while waiting
         if (tx_head != csr.read_TDH())
         {
            tx_sw.push(tx_hw.front());
            tx_hw.pop();
            tx_head++;
            tx_head %= 64;
         }
      }

      // check sequence number in response
      buffer_entry rx_buffer = rx_hw.front();
      rx_hw.pop ();
      rx_head++;
      rx_head %= 64;

      if (*(reinterpret_cast<unsigned long *>(&rx_buffer.pointer[14])) != i)
      {
         cout << "invalid trial number: " << i << " != " << *(reinterpret_cast<unsigned long *>(&rx_buffer.pointer[14])) << endl;
      }

      results [i] = tsc_to_ns(tsc2 - tsc1) / 1000;

      // replace rx_buffer
      rx_desc [rx_tail].buffer = rx_buffer.address;
      rx_desc [rx_tail].checksum = 0;
      rx_desc [rx_tail].error = 0;
      rx_desc [rx_tail].length = 0;
      rx_desc [rx_tail].status = 0;
      rx_desc [rx_tail].vlan = 0;
      rx_hw.push(rx_buffer);
      rx_tail++;
      rx_tail %= 64;
      csr.write_RDT (rx_tail);
   }

   compute_statistics (TRIALS, results);

#endif
}

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

   embedded_latency (csr);

#if 0
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

   unsigned char *tx_buffer = static_cast<unsigned char *>(memalign (PAGE_SIZE, PAGE_SIZE));
   uint64_t buffer_machine_address = virtual_pointer_to_machine_address(tx_buffer);
   Hypercall::update_va_mapping_nocache (pointer_to_address (tx_buffer), buffer_machine_address);

   unsigned long tx_tail = 0;


   cout.flush();
   cout <<  "RCTL: " << csr.read_RCTL () << endl;
   cout <<  "RXDCTL: " << csr.read_RXDCTL () << endl;
   cout << "setup receive descript table..." << endl;
   cout << "sizeof(rx_desc_t): " << sizeof(rx_desc_t) << endl;
   cout.flush();

   struct rx_desc_t *rx_desc = static_cast<struct rx_desc_t *>(memalign (PAGE_SIZE, PAGE_SIZE));
   memset(rx_desc, 0, PAGE_SIZE);
   uint64_t rx_desc_machine_address = virtual_pointer_to_machine_address(rx_desc);
   Hypercall::update_va_mapping_nocache (pointer_to_address (rx_desc), rx_desc_machine_address);
   csr.write_RDBA (rx_desc_machine_address);
   csr.write_RDLEN (256);
   cout << "RDBA: " << hex << csr.read_RDBA() << ", " << rx_desc_machine_address << endl;

   cout << "inserting receive buffers..." << endl;
   unsigned char *rx_buffer;
   unsigned long rx_head = 0;
   unsigned long rx_tail = 0;

   rx_buffer = static_cast<unsigned char *>(memalign (PAGE_SIZE, PAGE_SIZE));
   memset(rx_buffer, 0, PAGE_SIZE);
   uint64_t rx_buffer_machine_address = virtual_pointer_to_machine_address(rx_buffer);
   Hypercall::update_va_mapping_nocache (pointer_to_address (rx_buffer), rx_buffer_machine_address);
   rx_desc [rx_head].buffer = rx_buffer_machine_address;
   rx_desc [rx_head+1].buffer = rx_buffer_machine_address;
   rx_desc [rx_head+2].buffer = rx_buffer_machine_address;
   rx_desc [rx_head+3].buffer = rx_buffer_machine_address;
   rx_desc [rx_head+4].buffer = rx_buffer_machine_address;

   csr.write_RDT (rx_tail+4);


#define TRIALS 100
#define LENGTH 1024

// dalai 00-1b-21-d5-66-ef
// redpj 68-05-ca-01-f7-db
#if 1
// server

   tx_buffer [0] = 0x00;
   tx_buffer [1] = 0x1b;
   tx_buffer [2] = 0x21;
   tx_buffer [3] = 0xd5;
   tx_buffer [4] = 0x66;
   tx_buffer [5] = 0xef;
   tx_buffer [6] = 0x68;
   tx_buffer [7] = 0x05;
   tx_buffer [8] = 0xca;
   tx_buffer [9] = 0x01;
   tx_buffer [10] = 0xf7;
   tx_buffer [11] = 0xdb;
   tx_buffer [12] = 0x09;
   tx_buffer [13] = 0x0c;

   cout << "waiting for client message..." << endl;
   // wait for mesg and verify alpha chars
   //while (0 == rx_desc [rx_head].status);
   while (rx_head == csr.read_RDH ());
   verify_data_alpha (&rx_buffer [14], LENGTH);

   cout << "received client message..." << endl;

   rx_head++;
   rx_head %= 256;
   rx_desc [rx_head].buffer = rx_buffer_machine_address;
   rx_desc [rx_head].status = 0;
   rx_tail++;
   rx_tail %= 256;
   csr.write_RDT (rx_tail);

   // marks all bytes with numerals and send
   mark_data_numeric (&tx_buffer [14], LENGTH);

   tx_desc [tx_tail].buffer = buffer_machine_address;
   tx_desc [tx_tail].length = 14 + LENGTH + 4;
   tx_desc [tx_tail].CSO = 0;
   tx_desc [tx_tail].CMD = 0x0B;
   tx_desc [tx_tail].STA = 0;
   tx_desc [tx_tail].CSS = 0;
   tx_desc [tx_tail].VLAN = 0;

   tx_tail++;
   tx_tail %= 256;
   cout << "sending server message..." << endl;
   csr.write_TDT (tx_tail);

   for (unsigned long i = 0; i < TRIALS; i++)
   {
      // wait for message to arrive
      while (0 == rx_desc [rx_head].status);

      rx_head++;
      rx_head %= 256;
      rx_desc [rx_head].buffer = rx_buffer_machine_address;
      rx_desc [rx_head].status = 0;
      rx_tail++;
      rx_tail %= 256;
      csr.write_RDT (rx_tail);

      // place trial number in first "int" for master to verify
      *(reinterpret_cast<unsigned long *>(&tx_buffer [14])) = i;
      tx_desc [tx_tail].buffer = buffer_machine_address;
      tx_desc [tx_tail].length = 14 + LENGTH + 4;
      tx_desc [tx_tail].CSO = 0;
      tx_desc [tx_tail].CMD = 0x0B;
      tx_desc [tx_tail].STA = 0;
      tx_desc [tx_tail].CSS = 0;
      tx_desc [tx_tail].VLAN = 0;

      tx_tail++;
      tx_tail %= 256;
      csr.write_TDT (tx_tail);
   }

   // wait for mesg and verify alpha chars
   while (0 == rx_desc [rx_head].status);
   verify_data_alpha (&rx_buffer [14], LENGTH);

   // marks all bytes with numerals and send
   mark_data_numeric (&tx_buffer [14], LENGTH);

   tx_desc [tx_tail].buffer = buffer_machine_address;
   tx_desc [tx_tail].length = 14 + LENGTH + 4;
   tx_desc [tx_tail].CSO = 0;
   tx_desc [tx_tail].CMD = 0x0B;
   tx_desc [tx_tail].STA = 0;
   tx_desc [tx_tail].CSS = 0;
   tx_desc [tx_tail].VLAN = 0;

   tx_tail++;
   tx_tail %= 256;
   csr.write_TDT (tx_tail);

#else
   tx_buffer [0] = 0x68;
   tx_buffer [1] = 0x05;
   tx_buffer [2] = 0xca;
   tx_buffer [3] = 0x01;
   tx_buffer [4] = 0xf7;
   tx_buffer [5] = 0xdb;
   tx_buffer [6] = 0x00;
   tx_buffer [7] = 0x1b;
   tx_buffer [8] = 0x21;
   tx_buffer [9] = 0xd5;
   tx_buffer [10] = 0x66;
   tx_buffer [11] = 0xef;
   tx_buffer [12] = 0x09;
   tx_buffer [13] = 0x0c;

   // marks all bytes with alpha chars (a,b,c,...)
   mark_data_alpha (&tx_buffer [14], LENGTH);

   // send/recv and verify the data has been changed to numerals (1,2,3,...)
   tx_desc [tx_tail].buffer = buffer_machine_address;
   tx_desc [tx_tail].length = 14 + LENGTH + 4;
   tx_desc [tx_tail].CSO = 0;
   tx_desc [tx_tail].CMD = 0x0B;
   tx_desc [tx_tail].STA = 0;
   tx_desc [tx_tail].CSS = 0;
   tx_desc [tx_tail].VLAN = 0;

   tx_tail++;
   tx_tail %= 256;
   cout << "sending client message..." << endl;
   csr.write_TDT (tx_tail);

   cout << "waiting for server message..." << endl;
   while (0 == rx_desc [rx_head].status);
   cout << "received server message..." << endl;

   verify_data_numeric (&rx_buffer [14], LENGTH);

   rx_head++;
   rx_head %= 256;
   rx_desc [rx_head].buffer = rx_buffer_machine_address;
   rx_desc [rx_head].status = 0;
   rx_tail++;
   rx_tail %= 256;
   csr.write_RDT (rx_tail);

   for (unsigned long i = 0; i < TRIALS; i++)
   {
      // send/recv mesg, check first "int" in buffer is the trial number just
      // as a low cost sanity check to verify both machines are in sync
      tx_desc [tx_tail].buffer = buffer_machine_address;
      tx_desc [tx_tail].length = 14 + LENGTH + 4;
      tx_desc [tx_tail].CSO = 0;
      tx_desc [tx_tail].CMD = 0x0B;
      tx_desc [tx_tail].STA = 0;
      tx_desc [tx_tail].CSS = 0;
      tx_desc [tx_tail].VLAN = 0;

      tx_tail++;
      tx_tail %= 256;
      csr.write_TDT (tx_tail);

      while (0 == rx_desc [rx_head].status);

      if (*(reinterpret_cast<unsigned long *>(&rx_buffer[14])) != i)
      {
         cout << "invalid trial number: " << i << endl;
      }

      rx_head++;
      rx_head %= 256;
      rx_desc [rx_head].buffer = rx_buffer_machine_address;
      rx_desc [rx_head].status = 0;
      rx_tail++;
      rx_tail %= 256;
      csr.write_RDT (rx_tail);
   }

   // marks all bytes with alpha chars (a,b,c,...)
   mark_data_alpha (&tx_buffer [14], LENGTH);

   // send/recv and verify the data has been changed to numerals (1,2,3,...)
   tx_desc [tx_tail].buffer = buffer_machine_address;
   tx_desc [tx_tail].length = 14 + LENGTH + 4;
   tx_desc [tx_tail].CSO = 0;
   tx_desc [tx_tail].CMD = 0x0B;
   tx_desc [tx_tail].STA = 0;
   tx_desc [tx_tail].CSS = 0;
   tx_desc [tx_tail].VLAN = 0;

   tx_tail++;
   tx_tail %= 256;
   csr.write_TDT (tx_tail);

   while (0 == rx_desc [rx_head].status);

   verify_data_numeric (&rx_buffer [14], LENGTH);

   rx_head++;
   rx_head %= 256;
   rx_desc [rx_head].buffer = rx_buffer_machine_address;
   rx_desc [rx_head].status = 0;
   rx_tail++;
   rx_tail %= 256;
   csr.write_RDT (rx_tail);

#endif




#if 0
   cout << "waiting for packet arrival..." << endl;
   while (0 == rx_desc->status)
   {
      if (csr.read_RDH() > 0)
      {
         cout << "RDH is non-zero!" << endl;
         break;
      }

      cout << "DESC status: " << rx_desc->status << endl;
      cout << "FIFO head: " << (csr.read(0x02410) & 0x1FFF) << endl;
      cout << "FIFO tail: " << (csr.read(0x02418) & 0x1FFF) << endl;
      cout << "Missed: " << csr.read(0x04010) << endl;
      cout << "Good: " << csr.read(0x04074) << endl;
      cout << "Broadcasst: " << csr.read(0x04078) << endl;
      cout << "Multicast: " << csr.read(0x0407C) << endl;
      sleep (1);
   }

   cout << "RD Status: " << static_cast<unsigned int>(rx_desc->status) << endl;
   cout << "RD data[]:" << endl;

   for (int i = 0; i < rx_desc->length; i++)
   {
         char *data = rx_buffer [0];
         cout << hex << (static_cast<unsigned int>(data [i]) & 0xFF) << " ";
   }

   cout << endl;


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
#endif

#endif

   cout << "waiting 5 sec, then exit..." << endl;
   cout.flush ();
   sleep (5);

   return 0;
}

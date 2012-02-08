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

#include <llamaos/memory/memory.h>
#include <llamaos/net/e1000e/CSR.h>
#include <llamaos/xen/Hypercall.h>
#include <llamaos/config.h>

using namespace std;
using namespace llamaos;
using namespace llamaos::memory;
using namespace llamaos::net::e1000e;
using namespace llamaos::xen;

// !!! stolen from Linux !!!
# define __force
# define __iomem

#define build_mmio_read(name, size, type, reg, barrier) \
static inline type name(const volatile void __iomem *addr) \
{ type ret; asm volatile("mov" size " %1,%0":reg (ret) \
:"m" (*(volatile type __force *)addr) barrier); return ret; }

#define build_mmio_write(name, size, type, reg, barrier) \
static inline void name(type val, volatile void __iomem *addr) \
{ asm volatile("mov" size " %0,%1": :reg (val), \
"m" (*(volatile type __force *)addr) barrier); }

build_mmio_read(readb, "b", unsigned char, "=q", :"memory")
build_mmio_read(readw, "w", unsigned short, "=r", :"memory")
build_mmio_read(readl, "l", unsigned int, "=r", :"memory")

build_mmio_read(__readb, "b", unsigned char, "=q", )
build_mmio_read(__readw, "w", unsigned short, "=r", )
build_mmio_read(__readl, "l", unsigned int, "=r", )

build_mmio_write(writeb, "b", unsigned char, "q", :"memory")
build_mmio_write(writew, "w", unsigned short, "r", :"memory")
build_mmio_write(writel, "l", unsigned int, "r", :"memory")

build_mmio_write(__writeb, "b", unsigned char, "q", )
build_mmio_write(__writew, "w", unsigned short, "r", )
build_mmio_write(__writel, "l", unsigned int, "r", )

static inline bool tst_bit (uint32_t value, uint32_t mask)
{
   return !!(value & mask);
}

static inline void chg_bit (uint32_t value, uint32_t mask, bool flag)
{
   if (flag)
   {
      value |= mask;
   }
   else
   {
      value &= ~mask;
   }
}

const uint32_t Device_control::FD = (1 << 0);
const uint32_t Device_control::GIO_MASTER_DISABLE = (1 << 2);
const uint32_t Device_control::ASDE = (1 << 5);
const uint32_t Device_control::SLU = (1 << 6);
const uint32_t Device_control::SPEED1 = (1 << 8);
const uint32_t Device_control::SPEED2 = (1 << 9);
const uint32_t Device_control::FRCSPD = (1 << 11);
const uint32_t Device_control::FRCDPLX = (1 << 12);
const uint32_t Device_control::ADVD3WUC = (1 << 20);
const uint32_t Device_control::RST = (1 << 26);
const uint32_t Device_control::RFCE = (1 << 27);
const uint32_t Device_control::TFCE = (1 << 28);
const uint32_t Device_control::VME = (1 << 30);
const uint32_t Device_control::PHY_RST = (1 << 31);

Device_control::Device_control (uint32_t value)
   :  value(value)
{

}

Device_control::~Device_control ()
{

}

bool Device_control::get_FD () const
{
   return tst_bit (value, FD);
}

void Device_control::set_FD (bool flag)
{
   chg_bit (value, FD, flag);
}

bool Device_control::get_GIO_master_disable () const
{
   return tst_bit (value, GIO_MASTER_DISABLE);
}

void Device_control::set_GIO_master_disable (bool flag)
{
   chg_bit (value, GIO_MASTER_DISABLE, flag);
}

bool Device_control::get_ASDE () const
{
   return tst_bit (value, ASDE);
}

void Device_control::set_ASDE (bool flag)
{
   chg_bit (value, ASDE, flag);
}

bool Device_control::get_SLU () const
{
   return tst_bit (value, SLU);
}

void Device_control::set_SLU (bool flag)
{
   chg_bit (value, SLU, flag);
}

Device_control::SPEED Device_control::get_SPEED () const
{
   if (tst_bit (value, SPEED2))
   {
      return SPEED_1000MBS;
   }
   else if (tst_bit (value, SPEED1))
   {
      return SPEED_100MBS;
   }

   return SPEED_10MBS;
}

void Device_control::set_SPEED (SPEED speed)
{
   switch (speed)
   {
   default:
   case SPEED_10MBS:
      chg_bit (value, SPEED1, false);
      chg_bit (value, SPEED2, false);
      break;

   case SPEED_100MBS:
      chg_bit (value, SPEED1, true);
      chg_bit (value, SPEED2, false);
      break;

   case SPEED_1000MBS:
      chg_bit (value, SPEED1, false);
      chg_bit (value, SPEED2, true);
      break;
   }
}

bool Device_control::get_FRCSPD () const
{
   return tst_bit (value, FRCSPD);
}

void Device_control::set_FRCSPD (bool flag)
{
   chg_bit (value, FRCSPD, flag);
}

bool Device_control::get_FRCDPLX () const
{
   return tst_bit (value, FRCDPLX);
}

void Device_control::set_FRCDPLX (bool flag)
{
   chg_bit (value, FRCDPLX, flag);
}

bool Device_control::get_ADVD3WUC () const
{
   return tst_bit (value, ADVD3WUC);
}

void Device_control::set_ADVD3WUC (bool flag)
{
   chg_bit (value, ADVD3WUC, flag);
}

bool Device_control::get_RST () const
{
   return tst_bit (value, RST);
}

void Device_control::set_RST (bool flag)
{
   chg_bit (value, RST, flag);
}

bool Device_control::get_RFCE () const
{
   return tst_bit (value, RFCE);
}

void Device_control::set_RFCE (bool flag)
{
   chg_bit (value, RFCE, flag);
}

bool Device_control::get_TFCE () const
{
   return tst_bit (value, TFCE);
}

void Device_control::set_TFCE (bool flag)
{
   chg_bit (value, TFCE, flag);
}

bool Device_control::get_VME () const
{
   return tst_bit (value, VME);
}

void Device_control::set_VME (bool flag)
{
   chg_bit (value, VME, flag);
}

bool Device_control::get_PHY_RST () const
{
   return tst_bit (value, PHY_RST);
}

void Device_control::set_PHY_RST (bool flag)
{
   chg_bit (value, PHY_RST, flag);
}

const uint32_t Device_status::FD = (1 << 0);
const uint32_t Device_status::LU = (1 << 1);
const uint32_t Device_status::TXOFF = (1 << 4);
const uint32_t Device_status::SPEED1 = (1 << 6);
const uint32_t Device_status::SPEED2 = (1 << 7);
const uint32_t Device_status::ASDV1 = (1 << 8);
const uint32_t Device_status::ASDV2 = (1 << 9);
const uint32_t Device_status::PHYRA = (1 << 10);
const uint32_t Device_status::GIO_MASTER_ENABLED = (1 << 19);

Device_status::Device_status (uint32_t value)
   :  value(value)
{

}

Device_status::~Device_status ()
{

}

bool Device_status::get_FD () const
{
   return tst_bit (value, FD);
}

bool Device_status::get_LU () const
{
   return tst_bit (value, LU);
}

bool Device_status::get_TXOFF () const
{
   return tst_bit (value, TXOFF);
}

Device_status::SPEED Device_status::get_SPEED () const
{
   if (tst_bit (value, SPEED2))
   {
      return SPEED_1000MBS;
   }
   else if (tst_bit (value, SPEED1))
   {
      return SPEED_100MBS;
   }

   return SPEED_10MBS;
}

Device_status::SPEED Device_status::get_ASDV () const
{
   if (tst_bit (value, ASDV2))
   {
      return SPEED_1000MBS;
   }
   else if (tst_bit (value, ASDV1))
   {
      return SPEED_100MBS;
   }

   return SPEED_10MBS;
}

bool Device_status::get_PHYRA () const
{
   return tst_bit (value, PHYRA);
}

bool Device_status::get_GIO_MASTER_ENABLED () const
{
   return tst_bit (value, GIO_MASTER_ENABLED);
}

CSR::CSR (uint64_t machine_address, uint64_t virtual_address)
   :  pointer(address_to_pointer<uint8_t>(virtual_address))
{
   // mapping 128k
   for (uint64_t i = 0; i < 32; i++)
   {
      uint64_t offset = (i * PAGE_SIZE);
      Hypercall::update_va_mapping_nocache (virtual_address + offset, machine_address + offset);
   }
}

CSR::~CSR ()
{

}

uint32_t CSR::read (uint64_t offset) const
{
   return readl(pointer + offset);
}

void CSR::write (uint64_t offset, uint32_t value)
{
   writel (value, pointer + offset);
}

Device_control CSR::read_CTRL () const
{
   uint32_t value = readl(pointer + 0x00000);

   return Device_control (value);
}

void CSR::write_CTRL (const Device_control &CTRL)
{
   writel (CTRL.value, pointer + 0x00000);
}

Device_status CSR::read_STATUS () const
{
   uint32_t value = readl (pointer + 0x00008);

   return Device_status (value);
}

namespace llamaos {
namespace net {
namespace e1000e {

ostream &operator<< (ostream &out, const Device_control &CTRL)
{
   out << "Device control" << endl;
   out << "  FD: " << CTRL.get_FD () << " (" << ((CTRL.get_FD ()) ? "Full" : "Half") << " duplex)" << endl;
   out << "  GIO master disable: " << CTRL.get_GIO_master_disable () << endl;
   out << "  ASDE: " << CTRL.get_ASDE () << endl;
   out << "  SLU: " << CTRL.get_SLU () << endl;

   out << "  SPEED: " << CTRL.get_SPEED ();

   switch (CTRL.get_SPEED ())
   {
   default:
   case Device_control::SPEED_10MBS:
      out << " (10 MB/S)" << endl;
      break;

   case Device_control::SPEED_100MBS:
      out << " (100 MB/S)" << endl;
      break;

   case Device_control::SPEED_1000MBS:
      out << " (1000 MB/S)" << endl;
      break;
   }

   out << "  FRCSPD: " << CTRL.get_FRCSPD () << endl;
   out << "  FRCDPLX: " << CTRL.get_FRCDPLX () << endl;
   out << "  ADVD3WUC: " << CTRL.get_ADVD3WUC () << endl;
   out << "  RST: " << CTRL.get_RST () << endl;
   out << "  RFCE: " << CTRL.get_RFCE () << endl;
   out << "  TFCE: " << CTRL.get_TFCE () << endl;
   out << "  VME: " << CTRL.get_VME () << endl;
   out << "  PHY_RST: " << CTRL.get_PHY_RST () << endl;

   return out;
}

ostream &operator<< (std::ostream &out, const Device_status &STATUS)
{
   out << "Device status" << endl;
   out << "  FD: " << STATUS.get_FD () << " (" << ((STATUS.get_FD ()) ? "Full" : "Half") << " duplex)" << endl;
   out << "  LU: " << STATUS.get_LU () << " (" << ((STATUS.get_LU ()) ? "Link up" : "Link down") << " )" << endl;
   out << "  TXOFF: " << STATUS.get_TXOFF () << endl;

   out << "  SPEED: " << STATUS.get_SPEED ();

   switch (STATUS.get_SPEED ())
   {
   default:
   case Device_control::SPEED_10MBS:
      out << " (10 MB/S)" << endl;
      break;

   case Device_control::SPEED_100MBS:
      out << " (100 MB/S)" << endl;
      break;

   case Device_control::SPEED_1000MBS:
      out << " (1000 MB/S)" << endl;
      break;
   }

   out << "  ASDV: " << STATUS.get_ASDV ();

   switch (STATUS.get_ASDV ())
   {
   default:
   case Device_control::SPEED_10MBS:
      out << " (10 MB/S)" << endl;
      break;

   case Device_control::SPEED_100MBS:
      out << " (100 MB/S)" << endl;
      break;

   case Device_control::SPEED_1000MBS:
      out << " (1000 MB/S)" << endl;
      break;
   }

   out << "  PHYRA: " << STATUS.get_PHYRA () << endl;
   out << "  GIO master enabled: " << STATUS.get_GIO_MASTER_ENABLED () << endl;

   return out;
}

} } }

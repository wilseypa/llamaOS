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
   :  pointer(address_to_pointer<uint32_t>(virtual_address))
{
   // mapping 128k
   for (unsigned int i = 0; i < 32; i++)
   {
      unsigned int offset = (i * PAGE_SIZE);
      Hypercall::update_va_mapping (virtual_address + offset, machine_address + offset);
   }
}

CSR::~CSR ()
{

}

uint32_t CSR::read (uint64_t offset) const
{
   return pointer [offset];
}

void CSR::write (uint64_t offset, uint32_t value)
{
   pointer [offset] = value;
}

Device_control CSR::read_CTRL () const
{
   return Device_control (pointer [0x00000]);
}

void CSR::write_CTRL (const Device_control &CTRL)
{
   pointer [0x00000] = CTRL.value;
}

Device_status CSR::read_STATUS () const
{
   return Device_status (pointer [0x00008]);
}

namespace llamaos {
namespace net {
namespace e1000e {

ostream &operator<< (ostream &out, const Device_control &CTRL)
{
   out << "Device control" << endl;
   out << "  FD: " << CTRL.get_FD () << " (" << ((CTRL.get_FD ()) ? "Full" : "Half") << " duplex)";

   return out;
}

ostream &operator<< (std::ostream &out, const Device_status &STATUS)
{
   out << "Device status" << endl;
   out << "  FD: " << STATUS.get_FD () << " (" << ((STATUS.get_FD ()) ? "Full" : "Half") << " duplex)";

   return out;
}

} } }

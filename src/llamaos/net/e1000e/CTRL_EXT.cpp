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

#include <llamaos/net/e1000e/CTRL_EXT.h>
#include <llamaos/net/e1000e/IO.h>

using namespace llamaos::net::e1000e;

CTRL_EXT::CTRL_EXT (uint32_t value)
   :  value(value)
{

}

CTRL_EXT::operator uint32_t () const
{
   return value;
}

bool CTRL_EXT::ASDCHK () const
{
   return tst_bit (value, (1 << 12));
}

void CTRL_EXT::ASDCHK (bool flag)
{
   chg_bit (value, (1 << 12), flag);
}

bool CTRL_EXT::EE_RST () const
{
   return tst_bit (value, (1 << 13));
}

void CTRL_EXT::EE_RST (bool flag)
{
   chg_bit (value, (1 << 13), flag);
}

bool CTRL_EXT::SPD_BYPS () const
{
   return tst_bit (value, (1 << 15));
}

void CTRL_EXT::SPD_BYPS (bool flag)
{
   chg_bit (value, (1 << 15), flag);
}

bool CTRL_EXT::RO_DIS () const
{
   return tst_bit (value, (1 << 17));
}

void CTRL_EXT::RO_DIS (bool flag)
{
   chg_bit (value, (1 << 17), flag);
}

bool CTRL_EXT::DMA_DGE () const
{
   return tst_bit (value, (1 << 19));
}

void CTRL_EXT::DMA_DGE (bool flag)
{
   chg_bit (value, (1 << 19), flag);
}

bool CTRL_EXT::PHY_PDE () const
{
   return tst_bit (value, (1 << 20));
}

void CTRL_EXT::PHY_PDE (bool flag)
{
   chg_bit (value, (1 << 20), flag);
}

bool CTRL_EXT::TX_LS_FLOW () const
{
   return tst_bit (value, (1 << 22));
}

void CTRL_EXT::TX_LS_FLOW (bool flag)
{
   chg_bit (value, (1 << 22), flag);
}

bool CTRL_EXT::TX_LS () const
{
   return tst_bit (value, (1 << 23));
}

void CTRL_EXT::TX_LS (bool flag)
{
   chg_bit (value, (1 << 23), flag);
}

bool CTRL_EXT::EIAME () const
{
   return tst_bit (value, (1 << 24));
}

void CTRL_EXT::EIAME (bool flag)
{
   chg_bit (value, (1 << 24), flag);
}

bool CTRL_EXT::IAME () const
{
   return tst_bit (value, (1 << 27));
}

void CTRL_EXT::IAME (bool flag)
{
   chg_bit (value, (1 << 27), flag);
}

bool CTRL_EXT::DRV_LOAD () const
{
   return tst_bit (value, (1 << 28));
}

void CTRL_EXT::DRV_LOAD (bool flag)
{
   chg_bit (value, (1 << 28), flag);
}

bool CTRL_EXT::INT_TIMERS_CLEAR_ENA () const
{
   return tst_bit (value, (1 << 29));
}

void CTRL_EXT::INT_TIMERS_CLEAR_ENA (bool flag)
{
   chg_bit (value, (1 << 29), flag);
}

bool CTRL_EXT::PBA_SUPPORT () const
{
   return tst_bit (value, (1 << 31));
}

void CTRL_EXT::PBA_SUPPORT (bool flag)
{
   chg_bit (value, (1 << 31), flag);
}

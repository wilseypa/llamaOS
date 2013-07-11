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

#include <apps/net/intel/regs/CTRL_EXT.h>

using std::endl;
using std::ostream;

using apps::net::intel::regs::CTRL_EXT;

CTRL_EXT::CTRL_EXT (uint32_t value)
   :  value(value)
{

}

CTRL_EXT::operator uint32_t () const
{
   return value.to_ulong ();
}

bool CTRL_EXT::ASDCHK () const
{
   return value [12];
}

void CTRL_EXT::ASDCHK (bool flag)
{
   value [12] = flag;
}

bool CTRL_EXT::EE_RST () const
{
   return value [13];
}

void CTRL_EXT::EE_RST (bool flag)
{
   value [13] = flag;
}

bool CTRL_EXT::SPD_BYPS () const
{
   return value [15];
}

void CTRL_EXT::SPD_BYPS (bool flag)
{
   value [15] = flag;
}

bool CTRL_EXT::RO_DIS () const
{
   return value [17];
}

void CTRL_EXT::RO_DIS (bool flag)
{
   value [17] = flag;
}

bool CTRL_EXT::DMA_dynamic_gating_enable () const
{
   return value [19];
}

void CTRL_EXT::DMA_dynamic_gating_enable (bool flag)
{
   value [19] = flag;
}

bool CTRL_EXT::PHY_power_down_enable () const
{
   return value [20];
}

void CTRL_EXT::PHY_power_down_enable (bool flag)
{
   value [20] = flag;
}

bool CTRL_EXT::TX_LS_FLOW () const
{
   return value [22];
}

void CTRL_EXT::TX_LS_FLOW (bool flag)
{
   value [22] = flag;
}

bool CTRL_EXT::TX_LS () const
{
   return value [23];
}

void CTRL_EXT::TX_LS (bool flag)
{
   value [23] = flag;
}

bool CTRL_EXT::EIAME () const
{
   return value [24];
}

void CTRL_EXT::EIAME (bool flag)
{
   value [24] = flag;
}

bool CTRL_EXT::IAME () const
{
   return value [27];
}

void CTRL_EXT::IAME (bool flag)
{
   value [27] = flag;
}

bool CTRL_EXT::DRV_LOAD () const
{
   return value [28];
}

void CTRL_EXT::DRV_LOAD (bool flag)
{
   value [28] = flag;
}

bool CTRL_EXT::INT_TIMERS_CLEAR_ENA () const
{
   return value [29];
}

void CTRL_EXT::INT_TIMERS_CLEAR_ENA (bool flag)
{
   value [29] = flag;
}

bool CTRL_EXT::PBA_SUPPORT () const
{
   return value [31];
}

void CTRL_EXT::PBA_SUPPORT (bool flag)
{
   value [31] = flag;
}

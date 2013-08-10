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

#include <apps/net/intel/regs/TCTL.h>

using std::endl;
using std::ostream;

using apps::net::intel::regs::TCTL;

TCTL::TCTL (uint32_t value)
   :  value(value & 0x7FFFFFFA)    // mask reserved bits
{
   
}

TCTL::operator uint32_t () const
{
   return value.to_ulong ();
}

bool TCTL::EN () const
{
   return value [1];
}

void TCTL::EN (bool flag)
{
   value [1] = flag;
}

bool TCTL::PSP () const
{
   return value [3];
}

void TCTL::PSP (bool flag)
{
   value [3] = flag;
}

uint8_t TCTL::CT () const
{
   return (value.to_ulong() & 0xFF0) >> 4;
}

void TCTL::CT (uint8_t threshold)
{
   value &= ~(0xFF0);
   value |= (0xFF0 & (threshold << 4));
}

uint16_t TCTL::COLD () const
{
   return (value.to_ulong() & 0x3FF000) >> 12;
}

void TCTL::COLD (uint16_t distance)
{
   value &= ~(0x3FF000);
   value |= (0x3FF000 & (distance << 12));
}

bool TCTL::SWXOFF () const
{
   return value [22];
}

void TCTL::SWXOFF (bool flag)
{
   value [22] = flag;
}

bool TCTL::PBE () const
{
   return value [23];
}

void TCTL::PBE (bool flag)
{
   value [23] = flag;
}

bool TCTL::RTLC () const
{
   return value [24];
}

void TCTL::RTLC (bool flag)
{
   value [24] = flag;
}

bool TCTL::UNORTX () const
{
   return value [25];
}

void TCTL::UNORTX (bool flag)
{
   value [25] = flag;
}

uint8_t TCTL::TXDSCMT () const
{
   return (value.to_ulong() & 0xC000000) >> 26;
}

void TCTL::TXDSCMT (uint8_t threshold)
{
   value &= ~(0xC000000);
   value |= (0xC000000 & (threshold << 26));
}

bool TCTL::MULR () const
{
   return value [28];
}

void TCTL::MULR (bool flag)
{
   value [28] = flag;
}

TCTL::RRTHRESH_enum TCTL::RRTHRESH () const
{
   if (value [30])
   {
      if (value [29])
      {
         return RRTHRESH_none;
      }
      else
      {
         return RRTHRESH_8_lines;
      }
   }
   else
   {
      if (value [29])
      {
         return RRTHRESH_4_lines;
      }
      else
      {
         return RRTHRESH_2_lines;
      }
   }
}

void TCTL::RRTHRESH (TCTL::RRTHRESH_enum threshold)
{
   switch (threshold)
   {
      default:
      case RRTHRESH_2_lines:
         value [29] = false;
         value [30] = false;
         break;

      case RRTHRESH_4_lines:
         value [29] = true;
         value [30] = false;
         break;

      case RRTHRESH_8_lines:
         value [29] = false;
         value [30] = true;
         break;

      case RRTHRESH_none:
         value [29] = true;
         value [30] = true;
         break;
   }
}

ostream &operator<< (ostream &out, const TCTL &tctl)
{
   out << "Transmit control" << endl;
   out << "  EN: " << tctl.EN () << endl;
   out << "  PSP: " << tctl.PSP() << endl;
   out << "  CT: " << tctl.CT() << endl;
   out << "  COLD: " << tctl.COLD() << endl;
   out << "  SWXOFF: " << tctl.SWXOFF() << endl;
   out << "  PBE: " << tctl.COLD() << endl;
   out << "  RTLC: " << tctl.COLD() << endl;
   out << "  UNORTX: " << tctl.COLD() << endl;
   out << "  TXDSCMT: " << tctl.COLD() << endl;
   out << "  MULR: " << tctl.COLD() << endl;
   out << "  RRTHRESH: ";

   switch (tctl.RRTHRESH())
   {
      default:
      case TCTL::RRTHRESH_2_lines:
         out << "2 lines" << endl;
         break;

      case TCTL::RRTHRESH_4_lines:
         out << "4 lines" << endl;
         break;

      case TCTL::RRTHRESH_8_lines:
         out << "8 lines" << endl;
         break;

      case TCTL::RRTHRESH_none:
         out << "no threshold" << endl;
         break;
   }

   return out;
}

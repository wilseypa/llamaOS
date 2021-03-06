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

#include <apps/net/intel/regs/TXDCTL.h>

using std::endl;
using std::ostream;

using apps::net::intel::regs::TXDCTL;

TXDCTL::TXDCTL (uint32_t value)
   :  value(value & 0xFF3F3F3F)    // mask reserved bits
{
   
}

TXDCTL::operator uint32_t () const
{
   return value;
}

uint8_t TXDCTL::PTHRESH () const
{
   return (value & 0x3F);
}

void TXDCTL::PTHRESH (uint8_t threshold)
{
   value &= ~(0x3F);
   value |= (threshold & 0x3F);
}

uint8_t TXDCTL::HTHRESH () const
{
   return ((value >> 8) & 0x3F);
}

void TXDCTL::HTHRESH (uint8_t threshold)
{
   value &= ~(0x3F00);
   value |= ((threshold << 8) & 0x3F00);
}

uint8_t TXDCTL::WTHRESH () const
{
   return ((value >> 16) & 0x3F);
}

void TXDCTL::WTHRESH (uint8_t threshold)
{
   value &= ~(0x3F0000);
   value |= ((threshold << 16) & 0x3F0000);
}

bool TXDCTL::GRAN () const
{
   return ((value & 0x1000000) != 0);
}

void TXDCTL::GRAN (bool flag)
{
   if (flag)
   {
      value |= 0x1000000;
   }
   else
   {
      value &= ~0x1000000;
   }
}

uint8_t TXDCTL::LWTHRESH () const
{
   return ((value >> 16) & 0xFE);
}

void TXDCTL::LWTHRESH (uint8_t threshold)
{
   value &= ~(0xFE000000);
   value |= ((threshold << 25) & 0xFE000000);
}

ostream &operator<< (ostream &out, const TXDCTL &txdctl)
{
   out << "Transmit Descriptor Control" << endl;
   out << "  PTHRESH: " << txdctl.PTHRESH () << endl;
   out << "  HTHRESH: " << txdctl.HTHRESH () << endl;
   out << "  WTHRESH: " << txdctl.WTHRESH () << endl;
   out << "     GRAN: " << txdctl.GRAN () << endl;
   out << " LWTHRESH: " << txdctl.LWTHRESH () << endl;

   return out;
}

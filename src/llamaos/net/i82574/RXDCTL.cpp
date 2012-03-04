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

#include <llamaos/api/bit.h>
#include <llamaos/net/i82574/RXDCTL.h>

using namespace llamaos::api;
using namespace llamaos::net::i82574;

RXDCTL::RXDCTL (uint32_t value)
   :  value(value)
{

}

RXDCTL::operator uint32_t () const
{
   return value;
}

uint8_t RXDCTL::PTHRESH () const
{
   return static_cast<uint8_t>(value & 0x3F);
}

void RXDCTL::PTHRESH (uint8_t t)
{
   value &= 0xFFFFFFC0;
   t &= 0x3F;
   value |= t;
}

uint8_t RXDCTL::HTHRESH () const
{
   return static_cast<uint8_t>((value >> 8) & 0x3F);
}

void RXDCTL::HTHRESH (uint8_t t)
{
   value &= 0xFFFFC0FF;
   t &= 0x3F;
   value |= (t << 8);
}

uint8_t RXDCTL::WTHRESH () const
{
   return static_cast<uint8_t>((value >> 16) & 0x3F);
}

void RXDCTL::WTHRESH (uint8_t t)
{
   value &= 0xFFC0FFFF;
   t &= 0x3F;
   value |= (t << 16);
}

bool RXDCTL::GRAN () const
{
   return test_bit (value, 24);
}

void RXDCTL::GRAN (bool flag)
{
   edit_bit (value, 24, flag);
}

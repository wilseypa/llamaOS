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
#include <llamaos/net/i82574/TCTL.h>

using namespace llamaos::api;
using namespace llamaos::net::i82574;

TCTL::TCTL (uint32_t value)
   :  value(value)
{

}

TCTL::operator uint32_t () const
{
   return value;
}

bool TCTL::EN () const
{
   return test_bit (value, 1);
}

void TCTL::EN (bool flag)
{
   edit_bit (value, 1, flag);
}

bool TCTL::PSP () const
{
   return test_bit (value, 3);
}

void TCTL::PSP (bool flag)
{
   edit_bit (value, 3, flag);
}

uint8_t TCTL::CT () const
{
   return static_cast<uint8_t>(value >> 4);
}

void TCTL::CT (uint8_t n)
{
   value &= 0xFFFFF00F;
   value |= (n << 4);
}

uint16_t TCTL::COLD () const
{
   return static_cast<uint16_t>((value >> 12) & 0x3FF);
}

void TCTL::COLD (uint16_t t)
{
   value &= 0xFFC00FFF;
   t &= 0x3FF;
   value |= (t << 12);
}

bool TCTL::SWXOFF () const
{
   return test_bit (value, 22);
}

void TCTL::SWXOFF (bool flag)
{
   edit_bit (value, 22, flag);
}

bool TCTL::PBE () const
{
   return test_bit (value, 23);
}

void TCTL::PBE (bool flag)
{
   edit_bit (value, 23, flag);
}

bool TCTL::RTLC () const
{
   return test_bit (value, 24);
}

void TCTL::RTLC (bool flag)
{
   edit_bit (value, 24, flag);
}

bool TCTL::UNORTX () const
{
   return test_bit (value, 25);
}

void TCTL::UNORTX (bool flag)
{
   edit_bit (value, 25, flag);
}

// unsigned int TCTL::TXDSCMT () const
// void TCTL::TXDSCMT (unsigned int t)

bool TCTL::MULR () const
{
   return test_bit (value, 28);
}

void TCTL::MULR (bool flag)
{
   edit_bit (value, 28, flag);
}

TCTL::READ_REQUEST_THREAHOLD TCTL::RRTHRESH () const
{
   if (test_bit (value, 30))
   {
      return test_bit (value, 29) ? THREASHOLD_NONE : THREASHOLD_8_LINES;
   }
   else
   {
      return test_bit (value, 29) ? THREASHOLD_4_LINES : THREASHOLD_2_LINES;
   }
}

void TCTL::RRTHRESH (TCTL::READ_REQUEST_THREAHOLD rrt)
{
   switch (rrt)
   {
   default:
   case THREASHOLD_2_LINES:
      reset_bit (value, 29);
      reset_bit (value, 30);
      break;
   case THREASHOLD_4_LINES:
      set_bit (value, 29);
      reset_bit (value, 30);
      break;
   case THREASHOLD_8_LINES:
      reset_bit (value, 29);
      set_bit (value, 30);
      break;
   case THREASHOLD_NONE:
      set_bit (value, 29);
      set_bit (value, 30);
      break;
   }
}
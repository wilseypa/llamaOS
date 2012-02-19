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
#include <llamaos/net/i82574/GCR.h>

using namespace std;
using namespace llamaos::api;
using namespace llamaos::net::i82574;

GCR::GCR (uint32_t value)
   :  value(value)
{

}

GCR::operator uint32_t () const
{
   return value;
}

bool GCR::RXD_NOSNOOP () const
{
   return test_bit (value, 0);
}

void GCR::RXD_NOSNOOP (bool flag)
{
   edit_bit (value, 0, flag);
}

bool GCR::RXDSCW_NOSNOOP () const
{
   return test_bit (value, 1);
}

void GCR::RXDSCW_NOSNOOP (bool flag)
{
   edit_bit (value, 1, flag);
}

bool GCR::RXDSCR_NOSNOOP () const
{
   return test_bit (value, 2);
}

void GCR::RXDSCR_NOSNOOP (bool flag)
{
   edit_bit (value, 2, flag);
}

bool GCR::TXD_NOSNOOP () const
{
   return test_bit (value, 3);
}

void GCR::TXD_NOSNOOP (bool flag)
{
   edit_bit (value, 3, flag);
}

bool GCR::TXDSCW_NOSNOOP () const
{
   return test_bit (value, 4);
}

void GCR::TXDSCW_NOSNOOP (bool flag)
{
   edit_bit (value, 4, flag);
}

bool GCR::TXDSCR_NOSNOOP () const
{
   return test_bit (value, 5);
}

void GCR::TXDSCR_NOSNOOP (bool flag)
{
   edit_bit (value, 5, flag);
}

bool GCR::RX_L0S_ADJUST () const
{
   return test_bit (value, 9);
}

void GCR::RX_L0S_ADJUST (bool flag)
{
   edit_bit (value, 9, flag);
}

bool GCR::PBA_CL_DEAS () const
{
   return test_bit (value, 20);
}

void GCR::PBA_CL_DEAS (bool flag)
{
   edit_bit (value, 20, flag);
}

bool GCR::HEADER_LOG_ORDER () const
{
   return test_bit (value, 21);
}

void GCR::HEADER_LOG_ORDER (bool flag)
{
   edit_bit (value, 21, flag);
}

bool GCR::INITIALIZE () const
{
   return test_bit (value, 22);
}

void GCR::INITIALIZE (bool flag)
{
   edit_bit (value, 22, flag);
}

GCR::L1_ENTRY_LATENCY GCR::L1_ENTRY_LAT () const
{
   if (test_bit (value, 23))
   {
      if (test_bit (value, 26))
      {
         return test_bit (value, 25) ? GCR::LATENCY_4MSEC : GCR::LATENCY_1MSEC;
      }
      else
      {
         return test_bit (value, 25) ? GCR::LATENCY_256USEC : GCR::LATENCY_64USEC;
      }
   }
   else
   {
      if (test_bit (value, 26))
      {
         return test_bit (value, 25) ? GCR::LATENCY_32USEC : GCR::LATENCY_16USEC;
      }
      else
      {
         return test_bit (value, 25) ? GCR::LATENCY_8USEC : GCR::LATENCY_2USEC;
      }
   }
}

void GCR::L1_ENTRY_LAT (GCR::L1_ENTRY_LATENCY latency)
{
   switch (latency)
   {
   default:
   case GCR::LATENCY_2USEC:
      reset_bit (value, 25);
      reset_bit (value, 26);
      reset_bit (value, 23);
      break;
   case GCR::LATENCY_8USEC:
      set_bit (value, 25);
      reset_bit (value, 26);
      reset_bit (value, 23);
      break;
   case GCR::LATENCY_16USEC:
      reset_bit (value, 25);
      set_bit (value, 26);
      reset_bit (value, 23);
      break;
   case GCR::LATENCY_32USEC:
      set_bit (value, 25);
      set_bit (value, 26);
      reset_bit (value, 23);
      break;

   case GCR::LATENCY_64USEC:
      reset_bit (value, 25);
      reset_bit (value, 26);
      set_bit (value, 23);
      break;
   case GCR::LATENCY_256USEC:
      set_bit (value, 25);
      reset_bit (value, 26);
      set_bit (value, 23);
      break;
   case GCR::LATENCY_1MSEC:
      reset_bit (value, 25);
      set_bit (value, 26);
      set_bit (value, 23);
      break;
   case GCR::LATENCY_4MSEC:
      set_bit (value, 25);
      set_bit (value, 26);
      set_bit (value, 23);
      break;
   }
}

bool GCR::L0S_ENTRY_LAT () const
{
   return test_bit (value, 24);
}

void GCR::L0S_ENTRY_LAT (bool flag)
{
   edit_bit (value, 24, flag);
}

bool GCR::L1_ACT_WITHOUT_L0S_RX () const
{
   return test_bit (value, 27);
}

void GCR::L1_ACT_WITHOUT_L0S_RX (bool flag)
{
   edit_bit (value, 27, flag);
}

bool GCR::GIO_DIS_RD_ERR () const
{
   return test_bit (value, 28);
}

void GCR::GIO_DIS_RD_ERR (bool flag)
{
   edit_bit (value, 28, flag);
}

bool GCR::GIO_GOOD_L0S () const
{
   return test_bit (value, 29);
}

void GCR::GIO_GOOD_L0S (bool flag)
{
   edit_bit (value, 29, flag);
}

bool GCR::SELF_TEST_RESULT () const
{
   return test_bit (value, 30);
}

void GCR::SELF_TEST_RESULT (bool flag)
{
   edit_bit (value, 30, flag);
}

bool GCR::DISABLE_TIMEOUT () const
{
   return test_bit (value, 31);
}

void GCR::DISABLE_TIMEOUT (bool flag)
{
   edit_bit (value, 31, flag);
}

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
#include <llamaos/net/i82574/RCTL.h>

using namespace llamaos::api;
using namespace llamaos::net::i82574;

RCTL::RCTL (uint32_t value)
   :  value(value)
{

}

RCTL::operator uint32_t () const
{
   return value;
}

bool RCTL::EN () const
{
   return test_bit (value, 1);
}

void RCTL::EN (bool flag)
{
   edit_bit (value, 1, flag);
}

bool RCTL::SBP () const
{
   return test_bit (value, 2);
}

void RCTL::SBP (bool flag)
{
   edit_bit (value, 2, flag);
}


bool RCTL::UPE () const
{
   return test_bit (value, 3);
}

void RCTL::UPE (bool flag)
{
   edit_bit (value, 3, flag);
}


bool RCTL::MPE () const
{
   return test_bit (value, 4);
}

void RCTL::MPE (bool flag)
{
   edit_bit (value, 4, flag);
}


bool RCTL::LPE () const
{
   return test_bit (value, 5);
}

void RCTL::LPE (bool flag)
{
   edit_bit (value, 5, flag);
}

RCTL::DESC_THRESHOLD RCTL::RDMTS () const
{
   if (test_bit (value, 9))
   {
      return EIGHTH;
   }
   else if (test_bit (value, 8))
   {
      return QUARTER;
   }

   return HALF;
}

void RCTL::RDMTS (RCTL::DESC_THRESHOLD rdt)
{
   switch (rdt)
   {
   default:
   case HALF:
      reset_bit (value, 8);
      reset_bit (value, 9);
      break;

   case QUARTER:
      set_bit (value, 8);
      reset_bit (value, 9);
      break;

   case EIGHTH:
      reset_bit (value, 8);
      set_bit (value, 9);
      break;
   }
}

   enum DESC_TYPE { LEGACY, SPLIT };

RCTL::DESC_TYPE RCTL::DTYP () const
{
   return test_bit (value, 10) ? LEGACY : SPLIT;
}

void RCTL::DTYP (RCTL::DESC_TYPE type)
{
   switch (type)
   {
   default:
   case LEGACY:
      reset_bit (value, 10);
      reset_bit (value, 11);
      break;

   case SPLIT:
      set_bit (value, 10);
      reset_bit (value, 11);
      break;
   }
}

bool RCTL::BAM () const
{
   return test_bit (value, 15);
}

void RCTL::BAM (bool flag)
{
   edit_bit (value, 15, flag);
}

RCTL::BUFFER_SIZE RCTL::BSIZE () const
{
   if (test_bit (value, 17))
   {
      return test_bit (value, 16) ? BYTES_256 : BYTES_512;
   }
   else
   {
      return test_bit (value, 16) ? BYTES_1024 : BYTES_2048;
   }
}

void RCTL::BSIZE (RCTL::BUFFER_SIZE size)
{
   switch (size)
   {
   default:
   case BYTES_2048:
      reset_bit (value, 16);
      reset_bit (value, 17);
      break;

   case BYTES_1024:
      set_bit (value, 16);
      reset_bit (value, 17);
      break;

   case BYTES_512:
      reset_bit (value, 16);
      set_bit (value, 17);
      break;

   case BYTES_256:
      set_bit (value, 16);
      set_bit (value, 17);
      break;
   }
}

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

#include <llamaos/api/bit.h>
#include <llamaos/net/i82574/SWSM.h>

using namespace std;
using namespace llamaos::api;
using namespace llamaos::net::i82574;

SWSM::SWSM (uint32_t value)
   :  value(value)
{

}

SWSM::operator uint32_t () const
{
   return value;
}

bool SWSM::SMBI () const
{
   return test_bit (value, 0);
}

void SWSM::SMBI (bool flag)
{
   edit_bit (value, 0, flag);
}

bool SWSM::SWESMBI () const
{
   return test_bit (value, 1);
}

void SWSM::SWESMBI (bool flag)
{
   edit_bit (value, 1, flag);
}

ostream &llamaos::net::i82574::operator<< (ostream &out, const SWSM &swsm)
{
   if (swsm.SMBI ())
   {
      out << "S/W owner";
   }
   else if (swsm.SWESMBI ())
   {
      out << "F/W owner";
   }
   else
   {
      out << "No owner";
   }

   return out;
}

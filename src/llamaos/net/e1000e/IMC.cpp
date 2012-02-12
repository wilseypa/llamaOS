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

#include <llamaos/net/e1000e/IMC.h>
#include <llamaos/net/e1000e/IO.h>

using namespace llamaos::net::e1000e;

const IMC IMC::ALL (0x1F782D7);

IMC::IMC ()
   :  value(0)
{

}

IMC::IMC (uint32_t value)
   :  value(value)
{

}

IMC::operator uint32_t () const
{
   return value;
}

bool IMC::TXDW () const
{
   return tst_bit (value, (1 << 0));
}

void IMC::TXDW (bool flag)
{
   chg_bit (value, (1 << 0), flag);
}

bool IMC::TXQE () const
{
   return tst_bit (value, (1 << 1));
}

void IMC::TXQE (bool flag)
{
   chg_bit (value, (1 << 1), flag);
}

bool IMC::LSC () const
{
   return tst_bit (value, (1 << 2));
}

void IMC::LSC (bool flag)
{
   chg_bit (value, (1 << 2), flag);
}

bool IMC::RXDMTO () const
{
   return tst_bit (value, (1 << 4));
}

void IMC::RXDMTO (bool flag)
{
   chg_bit (value, (1 << 4), flag);
}

bool IMC::RXO () const
{
   return tst_bit (value, (1 << 6));
}

void IMC::RXO (bool flag)
{
   chg_bit (value, (1 << 6), flag);
}

bool IMC::RXTO () const
{
   return tst_bit (value, (1 << 7));
}

void IMC::RXTO (bool flag)
{
   chg_bit (value, (1 << 7), flag);
}

bool IMC::MDAC () const
{
   return tst_bit (value, (1 << 9));
}

void IMC::MDAC (bool flag)
{
   chg_bit (value, (1 << 9), flag);
}

bool IMC::TXD_LOW () const
{
   return tst_bit (value, (1 << 15));
}

void IMC::TXD_LOW (bool flag)
{
   chg_bit (value, (1 << 15), flag);
}

bool IMC::SRPD () const
{
   return tst_bit (value, (1 << 16));
}

void IMC::SRPD (bool flag)
{
   chg_bit (value, (1 << 16), flag);
}

bool IMC::ACK () const
{
   return tst_bit (value, (1 << 17));
}

void IMC::ACK (bool flag)
{
   chg_bit (value, (1 << 17), flag);
}

bool IMC::MNG () const
{
   return tst_bit (value, (1 << 18));
}

void IMC::MNG (bool flag)
{
   chg_bit (value, (1 << 18), flag);
}

bool IMC::RXQ0 () const
{
   return tst_bit (value, (1 << 20));
}

void IMC::RXQ0 (bool flag)
{
   chg_bit (value, (1 << 20), flag);
}

bool IMC::RXQ1 () const
{
   return tst_bit (value, (1 << 21));
}

void IMC::RXQ1 (bool flag)
{
   chg_bit (value, (1 << 21), flag);
}

bool IMC::TXQ0 () const
{
   return tst_bit (value, (1 << 22));
}

void IMC::TXQ0 (bool flag)
{
   chg_bit (value, (1 << 22), flag);
}

bool IMC::TXQ1 () const
{
   return tst_bit (value, (1 << 23));
}

void IMC::TXQ1 (bool flag)
{
   chg_bit (value, (1 << 23), flag);
}

bool IMC::OTHER () const
{
   return tst_bit (value, (1 << 24));
}

void IMC::OTHER (bool flag)
{
   chg_bit (value, (1 << 24), flag);
}

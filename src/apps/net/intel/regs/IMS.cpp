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

#include <apps/net/intel/regs/IMS.h>

using std::endl;
using std::ostream;

using apps::net::intel::regs::IMS;

IMS::IMS (uint32_t value)
   :  value(value & 0x1F782D7)    // mask reserved bits
{
   
}

IMS::operator uint32_t () const
{
   return value.to_ulong ();
}

bool IMS::TXDW () const
{
   return value [0];
}

void IMS::TXDW (bool flag)
{
   value [0] = flag;
}

bool IMS::TXQE () const
{
   return value [1];
}

void IMS::TXQE (bool flag)
{
   value [1] = flag;
}

bool IMS::LSC () const
{
   return value [2];
}

void IMS::LSC (bool flag)
{
   value [2] = flag;
}

bool IMS::RXDMT0 () const
{
   return value [4];
}

void IMS::RXDMT0 (bool flag)
{
   value [4] = flag;
}

bool IMS::RXO () const
{
   return value [6];
}

void IMS::RXO (bool flag)
{
   value [6] = flag;
}

bool IMS::RXT0 () const
{
   return value [7];
}

void IMS::RXT0 (bool flag)
{
   value [7] = flag;
}

bool IMS::MDAC () const
{
   return value [9];
}

void IMS::MDAC (bool flag)
{
   value [9] = flag;
}

bool IMS::TXD_LOW () const
{
   return value [15];
}

void IMS::TXD_LOW (bool flag)
{
   value [15] = flag;
}

bool IMS::SRPD () const
{
   return value [16];
}

void IMS::SRPD (bool flag)
{
   value [16] = flag;
}

bool IMS::ACK () const
{
   return value [17];
}

void IMS::ACK (bool flag)
{
   value [17] = flag;
}

bool IMS::MNG () const
{
   return value [18];
}

void IMS::MNG (bool flag)
{
   value [18] = flag;
}

bool IMS::RxQ0 () const
{
   return value [20];
}

void IMS::RxQ0 (bool flag)
{
   value [20] = flag;
}

bool IMS::RxQ1 () const
{
   return value [21];
}

void IMS::RxQ1 (bool flag)
{
   value [21] = flag;
}

bool IMS::TxQ0 () const
{
   return value [22];
}

void IMS::TxQ0 (bool flag)
{
   value [22] = flag;
}

bool IMS::TxQ1 () const
{
   return value [23];
}

void IMS::TxQ1 (bool flag)
{
   value [23] = flag;
}

bool IMS::Other () const
{
   return value [24];
}

void IMS::Other (bool flag)
{
   value [24] = flag;
}

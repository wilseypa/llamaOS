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

#include <apps/net/intel/regs/IMC.h>

using std::endl;
using std::ostream;

using apps::net::intel::regs::IMC;

IMC::IMC (uint32_t value)
   :  value(value & 0x1F782D7)    // mask reserved bits
{
   
}

IMC::operator uint32_t () const
{
   return value.to_ulong ();
}

void IMC::TXDW (bool flag)
{
   value [0] = flag;
}

void IMC::TXQE (bool flag)
{
   value [1] = flag;
}

void IMC::LSC (bool flag)
{
   value [2] = flag;
}

void IMC::RXDMT0 (bool flag)
{
   value [4] = flag;
}

void IMC::RXO (bool flag)
{
   value [6] = flag;
}

void IMC::RXT0 (bool flag)
{
   value [7] = flag;
}

void IMC::MDAC (bool flag)
{
   value [9] = flag;
}

void IMC::TXD_LOW (bool flag)
{
   value [15] = flag;
}

void IMC::SRPD (bool flag)
{
   value [16] = flag;
}

void IMC::ACK (bool flag)
{
   value [17] = flag;
}

void IMC::MNG (bool flag)
{
   value [18] = flag;
}

void IMC::RxQ0 (bool flag)
{
   value [20] = flag;
}

void IMC::RxQ1 (bool flag)
{
   value [21] = flag;
}

void IMC::TxQ0 (bool flag)
{
   value [22] = flag;
}

void IMC::TxQ1 (bool flag)
{
   value [23] = flag;
}

void IMC::Other (bool flag)
{
   value [24] = flag;
}

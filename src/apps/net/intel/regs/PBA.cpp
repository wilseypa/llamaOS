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

#include <apps/net/intel/regs/PBA.h>

using std::endl;
using std::hex;
using std::ostream;

using apps::net::intel::regs::PBA;

PBA::PBA (uint32_t value)
   :  value(value)
{

}

PBA::operator uint32_t () const
{
   return value;
}

uint16_t PBA::RXA () const
{
   return value & 0xFFFF;
}

void PBA::RXA (uint16_t size)
{
   value &= (0xFFFF0000 | size);
}

uint16_t PBA::TXA () const
{
   return ((value >> 16) & 0xFFFF);
}

void PBA::TXA (uint16_t size)
{
   value &= (0x0000FFFF | (size << 16));
}

ostream &operator<< (ostream &out, const PBA &pba)
{
   out << "Packet Buffer Allocation" << endl;
   out << "  RXA: 0x" << hex << pba.RXA () << endl;
   out << "  TXA: 0x" << hex << pba.TXA () << endl;

   return out;
}

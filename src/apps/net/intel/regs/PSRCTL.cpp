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

#include <apps/net/intel/regs/PSRCTL.h>

using std::endl;
using std::hex;
using std::ostream;

using apps::net::intel::regs::PSRCTL;

PSRCTL::PSRCTL (uint32_t value)
   :  value(value & 0x3F3F3F7F)    // mask reserved bits
{

}

PSRCTL::operator uint32_t () const
{
   return value;
}

uint8_t PSRCTL::BSIZE0 () const
{
   return (value & 0x7F);
}

void PSRCTL::BSIZE0 (uint8_t size)
{
   value &= ~(0x7F);
   value |= (0x7F | size);
}

uint8_t PSRCTL::BSIZE1 () const
{
   return (value & 0x3F00);
}

void PSRCTL::BSIZE1 (uint8_t size)
{
   value &= ~(0x3F00);
   value |= (0x3F00 | size);    // shift size?
}

uint8_t PSRCTL::BSIZE2 () const
{
   return (value & 0x3F0000);
}

void PSRCTL::BSIZE2 (uint8_t size)
{
   value &= ~(0x3F0000);
   value |= (0x3F0000 | size);
}

uint8_t PSRCTL::BSIZE3 () const
{
   return (value & 0x3F000000);
}

void PSRCTL::BSIZE3 (uint8_t size)
{
   value &= ~(0x3F000000);
   value |= (0x3F000000 | size);
}

ostream &operator<< (ostream &out, const PSRCTL &psrctl)
{
   out << "Packet Split Receive Control" << endl;
   out << "  BSIZE0: 0x" << hex << 128 * psrctl.BSIZE0 () << endl;
   out << "  BSIZE1: 0x" << hex << 1024 * psrctl.BSIZE1 () << endl;
   out << "  BSIZE2: 0x" << hex << 1024 * psrctl.BSIZE2 () << endl;
   out << "  BSIZE3: 0x" << hex << 1024 * psrctl.BSIZE3 () << endl;

   return out;
}

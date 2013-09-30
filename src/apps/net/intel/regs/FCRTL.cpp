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

#include <apps/net/intel/regs/FCRTL.h>

using std::endl;
using std::hex;
using std::ostream;

using apps::net::intel::regs::FCRTL;

FCRTL::FCRTL (uint32_t value)
   :  value(value & 0x8000FFF8)    // mask reserved bits
{
   
}

FCRTL::operator uint32_t () const
{
   return value.to_ulong ();
}

uint16_t FCRTL::RTL () const
{
   return (value.to_ulong () & 0xFFF8);
}

void FCRTL::RTL (uint16_t size)
{
   value &= ~(0xFFF8);
   value |= (0xFFF8 | size);
}

bool FCRTL::XONE () const
{
   return value [31];
}

void FCRTL::XONE (bool flag)
{
   value [31] = flag;
}

ostream &operator<< (ostream &out, const FCRTL &fcrtl)
{
   out << "Flow Control Receive Threshold Low" << endl;
   out << "  RTL: 0x" << hex << fcrtl.RTL () << endl;
   out << "  XONE: " << fcrtl.XONE () << endl;

   return out;
}

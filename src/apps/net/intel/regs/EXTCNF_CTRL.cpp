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

#include <apps/net/intel/regs/EXTCNF_CTRL.h>

using std::endl;
using std::ostream;

using apps::net::intel::regs::EXTCNF_CTRL;

EXTCNF_CTRL::EXTCNF_CTRL (uint32_t value)
   :  value(value & 0xE0)    // mask reserved bits
                             // set 3rd bit per intel manual
{
   
}

EXTCNF_CTRL::operator uint32_t () const
{
   return value.to_ulong ();
}

bool EXTCNF_CTRL::MDIO_mng_ownership () const
{
   return value [7];
}

void EXTCNF_CTRL::MDIO_mng_ownership (bool flag)
{
   value [7] = flag;
}

bool EXTCNF_CTRL::MDIO_hw_ownership () const
{
   return value [6];
}

void EXTCNF_CTRL::MDIO_hw_ownership (bool flag)
{
   value [6] = flag;
}

bool EXTCNF_CTRL::MDIO_sw_ownership () const
{
   return value [5];
}

void EXTCNF_CTRL::MDIO_sw_ownership (bool flag)
{
   value [5] = flag;
}

ostream &operator<< (ostream &out, const EXTCNF_CTRL &extcnf_ctrl)
{
   out << "Extended Configuration Control" << endl;
   out << "  MDIO mng ownership: " << extcnf_ctrl.MDIO_mng_ownership () << endl;
   out << "  MDIO hw ownership: " << extcnf_ctrl.MDIO_hw_ownership () << endl;
   out << "  MDIO sw ownership: " << extcnf_ctrl.MDIO_sw_ownership () << endl;

   return out;
}

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

#include <apps/net/intel/regs/CTRL.h>

using std::endl;
using std::ostream;

using apps::net::intel::regs::CTRL;

CTRL::CTRL (uint32_t value)
   :  value(value)
{

}

CTRL::operator uint32_t () const
{
   return value.to_ulong ();
}

bool CTRL::FD () const
{
   return value [0];
}

void CTRL::FD (bool flag)
{
   value [0] = flag;
}

bool CTRL::GIO_master_disable () const
{
   return value [2];
}

void CTRL::GIO_master_disable (bool flag)
{
   value [2] = flag;
}

bool CTRL::ASDE () const
{
   return value [5];
}

void CTRL::ASDE (bool flag)
{
   value [5] = flag;
}

bool CTRL::SLU () const
{
   return value [6];
}

void CTRL::SLU (bool flag)
{
   value [6] = flag;
}

CTRL::Speed_enum CTRL::SPEED () const
{
   if (value [9])
   {
      return Speed_1000Mbs;
   }
   else if (value [8])
   {
      return Speed_100Mbs;
   }

   return Speed_10Mbs;
}

void CTRL::SPEED (CTRL::Speed_enum speed)
{
   switch (speed)
   {
   default:
   case Speed_10Mbs:
      value [8] = false;
      value [9] = false;
      break;

   case Speed_100Mbs:
      value [8] = true;
      value [9] = false;
      break;

   case Speed_1000Mbs:
      value [8] = false;
      value [9] = true;
      break;
   }
}

bool CTRL::FRCSPD () const
{
   return value [11];
}

void CTRL::FRCSPD (bool flag)
{
   value [11] = flag;
}

bool CTRL::FRCDPLX () const
{
   return value [12];
}

void CTRL::FRCDPLX (bool flag)
{
   value [12] = flag;
}

bool CTRL::ADVD3WUC () const
{
   return value [20];
}

void CTRL::ADVD3WUC (bool flag)
{
   value [20] = flag;
}

bool CTRL::RST () const
{
   return value [26];
}

void CTRL::RST (bool flag)
{
   value [26] = flag;
}

bool CTRL::RFCE () const
{
   return value [27];
}

void CTRL::RFCE (bool flag)
{
   value [27] = flag;
}

bool CTRL::TFCE () const
{
   return value [28];
}

void CTRL::TFCE (bool flag)
{
   value [28] = flag;
}

bool CTRL::VME () const
{
   return value [30];
}

void CTRL::VME (bool flag)
{
   value [30] = flag;
}

bool CTRL::PHY_RST () const
{
   return value [31];
}

void CTRL::PHY_RST (bool flag)
{
   value [31] = flag;
}

ostream &operator<< (ostream &out, const CTRL &ctrl)
{
   out << "Device control" << endl;
   out << "  FD: " << ctrl.FD () << " (" << ((ctrl.FD ()) ? "Full" : "Half") << " duplex)" << endl;
   out << "  GIO master disable: " << ctrl.GIO_master_disable () << endl;
   out << "  ASDE: " << ctrl.ASDE () << endl;
   out << "  SLU: " << ctrl.SLU () << endl;

   out << "  SPEED: " << ctrl.SPEED ();

   switch (ctrl.SPEED ())
   {
   default:
   case CTRL::Speed_10Mbs:
      out << " (10 Mb/s)" << endl;
      break;

   case CTRL::Speed_100Mbs:
      out << " (100 Mb/s)" << endl;
      break;

   case CTRL::Speed_1000Mbs:
      out << " (1000 Mb/s)" << endl;
      break;
   }

   out << "  FRCSPD: " << ctrl.FRCSPD () << endl;
   out << "  FRCDPLX: " << ctrl.FRCDPLX () << endl;
   out << "  ADVD3WUC: " << ctrl.ADVD3WUC () << endl;
   out << "  RST: " << ctrl.RST () << endl;
   out << "  RFCE: " << ctrl.RFCE () << endl;
   out << "  TFCE: " << ctrl.TFCE () << endl;
   out << "  VME: " << ctrl.VME () << endl;
   out << "  PHY_RST: " << ctrl.PHY_RST () << endl;

   return out;
}

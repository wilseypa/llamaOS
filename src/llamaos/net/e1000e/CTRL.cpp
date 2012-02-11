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

#include <llamaos/net/e1000e/CTRL.h>
#include <llamaos/net/e1000e/IO.h>

using namespace std;
using namespace llamaos::net::e1000e;

CTRL::CTRL (uint32_t value)
   :  value(value)
{

}

CTRL::operator uint32_t () const
{
   return value;
}

bool CTRL::FD () const
{
   return tst_bit (value, (1 << 0));
}

void CTRL::FD (bool flag)
{
   chg_bit (value, (1 << 0), flag);
}

bool CTRL::GIO_MD () const
{
   return tst_bit (value, (1 << 2));
}

void CTRL::GIO_MD (bool flag)
{
   chg_bit (value, (1 << 2), flag);
}

bool CTRL::ASDE () const
{
   return tst_bit (value, (1 << 5));
}

void CTRL::ASDE (bool flag)
{
   chg_bit (value, (1 << 5), flag);
}

bool CTRL::SLU () const
{
   return tst_bit (value, (1 << 6));
}

void CTRL::SLU (bool flag)
{
   chg_bit (value, (1 << 6), flag);
}

CTRL::LINK_SPEED CTRL::SPEED () const
{
   if (tst_bit (value, (1 << 9)))
   {
      return SPEED_1000MBS;
   }
   else if (tst_bit (value, (1 << 8)))
   {
      return SPEED_100MBS;
   }

   return SPEED_10MBS;
}

void CTRL::SPEED (LINK_SPEED speed)
{
   switch (speed)
   {
   default:
   case SPEED_10MBS:
      chg_bit (value, (1 << 8), false);
      chg_bit (value, (1 << 9), false);
      break;

   case SPEED_100MBS:
      chg_bit (value, (1 << 8), true);
      chg_bit (value, (1 << 9), false);
      break;

   case SPEED_1000MBS:
      chg_bit (value, (1 << 8), false);
      chg_bit (value, (1 << 9), true);
      break;
   }
}

bool CTRL::FRCSPD () const
{
   return tst_bit (value, (1 << 11));
}

void CTRL::FRCSPD (bool flag)
{
   chg_bit (value, (1 << 11), flag);
}

bool CTRL::FRCDPLX () const
{
   return tst_bit (value, (1 << 12));
}

void CTRL::FRCDPLX (bool flag)
{
   chg_bit (value, (1 << 12), flag);
}

bool CTRL::ADVD3WUC () const
{
   return tst_bit (value, (1 << 20));
}

void CTRL::ADVD3WUC (bool flag)
{
   chg_bit (value, (1 << 20), flag);
}

bool CTRL::RST () const
{
   return tst_bit (value, (1 << 26));
}

void CTRL::RST (bool flag)
{
   chg_bit (value, (1 << 26), flag);
}

bool CTRL::RFCE () const
{
   return tst_bit (value, (1 << 27));
}

void CTRL::RFCE (bool flag)
{
   chg_bit (value, (1 << 27), flag);
}

bool CTRL::TFCE () const
{
   return tst_bit (value, (1 << 28));
}

void CTRL::TFCE (bool flag)
{
   chg_bit (value, (1 << 28), flag);
}

bool CTRL::VME () const
{
   return tst_bit (value, (1 << 30));
}

void CTRL::VME (bool flag)
{
   chg_bit (value, (1 << 30), flag);
}

bool CTRL::PHY_RST () const
{
   return tst_bit (value, (1 << 31));
}

void CTRL::PHY_RST (bool flag)
{
   chg_bit (value, (1 << 31), flag);
}

ostream &llamaos::net::e1000e::operator<< (ostream &out, const CTRL &ctrl)
{
   out << "Device control" << endl;
   out << "  FD: " << ctrl.FD () << " (" << ((ctrl.FD ()) ? "Full" : "Half") << " duplex)" << endl;
   out << "  GIO master disable: " << ctrl.GIO_MD () << endl;
   out << "  ASDE: " << ctrl.ASDE () << endl;
   out << "  SLU: " << ctrl.SLU () << endl;

   out << "  SPEED: " << ctrl.SPEED ();

   switch (ctrl.SPEED ())
   {
   default:
   case CTRL::SPEED_10MBS:
      out << " (10 MB/S)" << endl;
      break;

   case CTRL::SPEED_100MBS:
      out << " (100 MB/S)" << endl;
      break;

   case CTRL::SPEED_1000MBS:
      out << " (1000 MB/S)" << endl;
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

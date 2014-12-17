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

#include <apps/net/intel/regs/STATUS.h>

using std::endl;
using std::ostream;

using apps::net::intel::regs::STATUS;

STATUS::STATUS (uint32_t value)
   :  value(value & 0x807D3)    // mask reserved bits
{

}

STATUS::operator uint32_t () const
{
   return value.to_ulong ();
}

bool STATUS::FD () const
{
   return value [0];
}

bool STATUS::LU () const
{
   return value [1];
}

bool STATUS::TXOFF () const
{
   return value [4];
}

STATUS::Speed_enum STATUS::SPEED () const
{
   if (value [7])
   {
      return Speed_1000Mbs;
   }
   else if (value [6])
   {
      return Speed_100Mbs;
   }

   return Speed_10Mbs;
}

STATUS::Speed_enum STATUS::ASDV () const
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

bool STATUS::PHYRA () const
{
   return value [10];
}

bool STATUS::GIO_master_enable_status () const
{
   return value [19];
}

ostream &operator<< (ostream &out, const STATUS &status)
{
   out << "Device status" << endl;
   out << "  FD: " << status.FD () << " (" << ((status.FD ()) ? "Full" : "Half") << " duplex)" << endl;
   out << "  LU: " << status.LU () << " (" << ((status.LU ()) ? "Link up" : "Link down") << " )" << endl;
   out << "  TXOFF: " << status.TXOFF () << endl;

   out << "  SPEED: " << status.SPEED ();

   switch (status.SPEED ())
   {
   default:
   case STATUS::Speed_10Mbs:
      out << " (10 Mb/s)" << endl;
      break;

   case STATUS::Speed_100Mbs:
      out << " (100 Mb/s)" << endl;
      break;

   case STATUS::Speed_1000Mbs:
      out << " (1000 Mb/s)" << endl;
      break;
   }

   out << "  ASDV: " << status.ASDV ();

   switch (status.ASDV ())
   {
   default:
   case STATUS::Speed_10Mbs:
      out << " (10 Mb/s)" << endl;
      break;

   case STATUS::Speed_100Mbs:
      out << " (100 Mb/s)" << endl;
      break;

   case STATUS::Speed_1000Mbs:
      out << " (1000 Mb/s)" << endl;
      break;
   }

   out << "  PHYRA: " << status.PHYRA () << endl;
   out << "  GIO master enabled: " << status.GIO_master_enable_status () << endl;

   return out;
}

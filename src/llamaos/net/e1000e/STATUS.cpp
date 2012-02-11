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

#include <llamaos/net/e1000e/STATUS.h>
#include <llamaos/net/e1000e/IO.h>

using namespace std;
using namespace llamaos::net::e1000e;

STATUS::STATUS (uint32_t value)
   :  value(value)
{

}

bool STATUS::FD () const
{
   return tst_bit (value, (1 << 0));
}

bool STATUS::LU () const
{
   return tst_bit (value, (1 << 1));
}

bool STATUS::TXOFF () const
{
   return tst_bit (value, (1 << 4));
}

STATUS::LINK_SPEED STATUS::SPEED () const
{
   if (tst_bit (value, (1 << 7)))
   {
      return SPEED_1000MBS;
   }
   else if (tst_bit (value, (1 << 6)))
   {
      return SPEED_100MBS;
   }

   return SPEED_10MBS;
}

STATUS::LINK_SPEED STATUS::ASDV () const
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

bool STATUS::PHYRA () const
{
   return tst_bit (value, (1 << 10));
}

bool STATUS::GIO_ME () const
{
   return tst_bit (value, (1 << 19));
}

ostream &llamaos::net::e1000e::operator<< (std::ostream &out, const STATUS &status)
{
   out << "Device status" << endl;
   out << "  FD: " << status.FD () << " (" << ((status.FD ()) ? "Full" : "Half") << " duplex)" << endl;
   out << "  LU: " << status.LU () << " (" << ((status.LU ()) ? "Link up" : "Link down") << " )" << endl;
   out << "  TXOFF: " << status.TXOFF () << endl;

   out << "  SPEED: " << status.SPEED ();

   switch (status.SPEED ())
   {
   default:
   case STATUS::SPEED_10MBS:
      out << " (10 MB/S)" << endl;
      break;

   case STATUS::SPEED_100MBS:
      out << " (100 MB/S)" << endl;
      break;

   case STATUS::SPEED_1000MBS:
      out << " (1000 MB/S)" << endl;
      break;
   }

   out << "  ASDV: " << status.ASDV ();

   switch (status.ASDV ())
   {
   default:
   case STATUS::SPEED_10MBS:
      out << " (10 MB/S)" << endl;
      break;

   case STATUS::SPEED_100MBS:
      out << " (100 MB/S)" << endl;
      break;

   case STATUS::SPEED_1000MBS:
      out << " (1000 MB/S)" << endl;
      break;
   }

   out << "  PHYRA: " << status.PHYRA () << endl;
   out << "  GIO master enabled: " << status.GIO_ME () << endl;

   return out;
}

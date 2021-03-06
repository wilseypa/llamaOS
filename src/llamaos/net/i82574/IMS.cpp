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

#include <llamaos/api/bit.h>
#include <llamaos/net/i82574/IMS.h>

using namespace std;
using namespace llamaos::api;
using namespace llamaos::net::i82574;

IMS::IMS (uint32_t value)
   :  value(value)
{

}

IMS::operator uint32_t () const
{
   return value;
}

bool IMS::TXDW () const
{
   return test_bit (value, 0);
}

bool IMS::TXQE () const
{
   return test_bit (value, 1);
}

bool IMS::LSC () const
{
   return test_bit (value, 2);
}

bool IMS::RXDMTO () const
{
   return test_bit (value, 4);
}

bool IMS::RXO () const
{
   return test_bit (value, 6);
}

bool IMS::RXTO () const
{
   return test_bit (value, 7);
}

bool IMS::MDAC () const
{
   return test_bit (value, 9);
}

bool IMS::TXD_LOW () const
{
   return test_bit (value, 15);
}

bool IMS::SRPD () const
{
   return test_bit (value, 16);
}

bool IMS::ACK () const
{
   return test_bit (value, 17);
}

bool IMS::MNG () const
{
   return test_bit (value, 18);
}

bool IMS::RXQ0 () const
{
   return test_bit (value, 20);
}

bool IMS::RXQ1 () const
{
   return test_bit (value, 21);
}

bool IMS::TXQ0 () const
{
   return test_bit (value, 22);
}

bool IMS::TXQ1 () const
{
   return test_bit (value, 23);
}

bool IMS::OTHER () const
{
   return test_bit (value, 24);
}

ostream &llamaos::net::i82574::operator<< (ostream &out, const IMS &ims)
{
   out << "IMS" << endl;
   out << "  TXDW: " << ims.TXDW () << endl;
   out << "  TXQE: " << ims.TXQE () << endl;
   out << "  LSC: " << ims.LSC () << endl;
   out << "  RXDMTO: " << ims.RXDMTO () << endl;
   out << "  RXO: " << ims.RXO () << endl;
   out << "  RXTO: " << ims.RXTO () << endl;
   out << "  MDAC: " << ims.MDAC () << endl;
   out << "  TXD_LOW: " << ims.TXD_LOW () << endl;
   out << "  SRPD: " << ims.SRPD () << endl;
   out << "  ACK: " << ims.ACK () << endl;
   out << "  MNG: " << ims.MNG () << endl;
   out << "  RXQ0: " << ims.RXQ0 () << endl;
   out << "  RXQ1: " << ims.RXQ1 () << endl;
   out << "  TXQ0: " << ims.TXQ0 () << endl;
   out << "  TXQ1: " << ims.TXQ1 () << endl;
   out << "  OTHER: " << ims.OTHER () << endl;

   return out;
}

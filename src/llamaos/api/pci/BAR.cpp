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
#include <llamaos/api/pci/BAR.h>

using namespace std;
using namespace llamaos::api;
using namespace llamaos::api::pci;

BAR::BAR (uint32_t value)
   :  value(value)
{

}

BAR::operator uint32_t () const
{
   return value;
}

bool BAR::Memory () const
{
   return !test_bit (value, 0);
}

bool BAR::Type64 () const
{
   return test_bit (value, 2);
}

bool BAR::Prefetch () const
{
   return test_bit (value, 3);
}

uint32_t BAR::Address () const
{
   return value & (Memory () ? 0xFFFFFFF0 : 0xFFFFFFFC);
}

ostream &llamaos::api::pci::operator<< (ostream &out, const BAR &bar)
{
   out << "BAR: " << hex << static_cast<uint32_t>(bar) << endl;

   if (bar.Memory ())
   {
      out << "  Memory " << (bar.Type64 () ? "64" : "32") << "-bit (" << (bar.Prefetch () ? "P" : "Non-p") << "refetchable)" << endl;
   }
   else
   {
      out << "  I/O space" << endl;
   }

   out << "  Address: " << hex << bar.Address () << endl;

   return out;
}

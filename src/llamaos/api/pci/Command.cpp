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
#include <llamaos/api/pci/Command.h>

using namespace std;
using namespace llamaos::api;
using namespace llamaos::api::pci;

Command::Command (uint16_t value)
   :  value(value)
{

}

Command::operator uint16_t () const
{
   return value;
}

bool Command::IO_enable () const
{
   return test_bit (value, 0);
}

void Command::IO_enable (bool flag)
{
   edit_bit (value, 0, flag);
}

bool Command::Memory_enable () const
{
   return test_bit (value, 1);
}

void Command::Memory_enable (bool flag)
{
   edit_bit (value, 1, flag);
}

bool Command::Mastering_enable () const
{
   return test_bit (value, 2);
}

void Command::Mastering_enable (bool flag)
{
   edit_bit (value, 2, flag);
}

bool Command::Interrupt_disable () const
{
   return test_bit (value, 10);
}

void Command::Interrupt_disable (bool flag)
{
   edit_bit (value, 10, flag);
}

ostream &llamaos::api::pci::operator<< (ostream &out, const Command &cmd)
{
   out << "Command Register: " << hex << static_cast<uint16_t>(cmd) << endl;

   if (cmd.IO_enable ())
   {
      out << "  I/O access enable" << endl;
   }

   if (cmd.Memory_enable ())
   {
      out << "  Memory access enable" << endl;
   }

   if (cmd.Mastering_enable ())
   {
      out << "  Mastering LAN enable" << endl;
   }

   if (cmd.Interrupt_disable ())
   {
      out << "  Interrupt disable" << endl;
   }

   return out;
}

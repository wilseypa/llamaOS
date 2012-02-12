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

#include <iostream>

#include <llamaos/memory/memory.h>
#include <llamaos/net/e1000e/CSR.h>
#include <llamaos/net/e1000e/IO.h>
#include <llamaos/xen/Hypercall.h>
#include <llamaos/config.h>

using namespace std;
using namespace llamaos;
using namespace llamaos::memory;
using namespace llamaos::net::e1000e;
using namespace llamaos::xen;

CSR::CSR (uint64_t machine_address, uint64_t virtual_address)
   :  pointer(address_to_pointer<uint8_t>(virtual_address))
{
   // mapping 128k
   for (uint64_t i = 0; i < 32; i++)
   {
      uint64_t offset = (i * PAGE_SIZE);
      Hypercall::update_va_mapping_nocache (virtual_address + offset, machine_address + offset);
   }
}

CSR::~CSR ()
{

}

uint32_t CSR::read (uint64_t offset) const
{
   return readl(pointer + offset);
}

void CSR::write (uint64_t offset, uint32_t value)
{
   writel (value, pointer + offset);
}

CTRL CSR::read_CTRL () const
{
   return CTRL (readl(pointer + 0x00000));
}

void CSR::write_CTRL (const CTRL &ctrl)
{
   writel (ctrl, pointer + 0x00000);
}

STATUS CSR::read_STATUS () const
{
   return STATUS (readl (pointer + 0x00008));
}

CTRL_EXT CSR::read_CTRL_EXT () const
{
   return CTRL_EXT (readl (pointer + 0x00018));
}

void CSR::write_CTRL_EXT (const CTRL_EXT &reg)
{
   writel (reg, pointer + 0x00018);
}

IMS CSR::read_IMS () const
{
   return IMS (readl (pointer + 0x000D0));
}

void CSR::write_IMC (const IMC &reg)
{
   writel (reg, pointer + 0x000D8);
}

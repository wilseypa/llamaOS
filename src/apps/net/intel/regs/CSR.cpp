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

#include <apps/net/intel/regs/CSR.h>
#include <llamaos/memory/Memory.h>

// borrowed from Linux
static inline uint32_t reg_read32 (const volatile void *addr)
{
   uint32_t ret;

   asm volatile("movl %1,%0"
                :"=r" (ret)
                :"m" (*(volatile uint32_t *)addr)
                :"memory");

   return ret;
}

static inline void reg_write32 (uint32_t val, volatile void *addr)
{
   asm volatile("movl %0,%1"
                :
                :"r" (val), "m" (*(volatile uint32_t *)addr)
                :"memory");
}

using apps::net::intel::regs::CSR;
using apps::net::intel::regs::CTRL;
using apps::net::intel::regs::CTRL_EXT;
using apps::net::intel::regs::STATUS;

CSR::CSR (uint64_t address)
   :  pointer(llamaos::memory::address_to_pointer<uint8_t>(address))
{
   
}

CSR::~CSR ()
{
   
}

uint32_t CSR::read (unsigned int offset) const
{
   return reg_read32 (pointer + offset);
}

void CSR::write (unsigned int offset, uint32_t value) const
{
   reg_write32 (value, pointer + offset);
}

CTRL CSR::read_CTRL () const
{
   return CTRL (reg_read32 (pointer + 0x00000));
}

void CSR::write_CTRL (const CTRL &ctrl) const
{
   reg_write32 (ctrl, pointer + 0x00000);
}

CTRL_EXT CSR::read_CTRL_EXT () const
{
   return CTRL_EXT (reg_read32 (pointer + 0x00018));
}

void CSR::write_CTRL_EXT (const CTRL_EXT &ctrl) const
{
   reg_write32 (ctrl, pointer + 0x00018);
}

STATUS CSR::read_STATUS () const
{
   return STATUS (reg_read32 (pointer + 0x00008));
}

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
using apps::net::intel::regs::EXTCNF_CTRL;
using apps::net::intel::regs::FCAH;
using apps::net::intel::regs::FCAL;
using apps::net::intel::regs::FCRTV;
using apps::net::intel::regs::FCT;
using apps::net::intel::regs::FCTTV;
using apps::net::intel::regs::PBA;
using apps::net::intel::regs::STATUS;
using apps::net::intel::regs::VET;

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

STATUS CSR::read_STATUS () const
{
   return STATUS (reg_read32 (pointer + 0x00008));
}

CTRL_EXT CSR::read_CTRL_EXT () const
{
   return CTRL_EXT (reg_read32 (pointer + 0x00018));
}

void CSR::write_CTRL_EXT (const CTRL_EXT &ctrl) const
{
   reg_write32 (ctrl, pointer + 0x00018);
}

FCAL CSR::read_FCAL () const
{
   return FCAL (reg_read32 (pointer + 0x00028));
}

void CSR::write_FCAL (const FCAL &fcal) const
{
   reg_write32 (fcal, pointer + 0x00028);
}

FCAH CSR::read_FCAH () const
{
   return FCAH (reg_read32 (pointer + 0x0002C));
}

void CSR::write_FCAH (const FCAH &fcah) const
{
   reg_write32 (fcah, pointer + 0x0002C);
}

FCT CSR::read_FCT () const
{
   return FCT (reg_read32 (pointer + 0x00030));
}

void CSR::write_FCT (const FCT &fct) const
{
   reg_write32 (fct, pointer + 0x00030);
}

VET CSR::read_VET () const
{
   return VET (reg_read32 (pointer + 0x00038));
}

void CSR::write_VET (const VET &vet) const
{
   reg_write32 (vet, pointer + 0x00038);
}

FCTTV CSR::read_FCTTV () const
{
   return FCTTV (reg_read32 (pointer + 0x00170));
}

void CSR::write_FCTTV (const FCTTV &fcttv) const
{
   reg_write32 (fcttv, pointer + 0x00170);
}

FCRTV CSR::read_FCRTV () const
{
   return FCRTV (reg_read32 (pointer + 0x05F40));
}

void CSR::write_FCRTV (const FCRTV &fcrtv) const
{
   reg_write32 (fcrtv, pointer + 0x05F40);
}

EXTCNF_CTRL CSR::read_EXTCNF_CTRL () const
{
   return EXTCNF_CTRL (reg_read32 (pointer + 0x00F00));
}

void CSR::write_EXTCNF_CTRL (const EXTCNF_CTRL &extcnf_ctrl) const
{
   reg_write32 (extcnf_ctrl, pointer + 0x00F00);
}

PBA CSR::read_PBA () const
{
   return PBA (reg_read32 (pointer + 0x01000));
}

void CSR::write_PBA (const PBA &pba) const
{
   reg_write32 (pba, pointer + 0x01000);
}

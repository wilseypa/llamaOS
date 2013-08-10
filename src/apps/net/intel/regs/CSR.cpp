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
using apps::net::intel::regs::FCRTH;
using apps::net::intel::regs::FCRTL;
using apps::net::intel::regs::FCRTV;
using apps::net::intel::regs::FCT;
using apps::net::intel::regs::FCTTV;
using apps::net::intel::regs::IMC;
using apps::net::intel::regs::IMS;
using apps::net::intel::regs::PBA;
using apps::net::intel::regs::PSRCTL;
using apps::net::intel::regs::RCTL;
using apps::net::intel::regs::RDBAH;
using apps::net::intel::regs::RDBAL;
using apps::net::intel::regs::RDH;
using apps::net::intel::regs::RDLEN;
using apps::net::intel::regs::RDT;
using apps::net::intel::regs::STATUS;
using apps::net::intel::regs::SWSM;
using apps::net::intel::regs::TCTL;
using apps::net::intel::regs::TDBAH;
using apps::net::intel::regs::TDBAL;
using apps::net::intel::regs::TDH;
using apps::net::intel::regs::TDLEN;
using apps::net::intel::regs::TDT;
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

SWSM CSR::read_SWSM () const
{
   return SWSM (reg_read32 (pointer + 0x05B50));
}

void CSR::write_SWSM (const SWSM &swsm) const
{
   reg_write32 (swsm, pointer + 0x05B50);
}

IMS CSR::read_IMS () const
{
   return IMS (reg_read32 (pointer + 0x000D0));
}

void CSR::write_IMS (const IMS &ims) const
{
   reg_write32 (ims, pointer + 0x000D0);
}

void CSR::write_IMC (const IMC &imc) const
{
   reg_write32 (imc, pointer + 0x000D8);
}

RCTL CSR::read_RCTL () const
{
   return RCTL (reg_read32 (pointer + 0x00100));
}

void CSR::write_RCTL (const RCTL &rctl) const
{
   reg_write32 (rctl, pointer + 0x00100);
}

PSRCTL CSR::read_PSRCTL () const
{
   return PSRCTL (reg_read32 (pointer + 0x02170));
}

void CSR::write_PSRCTL (const PSRCTL &psrctl) const
{
   reg_write32 (psrctl, pointer + 0x02170);
}

FCRTL CSR::read_FCRTL () const
{
   return FCRTL (reg_read32 (pointer + 0x02160));
}

void CSR::write_FCRTL (const FCRTL &fcrtl) const
{
   reg_write32 (fcrtl, pointer + 0x02160);
}

FCRTH CSR::read_FCRTH () const
{
   return FCRTH (reg_read32 (pointer + 0x02168));
}

void CSR::write_FCRTH (const FCRTH &fcrth) const
{
   reg_write32 (fcrth, pointer + 0x02168);
}

RDBAL CSR::read_RDBAL () const
{
   return RDBAL (reg_read32 (pointer + 0x02800));
}

void CSR::write_RDBAL (const RDBAL &rdbal) const
{
   reg_write32 (rdbal, pointer + 0x02800);
}

RDBAH CSR::read_RDBAH () const
{
   return RDBAH (reg_read32 (pointer + 0x02804));
}

void CSR::write_RDBAH (const RDBAH &rdbah) const
{
   reg_write32 (rdbah, pointer + 0x02804);
}

RDLEN CSR::read_RDLEN () const
{
   return RDLEN (reg_read32 (pointer + 0x02808));
}

void CSR::write_RDLEN (const RDLEN &rdlen) const
{
   reg_write32 (rdlen, pointer + 0x02808);
}

RDH CSR::read_RDH () const
{
   return RDH (reg_read32 (pointer + 0x02810));
}

void CSR::write_RDH (const RDH &rdh) const
{
   reg_write32 (rdh, pointer + 0x02810);
}

RDT CSR::read_RDT () const
{
   return RDT (reg_read32 (pointer + 0x02818));
}

void CSR::write_RDT (const RDT &rdt) const
{
   reg_write32 (rdt, pointer + 0x02818);
}

TCTL CSR::read_TCTL () const
{
   return TCTL (reg_read32 (pointer + 0x00400));
}

void CSR::write_TCTL (const TCTL &tctl) const
{
   reg_write32 (tctl, pointer + 0x00400);
}

TDBAL CSR::read_TDBAL () const
{
   return TDBAL (reg_read32 (pointer + 0x03800));
}

void CSR::write_TDBAL (const TDBAL &tdbal) const
{
   reg_write32 (tdbal, pointer + 0x03800);
}

TDBAH CSR::read_TDBAH () const
{
   return TDBAH (reg_read32 (pointer + 0x03804));
}

void CSR::write_TDBAH (const TDBAH &tdbah) const
{
   reg_write32 (tdbah, pointer + 0x03804);
}

TDLEN CSR::read_TDLEN () const
{
   return TDLEN (reg_read32 (pointer + 0x03808));
}

void CSR::write_TDLEN (const TDLEN &tdlen) const
{
   reg_write32 (tdlen, pointer + 0x03808);
}

TDH CSR::read_TDH () const
{
   return TDH (reg_read32 (pointer + 0x03810));
}

void CSR::write_TDH (const TDH &tdh) const
{
   reg_write32 (tdh, pointer + 0x03810);
}

TDT CSR::read_TDT () const
{
   return TDT (reg_read32 (pointer + 0x03818));
}

void CSR::write_TDT (const TDT &tdt) const
{
   reg_write32 (tdt, pointer + 0x03818);
}

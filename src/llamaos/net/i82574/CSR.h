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

#ifndef llamaos_net_i82574_csr_h_
#define llamaos_net_i82574_csr_h_

#include <cstdint>

#include <llamaos/net/i82574/CTRL.h>
#include <llamaos/net/i82574/CTRL_EXT.h>
#include <llamaos/net/i82574/EXTCNF_CTRL.h>
#include <llamaos/net/i82574/GCR.h>
#include <llamaos/net/i82574/IMC.h>
#include <llamaos/net/i82574/IMS.h>
#include <llamaos/net/i82574/RCTL.h>
#include <llamaos/net/i82574/RXDCTL.h>
#include <llamaos/net/i82574/STATUS.h>
#include <llamaos/net/i82574/SWSM.h>
#include <llamaos/net/i82574/TCTL.h>
#include <llamaos/net/i82574/TXDCTL.h>

namespace llamaos {
namespace net {
namespace i82574 {

class CSR
{
public:
   CSR (uint64_t virtual_address);
   virtual ~CSR ();

   uint32_t read (uint64_t offset) const;
   void write (uint64_t offset, uint32_t value);

   CTRL read_CTRL () const;
   void write_CTRL (const CTRL &);

   STATUS read_STATUS () const;

   CTRL_EXT read_CTRL_EXT () const;
   void write_CTRL_EXT (const CTRL_EXT &);

   IMS read_IMS () const;
   void write_IMC (const IMC &);

   EXTCNF_CTRL read_EXTCNF_CTRL () const;
   void write_EXTCNF_CTRL (const EXTCNF_CTRL &);

   GCR read_GCR () const;
   void write_GCR (const GCR &);

   RCTL read_RCTL () const;
   void write_RCTL (const RCTL &);

   RXDCTL read_RXDCTL () const;
   void write_RXDCTL (const RXDCTL &);

   uint64_t read_RDBA () const;
   void write_RDBA (uint64_t address) const;

   uint32_t read_RDLEN () const;
   void write_RDLEN (uint32_t length) const;

   uint16_t read_RDH () const;

   uint16_t read_RDT () const;
   void write_RDT (uint16_t tail) const;

   SWSM read_SWSM () const;
   void write_SWSM (const SWSM &);

   TCTL read_TCTL () const;
   void write_TCTL (const TCTL &);

   TXDCTL read_TXDCTL () const;
   void write_TXDCTL (const TXDCTL &);

   uint64_t read_TDBA () const;
   void write_TDBA (uint64_t address) const;

   uint32_t read_TDLEN () const;
   void write_TDLEN (uint32_t length) const;

   uint16_t read_TDH () const;

   uint16_t read_TDT () const;
   void write_TDT (uint16_t tail) const;

private:
   CSR ();
   CSR (const CSR &);
   CSR &operator= (const CSR &);

   uint8_t *const pointer;

};

} } }

#endif  // llamaos_net_i82574_csr_h_

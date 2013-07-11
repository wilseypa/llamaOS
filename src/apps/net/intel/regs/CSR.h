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

#ifndef apps_net_intel_regs_csr_h_
#define apps_net_intel_regs_csr_h_

#include <cstdint>

#include <apps/net/intel/regs/CTRL.h>
#include <apps/net/intel/regs/CTRL_EXT.h>
#include <apps/net/intel/regs/EXTCNF_CTRL.h>
#include <apps/net/intel/regs/FCAH.h>
#include <apps/net/intel/regs/FCAL.h>
#include <apps/net/intel/regs/FCRTV.h>
#include <apps/net/intel/regs/FCT.h>
#include <apps/net/intel/regs/FCTTV.h>
#include <apps/net/intel/regs/PBA.h>
#include <apps/net/intel/regs/STATUS.h>
#include <apps/net/intel/regs/VET.h>

namespace apps {
namespace net {
namespace intel {
namespace regs {

/**
 * @brief CSR (Configuration and Status Registers).
 * 
 */
class CSR
{
public:
   /**
    * @brief Construct the CSR class from machine address.
    * 
    */
   CSR (uint64_t address);
   ~CSR ();

   /**
    * @brief Generic 32-bit read function.
    * 
    * @param offset offset from CSR base address.
    * 
    */
   uint32_t read (unsigned int offset) const;

   /**
    * @brief Generic 32-bit write function.
    * 
    * @param offset offset from CSR base address.
    * @param value value to write to register.
    * 
    */
   void write (unsigned int offset, uint32_t value) const;

   /**
    * @brief Read the CTRL (Device Control) register.
    * 
    */
   CTRL read_CTRL () const;

   /**
    * @brief Write to the CTRL (Device Control) register.
    * 
    * @param ctrl CTRL register object.
    * 
    */
   void write_CTRL (const CTRL &ctrl) const;

   /**
    * @brief Read the STATUS (Device Status) register.
    * 
    */
   STATUS read_STATUS () const;

   /**
    * @brief Read the CTRL_EXT (Extended Device Control) register.
    * 
    */
   CTRL_EXT read_CTRL_EXT () const;

   /**
    * @brief Write to the CTRL_EXT (Extended Device Control) register.
    * 
    * @param ctrl CTRL_EXT register object.
    * 
    */
   void write_CTRL_EXT (const CTRL_EXT &ctrl) const;

   /**
    * @brief Read the FCAL (Flow Control Address Low) register.
    * 
    */
   FCAL read_FCAL () const;

   /**
    * @brief Write to the FCAL (Flow Control Address Low) register.
    * 
    * @param fcal FCAL register object.
    * 
    */
   void write_FCAL (const FCAL &fcal) const;

   /**
    * @brief Read the FCAH (Flow Control Address High) register.
    * 
    */
   FCAH read_FCAH () const;

   /**
    * @brief Write to the FCAH (Flow Control Address High) register.
    * 
    * @param fcah FCAH register object.
    * 
    */
   void write_FCAH (const FCAH &fcah) const;

   /**
    * @brief Read the FCT (Flow Control Type) register.
    * 
    */
   FCT read_FCT () const;

   /**
    * @brief Write to the FCT (Flow Control Type) register.
    * 
    * @param fct FCT register object.
    * 
    */
   void write_FCT (const FCT &fct) const;

   /**
    * @brief Read the VET (VLAN Ether Type) register.
    * 
    */
   VET read_VET () const;

   /**
    * @brief Write to the VET (VLAN Ether Type) register.
    * 
    * @param vet VET register object.
    * 
    */
   void write_VET (const VET &vet) const;

   /**
    * @brief Read the FCTTV (Flow Control Transmit Timer Value) register.
    * 
    */
   FCTTV read_FCTTV () const;

   /**
    * @brief Write to the FCTTV (Flow Control Transmit Timer Value) register.
    * 
    * @param fcttv FCTTV register object.
    * 
    */
   void write_FCTTV (const FCTTV &fcttv) const;

   /**
    * @brief Read the FCRTV (Flow Control Refresh Threshold Value) register.
    * 
    */
   FCRTV read_FCRTV () const;

   /**
    * @brief Write to the FCRTV (Flow Control Refresh Threshold Value) register.
    * 
    * @param fcrtv FCRTV register object.
    * 
    */
   void write_FCRTV (const FCRTV &fcrtv) const;

   /**
    * @brief Read the EXTCNF_CTRL (Extended Configuration Control) register.
    * 
    */
   EXTCNF_CTRL read_EXTCNF_CTRL () const;

   /**
    * @brief Write to the EXTCNF_CTRL (Extended Configuration Control) register.
    * 
    * @param extcnf_ctrl EXTCNF_CTRL register object.
    * 
    */
   void write_EXTCNF_CTRL (const EXTCNF_CTRL &extcnf_ctrl) const;

   /**
    * @brief Read the PBA (Packet Buffer Allocation) register.
    * 
    */
   PBA read_PBA () const;

   /**
    * @brief Write to the PBA (Packet Buffer Allocation) register.
    * 
    * @param pba PBA register object.
    * 
    */
   void write_PBA (const PBA &pba) const;

private:
   uint8_t *const pointer;

};

} } } }

#endif // apps_net_intel_regs_csr_h_

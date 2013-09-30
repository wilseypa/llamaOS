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
#include <apps/net/intel/regs/FCRTH.h>
#include <apps/net/intel/regs/FCRTL.h>
#include <apps/net/intel/regs/FCRTV.h>
#include <apps/net/intel/regs/FCRUC.h>
#include <apps/net/intel/regs/FCT.h>
#include <apps/net/intel/regs/FCTTV.h>
#include <apps/net/intel/regs/IMC.h>
#include <apps/net/intel/regs/IMS.h>
#include <apps/net/intel/regs/MPC.h>
#include <apps/net/intel/regs/PBA.h>
#include <apps/net/intel/regs/PSRCTL.h>
#include <apps/net/intel/regs/RCTL.h>
#include <apps/net/intel/regs/RDBAH.h>
#include <apps/net/intel/regs/RDBAL.h>
#include <apps/net/intel/regs/RDH.h>
#include <apps/net/intel/regs/RDLEN.h>
#include <apps/net/intel/regs/RDT.h>
#include <apps/net/intel/regs/RXDCTL.h>
#include <apps/net/intel/regs/STATUS.h>
#include <apps/net/intel/regs/SWSM.h>
#include <apps/net/intel/regs/TCTL.h>
#include <apps/net/intel/regs/TDBAH.h>
#include <apps/net/intel/regs/TDBAL.h>
#include <apps/net/intel/regs/TDH.h>
#include <apps/net/intel/regs/TDLEN.h>
#include <apps/net/intel/regs/TDT.h>
#include <apps/net/intel/regs/TPR.h>
#include <apps/net/intel/regs/TPT.h>
#include <apps/net/intel/regs/TXDCTL.h>
#include <apps/net/intel/regs/VET.h>
#include <apps/net/intel/regs/XOFFRXC.h>
#include <apps/net/intel/regs/XOFFTXC.h>
#include <apps/net/intel/regs/XONRXC.h>
#include <apps/net/intel/regs/XONTXC.h>

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

   /**
    * @brief Read the SWSM (Software Semaphore) register.
    * 
    */
   SWSM read_SWSM () const;

   /**
    * @brief Write to the SWSM (Software Semaphore) register.
    * 
    * @param swsm SWSM register object.
    * 
    */
   void write_SWSM (const SWSM &swsm) const;

   /**
    * @brief Read the IMS (Interrupt Mask Set/Read) register.
    * 
    */
   IMS read_IMS () const;

   /**
    * @brief Write to the IMS (Interrupt Mask Set/Read) register.
    * 
    * @param ims IMS register object.
    * 
    */
   void write_IMS (const IMS &ims) const;

   /**
    * @brief Write to the IMC (Interrupt Mask Clear) register.
    * 
    * @param imc IMC register object.
    * 
    */
   void write_IMC (const IMC &imc) const;

   /**
    * @brief Read the RCTL (Receive Control) register.
    * 
    */
   RCTL read_RCTL () const;

   /**
    * @brief Write to the RCTL (Receive Control) register.
    * 
    * @param rctl RCTL register object.
    * 
    */
   void write_RCTL (const RCTL &rctl) const;

   /**
    * @brief Read the PSRCTL (Packet Split Receive Control) register.
    * 
    */
   PSRCTL read_PSRCTL () const;

   /**
    * @brief Write to the PSRCTL (Packet Split Receive Control) register.
    * 
    * @param psrctl PSRCTL register object.
    * 
    */
   void write_PSRCTL (const PSRCTL &psrctl) const;

   /**
    * @brief Read the FCRTL (Flow Control Receive Threshold Low) register.
    * 
    */
   FCRTL read_FCRTL () const;

   /**
    * @brief Write to the FCRTL (Flow Control Receive Threshold Low) register.
    * 
    * @param fcrtl FCRTL register object.
    * 
    */
   void write_FCRTL (const FCRTL &fcrtl) const;

   /**
    * @brief Read the FCRTH (Flow Control Receive Threshold High) register.
    * 
    */
   FCRTH read_FCRTH () const;

   /**
    * @brief Write to the FCRTH (Flow Control Receive Threshold High) register.
    * 
    * @param fcrth FCRTH register object.
    * 
    */
   void write_FCRTH (const FCRTH &fcrth) const;

   /**
    * @brief Read the RDBAL (Receive Descriptor Base Address Low) register.
    * 
    */
   RDBAL read_RDBAL () const;

   /**
    * @brief Write to the RDBAL (Receive Descriptor Base Address Low) register.
    * 
    * @param rdbal RDBAL register object.
    * 
    */
   void write_RDBAL (const RDBAL &rdbal) const;

   /**
    * @brief Read the RDBAH (Receive Descriptor Base Address High) register.
    * 
    */
   RDBAH read_RDBAH () const;

   /**
    * @brief Write to the RDBAH (Receive Descriptor Base Address High) register.
    * 
    * @param rdbah RDBAH register object.
    * 
    */
   void write_RDBAH (const RDBAH &rdbah) const;

   /**
    * @brief Read the RDLEN (Receive Descriptor Length) register.
    * 
    */
   RDLEN read_RDLEN () const;

   /**
    * @brief Write to the RDLEN (Receive Descriptor Length) register.
    * 
    * @param rdlen RDLEN register object.
    * 
    */
   void write_RDLEN (const RDLEN &rdlen) const;

   /**
    * @brief Read the RDH (Receive Descriptor Head) register.
    * 
    */
   RDH read_RDH () const;

   /**
    * @brief Write to the RDH (Receive Descriptor Head) register.
    * 
    * @param rdh RDH register object.
    * 
    */
   void write_RDH (const RDH &rdh) const;

   /**
    * @brief Read the RDT (Receive Descriptor Tail) register.
    * 
    */
   RDT read_RDT () const;

   /**
    * @brief Write to the RDT (Receive Descriptor Tail) register.
    * 
    * @param rdt RDT register object.
    * 
    */
   void write_RDT (const RDT &rdt) const;

   /**
    * @brief Read the TCTL (Transmit Control) register.
    * 
    */
   TCTL read_TCTL () const;

   /**
    * @brief Write to the TCTL (Transmit Control) register.
    * 
    * @param tctl TCTL register object.
    * 
    */
   void write_TCTL (const TCTL &tctl) const;

   /**
    * @brief Read the TDBAL (Transmit Descriptor Base Address Low) register.
    * 
    */
   TDBAL read_TDBAL () const;

   /**
    * @brief Write to the TDBAL (Transmit Descriptor Base Address Low) register.
    * 
    * @param tdbal TDBAL register object.
    * 
    */
   void write_TDBAL (const TDBAL &tdbal) const;

   /**
    * @brief Read the TDBAH (Transmit Descriptor Base Address High) register.
    * 
    */
   TDBAH read_TDBAH () const;

   /**
    * @brief Write to the TDBAH (Transmit Descriptor Base Address High)
    *        register.
    * 
    * @param tdbah TDBAH register object.
    * 
    */
   void write_TDBAH (const TDBAH &tdbah) const;

   /**
    * @brief Read the TDLEN (Transmit Descriptor Length) register.
    * 
    */
   TDLEN read_TDLEN () const;

   /**
    * @brief Write to the TDLEN (Transmit Descriptor Length) register.
    * 
    * @param tdlen TDLEN register object.
    * 
    */
   void write_TDLEN (const TDLEN &tdlen) const;

   /**
    * @brief Read the TDH (Transmit Descriptor Head) register.
    * 
    */
   TDH read_TDH () const;

   /**
    * @brief Write to the TDH (Transmit Descriptor Head) register.
    * 
    * @param tdh TDH register object.
    * 
    */
   void write_TDH (const TDH &tdh) const;

   /**
    * @brief Read the TDT (Transmit Descriptor Tail) register.
    * 
    */
   TDT read_TDT () const;

   /**
    * @brief Write to the TDT (Transmit Descriptor Tail) register.
    * 
    * @param tdt TDT register object.
    * 
    */
   void write_TDT (const TDT &tdt) const;

   /**
    * @brief Read the TXDCTL (Transmit Descriptor Control) register.
    * 
    */
   TXDCTL read_TXDCTL () const;

   /**
    * @brief Write to the TXDCTL (Transmit Descriptor Control) register.
    * 
    * @param txdctl TXDCTL register object.
    * 
    */
   void write_TXDCTL (const TXDCTL &txdctl) const;

   /**
    * @brief Read the MPC (Missed Packets Count) register.
    * 
    */
   MPC read_MPC () const;

   /**
    * @brief Read the XONRXC (XON Received Count) register.
    * 
    */
   XONRXC read_XONRXC () const;

   /**
    * @brief Read the XONTXC (XON Transmitted Count) register.
    * 
    */
   XONTXC read_XONTXC () const;

   /**
    * @brief Read the XOFFRXC (XOFF Received Count) register.
    * 
    */
   XOFFRXC read_XOFFRXC () const;

   /**
    * @brief Read the XOFFTXC (XOFF Transmitted Count) register.
    * 
    */
   XOFFTXC read_XOFFTXC () const;

   /**
    * @brief Read the FCRUC (FC Received Unsupported Count) register.
    * 
    */
   FCRUC read_FCRUC () const;

   /**
    * @brief Read the TPR (Total Packets Received) register.
    * 
    */
   TPR read_TPR () const;

   /**
    * @brief Read the TPT (Total Packets Transmitted) register.
    * 
    */
   TPT read_TPT () const;

private:
   uint8_t *const pointer;

};

} } } }

#endif // apps_net_intel_regs_csr_h_

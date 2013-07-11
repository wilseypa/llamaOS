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

#ifndef llamaos_net_intel_regs_ctrl_ext_h_
#define llamaos_net_intel_regs_ctrl_ext_h_

#include <cstdint>

#include <bitset>
#include <ostream>

namespace apps {
namespace net {
namespace intel {
namespace regs {

/**
 * @brief Extended Device Control register.
 * 
 */
class CTRL_EXT
{
public:
   /**
    * @breif Construct from value.
    * 
    * @param value Initial value (usually read from hardware).
    * 
    */
   CTRL_EXT (uint32_t value);

   /**
    * @breif Convert to 32-bit integer.
    * 
    */
   operator uint32_t () const;

   /**
    * @brief Auto Speed Detection Check bit.
    * 
    */
   bool ASDCHK () const;

   /**
    * @brief Auto Speed Detection Check bit.
    * 
    */
   void ASDCHK (bool flag);

   /**
    * @brief EEPROM Reset bit.
    * 
    */
   bool EE_RST () const;

   /**
    * @brief EEPROM Reset bit.
    * 
    */
   void EE_RST (bool flag);

   /**
    * @brief Speed Select Bypass bit.
    * 
    */
   bool SPD_BYPS () const;

   /**
    * @brief Speed Select Bypass bit.
    * 
    */
   void SPD_BYPS (bool flag);

   /**
    * @brief Relaxed Ordering Disable bit.
    * 
    */
   bool RO_DIS () const;

   /**
    * @brief Relaxed Ordering Disable bit.
    * 
    */
   void RO_DIS (bool flag);

   /**
    * @brief DMA Dynamic Gating Enable bit.
    *
    */ 
   bool DMA_dynamic_gating_enable () const;

   /**
    * @brief DMA Dynamic Gating Enable bit.
    *
    */ 
   void DMA_dynamic_gating_enable (bool flag);

   /**
    * @brief PHY Power Down Enable bit.
    * 
    */
   bool PHY_power_down_enable () const;

   /**
    * @brief PHY Power Down Enable bit.
    * 
    */
   void PHY_power_down_enable (bool flag);

   /**
    * @brief TX LS Flow bit.
    * 
    */
   bool TX_LS_FLOW () const;

   /**
    * @brief TX LS Flow bit.
    * 
    */
   void TX_LS_FLOW (bool flag);

   /**
    * @brief TX LS bit.
    * 
    */
   bool TX_LS () const;

   /**
    * @brief TX LS bit.
    * 
    */
   void TX_LS (bool flag);

   /**
    * @brief Extended Interrupt Auto Mask Enable bit.
    * 
    */
   bool EIAME () const;

   /**
    * @brief Extended Interrupt Auto Mask Enable bit.
    * 
    */
   void EIAME (bool flag);
   /**
    * @brief Interrupt Acknowledge Auto Mask Enable bit.
    * 
    */
   bool IAME () const;

   /**
    * @brief Interrupt Acknowledge Auto Mask Enable bit.
    * 
    */
   void IAME (bool flag);

   /**
    * @brief Driver Loaded bit.
    * 
    */
   bool DRV_LOAD () const;

   /**
    * @brief Driver Loaded bit.
    * 
    */
   void DRV_LOAD (bool flag);

   /**
    * @brief Interrupt Timers Clear Enable bit.
    * 
    */
   bool INT_TIMERS_CLEAR_ENA () const;

   /**
    * @brief Interrupt Timers Clear Enable bit.
    * 
    */
   void INT_TIMERS_CLEAR_ENA (bool flag);

   /**
    * @brief PBA Support bit.
    * 
    */
   bool PBA_SUPPORT () const;

   /**
    * @brief PBA Support bit.
    * 
    */
   void PBA_SUPPORT (bool flag);

private:
   std::bitset<32> value;

};

/**
 * @brief Stream insertion operator.
 * 
 */
std::ostream &operator<< (std::ostream &, const CTRL_EXT &);

} } } }

#endif // llamaos_net_intel_regs_ctrl_ext_h_

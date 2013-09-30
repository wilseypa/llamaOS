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

#ifndef llamaos_net_intel_regs_ctrl_h_
#define llamaos_net_intel_regs_ctrl_h_

#include <cstdint>

#include <bitset>
#include <ostream>

namespace apps {
namespace net {
namespace intel {
namespace regs {

/**
 * @brief Device Control register.
 * 
 */
class CTRL
{
public:
   /**
    * @breif Construct from value.
    * 
    * @param value Initial value (usually read from hardware).
    * 
    */
   CTRL (uint32_t value);

   /**
    * @breif Convert to 32-bit integer.
    * 
    */
   operator uint32_t () const;

   /**
    * @brief Full Duplex bit.
    * 
    */
   bool FD () const;

   /**
    * @brief Full Duplex bit.
    * 
    */
   void FD (bool flag);

   /**
    * @brief GIO master disable bit.
    * 
    */
   bool GIO_master_disable () const;

   /**
    * @brief GIO master disable bit.
    * 
    */
   void GIO_master_disable (bool flag);

   /**
    * @brief Auto-Speed Detect Enable bit.
    * 
    */
   bool ASDE () const;

   /**
    * @brief Auto-Speed Detect Enable bit.
    * 
    */
   void ASDE (bool flag);

   /**
    * @brief Set Link Up bit.
    * 
    */
   bool SLU () const;

   /**
    * @brief Set Link Up bit.
    * 
    */
   void SLU (bool flag);

   /**
    * @brief Speed Selection options.
    * 
    */
   enum Speed_enum { Speed_10Mbs, Speed_100Mbs, Speed_1000Mbs };

   /**
    * @brief Speed Selection bits.
    * 
    */
   Speed_enum SPEED () const;

   /**
    * @brief Speed Selection bits.
    * 
    */
   void SPEED (Speed_enum speed);

   /**
    * @brief Force Speed bit.
    * 
    */
   bool FRCSPD () const;

   /**
    * @brief Force Speed bit.
    * 
    */
   void FRCSPD (bool flag);

   /**
    * @brief Force Duplex bit.
    * 
    */
   bool FRCDPLX () const;

   /**
    * @brief Force Duplex bit.
    * 
    */
   void FRCDPLX (bool flag);

   /**
    * @brief D3Cold WakeUp Capability Advertisement Enable bit.
    * 
    */
   bool ADVD3WUC () const;

   /**
    * @brief D3Cold WakeUp Capability Advertisement Enable bit.
    * 
    */
   void ADVD3WUC (bool flag);

   /**
    * @brief Device Reset bit.
    * 
    */
   bool RST () const;

   /**
    * @brief Device Reset bit.
    * 
    */
   void RST (bool flag);

   /**
    * @brief Receive Flow Control Enable bit.
    * 
    */
   bool RFCE () const;

   /**
    * @brief Receive Flow Control Enable bit.
    * 
    */
   void RFCE (bool flag);

   /**
    * @brief Transmit Flow Control Enable bit.
    * 
    */
   bool TFCE () const;

   /**
    * @brief Transmit Flow Control Enable bit.
    * 
    */
   void TFCE (bool flag);

   /**
    * @brief VLAN Mode Enable.
    * 
    */
   bool VME () const;

   /**
    * @brief VLAN Mode Enable.
    * 
    */
   void VME (bool flag);

   /**
    * @brief PHY Reset bit.
    * 
    */
   bool PHY_RST () const;

   /**
    * @brief PHY Reset bit.
    * 
    */
   void PHY_RST (bool flag);

private:
   std::bitset<32> value;

};

/**
 * @brief Stream insertion operator.
 * 
 */
std::ostream &operator<< (std::ostream &, const CTRL &);

} } } }

#endif // apps_net_intel_regs_ctrl_h_

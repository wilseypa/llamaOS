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

#ifndef llamaos_net_intel_regs_imc_h_
#define llamaos_net_intel_regs_imc_h_

#include <cstdint>

#include <bitset>
#include <ostream>

namespace apps {
namespace net {
namespace intel {
namespace regs {

/**
 * @brief Interrupt Mask Clear register.
 * 
 */
class IMC
{
public:
   /**
    * @breif Construct from value.
    * 
    * @param value Initial value (usually read from hardware).
    * 
    */
   IMC (uint32_t value);

   /**
    * @breif Convert to 32-bit integer.
    * 
    */
   operator uint32_t () const;

   /**
    * @brief Transmit Descriptor Writeback bit.
    * 
    */
   void TXDW (bool flag);

   /**
    * @brief Transmit Queue Empty bit.
    * 
    */
   void TXQE (bool flag);

   /**
    * @brief Link Status Change bit.
    * 
    */
   void LSC (bool flag);

   /**
    * @brief Receive Descriptor Minimum Threshold bit.
    * 
    */
   void RXDMT0 (bool flag);

   /**
    * @brief Receive Overrun bit.
    * 
    */
   void RXO (bool flag);

   /**
    * @brief Receive Timer bit.
    * 
    */
   void RXT0 (bool flag);

   /**
    * @brief MDIO Access Complete bit.
    * 
    */
   void MDAC (bool flag);

   /**
    * @brief Transmit Descriptor Low threshold bit.
    * 
    */
   void TXD_LOW (bool flag);

   /**
    * @brief Small Receive Packet Detect bit.
    * 
    */
   void SRPD (bool flag);

   /**
    * @brief Receive ACK frame detect bit.
    * 
    */
   void ACK (bool flag);

   /**
    * @brief Manageabiltity bit.
    * 
    */
   void MNG (bool flag);

   /**
    * @brief Receive Queue 0 bit.
    * 
    */
   void RxQ0 (bool flag);

   /**
    * @brief Receive Queue 1 bit.
    * 
    */
   void RxQ1 (bool flag);

   /**
    * @brief Transmit Queue 0 bit.
    * 
    */
   void TxQ0 (bool flag);

   /**
    * @brief Transmit Queue 1 bit.
    * 
    */
   void TxQ1 (bool flag);

   /**
    * @brief Other bit.
    * 
    */
   void Other (bool flag);

private:
   std::bitset<32> value;

};

} } } }

#endif // llamaos_net_intel_regs_imc_h_

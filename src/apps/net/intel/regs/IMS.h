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

#ifndef llamaos_net_intel_regs_ims_h_
#define llamaos_net_intel_regs_ims_h_

#include <cstdint>

#include <bitset>
#include <ostream>

namespace apps {
namespace net {
namespace intel {
namespace regs {

/**
 * @brief Interrupt Mask Set/Read register.
 * 
 */
class IMS
{
public:
   /**
    * @breif Construct from value.
    * 
    * @param value Initial value (usually read from hardware).
    * 
    */
   IMS (uint32_t value);

   /**
    * @breif Convert to 32-bit integer.
    * 
    */
   operator uint32_t () const;

   /**
    * @brief Transmit Descriptor Writeback bit.
    * 
    */
   bool TXDW () const;

   /**
    * @brief Transmit Descriptor Writeback bit.
    * 
    */
   void TXDW (bool flag);

   /**
    * @brief Transmit Queue Empty bit.
    * 
    */
   bool TXQE () const;

   /**
    * @brief Transmit Queue Empty bit.
    * 
    */
   void TXQE (bool flag);

   /**
    * @brief Link Status Change bit.
    * 
    */
   bool LSC () const;

   /**
    * @brief Link Status Change bit.
    * 
    */
   void LSC (bool flag);

   /**
    * @brief Receive Descriptor Minimum Threshold bit.
    * 
    */
   bool RXDMT0 () const;

   /**
    * @brief Receive Descriptor Minimum Threshold bit.
    * 
    */
   void RXDMT0 (bool flag);

   /**
    * @brief Receive Overrun bit.
    * 
    */
   bool RXO () const;

   /**
    * @brief Receive Overrun bit.
    * 
    */
   void RXO (bool flag);

   /**
    * @brief Receive Timer bit.
    * 
    */
   bool RXT0 () const;

   /**
    * @brief Receive Timer bit.
    * 
    */
   void RXT0 (bool flag);

   /**
    * @brief MDIO Access Complete bit.
    * 
    */
   bool MDAC () const;

   /**
    * @brief MDIO Access Complete bit.
    * 
    */
   void MDAC (bool flag);

   /**
    * @brief Transmit Descriptor Low threshold bit.
    * 
    */
   bool TXD_LOW () const;

   /**
    * @brief Transmit Descriptor Low threshold bit.
    * 
    */
   void TXD_LOW (bool flag);

   /**
    * @brief Small Receive Packet Detect bit.
    * 
    */
   bool SRPD () const;

   /**
    * @brief Small Receive Packet Detect bit.
    * 
    */
   void SRPD (bool flag);

   /**
    * @brief Receive ACK frame detect bit.
    * 
    */
   bool ACK () const;

   /**
    * @brief Receive ACK frame detect bit.
    * 
    */
   void ACK (bool flag);

   /**
    * @brief Manageabiltity bit.
    * 
    */
   bool MNG () const;

   /**
    * @brief Manageabiltity bit.
    * 
    */
   void MNG (bool flag);

   /**
    * @brief Receive Queue 0 bit.
    * 
    */
   bool RxQ0 () const;

   /**
    * @brief Receive Queue 0 bit.
    * 
    */
   void RxQ0 (bool flag);

   /**
    * @brief Receive Queue 1 bit.
    * 
    */
   bool RxQ1 () const;

   /**
    * @brief Receive Queue 1 bit.
    * 
    */
   void RxQ1 (bool flag);

   /**
    * @brief Transmit Queue 0 bit.
    * 
    */
   bool TxQ0 () const;

   /**
    * @brief Transmit Queue 0 bit.
    * 
    */
   void TxQ0 (bool flag);

   /**
    * @brief Transmit Queue 1 bit.
    * 
    */
   bool TxQ1 () const;

   /**
    * @brief Transmit Queue 1 bit.
    * 
    */
   void TxQ1 (bool flag);

   /**
    * @brief Other bit.
    * 
    */
   bool Other () const;

   /**
    * @brief Other bit.
    * 
    */
   void Other (bool flag);

private:
   std::bitset<32> value;

};

/**
 * @brief Stream insertion operator.
 * 
 */
std::ostream &operator<< (std::ostream &, const IMS &);

   
} } } }

#endif // llamaos_net_intel_regs_ims_h_

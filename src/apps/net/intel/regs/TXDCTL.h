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

#ifndef llamaos_net_intel_regs_txdctl_h_
#define llamaos_net_intel_regs_txdctl_h_

#include <cstdint>

#include <ostream>

namespace apps {
namespace net {
namespace intel {
namespace regs {

/**
 * @brief Transmit Descriptor Control register.
 * 
 */
class TXDCTL
{
public:
   /**
    * @breif Construct from value.
    * 
    * @param value Initial value (usually read from hardware).
    * 
    */
   TXDCTL (uint32_t value);

   /**
    * @breif Convert to 32-bit integer.
    * 
    */
   operator uint32_t () const;

   /**
    * @brief Prefetch Threshold value.
    * 
    */
   uint8_t PTHRESH () const;

   /**
    * @brief Prefetch Threshold value.
    * 
    */
   void PTHRESH (uint8_t threshold);

   /**
    * @brief Host Threshold value.
    * 
    */
   uint8_t HTHRESH () const;

   /**
    * @brief Host Threshold value.
    * 
    */
   void HTHRESH (uint8_t threshold);

   /**
    * @brief Write-back Threshold value.
    * 
    */
   uint8_t WTHRESH () const;

   /**
    * @brief Write-back Threshold value.
    * 
    */
   void WTHRESH (uint8_t threshold);

   /**
    * @brief Ganularity bit.
    * 
    */
   bool GRAN () const;

   /**
    * @brief Ganularity bit.
    * 
    */
   void GRAN (bool flag);

   /**
    * @brief Low Threshold value.
    * 
    */
   uint8_t LWTHRESH () const;

   /**
    * @brief Low Threshold value.
    * 
    */
   void LWTHRESH (uint8_t threshold);

private:
   uint32_t value;

};

/**
 * @brief Stream insertion operator.
 * 
 */
std::ostream &operator<< (std::ostream &, const TXDCTL &);

} } } }

#endif // llamaos_net_intel_regs_txdctl_h_

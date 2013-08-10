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

#ifndef llamaos_net_intel_regs_tctl_h_
#define llamaos_net_intel_regs_tctl_h_

#include <cstdint>

#include <bitset>
#include <ostream>

namespace apps {
namespace net {
namespace intel {
namespace regs {

/**
 * @brief Transmit Control register.
 * 
 */
class TCTL
{
public:
   /**
    * @breif Construct from value.
    * 
    * @param value Initial value (usually read from hardware).
    * 
    */
   TCTL (uint32_t value);

   /**
    * @breif Convert to 32-bit integer.
    * 
    */
   operator uint32_t () const;

   /**
    * @brief Enable bit.
    * 
    */
   bool EN () const;

   /**
    * @brief Enable bit.
    * 
    */
   void EN (bool flag);

   /**
    * @brief Pad Short Packets bit.
    * 
    */
   bool PSP () const;

   /**
    * @brief Pad Short Packets bit.
    * 
    */
   void PSP (bool flag);

   /**
    * @brief Collision Threshold bit.
    * 
    */
   uint8_t CT () const;

   /**
    * @brief Collision Threshold bit.
    * 
    */
   void CT (uint8_t threshold);

   /**
    * @brief Collision Distance bit.
    * 
    */
   uint16_t COLD () const;

   /**
    * @brief Collision Distance bit.
    * 
    */
   void COLD (uint16_t distance);

   /**
    * @brief Software XOFF Transmission bit.
    * 
    */
   bool SWXOFF () const;

   /**
    * @brief Software XOFF Transmission bit.
    * 
    */
   void SWXOFF (bool flag);

   /**
    * @brief Packet Burst Enable bit.
    * 
    */
   bool PBE () const;

   /**
    * @brief Packet Burst Enable bit.
    * 
    */
   void PBE (bool flag);

   /**
    * @brief Re-Transmit on Late Collision bit.
    * 
    */
   bool RTLC () const;

   /**
    * @brief Re-Transmit on Late Collision bit.
    * 
    */
   void RTLC (bool flag);

   /**
    * @brief Under run No Re-transmit bit.
    * 
    */
   bool UNORTX () const;

   /**
    * @brief Under run No Re-transmit bit.
    * 
    */
   void UNORTX (bool flag);

   /**
    * @brief Tx Descriptor Minimum Threshold bit.
    * 
    */
   uint8_t TXDSCMT () const;

   /**
    * @brief Tx Descriptor Minimum Threshold bit.
    * 
    */
   void TXDSCMT (uint8_t threshold);

   /**
    * @brief Multiple Request Support bit.
    * 
    */
   bool MULR () const;

   /**
    * @brief Multiple Request Support bit.
    * 
    */
   void MULR (bool flag);

   /**
    * @brief Read Request Threshold options.
    * 
    */
   enum RRTHRESH_enum { RRTHRESH_2_lines, RRTHRESH_4_lines,
                        RRTHRESH_8_lines, RRTHRESH_none };

   /**
    * @brief Read Request Threshold setting.
    * 
    */
   RRTHRESH_enum RRTHRESH () const;

   /**
    * @brief Read Request Threshold.
    * 
    */
   void RRTHRESH (RRTHRESH_enum threshold);

private:
   std::bitset<32> value;

};

/**
 * @brief Stream insertion operator.
 * 
 */
std::ostream &operator<< (std::ostream &, const TCTL &);

} } } }

#endif // llamaos_net_intel_regs_tctl_h_

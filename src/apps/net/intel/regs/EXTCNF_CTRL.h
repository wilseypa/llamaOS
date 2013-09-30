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

#ifndef llamaos_net_intel_regs_extcnf_ctrl_h_
#define llamaos_net_intel_regs_extcnf_ctrl_h_

#include <cstdint>

#include <bitset>
#include <ostream>

namespace apps {
namespace net {
namespace intel {
namespace regs {

/**
 * @brief Extended Configuration Control register.
 * 
 */
class EXTCNF_CTRL
{
public:
   /**
    * @breif Construct from value.
    * 
    * @param value Initial value (usually read from hardware).
    * 
    */
   EXTCNF_CTRL (uint32_t value);

   /**
    * @breif Convert to 32-bit integer.
    * 
    */
   operator uint32_t () const;

   /**
    * @brief MDIO Management Request bit.
    * 
    */
   bool MDIO_mng_ownership () const;

   /**
    * @brief MDIO Management Request bit.
    * 
    */
   void MDIO_mng_ownership (bool flag);

   /**
    * @brief MDIO Hardware Request bit.
    * 
    */
   bool MDIO_hw_ownership () const;

   /**
    * @brief MDIO Hardware Request bit.
    * 
    */
   void MDIO_hw_ownership (bool flag);

   /**
    * @brief MDIO Software Request bit.
    * 
    */
   bool MDIO_sw_ownership () const;

   /**
    * @brief MDIO Software Request bit.
    * 
    */
   void MDIO_sw_ownership (bool flag);

private:
   std::bitset<32> value;

};

/**
 * @brief Stream insertion operator.
 * 
 */
std::ostream &operator<< (std::ostream &, const EXTCNF_CTRL &);

} } } }

#endif // llamaos_net_intel_regs_extcnf_ctrl_h_

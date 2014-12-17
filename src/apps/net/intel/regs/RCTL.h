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

#ifndef llamaos_net_intel_regs_rctl_h_
#define llamaos_net_intel_regs_rctl_h_

#include <cstdint>

#include <bitset>
#include <ostream>

namespace apps {
namespace net {
namespace intel {
namespace regs {

/**
 * @brief Receive Control register.
 * 
 */
class RCTL
{
public:
   /**
    * @breif Construct from value.
    * 
    * @param value Initial value (usually read from hardware).
    * 
    */
   RCTL (uint32_t value);

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
    * @brief Store Bad Packets bit.
    * 
    */
   bool SBP () const;

   /**
    * @brief Store Bad Packets bit.
    * 
    */
   void SBP (bool flag);

   /**
    * @brief Unicast Promiscuous Enable bit.
    * 
    */
   bool UPE () const;

   /**
    * @brief Unicast Promiscuous Enable bit.
    * 
    */
   void UPE (bool flag);

   /**
    * @brief Multicast Promiscuous Enable bit.
    * 
    */
   bool MPE () const;

   /**
    * @brief Multicast Promiscuous Enable bit.
    * 
    */
   void MPE (bool flag);

   /**
    * @brief Long Packet Enable bit.
    * 
    */
   bool LPE () const;

   /**
    * @brief Long Packet Enable bit.
    * 
    */
   void LPE (bool flag);

   /**
    * @brief Loopback Mode options.
    * 
    */
   enum LBM_enum { LBM_normal, LBM_mac };

   /**
    * @brief Loopback Mode setting.
    * 
    */
   LBM_enum LBM () const;

   /**
    * @brief Loopback Mode setting.
    * 
    */
   void LBM (LBM_enum mode);

   /**
    * @brief Receive Descriptor Minimum Threshold Size options.
    * 
    */
   enum RDMTS_enum { RDMTS_half, RDMTS_quarter, RDMTS_eighth };

   /**
    * @brief Receive Descriptor Minimum Threshold Size setting.
    * 
    */
   RDMTS_enum RDMTS () const;

   /**
    * @brief Receive Descriptor Minimum Threshold Size setting.
    * 
    */
   void RDMTS (RDMTS_enum size);

   /**
    * @brief Descriptor Type options.
    * 
    */
   enum DTYP_enum { DTYP_legacy, DTYP_split };

   /**
    * @brief Descriptor Type setting.
    * 
    */
   DTYP_enum DTYP () const;

   /**
    * @brief Descriptor Type setting.
    * 
    */
   void DTYP (DTYP_enum type);

   /**
    * @brief Multicast Offset options.
    * 
    */
   enum MO_enum { MO_47_36, MO_46_35, MO_45_34, MO_43_32 };

   /**
    * @brief Multicast Offset setting.
    * 
    */
   MO_enum MO () const;

   /**
    * @brief Multicast Offset setting.
    * 
    */
   void MO (MO_enum offset);

   /**
    * @brief Broadcast Accept Mode bit.
    * 
    */
   bool BAM () const;

   /**
    * @brief Broadcast Accept Mode bit.
    * 
    */
   void BAM (bool flag);

   /**
    * @brief Receive Buffer Size options.
    * 
    */
   enum BSIZE_enum { BSIZE_256, BSIZE_512, BSIZE_1024, BSIZE_2048,
                     BSIZE_4096, BSIZE_8192, BSIZE_16384 };

   /**
    * @brief Receive Buffer Size setting.
    * 
    */
   BSIZE_enum BSIZE () const;

   /**
    * @brief Receive Buffer Size setting.
    * 
    */
   void BSIZE (BSIZE_enum size);

   /**
    * @brief VLAN Filter Enable bit.
    * 
    */
   bool VFE () const;

   /**
    * @brief VLAN Filter Enable bit.
    * 
    */
   void VFE (bool flag);

   /**
    * @brief Canonical Form Indicator Enable bit.
    * 
    */
   bool CFIEN () const;

   /**
    * @brief Canonical Form Indicator Enable bit.
    * 
    */
   void CFIEN (bool flag);

   /**
    * @brief Canonical Form Indicator Value bit.
    * 
    */
   bool CFI () const;

   /**
    * @brief Canonical Form Indicator Value bit.
    * 
    */
   void CFI (bool flag);

   /**
    * @brief Discard Pause Frames bit.
    * 
    */
   bool DPF () const;

   /**
    * @brief Discard Pause Frames bit.
    * 
    */
   void DPF (bool flag);

   /**
    * @brief Pass MAC Control Frames bit.
    * 
    */
   bool PMCF () const;

   /**
    * @brief Pass MAC Control Frames bit.
    * 
    */
   void PMCF (bool flag);

   /**
    * @brief Buffer Size Extension bit.
    * 
    */
   bool BSEX () const;

   /**
    * @brief Buffer Size Extension bit.
    * 
    */
   void BSEX (bool flag);

   /**
    * @brief Strip Ethernet CRC  bit.
    * 
    */
   bool SECRC () const;

   /**
    * @brief Strip Ethernet CRC  bit.
    * 
    */
   void SECRC (bool flag);

   /**
    * @brief Flexible Buffer Size setting.
    * 
    */
   uint8_t FLXBUF () const;

   /**
    * @brief Flexible Buffer Size setting.
    * 
    */
   void FLXBUF (uint8_t size);

private:
   std::bitset<32> value;

};

/**
 * @brief Stream insertion operator.
 * 
 */
std::ostream &operator<< (std::ostream &, const RCTL &);

} } } }

#endif // llamaos_net_intel_regs_rctl_h_

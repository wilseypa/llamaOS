/*
Copyright (c) 2012, William Magato
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

#ifndef llamaos_net_i82574_ctrl_ext_h_
#define llamaos_net_i82574_ctrl_ext_h_

#include <cstdint>

namespace llamaos {
namespace net {
namespace i82574 {

class CTRL_EXT
{
public:
   CTRL_EXT (uint32_t value);

   operator uint32_t () const;

   bool ASDCHK () const;
   void ASDCHK (bool flag);

   bool EE_RST () const;
   void EE_RST (bool flag);

   bool SPD_BYPS () const;
   void SPD_BYPS (bool flag);

   bool RO_DIS () const;
   void RO_DIS (bool flag);

   bool DMA_DGE () const;
   void DMA_DGE (bool flag);

   bool PHY_PDE () const;
   void PHY_PDE (bool flag);

   bool TX_LS_FLOW () const;
   void TX_LS_FLOW (bool flag);

   bool TX_LS () const;
   void TX_LS (bool flag);

   bool EIAME () const;
   void EIAME (bool flag);

   bool IAME () const;
   void IAME (bool flag);

   bool DRV_LOAD () const;
   void DRV_LOAD (bool flag);

   bool INT_TIMERS_CLEAR_ENA () const;
   void INT_TIMERS_CLEAR_ENA (bool flag);

   bool PBA_SUPPORT () const;
   void PBA_SUPPORT (bool flag);

private:
   uint32_t value;
};

} } }

#endif  // llamaos_net_i82574_ctrl_ext_h_

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

#ifndef llamaos_net_i82574_ctrl_h_
#define llamaos_net_i82574_ctrl_h_

#include <cstdint>

#include <ostream>

namespace llamaos {
namespace net {
namespace i82574 {

class CTRL
{
public:
   CTRL (uint32_t value);

   operator uint32_t () const;

   enum LINK_SPEED { SPEED_10MBS, SPEED_100MBS, SPEED_1000MBS };

   bool FD () const;
   void FD (bool flag);

   bool GIO_MD () const;
   void GIO_MD (bool flag);

   bool ASDE () const;
   void ASDE (bool flag);

   bool SLU () const;
   void SLU (bool flag);

   LINK_SPEED SPEED () const;
   void SPEED (LINK_SPEED speed);

   bool FRCSPD () const;
   void FRCSPD (bool flag);

   bool FRCDPLX () const;
   void FRCDPLX (bool flag);

   bool ADVD3WUC () const;
   void ADVD3WUC (bool flag);

   bool RST () const;
   void RST (bool flag);

   bool RFCE () const;
   void RFCE (bool flag);

   bool TFCE () const;
   void TFCE (bool flag);

   bool VME () const;
   void VME (bool flag);

   bool PHY_RST () const;
   void PHY_RST (bool flag);

private:
   uint32_t value;
};

std::ostream &operator<< (std::ostream &, const CTRL &);

} } }

#endif  // llamaos_net_i82574_ctrl_h_

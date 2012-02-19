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

#ifndef llamaos_net_i82574_tctl_h_
#define llamaos_net_i82574_tctl_h_

#include <cstdint>

namespace llamaos {
namespace net {
namespace i82574 {

class TCTL
{
public:
   TCTL (uint32_t value);

   operator uint32_t () const;

   bool EN () const;
   void EN (bool flag);

   bool PSP () const;
   void PSP (bool flag);

   uint8_t CT () const;
   void CT (uint8_t n);

   uint16_t COLD () const;
   void COLD (uint16_t t);

   bool SWXOFF () const;
   void SWXOFF (bool flag);

   bool PBE () const;
   void PBE (bool flag);

   bool RTLC () const;
   void RTLC (bool flag);

   bool UNORTX () const;
   void UNORTX (bool flag);

//   unsigned int TXDSCMT () const;
//   void TXDSCMT (unsigned int t);

   bool MULR () const;
   void MULR (bool flag);

   enum READ_REQUEST_THREAHOLD { THREASHOLD_2_LINES, THREASHOLD_4_LINES, THREASHOLD_8_LINES, THREASHOLD_NONE };

   READ_REQUEST_THREAHOLD RRTHRESH () const;
   void RRTHRESH (READ_REQUEST_THREAHOLD rrt);

private:
   uint32_t value;
};

} } }

#endif  // llamaos_net_i82574_tctl_h_

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

#ifndef llamaos_net_i82574_gcr_h_
#define llamaos_net_i82574_gcr_h_

#include <cstdint>

#include <ostream>

namespace llamaos {
namespace net {
namespace i82574 {

class GCR
{
public:
   GCR (uint32_t value);

   operator uint32_t () const;

   enum L1_ENTRY_LATENCY { LATENCY_2USEC, LATENCY_8USEC, LATENCY_16USEC, LATENCY_32USEC, LATENCY_64USEC, LATENCY_256USEC, LATENCY_1MSEC, LATENCY_4MSEC };

   bool RXD_NOSNOOP () const;
   void RXD_NOSNOOP (bool flag);

   bool RXDSCW_NOSNOOP () const;
   void RXDSCW_NOSNOOP (bool flag);

   bool RXDSCR_NOSNOOP () const;
   void RXDSCR_NOSNOOP (bool flag);

   bool TXD_NOSNOOP () const;
   void TXD_NOSNOOP (bool flag);

   bool TXDSCW_NOSNOOP () const;
   void TXDSCW_NOSNOOP (bool flag);

   bool TXDSCR_NOSNOOP () const;
   void TXDSCR_NOSNOOP (bool flag);

   bool RX_L0S_ADJUST () const;
   void RX_L0S_ADJUST (bool flag);

   bool PBA_CL_DEAS () const;
   void PBA_CL_DEAS (bool flag);

   bool HEADER_LOG_ORDER () const;
   void HEADER_LOG_ORDER (bool flag);

   bool INITIALIZE () const;
   void INITIALIZE (bool flag);

   L1_ENTRY_LATENCY L1_ENTRY_LAT () const;
   void L1_ENTRY_LAT (L1_ENTRY_LATENCY usec);

   bool L0S_ENTRY_LAT () const;
   void L0S_ENTRY_LAT (bool flag);

   bool L1_ACT_WITHOUT_L0S_RX () const;
   void L1_ACT_WITHOUT_L0S_RX (bool flag);

   bool GIO_DIS_RD_ERR () const;
   void GIO_DIS_RD_ERR (bool flag);

   bool GIO_GOOD_L0S () const;
   void GIO_GOOD_L0S (bool flag);

   bool SELF_TEST_RESULT () const;
   void SELF_TEST_RESULT (bool flag);

   bool DISABLE_TIMEOUT () const;
   void DISABLE_TIMEOUT (bool flag);

private:
   uint32_t value;
};

} } }

#endif  // llamaos_net_i82574_gcr_h_

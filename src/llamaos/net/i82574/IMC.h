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

#ifndef llamaos_net_i82574_imc_h_
#define llamaos_net_i82574_imc_h_

#include <cstdint>

namespace llamaos {
namespace net {
namespace i82574 {

class IMC
{
public:
   static const IMC ALL;

   IMC ();
   IMC (uint32_t value);

   operator uint32_t () const;

   bool TXDW () const;
   void TXDW (bool flag);

   bool TXQE () const;
   void TXQE (bool flag);

   bool LSC () const;
   void LSC (bool flag);

   bool RXDMTO () const;
   void RXDMTO (bool flag);

   bool RXO () const;
   void RXO (bool flag);

   bool RXTO () const;
   void RXTO (bool flag);

   bool MDAC () const;
   void MDAC (bool flag);

   bool TXD_LOW () const;
   void TXD_LOW (bool flag);

   bool SRPD () const;
   void SRPD (bool flag);

   bool ACK () const;
   void ACK (bool flag);

   bool MNG () const;
   void MNG (bool flag);

   bool RXQ0 () const;
   void RXQ0 (bool flag);

   bool RXQ1 () const;
   void RXQ1 (bool flag);

   bool TXQ0 () const;
   void TXQ0 (bool flag);

   bool TXQ1 () const;
   void TXQ1 (bool flag);

   bool OTHER () const;
   void OTHER (bool flag);

private:
   uint32_t value;
};

} } }

#endif  // llamaos_net_i82574_imc_h_

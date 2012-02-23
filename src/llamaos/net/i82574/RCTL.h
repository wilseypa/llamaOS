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

#ifndef llamaos_net_i82574_rctl_h_
#define llamaos_net_i82574_rctl_h_

#include <cstdint>

namespace llamaos {
namespace net {
namespace i82574 {

class RCTL
{
public:
   RCTL (uint32_t value);

   operator uint32_t () const;

   bool EN () const;
   void EN (bool flag);

   bool SBP () const;
   void SBP (bool flag);

   bool UPE () const;
   void UPE (bool flag);

   bool MPE () const;
   void MPE (bool flag);

   bool LPE () const;
   void LPE (bool flag);

   enum DESC_THRESHOLD { HALF, QUARTER, EIGHTH };

   DESC_THRESHOLD RDMTS () const;
   void RDMTS (DESC_THRESHOLD rdt);

   enum DESC_TYPE { LEGACY, SPLIT };

   DESC_TYPE DTYP () const;
   void DTYP (DESC_TYPE type);

   bool BAM () const;
   void BAM (bool flag);

   enum BUFFER_SIZE { BYTES_2048, BYTES_1024, BYTES_512, BYTES_256 };

   BUFFER_SIZE BSIZE () const;
   void BSIZE (BUFFER_SIZE size);

private:
   uint32_t value;
};

} } }

#endif  // llamaos_net_i82574_rctl_h_

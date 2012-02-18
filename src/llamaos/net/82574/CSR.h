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

#ifndef llamaos_net_i82574_csr_h_
#define llamaos_net_i82574_csr_h_

#include <cstdint>

#include <llamaos/net/e1000e/CTRL.h>
#include <llamaos/net/e1000e/CTRL_EXT.h>
#include <llamaos/net/e1000e/IMC.h>
#include <llamaos/net/e1000e/IMS.h>
#include <llamaos/net/e1000e/STATUS.h>

namespace llamaos {
namespace net {
namespace i82574 {

class CSR
{
public:
   CSR (uint64_t virtual_address);
   virtual ~CSR ();

   uint32_t read (uint64_t offset) const;
   void write (uint64_t offset, uint32_t value);

   CTRL read_CTRL () const;
   void write_CTRL (const CTRL &);

   STATUS read_STATUS () const;

   CTRL_EXT read_CTRL_EXT () const;
   void write_CTRL_EXT (const CTRL_EXT &);

   IMS read_IMS () const;
   void write_IMC (const IMC &);

private:
   CSR ();
   CSR (const CSR &);
   CSR &operator= (const CSR &);

   uint8_t *const pointer;

};

} } }

#endif  // llamaos_net_i82574_csr_h_

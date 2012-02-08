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

#ifndef llamaos_net_e1000e_csr_h_
#define llamaos_net_e1000e_csr_h_

#include <cstdint>

namespace llamaos {
namespace net {
namespace e1000e {

class Device_control
{
public:
   static const uint32_t FD;
   static const uint32_t GIO_MASTER_DISABLE;
   static const uint32_t ASDE;
   static const uint32_t SLU;
   static const uint32_t SPEED1;
   static const uint32_t SPEED2;
   static const uint32_t FRCSPD;
   static const uint32_t FRCDPLX;
   static const uint32_t ADVD3WUC;
   static const uint32_t RST;
   static const uint32_t RFCE;
   static const uint32_t TFCE;
   static const uint32_t VME;
   static const uint32_t PHY_RST;

   Device_control (uint32_t value);
   ~Device_control ();

   enum SPEED { SPEED_10MBS, SPEED_100MBS, SPEED_1000MBS };

   bool get_FD () const;
   void set_FD (bool flag);

   bool get_GIO_master_disable () const;
   void set_GIO_master_disable (bool flag);

   bool get_ASDE () const;
   void set_ASDE (bool flag);

   bool get_SLU () const;
   void set_SLU (bool flag);

   SPEED get_SPEED () const;
   void set_SPEED (SPEED speed);

   bool get_FRCSPD () const;
   void set_FRCSPD (bool flag);

   bool get_FRCDPLX () const;
   void set_FRCDPLX (bool flag);

   bool get_ADVD3WUC () const;
   void set_ADVD3WUC (bool flag);

   bool get_RST () const;
   void set_RST (bool flag);

   bool get_RFCE () const;
   void set_RFCE (bool flag);

   bool get_TFCE () const;
   void set_TFCE (bool flag);

   bool get_VME () const;
   void set_VME (bool flag);

   bool get_PHY_RST () const;
   void set_PHY_RST (bool flag);

   uint32_t value;
};

class Device_status
{
public:
   static const uint32_t FD;
   static const uint32_t LU;
   static const uint32_t TXOFF;
   static const uint32_t SPEED1;
   static const uint32_t SPEED2;
   static const uint32_t ASDV1;
   static const uint32_t ASDV2;
   static const uint32_t PHYRA;
   static const uint32_t GIO_MASTER_ENABLED;

   Device_status (uint32_t value);
   ~Device_status ();

   enum SPEED { SPEED_10MBS, SPEED_100MBS, SPEED_1000MBS };

   bool get_FD () const;
   bool get_LU () const;
   bool get_TXOFF () const;
   SPEED get_SPEED () const;
   SPEED get_ASDV () const;
   bool get_PHYRA () const;
   bool get_GIO_MASTER_ENABLED () const;

   uint32_t value;
};

class CSR
{
public:
   CSR (uint64_t machine_address, uint64_t virtual_address);
   virtual ~CSR ();

   uint32_t read (uint64_t offset) const;
   void write (uint64_t offset, uint32_t value);

   Device_control read_CTRL () const;
   void write_CTRL (const Device_control &CTRL);

   Device_status read_STATUS () const;

private:
   CSR ();
   CSR (const CSR &);
   CSR &operator= (const CSR &);

   uint8_t *const pointer;

};

std::ostream &operator<< (std::ostream &out, const Device_control &CTRL);
std::ostream &operator<< (std::ostream &out, const Device_status &STATUS);

} } }

#endif  // llamaos_net_e1000e_pci_h_

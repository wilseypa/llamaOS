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

#include <apps/net/intel/regs/RCTL.h>

using std::endl;
using std::ostream;

using apps::net::intel::regs::RCTL;

RCTL::RCTL (uint32_t value)
   :  value(value & 0x7EDFBFFE)    // mask reserved bits
{
   
}

RCTL::operator uint32_t () const
{
   return value.to_ulong ();
}

bool RCTL::EN () const
{
   return value [1];
}

void RCTL::EN (bool flag)
{
   value [1] = flag;
}

bool RCTL::SBP () const
{
   return value [2];
}

void RCTL::SBP (bool flag)
{
   value [2] = flag;
}

bool RCTL::UPE () const
{
   return value [3];
}

void RCTL::UPE (bool flag)
{
   value [3] = flag;
}

bool RCTL::MPE () const
{
   return value [4];
}

void RCTL::MPE (bool flag)
{
   value [4] = flag;
}

bool RCTL::LPE () const
{
   return value [5];
}

void RCTL::LPE (bool flag)
{
   value [5] = flag;
}

RCTL::LBM_enum RCTL::LBM () const
{
   return (value [6]) ? LBM_mac : LBM_normal;
}

void RCTL::LBM (RCTL::LBM_enum mode)
{
   value [6] = (mode == LBM_mac);
   value [7] = false;
}

RCTL::RDMTS_enum RCTL::RDMTS () const
{
   if (value [9])
   {
      return RDMTS_eighth;
   }
   else if (value [8])
   {
      return RDMTS_quarter;
   }

   return RDMTS_half;
}

void RCTL::RDMTS (RCTL::RDMTS_enum size)
{
   switch (size)
   {
      default:
      case RDMTS_half:
         value [8] = false;
         value [9] = false;
         break;
      case RDMTS_quarter:
         value [8] = true;
         value [9] = false;
         break;
      case RDMTS_eighth:
         value [8] = false;
         value [9] = true;
         break;
   }
}

RCTL::DTYP_enum RCTL::DTYP () const
{
   return (value [10]) ? DTYP_split : DTYP_legacy;
}

void RCTL::DTYP (RCTL::DTYP_enum type)
{
   value [10] = (type == DTYP_split);
   value [11] = false;
}

RCTL::MO_enum RCTL::MO () const
{
   if (value [13])
   {
      if (value [12])
      {
         return MO_43_32;
      }
      else
      {
         return MO_45_34;
      }
   }
   else
   {
      if (value [12])
      {
         return MO_46_35;
      }
      else
      {
         return MO_47_36;
      }
   }
}

void RCTL::MO (RCTL::MO_enum offset)
{
   switch (offset)
   {
      default:
      case MO_47_36:
         value [12] = false;
         value [13] = false;
         break;
      case MO_46_35:
         value [12] = true;
         value [13] = false;
         break;
      case MO_45_34:
         value [12] = false;
         value [13] = true;
         break;
      case MO_43_32:
         value [12] = true;
         value [13] = true;
         break;
   }
}

bool RCTL::BAM () const
{
   return value [15];
}

void RCTL::BAM (bool flag)
{
   value [15] = flag;
}

RCTL::BSIZE_enum RCTL::BSIZE () const
{
   if (BSEX ())
   {
      if (value [17])
      {
         if (value [16])
         {
            return BSIZE_4096;
         }
         else
         {
            return BSIZE_8192;
         }
      }
      else
      {
         return BSIZE_16384;
      }
   }
   else
   {
      if (value [17])
      {
         if (value [16])
         {
            return BSIZE_256;
         }
         else
         {
            return BSIZE_512;
         }
      }
      else
      {
         if (value [16])
         {
            return BSIZE_1024;
         }
         else
         {
            return BSIZE_2048;
         }
      }
   }
}

void RCTL::BSIZE (RCTL::BSIZE_enum size)
{
   switch (size)
   {
      default:
      case BSIZE_2048:
         value [16] = false;
         value [17] = false;
         break;
      case BSIZE_1024:
      case BSIZE_16384:
         value [16] = true;
         value [17] = false;
         break;
      case BSIZE_512:
      case BSIZE_8192:
         value [16] = false;
         value [17] = true;
         break;
      case BSIZE_256:
      case BSIZE_4096:
         value [16] = true;
         value [17] = true;
         break;
   }
}

bool RCTL::VFE () const
{
   return value [18];
}

void RCTL::VFE (bool flag)
{
   value [18] = flag;
}

bool RCTL::CFIEN () const
{
   return value [19];
}

void RCTL::CFIEN (bool flag)
{
   value [19] = flag;
}

bool RCTL::CFI () const
{
   return value [20];
}

void RCTL::CFI (bool flag)
{
   value [20] = flag;
}

bool RCTL::DPF () const
{
   return value [22];
}

void RCTL::DPF (bool flag)
{
   value [22] = flag;
}

bool RCTL::PMCF () const
{
   return value [23];
}

void RCTL::PMCF (bool flag)
{
   value [23] = flag;
}

bool RCTL::BSEX () const
{
   return value [25];
}

void RCTL::BSEX (bool flag)
{
   value [25] = flag;
}

bool RCTL::SECRC () const
{
   return value [26];
}

void RCTL::SECRC (bool flag)
{
   value [26] = flag;
}

uint8_t RCTL::FLXBUF () const
{
   return ((value.to_ulong () >> 27) & 0xF);
}

void RCTL::FLXBUF (uint8_t size)
{
   value &= (0x78000000 | (size << 27));
}

ostream &operator<< (ostream &out, const RCTL &rctl)
{
   out << "Receive control" << endl;
   out << "  EN: " << rctl.EN () << endl;
   out << "  SBP: " << rctl.SBP () << endl;
   out << "  UPE: " << rctl.UPE () << endl;
   out << "  MPE: " << rctl.MPE () << endl;
   out << "  LPE: " << rctl.LPE () << endl;

   out << "  LBM: ";
   if (rctl.LBM () == RCTL::LBM_normal)
   {
      out << "Normal";
   }
   else
   {
      out << "MAC Loopback";
   }
   out << endl;

   out << "  RDMTS: " << rctl.RDMTS () << endl;

   out << "  DTYP: ";
   if (rctl.DTYP () == RCTL::DTYP_legacy)
   {
      out << "Legacy";
   }
   else
   {
      out << "Packet Split";
   }
   out << endl;

   out << "  MO: ";
   switch(rctl.MO ())
   {
      default:
      case RCTL::MO_43_32:
         out << "[43:32]";
         break;
      case RCTL::MO_45_34:
         out << "[45:34]";
         break;
      case RCTL::MO_46_35:
         out << "[46:35]";
         break;
      case RCTL::MO_47_36:
         out << "[47:36]";
         break;
   }
   out << endl;

   out << "  BAM: " << rctl.BAM () << endl;

   out << "  BSIZE: ";
   switch(rctl.BSIZE ())
   {
      default:
      case RCTL::BSIZE_2048:
         out << "2048";
         break;
      case RCTL::BSIZE_1024:
         out << "1024";
         break;
      case RCTL::BSIZE_512:
         out << "512";
         break;
      case RCTL::BSIZE_256:
         out << "256";
         break;
      case RCTL::BSIZE_16384:
         out << "16384";
         break;
      case RCTL::BSIZE_8192:
         out << "8192";
         break;
      case RCTL::BSIZE_4096:
         out << "4096";
         break;
   }
   out << endl;

   out << "  VFE: " << rctl.VFE () << endl;
   out << "  CFIEN: " << rctl.CFIEN () << endl;
   out << "  CFI: " << rctl.CFI () << endl;
   out << "  DPF: " << rctl.DPF () << endl;
   out << "  PMCF: " << rctl.PMCF () << endl;
   out << "  BSEX: " << rctl.BSEX () << endl;
   out << "  SECRC: " << rctl.SECRC () << endl;
   out << "  FLXBUF: " << rctl.FLXBUF () << endl;

   return out;
}

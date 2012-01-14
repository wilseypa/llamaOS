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

#ifndef llamaos_memory_entry_h_
#define llamaos_memory_entry_h_

#include <cstdint>
#include <cstdio>

namespace llamaos {
namespace memory {

// Assume 64-bit/long mode operation only (for now)

// Page-Map Level-4 (PML4)              bits 39-47
// Page-Directory-Pointer (PDP)         bits 30-38
// Page-directory (PD)                  bits 21-29
// Page-Table (PT)                      bits 12-20
// Physical-Page Offset                 bits 0-11

class Entry
{
public:
   // Present bit.
   static const uint64_t P;

   // Read/Write bit.
   static const uint64_t RW;

   // User/Supervisor bit.
   static const uint64_t US;

   // Page-level write-through bit.
   static const uint64_t PWT;

   // Page-level cache disable bit.
   static const uint64_t PCD;

   // Accessed bit.
   static const uint64_t A;

   // Address mask.
   static const uint64_t ADDR_MASK;

   Entry (uint64_t machine_address, uint64_t value)
      :  machine_address(machine_address),
         value(value)
   {

   }

   virtual ~Entry ()
   {

   }

   // Test for present bit (P).
   bool present () const { return value & P; }

   // Test for read/write bit (RW).
   bool writable () const { return value & RW; }

   // Test for user/supervisor bit (US).
   bool user () const { return value & US; }

   // Test for page-level write-through bit (PWT).
   bool page_level_write_through () const { return value & PWT; }

   // Test for page-level cache diable bit (PCD).
   bool page_level_cache_disable () const { return value & PCD; }

   // Test for accessed bit (A).
   bool accessed () const { return value & A; }

   // Compute entry address.
   uint64_t address () const { return value & ADDR_MASK; }

   // Returns True if the entry is empty (null).
   bool empty () const { return (0 == value); }

   // Get a formatted string of the value.
   const char *to_string () const
   {
      static char text [32] = { '\0' };

      std::sprintf (text,
                    "0x%016lx %c %c %c %c %c %c",
                    value & ADDR_MASK,
                    (value & A) ? 'A' : ' ',
                    (value & PCD) ? '1' : '0',
                    (value & PWT) ? '1' : '0',
                    (value & US) ? 'S' : 'U',
                    (value & RW) ? 'W' : 'R',
                    (value & P) ? 'P' : ' ');

      return text;
   }

   // address of the entry (needed for mmu updates)
   const uint64_t machine_address;

   // Entry value.
   const uint64_t value;

private:
   Entry ();
   Entry (const Entry &);
   Entry &operator= (const Entry &);

};

} }

#endif  // llamaos_memory_entry_h_

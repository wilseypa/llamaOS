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

#ifndef llamaos_memory_memory_h_
#define llamaos_memory_memory_h_

#include <cstdint>

// defined by linker script
extern char _text;

#define mb()    asm volatile("mfence":::"memory")
#define rmb()   asm volatile("lfence":::"memory")
#define wmb()   asm volatile("sfence" ::: "memory")

namespace llamaos {
namespace memory {

inline uint64_t address_to_page (uint64_t address)
{
   return address >> 12;
}

inline uint64_t page_to_address (uint64_t page)
{
   return page << 12;
}

template <typename T>
inline T *address_to_pointer (uint64_t address)
{
   return reinterpret_cast<T *>(address);
}

template <typename T>
inline uint64_t pointer_to_address (T *pointer)
{
   return reinterpret_cast<uint64_t>(pointer);
}

inline uint64_t pseudo_to_virtual (uint64_t address)
{
   return address + pointer_to_address(&_text);
}

inline uint64_t virtual_to_pseudo (uint64_t address)
{
   return address - pointer_to_address(&_text);
}

uint64_t machine_page_to_pseudo_page (uint64_t page);
uint64_t pseudo_page_to_machine_page (uint64_t page);

template <typename T>
inline T *machine_page_to_virtual_pointer (uint64_t page)
{
   return address_to_pointer <T> (pseudo_to_virtual (page_to_address (machine_page_to_pseudo_page (page))));
}

template <typename T>
inline T *machine_address_to_virtual_pointer (uint64_t address)
{
   return machine_page_to_virtual_pointer<T> (address_to_page (address));
}

template <typename T>
inline uint64_t virtual_pointer_to_machine_page (T *pointer)
{
   return pseudo_page_to_machine_page (address_to_page (virtual_to_pseudo (pointer_to_address(pointer))));
}

template <typename T>
inline uint64_t virtual_pointer_to_machine_address (T *pointer)
{
   return page_to_address (pseudo_page_to_machine_page (address_to_page (virtual_to_pseudo (pointer_to_address(pointer)))));
}

void create_table_entry (uint64_t CR3_virtual_address,
                         uint64_t table_virtual_address,
                         uint64_t table_machine_address);
void update_table_entry (uint64_t entry_machine_address, uint64_t page_machine_address);

bool initialize (uint64_t CR3_virtual_address, uint64_t total_pages, uint64_t reserved_pages);

uint64_t get_reserved_virtual_address (uint64_t pages);
uint64_t get_reserved_size ();

void *get_program_break ();
void *set_program_break (void *address);

} }

#endif  // llamaos_memory_memory_h_

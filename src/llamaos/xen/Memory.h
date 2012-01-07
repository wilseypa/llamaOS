/*
Copyright (c) 2011, William Magato
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

#ifndef llamaos_xen_memory_h_
#define llamaos_xen_memory_h_

#include <cstdint>

namespace llamaos {
namespace xen {
namespace memory {

/**
 * @brief Convert address to pointer.
 *
 * @param address Address to convert.
 *
 */
template <typename T>
inline T *to_pointer (uint64_t address)
{
   return reinterpret_cast<T *>(address);
}

/**
 * @brief Convert pointer to address.
 *
 * @param pointer Pointer to convert.
 *
 */
template <typename T>
inline uint64_t to_address (T *pointer)
{
   return reinterpret_cast<uint64_t>(pointer);
}

/**
 * @brief Convert a machine address to a virtual address.
 *
 * @param address Address to convert.
 *
 */
uint64_t machine_to_virtual (uint64_t address);

/**
 * @brief Utility class to convert page frame number to/from the machine/pseudo address space.
 * 
 */
class Page_converter
{
public:
   /**
    * @brief Constructor.
    *
    * @param table Address of the conversion table.
    * @param size  Size of the conversion table.
    *
    */
   Page_converter (const uint64_t *table, uint64_t size);

   /**
    * @brief Destructor.
    *
    */
   ~Page_converter ();

   /**
    * @brief Index operator to perform page conversion.
    *
    */
   uint64_t operator[] (uint64_t page) const;

private:
   Page_converter ();
   Page_converter (const Page_converter &);
   Page_converter &operator= (const Page_converter &);

   const uint64_t *table;
   uint64_t size;

};

}

/**
 * @brief Memory interface class.
 *
 */
class Memory
{
public:

   /**
    * @brief Implementation for glibc export function __brk.
    *
    * @param address
    * @param __curbrk
    * 
    */
   void *brk (void *address);

   /**
    * @brief Address of page tables.
    *
    */
   const uint64_t CR3_virtual_address;

   /**
    * @brief Total number of pages available.
    *
    */
   const uint64_t total_pages;

   /**
    * @brief Convert pseudo pages to machine pages.
    *
    */
   memory::Page_converter pseudo_converter;

private:
   Memory ();
   ~Memory ();
   Memory (const Memory &);
   Memory (uint64_t CR3_virtual_address, uint64_t total_pages, uint64_t pseudo_converter_virtual_address);
   Memory &operator= (const Memory &);

   const uint64_t start_pseudo_page;
   const uint64_t end_pseudo_page;

   const uint64_t start_virtual_address;
   const uint64_t end_virtual_address;

   void *program_break;

   // allow access to the private constructor
   friend class Hypervisor;

};

} }

#endif  // llamaos_xen_memory_h_

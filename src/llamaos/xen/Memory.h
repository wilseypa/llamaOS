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

#include <stdint.h>

namespace llamaos {
namespace xen {

/**
 * @brief Convert an address to a page frame.
 *
 * @param address Address to convert.
 *
 */
inline uint64_t address_to_page (uint64_t address)
{
   return address >> 12;
}

/**
 * @brief Compute the page offset portion of an address.
 *
 * @param address Address to compute offset from.
 *
 */
inline uint64_t address_to_page_offset (uint64_t address)
{
   return address & 0xFFF;
}

/**
 * @brief Convert a page frame to an address.
 *
 * @param page Page frame to convert.
 *
 */
inline uint64_t page_to_address (uint64_t page)
{
   return page << 12;;
}

/**
 * @brief Convert address to pointer.
 *
 * @param address Address to convert.
 *
 */
template <typename T>
inline T *address_to_pointer (uint64_t address)
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
inline uint64_t pointer_to_address (T *pointer)
{
   return reinterpret_cast<uint64_t>(pointer);
}

/**
 * @brief Convert a machine page frame to a pseudo page frame.
 *
 */
uint64_t machine_to_pseudo_page (uint64_t page);

/**
 * @brief Convert a pseudo page frame to a machine page frame.
 *
 */
uint64_t pseudo_to_machine_page (uint64_t page);

/**
 * @brief Convert a machine address to a pseudo-physical address.
 *
 */
inline uint64_t machine_to_pseudo (uint64_t address)
{
   return (page_to_address (machine_to_pseudo_page (address_to_page (address))) | address_to_page_offset (address));
}

/**
 * @brief Convert a machine pointer to a pseudo-physical pointer.
 *
 */
template <typename T>
inline T *machine_to_psuedo (T *pointer)
{
   reinterpret_cast<T *>(machine_to_pseudo (reinterpret_cast<uint64_t>(pointer)));
}

/**
 * @brief Convert a pseudo-physical address to a virtual address.
 *
 */
inline uint64_t pseudo_to_virtual (uint64_t address)
{
   return address;
}

/**
 * @brief Convert a pseudo-physical pointer to a virtual pointer.
 *
 */
template <typename T>
inline T *pseudo_to_virtual (T *pointer)
{
   reinterpret_cast<T *>(pseudo_to_virtual (reinterpret_cast<uint64_t>(pointer)));
}

/**
 * @brief Convert a machine address to a virtual address.
 *
 */
inline uint64_t machine_to_virtual (uint64_t address)
{
   return pseudo_to_virtual (machine_to_pseudo (address));
}

/**
 * @brief Convert a machine pointer to a virtual pointer.
 *
 */
template <typename T>
inline T *machine_to_virtual (T *pointer)
{
   reinterpret_cast<T *>(machine_to_virtual (reinterpret_cast<uint64_t>(pointer)));
}

/**
 * @brief Convert a virtual address to a pseudo-physical address.
 *
 */
inline uint64_t virtual_to_pseudo (uint64_t address)
{
   return address;
}

/**
 * @brief Convert a virtual pointer to a pseudo-physical pointer.
 *
 */
template <typename T>
inline T *virtual_to_pseudo (T *pointer)
{
   reinterpret_cast<T *>(virtual_to_pseudo (reinterpret_cast<uint64_t>(pointer)));
}

/**
 * @brief Convert a pseudo-physical address to a machine address.
 *
 */
inline uint64_t pseudo_to_machine (uint64_t address)
{
   return (page_to_address (pseudo_to_machine_page (address_to_page (address))) | address_to_page_offset (address));
}

/**
 * @brief Convert a pseudo-physical pointer to a machine pointer.
 *
 */
template <typename T>
inline T *psuedo_to_machine (T *pointer)
{
   reinterpret_cast<T *>(pseudo_to_machine (reinterpret_cast<uint64_t>(pointer)));
}

/**
 * @brief Convert a virtual address to a machine address.
 *
 */
inline uint64_t virtual_to_machine (uint64_t address)
{
   return pseudo_to_machine (virtual_to_pseudo (address));
}

/**
 * @brief Convert a virtual pointer to a machine pointer.
 *
 */
template <typename T>
inline T *virtual_to_machine (T *pointer)
{
   reinterpret_cast<T *>(virtual_to_machine (reinterpret_cast<uint64_t>(pointer)));
}

// Assume 64-bit/long mode operation only (for now)

// Page-Map Level-4 (PML4)              bits 39-47
// Page-Directory-Pointer (PDP)         bits 30-38
// Page-directory (PD)                  bits 21-29
// Page-Table (PT)                      bits 12-20
// Physical-Page Offset                 bits 0-11

/**
 * @brief Page entry into a table of the Paging hierarchy.
 *
 */
class Page_entry
{
public:
   /**
    * @brief Present bit.
    *
    */
   static const uint64_t P;

   /**
    * @brief Read/Write bit.
    *
    */
   static const uint64_t RW;

   /**
    * @brief User/Supervisor bit.
    *
    */
   static const uint64_t US;

   /**
    * @brief Page-level write-through bit.
    *
    */
   static const uint64_t PWT;

   /**
    * @brief Page-level cache disable bit.
    *
    */
   static const uint64_t PCD;

   /**
    * @brief Accessed bit.
    *
    */
   static const uint64_t A;

   /**
    * @brief Address mask.
    *
    */
   static const uint64_t ADDR_MASK;

   /**
    * @brief Compute entry address.
    *
    */
   static uint64_t address (uint64_t value) { return value & ADDR_MASK; }

   /**
    * @brief Constructor.
    *
    */
   Page_entry (uint64_t index, uint64_t value);

   /**
    * @brief Copy constructor.
    *
    */
   Page_entry (const Page_entry & pe);

   /**
    * @brief Destructor.
    *
    */
   virtual ~Page_entry ();

   /**
    * @brief Test for present bit (P).
    *
    */
   bool present () const { return value & P; }

   /**
    * @brief Test for read/write bit (RW).
    *
    */
   bool writable () const { return value & RW; }

   /**
    * @brief Test for user/supervisor bit (US).
    *
    */
   bool user () const { return value & US; }

   /**
    * @brief Test for page-level write-through bit (PWT).
    *
    */
   bool page_level_write_through () const { return value & PWT; }

   /**
    * @brief Test for page-level cache diable bit (PCD).
    *
    */
   bool page_level_cache_disable () const { return value & PCD; }

   /**
    * @brief Test for accessed bit (A).
    *
    */
   bool accessed () const { return value & A; }

   /**
    * @brief Compute entry address.
    *
    */
   uint64_t address () const { return address (value); }

   /**
    * @brief Returns True if the entry is empty (null).
    *
    */
   bool empty () const { return (0 == value); }

   /**
    * @brief Get a formatted string of the value.
    *
    */
   const char *to_string () const;

   /**
    * @brief Entry index.
    *
    */
   const uint64_t index;

   /**
    * @brief Entry value.
    *
    */
   const uint64_t value;

private:
   Page_entry ();
   Page_entry &operator= (const Page_entry &);

};

// forward declarations
class PT;
class PD;
class PDP;

/**
 * @brief Page entry into a table of the Paging hierarchy.
 *
 */
class PTE : public Page_entry
{
public:
   /**
    * @brief Constructor.
    *
    */
   PTE (uint64_t index, uint64_t value);

   /**
    * @brief Destructor.
    *
    */
   virtual ~PTE ();

};

/**
 * @brief Page entry into a table of the Paging hierarchy.
 *
 */
class PDE : public Page_entry
{
public:
   /**
    * @brief Constructor.
    *
    */
   PDE (uint64_t index, uint64_t value);

   /**
    * @brief Destructor.
    *
    */
   virtual ~PDE ();

   /**
    * @brief Convert entry to a table.
    *
    */
   operator PT ();

};

/**
 * @brief Page entry into a table of the Paging hierarchy.
 *
 */
class PDPE : public Page_entry
{
public:
   /**
    * @brief Constructor.
    *
    */
   PDPE (uint64_t index, uint64_t value);

   /**
    * @brief Destructor.
    *
    */
   virtual ~PDPE ();

   /**
    * @brief Convert entry to a PD.
    *
    */
   operator PD ();

};

/**
 * @brief Page entry into a table of the Paging hierarchy.
 *
 */
class PML4E : public Page_entry
{
public:
   /**
    * @brief Constructor.
    *
    */
   PML4E (uint64_t index, uint64_t value);

   /**
    * @brief Destructor.
    *
    */
   virtual ~PML4E ();

   /**
    * @brief Convert entry to a PDP.
    *
    */
   operator PDP ();

};

/**
 * @brief Page table.
 *
 */
class PT
{
public:
   /**
    * @brief Constructor.
    *
    */
   PT (const PDE &);

   /**
    * @brief Copy constructor.
    *
    */
   PT (const PT &);

   /**
    * @brief Destructor.
    *
    */
   virtual ~PT ();

   /**
    * @brief Create an entry object.
    *
    * @param index Entry index.
    *
    */
   PTE operator[] (uint64_t index) const;

   /**
    * @brief Create an entry object.
    *
    * @param address Entry address.
    *
    */
   PTE get_entry (uint64_t address) const;

   /**
    * @brief Get address of entry.
    *
    * @param index Entry index.
    *
    */
   uint64_t get_entry_address (uint64_t index) const { return pointer_to_address (pointer + index); }

private:
   PT ();
   PT &operator= (const PT &);

   PDE entry;
   uint64_t *pointer;

};

/**
 * @brief Page-directory table.
 *
 */
class PD
{
public:
   /**
    * @brief Constructor.
    *
    */
   PD (const PDPE &);

   /**
    * @brief Copy constructor.
    *
    */
   PD (const PD &);

   /**
    * @brief Destructor.
    *
    */
   virtual ~PD ();

   /**
    * @brief Create an entry object.
    *
    * @param index Entry index.
    *
    */
   PDE operator[] (uint64_t index) const;

   /**
    * @brief Create an entry object.
    *
    * @param address Entry address.
    *
    */
   PDE get_entry (uint64_t address) const;

   /**
    * @brief Get address of entry.
    *
    * @param index Entry index.
    *
    */
   uint64_t get_entry_address (uint64_t index) const { return pointer_to_address (pointer + index); }

private:
   PD ();
   PD &operator= (const PD &);

   PDPE entry;
   uint64_t *pointer;

};

/**
 * @brief Page-directory-pointer table.
 *
 */
class PDP
{
public:
   /**
    * @brief Constructor.
    *
    */
   PDP (const PML4E &);

   /**
    * @brief Copy constructor.
    *
    */
   PDP (const PDP &);

   /**
    * @brief Destructor.
    *
    */
   virtual ~PDP ();

   /**
    * @brief Create an entry object.
    *
    * @param index Entry index.
    *
    */
   PDPE operator[] (uint64_t index) const;

   /**
    * @brief Create an entry object.
    *
    * @param address Entry address.
    *
    */
   PDPE get_entry (uint64_t address) const;

   /**
    * @brief Get address of entry.
    *
    * @param index Entry index.
    *
    */
   uint64_t get_entry_address (uint64_t index) const { return pointer_to_address (pointer + index); }

private:
   PDP ();
   PDP &operator= (const PDP &);

   class PML4E entry;
   uint64_t *pointer;

};

/**
 * @brief Page-map level 4 table.
 *
 */
class PML4
{
public:
   /**
    * @brief Constructor.
    *
    * @param address Virtual address of Page-map level 4 table.
    *
    */
   PML4 (uint64_t address);

   /**
    * @brief Copy constructor.
    *
    */
   PML4 (const PML4 &);

   /**
    * @brief Destructor.
    *
    */
   virtual ~PML4 ();

   /**
    * @brief Create an entry object.
    *
    * @param index Entry index.
    *
    */
   PML4E operator[] (uint64_t index) const;

   /**
    * @brief Create an entry object.
    *
    * @param address Entry address.
    *
    */
   PML4E get_entry (uint64_t address) const;

   /**
    * @brief Get address of entry.
    *
    * @param index Entry index.
    *
    */
   uint64_t get_entry_address (uint64_t index) const { return pointer_to_address (pointer + index); }

private:
   PML4 ();
   PML4 &operator= (const PML4 &);

   uint64_t *pointer;

};

/**
 * @brief Memory interface class.
 *
 */
class Memory
{
public:
   /**
    * @brief Constructor.
    *
    * @param CR3         Virtual address of page tables.
    * @param total_pages Total number of pages alloted.
    *
    */
   Memory (uint64_t CR3, uint64_t total_pages);

   /**
    * @brief Destructor.
    *
    */
   virtual ~Memory ();

   /**
    * @brief Get virtual start adddress of heap.
    *
    */
   uint64_t _start_address () const { return start_address; }

   /**
    * @brief Get virtual end adddress of heap.
    *
    */
   uint64_t _end_address () const { return end_address; }

private:
   Memory ();
   Memory (const Memory &);
   Memory &operator= (const Memory &);

   PML4 pml4;

   const uint64_t start_page;
   const uint64_t end_page;

   const uint64_t start_address;
   const uint64_t end_address;

};

} }

#endif  // llamaos_xen_memory_h_

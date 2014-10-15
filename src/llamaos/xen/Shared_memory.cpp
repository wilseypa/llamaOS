/*
Copyright (c) 2014, William Magato
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

#include <cstring>

#include <iostream>
#include <sstream>

#include <llamaos/xen/Hypervisor.h>
#include <llamaos/xen/Shared_memory.h>
#include <llamaos/llamaOS.h>

using std::cout;
using std::endl;
using std::string;
using std::istringstream;
using std::vector;

using namespace llamaos;
using llamaos::xen::Hypervisor;
using llamaos::xen::Shared_memory;
using llamaos::xen::Shared_memory_creator;
using llamaos::xen::Shared_memory_user;

// static const int SHARED_PAGES = 6080;
// static const int SHARED_PAGES = 4096;
static const int SHARED_PAGES = 2048;

// static const int MAX_ENTRIES = 31; // NEED MORE !!!!
static const int MAX_ENTRIES = 28;
// static const int MAX_ENTRIES = 48;
static const int MAX_NAME = 55;
static const int MAX_ALIAS = 47;

#pragma pack(1)
typedef struct
{
   uint8_t name [MAX_NAME+1];
   uint8_t alias [MAX_ALIAS+1];
   uint64_t lock;
   uint64_t lock2;
   uint64_t offset;
   uint64_t size;

} directory_entry_t;

typedef struct
{
   uint64_t nodes;
   uint64_t barrier_count;
   bool barrier_sense;

   uint64_t next_offset;

   directory_entry_t entries [MAX_ENTRIES];

} directory_t;
#pragma pack()

Shared_memory *Shared_memory::create (const std::string &name, domid_t domid)
{
   // check if resource node
   size_t pos = name.find("-r.");

   if (pos != string::npos)
   {
      istringstream s(name.substr(pos+3));
      int nodes;
      s >> nodes;

      return new Shared_memory_creator (domid, nodes); 
   }

   pos = name.find("-");

   if (pos != string::npos)
   {
      istringstream s(name.substr(pos+1));
      int node;
      s >> node;

      return new Shared_memory_user (domid, node); 
   }

   return nullptr;
}

Shared_memory::Shared_memory ()
   :  barrier_sense(false)
{
   
}

Shared_memory::~Shared_memory ()
{
   
}

int Shared_memory::open (const std::string &name) const
{
   directory_t *directory = reinterpret_cast<directory_t *>(get_pointer ());

   if (directory != nullptr)
   {
//   cout << "nodes: " << directory->nodes << endl;
//      cout << "opening " << name << endl;

      for (int i = 0; i < MAX_ENTRIES; i++)
      {
//         cout << "   [" << i << "] " << directory->entries [i].name << endl;

         // if (__sync_lock_test_and_set(&directory->entries [i].lock, 1) == 0)
         if (__sync_fetch_and_add(&directory->entries [i].lock, 1) == 0)
         {
            cout << "   writing to entry " << i << ", " << name.c_str () << endl;
            strncpy(reinterpret_cast<char *>(directory->entries [i].name), name.c_str (), MAX_NAME);
            wmb();
            return i + 200;
         }

//         cout << "   searching in entry " << i << endl;

         while (directory->entries [i].name [0] == '\0')
         {
            cout << "   open waiting for entry name to be written: " << i << endl;
            mb();
         }

         if (strncmp(name.c_str(), reinterpret_cast<const char *>(directory->entries [i].name), MAX_NAME) == 0)
         {
//            cout << "   found in entry " << i << endl;
            return i + 200;
         }
      }
   }

   return -1;
}

void *Shared_memory::map (int fd, uint64_t size) const
{
   uint8_t *pointer = get_pointer ();
   directory_t *directory = reinterpret_cast<directory_t *>(pointer);

   if (directory != nullptr)
   {
//   cout << "nodes: " << directory->nodes << endl;
      cout << "mapping fd " << fd << ", size " << size << endl;
      int index = fd - 200;
      // uint64_t offset = PAGE_SIZE;

      if (__sync_fetch_and_add(&directory->entries [index].lock2, 1) == 0)
      {
         uint64_t offset = __sync_fetch_and_add(&directory->next_offset, size);

         directory->entries [index].offset = offset;
         directory->entries [index].size = size;
         wmb();
      }

      while (directory->entries [index].offset == 0)
      {
         cout << "   map waiting for entry offset to be written..." << index << endl;
         mb();
      }

      // for (int i = 0; i < index; i++)
      // {
      //    offset += directory->entries [i].size;
      // }

      // directory->entries [index].offset = offset;

      if ((directory->entries [index].offset + size) > (SHARED_PAGES * PAGE_SIZE))
      {
         cout << "exceeded shared memory space!!!!!" << endl;
         // throw
         for (;;);
         return nullptr;
      }

      cout << "     mapped to offset " << directory->entries [index].offset << endl;
      return pointer + directory->entries [index].offset;
   }

   return nullptr;
}

void Shared_memory::unmap (int ) const
{
   
}

void *Shared_memory::get (int fd) const
{
   uint8_t *pointer = get_pointer ();
   directory_t *directory = reinterpret_cast<directory_t *>(pointer);

   if (directory != nullptr)
   {
//   cout << "nodes: " << directory->nodes << endl;
      return pointer + directory->entries [fd - 200].offset;
   }

   return nullptr;
}

int Shared_memory::get_size () const
{
   directory_t *directory = reinterpret_cast<directory_t *>(get_pointer ());

   if (directory != nullptr)
   {
//   cout << "nodes: " << directory->nodes << endl;
      for (int i = 0; i < MAX_ENTRIES; i++)
      {
         if (!directory->entries [i].lock)
         {
            return i;
         }
      }

      return MAX_ENTRIES;
   }

   return 0;
}

vector<string> Shared_memory::get_names () const
{
   vector<string> names;
   directory_t *directory = reinterpret_cast<directory_t *>(get_pointer ());

   if (directory != nullptr)
   {
//   cout << "nodes: " << directory->nodes << endl;
      for (int i = 0; i < MAX_ENTRIES; i++)
      {
//         if (directory->entries [i].name [0] == '\0')
//         {
//            break;
//         }

         if (!directory->entries [i].lock)
         {
            break;
         }

         while (directory->entries [i].name [0] == '\0')
         {
            cout << "   get_names waiting for entry to be written..." << i << endl;
            mb();
         }

         names.push_back (reinterpret_cast<const char *>(directory->entries [i].name));
      }
   }

   return names;
}

void Shared_memory::put_alias (const string &name, const string &alias) const
{
   directory_t *directory = reinterpret_cast<directory_t *>(get_pointer ());

   if (directory != nullptr)
   {
//   cout << "nodes: " << directory->nodes << endl;
      for (int i = 0; i < MAX_ENTRIES; i++)
      {
//         if (directory->entries [i].name [0] == '\0')
//         {
//            break;
//         }
         if (!directory->entries [i].lock)
         {
            break;
         }

         while (directory->entries [i].name [0] == '\0')
         {
            cout << "   put_alias waiting for entry name to be written..." << i << endl;
            mb();
         }

         if (strncmp(name.c_str(), reinterpret_cast<const char *>(directory->entries [i].name), MAX_NAME) == 0)
         {
            strncpy(reinterpret_cast<char *>(directory->entries [i].alias), alias.c_str (), MAX_ALIAS);
            break;
         }
      }
   }
}

string Shared_memory::get_name (const string &alias) const
{
   directory_t *directory = reinterpret_cast<directory_t *>(get_pointer ());

   if (directory != nullptr)
   {
//   cout << "nodes: " << directory->nodes << endl;
      for (int i = 0; i < MAX_ENTRIES; i++)
      {
//         if (directory->entries [i].name [0] == '\0')
//         {
//            break;
//         }
         if (!directory->entries [i].lock)
         {
            break;
         }

         while (directory->entries [i].alias [0] == '\0')
         {
            cout << "   get_name waiting for entry alias to be written..." << i << endl;
            mb();
         }

         if (strncmp(alias.c_str(), reinterpret_cast<const char *>(directory->entries [i].alias), MAX_ALIAS) == 0)
         {
            return reinterpret_cast<const char *>(directory->entries [i].name);
         }
      }
   }

   return "name not found";
}

void Shared_memory::barrier ()
{
   directory_t *directory = reinterpret_cast<directory_t *>(get_pointer ());
//   cout << "nodes: " << directory->nodes << endl;

   barrier_sense ^= true;

   if (__sync_sub_and_fetch (&directory->barrier_count, 1) == 0)
   {
      cout << "resetting barrier..." << endl;
         cout << "barrier: " << directory->barrier_count
              << ", " << directory->barrier_sense
              << ", " << barrier_sense << endl;
   cout << "nodes: " << directory->nodes << endl;

      directory->barrier_count = directory->nodes;
      wmb();

      directory->barrier_sense = barrier_sense;
         cout << "barrier: " << directory->barrier_count
              << ", " << directory->barrier_sense
              << ", " << barrier_sense << endl;
   cout << "nodes: " << directory->nodes << endl;
   }
   else
   {
         cout << "barrier: " << directory->barrier_count
              << ", " << directory->barrier_sense
              << ", " << barrier_sense << endl;
   cout << "nodes: " << directory->nodes << endl;
      while (barrier_sense != directory->barrier_sense)
      {
         mb();
      }
         cout << "barrier: " << directory->barrier_count
              << ", " << directory->barrier_sense
              << ", " << barrier_sense << endl;
   cout << "nodes: " << directory->nodes << endl;
   }
}

static uint8_t *create_pointer (domid_t domid, int nodes)
{
   Hypervisor *hypervisor = Hypervisor::get_instance ();

   const unsigned int size = SHARED_PAGES * PAGE_SIZE;
   uint8_t *pointer = static_cast<uint8_t *>(aligned_alloc (PAGE_SIZE, size));
   memset(static_cast<void *>(pointer), 0, size);

   for (int i = 0; i < nodes; i++)
   {
      for (int j = 0; j < SHARED_PAGES; j++)
      {
         hypervisor->grant_table.grant_access (domid + 1 + i, &pointer [j * PAGE_SIZE]);
      }
   }

   return pointer;
}

Shared_memory_creator::Shared_memory_creator (domid_t domid, int nodes)
   : pointer(create_pointer(domid, nodes))
{
   directory_t *directory = reinterpret_cast<directory_t *>(pointer);

   directory->nodes = nodes;
   directory->barrier_count = nodes;
   directory->barrier_sense = false;

   directory->next_offset = 2 * PAGE_SIZE;

//   cout << "nodes: " << directory->nodes << endl;
}

Shared_memory_creator::~Shared_memory_creator ()
{
   delete pointer;
}

uint8_t *Shared_memory_creator::get_pointer () const
{
   return pointer;
}

Shared_memory_user::Shared_memory_user (domid_t domid, int node)
   : grant_map(domid-1-node, (node * SHARED_PAGES), SHARED_PAGES)
//   : grant_map(domid-1-node, 49151 - (node * SHARED_PAGES), SHARED_PAGES)
//   : grant_map(domid-1-node, 32767 - (node * SHARED_PAGES), SHARED_PAGES)
//   : grant_map(domid-1-node, 16383 - (node * SHARED_PAGES), SHARED_PAGES)
{
   directory_t *directory = reinterpret_cast<directory_t *>(get_pointer ());

   cout << "nodes: " << directory->nodes << endl;
}

uint8_t *Shared_memory_user::get_pointer () const
{
   return reinterpret_cast<uint8_t *>(grant_map.get_pointer ());
}

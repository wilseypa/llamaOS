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

#ifndef llamaos_xen_shared_memory_h_
#define llamaos_xen_shared_memory_h_

#include <cstdint>

#include <string>

#include <xen/xen.h>

#include <llamaos/xen/Grant_map.h>

namespace llamaos {
namespace xen {

/**
 * @brief Shared memory wrapper class.
 *
 */
class Shared_memory
{
public:
   static Shared_memory *create (const std::string &name, domid_t domid);

   Shared_memory ();
   virtual ~Shared_memory ();

   int open (const std::string &name) const;
   void *map (int fd, uint64_t size) const;
   void unmap (int fd) const;

   void *get (int fd) const;

   int get_size () const;
   std::vector<std::string> get_names () const;

   void put_alias (const std::string &name, const std::string &alias) const;
   std::string get_name (const std::string &alias) const;

   void barrier ();

protected:
   virtual uint8_t *get_pointer () const = 0;

private:
   Shared_memory (const Shared_memory &);
   Shared_memory &operator= (const Shared_memory &);

   bool barrier_sense;

};

class Shared_memory_creator : public Shared_memory
{
public:
   Shared_memory_creator (domid_t domid, int nodes);
   virtual ~Shared_memory_creator ();

protected:
   virtual uint8_t *get_pointer () const;

private:
   Shared_memory_creator ();
   Shared_memory_creator (const Shared_memory_creator &);
   Shared_memory_creator &operator= (const Shared_memory_creator &);

   uint8_t *const pointer;

};

class Shared_memory_user : public Shared_memory
{
public:
   Shared_memory_user (domid_t domid, int node);

protected:
   virtual uint8_t *get_pointer () const;

private:
   Shared_memory_user ();
   Shared_memory_user (const Shared_memory_user &);
   Shared_memory_user &operator= (const Shared_memory_user &);

   Grant_map<char> grant_map;

};

} }

#endif  // llamaos_xen_shared_memory_h_

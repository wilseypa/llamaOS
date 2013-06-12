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

#ifndef llamaos_xen_block_h_
#define llamaos_xen_block_h_

#include <cstdint>
#include <cstring>
#include <sstream>
#include <string>

#include <xen/xen.h>
#include <xen/event_channel.h>

#include <xen/io/blkif.h>
#include <xen/io/console.h>

namespace llamaos {
namespace xen {

class Block
{
public:
   Block (const std::string &key);
   virtual ~Block ();

   ssize_t read (void *buf, size_t nbytes);
   off64_t lseek64 (off64_t offset, int whence);

   const std::string frontend_key;

   std::string get_name () const { return name; }
   std::string get_dev () const { return dev; }
   unsigned int get_size () const { return size; }

private:
   Block ();
   Block (const Block &);
   Block &operator= (const Block &);

   blkif_sring_t *const shared;

   evtchn_port_t port;

   std::string name;
   std::string dev;
   unsigned int size;

   unsigned int position;

   std::string data;

};

} }

#endif  // llamaos_xen_block_h_

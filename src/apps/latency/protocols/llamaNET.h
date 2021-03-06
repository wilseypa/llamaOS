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

#ifndef latency_protocols_llamanet_h_
#define latency_protocols_llamanet_h_

#include <latency/Protocol.h>
#include <llamaos/net/llamaNET.h>

namespace latency {
namespace protocols {

class llamaNET : public Protocol
{
public:
   static Protocol *create (int argc, char *argv []);

   llamaNET (int argc, char *argv []);
   virtual ~llamaNET ();

   virtual bool root_node ();

   virtual bool startup (unsigned long max_msg_size);
   virtual bool cleanup ();

   virtual bool run_verify (unsigned long msg_size);
   virtual bool run_trial (unsigned long msg_size, unsigned long trial_number);

private:
   llamaNET ();
   llamaNET (const llamaNET &);
   llamaNET &operator= (const llamaNET &);

   const uint32_t node;
   const bool client;
   llamaos::net::llamaNET interface;

};

} }

#endif  // latency_protocols_llamanet_h_

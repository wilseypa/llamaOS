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

#ifndef llamaos_xen_hypervisor_h_
#define llamaos_xen_hypervisor_h_

#include <cstdint>

#include <xen/xen.h>

#include <llamaos/xen/Console.h>
#include <llamaos/xen/Events.h>
#include <llamaos/xen/Grant_table.h>
#include <llamaos/xen/Traps.h>
#include <llamaos/xen/Xenstore.h>

namespace llamaos {
namespace xen {

/**
 * @brief Hypervisor class.
 *
 */
class Hypervisor
{
public:
   /**
    * @brief Allow public access to singleton Hypervisor object.
    *
    */
   static Hypervisor *get_instance ();

   /**
    * @brief Only public constructor (throws if called more than once).
    *
    */
   Hypervisor (const start_info_t *start_info);

   /**
    * @brief Destructor.
    *
    */
   virtual ~Hypervisor ();

   void initialize ();
   
   /**
    * @brief Xen start_info structure.
    *
    */
   const start_info_t start_info;

   /**
    * @brief Xen shared_info structure.
    *
    */
   shared_info_t *const shared_info;

   /**
    * @brief Systme console.
    *
    */
   Console console;

   Traps traps;
   Events events;
   Grant_table grant_table;
   Xenstore xenstore;

   std::string name;
   int domid;

   int argc;
   char *argv [64];

private:
   Hypervisor ();
   Hypervisor (const Hypervisor &);
   Hypervisor &operator= (const Hypervisor &);

};

} }

#endif  // llamaos_xen_hypervisor_h_

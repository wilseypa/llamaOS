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

#include <stdexcept>

#include <llamaos/memory/memory.h>
#include <llamaos/xen/Hypervisor.h>
#include <llamaos/trace.h>

using namespace std;
using namespace llamaos;
using namespace llamaos::memory;
using namespace llamaos::xen;

static Hypervisor *instance = nullptr;

static const start_info_t enforce_single_instance (const start_info_t *start_info)
{
   if (nullptr != instance)
   {
      throw runtime_error ("duplicate Hypervisor objects created");
   }

   if (nullptr == start_info)
   {
      throw runtime_error ("invalid start_info pointer");
   }

   return *start_info;
}

Hypervisor *Hypervisor::get_instance ()
{
   if (nullptr == instance)
   {
      throw runtime_error ("invalid Hypervisor instance");
   }

   return instance;
}

Hypervisor::Hypervisor (const start_info_t *start_info)
   :  start_info(enforce_single_instance(start_info)),
      console(machine_page_to_virtual_pointer<xencons_interface>(start_info->console.domU.mfn), start_info->console.domU.evtchn),
      xenstore(machine_page_to_virtual_pointer<xenstore_domain_interface>(start_info->store_mfn), start_info->store_evtchn)
{
   instance = this;
   trace ("Hypervisor created.\n");
}

Hypervisor::~Hypervisor ()
{

}

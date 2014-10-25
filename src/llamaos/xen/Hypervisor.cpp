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

#include <unistd.h>

#include <iostream>
#include <stdexcept>

#include <llamaos/memory/Memory.h>
#include <llamaos/xen/Hypercall.h>
#include <llamaos/xen/Hypervisor.h>
#include <llamaos/llamaOS.h>
#include <llamaos/Trace.h>

using namespace std;
using namespace llamaos;
using namespace llamaos::memory;
using namespace llamaos::xen;

static Hypervisor *instance = nullptr;

static const start_info_t enforce_single_instance (const start_info_t *start_info)
{
   if (nullptr != instance)
   {
//      throw runtime_error ("duplicate Hypervisor objects created");
   }

   if (nullptr == start_info)
   {
//      throw runtime_error ("invalid start_info pointer");
   }

   return *start_info;
}

// defined in entry assembler
extern shared_info_t shared_info;

// used in entry assembler
shared_info_t *HYPERVISOR_shared_info = 0;

static shared_info_t *map_shared_info (const start_info_t *start_info)
{
   if (Hypercall::update_va_mapping (pointer_to_address(&shared_info), start_info->shared_info))
   {
      // !BAM try to get rid of this global
      HYPERVISOR_shared_info = &shared_info;

      return &shared_info;
   }

   return 0;
}

// static void virq_timer_event (void *data)
// {
//   trace ("calling virq\n");
//   Hypervisor *hypervisor = reinterpret_cast<Hypervisor *> (data);

   // cout << "virq_timer_event" << endl;
//    cout.flush ();
//    fflush (stdout);

   // hit up both the console and the xenstore with an event_handler
//   Hypercall::event_channel_send (hypervisor->console.port);
//   Hypercall::event_channel_send (hypervisor->xenstore.port);
// }

Hypervisor *Hypervisor::get_instance ()
{
   if (nullptr == instance)
   {
//      throw runtime_error ("invalid Hypervisor instance");
   }

   return instance;
}

Hypervisor::Hypervisor (const start_info_t *start_info)
   :  start_info(enforce_single_instance(start_info)),
      shared_info(map_shared_info(start_info)),
      console(machine_page_to_virtual_pointer<xencons_interface>(start_info->console.domU.mfn), start_info->console.domU.evtchn),
      traps(),
      events(shared_info),
      grant_table(),
      xenstore(machine_page_to_virtual_pointer<xenstore_domain_interface>(start_info->store_mfn), start_info->store_evtchn),
      name(xenstore.read_string ("name")),
      domid(xenstore.read<domid_t>("domid")),
      shared_memory(nullptr),
      argc(0),
      blocks()
{
   instance = this;
   trace ("Hypervisor created.\n");
}

Hypervisor::~Hypervisor ()
{
   delete shared_memory;
}

void Hypervisor::initialize ()
{
//   sleep (1);

//   for (;;) { cout << "name: " << xenstore.read_string ("name") << endl; }
//   long var_long = 0; for (;;) { cout << "long: " << var_long++ << endl; }

//   name = xenstore.read_string ("name"); // .c_str ();
//   trace ("Xenstore name: %s\n", name.c_str ()); 
//   domid = xenstore.read<domid_t>("domid");
//   trace ("Xenstore domid: %d\n", domid); 

//   trace ("float math: %f, %f, %f\n", 1.0f / 2638.0f, 25 / 43219.0f, 1 / 3.0f);
//   trace ("double math: %lf, %lf, %lf\n", 1.0 / 2638.0, 25 / 43219.0, 1 / 3.0);

//   trace ("binding to VIRQ_TIMER...\n");
//   events.bind_virq (VIRQ_TIMER, virq_timer_event, this);

//   events.bind (console.port, console.event_handler, &console);

//   if (grant_table.max_frames < FRAME_LIST_SIZE)
//   {
//      cout << "ERROR: Grant table max frames " << grant_table.max_frames
//           << " is less than llamaOS configuration "<< FRAME_LIST_SIZE << endl;
//      cout << "increase max frames with Xen command line parameter: gnttab_max_nr_frames" << endl;
//      exit(-100);
//   }

   for (int i = 0; i < 64; i++)
   {
      argv [i] = '\0';
   }

   // go looking for block devices
   vector<string> keys = xenstore.list("device/vbd");
//   cout << "keys: " << keys.size() << endl;

   for (size_t i = 0; i < keys.size(); i++)
   {
//      cout << "keys [" << i << "]: " << keys [i] << endl;
      blocks.push_back(new Block(string("device/vbd/") + keys [i]));
   }

   shared_memory = Shared_memory::create(name, domid);

}

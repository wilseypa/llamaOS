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

#include <cstdint>
#include <cstring>

#include <xen/xen.h>
#include <xen/features.h>

#include <llamaos/xen/Hypervisor.h>
#include <llamaos/llamaOS.h>
#include <llamaos/Trace.h>

using namespace std;
using namespace llamaos;
using namespace llamaos::xen;

uint8_t xen_features [XENFEAT_NR_SUBMAPS * 32];

int main (int argc, char *argv []);

void entry_llamaOS (start_info_t *start_info)
{
   try
   {
      // create the one and only hypervisor object
      trace ("Creating Hypervisor...\n");
      Hypervisor hypervisor (start_info);

      // start the application
      char *argv [2];
      argv [0] = const_cast<char *>("llamaOS");
      argv [1] = nullptr;

      trace ("Before application main()...\n");

      main (1, argv);

      trace ("After application main()...\n");
   }
   catch (const std::runtime_error &e)
   {
      trace ("*** runtime_error: %s ***\n", e.what ());
   }
   catch (...)
   {
      trace ("*** unknown exception ***\n");
   }
}

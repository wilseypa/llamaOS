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

#include <iostream>

#include <llamaos/xen/Hypercall.h>
#include <llamaos/xen/Hypervisor.h>
#include <llamaos/trace.h>

using namespace std;
using namespace llamaos;
using namespace llamaos::xen;

int main (int /* argc */, char ** /* argv [] */)
{
   cout << "running e1000e llamaNET domain...\n" << endl;

   uint32_t frames = 0;
   uint32_t max_frames = 0;
   int16_t status = 0;

   if (!Hypercall::grant_table_query_size (frames, max_frames, status))
   {
      cout << "Hypercall::grant_table_query_size FAILED" << endl;
   }
   cout << "grant table frames: " << frames << endl;
   cout << "grant table max frames: " << max_frames << endl;
   cout << "grant table status: " << status << endl;

   unsigned long frame_list [6] = { 0 };
   if (!Hypercall::grant_table_setup_table (5, frame_list))
   {
      cout << "Hypercall::grant_table_query_size FAILED" << endl;
   }
   cout << "frame_list [0]: " << frame_list [0] << endl;
   cout << "frame_list [1]: " << frame_list [1] << endl;
   cout << "frame_list [2]: " << frame_list [2] << endl;
   cout << "frame_list [3]: " << frame_list [3] << endl;
   cout << "frame_list [4]: " << frame_list [4] << endl;
   cout << "frame_list [5]: " << frame_list [5] << endl;

   if (!Hypercall::grant_table_query_size (frames, max_frames, status))
   {
      cout << "Hypercall::grant_table_query_size FAILED" << endl;
   }
   cout << "grant table frames: " << frames << endl;
   cout << "grant table max frames: " << max_frames << endl;
   cout << "grant table status: " << status << endl;

   int backend_id = Hypervisor::get_instance ()->xenstore.read<int>("device/pci/0/backend-id");

   cout << "backend-id: " << backend_id << endl;
   
   return 0;
}

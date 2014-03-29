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

#include <cstdlib>
#include <sys/time.h>

#include <iostream>

#include <llamaos/memory/Memory.h>
#include <llamaos/xen/Hypercall.h>
#include <llamaos/llamaOS.h>

using namespace std;
using namespace llamaos;
using namespace llamaos::memory;
using namespace llamaos::xen;

// simple guest instance should just output text to console
int main (int argc, char *argv [])
{
   cout << endl << "running memory test app..." << endl;

   const int mem_size = 2 * 1024 * 1024;
   const int mem_pages = mem_size / PAGE_SIZE;
   volatile char *mem = static_cast<volatile char *>(aligned_alloc (PAGE_SIZE, mem_size));

   struct timeval tv1;
   struct timeval tv2;

   cout << "memory intensive logic with cache..." <<endl;

   volatile double d = 0.0;

   gettimeofday (&tv1, 0);

   for (int j = 0; j < 1000; j++)
   {
      mem [0] = 4.3;
      mem [1] = 2.3;

      for (int i = 2; i < mem_size; i++)
      {
         d = 3.1 * mem [i-1] + mem [i-2] + 5.5;
      }
   }

   gettimeofday (&tv2, 0);

   cout << "time is " << ((tv2.tv_sec - tv1.tv_sec) * 1000000UL) + tv2.tv_usec - tv1.tv_usec << " usec" << endl;
   cout << "   d = " << d << endl;

   for (unsigned int i = 0; i < mem_pages; i++)
   {
      Hypercall::update_va_mapping_nocache (
               pointer_to_address (mem + (i * PAGE_SIZE)),
               virtual_pointer_to_machine_address(mem + (i * PAGE_SIZE)));
   }

   cout << "memory intensive logic without cache..." <<endl;

   gettimeofday (&tv1, 0);

   for (int j = 0; j < 1000; j++)
   {
      mem [0] = 4.3;
      mem [1] = 2.3;

      for (int i = 2; i < mem_size; i++)
      {
         d = 3.1 * mem [i-1] + mem [i-2] + 5.5;
      }
   }

   gettimeofday (&tv2, 0);

   cout << "time is " << ((tv2.tv_sec - tv1.tv_sec) * 1000000UL) + tv2.tv_usec - tv1.tv_usec << " usec" << endl;
   cout << "   d = " << d << endl;

   return 0;
}

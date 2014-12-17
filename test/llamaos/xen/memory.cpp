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

#include <cstring>

#include <iostream>

#include <llamaos/memory/Memory.h>

using namespace std;
using namespace llamaos::memory;

volatile void *ptrs [1024];

const bool should_leak = false;

int main (int argc, char *argv [])
{
   cout << "running memory stress test for malloc..." << endl;

   if (should_leak)
   {
      cout <<"   this test is leaking..." << endl;
   }

   for (int i = 0; i < 1024; i++)
   {
      ptrs [i] = (volatile void *)malloc (1024);

      cout << "   program break: " << hex << get_program_break () << endl;

      memset ((void *)ptrs [i], 0, 1024);

      if (!should_leak)
      {
         free((void *)ptrs[i]);
      }
   }

   cout << "running memory stress test for new..." << endl;

   for (int i = 0; i < 1024; i++)
   {
      ptrs [i] = (volatile void *)new char [1024];

      cout << "   program break: " << hex << get_program_break () << endl;

      memset ((void *)ptrs [i], 0, 1024);

      if (!should_leak)
      {
         delete (char *)ptrs[i];
      }
   }

   cout << "done with memory stress test." << endl;
   return 0;
}

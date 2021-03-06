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

#include <stdio.h>
// #include <sys/time.h>
#include <time.h>
// #include <sys/types.h>

#include <iostream>

#include <llamaos/memory/Memory.h>

using namespace std;
using namespace llamaos::memory;

// simple guest instance should just output text to console
int main (int argc, char *argv [])
{
   cout << endl << "hello llamaOS" << endl;
   cout.flush ();
   cout << endl;

   cout << "sizeof long " << sizeof(long) << endl;

   cout << "program break: " << (pointer_to_address(get_program_break ()) / 1024.0) / 1024.0 << endl;


   cout << "argc: " << argc << endl;

   for (int i = 0; i < argc; i++)
   {
      cout << "argv[" << i << "]: " << argv [i] << endl;
   }

   double third = (1.0 / 3.0);
   cout << "print floats again: " << third << endl;
#if 0
      char data = 'a';
      for (;;)
      {
         cout << data;
         if (data == 'z')
         {
            data = 'a';
         }
         else
         {
            data++;
         }
      }
#endif

   cout << "time returns " << time((time_t *) NULL) << endl;

   errno = 0;
   perror ("test message");
   perror ("test message");

   errno = 0;
   FILE *fp = fdopen (1, "w");

   if (fp == NULL)
   {
      perror ("fdopen failed");
   }
   else
   {
      perror ("fdopen success");
   }

   return 0;
}

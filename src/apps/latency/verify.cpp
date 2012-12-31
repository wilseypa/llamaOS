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

#include <latency/verify.h>

using namespace std;

void latency::mark_data_alpha (unsigned char *buffer, unsigned long length)
{
   unsigned long j = 0;

   // put alpha data (A B C D ...)
   for (unsigned long i = 0; i < length; i++)
   {
      buffer [i] = ('A' + (++j % 26));
   }
}

bool latency::verify_data_alpha (const unsigned char *buffer, unsigned long length)
{
   unsigned long j = 0;
   unsigned char c;

   for (unsigned long i = 0; i < length; i++)
   {
      c = 'A' + (++j % 26);

      if (buffer [i] != c)
      {
         cout << "verify alpha failed (" << buffer [i] << " != " << c << ") @ index " << i << endl;
         return false;
      }
   }

   return true;
}

void latency::mark_data_numeric (unsigned char *buffer, unsigned long length)
{
   unsigned long j = 0;

   // put num data (0 1 2 3 ...)
   for (unsigned long i = 0; i < length; i++)
   {
      buffer [i] = ('0' + (++j % 10));
   }
}

bool latency::verify_data_numeric (const unsigned char *buffer, unsigned long length)
{
   unsigned long j = 0;
   unsigned char c;

   for (unsigned long i = 0; i < length; i++)
   {
      c = '0' + (++j % 10);

      if (buffer [i] != c)
      {
         cout << "verify numeric failed (" << buffer [i] << " != " << c << ") @ index " << i << endl;
         return false;
      }
   }

   return true;
}

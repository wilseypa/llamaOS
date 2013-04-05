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

#include <iGlobals.h>

int MPI_Type_size(MPI_Datatype datatype, int *size)
{
   switch (datatype)
   {
     default:
       *size = 0;
       break;

     case MPI_CHAR:
     case MPI_BYTE:
       *size = sizeof(char);
       break;

     case MPI_SHORT:
       *size = sizeof(short);
       break;

     case MPI_INT:
       *size = sizeof(int);
       break;

     case MPI_LONG:
       *size = sizeof(long);
       break;

     case MPI_FLOAT:
       *size = sizeof(float);
       break;

     case MPI_DOUBLE:
       *size = sizeof(double);
       break;

     case MPI_UNSIGNED_CHAR:
       *size = sizeof(unsigned char);
       break;

     case MPI_UNSIGNED_SHORT:
       *size = sizeof(unsigned short);
       break;

     case MPI_UNSIGNED:
       *size = sizeof(unsigned);
       break;

     case MPI_UNSIGNED_LONG:
       *size = sizeof(unsigned long);
       break;

     case MPI_LONG_DOUBLE:
       *size = sizeof(long double);
       break;

     case MPI_LONG_LONG_INT:
       *size = sizeof(long long int);
       break;
   }

   return MPI_SUCCESS;
}

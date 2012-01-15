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

#include <cstdlib>
#include <cstdio>

#include "latency.h"

int latency_data_alloc (LATENCY_PARAM *param)
{
   // allocate message data space (+4096 to allow page alignment)
   param->buffer = (unsigned char *)malloc (4096+param->length);

   if (!param->buffer)
   {
      printf ("error allocating memory\n");
      return LATENCY_FAILURE;
   }

   // align pointer to page boundary
   param->header =
        (unsigned char *)(((unsigned long)param->buffer + 4096) & (~4095));
   param->data = param->header;

   return LATENCY_SUCCESS;
}

int latency_header_data_alloc (LATENCY_PARAM *param, int header_length)
{
   // allocate message data space (+4096 to allow page alignment)
   param->buffer = (unsigned char *)malloc (4096+header_length+param->length);

   if (!param->buffer)
   {
      printf ("error allocating memory\n");
      return LATENCY_FAILURE;
   }

   // align pointer to page boundary
   param->header =
        (unsigned char *)(((unsigned long)param->buffer + 4096) & (~4095));
   param->data = param->header + header_length;

   return LATENCY_SUCCESS;
}

void latency_data_free (LATENCY_PARAM *param)
{
   if (param->buffer)
   {
      free (param->buffer);
      param->buffer = 0;
      param->data = 0;
   }
}

void mark_data_alpha (LATENCY_PARAM *param)
{
   int i, j;

   // put alpha data (A B C D ...)
   for (i = 0, j = 0; i < param->length; i++)
   {
      param->data [i] = ('A' + (++j % 26));
   }
}

int mark_data_alpha_verify (LATENCY_PARAM *param)
{
   int i, j;
   unsigned char c;

   for (i = 0, j = 0; i < param->length; i++)
   {
      c = 'A' + (++j % 26);

      if (param->data [i] != c)
      {
         printf ("verify failed (%c != %c) @ index %d\n",
                 param->data [i], c, i);
         return LATENCY_FAILURE;
      }
   }

   return LATENCY_SUCCESS;
}

void mark_data_numeric (LATENCY_PARAM *param)
{
   int i, j;

   // put num data (0 1 2 3 ...)
   for (i = 0, j = 0; i < param->length; i++)
   {
      param->data [i] = ('0' + (++j % 10));
   }
}

int mark_data_numeric_verify (LATENCY_PARAM *param)
{
   int i, j;
   unsigned char c;

   for (i = 0, j = 0; i < param->length; i++)
   {
      c = '0' + (++j % 10);

      if (param->data [i] != c)
      {
         printf ("verify failed (%c != %c) @ index %d\n",
                 param->data [i], c, i);
         return LATENCY_FAILURE;
      }
   }

   return LATENCY_SUCCESS;
}

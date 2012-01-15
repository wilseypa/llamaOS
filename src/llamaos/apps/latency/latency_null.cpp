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

#include <cstdio>

#include "latency.h"
#include "latency_data.h"

int latency_init (LATENCY_PARAM *param, int /* argc */, char ** /* argv */)
{
   if (!latency_data_alloc (param))
   {
      return LATENCY_FAILURE;
   }

   param->master = 1;
   return LATENCY_SUCCESS;
}

void latency_exit (LATENCY_PARAM *param)
{
   latency_data_free (param);
}

void latency_usage (void)
{
   printf (" usage: latency_null trials length\n");
}

int latency_recv_msg (LATENCY_PARAM *param)
{
   static int trial = -1;

   if (   (trial == -1)
       || (trial == param->trials))
   {
      if (mark_data_alpha_verify (param))
      {
         mark_data_numeric (param);
         trial++;
         return LATENCY_SUCCESS;
      }
   }
   else
   {
      *((int *)param->data) = trial++;
      return LATENCY_SUCCESS;
   }

   return LATENCY_FAILURE;
}

int latency_send_msg (LATENCY_PARAM * /* param */)
{
   return LATENCY_SUCCESS;
}

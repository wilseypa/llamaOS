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

#ifndef llamaos_apps_latency_latency_h_
#define llamaos_apps_latency_latency_h_

#define LATENCY_FAILURE 0
#define LATENCY_SUCCESS 1

#define LATENCY_MAX_TRIALS 1000000

typedef struct latency_var
{
   // set from program args
   char name [256];
   int trials;
   int length;

   // managed by implementation specific logic
   int master;
   unsigned char *buffer;
   unsigned char *header;
   unsigned char *data;

   // experiemnt results
   int results [LATENCY_MAX_TRIALS];

} LATENCY_PARAM;

// implementation specific interface
int latency_init (LATENCY_PARAM *param, int argc, char **argv);
void latency_exit (LATENCY_PARAM *param);
void latency_usage ();

int latency_recv_msg (LATENCY_PARAM *param);
int latency_send_msg (LATENCY_PARAM *param);

#endif  // llamaos_apps_latency_latency_h_

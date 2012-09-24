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

#include <netpipe.h>

#include <llamaNET_impl.h>

void Init(ArgStruct *p, int* pargc, char*** pargv)
{
   p->tr = 0;     /* The transmitter will be set using the -h host flag. */
   p->rcv = 1;
}

void Setup(ArgStruct *p)
{
   if (p->tr)
   {
      llamaNET_setup (0);
   }
   else
   {
      llamaNET_setup (6);
   }
}

void Sync(ArgStruct *p)
{
   llamaNET_sync ((p->tr) ? 1 : 0);
}

void PrepareToReceive(ArgStruct *p)
{
}

void SendData(ArgStruct *p)
{
   llamaNET_send_data (p->s_ptr, p->bufflen);
}

void RecvData(ArgStruct *p)
{
  llamaNET_recv_data (p->s_ptr, p->bufflen);
}

void SendTime(ArgStruct *p, double *t)
{
   llamaNET_send_time (*t);
}

void RecvTime(ArgStruct *p, double *t)
{
   *t = llamaNET_recv_time ();
}

void SendRepeat(ArgStruct *p, int rpt)
{
   llamaNET_send_repeat (rpt);
}

void RecvRepeat(ArgStruct *p, int *rpt)
{
   *rpt = llamaNET_recv_repeat ();
}

void CleanUp(ArgStruct *p)
{
   if (p->tr)
   {
      llamaNET_cleanup (1);
   }
   else if( p->rcv )
   {
      llamaNET_cleanup (0);
   }
}

void Reset(ArgStruct *p)
{
}

void AfterAlignmentInit(ArgStruct *p)
{
}

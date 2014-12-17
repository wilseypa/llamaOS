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

#include    "netpipe.h"


void Init(ArgStruct *p, int* argc, char*** argv)
{
  printf("\n");
  printf("  *** Note about memcpy module results ***  \n");
  printf("\n");

  p->tr = 1;
  p->rcv = 0;
}

void Setup(ArgStruct *p)
{

}

void establish(ArgStruct *p)
{
   
}

void Sync(ArgStruct *p)
{

}

void PrepareToReceive(ArgStruct *p)
{
   
}

void SendData(ArgStruct *p)
{
//    int nbytes = p->bufflen, nleft;
//    char *src = p->s_ptr, *dest = p->r_ptr;

//    memcpy(dest, src, nbytes);
   volatile int x = 0;
//   volatile int y = 0;

   for(int i = 0; i < 100000; ++i)
   {
      x += x * 2 + 3;
//      getpid();
//      getuid();

//      int *z = malloc(sizeof(int));
//      y = x;//*z;
//      free(z);
   }
}

void RecvData(ArgStruct *p)
{
//    int nbytes = p->bufflen, nleft;
//    char *src = p->s_ptr, *dest = p->r_ptr;

//    memcpy(src, dest, nbytes);
}

void SendTime(ArgStruct *p, double *t)
{

}

void RecvTime(ArgStruct *p, double *t)
{

}

void SendRepeat(ArgStruct *p, int rpt)
{

}

void RecvRepeat(ArgStruct *p, int *rpt)
{

}

void CleanUp(ArgStruct *p)
{

}

void Reset(ArgStruct *p)
{

}

void AfterAlignmentInit(ArgStruct *p)
{

}

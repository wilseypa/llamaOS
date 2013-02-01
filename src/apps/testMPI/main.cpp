/*
Copyright (c) 2013, John Gideon
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

#include <mpi.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <llamaos/api/sleep.h>

using namespace std;

void duoTest();

int main(int argc, char *argv []) {
   MPI_Init (&argc, &argv);
   cout << "Starting program" << endl;

   duoTest();

   cout << "Ending program" << endl;
   MPI_Finalize();

   return 0;
}

void duoTest() {
   cout << "Starting duo test" << endl;
   int rank, totNodes;
   MPI_Comm_rank(MPI_COMM_WORLD, &rank);
   MPI_Comm_size(MPI_COMM_WORLD, &totNodes);

   cout << "Pt2pt test..." << endl;
   if (rank == 0) {
      llamaos::api::sleep(5);
      for (int source = 1; source < totNodes; source++) {
         char buf[100];
         MPI_Status status;
         MPI_Recv(&buf, 100, MPI_UNSIGNED_CHAR, source, 0, MPI_COMM_WORLD, &status);
         cout << buf << endl;
      }
   } else {
      char buf[100];
      sprintf(buf, "Received message from node %d", rank);
      MPI_Send(&buf, 100, MPI_UNSIGNED_CHAR, 0, 0, MPI_COMM_WORLD);
      cout << "Sent message to root" << endl;
   }

   cout << "Broadcast test" << endl;
   int rootRank = rank;
   MPI_Bcast(&rootRank, 4, MPI_UNSIGNED_CHAR, 1, MPI_COMM_WORLD);
   cout << "Root Rank: " << rootRank << endl;

   cout << "Barrier test" << endl;
   MPI_Barrier(MPI_COMM_WORLD);

   cout << "Scatter/Gather test" << endl;
   int intBuf[8] = {0,0,0,0,0,0,0,0};
   if (rank == 0) {
      for (int i = 0; i < 8; i++) {
         intBuf[i] = i;
      }
   }
   int subIntBuf[4];
   MPI_Scatter(intBuf, 4, MPI_INT, subIntBuf, 4, MPI_INT, 0, MPI_COMM_WORLD);
   for (int i = 0; i < 4; i++) {
      subIntBuf[i] += 1000;
   }
   MPI_Gather(subIntBuf, 4, MPI_INT, intBuf, 4, MPI_INT, 0, MPI_COMM_WORLD);
   cout << "Result is:" << endl;
   for (int i = 0; i < 8; i++) {
      cout << intBuf[i] << " ";
   } 
   cout << endl;

   cout << "Allgather test" << endl;
   MPI_Allgather(subIntBuf, 4, MPI_INT, intBuf, 4, MPI_INT, MPI_COMM_WORLD);
   cout << "Result is:" << endl;
   for (int i = 0; i < 8; i++) {
      cout << intBuf[i] << " ";
   } 
   cout << endl;

   cout << "Alltoall test" << endl;
   int ataBuf[8];
   for (int i = 0; i < 8; i++) {
      intBuf[i] = i + (10*rank);
      ataBuf[i] = -1;
   }
   MPI_Alltoall(intBuf, 4, MPI_INT, ataBuf, 4, MPI_INT, MPI_COMM_WORLD);
   cout << "Result is:" << endl;
   for (int i = 0; i < 8; i++) {
      cout << ataBuf[i] << " ";
   } 
   cout << endl;

   cout << "Reduce tests" << endl;
   cout << "Using integer values: ";
   short rValue[8];
   short subR[4];
   short resR[4];
   for (int i = 0; i < 8; i++) {
      rValue[i] = ((short)((i+1)*0xc8527a969e6d7b9e))%256;
      cout << rValue[i] << " ";
   }
   cout << endl;
   MPI_Scatter(rValue, 4, MPI_SHORT, subR, 4, MPI_SHORT, 0, MPI_COMM_WORLD);
   MPI_Reduce(subR, resR, 4, MPI_SHORT, MPI_MAX, 0, MPI_COMM_WORLD);
   cout << "MAX Results: ";
   for (int i = 0; i < 4; i++) {cout << resR[i] << " ";}
   cout << endl;
   MPI_Reduce(subR, resR, 4, MPI_SHORT, MPI_MIN, 0, MPI_COMM_WORLD);
   cout << "MIN Results: ";
   for (int i = 0; i < 4; i++) {cout << resR[i] << " ";}
   cout << endl;
   MPI_Reduce(subR, resR, 4, MPI_SHORT, MPI_SUM, 0, MPI_COMM_WORLD);
   cout << "SUM Results: ";
   for (int i = 0; i < 4; i++) {cout << resR[i] << " ";}
   cout << endl;
   MPI_Reduce(subR, resR, 4, MPI_SHORT, MPI_PROD, 0, MPI_COMM_WORLD);
   cout << "PROD Results: ";
   for (int i = 0; i < 4; i++) {cout << resR[i] << " ";}
   cout << endl;

   cout << "Using unsigned integer values: ";
   unsigned char ruValue[8];
   unsigned char subRu[4];
   unsigned char resRu[4];
   for (int i = 0; i < 8; i++) {
      ruValue[i] = ((unsigned char)((i+1+8)*0xc8527a969e6d7b9e))%256;
      cout << (unsigned int)ruValue[i] << " ";
   }
   cout << endl;
   MPI_Scatter(ruValue, 4, MPI_BYTE, subRu, 4, MPI_SHORT, 0, MPI_COMM_WORLD);
   MPI_Reduce(subRu, resRu, 4, MPI_BYTE, MPI_BAND, 0, MPI_COMM_WORLD);
   cout << "BAND Results: ";
   for (int i = 0; i < 4; i++) {cout << (unsigned int)resRu[i] << " ";}
   cout << endl;
   MPI_Reduce(subRu, resRu, 4, MPI_BYTE, MPI_BOR, 0, MPI_COMM_WORLD);
   cout << "BOR Results: ";
   for (int i = 0; i < 4; i++) {cout << (unsigned int)resRu[i] << " ";}
   cout << endl;
   MPI_Reduce(subRu, resRu, 4, MPI_BYTE, MPI_BXOR, 0, MPI_COMM_WORLD);
   cout << "BXOR Results: ";
   for (int i = 0; i < 4; i++) {cout << (unsigned int)resRu[i] << " ";}
   cout << endl;

   cout << "Using logical values: ";
   int rlValue[8] = {0, 0, 1, 16, 0, -122, 0, 1777777};
   int subRl[4];
   int resRl[4];
   for (int i = 0; i < 8; i++) {
      cout << rlValue[i] << " ";
   }
   cout << endl;
   MPI_Scatter(rlValue, 4, MPI_INT, subRl, 4, MPI_INT, 0, MPI_COMM_WORLD);
   MPI_Reduce(subRl, resRl, 4, MPI_INT, MPI_LAND, 0, MPI_COMM_WORLD);
   cout << "LAND Results: ";
   for (int i = 0; i < 4; i++) {cout << resRl[i] << " ";}
   cout << endl;
   MPI_Reduce(subRl, resRl, 4, MPI_INT, MPI_LOR, 0, MPI_COMM_WORLD);
   cout << "LOR Results: ";
   for (int i = 0; i < 4; i++) {cout << resRl[i] << " ";}
   cout << endl;
   MPI_Reduce(subRl, resRl, 4, MPI_INT, MPI_LXOR, 0, MPI_COMM_WORLD);
   cout << "LXOR Results: ";
   for (int i = 0; i < 4; i++) {cout << resRl[i] << " ";}
   cout << endl;

   struct resPair_T {
      short value;
      int index;
   };
   cout << "Using integer values: ";
   resPair_T rpValue[8];
   resPair_T subRp[4];
   resPair_T resRp[4];
   for (int i = 0; i < 8; i++) {
      rpValue[i].value = ((short)((i+1+(8*3))*0xc8527a969e6d7b9e))%256;
      rpValue[i].index = (((int)((i+1+(8*4))*0xc8527a969e6d7b9e))%128)+127;
      cout << "(" << rpValue[i].value << "," << rpValue[i].index << ") ";
   }
   cout << endl;
   MPI_Scatter(rpValue, 4, MPI_SHORT_INT, subRp, 4, MPI_SHORT_INT, 0, MPI_COMM_WORLD);
   MPI_Reduce(subRp, resRp, 4, MPI_SHORT_INT, MPI_MAXLOC, 0, MPI_COMM_WORLD);
   cout << "MAXLOC Results: ";
   for (int i = 0; i < 4; i++) {cout << "(" << resRp[i].value << "," << resRp[i].index << ") ";}
   cout << endl;
   MPI_Reduce(subRp, resRp, 4, MPI_SHORT_INT, MPI_MINLOC, 0, MPI_COMM_WORLD);
   cout << "MINLOC Results: ";
   for (int i = 0; i < 4; i++) {cout << "(" << resRp[i].value << "," << resRp[i].index << ") ";}
   cout << endl;

   cout << "Allreduce tests" << endl;
   cout << "Using integer values: ";
   for (int i = 0; i < 8; i++) {
      rValue[i] = ((short)((i+1+(8*5))*0xc8527a969e6d7b9e))%256;
      cout << rValue[i] << " ";
   }
   cout << endl;
   MPI_Scatter(rValue, 4, MPI_SHORT, subR, 4, MPI_SHORT, 0, MPI_COMM_WORLD);
   MPI_Allreduce(subR, resR, 4, MPI_SHORT, MPI_MAX, MPI_COMM_WORLD);
   cout << "MAX Results: ";
   for (int i = 0; i < 4; i++) {cout << resR[i] << " ";}
   cout << endl;
   MPI_Allreduce(subR, resR, 4, MPI_SHORT, MPI_MIN, MPI_COMM_WORLD);
   cout << "MIN Results: ";
   for (int i = 0; i < 4; i++) {cout << resR[i] << " ";}
   cout << endl;
}

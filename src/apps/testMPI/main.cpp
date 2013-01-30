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

int main(int argc, char *argv []) {
   MPI_Init (&argc, &argv);

   int rank, totNodes;
   MPI_Comm_rank(MPI_COMM_WORLD, &rank);
   MPI_Comm_size(MPI_COMM_WORLD, &totNodes);

   cout << "Starting app..." << endl;

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

   int rootRank = rank;
   MPI_Bcast(&rootRank, 4, MPI_UNSIGNED_CHAR, 1, MPI_COMM_WORLD);
   cout << "Root Rank: " << rootRank << endl;

   MPI_Barrier(MPI_COMM_WORLD);

   int intBuf[8] = {4,7,9,1,4,0,1,5};
   int subIntBuf[4];
   MPI_Scatter(intBuf, 4*4, MPI_UNSIGNED_CHAR, subIntBuf, 4*4, MPI_UNSIGNED_CHAR, 0, MPI_COMM_WORLD);
   for (int i = 0; i < 4; i++) {
      subIntBuf[i] += 1000;
   }
   MPI_Gather(subIntBuf, 4*4, MPI_UNSIGNED_CHAR, intBuf, 4*4, MPI_UNSIGNED_CHAR, 0, MPI_COMM_WORLD);
   cout << "Result is:" << endl;
   for (int i = 0; i < 8; i++) {
      cout << intBuf[i] << " ";
   } 
   cout << endl;

   MPI_Finalize();

   return 0;
}

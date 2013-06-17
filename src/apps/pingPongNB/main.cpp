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

#define NUM_MESS_PER_TIME 50000

using namespace std;

int main(int argc, char *argv []) {
   MPI_Init (&argc, &argv);
   int rank;
   MPI_Comm_rank(MPI_COMM_WORLD, &rank);
   int orank = 1 - rank;
   cout << "Starting program" << endl;
   while (1) {
      double startTime = MPI_Wtime();
      for (int messOn = 0; messOn < NUM_MESS_PER_TIME; messOn++) {
         if (messOn%2 == rank) {
            unsigned char *dataBuf = new unsigned char[3000];
            MPI_Request request;
            MPI_Isend(&dataBuf, 3000, MPI_UNSIGNED_CHAR, orank, 0, MPI_COMM_WORLD, &request );
            int mpiCompleteStatus = 0;
            MPI_Status myLastStatus;
            MPI_Test( &request, &mpiCompleteStatus, &myLastStatus );
            delete[] dataBuf;
         } else {
            while (1) {
               MPI_Status status;
               int count = 0;
               int flag = 0;
               MPI_Iprobe(MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &flag, &status);
              
               if (flag != 0) {
                  // how many messages did we get ? ...
                  MPI_Get_count( &status, MPI_UNSIGNED_CHAR, &count );
                  unsigned char *dataBuf = new unsigned char[count];
                  MPI_Recv( dataBuf, count, MPI_UNSIGNED_CHAR, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE );
                  delete[] dataBuf;
                  break;
               }
            }
         }
      }      
      double stopTime = MPI_Wtime();
      cout << "Completed set after " << stopTime - startTime << " seconds\n";
   }
   MPI_Finalize();
   return 0;
}


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

#include <iGlobals.h>
#include <string.h>
#include <iostream>

using namespace std;

int MPI_Alltoall(void *sendbuf, int sendcount, MPI_Datatype sendtype, 
                 void *recvbuf, int recvcount, MPI_Datatype recvtype, 
                 MPI_Comm comm) {
   #ifdef MPI_COUT_COLLECTIVE_FUNCTIONS
   iLevelSpacesPrint();
   cout << "--- MPI_Alltoall ---" << endl;
   iLevelSpacesIncrease();
   #endif
   #ifdef MPI_BARRIER_ALL_COLLECTIVE
   MPI_Barrier(comm);
   #endif
                 
   int size;
   MPI_Comm_size(comm, &size);

   // Transpose the send buffers amoung the nodes' recv buffers
   char *bufPartPtr = reinterpret_cast<char*>(sendbuf); 
   for (int i = 0; i < size; i++) {
      iSend(bufPartPtr, sendcount, sendtype, i, 
            MPI_FUNC_TAG_ALLTOALL, comm, MPI_CONTEXT_COLLECTIVE); 
      bufPartPtr += sendcount*iSizeof(sendtype);
   }
   bufPartPtr = reinterpret_cast<char*>(recvbuf);
   for (int i = 0; i < size; i++) {
      iReceive(bufPartPtr, recvcount, recvtype, i, 
            MPI_FUNC_TAG_ALLTOALL, comm, MPI_CONTEXT_COLLECTIVE, 0);
      bufPartPtr += recvcount*iSizeof(recvtype);
   }
   
   #ifdef MPI_COUT_COLLECTIVE_FUNCTIONS
   iLevelSpacesDecrease();
   #endif

   return MPI_SUCCESS;
}

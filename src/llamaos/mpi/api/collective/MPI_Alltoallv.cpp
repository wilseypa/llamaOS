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

using namespace std;

int MPI_Alltoallv(void *sendbuf, int *sendcnts, int *sdispls, 
                  MPI_Datatype sendtype, void *recvbuf, int *recvcnts, 
                  int *rdispls, MPI_Datatype recvtype, MPI_Comm comm) {
   int size;
   MPI_Comm_size(comm, &size);
   int rank; 
   MPI_Comm_rank(comm, &rank);

   // Transpose the send buffers amoung the nodes' recv buffers
   for (int i = 0; i < size; i++) {
      char *bufPartPtr = reinterpret_cast<char*>(sendbuf) + sdispls[i]*iSizeof(sendtype);
      iSend(bufPartPtr, sendcnts[i], sendtype, i, 
            MPI_FUNC_TAG_ALLTOALLV, comm, MPI_CONTEXT_COLLECTIVE);
   }
   for (int i = 0; i < size; i++) {
      char *bufPartPtr = reinterpret_cast<char*>(recvbuf) + rdispls[i]*iSizeof(recvtype);
      iReceive(bufPartPtr, recvcnts[i], recvtype, i, 
            MPI_FUNC_TAG_ALLTOALLV, comm, MPI_CONTEXT_COLLECTIVE, 0);
   }

   return MPI_SUCCESS;
}

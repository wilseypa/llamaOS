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

int MPI_Bcast(void *buffer, int count, MPI_Datatype datatype, int root, MPI_Comm comm ) {
   // Determine process rank
   int rank; 
   MPI_Comm_rank(comm, &rank);
   // linear
   // Send a message to all nodes if process is root
   if (rank == root) { 
      int size;
      MPI_Comm_size(comm, &size);
      for (int i = 0; i < size; i++) {
         iSend(buffer, count, datatype, i, MPI_FUNC_TAG_BROADCAST, comm, MPI_CONTEXT_COLLECTIVE);
      }
   }
   // Receive the broadcast message
   iReceive(buffer, count, datatype, root, MPI_FUNC_TAG_BROADCAST, 
                    comm, MPI_CONTEXT_COLLECTIVE, 0);

   return MPI_SUCCESS;
}

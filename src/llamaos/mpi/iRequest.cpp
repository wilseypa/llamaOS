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

#include <iRequest.h>
#include <string.h>
#include <iostream>

using namespace std;

// Return the next unique identifier
MPI_Request iRequest::getNextId() {
   static MPI_Request nextId = 1;
   return nextId++;
}

iRequest::iRequest(IREQUEST_TYPE ptype, void *pbuf, int pcount, MPI_Datatype pdatatype, 
      int prank, int ptag, MPI_Comm pcomm) {
   id = getNextId();
   type = ptype;
   buf = pbuf;
   count = pcount;
   datatype = pdatatype;
   rank = prank;
   tag = ptag;
   comm = pcomm;
   mpiData.request[id] = this;

   // If this is a receive request, add an entry to the associated buffer
   if (ptype == IREQUEST_RECEIVE) {
      int sizeInBytes = count*iSizeof(datatype);
   
      #ifdef MPI_COUT_EVERY_MESSAGE
      iLevelSpacesPrint();
      cout << "Creating Request for rank " << rank << " Comm: " << comm;
      cout << " Tag: " << tag << " TotSize: " << sizeInBytes;
      #endif
   
      MAP_TYPE<MPI_Comm,iComm*>::iterator it = mpiData.comm.find(comm);
      if (it != mpiData.comm.end()) { // Comm is declared
         // Get receive buffer
         iRxBuffer *rxBuff = it->second->getPt2ptRxBuffer();
         rxBuff->pushMessageReq((unsigned char*)buf, rank, tag, sizeInBytes);
      }
   }
}

iRequest::~iRequest() {
   mpiData.request.erase(id);
}

int iRequest::wait(MPI_Status *status) {
   switch (type) {
      case IREQUEST_SEND:
         return MPI_SUCCESS;
      case IREQUEST_RECEIVE:
         iReceive(buf, count, datatype, rank, tag, comm, MPI_CONTEXT_PT2PT, status);
         return MPI_SUCCESS;
      default:
         return -1;
   }
}

int iRequest::test(int *flag, MPI_Status *status) {
   switch (type) {
      case IREQUEST_SEND:
         (*flag) = true;
         return MPI_SUCCESS;
      case IREQUEST_RECEIVE:
         iReceiveNB(buf, count, datatype, rank, tag, comm, MPI_CONTEXT_PT2PT, status, flag);
         return MPI_SUCCESS;
      default:
         return -1;
   }
}

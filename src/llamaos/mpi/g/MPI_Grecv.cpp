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
#include <llamaConn.h>
#include <iostream>

using namespace std;

int MPI_Grecv(void **buf, int *count, MPI_Datatype datatype, int *flag) {
   #ifdef MPI_WATCHDOG_TIME
   double timeDiff = MPI_Wtime() - mpiData.prevWatchdogTime;
   if (timeDiff > MPI_WATCHDOG_TIME) {
      mpiData.prevWatchdogTime = MPI_Wtime();
      cout << "Five seconds since last receive." << endl;
   }
   #endif
   net::llamaNET::Protocol_header *header;
   header = llamaNetInterface->recvNB(mpiData.rank);
   if (header == NULL) { // Exit if no message in queue
      (*flag) = false;
      return MPI_SUCCESS;
   } 
   (*flag) = true;
   #ifdef MPI_WATCHDOG_TIME
   mpiData.prevWatchdogTime = MPI_Wtime();
   #endif
   
   int rxCommContext, rxTag, rxSource, rxTotSize, rxPart;
   int *data = reinterpret_cast<int *>(header + 1);
   memcpy(&rxCommContext, data++, 4);
   memcpy(&rxTag, data++, 4);
   memcpy(&rxTotSize, data++, 4);
   memcpy(&rxPart, data++, 4);
   rxSource = static_cast<int>(header->src);
   
   if (rxTotSize > MAX_MESS_SIZE) {
      cout << "ERROR: Grecv with message size larger than max packet" << endl;
      while (1);
   }
   
   // Allocate buffer and copy message
   (*buf) = new char[rxTotSize];
   memcpy((*buf), data, rxTotSize);
   
   (*count) = rxTotSize / iSizeof(datatype);
   llamaNetInterface->release_recv_buffer(header); // Release llama rx message buffer
   
   return MPI_SUCCESS;
}

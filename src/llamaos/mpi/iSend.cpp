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
#include <string.h>

using namespace std;

void iSend(void *buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm, MPI_Context context) {
   static uint32_t seq = 1;
   net::llamaNET::Protocol_header *header;

   MAP_TYPE<MPI_Comm,iComm*>::iterator it = mpiData.comm.find(comm);
   if (it == mpiData.comm.end()) {  // Comm does not exist
      cout << "WARNING: Comm " << comm << " does not exist" << endl;
      return;
   }
   iComm *commPtr = it->second;

   // Determine actual send size in bytes
   unsigned int sizeInBytes = count*iSizeof(datatype);

   // Translate comm ranks into world ranks
   int destWorldRank = commPtr->getWorldRankFromRank(dest);
   if (destWorldRank == MPI_UNDEFINED) {return;} // Destination rank is not in comm
   int srcWorldRank = commPtr->getLocalWorldRank();
   if (srcWorldRank == MPI_UNDEFINED) {return;} // Source rank is not in comm
   int commContext = comm | context;

   header = llamaNetInterface->get_send_buffer();
   header->dest = static_cast<uint32_t>(destWorldRank);
   header->src = static_cast<uint32_t>(srcWorldRank);
   header->type = 1;
   header->seq = seq++; 
   header->len = sizeInBytes + 8;
   memcpy(header->eth_dest, mpiData.hostTable[destWorldRank].address, 6);
   memcpy(header->eth_src, mpiData.address, 6);

   // get pointer to data section of buffer
   int *data = reinterpret_cast<int *>(header + 1);
   memcpy(data++, &commContext, 4);
   memcpy(data++, &tag, 4);
   memcpy(data, buf, sizeInBytes);

   // Print header
   #ifdef MPI_COUT_EVERY_MESSAGE
   cout << "Sending to dest " << header->dest << " with MAC address ";
   iPrintMAC(header->eth_dest);
   cout << "    From src " << header->src << " with MAC address ";
   iPrintMAC(header->eth_src);
   cout << endl;
   #endif

   // send/recv and verify the data has been changed to numerals (1,2,3,...)
   llamaNetInterface->send(header);
}

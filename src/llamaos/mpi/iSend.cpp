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

#ifdef SLOW_SENDS
#include <llamaos/api/sleep.h>
#endif

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

   // Determine actual send size in bytes and the union of comm and context
   unsigned int sizeInBytes = count*iSizeof(datatype);
   int commContext = comm | context;
   
   // Check if sending message to self
   if (commPtr->getLocalRank() == dest) {
      // Print header
      #ifdef MPI_COUT_EVERY_MESSAGE
      iLevelSpacesPrint();
      cout << "[SendToSelf]";
      cout << " Message received from self src/dest " << dest << " Context: " << commContext;
      cout << " Tag: " << tag << " TotSize: " << sizeInBytes;
      #endif
      
      // Get receive buffer
      iRxBuffer *rxBuff;
      if (context == MPI_CONTEXT_PT2PT) {
         rxBuff = it->second->getPt2ptRxBuffer();
      } else {
         rxBuff = it->second->getCollectiveRxBuffer();
      }
      
      // Add to receive buffer
      rxBuff->pushMessage((unsigned char*)buf, sizeInBytes, dest, tag, sizeInBytes, 0);
      return;
   }

   // Translate comm ranks into world ranks
   int destWorldRank = commPtr->getWorldRankFromRank(dest);
   //if (destWorldRank == MPI_UNDEFINED) {return;} // Destination rank is not in comm (Removed for BCast)
   int srcWorldRank = commPtr->getLocalWorldRank();
   if (srcWorldRank == MPI_UNDEFINED) {return;} // Source rank is not in comm

   // Split large messages into multiple sends
   int numFullMess = sizeInBytes/MAX_MESS_SIZE;
   int remMessSize = sizeInBytes%MAX_MESS_SIZE;
   for (int partOn=0; partOn <= numFullMess; partOn++) {
      #ifdef MPI_RX_BEFORE_TX
      iBufferMessage();
      #endif
      int messSize = (partOn==numFullMess) ? remMessSize : MAX_MESS_SIZE;

      if (messSize == 0 && partOn != 0) {break;} // Exception for zero-sized messages

      #ifdef MPI_SLOW_SENDS
      llamaos::api::sleep(1);
      #endif

      header = llamaNetInterface->get_send_buffer(static_cast<uint32_t>(srcWorldRank));
      header->dest = static_cast<uint32_t>(destWorldRank);
      header->src = static_cast<uint32_t>(srcWorldRank);
      header->type = 1;
      header->seq = seq++; 
      header->len = messSize + 16;
      if (dest == MPI_SEND_BCAST) {
         header->eth_dest[0] = 0xFF; 
         header->eth_dest[1] = 0xFF; 
         header->eth_dest[2] = 0xFF; 
         header->eth_dest[3] = 0xFF; 
         header->eth_dest[4] = 0xFF; 
         header->eth_dest[5] = 0xFF; 
      } else {
         memcpy(header->eth_dest, mpiData.hostTable[destWorldRank].address, 6);
      }
      memcpy(header->eth_src, mpiData.address, 6);

      // get pointer to data section of buffer
      int *data = reinterpret_cast<int *>(header + 1);
      memcpy(data++, &commContext, 4);
      memcpy(data++, &tag, 4);
	   memcpy(data++, &sizeInBytes, 4);
      memcpy(data++, &partOn, 4);
      memcpy(data, buf, messSize);

      // Print header
      #ifdef MPI_COUT_EVERY_MESSAGE
      int totParts = sizeInBytes / MAX_MESS_SIZE;
      if (sizeInBytes % MAX_MESS_SIZE != 0) {totParts++;}
      iLevelSpacesPrint();
      cout << "Sending to dest " << header->dest << " Context: " << commContext;
      cout << " Tag: " << tag << " TotSize: " << sizeInBytes << " Part: " << partOn+1 << "/" << totParts;
      cout << endl;
      #endif

      // send the message
      llamaNetInterface->send(header);
      buf = (void*)((char*)buf + MAX_MESS_SIZE); // Advance the pointer
   }
}

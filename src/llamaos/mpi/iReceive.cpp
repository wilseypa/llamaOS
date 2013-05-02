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
#include <iRxBuffer.h>
#include <iostream>
#include <string.h>

using namespace std;
using namespace llamaos;
using namespace llamaos::net;
using namespace llamaos::xen;

void iReceive(void *buf, int count, MPI_Datatype datatype, int source, int tag, 
			MPI_Comm comm, MPI_Context context, MPI_Status *status) {
   // Determine actual send size in bytes
   int sizeInBytes = count*iSizeof(datatype);

   // Get receive buffer
   iRxBuffer *rxBuff;
   MAP_TYPE<MPI_Comm,iComm*>::iterator it = mpiData.comm.find(comm);
   if (it != mpiData.comm.end()) { // Comm is declared
      // Get receive buffer
      if (context == MPI_CONTEXT_PT2PT) {
         rxBuff = it->second->getPt2ptRxBuffer();
      } else {
         rxBuff = it->second->getCollectiveRxBuffer();
      }
   } else { // Comm does not exist
      cout << "WARNING: Comm " << comm << " does not exist" << endl;
      return;
   }
   iComm *commPtr = it->second;

   // Determine source world rank from comm
   int srcWorldRank = commPtr->getWorldRankFromRank(source);
   if (srcWorldRank == MPI_UNDEFINED) {return;} // Source rank is not in comm

   // Print receive request
   #ifdef MPI_COUT_EVERY_MESSAGE
   int commContext = comm | context;
   cout << "Waiting for message from src " << srcWorldRank;
   cout << " Context: " << commContext << " Tag: " << tag;
   cout << " TotSize: " << sizeInBytes;
   cout << endl;
   #endif

   // Check through receive buffer
   int curRxSize = rxBuff->popMessage(source, tag, buf, sizeInBytes, status);
   if (curRxSize == sizeInBytes) { // Message has been popped
      #ifdef MPI_COUT_EVERY_MESSAGE
      cout << "Receive from src " << srcWorldRank << " COMPLETE" << endl;
      #endif
      return;
   }
   #ifdef MPI_COUT_EVERY_MESSAGE
   if (curRxSize > 0) {
      cout << "Pulled message from src " << srcWorldRank << " with curSize " << curRxSize << endl;
   } else {
      cout << "Nothing found in rxBuffer" << endl;
   }
   #endif

   // If not in receive buffer, wait unti message received while buffering all other messages
   net::llamaNET::Protocol_header *header;
   int rxCommContext, rxTag, rxSource, rxTotSize, rxPart;
   MPI_Comm rxComm;
   MPI_Context rxContext;
   for (;;) {
      // Receive most recent packet and extract needed information
      header = llamaNetInterface->recv(mpiData.rank);
      int *data = reinterpret_cast<int *>(header + 1);
      memcpy(&rxCommContext, data++, 4);
      rxComm = rxCommContext & MPI_COMM_MASK;
      rxContext = rxCommContext & MPI_CONTEXT_MASK;
      memcpy(&rxTag, data++, 4);
      memcpy(&rxTotSize, data++, 4);
      memcpy(&rxPart, data++, 4);
      rxSource = static_cast<int>(header->src);

      // Print header
      #ifdef MPI_COUT_EVERY_MESSAGE
      int totParts = rxTotSize / MAX_MESS_SIZE;
      if (rxTotSize % MAX_MESS_SIZE != 0) {totParts++;}
      cout << "Received from src " << header->src << " Context: " << rxCommContext;
      cout << " Tag: " << rxTag << " TotSize: " << rxTotSize << " Part: " << rxPart+1 << "/" << totParts;
      #endif

      // Check if desired message type
      if (((rxSource == srcWorldRank) || (srcWorldRank == MPI_ANY_SOURCE)) &&
               (rxComm == comm) && (rxContext == context) && ((rxTag == tag) || (tag == MPI_ANY_TAG))) {
         // Verify length
         if (sizeInBytes < rxTotSize) { // Will not fit in buffer - discard
            cout << endl;
            cout << "ERROR: Message Size: " << rxTotSize;
            cout << " Buffer Size: " << sizeInBytes << " Will not fit" << endl;
            llamaNetInterface->release_recv_buffer(header);
            return;
         }
         // Determine the part of buffer to add to
         char *bufPart = (char*)buf;
         bufPart += rxPart*MAX_MESS_SIZE;
         
         // Copy into buffer
         memcpy(bufPart, data, header->len - 16);
         curRxSize += (header->len - 16);
         
         #ifdef MPI_COUT_EVERY_MESSAGE
         cout << " CurSize: " << curRxSize << endl;
         #endif

         // Check if finished
         bool isFinished = false;
         if (curRxSize > rxTotSize) {isFinished = true;} //error
         if (curRxSize == rxTotSize) {
            if (status != MPI_STATUS_IGNORE) {
               status->MPI_SOURCE = commPtr->getRankFromWorldRank(rxSource);
               status->MPI_TAG = rxTag;
               status->MPI_ERROR = MPI_SUCCESS;
               status->size = rxTotSize;
            }
            isFinished = true;
         }
         llamaNetInterface->release_recv_buffer(header); // Release llama rx message buffer
         if (isFinished) {
            #ifdef MPI_COUT_EVERY_MESSAGE
            cout << "Receive from src " << srcWorldRank << " COMPLETE" << endl;
            #endif
            return;
         }
      } else { // Store in receive buffer
         it = mpiData.comm.find(rxComm);
         if (it != mpiData.comm.end()) { // Comm is declared
            // Get receive buffer
            if (rxContext == MPI_CONTEXT_PT2PT) {
               rxBuff = it->second->getPt2ptRxBuffer();
            } else {
               rxBuff = it->second->getCollectiveRxBuffer();
            }
            
            // Add to receive buffer
            int rxCommRank = it->second->getRankFromWorldRank(rxSource);
            if (rxCommRank != MPI_UNDEFINED) { // rank is in comm
               rxBuff->pushMessage((unsigned char*)data, header->len-16, rxCommRank, 
                     rxTag, rxTotSize, rxPart);
            }
         } else {
            cout << "WARNING: Received comm " << rxComm << " does not exist" << endl;
         }
         llamaNetInterface->release_recv_buffer(header); // Release llama rx message buffer
      }
   }
}

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
#include <iRequest.h>

using namespace std;
using namespace llamaos;
using namespace llamaos::net;
using namespace llamaos::xen;

void iGetMessage(void *buf, int count, MPI_Datatype datatype, int source, int tag, 
			MPI_Comm comm, MPI_Context context, MPI_Status *status, int *flag,
			bool isProbe, bool isNB) {
	int rxCommContext, rxTag, rxSource, rxTotSize, rxPart;
	// Set initial state of flag to false (not received)
	(*flag) = false;
			
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
   int srcWorldRank;
   if (source != MPI_ANY_SOURCE) {
      srcWorldRank = commPtr->getWorldRankFromRank(source);
      if (srcWorldRank == MPI_UNDEFINED) { // Source rank is not in comm
         cout << "ERROR: Source rank " << source << " not found in comm " << comm << endl;
         while(1);
         return;
      } 
   } else {
      srcWorldRank = source;
   }

   // Print receive request
   #ifdef MPI_COUT_EVERY_MESSAGE
   if (!isNB) {
      iLevelSpacesPrint();
      if (!isProbe) {cout << "[iReceive]";}
      else {cout << "[iProbe]";}
      int commContext = comm | context;
      cout << " Waiting for message from src " << srcWorldRank;
      cout << " Context: " << commContext << " Tag: " << tag;
      cout << " TotSize: " << sizeInBytes;
      cout << endl;
   }
   #ifdef MPI_COUT_NB_MESSAGES
   else {
      iLevelSpacesPrint();
      if (!isProbe) {cout << "[iReceiveNB]";}
      else {cout << "[iProbeNB]";}
      int commContext = comm | context;
      cout << " Waiting for message from src " << srcWorldRank;
      cout << " Context: " << commContext << " Tag: " << tag;
      cout << " TotSize: " << sizeInBytes;
      cout << endl;
   }
   #endif
   #endif

   // Check through receive buffer
   int curRxSize = 0;
   MPI_Status tmpStatus;
   if (isProbe) {
      // Only check to see if complete message in buffer - either way do not touch it
      if (rxBuff->probeMessage(source, tag, &tmpStatus)) {
         #ifdef MPI_COUT_EVERY_MESSAGE
         srcWorldRank = commPtr->getWorldRankFromRank(tmpStatus.MPI_SOURCE);
         iLevelSpacesPrint();
         if (isNB) {cout << "[iProbeNB]";}
         else {cout << "[iProbe]";}
         cout << " SUCCESS from src " << srcWorldRank << endl;
         #endif
         memcpy(status, &tmpStatus, sizeof(MPI_Status));
         (*flag) = true;
         return;
      }
   } else if (!isNB) {
      // Pull even incomplete messages out of the buffer
      curRxSize = rxBuff->popMessage(source, tag, buf, sizeInBytes, &tmpStatus);
      // Print buffer pull
      if (curRxSize > 0) {
         srcWorldRank = commPtr->getWorldRankFromRank(tmpStatus.MPI_SOURCE);
         tag = tmpStatus.MPI_TAG;
         rxTotSize = tmpStatus.size;
      }
      #ifdef MPI_COUT_EVERY_MESSAGE
      iLevelSpacesPrint();
      if (curRxSize > 0) {
         if (isNB) {cout << "[iReceiveNB]";}
         else {cout << "[iReceive]";}
         cout << " Pulled message from src " << srcWorldRank << " with tag " << tag;
         cout << " and size " << curRxSize << "/" << rxTotSize << endl;
      } else if (!isNB) {
         cout << "[iReceive] Nothing found in rxBuffer" << endl;
      }
      #endif
      // Check if finished already
      if ((curRxSize > 0) && (curRxSize == rxTotSize)) {
         #ifdef MPI_COUT_EVERY_MESSAGE
         iLevelSpacesPrint();
         cout << "[iReceive]";
         cout << " COMPLETE from src " << srcWorldRank << " Comm: " << comm << " Tag: " << tag << endl;
         #endif
         memcpy(status, &tmpStatus, sizeof(MPI_Status));
         (*flag) = true;
         return;
      }
   } else {
      // Check to see if finished with recvNB
      if (rxBuff->probeMessage(source, tag, status)) {
         // Message is complete
         (*flag) = true;
         rxBuff->removeMessage(source, tag);
         #ifdef MPI_COUT_EVERY_MESSAGE
         cout << "[iReceiveNB] COMPLETE from src " << srcWorldRank << " Comm: " << comm << " Tag: " << tag << endl;
         #endif
         return;
      }
   }

   // If not in receive buffer, wait until message received while buffering all other messages
   net::llamaNET::Protocol_header *header;
   MPI_Comm rxComm;
   MPI_Context rxContext;
   for (;;) {
      // Receive most recent packet and extract needed information
      if (isNB) {
         header = llamaNetInterface->recvNB(mpiData.rank);
         if (header == NULL) {return;} // Exit if no message in queue
      } else {
         header = llamaNetInterface->recv(mpiData.rank);
      }
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
      iLevelSpacesPrint();
      int totParts = rxTotSize / MAX_MESS_SIZE;
      if (rxTotSize % MAX_MESS_SIZE != 0) {totParts++;}
      if (!isProbe && !isNB) {cout << "[iReceive]";}
      else if (!isProbe && isNB) {cout << "[iReceiveNB]";}
      else if (isProbe && !isNB) {cout << "[iProbe]";}
      else if (isProbe && isNB) {cout << "[iProbeNB]";}
      cout << " Message received from src " << header->src << " Context: " << rxCommContext;
      cout << " Tag: " << rxTag << " TotSize: " << rxTotSize << " Part: " << rxPart+1 << "/" << totParts;
      #endif

      // Check if desired message type and not a probe
      if ( (!isProbe) && (!isNB) && ((rxSource == srcWorldRank) || (srcWorldRank == MPI_ANY_SOURCE)) && 
               (rxComm == comm) && (rxContext == context) && ((rxTag == tag) || (tag == MPI_ANY_TAG))) {
         srcWorldRank = rxSource;
         tag = rxTag;
         // Verify length
         if (sizeInBytes < rxTotSize) { // Will not fit in buffer - discard
            cout << endl;
            cout << "ERROR: Message Size: " << rxTotSize;
            cout << " Buffer Size: " << sizeInBytes << " Will not fit" << endl;
            llamaNetInterface->release_recv_buffer(header);
            while(1);
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
         
         // Release llama rx message buffer
         llamaNetInterface->release_recv_buffer(header); 

         // Check if finished
         if (curRxSize > rxTotSize) {
            cout << "WARNING: Message will not fit in provided buffer" << endl;
            return; //error
         } 
         if (curRxSize == rxTotSize) {
            if (status != MPI_STATUS_IGNORE) {
               status->MPI_SOURCE = commPtr->getRankFromWorldRank(rxSource);
               status->MPI_TAG = rxTag;
               status->MPI_ERROR = MPI_SUCCESS;
               status->size = rxTotSize;
            }
            #ifdef MPI_COUT_EVERY_MESSAGE
            iLevelSpacesPrint();
            cout << "[iReceive]";
            cout << " COMPLETE from src " << srcWorldRank << " Comm: " << comm << " Tag: " << tag << endl;
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
            } else {
               cout << "ERROR: Source rank " << rxCommRank << " not found in comm " << rxComm << endl;
               llamaNetInterface->release_recv_buffer(header);
               while(1);
               return;
            }
            
            // Release llama rx message buffer
            llamaNetInterface->release_recv_buffer(header);
            
            // Check if desired message type and probing or recvNB
            if ( (isProbe || isNB) && ((rxSource == srcWorldRank) || (srcWorldRank == MPI_ANY_SOURCE)) && 
                     (rxComm == comm) && (rxContext == context) && 
                     ((rxTag == tag) || (tag == MPI_ANY_TAG)) ) {
               source = rxSource;
               tag = rxTag;
               if (isProbe) {               
                  // Only check to see if complete message in buffer - either way do not touch it
                  if (rxBuff->probeMessage(source, tag, status)) {
                     #ifdef MPI_COUT_EVERY_MESSAGE
                     iLevelSpacesPrint();
                     if (isNB) {cout << "[iProbeNB]";}
                     else {cout << "[iProbe]";}
                     cout << " SUCCESS from src " << srcWorldRank << endl;
                     #endif
                     (*flag) = true;
                     return;
                  }
               } else {
                  if (rxBuff->probeMessage(source, tag, status)) {
                     // Message is complete
                     (*flag) = true;
                     rxBuff->removeMessage(source, tag);
                     #ifdef MPI_COUT_EVERY_MESSAGE
                     cout << "[iReceiveNB] COMPLETE from src " << srcWorldRank << " Comm: " << comm << " Tag: " << tag << endl;
                     #endif
                     return;
                  }
               }
            }
         } else {
            cout << "ERROR: Received comm " << rxComm << " does not exist" << endl;
            llamaNetInterface->release_recv_buffer(header); // Release llama rx message buffer
            while(1);
            return;
         }
      }
   }
}

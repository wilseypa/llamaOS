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

void iProbeNB(int source, int tag, MPI_Comm comm, MPI_Context context, MPI_Status *status, int *flag) {
   (*flag) = false;
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
   cout << "Waiting for message from src " << srcWorldRank << " from MAC address ";
   iPrintMAC(mpiData.hostTable[srcWorldRank].address);
   cout << endl;
   #endif

   // Check through receive buffer
   if (rxBuff->probeMessage(source, tag, status)) { // Message has been probed
      (*flag) = true;
      return;
   }

   // If not in receive buffer, wait unti message received while buffering all other messages
   net::llamaNET::Protocol_header *header;
   int rxCommContext, rxTag, rxSource;
   MPI_Comm rxComm;
   MPI_Context rxContext;

   // Receive most recent packet and extract needed information
   header = llamaNetInterface->recvNB(mpiData.rank);
   if (header == NULL) {return;} // Exit if no message in queue
   int *data = reinterpret_cast<int *>(header + 1);
   memcpy(&rxCommContext, data++, 4);
   rxComm = rxCommContext & MPI_COMM_MASK;
   rxContext = rxCommContext & MPI_CONTEXT_MASK;
   memcpy(&rxTag, data++, 4);
   rxSource = static_cast<int>(header->src);

   // Print header
   #ifdef MPI_COUT_EVERY_MESSAGE
   cout << "Received from src " << header->src << " with MAC address ";
   iPrintMAC(header->eth_src);
   cout << "    At dest " << header->dest << " with MAC address ";
   iPrintMAC(header->eth_dest);
   cout << endl;
   #endif
 
   // Store in receive buffer
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
         rxBuff->pushMessage((unsigned char*)data, header->len - 8, rxCommRank, rxTag);
      }

      // Check if desired message type - Block until received
      if (((rxSource == srcWorldRank) || (srcWorldRank == MPI_ANY_SOURCE)) &&
               (rxComm == comm) && (rxContext == context) && ((rxTag == tag) || (tag == MPI_ANY_TAG))) {
         if (status != MPI_STATUS_IGNORE) {
            status->MPI_SOURCE = commPtr->getRankFromWorldRank(rxSource);
            status->MPI_TAG = rxTag;
            status->MPI_ERROR = MPI_SUCCESS;
            status->size = header->len - 8;
         }
         (*flag) = true;
      }
   } else {
      cout << "WARNING: Received comm " << rxComm << " does not exist" << endl;
   }
   llamaNetInterface->release_recv_buffer(header); // Release llama rx message buffer
   return;
}

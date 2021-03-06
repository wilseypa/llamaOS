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

void iBufferMessage() {
   net::llamaNET::Protocol_header *header;
   MPI_Comm rxComm;
   MPI_Context rxContext;
   int rxCommContext, rxTag, rxSource, rxTotSize, rxPart;
   
   while (1) {
      // Non-blocking receive most recent packet 
      header = llamaNetInterface->recvNB(mpiData.rank);
      if (header == NULL) {return;} // Exit if no message in queue
      
      // Extract needed information
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
      iLevelSpacesPrint();
      cout << "[iBufferMessage]";
      cout << " Message received from src " << header->src << " Context: " << rxCommContext;
      cout << " Tag: " << rxTag << " TotSize: " << rxTotSize << " Part: " << rxPart+1 << "/" << totParts;
      #endif
      
      // Store in receive buffer
      iRxBuffer *rxBuff;
      MAP_TYPE<MPI_Comm,iComm*>::iterator it = mpiData.comm.find(rxComm);
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
      } else {
         cout << "ERROR: Received comm " << rxComm << " does not exist" << endl;
         llamaNetInterface->release_recv_buffer(header); // Release llama rx message buffer
         while(1);
         return;
      }
   }
}

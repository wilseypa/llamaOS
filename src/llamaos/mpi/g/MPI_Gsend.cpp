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

int MPI_Gsend(void *buf, int count, MPI_Datatype datatype, int dest) {
   static uint32_t seq = 1;
   net::llamaNET::Protocol_header *header;
   unsigned int sizeInBytes = count*iSizeof(datatype);
   int src = mpiData.rank;
   
   if (src == dest) {
      cout << "ERROR: Gsend with destination same as self" << endl;
      while (1);
   }
   
   if (sizeInBytes > MAX_MESS_SIZE) {
      cout << "ERROR: Gsend with message size larger than max packet" << endl;
      while (1);
   }
   
   // Set up eth header
   header = llamaNetInterface->get_send_buffer(static_cast<uint32_t>(src));
   header->dest = static_cast<uint32_t>(dest);
   header->src = static_cast<uint32_t>(src);
   header->type = 1;
   header->seq = seq++; 
   header->len = sizeInBytes + 16;
   memcpy(header->eth_dest, mpiData.hostTable[dest].address, 6);
   memcpy(header->eth_src, mpiData.address, 6);

   // get pointer to data section of buffer
   int commContext = MPI_COMM_WORLD | MPI_CONTEXT_PT2PT;
   int tag = 12321;
   int partOn = 0;
   int *data = reinterpret_cast<int *>(header + 1);
   memcpy(data++, &commContext, 4);
   memcpy(data++, &tag, 4);
   memcpy(data++, &sizeInBytes, 4);
   memcpy(data++, &partOn, 4);
   memcpy(data, buf, sizeInBytes);
   
   // send the message
   llamaNetInterface->send(header);
   
   return MPI_SUCCESS;
}

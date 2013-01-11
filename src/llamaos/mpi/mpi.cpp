/*
Copyright (c) 2013, William Magato
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

#include <cstdint>
#include <llamaos/mpi/mpi.h>
#include <llamaos/net/llamaNET.h>
#include <llamaos/xen/Hypervisor.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <iomanip>

using namespace std;
using namespace llamaos;
using namespace llamaos::net;
using namespace llamaos::xen;

#define MPI_COUT_EVERY_MESSAGE
#define MPI_MAX_NODES 256

typedef struct MpiHostTable_T {
   uint8_t address[6];
   uint32_t pid;
   bool ready;
} MpiHostTable_T;

typedef struct MpiData_T {
   uint32_t rank;
   uint8_t address[6];
   uint32_t pid;
   uint32_t totNodes;
   MpiHostTable_T hostTable[MPI_MAX_NODES];
   llamaNET *interface;
} MpiData_T;
static MpiData_T mpiData;

static uint32_t seq = 1;

static const int ARG_TAG_DNE = -1;
static const int ARG_TAG_NO_VAL = 0;

static void printMAC(uint8_t mac[]) {
   int macPart;
   for (macPart = 0; macPart < 6; macPart++) {
      cout << hex << setfill('0') << setw(2) << (unsigned int)mac[macPart];
      if (macPart != 5) {
         cout << ":";
      }
   }
   cout << dec << setfill(' ');
}

static int getArgIndex(int argc, char *argv[], const std::string &arg) {
   for (int i = 1; i < argc; i++)
   {
      if (arg == argv [i])
      {
         if (i++ <= argc) {
            return i;
         } else {
            return ARG_TAG_NO_VAL;
         }
      }
   }
   return ARG_TAG_DNE;
}

int MPI_Init (int *argc, char ***argv) {
   cout << "Starting llamaMPI..." << endl;
   cout.flush();

   //Check if rank is missing - running alone
   int rankIndex = getArgIndex(*argc, *argv, "--rank");
   if (rankIndex <= 0) {
      cout << "No rank given: running alone" << endl;
      mpiData.rank = 0;
      mpiData.totNodes = 1;
      return MPI_SUCCESS; //No sync necessary
   }

   //The first input argument gives the process its rank
   mpiData.rank = atoi((*argv)[rankIndex]);
   cout << "My Rank: "  << mpiData.rank << endl;

   //Check if host table is not present - running alone
   int hostTableIndex = getArgIndex(*argc, *argv, "--hostTable");
   if (hostTableIndex <= 0) {
      cout << "Host table not present: running alone" << endl;
      mpiData.rank = 0;
      mpiData.totNodes = 1;
      return MPI_SUCCESS; //No sync necessary
   }

   //Get host table size
   int hostTableSize = atoi((*argv)[hostTableIndex++]);
   cout << "Host Table Arguments: " << hostTableSize << endl;

   //Check for partial host table - running alone
   if (hostTableIndex + (hostTableSize*2) >= *argc) {
      cout << "Partial host table: running alone" << endl;
      mpiData.rank = 0;
      mpiData.totNodes = 1;
      return MPI_SUCCESS; //No sync necessary
   }

   //Construct the host table
   mpiData.totNodes = 0;
   for (; hostTableSize > 0; hostTableSize--) {
      //Get the MAC address
      int macPart;
      int8_t macBuff[6];
      for (macPart = 0; macPart < 6; macPart++) {
         char macSecBuff[3];
         macSecBuff[0] = (*argv)[hostTableIndex][(macPart*3)+0];
         macSecBuff[1] = (*argv)[hostTableIndex][(macPart*3)+1];
         macSecBuff[2] = '\0';
         macBuff[macPart] = strtoul(macSecBuff, NULL, 16);
      }
      hostTableIndex++;

      //Get the number of processes
      int numProcesses = atoi((*argv)[hostTableIndex++]);

      //Create the table entry
      int pidOn;
      for (pidOn = 0; pidOn < numProcesses; pidOn++) {
         memcpy(mpiData.hostTable[mpiData.totNodes].address, macBuff, 6);
         mpiData.hostTable[mpiData.totNodes++].pid = pidOn;
      }
   }
   memcpy(mpiData.address, mpiData.hostTable[mpiData.rank].address, 6);
   mpiData.pid = mpiData.hostTable[mpiData.rank].pid;

   //Display the constructed host table
   unsigned int addOn;
   cout << "The constructed host table consisting of " << mpiData.totNodes << " entries:" << endl;
   for (addOn = 0; addOn < mpiData.totNodes; addOn++) {
      cout << "Rank " << addOn << "   Address ";
      printMAC(mpiData.hostTable[addOn].address);
      cout << "   PID " << mpiData.hostTable[addOn].pid << endl;
   }
   cout.flush();

   //Initialize llamaNET connection
   cout << "Creating llamaNET interface... ";
   domid_t self_id = Hypervisor::get_instance()->domid;
   mpiData.interface = new llamaNET(self_id - 1 - mpiData.pid, mpiData.pid);
   cout << "DONE" << endl;
   cout.flush();

   //The process sends a message to the root node saying it is ready

   //The process waits for the sync start signal from the root node
   return MPI_SUCCESS;
}

int MPI_Finalize (void) {
   delete mpiData.interface;
   return MPI_SUCCESS;
}

int MPI_Comm_rank (MPI_Comm comm, int *rank) {
   (*rank) = mpiData.rank;
   return MPI_SUCCESS;
}

int MPI_Recv(void *buf, int count, MPI_Datatype datatype, int source, int tag, MPI_Comm comm, MPI_Status *status) {
   // Print receive request
   #ifdef MPI_COUT_EVERY_MESSAGE
   cout << "Waiting for message from src " << source << " from MAC address ";
   printMAC(mpiData.hostTable[source].address);
   cout << endl;
   #endif

   //Receive packet on mpiData.rank from source
   net::llamaNET::Protocol_header *header;
   for (;;) {
      header = mpiData.interface->recv(mpiData.rank);

      if (header->src == static_cast<uint32_t>(source)) {
         break;
      } else {
         mpiData.interface->release_recv_buffer(header);
      }
   }

   //Check that packet length matches
   if (header->len < static_cast<uint32_t>(count)) {
      mpiData.interface->release_recv_buffer (header);
      return -1;
   }

   //Copy data buffer and release recv buffer
   unsigned char *data = reinterpret_cast<unsigned char *>(header + 1);
   memcpy (buf, data, header->len);
   status->count = header->len;
   status->MPI_SOURCE = header->src;
   mpiData.interface->release_recv_buffer (header);

   // Print header
   #ifdef MPI_COUT_EVERY_MESSAGE
   cout << "Received from src " << header->src << " with MAC address ";
   printMAC(header->eth_src);
   cout << "    At dest " << header->dest << " with MAC address ";
   printMAC(header->eth_dest);
   cout << endl;
   #endif

   return MPI_SUCCESS;
}

int MPI_Irecv(void *buf, int count, MPI_Datatype datatype, int source, int tag, MPI_Comm comm, MPI_Request *request) {
   return 0;
}

int MPI_Send(void *buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm) {
   net::llamaNET::Protocol_header *header;

   header = mpiData.interface->get_send_buffer();
   header->dest = dest;
   header->src = mpiData.rank;
   header->type = 1;
   header->seq = seq++;
   header->len = count;
   memcpy(header->eth_dest, mpiData.hostTable[dest].address, 6);
   memcpy(header->eth_src, mpiData.address, 6);
   // get pointer to data section of buffer
   unsigned char *data = reinterpret_cast<unsigned char *>(header + 1);
   memcpy(data, buf, count);

   // Print header
   #ifdef MPI_COUT_EVERY_MESSAGE
   cout << "Sending to dest " << header->dest << " with MAC address ";
   printMAC(header->eth_dest);
   cout << "    From src " << header->src << " with MAC address ";
   printMAC(header->eth_src);
   cout << endl;
   #endif

   // send/recv and verify the data has been changed to numerals (1,2,3,...)
   mpiData.interface->send(header);

   return MPI_SUCCESS;
}

int MPI_Isend(void *buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm, MPI_Request *request) {
   return 0;
}

int MPI_Test(MPI_Request *request, int *flag, MPI_Status *status) {
   return 0;
}

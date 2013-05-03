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
#include <llamaos/mpi/mpi.h>
#include <llamaos/net/llamaNET.h>
#include <llamaos/xen/Hypervisor.h>
#include <iostream>
#include <string.h>

using namespace std;
using namespace llamaos;
using namespace llamaos::net;
using namespace llamaos::xen;

static const int ARG_TAG_DNE = -1;
static const int ARG_TAG_NO_VAL = 0;

static int iGetArgIndex(int argc, char *argv[], const std::string &arg) {
   for (int i = 0; i < argc; i++)
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
   
   //Initialize data structures
   mpiData.hostTable.clear();
   mpiData.comm.clear();
   mpiData.group.clear();
   mpiData.request.clear();

   //Check if rank is missing - running alone
   int rankIndex = iGetArgIndex(*argc, *argv, "--rank");
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
   int hostTableIndex = iGetArgIndex(*argc, *argv, "--hostTable");
   if (hostTableIndex <= 0) {
      cout << "Host table not present: running alone" << endl;
      mpiData.rank = 0;
      mpiData.totNodes = 1;
      (*argc) = rankIndex-1;
      return MPI_SUCCESS; //No sync necessary
   }

   //Get host table size
   int hostTableSize = atoi((*argv)[hostTableIndex++]);
   cout << "Host Table Arguments: " << hostTableSize << endl;

   //Check for partial host table - running alone
   if (hostTableIndex + (hostTableSize*2) > *argc) {
      cout << "Partial host table: running alone" << endl;
      mpiData.rank = 0;
      mpiData.totNodes = 1;
      (*argc) = rankIndex-1;
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

      //Create the table entries
      int pidOn;
      for (pidOn = 0; pidOn < numProcesses; pidOn++) {
         MpiHostTable_T newEntry;
         memcpy(&newEntry.address, macBuff, 6);
         newEntry.pid = pidOn;
         mpiData.hostTable.push_back(newEntry);
         mpiData.totNodes++;
      }
   }
   memcpy(mpiData.address, mpiData.hostTable[mpiData.rank].address, 6);
   mpiData.pid = mpiData.hostTable[mpiData.rank].pid;

   //Display the constructed host table
   unsigned int addOn;
   cout << "The constructed host table consisting of " << mpiData.totNodes << " entries:" << endl;
   for (addOn = 0; addOn < mpiData.totNodes; addOn++) {
      cout << "Rank " << addOn << "   Address ";
      iPrintMAC(mpiData.hostTable[addOn].address);
      cout << "   PID " << mpiData.hostTable[addOn].pid << endl;
   }
   cout.flush();

   //Initialize Groups
   cout << "Initializing groups... ";
   new iGroup(IGROUP_CREATE_EMPTY);
   cout << "DONE" << endl;

   //Initialize Communicators
   cout << "Initializing communicators... ";
   new iComm(MPI_COMM_WORLD, new iGroup(IGROUP_CREATE_WORLD));
   new iComm(MPI_COMM_SELF, new iGroup(IGROUP_CREATE_SELF));
   cout << "DONE" << endl;

   //Initialize llamaNET connection
   cout << "Creating llamaNET interface... ";
   domid_t self_id = Hypervisor::get_instance()->domid;
   llamaNetInterface = new llamaNET(self_id - 1 - mpiData.pid, mpiData.pid);
   cout << "DONE" << endl;
   cout.flush();

   //The process waits for the sync to start
   MPI_Barrier(MPI_COMM_WORLD);
   (*argc) = rankIndex-1;
   return MPI_SUCCESS;
}

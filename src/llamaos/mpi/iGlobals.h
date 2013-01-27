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

#ifndef I_GLOBALS_H_
#define I_GLOBALS_H_

#include <cstdint>
#include <vector>
#define MAP_TYPE std::map
#include <map>

#include <mpi.h>
#include <iGroup.h>
#include <iComm.h>

class iGroup;
class iComm;

//#define MPI_COUT_EVERY_MESSAGE

typedef int MPI_Context;
#define MPI_COMM_MASK (0x7FFFFFFF)
#define MPI_CONTEXT_MASK (0x80000000)
#define MPI_CONTEXT_PT2PT (0x00000000)
#define MPI_CONTEXT_COLLECTIVE 2 (0x80000000)

typedef struct MpiHostTable_T {
   uint8_t address[6];
   uint32_t pid;
} MpiHostTable_T;

typedef struct MpiData_T {
   uint32_t rank;	// The current node world rank
   uint8_t address[6];	// The current node MAC address
   uint32_t pid;	// The current node pid on machine (0 - #nodes on machine)
   uint32_t totNodes;	// The total nodes in the world
   std::vector<MpiHostTable_T> hostTable;	// The vector of all MAC addresses and pid per world rank
   MAP_TYPE<MPI_Comm,iComm*> comm;	// Map of integer handles to communicators
   MAP_TYPE<MPI_Group,iGroup*> group; // Map of integer handles to groups
} MpiData_T;


// GLOBAL VARIABLES
extern MpiData_T mpiData;


// INTERNAL FUNCTIONS
// Low level send and receive
void iSend(void *buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm, MPI_Context context);
void iReceive(void *buf, int count, MPI_Datatype datatype, int source, int tag, 
			MPI_Comm comm, MPI_Context context, MPI_Status *status);


// Tools
void iPrintMAC(uint8_t mac[]);

#endif

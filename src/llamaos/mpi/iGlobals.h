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
//#define MAP_TYPE std::unordered_map
//#include <unordered_map>
#include <limits>

#include <mpi.h>
#include <iGroup.h>
#include <iComm.h>
#include <iRequest.h>

class iGroup;
class iComm;
class iRequest;

//#define MPI_COUT_EVERY_MESSAGE
//#define MPI_COUT_NB_MESSAGES
#define MPI_COUT_INITIALIZATION
//#define MPI_COUT_COLLECTIVE_FUNCTIONS
#define MPI_COUT_TAB "    "
//#define MPI_SLOW_SENDS
//#define MPI_BARRIER_ALL_COLLECTIVE
//#define MPI_RX_BEFORE_TX
//#define MPI_USE_BCAST_HARDWARE
#define MPI_WATCHDOG_TIME 5

// #define MAX_MESS_SIZE 3950

// 1500 - 64
#define MAX_MESS_SIZE 1436

// 4096 - 64
// #define MAX_MESS_SIZE 4032

typedef char MPI_CHAR_T;
typedef unsigned char MPI_BYTE_T;		
typedef short MPI_SHORT_T;		
typedef int MPI_INT_T;		
typedef long MPI_LONG_T;		
typedef float MPI_FLOAT_T;		
typedef double MPI_DOUBLE_T;		
typedef unsigned char MPI_UNSIGNED_CHAR_T;	
typedef short MPI_UNSIGNED_SHORT_T;	
typedef unsigned MPI_UNSIGNED_T;		
typedef unsigned long MPI_UNSIGNED_LONG_T;	
typedef long double MPI_LONG_DOUBLE_T;	
typedef long long int MPI_LONG_LONG_INT_T;	

struct MPI_FLOAT_INT_T {MPI_FLOAT_T value; MPI_INT_T index;};
struct MPI_LONG_INT_T {MPI_LONG_T value; MPI_INT_T index;};
struct MPI_DOUBLE_INT_T {MPI_DOUBLE_T value; MPI_INT_T index;};
struct MPI_SHORT_INT_T {MPI_SHORT_T value; MPI_INT_T index;};
struct MPI_2INT_T {MPI_INT_T value; MPI_INT_T index;};
struct MPI_LONG_DOUBLE_INT_T {MPI_LONG_DOUBLE_T value; MPI_INT_T index;};

typedef char MPI_CHARACTER_T;
typedef int MPI_INTEGER_T;
typedef signed char MPI_INTEGER1_T;
typedef short MPI_INTEGER2_T;
typedef int MPI_INTEGER4_T;
typedef float MPI_REAL_T;
typedef double MPI_DOUBLE_PRECISION_T;
typedef float _Complex MPI_COMPLEX_T;
typedef double _Complex MPI_DOUBLE_COMPLEX_T;
typedef bool MPI_LOGICAL_T;

struct MPI_2REAL_T {MPI_REAL_T value; MPI_REAL_T index;};
struct MPI_2DOUBLE_PRECISION_T {MPI_DOUBLE_PRECISION_T value; MPI_DOUBLE_PRECISION_T index;};
struct MPI_2INTEGER_T {MPI_INTEGER_T value; MPI_INTEGER_T index;};

typedef int MPI_Context;
#define MPI_COMM_MASK ((int)0x7FFFFFFF)
#define MPI_CONTEXT_MASK ((int)0x80000000)
#define MPI_CONTEXT_PT2PT ((int)0x00000000)
#define MPI_CONTEXT_COLLECTIVE ((int)0x80000000)

#define MPI_RANK_ROOT ((int)0)
#define MPI_SEND_BCAST ((int)-1)

#define MPI_FUNC_TAG_BARRIER     ((int)-2)
#define MPI_FUNC_TAG_BROADCAST   ((int)-3)
#define MPI_FUNC_TAG_GATHER      ((int)-4)
#define MPI_FUNC_TAG_SCATTER     ((int)-5)
#define MPI_FUNC_TAG_ALLTOALL    ((int)-6)
#define MPI_FUNC_TAG_REDUCE      ((int)-7)
#define MPI_FUNC_TAG_ALLTOALLV   ((int)-8)

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
   MAP_TYPE<MPI_Request,iRequest*> request; // Map of integer handles to requests
   bool isPerformingOp;
   #ifdef MPI_WATCHDOG_TIME
   double prevWatchdogTime;
   #endif
} MpiData_T;


// GLOBAL VARIABLES
extern MpiData_T mpiData;


// INTERNAL FUNCTIONS
// Low level send and receive
void iSend(void *buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm, MPI_Context context);
void iReceive(void *buf, int count, MPI_Datatype datatype, int source, int tag, 
			MPI_Comm comm, MPI_Context context, MPI_Status *status);
void iReceiveNB(void *buf, int count, MPI_Datatype datatype, int source, int tag, 
			MPI_Comm comm, MPI_Context context, MPI_Status *status, int *flag);
void iProbe(int source, int tag, MPI_Comm comm, MPI_Context context, MPI_Status *status);
void iProbeNB(int source, int tag, MPI_Comm comm, MPI_Context context, MPI_Status *status, int *flag);
void iGetMessage(void *buf, int count, MPI_Datatype datatype, int source, int tag, 
			MPI_Comm comm, MPI_Context context, MPI_Status *status, int *flag,
			bool isProbe, bool isNB);
int iSizeof(MPI_Datatype type);
int iPerformOp(void *runningTotal, void *newValue, int count, MPI_Datatype type, MPI_Op op);
int iStartOp(void *runningTotal, int count, MPI_Datatype type, MPI_Op op);
void iBufferMessage();

// Tools
void iPrintMAC(uint8_t mac[]);
void iLevelSpacesPrint();
void iLevelSpacesIncrease();
void iLevelSpacesDecrease();

#endif

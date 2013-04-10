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

#ifndef llamaos_mpi_mpi_h_
#define llamaos_mpi_mpi_h_

#ifdef __cplusplus
extern "C" {
#endif

// MPI TYPEDEF AND DEFINES
/* MPI's error classes */
#define MPI_SUCCESS          0      /* Successful return code */

typedef int MPI_Datatype;
#define MPI_CHAR		((MPI_Datatype)1)
#define MPI_BYTE		((MPI_Datatype)2)
#define MPI_SHORT		((MPI_Datatype)3)
#define MPI_INT			((MPI_Datatype)4)
#define MPI_LONG		((MPI_Datatype)5)
#define MPI_FLOAT		((MPI_Datatype)6)
#define MPI_DOUBLE		((MPI_Datatype)7)
#define MPI_UNSIGNED_CHAR	((MPI_Datatype)8)
#define MPI_UNSIGNED_SHORT	((MPI_Datatype)9)
#define MPI_UNSIGNED		((MPI_Datatype)10)
#define MPI_UNSIGNED_LONG	((MPI_Datatype)11)
#define MPI_LONG_DOUBLE		((MPI_Datatype)12)
#define MPI_LONG_LONG_INT	((MPI_Datatype)13)

#define MPI_FLOAT_INT		((MPI_Datatype)14)
#define MPI_LONG_INT		((MPI_Datatype)15)
#define MPI_DOUBLE_INT		((MPI_Datatype)16)
#define MPI_SHORT_INT		((MPI_Datatype)17)
#define MPI_2INT		((MPI_Datatype)18)
#define MPI_LONG_DOUBLE_INT	((MPI_Datatype)19)

// !BAM added
#define MPI_DATATYPE_NULL	((MPI_Datatype)20)
#define MPI_OP_NULL		((MPI_Datatype)21)
#define MPI_ERRHANDLER_NULL	((MPI_Datatype)22)

#define MPI_CHARACTER  ((MPI_Datatype)23)
#define MPI_INTEGER  ((MPI_Datatype)24)
#define MPI_INTEGER1  ((MPI_Datatype)25)
#define MPI_INTEGER2  ((MPI_Datatype)26)
#define MPI_INTEGER4  ((MPI_Datatype)27)
#define MPI_REAL  ((MPI_Datatype)28)
#define MPI_DOUBLE_PRECISION  ((MPI_Datatype)29)
#define MPI_COMPLEX  ((MPI_Datatype)30)
#define MPI_DOUBLE_COMPLEX  ((MPI_Datatype)31)
#define MPI_LOGICAL  ((MPI_Datatype)32)

typedef int MPI_Op;
#define MPI_MAX       ((MPI_Op)1)      //maximum
#define MPI_MIN       ((MPI_Op)2)      //minimum
#define MPI_SUM       ((MPI_Op)3)      //sum
#define MPI_PROD      ((MPI_Op)4)      //product
#define MPI_LAND      ((MPI_Op)5)      //logical and
#define MPI_BAND      ((MPI_Op)6)      //bit-wise and
#define MPI_LOR       ((MPI_Op)7)      //logical or
#define MPI_BOR       ((MPI_Op)8)      //bit-wise or
#define MPI_LXOR      ((MPI_Op)9)      //logical xor
#define MPI_BXOR      ((MPI_Op)10)     //bit-wise xor
#define MPI_MAXLOC    ((MPI_Op)11)     //max value and location
#define MPI_MINLOC    ((MPI_Op)12)     //min value and location

typedef int MPI_Comm;
#define MPI_COMM_NULL  ((MPI_Comm)0x00000000)
#define MPI_COMM_WORLD ((MPI_Comm)0x7FFFFFFF)
#define MPI_COMM_SELF  ((MPI_Comm)0x7FFFFFFE)

typedef int MPI_Group;
#define MPI_GROUP_NULL  ((MPI_Group)0x00000000)
#define MPI_GROUP_EMPTY ((MPI_Group)0xFFFFFFFF)

typedef int MPI_Count;

typedef int MPI_Request;
#define MPI_REQUEST_NULL ((MPI_Request)0)

// MPI Compare Results
#define MPI_IDENT 1     //Identical
#define MPI_CONGRUENT 2 //(only for MPI_COMM_COMPARE ) The groups are identical
#define MPI_SIMILAR 3   //Same members, but in a different order
#define MPI_UNEQUAL 4   //Different

#define MPI_STATUS_IGNORE (0)
#define MPI_TAG_UB ((int)0x7FFFFFFF)
#define MPI_UNDEFINED (-1)
#define MPI_ANY_SOURCE ((int)0xFFFFFFFF)
#define MPI_ANY_TAG ((int)0xFFFFFFFF)


// MPI STRUCTURES
typedef struct MPI_Status {
    int MPI_SOURCE;
    int MPI_TAG;
    int MPI_ERROR;
    int size;
} MPI_Status;
#define MPI_STATUS_SIZE 4

// !BAM added
typedef int MPI_Errhandler;
typedef void *MPI_Aint;

#define MPI_ERR_INTERN 0
#define MPI_MAX_ERROR_STRING 0

// MPI FUNCTIONS
// SYSTEM FUNCTIONS
int MPI_Init (int *argc, char ***argv);
int MPI_Finalize (void);

// POINT TO POINT - Blocking
int MPI_Send(void *buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm);
int MPI_Recv(void *buf, int count, MPI_Datatype datatype, int source, int tag, MPI_Comm comm, MPI_Status *status);
int MPI_Probe(int source, int tag, MPI_Comm comm, MPI_Status *status);
// POINT TO POINT - Non-Blocking
int MPI_Isend(void *buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm, MPI_Request *request);
int MPI_Irecv(void *buf, int count, MPI_Datatype datatype, int source, int tag, MPI_Comm comm, MPI_Request *request);
int MPI_Iprobe(int source, int tag, MPI_Comm comm, int *flag, MPI_Status *status);
int MPI_Request_free(MPI_Request *request);
int MPI_Wait(MPI_Request *request, MPI_Status *status);
int MPI_Test(MPI_Request *request, int *flag, MPI_Status *status);
int MPI_Waitall(int count, MPI_Request array_of_requests[], 
               MPI_Status array_of_statuses[]);
int MPI_Waitany(int count, MPI_Request array_of_requests[], int *index, 
               MPI_Status *status);
int MPI_Waitsome(int incount, MPI_Request array_of_requests[], 
                int *outcount, int array_of_indices[],
                MPI_Status array_of_statuses[]);
int MPI_Testall(int count, MPI_Request array_of_requests[], int *flag, 
               MPI_Status array_of_statuses[]);
int MPI_Testany(int count, MPI_Request array_of_requests[], int *index, 
               int *flag, MPI_Status *status);
int MPI_Testsome(int incount, MPI_Request array_of_requests[], int *outcount, 
                int array_of_indices[], MPI_Status array_of_statuses[]);
// POINT TO POINT - Status
int MPI_Get_count( MPI_Status *status,  MPI_Datatype datatype, int *count );

// GROUPS - Constructors
int MPI_Group_incl(MPI_Group group, int n, int *ranks, MPI_Group *newgroup);
int MPI_Group_excl(MPI_Group group, int n, int *ranks, MPI_Group *newgroup);
int MPI_Group_union(MPI_Group group1, MPI_Group group2, MPI_Group *newgroup);
int MPI_Group_intersection(MPI_Group group1, MPI_Group group2, MPI_Group *newgroup);
int MPI_Group_difference(MPI_Group group1, MPI_Group group2, MPI_Group *newgroup);
// GROUPS - Accessors
int MPI_Group_rank (MPI_Group group, int *rank);
int MPI_Group_size (MPI_Group group, int *size);
int MPI_Group_translate_ranks(MPI_Group group1, int n, int *ranks1, MPI_Group group2, int *ranks2);
int MPI_Group_compare(MPI_Group group1, MPI_Group group2, int *result);
// GROUPS - Destructor
int MPI_Group_free(MPI_Group *group);

// COMMUNICATORS - Constructors
int MPI_Comm_dup(MPI_Comm comm, MPI_Comm *newcomm);
int MPI_Comm_create(MPI_Comm comm, MPI_Group group, MPI_Comm *newcomm);
int MPI_Comm_split(MPI_Comm comm, int color, int key, MPI_Comm *newcomm);
// COMMUNICATORS - Accessors
int MPI_Comm_rank (MPI_Comm comm, int *rank);
int MPI_Comm_size (MPI_Comm comm, int *size);
int MPI_Comm_group(MPI_Comm comm, MPI_Group *group); // Also functions as a group constructor
int MPI_Comm_compare(MPI_Comm comm1, MPI_Comm comm2, int *result);
// COMMUNICATORS - Destructors
int MPI_Comm_free(MPI_Comm *comm);

// COLLECTIVE - Program Synchronization
int MPI_Barrier (MPI_Comm comm);
// COLLECTIVE - Data Routing
int MPI_Bcast(void *buffer, int count, MPI_Datatype datatype, int root, MPI_Comm comm );
int MPI_Gather(void *sendbuf, int sendcnt, MPI_Datatype sendtype, 
               void *recvbuf, int recvcnt, MPI_Datatype recvtype, 
               int root, MPI_Comm comm);
int MPI_Scatter(void *sendbuf, int sendcnt, MPI_Datatype sendtype, 
               void *recvbuf, int recvcnt, MPI_Datatype recvtype, int root, 
               MPI_Comm comm);
int MPI_Allgather(void *sendbuf, int sendcount, MPI_Datatype sendtype, 
               void *recvbuf, int recvcount, MPI_Datatype recvtype, 
               MPI_Comm comm);
int MPI_Alltoall(void *sendbuf, int sendcount, MPI_Datatype sendtype, 
                 void *recvbuf, int recvcount, MPI_Datatype recvtype, 
                 MPI_Comm comm);
int MPI_Alltoallv(void *sendbuf, int *sendcnts, int *sdispls, 
                  MPI_Datatype sendtype, void *recvbuf, int *recvcnts, 
                  int *rdispls, MPI_Datatype recvtype, MPI_Comm comm);
// COLLECTIVE - Computational
int MPI_Reduce(void *sendbuf, void *recvbuf, int count, MPI_Datatype datatype, 
               MPI_Op op, int root, MPI_Comm comm);
int MPI_Allreduce ( void *sendbuf, void *recvbuf, int count, 
                   MPI_Datatype datatype, MPI_Op op, MPI_Comm comm );

// TIME 
double MPI_Wtime();
double MPI_Wtick();

// !BAM added
int MPI_Abort(MPI_Comm comm, int errorcode);
int MPI_Error_string(int errorcode, char *string, int *resultlen);
int MPI_Get_version(int *version, int *subversion);
int MPI_Type_size(MPI_Datatype datatype, int *size);

#ifdef __cplusplus
} //extern "C"
#endif

#endif  // llamaos_mpi_mpi_h_

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

#include "mpi.h"
#include <llamaos/api/sleep.h>

#ifdef __cplusplus
extern "C" {
#endif

// MPI FUNCTIONS
void mpi_sleep_ (int *seconds) {
   llamaos::api::sleep(*seconds);
}

// SYSTEM FUNCTIONS
void mpi_init_full_ (int *argc, char ***argv, int *ierr) {
   (*ierr) = MPI_Init(argc, argv);
}
/*int MPI_Finalize (void);

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
*/

#ifdef __cplusplus
} //extern "C"
#endif

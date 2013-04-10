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
#include <iostream>
#include <string.h>

using namespace std;

#ifdef __cplusplus
extern "C" {
#endif

extern int _gfortran_iargc(); 
extern void _gfortran_getarg_i4(int *i,char *arg,int len);

// MPI FUNCTIONS
void mpi_sleep_ (int *seconds) {
   llamaos::api::sleep(*seconds);
}

// SYSTEM FUNCTIONS
void mpi_init_ (int *ierr) { // Used http://svn.code.sf.net/p/rsf/code/trunk/api/f90/fortran.c
   int i, len, argc;
   char **argv, *argvi, arg[256];
   argc = 1+_gfortran_iargc();  
   argv = new char*[argc+1];
   for (i=0; i < argc; i++) {
      _gfortran_getarg_i4(&i,arg,256);
	   len = strchr(arg,' ')-arg+1;
	   argvi = argv[i] = new char[len];
	   memcpy(argvi,arg,len);
      argvi[len-1]='\0';
   }    
   argv[argc] = NULL;
   (*ierr) = MPI_Init(&argc, &argv);
}
void mpi_finalize_ (int *ierr) {
   (*ierr) = MPI_Finalize();
}

// POINT TO POINT - Blocking
void mpi_send_ (void *buf, int *count, MPI_Datatype *datatype, int *dest, int *tag, MPI_Comm *comm, int *ierr) {
   (*ierr) = MPI_Send(buf, *count, *datatype, *dest, *tag, *comm);
}
void mpi_recv_ (void *buf, int *count, MPI_Datatype *datatype, int *source, int *tag, MPI_Comm *comm, MPI_Status *status, int *ierr) {
   (*ierr) = MPI_Recv(buf, *count, *datatype, *source, *tag, *comm, status);
}
void mpi_probe_ (int *source, int *tag, MPI_Comm *comm, MPI_Status *status, int *ierr) {
   (*ierr) = MPI_Probe(*source, *tag, *comm, status);
}
// POINT TO POINT - Non-Blocking
void mpi_isend_ (void *buf, int *count, MPI_Datatype *datatype, int *dest, int *tag, MPI_Comm *comm, MPI_Request *request, int *ierr) {
   (*ierr) = MPI_Isend(buf, *count, *datatype, *dest, *tag, *comm, request);
}
void mpi_irecv_ (void *buf, int *count, MPI_Datatype *datatype, int *source, int *tag, MPI_Comm *comm, MPI_Request *request, int *ierr) {
   (*ierr) = MPI_Irecv(buf, *count, *datatype, *source, *tag, *comm, request);
}
void mpi_iprobe_ (int *source, int *tag, MPI_Comm *comm, int *flag, MPI_Status *status, int *ierr) {
   (*ierr) = MPI_Iprobe(*source, *tag, *comm, flag, status);
}
void mpi_request_free_ (MPI_Request *request, int *ierr) {
   (*ierr) = MPI_Request_free(request);
}
void mpi_wait_ (MPI_Request *request, MPI_Status *status, int *ierr) {
   (*ierr) = MPI_Wait(request, status);
}
void mpi_test_ (MPI_Request *request, int *flag, MPI_Status *status, int *ierr) {
   (*ierr) = MPI_Test(request, flag, status);
}
void mpi_waitall_ (int *count, MPI_Request array_of_requests[], 
               MPI_Status array_of_statuses[], int *ierr) {
   (*ierr) = MPI_Waitall(*count, array_of_requests, array_of_statuses);
}
void mpi_waitany_ (int *count, MPI_Request array_of_requests[], int *index, 
               MPI_Status *status, int *ierr) {
   (*ierr) = MPI_Waitany(*count, array_of_requests, index, status);
}
void mpi_waitsome_ (int *incount, MPI_Request array_of_requests[], 
                int *outcount, int array_of_indices[],
                MPI_Status array_of_statuses[], int *ierr) {
   (*ierr) = MPI_Waitsome(*incount, array_of_requests, outcount, array_of_indices, array_of_statuses);
}
void mpi_testall_ (int *count, MPI_Request array_of_requests[], int *flag, 
               MPI_Status array_of_statuses[], int *ierr) {
   (*ierr) = MPI_Testall(*count, array_of_requests, flag, array_of_statuses);
}
void mpi_testany_ (int *count, MPI_Request array_of_requests[], int *index, 
               int *flag, MPI_Status *status, int *ierr) {
   (*ierr) = MPI_Testany(*count, array_of_requests, index, flag, status);
}
void mpi_testsome_ (int *incount, MPI_Request array_of_requests[], int *outcount, 
                int array_of_indices[], MPI_Status array_of_statuses[], int *ierr) {               
   (*ierr) = MPI_Testsome(*incount, array_of_requests, outcount, array_of_indices, array_of_statuses);
}                
// POINT TO POINT - Status
void mpi_get_count_ ( MPI_Status *status,  MPI_Datatype *datatype, int *count, int *ierr) {
   (*ierr) = MPI_Get_count(status, *datatype, count);
}

// GROUPS - Constructors
void mpi_group_incl_ (MPI_Group *group, int *n, int *ranks, MPI_Group *newgroup, int *ierr) {
   (*ierr) = MPI_Group_incl(*group, *n, ranks, newgroup);
}
void mpi_group_excl_ (MPI_Group *group, int *n, int *ranks, MPI_Group *newgroup, int *ierr) {
   (*ierr) = MPI_Group_excl(*group, *n, ranks, newgroup);
}
void mpi_group_union_ (MPI_Group *group1, MPI_Group *group2, MPI_Group *newgroup, int *ierr) {
   (*ierr) = MPI_Group_union(*group1, *group2, newgroup);
}
void mpi_group_intersection_ (MPI_Group *group1, MPI_Group *group2, MPI_Group *newgroup, int *ierr) {
   (*ierr) = MPI_Group_intersection(*group1, *group2, newgroup);
}
void mpi_group_difference_ (MPI_Group *group1, MPI_Group *group2, MPI_Group *newgroup, int *ierr) {
   (*ierr) = MPI_Group_difference(*group1, *group2, newgroup);
}
// GROUPS - Accessors
void mpi_group_rank_ (MPI_Group *group, int *rank, int *ierr) {
   (*ierr) = MPI_Group_rank(*group, rank);
}
void mpi_group_size_ (MPI_Group *group, int *size, int *ierr) {
   (*ierr) = MPI_Group_size(*group, size);
}
void mpi_group_translate_ranks(MPI_Group *group1, int *n, int *ranks1, MPI_Group *group2, 
               int *ranks2, int *ierr) {
   (*ierr) = MPI_Group_translate_ranks(*group1, *n, ranks1, *group2, ranks2);
}
void mpi_group_compare_ (MPI_Group *group1, MPI_Group *group2, int *result, int *ierr) {
   (*ierr) = MPI_Group_compare(*group1, *group2, result);
}
// GROUPS - Destructor
void mpi_group_free_ (MPI_Group *group, int *ierr) {
   (*ierr) = MPI_Group_free(group);
}

// COMMUNICATORS - Constructors
void mpi_comm_dup_ (MPI_Comm *comm, MPI_Comm *newcomm, int *ierr) {
   (*ierr) = MPI_Comm_dup(*comm, newcomm);
}
void mpi_comm_create_ (MPI_Comm *comm, MPI_Group *group, MPI_Comm *newcomm, int *ierr) {
   (*ierr) = MPI_Comm_create(*comm, *group, newcomm);
}
void mpi_comm_split_ (MPI_Comm *comm, int *color, int *key, MPI_Comm *newcomm, int *ierr) {
   (*ierr) = MPI_Comm_split(*comm, *color, *key, newcomm);
}
// COMMUNICATORS - Accessors
void mpi_comm_rank_ (MPI_Comm *comm, int *rank, int *ierr) {
   (*ierr) = MPI_Comm_rank(*comm, rank);
}
void mpi_comm_size_ (MPI_Comm *comm, int *size, int *ierr) {
   (*ierr) = MPI_Comm_size(*comm, size);
}
void mpi_comm_group_ (MPI_Comm *comm, MPI_Group *group, int *ierr) {
   (*ierr) = MPI_Comm_group(*comm, group);
}
void mpi_comm_compare_ (MPI_Comm *comm1, MPI_Comm *comm2, int *result, int *ierr) { 
   (*ierr) = MPI_Comm_compare(*comm1, *comm2, result);
}
// COMMUNICATORS - Destructors
void mpi_comm_free_ (MPI_Comm *comm, int *ierr) {
   (*ierr) = MPI_Comm_free(comm);
}

// COLLECTIVE - Program Synchronization
void mpi_barrier_ (MPI_Comm *comm, int *ierr) {
   (*ierr) = MPI_Barrier (*comm);
}
// COLLECTIVE - Data Routing
void mpi_bcast_ (void *buffer, int *count, MPI_Datatype *datatype, int *root, MPI_Comm *comm, int *ierr) {
   (*ierr) = MPI_Bcast(buffer, *count, *datatype, *root, *comm);
}
void mpi_gather_ (void *sendbuf, int *sendcnt, MPI_Datatype *sendtype, 
               void *recvbuf, int *recvcnt, MPI_Datatype *recvtype, 
               int *root, MPI_Comm *comm, int *ierr) {
   (*ierr) = MPI_Gather(sendbuf, *sendcnt, *sendtype, recvbuf, *recvcnt, *recvtype, *root, *comm);
}
void mpi_scatter_ (void *sendbuf, int *sendcnt, MPI_Datatype *sendtype, 
               void *recvbuf, int *recvcnt, MPI_Datatype *recvtype, int *root, 
               MPI_Comm *comm, int *ierr) {
   (*ierr) = MPI_Scatter(sendbuf, *sendcnt, *sendtype, recvbuf, *recvcnt, *recvtype, *root, *comm);
}
void mpi_allgather_ (void *sendbuf, int *sendcount, MPI_Datatype *sendtype, 
               void *recvbuf, int *recvcount, MPI_Datatype *recvtype, 
               MPI_Comm *comm, int *ierr) {
   (*ierr) = MPI_Allgather(sendbuf, *sendcount, *sendtype, recvbuf, *recvcount, *recvtype, *comm);
}
void mpi_alltoall_ (void *sendbuf, int *sendcount, MPI_Datatype *sendtype, 
                 void *recvbuf, int *recvcount, MPI_Datatype *recvtype, 
                 MPI_Comm *comm, int *ierr) {
   (*ierr) = MPI_Alltoall(sendbuf, *sendcount, *sendtype, recvbuf, *recvcount, *recvtype, *comm);
}
void mpi_alltoallv_ (void *sendbuf, int *sendcnts, int *sdispls, 
                  MPI_Datatype *sendtype, void *recvbuf, int *recvcnts, 
                  int *rdispls, MPI_Datatype *recvtype, MPI_Comm *comm, int *ierr) {
   (*ierr) = MPI_Alltoallv(sendbuf, sendcnts, sdispls, *sendtype, recvbuf, recvcnts, rdispls, *recvtype, *comm);
}
// COLLECTIVE - Computational
void mpi_reduce_ (void *sendbuf, void *recvbuf, int *count, MPI_Datatype *datatype, 
               MPI_Op *op, int *root, MPI_Comm *comm, int *ierr) {
   (*ierr) = MPI_Reduce(sendbuf, recvbuf, *count, *datatype, *op, *root, *comm);
}
void mpi_allreduce_ (void *sendbuf, void *recvbuf, int *count, 
                   MPI_Datatype *datatype, MPI_Op *op, MPI_Comm *comm, int *ierr) {
   (*ierr) = MPI_Allreduce (sendbuf, recvbuf, *count, *datatype, *op, *comm);
}

// TIME 
double mpi_wtime_ () {
   return MPI_Wtime();
}
double mpi_wtick_ () {
   return MPI_Wtick();
}

// !BAM added
void mpi_abort_ (MPI_Comm *comm, int *errorcode, int *ierr) {
   (*ierr) = MPI_Abort(*comm, *errorcode);
}
void mpi_error_string_ (int *errorcode, char *string, int len, int *resultlen, int *ierr) {
   char *newStr = new char[len];
   memcpy(newStr,string,len);
   newStr[len-1]='\0';
   (*ierr) = MPI_Error_string(*errorcode, newStr, resultlen);
}
void mpi_get_version_ (int *version, int *subversion, int *ierr) {
   (*ierr) = MPI_Get_version(version, subversion);
}
void mpi_type_size_ (MPI_Datatype *datatype, int *size, int *ierr) {
   (*ierr) = MPI_Type_size(*datatype, size);
}

#ifdef __cplusplus
} //extern "C"
#endif

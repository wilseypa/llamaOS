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

#ifndef llamaos_mpi_mpi_h_
#define llamaos_mpi_mpi_h_

#ifdef __cplusplus
extern "C" {
#endif

/* MPI's error classes */
#define MPI_SUCCESS          0      /* Successful return code */

typedef int MPI_Datatype;
#define MPI_CHAR           ((MPI_Datatype)0x4c000101)
#define MPI_SIGNED_CHAR    ((MPI_Datatype)0x4c000118)
#define MPI_UNSIGNED_CHAR  ((MPI_Datatype)0x4c000102)
#define MPI_BYTE           ((MPI_Datatype)0x4c00010d)
#define MPI_WCHAR          ((MPI_Datatype)0x4c00040e)
#define MPI_SHORT          ((MPI_Datatype)0x4c000203)
#define MPI_UNSIGNED_SHORT ((MPI_Datatype)0x4c000204)
#define MPI_INT            ((MPI_Datatype)0x4c000405)
#define MPI_UNSIGNED       ((MPI_Datatype)0x4c000406)
#define MPI_LONG           ((MPI_Datatype)0x4c000807)
#define MPI_UNSIGNED_LONG  ((MPI_Datatype)0x4c000808)
#define MPI_FLOAT          ((MPI_Datatype)0x4c00040a)
#define MPI_DOUBLE         ((MPI_Datatype)0x4c00080b)
#define MPI_LONG_DOUBLE    ((MPI_Datatype)0x4c00100c)
#define MPI_LONG_LONG_INT  ((MPI_Datatype)0x4c000809)
#define MPI_UNSIGNED_LONG_LONG ((MPI_Datatype)0x4c000819)
#define MPI_LONG_LONG      MPI_LONG_LONG_INT

typedef int MPI_Comm;
#define MPI_COMM_WORLD ((MPI_Comm)0x44000000)
#define MPI_COMM_SELF  ((MPI_Comm)0x44000001)

/* Groups */
typedef int MPI_Group;
#define MPI_GROUP_EMPTY ((MPI_Group)0x48000000)

typedef int MPI_Count;

/* Define some null objects */
#define MPI_COMM_NULL      ((MPI_Comm)0x04000000)
#define MPI_OP_NULL        ((MPI_Op)0x18000000)
#define MPI_GROUP_NULL     ((MPI_Group)0x08000000)
#define MPI_DATATYPE_NULL  ((MPI_Datatype)0x0c000000)
#define MPI_REQUEST_NULL   ((MPI_Request)0x2c000000)
#define MPI_ERRHANDLER_NULL ((MPI_Errhandler)0x14000000)
#define MPI_MESSAGE_NULL   ((MPI_Message)MPI_REQUEST_NULL)
#define MPI_MESSAGE_NO_PROC ((MPI_Message)0x6c000000)

/* Pre-defined constants */
#define MPI_UNDEFINED      (-32766)
#define MPI_KEYVAL_INVALID 0x24000000

#define MPI_ERR_UNKNOWN     13      /* Unknown error */
#define MPI_ERR_INTERN      16      /* Internal error code    */

#define MPI_MAX_LIBRARY_VERSION_STRING 256
#define MPI_MAX_ERROR_STRING   256

#define MPI_PROC_NULL   (-1)
#define MPI_ANY_SOURCE  (-2)
#define MPI_ROOT        (-3)
#define MPI_ANY_TAG     (-1)

/* The order of these elements must match that in mpif.h */
typedef struct MPI_Status {
    int MPI_SOURCE;
    int MPI_TAG;
    int MPI_ERROR;
    MPI_Count count;
    int cancelled;
    int abi_slush_fund[2];
//    @EXTRA_STATUS_DECL@
} MPI_Status;

/* Collective operations */
typedef int MPI_Op;

#define MPI_MAX     (MPI_Op)(0x58000001)
#define MPI_MIN     (MPI_Op)(0x58000002)
#define MPI_SUM     (MPI_Op)(0x58000003)
#define MPI_PROD    (MPI_Op)(0x58000004)
#define MPI_LAND    (MPI_Op)(0x58000005)
#define MPI_BAND    (MPI_Op)(0x58000006)
#define MPI_LOR     (MPI_Op)(0x58000007)
#define MPI_BOR     (MPI_Op)(0x58000008)
#define MPI_LXOR    (MPI_Op)(0x58000009)
#define MPI_BXOR    (MPI_Op)(0x5800000a)
#define MPI_MINLOC  (MPI_Op)(0x5800000b)
#define MPI_MAXLOC  (MPI_Op)(0x5800000c)
#define MPI_REPLACE (MPI_Op)(0x5800000d)
#define MPI_NO_OP   (MPI_Op)(0x5800000e)

typedef int MPI_Errhandler;

typedef int MPI_Aint;

int MPI_Init (int *argc, char ***argv);
int MPI_Finalize (void);
int MPI_Abort(MPI_Comm comm, int errorcode);

int MPI_Comm_rank (MPI_Comm comm, int *rank);
int MPI_Comm_size(MPI_Comm comm, int *size);
int MPI_Comm_group(MPI_Comm comm, MPI_Group *group);
int MPI_Comm_split(MPI_Comm comm, int color, int key, MPI_Comm *newcomm);
int MPI_Comm_free(MPI_Comm *comm);

int MPI_Group_translate_ranks(MPI_Group group1, int n, const int ranks1[], MPI_Group group2,
                              int ranks2[]);

int MPI_Get_count(const MPI_Status *status, MPI_Datatype datatype, int *count);

typedef int MPI_Request;

int MPI_Waitall(int count, MPI_Request array_of_requests[], MPI_Status array_of_statuses[]);


int MPI_Barrier(MPI_Comm comm);
int MPI_Type_size(MPI_Datatype datatype, int *size);

int MPI_Recv(void *buf, int count, MPI_Datatype datatype, int source, int tag, MPI_Comm comm, MPI_Status *status);
int MPI_Irecv(void *buf, int count, MPI_Datatype datatype, int source, int tag, MPI_Comm comm, MPI_Request *request);

int MPI_Send(void *buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm);
int MPI_Isend(void *buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm, MPI_Request *request);

int MPI_Test(MPI_Request *request, int *flag, MPI_Status *status);

int MPI_Bcast(void *buffer, int count, MPI_Datatype datatype, int root, MPI_Comm comm);

double MPI_Wtime(void);
double MPI_Wtick(void);

int MPI_Error_string(int errorcode, char *string, int *resultlen);
int MPI_Get_version(int *version, int *subversion);

int MPI_Allreduce(const void *sendbuf, void *recvbuf, int count, MPI_Datatype datatype,
                  MPI_Op op, MPI_Comm comm);
int MPI_Gather(const void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf,
               int recvcount, MPI_Datatype recvtype, int root, MPI_Comm comm);

#ifdef __cplusplus
}
#endif

#endif  // llamaos_mpi_mpi_h_

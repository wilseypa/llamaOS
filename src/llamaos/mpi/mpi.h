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

// MOST OF THE FOLLOWING IS COPIED FROM MPICH-3.0.1

#if 0
                                  COPYRIGHT

The following is a notice of limited availability of the code, and disclaimer
which must be included in the prologue of the code and in all source listings
of the code.

Copyright Notice
 + 2002 University of Chicago

Permission is hereby granted to use, reproduce, prepare derivative works, and
to redistribute to others.  This software was authored by:

Mathematics and Computer Science Division
Argonne National Laboratory, Argonne IL 60439

(and)

Department of Computer Science
University of Illinois at Urbana-Champaign


                              GOVERNMENT LICENSE

Portions of this material resulted from work developed under a U.S.
Government Contract and are subject to the following license: the Government
is granted for itself and others acting on its behalf a paid-up, nonexclusive,
irrevocable worldwide license in this computer software to reproduce, prepare
derivative works, and perform publicly and display publicly.

                                  DISCLAIMER

This computer code material was prepared, in part, as an account of work
sponsored by an agency of the United States Government.  Neither the United
States, nor the University of Chicago, nor any of their employees, makes any
warranty express or implied, or assumes any legal liability or responsibility
for the accuracy, completeness, or usefulness of any information, apparatus,
product, or process disclosed, or represents that its use would not infringe
privately owned rights.

#endif

// MPI macros and type defines


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



/* Communicators */
typedef int MPI_Comm;
#define MPI_COMM_WORLD ((MPI_Comm)0x44000000)
#define MPI_COMM_SELF  ((MPI_Comm)0x44000001)

/* Groups */
typedef int MPI_Group;
#define MPI_GROUP_EMPTY ((MPI_Group)0x48000000)

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

/* Define some null objects */
#define MPI_COMM_NULL      ((MPI_Comm)0x04000000)
#define MPI_OP_NULL        ((MPI_Op)0x18000000)
#define MPI_GROUP_NULL     ((MPI_Group)0x08000000)
#define MPI_DATATYPE_NULL  ((MPI_Datatype)0x0c000000)
#define MPI_REQUEST_NULL   ((MPI_Request)0x2c000000)
#define MPI_ERRHANDLER_NULL ((MPI_Errhandler)0x14000000)
#define MPI_MESSAGE_NULL   ((MPI_Message)MPI_REQUEST_NULL)
#define MPI_MESSAGE_NO_PROC ((MPI_Message)0x6c000000)

/* These are only guesses; make sure you change them in mpif.h as well */
#define MPI_MAX_PROCESSOR_NAME 128
#define MPI_MAX_LIBRARY_VERSION_STRING 8192
#define MPI_MAX_ERROR_STRING   1024
#define MPI_MAX_PORT_NAME      256
#define MPI_MAX_OBJECT_NAME    128

/* Pre-defined constants */
#define MPI_UNDEFINED      (-32766)
#define MPI_KEYVAL_INVALID 0x24000000

#define MPI_PROC_NULL   (-1)
#define MPI_ANY_SOURCE  (-2)
#define MPI_ROOT        (-3)
#define MPI_ANY_TAG     (-1)

#define MPI_LOCK_EXCLUSIVE  234
#define MPI_LOCK_SHARED     235

/* MPI request opjects */
typedef int MPI_Request;

/* MPI message objects for Mprobe and related functions */
typedef int MPI_Message;

/* User combination function */
typedef void (MPI_User_function) ( void *, void *, int *, MPI_Datatype * ); 

/* MPI Attribute copy and delete functions */
typedef int (MPI_Copy_function) ( MPI_Comm, int, void *, void *, void *, int * );
typedef int (MPI_Delete_function) ( MPI_Comm, int, void *, void * );

#define MPI_VERSION    3
#define MPI_SUBVERSION 0

/* for info */
typedef int MPI_Info;
#define MPI_INFO_NULL         ((MPI_Info)0x1c000000)
#define MPI_INFO_ENV          ((MPI_Info)0x5c000001)
#define MPI_MAX_INFO_KEY       255
#define MPI_MAX_INFO_VAL      1024

/* predefined types for MPI_Comm_split_type */
#define MPI_COMM_TYPE_SHARED    1

/* Definitions that are determined by configure. */
typedef long MPI_Aint;
typedef int MPI_Fint;
typedef long long MPI_Count;

/* The order of these elements must match that in mpif.h */
typedef struct MPI_Status {
    int MPI_SOURCE;
    int MPI_TAG;
    int MPI_ERROR;
    MPI_Count count;
    int cancelled;
    int abi_slush_fund[2];
    
} MPI_Status;

/* The MPI standard requires that the ARGV_NULL values be the same as
   NULL (see 5.3.2) */
#define MPI_ARGV_NULL (char **)0
#define MPI_ARGVS_NULL (char ***)0

/* MPI's error classes */
#define MPI_SUCCESS          0      /* Successful return code */
/* Communication argument parameters */
#define MPI_ERR_BUFFER       1      /* Invalid buffer pointer */
#define MPI_ERR_COUNT        2      /* Invalid count argument */
#define MPI_ERR_TYPE         3      /* Invalid datatype argument */
#define MPI_ERR_TAG          4      /* Invalid tag argument */
#define MPI_ERR_COMM         5      /* Invalid communicator */
#define MPI_ERR_RANK         6      /* Invalid rank */
#define MPI_ERR_ROOT         7      /* Invalid root */
#define MPI_ERR_TRUNCATE    14      /* Message truncated on receive */

/* MPI Objects (other than COMM) */
#define MPI_ERR_GROUP        8      /* Invalid group */
#define MPI_ERR_OP           9      /* Invalid operation */
#define MPI_ERR_REQUEST     19      /* Invalid mpi_request handle */

/* Special topology argument parameters */
#define MPI_ERR_TOPOLOGY    10      /* Invalid topology */
#define MPI_ERR_DIMS        11      /* Invalid dimension argument */

/* All other arguments.  This is a class with many kinds */
#define MPI_ERR_ARG         12      /* Invalid argument */

/* Other errors that are not simply an invalid argument */
#define MPI_ERR_OTHER       15      /* Other error; use Error_string */

#define MPI_ERR_UNKNOWN     13      /* Unknown error */
#define MPI_ERR_INTERN      16      /* Internal error code    */

/* Multiple completion has two special error classes */
#define MPI_ERR_IN_STATUS   17      /* Look in status for error value */
#define MPI_ERR_PENDING     18      /* Pending request */

/* New MPI-2 Error classes */
#define MPI_ERR_FILE        27      /* */
#define MPI_ERR_ACCESS      20      /* */
#define MPI_ERR_AMODE       21      /* */
#define MPI_ERR_BAD_FILE    22      /* */
#define MPI_ERR_FILE_EXISTS 25      /* */
#define MPI_ERR_FILE_IN_USE 26      /* */
#define MPI_ERR_NO_SPACE    36      /* */
#define MPI_ERR_NO_SUCH_FILE 37     /* */
#define MPI_ERR_IO          32      /* */
#define MPI_ERR_READ_ONLY   40      /* */
#define MPI_ERR_CONVERSION  23      /* */
#define MPI_ERR_DUP_DATAREP 24      /* */
#define MPI_ERR_UNSUPPORTED_DATAREP   43  /* */

/* MPI_ERR_INFO is NOT defined in the MPI-2 standard.  I believe that
   this is an oversight */
#define MPI_ERR_INFO        28      /* */
#define MPI_ERR_INFO_KEY    29      /* */
#define MPI_ERR_INFO_VALUE  30      /* */
#define MPI_ERR_INFO_NOKEY  31      /* */

#define MPI_ERR_NAME        33      /* */
#define MPI_ERR_NO_MEM      34      /* Alloc_mem could not allocate memory */
#define MPI_ERR_NOT_SAME    35      /* */
#define MPI_ERR_PORT        38      /* */
#define MPI_ERR_QUOTA       39      /* */
#define MPI_ERR_SERVICE     41      /* */
#define MPI_ERR_SPAWN       42      /* */
#define MPI_ERR_UNSUPPORTED_OPERATION 44 /* */
#define MPI_ERR_WIN         45      /* */

#define MPI_ERR_BASE        46      /* */
#define MPI_ERR_LOCKTYPE    47      /* */
#define MPI_ERR_KEYVAL      48      /* Erroneous attribute key */
#define MPI_ERR_RMA_CONFLICT 49     /* */
#define MPI_ERR_RMA_SYNC    50      /* */ 
#define MPI_ERR_SIZE        51      /* */
#define MPI_ERR_DISP        52      /* */
#define MPI_ERR_ASSERT      53      /* */

#define MPIX_ERR_PROC_FAIL_STOP 54   /* Process failure */

#define MPI_ERR_RMA_RANGE  55       /* */
#define MPI_ERR_RMA_ATTACH 56       /* */
#define MPI_ERR_RMA_SHARED 57       /* */
#define MPI_ERR_RMA_FLAVOR 58       /* */

#define MPI_ERR_LASTCODE    0x3fffffff  /* Last valid error code for a 
                                           predefined error class */
/* WARNING: this is also defined in mpishared.h.  Update both locations */

// C function API prototypes

int MPI_Init (int *argc, char ***argv);
int MPI_Finalize (void);

int MPI_Comm_rank (MPI_Comm comm, int *rank);
int MPI_Comm_size (MPI_Comm comm, int *size);

int MPI_Recv (void *buf, int count, MPI_Datatype datatype, int source, int tag, MPI_Comm comm, MPI_Status *status);
int MPI_Irecv (void *buf, int count, MPI_Datatype datatype, int source, int tag, MPI_Comm comm, MPI_Request *request);

int MPI_Send (void *buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm);
int MPI_Isend (void *buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm, MPI_Request *request);

int MPI_Test (MPI_Request *request, int *flag, MPI_Status *status);


#if 0

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

#endif

#ifdef __cplusplus
}
#endif

#endif  // llamaos_mpi_mpi_h_

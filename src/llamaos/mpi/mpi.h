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

// MPI TYPEDEF AND DEFINES
/* MPI's error classes */
#define MPI_SUCCESS          0      /* Successful return code */

typedef int MPI_Datatype;
#define MPI_UNSIGNED_CHAR  ((MPI_Datatype)1)

typedef int MPI_Comm;
#define MPI_COMM_NULL  ((MPI_Comm)0x00000000)
#define MPI_COMM_WORLD ((MPI_Comm)0x7FFFFFFF)
#define MPI_COMM_SELF  ((MPI_Comm)0x7FFFFFFE)

typedef int MPI_Group;
#define MPI_GROUP_NULL  ((MPI_Group)0x00000000)
#define MPI_GROUP_EMPTY ((MPI_Group)0xFFFFFFFF)

typedef int MPI_Count;
typedef int MPI_Request;

#define MPI_UNDEFINED (-1)

#define MPI_ANY_SOURCE (0xFFFFFFFF)
#define MPI_ANY_TAG (0xFFFFFFFF)


// MPI STRUCTURES
typedef struct MPI_Status {
    int MPI_SOURCE;
    int MPI_TAG;
    int MPI_ERROR;
} MPI_Status;


// MPI FUNCTIONS
int MPI_Init (int *argc, char ***argv);
int MPI_Finalize (void);

int MPI_Comm_rank (MPI_Comm comm, int *rank);
int MPI_Comm_size (MPI_Comm comm, int *size);

int MPI_Recv(void *buf, int count, MPI_Datatype datatype, int source, int tag, MPI_Comm comm, MPI_Status *status);
int MPI_Irecv(void *buf, int count, MPI_Datatype datatype, int source, int tag, MPI_Comm comm, MPI_Request *request);

int MPI_Send(void *buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm);
int MPI_Isend(void *buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm, MPI_Request *request);

int MPI_Test(MPI_Request *request, int *flag, MPI_Status *status);

int MPI_Bcast(void *buffer, int count, MPI_Datatype datatype, int root, MPI_Comm comm );
int MPI_Barrier (MPI_Comm comm);

#endif  // llamaos_mpi_mpi_h_

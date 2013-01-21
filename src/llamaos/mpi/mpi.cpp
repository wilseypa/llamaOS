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

#include <cstring>

#include <stdexcept>
#include <string>
#include <sstream>

#include <llamaos/mpi/mpi.h>
#include <llamaos/net/llamaNET.h>
#include <llamaos/xen/Hypervisor.h>

template <typename T>
static T convert (const std::string &s)
{
   std::stringstream ss (s);
   T t;
   ss >> t;

   if (!ss.fail ())
   {
      return t;
   }

   std::stringstream err;
   err << "failed to convert string: " << s;
   throw std::runtime_error (err.str ());
}

template <typename T>
static T parse (int argc, char *argv [], const std::string &arg, const T &value)
{
   for (int i = 1; i < argc; i++)
   {
      if (arg == argv [i])
      {
         if ((i + 1) >= argc)
         {
            std::stringstream err;
            err << "missing argument value for " << arg;
            throw std::runtime_error (err.str ());
         }

         return convert<T> (argv [i + 1]);
      }
   }

   return value;
}

using namespace std;
using namespace llamaos;
using namespace llamaos::xen;

static net::llamaNET *interface = nullptr;
static int node;

static uint32_t seq = 1;

static domid_t get_domd_id (int node)
{
   // for now it's just self minus node % 6
   domid_t self_id = Hypervisor::get_instance ()->domid;

   //  0,  2,  4,  6,  8, 10
   // -1, -2, -3, -4, -5, -6

   //  1,  3,  5,  7,  9, 11
   // -1, -2, -3, -4, -5, -6

   return (self_id - 1 - (node / 2));
}

extern "C"
int MPI_Init (int *argc, char ***argv)
{
   node = parse<int>(*argc, *argv, "--node", 0);
   interface = new net::llamaNET (get_domd_id (node), (node / 2));

   return MPI_SUCCESS;
}

extern "C"
int MPI_Finalize (void)
{
   delete interface;

   return MPI_SUCCESS;
}

extern "C"
int MPI_Comm_rank (MPI_Comm comm, int *rank)
{
   *rank = node;

   return MPI_SUCCESS;
}

extern "C"
int MPI_Comm_size (MPI_Comm comm, int *size)
{
   *size = 2;

   return MPI_SUCCESS;
}

extern "C"
int MPI_Recv (void *buf, int count, MPI_Datatype datatype, int source, int tag, MPI_Comm comm, MPI_Status *status)
{
   net::llamaNET::Protocol_header *header;

   for (;;)
   {
      header = interface->recv (node);

      if (header->src == static_cast<uint32_t>(source))
      {
         break;
      }
      else
      {
         interface->release_recv_buffer (header);
      }
   }

   if (header->len < static_cast<uint32_t>(count))
   {
      interface->release_recv_buffer (header);
      return -1;
   }

   unsigned char *data = reinterpret_cast<unsigned char *>(header + 1);

   memcpy (buf, data, header->len);
   status->count = header->len;
   status->MPI_SOURCE = header->src;
   interface->release_recv_buffer (header);

   return MPI_SUCCESS;
}

extern "C"
int MPI_Irecv (void *buf, int count, MPI_Datatype datatype, int source, int tag, MPI_Comm comm, MPI_Request *request)
{
   return MPI_SUCCESS;
}

extern "C"
int MPI_Send (void *buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm)
{
   net::llamaNET::Protocol_header *header = interface->get_send_buffer ();

   header->dest = dest;
   header->src = node;
   header->type = 1;
   header->seq = seq++;
   header->len = count;

   unsigned char *data = reinterpret_cast<unsigned char *>(header + 1);

   memcpy (data, buf, count);

   interface->send (header);

   return MPI_SUCCESS;
}

extern "C"
int MPI_Isend (void *buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm, MPI_Request *request)
{
   return MPI_SUCCESS;
}

extern "C"
int MPI_Test (MPI_Request *request, int *flag, MPI_Status *status)
{
   return MPI_SUCCESS;
}

extern "C"
int MPI_Barrier (MPI_Comm comm)
{
   return MPI_SUCCESS;
}

extern "C"
int MPI_Type_size (MPI_Datatype datatype, int *size)
{
   return MPI_SUCCESS;
}

extern "C"
double MPI_Wtime (void)
{
   return 0.0;
}

extern "C"
int MPI_Error_string (int errorcode, char *string, int *resultlen)
{
   return MPI_SUCCESS;
}

extern "C"
int MPI_Abort (MPI_Comm comm, int errorcode)
{
   return MPI_SUCCESS;
}

extern "C"
int MPI_Waitall (int count, MPI_Request array_of_requests[], MPI_Status array_of_statuses[])
{
   return MPI_SUCCESS;
}

extern "C"
int MPI_Get_version (int *version, int *subversion)
{
   return MPI_SUCCESS;
}

extern "C"
int MPI_Bcast (void *buffer, int count, MPI_Datatype datatype, int root, MPI_Comm comm)
{
   return MPI_SUCCESS;
}

extern "C"
int MPI_Comm_free (MPI_Comm *comm)
{
   return MPI_SUCCESS;
}

extern "C"
int MPI_Comm_split (MPI_Comm comm, int color, int key, MPI_Comm *newcomm)
{
   return MPI_SUCCESS;
}

extern "C"
int MPI_Comm_group (MPI_Comm comm, MPI_Group *group)
{
   return MPI_SUCCESS;
}

extern "C"
int MPI_Group_translate_ranks (MPI_Group group1, int n, int *ranks1, MPI_Group group2, int *ranks2)
{
   return MPI_SUCCESS;
}

extern "C"
int MPI_Get_count (MPI_Status *status,  MPI_Datatype datatype, int *count)
{
   return MPI_SUCCESS;
}

extern "C"
int MPI_Allreduce (void *sendbuf, void *recvbuf, int count, MPI_Datatype datatype, MPI_Op op, MPI_Comm comm)
{
   return MPI_SUCCESS;
}

extern "C"
int MPI_Gather (void *sendbuf, int sendcnt, MPI_Datatype sendtype, void *recvbuf, int recvcnt, MPI_Datatype recvtype, int root, MPI_Comm comm)
{
   return MPI_SUCCESS;
}

#if 0

#include <cstring>

#include <sstream>
#include <stdexcept>
#include <string>

#include <iostream>

template <typename T>
static T convert (const std::string &s)
{
   std::stringstream ss (s);
   T t;
   ss >> t;

   if (!ss.fail ())
   {
      return t;
   }

   std::stringstream err;
   err << "failed to convert string: " << s;
   throw std::runtime_error (err.str ());
}

template <typename T>
static T parse (int argc, char *argv [], const std::string &arg, const T &value)
{
std::cout << "parsing args" << std::endl;
   for (int i = 1; i < argc; i++)
   {
std::cout << " " << argv [i] << std::endl;
      if (arg == argv [i])
      {
         if ((i + 1) >= argc)
         {
            std::stringstream err;
            err << "missing argument value for " << arg;
            throw std::runtime_error (err.str ());
         }

         return convert<T> (argv [i + 1]);
      }
   }

   return value;
}

#include <llamaos/mpi/mpi.h>
#include <llamaos/net/llamaNET.h>
#include <llamaos/xen/Hypervisor.h>

using namespace std;
using namespace llamaos;
using namespace llamaos::xen;

static uint32_t seq = 1;

static domid_t get_domd_id (int node)
{
   // for now it's just self minus node % 6
   domid_t self_id = Hypervisor::get_instance ()->domid;

   //  0,  2,  4,  6,  8, 10
   // -1, -2, -3, -4, -5, -6

   //  1,  3,  5,  7,  9, 11
   // -1, -2, -3, -4, -5, -6

   return (self_id - 1 - (node / 2));
}

static net::llamaNET *interface = nullptr;
static int node;

int MPI_Init (int *argc, char ***argv) 
{
   node = parse<int>(*argc, *argv, "--node", 0);
   interface = new net::llamaNET (get_domd_id (node), (node / 2));

   return MPI_SUCCESS;
}

int MPI_Finalize (void)
{
   delete interface;

   return MPI_SUCCESS;
}

int MPI_Comm_rank (MPI_Comm comm, int *rank)
{
   *rank = node;

   return MPI_SUCCESS;
}

int MPI_Recv(void *buf, int count, MPI_Datatype datatype, int source, int tag, MPI_Comm comm, MPI_Status *status)
{
   net::llamaNET::Protocol_header *header;

   for (;;)
   {
      header = interface->recv (node);

      if (header->src == static_cast<uint32_t>(source))
      {
         break;
      }
      else
      {
         interface->release_recv_buffer (header);
      }
   }

   if (header->len < static_cast<uint32_t>(count))
   {
      interface->release_recv_buffer (header);
      return -1;
   }

   unsigned char *data = reinterpret_cast<unsigned char *>(header + 1);

   memcpy (buf, data, header->len);
   status->count = header->len;
   status->MPI_SOURCE = header->src;
   interface->release_recv_buffer (header);

   return MPI_SUCCESS;
}

int MPI_Irecv(void *buf, int count, MPI_Datatype datatype, int source, int tag, MPI_Comm comm, MPI_Request *request)
{
   return 0;
}

int MPI_Send(void *buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm)
{
   net::llamaNET::Protocol_header *header = interface->get_send_buffer ();

   header->dest = dest;
   header->src = node;
   header->type = 1;
   header->seq = seq++;
   header->len = count;

   unsigned char *data = reinterpret_cast<unsigned char *>(header + 1);

   memcpy (data, buf, count);

   interface->send (header);

   return MPI_SUCCESS;
}

int MPI_Isend(void *buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm, MPI_Request *request)
{
   return 0;
}

int MPI_Test(MPI_Request *request, int *flag, MPI_Status *status)
{
   return 0;
}

int MPI_Barrier(MPI_Comm comm)
{
   return MPI_SUCCESS;
}

int MPI_Type_size(MPI_Datatype datatype, int *size)
{
   return MPI_SUCCESS;
}

double MPI_Wtime(void)
{
   return 0.0;
}

double MPI_Wtick(void)
{
   return 0.0;
}

#endif
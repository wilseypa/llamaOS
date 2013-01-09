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

#include <sstream>
#include <stdexcept>
#include <string>

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

   return (self_id - 1 - (node % 6));
}

static net::llamaNET *interface = nullptr;
static int node;

int MPI_Init (int *argc, char ***argv) 
{
   node = parse<int>(*argc, *argv, "--node", 0);
   interface = new net::llamaNET (get_domd_id (node), (node % 6));

   return MPI_SUCCESS;
}

int MPI_Finalize (void)
{
   delete interface;

   return MPI_SUCCESS;
}

int MPI_Comm_rank (MPI_Comm comm, int *rank)
{
   return node;
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

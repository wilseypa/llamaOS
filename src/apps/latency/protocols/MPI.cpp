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

#include <cstdlib>
#include <cstring>

#include <iostream>

#include <mpi.h>

#include <latency/protocols/MPI.h>
#include <latency/parse_args.cpp>
#include <latency/verify.h>


using namespace std;
using namespace latency;

Protocol *Protocol::create (int argc, char *argv [])
{
   cout << "creating MPI protocol" << endl;
   return new protocols::MPI (argc, argv);
}

static int get_node (int argc, char *argv [])
{
   MPI_Init (&argc, &argv);

   int rank;
   MPI_Comm_rank (MPI_COMM_WORLD, &rank);

   return rank;
}

static unsigned char *alloc_buffer ()
{
   void *mem;
   posix_memalign (&mem, 4096, 4096);

   return reinterpret_cast<unsigned char *>(mem);
}

protocols::MPI::MPI (int argc, char *argv [])
   :  node(get_node(argc, argv)),
      client((node % 2) == 1),
      blocking(parse<bool>(argc, argv, "--blocking", false)),
      buffer(alloc_buffer ())
{
   memset (buffer, '\0', 4096);

   cout << "Node number " << node << endl;
   if (client) {
      cout << "I am the client" << endl;
   } else {
      cout << "I am the server" << endl;
   }
   if (blocking) {
      cout << "Running in blocking mode" << endl;
   } else {
      cout << "Running in non-blocking mode" << endl;
   }

   if (node == 0)
   {
      cout << "latency-MPI" << endl
           << "  node: " << node << endl;
   }
}

protocols::MPI::~MPI ()
{
   MPI_Finalize ();
}

bool protocols::MPI::root_node ()
{
   return (node == 0);
}

bool protocols::MPI::startup (unsigned long max_msg_size)
{
   return true;
}

bool protocols::MPI::cleanup ()
{
   return true;
}

bool protocols::MPI::run_verify (unsigned long msg_size)
{
   // TCP doesn't send anything for a zero length message, so make it 8 bytes
   msg_size = max (8UL, msg_size);

   // client initiates the trial
   if (client)
   {
      // marks all bytes with alpha chars (a,b,c,...)
      mark_data_alpha (buffer, msg_size);

      // send/recv and verify the data has been changed to numerals (1,2,3,...)
      if (   (send_buffer (msg_size))
          && (recv_buffer (msg_size))
          && (verify_data_numeric (buffer, msg_size)))
      {
         return true;
      }
   }
   else
   {
      // wait for mesg and verify alpha chars
      if (   (recv_buffer (msg_size))
          && (verify_data_alpha (buffer, msg_size)))
      {
         // marks all bytes with numerals and send
         mark_data_numeric (buffer, msg_size);
         return send_buffer (msg_size);
      }
   }

   return false;
}

bool protocols::MPI::run_trial (unsigned long msg_size, unsigned long trial_number)
{
   // TCP doesn't send anything for a zero length message, so make it 8 bytes
   msg_size = max (8UL, msg_size);

   // client initiates the trial
   if (client)
   {
      // send/recv mesg, check first "int" in buffer is the trial number just
      // as a low cost sanity check to verify both machines are in sync
      if (   (send_buffer (msg_size))
          && (recv_buffer (msg_size))
          && (*(reinterpret_cast<unsigned long *>(buffer)) == trial_number))
      {
         return true;
      }
   }
   else
   {
      // wait for message to arrive
      if (recv_buffer (msg_size))
      {
         // place trial number in first "int" for master to verify
         *(reinterpret_cast<unsigned long *>(buffer)) = trial_number;
         return send_buffer (msg_size);
      }
   }

   return true;
}

bool protocols::MPI::recv_buffer (unsigned long length)
{
   MPI_Status status;
   int peer = (node % 2) ? (node - 1) : (node + 1);

   if (blocking)
   {
      if (MPI_SUCCESS == MPI_Recv (buffer,
                                 length,
                                 MPI_UNSIGNED_CHAR,
                                 peer,
                                 0,
                                 MPI_COMM_WORLD,
                                 &status))
      {
         return (peer == status.MPI_SOURCE);
      }
   }
   else
   {
/*      MPI_Request request;

      if (MPI_SUCCESS == MPI_Irecv (buffer,
                                    length,
                                    MPI_UNSIGNED_CHAR,
                                    peer,
                                    0,
                                    MPI_COMM_WORLD,
                                    &request))
      {
         int flag = 0;

         for (;;)
         {
            MPI_Test (&request, &flag, &status);

            if (flag)
            {
               return (peer == status.MPI_SOURCE);
            }
         }
      }*/
   }

   return false;
}

bool protocols::MPI::send_buffer (unsigned long length)
{
   int peer = (node % 2) ? (node - 1) : (node + 1);

   if (blocking)
   {
      if (MPI_SUCCESS == MPI_Send (buffer,
                                 length,
                                 MPI_UNSIGNED_CHAR,
                                 peer,
                                 0,
                                 MPI_COMM_WORLD))
      {
         return true;
      }
   }
   else
   {
      /*MPI_Request request;

      if (MPI_SUCCESS == MPI_Isend (buffer,
                                    length,
                                    MPI_UNSIGNED_CHAR,
                                    peer,
                                    0,
                                    MPI_COMM_WORLD,
                                    &request))
      {
         int flag = 0;
         MPI_Status status;

         for (;;)
         {
            MPI_Test (&request, &flag, &status);

            if (flag)
            {
               return true;
            }
         }
      }*/
   }

   return false;
}

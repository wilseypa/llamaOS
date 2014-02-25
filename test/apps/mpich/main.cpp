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

#include <iostream>

#include <gtest/gtest.h>

#include <mpi.h>

#include <llamaos/xen/Hypervisor.h>

using std::cout;
using std::endl;
using llamaos::xen::Hypervisor;

static int _argc;
static char **_argv;

TEST(MPI_Init, init)
{
   EXPECT_EQ(MPI_SUCCESS, MPI_Init (&_argc, &_argv));
}

TEST(MPI_Comm, size)
{
   int np = -1;

   EXPECT_EQ(MPI_SUCCESS, MPI_Comm_size(MPI_COMM_WORLD, &np));

   EXPECT_EQ(2, np);
}

TEST(MPI_Comm, rank)
{
   int id = -1;

   EXPECT_EQ(MPI_SUCCESS, MPI_Comm_rank(MPI_COMM_WORLD, &id));

   EXPECT_EQ(0, id);
}

TEST(MPI_Send, send)
{
   char buffer [256] = "hello";

   EXPECT_EQ(MPI_SUCCESS, MPI_Send(buffer, strlen(buffer), MPI_CHAR, 1, 0, MPI_COMM_WORLD));
}

TEST(MPI_Finalize, finalize)
{
   EXPECT_EQ(MPI_SUCCESS, MPI_Finalize());
}

int main (int argc, char *argv[])
{
   testing::InitGoogleTest (&argc, argv);

   _argc = argc;
   _argv = argv;

   Hypervisor *hypervisor = Hypervisor::get_instance ();
   hypervisor->xenstore.write_string("/example/f", "test_value");

   return RUN_ALL_TESTS ();
}

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

#include <pmi.h>

#include <iostream>
#include <sstream>
#include <string>

#include <llamaos/xen/Hypervisor.h>
#include <llamaos/mpi/mpi.h>

using std::cout;
using std::endl;
using std::istringstream;
using std::string;

using llamaos::xen::Hypervisor;

static Hypervisor *hypervisor = nullptr;
static int init_rank = -1;
static int init_size = -1;

extern "C"
int PMI_Init( int *spawned )
{
   cout << "calling PMI_Init..." << endl;
   *spawned = 0;

   hypervisor = Hypervisor::get_instance ();

   size_t pos = hypervisor->name.find("-");

   if (pos != string::npos)
   {
      istringstream s(hypervisor->name.substr(pos+1));
      char c;

      s >> init_rank;
      s >> c;
      s >> init_size;
   }

   return PMI_SUCCESS;
}

extern "C"
int PMI_Initialized( int *initialized )
{
   cout << "calling PMI_Initialized..." << endl;
   *initialized = 1;

   return PMI_SUCCESS;
}

extern "C"
int PMI_Finalize( void )
{
   cout << "calling PMI_Finalize..." << endl;

   return PMI_SUCCESS;
}

extern "C"
int PMI_Get_size( int *size )
{
   cout << "calling PMI_Get_size...";

//   *size = atoi(hypervisor->argv [2]);
   *size = init_size;

   cout << *size << endl;

   return PMI_SUCCESS;
}

extern "C"
int PMI_Get_rank( int *rank )
{
   cout << "calling PMI_Get_rank...";

//   *rank = atoi(hypervisor->argv [1]) - 1;
   *rank = init_rank;

   cout << *rank << endl;

   return PMI_SUCCESS;
}

extern "C"
int PMI_Get_universe_size( int *size )
{
   cout << "calling PMI_Get_universe_size...";

//   *size = atoi(hypervisor->argv [2]);
   *size = init_size;

   cout << *size << endl;

   return PMI_SUCCESS;
}

extern "C"
int PMI_Get_appnum( int *appnum )
{
   cout << "calling PMI_Get_appnum..." << endl;
   *appnum = 0;

   return PMI_SUCCESS;
}

extern "C"
int PMI_Publish_name( const char service_name[], const char port[] )
{
   cout << "calling PMI_Publish_name..." << endl;
   return 0;
}

extern "C"
int PMI_Unpublish_name( const char service_name[] )
{
   cout << "calling PMI_Unpublish_name..." << endl;
   return 0;
}

extern "C"
int PMI_Lookup_name( const char service_name[], char port[] )
{
   cout << "calling PMI_Lookup_name..." << endl;
   return 0;
}

extern "C"
int PMI_Barrier( void )
{
   cout << "calling PMI_Barrier..." << endl;

   hypervisor->shared_memory->barrier ();

   return PMI_SUCCESS;
}

extern "C"
int PMI_Abort(int exit_code, const char error_msg[])
{
   cout << "calling PMI_Abort..." << endl;
   return 0;
}

extern "C"
int PMI_KVS_Get_my_name( char kvsname[], int length )
{
   cout << "calling PMI_KVS_Get_my_name..." << endl;
   strncpy(kvsname, "llamaOS", length);

   return PMI_SUCCESS;
}

extern "C"
int PMI_KVS_Get_name_length_max( int *length )
{
   cout << "calling PMI_KVS_Get_name_length_max..." << endl;
   *length = 256;

   return PMI_SUCCESS;
}

extern "C"
int PMI_KVS_Get_key_length_max( int *length )
{
   cout << "calling PMI_KVS_Get_key_length_max..." << endl;
   *length = 256;

   return PMI_SUCCESS;
}

extern "C"
int PMI_KVS_Get_value_length_max( int *length )
{
   cout << "calling PMI_KVS_Get_value_length_max..." << endl;
   *length = 256;

   return PMI_SUCCESS;
}

extern "C"
int PMI_KVS_Put( const char kvsname[], const char key[], const char value[])
{
   cout << "calling PMI_KVS_Put..." << endl;
   cout << "  kvsname: " << kvsname << endl;
   cout << "  key: " << key << endl;
   cout << "  value: " << value << endl;

   if (0 == strcmp (key, "sharedFilename[0]"))
   {
      hypervisor->shared_memory->put_alias(value, key);
   }

   return PMI_SUCCESS;
}

extern "C"
int PMI_KVS_Commit( const char kvsname[] )
{
   cout << "calling PMI_KVS_Commit..." << endl;
   cout << "  kvsname: " << kvsname << endl;

   return PMI_SUCCESS;
}

extern "C"
int PMI_KVS_Get( const char kvsname[], const char key[], char value[], int length)
{
   cout << "calling PMI_KVS_Get..." << endl;
   cout << "  kvsname: " << kvsname << endl;
   cout << "  key: " << key << endl;

   if (0 == strcmp (key, "PMI_process_mapping"))
   {
//      strncpy(value, "(vector,(0,2,1),(1,2,1))", length);
//      strncpy(value, "(vector,(0,1,2))", length);
      snprintf(value, length, "(vector,(0,1,%d))", init_size);//atoi(hypervisor->argv [2]));
//      snprintf(value, length, "(vector,(0,4,1))");
      cout << "  value: " << value << endl;

      return PMI_SUCCESS;
   }
   else if (0 == strcmp (key, "sharedFilename[0]"))
   {
      strncpy(value, hypervisor->shared_memory->get_name(key).c_str(), length);
      return PMI_SUCCESS;
   }

   cout << "PMI_ERR_INVALID_KEY: " << key << endl;
   return PMI_ERR_INVALID_KEY;
}

extern "C"
int PMI_Spawn_multiple(int count,
                       const char * cmds[],
                       const char ** argvs[],
                       const int maxprocs[],
                       const int info_keyval_sizesp[],
                       const PMI_keyval_t * info_keyval_vectors[],
                       int preput_keyval_size,
                       const PMI_keyval_t preput_keyval_vector[],
                       int errors[])
{
   cout << "calling PMI_Spawn_multiple..." << endl;
   return 0;
}

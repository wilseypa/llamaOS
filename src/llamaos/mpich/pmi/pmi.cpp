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

#include <pmi.h>

extern "C"
int PMI_Init( int *spawned )
{
   return 0;
}

extern "C"
int PMI_Initialized( int *initialized )
{
   return 0;
}

extern "C"
int PMI_Finalize( void )
{
   return 0;
}

extern "C"
int PMI_Get_size( int *size )
{
   return 0;
}

extern "C"
int PMI_Get_rank( int *rank )
{
   return 0;
}

extern "C"
int PMI_Get_universe_size( int *size )
{
   return 0;
}

extern "C"
int PMI_Get_appnum( int *appnum )
{
   return 0;
}

extern "C"
int PMI_Publish_name( const char service_name[], const char port[] )
{
   return 0;
}

extern "C"
int PMI_Unpublish_name( const char service_name[] )
{
   return 0;
}

extern "C"
int PMI_Lookup_name( const char service_name[], char port[] )
{
   return 0;
}

extern "C"
int PMI_Barrier( void )
{
   return 0;
}

extern "C"
int PMI_Abort(int exit_code, const char error_msg[])
{
   return 0;
}

extern "C"
int PMI_KVS_Get_my_name( char kvsname[], int length )
{
   return 0;
}

extern "C"
int PMI_KVS_Get_name_length_max( int *length )
{
   return 0;
}

extern "C"
int PMI_KVS_Get_key_length_max( int *length )
{
   return 0;
}

extern "C"
int PMI_KVS_Get_value_length_max( int *length )
{
   return 0;
}

extern "C"
int PMI_KVS_Put( const char kvsname[], const char key[], const char value[])
{
   return 0;
}

extern "C"
int PMI_KVS_Commit( const char kvsname[] )
{
   return 0;
}

extern "C"
int PMI_KVS_Get( const char kvsname[], const char key[], char value[], int length)
{
   return 0;
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
   return 0;
}

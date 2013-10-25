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

#ifndef glibc_nptl_sysdeps_llamaos_internaltypes_h
#define glibc_nptl_sysdeps_llamaos_internaltypes_h

#include <stdint.h>

struct pthread_attr
{
  /* Scheduler parameters and priority.  */
  struct sched_param schedparam;
  int schedpolicy;
  /* Various flags like detachstate, scope, etc.  */
  int flags;
  /* Size of guard area.  */
  size_t guardsize;
  /* Stack handling.  */
  void *stackaddr;
  size_t stacksize;
  /* Affinity map.  */
  cpu_set_t *cpuset;
  size_t cpusetsize;
};

#define ATTR_FLAG_DETACHSTATE		0x0001
#define ATTR_FLAG_NOTINHERITSCHED	0x0002
#define ATTR_FLAG_SCOPEPROCESS		0x0004
#define ATTR_FLAG_STACKADDR		0x0008
#define ATTR_FLAG_OLDATTR		0x0010
#define ATTR_FLAG_SCHED_SET		0x0020
#define ATTR_FLAG_POLICY_SET		0x0040

/* Mutex attribute data structure.  */
struct pthread_mutexattr
{
  /* Identifier for the kind of mutex.

     Bit 31 is set if the mutex is to be shared between processes.

     Bit 0 to 30 contain one of the PTHREAD_MUTEX_ values to identify
     the type of the mutex.  */
  int mutexkind;
};

/* Compatibility type for old conditional variable interfaces.  */
typedef struct
{
  pthread_cond_t *cond;
} pthread_cond_2_0_t;

/* Thread-local data handling.  */
struct pthread_key_struct
{
  /* Sequence numbers.  Even numbers indicated vacant entries.  Note
     that zero is even.  We use uintptr_t to not require padding on
     32- and 64-bit machines.  On 64-bit machines it helps to avoid
     wrapping, too.  */
  uintptr_t seq;

  /* Destructor for the data.  */
  void (*destr) (void *);
};

// #include_next <internaltypes.h>

#endif	// glibc_nptl_sysdeps_llamaos_internaltypes_h


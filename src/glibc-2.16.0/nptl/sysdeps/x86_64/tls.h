/*
Copyright (c) 2012, William Magato
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

#ifndef _TLS_H
#define _TLS_H	1

// bypassing pthread logic until llamaOS supports threads


#ifndef llamaos_tls_h
#define llamaos_tls_h

# include <stdbool.h>
# include <stddef.h>
# include <stdint.h>
# include <stdlib.h>
# include <sysdep.h>

#include_next <tls.h>

typedef struct
{
  int multiple_threads;

} tcbhead_t;

#define TLS_TCB_AT_TP 1

#endif  //  llamaos_tls_h

#if 0

# include <stdbool.h>
# include <stddef.h>
# include <stdint.h>
# include <stdlib.h>
# include <sysdep.h>
# include <kernel-features.h>
# include <xmmintrin.h>

/* Type for the dtv.  */
typedef union dtv
{
  size_t counter;
  struct
  {
    void *val;
    bool is_static;
  } pointer;
} dtv_t;

typedef struct
{
  void *tcb;		/* Pointer to the TCB.  Not necessarily the
			   thread descriptor used by libpthread.  */
  dtv_t *dtv;
  void *self;		/* Pointer to the thread descriptor.  */
  int multiple_threads;
  int gscope_flag;
  uintptr_t sysinfo;
  uintptr_t stack_guard;
  uintptr_t pointer_guard;
  unsigned long int vgetcpu_cache[2];
# ifndef __ASSUME_PRIVATE_FUTEX
  int private_futex;
# else
  int __unused1;
# endif
  int rtld_must_xmm_save;
  /* Reservation of some values for the TM ABI.  */
  void *__private_tm[5];
  long int __unused2;
  /* Have space for the post-AVX register size.  */
  __m128 rtld_savespace_sse[8][4] __attribute__ ((aligned (32)));

  void *__padding[8];
} tcbhead_t;
#endif

#endif	/* tls.h */

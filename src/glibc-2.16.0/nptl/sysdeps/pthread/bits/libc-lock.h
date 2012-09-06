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

// bypassing pthread logic until llamaOS supports threads

#ifndef _BITS_LIBC_LOCK_H
#define _BITS_LIBC_LOCK_H 1

// !BAM
// this is from bits/libc-lock.h

/* Define a lock variable NAME with storage class CLASS.  The lock must be
   initialized with __libc_lock_init before it can be used (or define it
   with __libc_lock_define_initialized, below).  Use `extern' for CLASS to
   declare a lock defined in another module.  In public structure
   definitions you must use a pointer to the lock structure (i.e., NAME
   begins with a `*'), because its storage size will not be known outside
   of libc.  */
// !BAM
//#define __libc_lock_define(CLASS,NAME)

// !BAM
// #define __libc_lock_define_recursive(CLASS,NAME)
// #define __rtld_lock_define_recursive(CLASS,NAME)
// #define __libc_rwlock_define(CLASS,NAME)

/* Define an initialized lock variable NAME with storage class CLASS.  */
#define __libc_lock_define_initialized(CLASS,NAME)
#define __libc_rwlock_define_initialized(CLASS,NAME)

/* Define an initialized recursive lock variable NAME with storage
   class CLASS.  */
#define __libc_lock_define_initialized_recursive(CLASS,NAME)
#define __rtld_lock_define_initialized_recursive(CLASS,NAME)

/* Initialize the named lock variable, leaving it in a consistent, unlocked
   state.  */
#define __libc_lock_init(NAME)
#define __libc_rwlock_init(NAME)

/* Same as last but this time we initialize a recursive mutex.  */
#define __libc_lock_init_recursive(NAME)
#define __rtld_lock_init_recursive(NAME)

/* Finalize the named lock variable, which must be locked.  It cannot be
   used again until __libc_lock_init is called again on it.  This must be
   called on a lock variable before the containing storage is reused.  */
#define __libc_lock_fini(NAME)
#define __libc_rwlock_fini(NAME)

/* Finalize recursive named lock.  */
#define __libc_lock_fini_recursive(NAME)

/* Lock the named lock variable.  */
#define __libc_lock_lock(NAME)
#define __libc_rwlock_rdlock(NAME)
#define __libc_rwlock_wrlock(NAME)

/* Lock the recursive named lock variable.  */
#define __libc_lock_lock_recursive(NAME)
#define __rtld_lock_lock_recursive(NAME)

/* Try to lock the named lock variable.  */
#define __libc_lock_trylock(NAME) 0
#define __libc_rwlock_tryrdlock(NAME) 0
#define __libc_rwlock_trywrlock(NAME) 0

/* Try to lock the recursive named lock variable.  */
#define __libc_lock_trylock_recursive(NAME) 0

/* Unlock the named lock variable.  */
#define __libc_lock_unlock(NAME)
#define __libc_rwlock_unlock(NAME)

/* Unlock the recursive named lock variable.  */
#define __libc_lock_unlock_recursive(NAME)
#define __rtld_lock_unlock_recursive(NAME)


/* Define once control variable.  */
#define __libc_once_define(CLASS, NAME) CLASS int NAME = 0

/* Call handler iff the first call.  */
#define __libc_once(ONCE_CONTROL, INIT_FUNCTION) \
  do {									      \
    if ((ONCE_CONTROL) == 0) {						      \
      INIT_FUNCTION ();							      \
      (ONCE_CONTROL) = 1;						      \
    }									      \
  } while (0)

/* Get once control variable.  */
#define __libc_once_get(ONCE_CONTROL) \
  ((ONCE_CONTROL) == 1)

/* Start a critical region with a cleanup function */
#define __libc_cleanup_region_start(DOIT, FCT, ARG)			    \
{									    \
  typeof (***(FCT)) *__save_FCT = (DOIT) ? (FCT) : 0;			    \
  typeof (ARG) __save_ARG = ARG;					    \
  /* close brace is in __libc_cleanup_region_end below. */

/* End a critical region started with __libc_cleanup_region_start. */
#define __libc_cleanup_region_end(DOIT)					    \
  if ((DOIT) && __save_FCT != 0)					    \
    (*__save_FCT)(__save_ARG);						    \
}

/* Sometimes we have to exit the block in the middle.  */
#define __libc_cleanup_end(DOIT)					    \
  if ((DOIT) && __save_FCT != 0)					    \
    (*__save_FCT)(__save_ARG);						    \

#define __libc_cleanup_push(fct, arg) __libc_cleanup_region_start (1, fct, arg)
#define __libc_cleanup_pop(execute) __libc_cleanup_region_end (execute)

/* We need portable names for some of the functions.  */
#define __libc_mutex_unlock

/* Type for key of thread specific data.  */
typedef int __libc_key_t;

/* Create key for thread specific data.  */
#define __libc_key_create(KEY,DEST) -1

/* Set thread-specific data associated with KEY to VAL.  */
#define __libc_setspecific(KEY,VAL) ((void)0)

/* Get thread-specific data associated with KEY.  */
#define __libc_getspecific(KEY) 0

// !BAM
// additions from nptl files

# define _LIBC_LOCK_RECURSIVE_INITIALIZER \
  { 0, 0, NULL }
//  { LLL_LOCK_INITIALIZER, 0, NULL }

#define MUTEX_INITIALIZER 0

/* Mutex type.  */
#if defined _LIBC || defined _IO_MTSAFE_IO
# if (defined NOT_IN_libc && !defined IS_IN_libpthread) || !defined _LIBC
typedef struct { pthread_mutex_t mutex; } __libc_lock_recursive_t;
# else
typedef struct { int lock; int cnt; void *owner; } __libc_lock_recursive_t;
# endif
#else
typedef struct __libc_lock_recursive_opaque__ __libc_lock_recursive_t;
#endif

/* Define a lock variable NAME with storage class CLASS.  The lock must be
   initialized with __libc_lock_init before it can be used (or define it
   with __libc_lock_define_initialized, below).  Use `extern' for CLASS to
   declare a lock defined in another module.  In public structure
   definitions you must use a pointer to the lock structure (i.e., NAME
   begins with a `*'), because its storage size will not be known outside
   of libc.  */
#define __libc_lock_define_recursive(CLASS,NAME) \
  CLASS __libc_lock_recursive_t NAME;

/* Hide the definitions which are only supposed to be used inside libc in
   a separate file.  This file is not present in the installation!  */
#ifdef _LIBC
# include "libc-lockP.h"
#endif

#endif	/* bits/libc-lock.h */


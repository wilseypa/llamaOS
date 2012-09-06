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

#ifndef _PTHREAD_H
#define _PTHREAD_H	1

#include <sched.h>

#include <bits/pthreadtypes.h>

#ifndef NULL
#define NULL 0
#endif

/* Mutex types.  */
enum
{
  PTHREAD_MUTEX_TIMED_NP,
  PTHREAD_MUTEX_RECURSIVE_NP,
  PTHREAD_MUTEX_ERRORCHECK_NP,
  PTHREAD_MUTEX_ADAPTIVE_NP
#if defined __USE_UNIX98 || defined __USE_XOPEN2K8
  ,
  PTHREAD_MUTEX_NORMAL = PTHREAD_MUTEX_TIMED_NP,
  PTHREAD_MUTEX_RECURSIVE = PTHREAD_MUTEX_RECURSIVE_NP,
  PTHREAD_MUTEX_ERRORCHECK = PTHREAD_MUTEX_ERRORCHECK_NP,
  PTHREAD_MUTEX_DEFAULT = PTHREAD_MUTEX_NORMAL
#endif
#ifdef __USE_GNU
  /* For compatibility.  */
  , PTHREAD_MUTEX_FAST_NP = PTHREAD_MUTEX_TIMED_NP
#endif
};

/* Mutex initializers.  */
#ifdef __PTHREAD_MUTEX_HAVE_PREV
# define PTHREAD_MUTEX_INITIALIZER \
  { { 0, 0, 0, 0, 0, 0, { 0, 0 } } }
# ifdef __USE_GNU
#  define PTHREAD_RECURSIVE_MUTEX_INITIALIZER_NP \
  { { 0, 0, 0, 0, PTHREAD_MUTEX_RECURSIVE_NP, 0, { 0, 0 } } }
#  define PTHREAD_ERRORCHECK_MUTEX_INITIALIZER_NP \
  { { 0, 0, 0, 0, PTHREAD_MUTEX_ERRORCHECK_NP, 0, { 0, 0 } } }
#  define PTHREAD_ADAPTIVE_MUTEX_INITIALIZER_NP \
  { { 0, 0, 0, 0, PTHREAD_MUTEX_ADAPTIVE_NP, 0, { 0, 0 } } }
# endif
#else
# define PTHREAD_MUTEX_INITIALIZER \
  { { 0, 0, 0, 0, 0, { 0 } } }
# ifdef __USE_GNU
#  define PTHREAD_RECURSIVE_MUTEX_INITIALIZER_NP \
  { { 0, 0, 0, PTHREAD_MUTEX_RECURSIVE_NP, 0, { 0 } } }
#  define PTHREAD_ERRORCHECK_MUTEX_INITIALIZER_NP \
  { { 0, 0, 0, PTHREAD_MUTEX_ERRORCHECK_NP, 0, { 0 } } }
#  define PTHREAD_ADAPTIVE_MUTEX_INITIALIZER_NP \
  { { 0, 0, 0, PTHREAD_MUTEX_ADAPTIVE_NP, 0, { 0 } } }
# endif
#endif

/* Conditional variable handling.  */
#define PTHREAD_COND_INITIALIZER { { 0, 0, 0, 0, 0, (void *) 0, 0, 0 } }

/* Single execution handling.  */
#define PTHREAD_ONCE_INIT 0

__BEGIN_DECLS

/* Cancel THREAD immediately or at the next possibility.  */
extern int pthread_cancel (pthread_t __th);

/* Create a new thread, starting with execution of START-ROUTINE
   getting passed ARG.  Creation attributed come from ATTR.  The new
   handle is stored in *NEWTHREAD.  */
extern int pthread_create (pthread_t *__restrict __newthread,
			   const pthread_attr_t *__restrict __attr,
			   void *(*__start_routine) (void *),
			   void *__restrict __arg) __THROWNL __nonnull ((1, 3));

/* Terminate calling thread.

   The registered cleanup handlers are called via exception handling
   so we cannot mark this function with __THROW.*/
extern void pthread_exit (void *__retval) __attribute__ ((__noreturn__));

/* Make calling thread wait for termination of the thread TH.  The
   exit status of the thread is stored in *THREAD_RETURN, if THREAD_RETURN
   is not NULL.

   This function is a cancellation point and therefore not marked with
   __THROW.  */
extern int pthread_join (pthread_t __th, void **__thread_return);

/* Indicate that the thread TH is never to be joined with PTHREAD_JOIN.
   The resources of TH will therefore be freed immediately when it
   terminates, instead of waiting for another thread to perform PTHREAD_JOIN
   on it.  */
extern int pthread_detach (pthread_t __th) __THROW;


/* Obtain the identifier of the current thread.  */
extern pthread_t pthread_self (void) __THROW __attribute__ ((__const__));

/* Compare two thread identifiers.  */
extern int pthread_equal (pthread_t __thread1, pthread_t __thread2)
  __THROW __attribute__ ((__const__));

/* Functions for handling initialization.  */

/* Guarantee that the initialization function INIT_ROUTINE will be called
   only once, even if pthread_once is executed several times with the
   same ONCE_CONTROL argument. ONCE_CONTROL must point to a static or
   extern variable initialized to PTHREAD_ONCE_INIT.

   The initialization functions might throw exception which is why
   this function is not marked with __THROW.  */
extern int pthread_once (pthread_once_t *__once_control,
			 void (*__init_routine) (void)) __nonnull ((1, 2));


/* Functions for handling thread-specific data.  */

/* Create a key value identifying a location in the thread-specific
   data area.  Each thread maintains a distinct thread-specific data
   area.  DESTR_FUNCTION, if non-NULL, is called with the value
   associated to that key when the key is destroyed.
   DESTR_FUNCTION is not called if the value associated is NULL when
   the key is destroyed.  */
extern int pthread_key_create (pthread_key_t *__key,
			       void (*__destr_function) (void *))
     __THROW __nonnull ((1));

/* Destroy KEY.  */
extern int pthread_key_delete (pthread_key_t __key) __THROW;

/* Return current value of the thread-specific data slot identified by KEY.  */
extern void *pthread_getspecific (pthread_key_t __key) __THROW;

/* Store POINTER in the thread-specific data slot identified by KEY. */
extern int pthread_setspecific (pthread_key_t __key,
				const void *__pointer) __THROW ;


/* Mutex handling.  */

/* Initialize a mutex.  */
extern int pthread_mutex_init (pthread_mutex_t *__mutex,
			       const pthread_mutexattr_t *__mutexattr)
     __THROW __nonnull ((1));

/* Destroy a mutex.  */
extern int pthread_mutex_destroy (pthread_mutex_t *__mutex)
     __THROW __nonnull ((1));

/* Try locking a mutex.  */
extern int pthread_mutex_trylock (pthread_mutex_t *__mutex)
     __THROWNL __nonnull ((1));

/* Lock a mutex.  */
extern int pthread_mutex_lock (pthread_mutex_t *__mutex)
     __THROWNL __nonnull ((1));

#ifdef __USE_XOPEN2K
/* Wait until lock becomes available, or specified time passes. */
extern int pthread_mutex_timedlock (pthread_mutex_t *__restrict __mutex,
				    const struct timespec *__restrict
				    __abstime) __THROWNL __nonnull ((1, 2));
#endif

/* Unlock a mutex.  */
extern int pthread_mutex_unlock (pthread_mutex_t *__mutex)
     __THROWNL __nonnull ((1));


/* Get the priority ceiling of MUTEX.  */
extern int pthread_mutex_getprioceiling (const pthread_mutex_t *
					 __restrict __mutex,
					 int *__restrict __prioceiling)
     __THROW __nonnull ((1, 2));

/* Set the priority ceiling of MUTEX to PRIOCEILING, return old
   priority ceiling value in *OLD_CEILING.  */
extern int pthread_mutex_setprioceiling (pthread_mutex_t *__restrict __mutex,
					 int __prioceiling,
					 int *__restrict __old_ceiling)
     __THROW __nonnull ((1, 3));


#ifdef __USE_XOPEN2K8
/* Declare the state protected by MUTEX as consistent.  */
extern int pthread_mutex_consistent (pthread_mutex_t *__mutex)
     __THROW __nonnull ((1));
# ifdef __USE_GNU
extern int pthread_mutex_consistent_np (pthread_mutex_t *__mutex)
     __THROW __nonnull ((1));
# endif
#endif

/* Functions for handling mutex attributes.  */

/* Initialize mutex attribute object ATTR with default attributes
   (kind is PTHREAD_MUTEX_TIMED_NP).  */
extern int pthread_mutexattr_init (pthread_mutexattr_t *__attr)
     __THROW __nonnull ((1));

/* Destroy mutex attribute object ATTR.  */
extern int pthread_mutexattr_destroy (pthread_mutexattr_t *__attr)
     __THROW __nonnull ((1));

/* Get the process-shared flag of the mutex attribute ATTR.  */
extern int pthread_mutexattr_getpshared (const pthread_mutexattr_t *
					 __restrict __attr,
					 int *__restrict __pshared)
     __THROW __nonnull ((1, 2));

/* Set the process-shared flag of the mutex attribute ATTR.  */
extern int pthread_mutexattr_setpshared (pthread_mutexattr_t *__attr,
					 int __pshared)
     __THROW __nonnull ((1));

#if defined __USE_UNIX98 || defined __USE_XOPEN2K8
/* Return in *KIND the mutex kind attribute in *ATTR.  */
extern int pthread_mutexattr_gettype (const pthread_mutexattr_t *__restrict
				      __attr, int *__restrict __kind)
     __THROW __nonnull ((1, 2));

/* Set the mutex kind attribute in *ATTR to KIND (either PTHREAD_MUTEX_NORMAL,
   PTHREAD_MUTEX_RECURSIVE, PTHREAD_MUTEX_ERRORCHECK, or
   PTHREAD_MUTEX_DEFAULT).  */
extern int pthread_mutexattr_settype (pthread_mutexattr_t *__attr, int __kind)
     __THROW __nonnull ((1));
#endif

/* Return in *PROTOCOL the mutex protocol attribute in *ATTR.  */
extern int pthread_mutexattr_getprotocol (const pthread_mutexattr_t *
					  __restrict __attr,
					  int *__restrict __protocol)
     __THROW __nonnull ((1, 2));

/* Set the mutex protocol attribute in *ATTR to PROTOCOL (either
   PTHREAD_PRIO_NONE, PTHREAD_PRIO_INHERIT, or PTHREAD_PRIO_PROTECT).  */
extern int pthread_mutexattr_setprotocol (pthread_mutexattr_t *__attr,
					  int __protocol)
     __THROW __nonnull ((1));

/* Return in *PRIOCEILING the mutex prioceiling attribute in *ATTR.  */
extern int pthread_mutexattr_getprioceiling (const pthread_mutexattr_t *
					     __restrict __attr,
					     int *__restrict __prioceiling)
     __THROW __nonnull ((1, 2));

/* Set the mutex prioceiling attribute in *ATTR to PRIOCEILING.  */
extern int pthread_mutexattr_setprioceiling (pthread_mutexattr_t *__attr,
					     int __prioceiling)
     __THROW __nonnull ((1));

#ifdef __USE_XOPEN2K
/* Get the robustness flag of the mutex attribute ATTR.  */
extern int pthread_mutexattr_getrobust (const pthread_mutexattr_t *__attr,
					int *__robustness)
     __THROW __nonnull ((1, 2));
# ifdef __USE_GNU
extern int pthread_mutexattr_getrobust_np (const pthread_mutexattr_t *__attr,
					   int *__robustness)
     __THROW __nonnull ((1, 2));
# endif

/* Set the robustness flag of the mutex attribute ATTR.  */
extern int pthread_mutexattr_setrobust (pthread_mutexattr_t *__attr,
					int __robustness)
     __THROW __nonnull ((1));
# ifdef __USE_GNU
extern int pthread_mutexattr_setrobust_np (pthread_mutexattr_t *__attr,
					   int __robustness)
     __THROW __nonnull ((1));
# endif
# endif

/* Functions for handling conditional variables.  */

/* Initialize condition variable COND using attributes ATTR, or use
   the default values if later is NULL.  */
extern int pthread_cond_init (pthread_cond_t *__restrict __cond,
			      const pthread_condattr_t *__restrict __cond_attr)
     __THROW __nonnull ((1));

/* Destroy condition variable COND.  */
extern int pthread_cond_destroy (pthread_cond_t *__cond)
     __THROW __nonnull ((1));

/* Wake up one thread waiting for condition variable COND.  */
extern int pthread_cond_signal (pthread_cond_t *__cond)
     __THROWNL __nonnull ((1));

/* Wake up all threads waiting for condition variables COND.  */
extern int pthread_cond_broadcast (pthread_cond_t *__cond)
     __THROWNL __nonnull ((1));

/* Wait for condition variable COND to be signaled or broadcast.
   MUTEX is assumed to be locked before.

   This function is a cancellation point and therefore not marked with
   __THROW.  */
extern int pthread_cond_wait (pthread_cond_t *__restrict __cond,
			      pthread_mutex_t *__restrict __mutex)
     __nonnull ((1, 2));

/* Wait for condition variable COND to be signaled or broadcast until
   ABSTIME.  MUTEX is assumed to be locked before.  ABSTIME is an
   absolute time specification; zero is the beginning of the epoch
   (00:00:00 GMT, January 1, 1970).

   This function is a cancellation point and therefore not marked with
   __THROW.  */
extern int pthread_cond_timedwait (pthread_cond_t *__restrict __cond,
				   pthread_mutex_t *__restrict __mutex,
				   const struct timespec *__restrict __abstime)
     __nonnull ((1, 2, 3));

/* Functions for handling condition variable attributes.  */

/* Initialize condition variable attribute ATTR.  */
extern int pthread_condattr_init (pthread_condattr_t *__attr)
     __THROW __nonnull ((1));

/* Destroy condition variable attribute ATTR.  */
extern int pthread_condattr_destroy (pthread_condattr_t *__attr)
     __THROW __nonnull ((1));

/* Get the process-shared flag of the condition variable attribute ATTR.  */
extern int pthread_condattr_getpshared (const pthread_condattr_t *
					__restrict __attr,
					int *__restrict __pshared)
     __THROW __nonnull ((1, 2));

/* Set the process-shared flag of the condition variable attribute ATTR.  */
extern int pthread_condattr_setpshared (pthread_condattr_t *__attr,
					int __pshared) __THROW __nonnull ((1));

#ifdef __USE_XOPEN2K
/* Get the clock selected for the conditon variable attribute ATTR.  */
extern int pthread_condattr_getclock (const pthread_condattr_t *
				      __restrict __attr,
				      __clockid_t *__restrict __clock_id)
     __THROW __nonnull ((1, 2));

/* Set the clock selected for the conditon variable attribute ATTR.  */
extern int pthread_condattr_setclock (pthread_condattr_t *__attr,
				      __clockid_t __clock_id)
     __THROW __nonnull ((1));
#endif
     
__END_DECLS

#endif	//  _PTHREAD_H

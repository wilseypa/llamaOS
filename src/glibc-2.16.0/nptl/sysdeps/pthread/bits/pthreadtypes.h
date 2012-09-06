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

#ifndef _PTHREADTYPES_H
#define _PTHREADTYPES_H	1

#include <bits/wordsize.h>

#ifdef __x86_64__
# if __WORDSIZE == 64
#  define __SIZEOF_PTHREAD_ATTR_T 56
#  define __SIZEOF_PTHREAD_MUTEX_T 40
#  define __SIZEOF_PTHREAD_MUTEXATTR_T 4
#  define __SIZEOF_PTHREAD_COND_T 48
#  define __SIZEOF_PTHREAD_CONDATTR_T 4
#  define __SIZEOF_PTHREAD_RWLOCK_T 56
#  define __SIZEOF_PTHREAD_RWLOCKATTR_T 8
#  define __SIZEOF_PTHREAD_BARRIER_T 32
#  define __SIZEOF_PTHREAD_BARRIERATTR_T 4
# else
#  define __SIZEOF_PTHREAD_ATTR_T 32
#  define __SIZEOF_PTHREAD_MUTEX_T 32
#  define __SIZEOF_PTHREAD_MUTEXATTR_T 4
#  define __SIZEOF_PTHREAD_COND_T 48
#  define __SIZEOF_PTHREAD_CONDATTR_T 4
#  define __SIZEOF_PTHREAD_RWLOCK_T 44
#  define __SIZEOF_PTHREAD_RWLOCKATTR_T 8
#  define __SIZEOF_PTHREAD_BARRIER_T 20
#  define __SIZEOF_PTHREAD_BARRIERATTR_T 4
# endif
#else
# define __SIZEOF_PTHREAD_ATTR_T 36
# define __SIZEOF_PTHREAD_MUTEX_T 24
# define __SIZEOF_PTHREAD_MUTEXATTR_T 4
# define __SIZEOF_PTHREAD_COND_T 48
# define __SIZEOF_PTHREAD_CONDATTR_T 4
# define __SIZEOF_PTHREAD_RWLOCK_T 32
# define __SIZEOF_PTHREAD_RWLOCKATTR_T 8
# define __SIZEOF_PTHREAD_BARRIER_T 20
# define __SIZEOF_PTHREAD_BARRIERATTR_T 4
#endif

/* Thread identifiers.  The structure of the attribute type is not
   exposed on purpose.  */
typedef unsigned long int pthread_t;

union pthread_attr_t
{
  char __size[__SIZEOF_PTHREAD_ATTR_T];
  long int __align;
};
#ifndef __have_pthread_attr_t
typedef union pthread_attr_t pthread_attr_t;
# define __have_pthread_attr_t	1
#endif

#ifdef __x86_64__
typedef struct __pthread_internal_list
{
  struct __pthread_internal_list *__prev;
  struct __pthread_internal_list *__next;
} __pthread_list_t;
#else
typedef struct __pthread_internal_slist
{
  struct __pthread_internal_slist *__next;
} __pthread_slist_t;
#endif

/* Data structures for mutex handling.  The structure of the attribute
   type is not exposed on purpose.  */
typedef union
{
  struct __pthread_mutex_s
  {
    int __lock;
    unsigned int __count;
    int __owner;
#ifdef __x86_64__
    unsigned int __nusers;
#endif
    /* KIND must stay at this position in the structure to maintain
       binary compatibility.  */
    int __kind;
#ifdef __x86_64__
    int __spins;
    __pthread_list_t __list;
# define __PTHREAD_MUTEX_HAVE_PREV	1
#else
    unsigned int __nusers;
    __extension__ union
    {
      int __spins;
      __pthread_slist_t __list;
    };
#endif
  } __data;
  char __size[__SIZEOF_PTHREAD_MUTEX_T];
  long int __align;
} pthread_mutex_t;

typedef union
{
  char __size[__SIZEOF_PTHREAD_MUTEXATTR_T];
  int __align;
} pthread_mutexattr_t;

/* Data structure for conditional variable handling.  The structure of
   the attribute type is not exposed on purpose.  */
typedef union
{
  struct
  {
    int __lock;
    unsigned int __futex;
    __extension__ unsigned long long int __total_seq;
    __extension__ unsigned long long int __wakeup_seq;
    __extension__ unsigned long long int __woken_seq;
    void *__mutex;
    unsigned int __nwaiters;
    unsigned int __broadcast_seq;
  } __data;
  char __size[__SIZEOF_PTHREAD_COND_T];
  __extension__ long long int __align;
} pthread_cond_t;

typedef union
{
  char __size[__SIZEOF_PTHREAD_CONDATTR_T];
  int __align;
} pthread_condattr_t;

/* Keys for thread-specific data */
typedef unsigned int pthread_key_t;


/* Once-only execution */
typedef int pthread_once_t;

//#if defined __USE_UNIX98 || defined __USE_XOPEN2K
/* Data structure for read-write lock variable handling.  The
   structure of the attribute type is not exposed on purpose.  */
typedef union
{
# ifdef __x86_64__
  struct
  {
    int __lock;
    unsigned int __nr_readers;
    unsigned int __readers_wakeup;
    unsigned int __writer_wakeup;
    unsigned int __nr_readers_queued;
    unsigned int __nr_writers_queued;
    int __writer;
    int __shared;
    unsigned long int __pad1;
    unsigned long int __pad2;
    /* FLAGS must stay at this position in the structure to maintain
       binary compatibility.  */
    unsigned int __flags;
# define __PTHREAD_RWLOCK_INT_FLAGS_SHARED	1
  } __data;
# else
  struct
  {
    int __lock;
    unsigned int __nr_readers;
    unsigned int __readers_wakeup;
    unsigned int __writer_wakeup;
    unsigned int __nr_readers_queued;
    unsigned int __nr_writers_queued;
    /* FLAGS must stay at this position in the structure to maintain
       binary compatibility.  */
    unsigned char __flags;
    unsigned char __shared;
    unsigned char __pad1;
    unsigned char __pad2;
    int __writer;
  } __data;
# endif
  char __size[__SIZEOF_PTHREAD_RWLOCK_T];
  long int __align;
} pthread_rwlock_t;

typedef union
{
  char __size[__SIZEOF_PTHREAD_RWLOCKATTR_T];
  long int __align;
} pthread_rwlockattr_t;
//#endif

#endif	// _PTHREADTYPES_H

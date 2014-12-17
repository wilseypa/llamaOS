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

#ifndef glibc_sysdeps_llamaos_bits_sigset_h
#define glibc_sysdeps_llamaos_bits_sigset_h

// #include_next <bits/sigset.h>
/* __sig_atomic_t, __sigset_t, and related definitions.  Generic/BSD version.
   Copyright (C) 1991, 1992, 1994, 1996, 1997, 2007, 2012
   Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <http://www.gnu.org/licenses/>.  */

#ifndef	_SIGSET_H_types
#define	_SIGSET_H_types	1

typedef int __sig_atomic_t;

/* A `sigset_t' has a bit for each signal.  */
typedef unsigned long int __sigset_t;

#endif


/* We only want to define these functions if <signal.h> was actually
   included; otherwise we were included just to define the types.  Since we
   are namespace-clean, it wouldn't hurt to define extra macros.  But
   trouble can be caused by functions being defined (e.g., any global
   register vars declared later will cause compilation errors).  */

#if !defined _SIGSET_H_fns && defined _SIGNAL_H
#define _SIGSET_H_fns 1

#ifndef _EXTERN_INLINE
# define _EXTERN_INLINE __extern_inline
#endif

/* Return a mask that includes SIG only.  The cast to `sigset_t' avoids
   overflow if `sigset_t' is wider than `int'.  */
#define	__sigmask(sig)	(((__sigset_t) 1) << ((sig) - 1))

#define	__sigemptyset(set)	((*(set) = (__sigset_t) 0), 0)
#define	__sigfillset(set)	((*(set) = ~(__sigset_t) 0), 0)

#ifdef _GNU_SOURCE
# define __sigisemptyset(set)	(*(set) == (__sigset_t) 0)
# define __sigandset(dest, left, right) \
				((*(dest) = (*(left) & *(right))), 0)
# define __sigorset(dest, left, right) \
				((*(dest) = (*(left) | *(right))), 0)
#endif

/* These functions needn't check for a bogus signal number -- error
   checking is done in the non __ versions.  */

extern int __sigismember (const __sigset_t *, int);
extern int __sigaddset (__sigset_t *, int);
extern int __sigdelset (__sigset_t *, int);

#ifdef __USE_EXTERN_INLINES
# define __SIGSETFN(NAME, BODY, CONST)					      \
  _EXTERN_INLINE int							      \
  NAME (CONST __sigset_t *__set, int __sig)				      \
  {									      \
    __sigset_t __mask = __sigmask (__sig);				      \
    return BODY;							      \
  }

__SIGSETFN (__sigismember, (*__set & __mask) ? 1 : 0, const)
__SIGSETFN (__sigaddset, ((*__set |= __mask), 0), )
__SIGSETFN (__sigdelset, ((*__set &= ~__mask), 0), )

# undef __SIGSETFN
#endif


#endif /* ! _SIGSET_H_fns.  */





// !BAM this is weird
#ifndef __sigfillset
#define	__sigfillset(set)	((*(set) = ~(__sigset_t) 0), 0)
#endif

extern int __sigaddset (__sigset_t *, int);

#endif	// glibc_sysdeps_llamaos_bits_sigset_h


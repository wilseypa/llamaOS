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

#ifndef glibc_sysdeps_llamaos_x86_bits_environments_h
#define glibc_sysdeps_llamaos_x86_bits_environments_h

// #include_next <bits/environments.h>
// bits/envirnments.h

/* Copyright (C) 1999, 2001, 2004, 2009 Free Software Foundation, Inc.
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

#ifndef _UNISTD_H
# error "Never include this file directly.  Use <unistd.h> instead"
#endif

#include <bits/wordsize.h>

/* This header should define the following symbols under the described
   situations.  A value `1' means that the model is always supported,
   `-1' means it is never supported.  Undefined means it cannot be
   statically decided.

   _POSIX_V7_ILP32_OFF32   32bit int, long, pointers, and off_t type
   _POSIX_V7_ILP32_OFFBIG  32bit int, long, and pointers and larger off_t type

   _POSIX_V7_LP64_OFF32	   64bit long and pointers and 32bit off_t type
   _POSIX_V7_LPBIG_OFFBIG  64bit long and pointers and large off_t type

   The macros _POSIX_V6_ILP32_OFF32, _POSIX_V6_ILP32_OFFBIG,
   _POSIX_V6_LP64_OFF32, _POSIX_V6_LPBIG_OFFBIG, _XBS5_ILP32_OFF32,
   _XBS5_ILP32_OFFBIG, _XBS5_LP64_OFF32, and _XBS5_LPBIG_OFFBIG were
   used in previous versions of the Unix standard and are available
   only for compatibility.
*/

#if __WORDSIZE == 64

/* We can never provide environments with 32-bit wide pointers.  */
# define _POSIX_V7_ILP32_OFF32	-1
# define _POSIX_V7_ILP32_OFFBIG	-1
# define _POSIX_V6_ILP32_OFF32	-1
# define _POSIX_V6_ILP32_OFFBIG	-1
# define _XBS5_ILP32_OFF32	-1
# define _XBS5_ILP32_OFFBIG	-1
/* We also have no use (for now) for an environment with bigger pointers
   and offsets.  */
# define _POSIX_V7_LPBIG_OFFBIG	-1
# define _POSIX_V6_LPBIG_OFFBIG	-1
# define _XBS5_LPBIG_OFFBIG	-1

/* By default we have 64-bit wide `long int', pointers and `off_t'.  */
# define _POSIX_V7_LP64_OFF64	1
# define _POSIX_V6_LP64_OFF64	1
# define _XBS5_LP64_OFF64	1

#else /* __WORDSIZE == 32 */

/* By default we have 32-bit wide `int', `long int', pointers and `off_t'
   and all platforms support LFS.  */
# define _POSIX_V7_ILP32_OFF32	1
# define _POSIX_V7_ILP32_OFFBIG	1
# define _POSIX_V6_ILP32_OFF32	1
# define _POSIX_V6_ILP32_OFFBIG	1
# define _XBS5_ILP32_OFF32	1
# define _XBS5_ILP32_OFFBIG	1

/* We optionally provide an environment with the above size but an 64-bit
   side `off_t'.  Therefore we don't define _POSIX_V7_ILP32_OFFBIG.  */

/* We can never provide environments with 64-bit wide pointers.  */
# define _POSIX_V7_LP64_OFF64	-1
# define _POSIX_V7_LPBIG_OFFBIG	-1
# define _POSIX_V6_LP64_OFF64	-1
# define _POSIX_V6_LPBIG_OFFBIG	-1
# define _XBS5_LP64_OFF64	-1
# define _XBS5_LPBIG_OFFBIG	-1

/* CFLAGS.  */
#define __ILP32_OFFBIG_CFLAGS   "-D_LARGEFILE_SOURCE -D_FILE_OFFSET_BITS=64"

#endif /* __WORDSIZE == 32 */

#endif	// glibc_sysdeps_llamaos_x86_bits_environments_h


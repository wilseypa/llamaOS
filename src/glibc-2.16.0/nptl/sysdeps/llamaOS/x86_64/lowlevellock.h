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

#ifndef glibc_nptl_sysdeps_llamaos_x86_64_lowlevellock_h_
#define glibc_nptl_sysdeps_llamaos_x86_64_lowlevellock_h_

// glibc-2.16.0/nptl/sysdeps/unix/sysv/linux/x86_64/lowlevellock.h

/* Copyright (C) 2002-2012 Free Software Foundation, Inc.
   This file is part of the GNU C Library.
   Contributed by Ulrich Drepper <drepper@redhat.com>, 2002.

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


#define SYS_futex		__NR_futex
#define FUTEX_WAIT		0
#define FUTEX_WAKE		1
#define FUTEX_CMP_REQUEUE	4
#define FUTEX_WAKE_OP		5
#define FUTEX_LOCK_PI		6
#define FUTEX_UNLOCK_PI		7
#define FUTEX_TRYLOCK_PI	8
#define FUTEX_WAIT_BITSET	9
#define FUTEX_WAKE_BITSET	10
#define FUTEX_WAIT_REQUEUE_PI	11
#define FUTEX_CMP_REQUEUE_PI	12
#define FUTEX_PRIVATE_FLAG	128
#define FUTEX_CLOCK_REALTIME	256

#define FUTEX_BITSET_MATCH_ANY	0xffffffff

#define FUTEX_OP_CLEAR_WAKE_IF_GT_ONE	((4 << 24) | 1)

/* Values for 'private' parameter of locking macros.  Yes, the
   definition seems to be backwards.  But it is not.  The bit will be
   reversed before passing to the system call.  */
#define LLL_PRIVATE	0
#define LLL_SHARED	FUTEX_PRIVATE_FLAG

#endif	// glibc_nptl_sysdeps_llamaos_x86_64_lowlevellock_h_

/*
Copyright (c) 2011, William Magato
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

#include <errno.h>

void __lll_lock_wait_private (int *futex)
{
   __set_errno (ENOSYS);
}

int __lll_unlock_wake_private (int *futex)
{
   __set_errno (ENOSYS);

   return -1;
}

#if 0
/* low level locking for pthread library.  Generic futex-using version.
   Copyright (C) 2003, 2007 Free Software Foundation, Inc.
   This file is part of the GNU C Library.
   Contributed by Paul Mackerras <paulus@au.ibm.com>, 2003.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	 See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <http://www.gnu.org/licenses/>.  */

#include <errno.h>
#include <sysdep.h>
#include <lowlevellock.h>
#include <sys/time.h>


void
__lll_lock_wait_private (int *futex)
{
  if (*futex == 2)
    lll_futex_wait (futex, 2, LLL_PRIVATE);

  while (atomic_exchange_acq (futex, 2) != 0)
    lll_futex_wait (futex, 2, LLL_PRIVATE);
}


/* These functions don't get included in libc.so  */
#ifdef IS_IN_libpthread
void
__lll_lock_wait (int *futex, int private)
{
  if (*futex == 2)
    lll_futex_wait (futex, 2, private);

  while (atomic_exchange_acq (futex, 2) != 0)
    lll_futex_wait (futex, 2, private);
}


int
__lll_timedlock_wait (int *futex, const struct timespec *abstime, int private)
{
  /* Reject invalid timeouts.  */
  if (abstime->tv_nsec < 0 || abstime->tv_nsec >= 1000000000)
    return EINVAL;

  /* Try locking.  */
  while (atomic_exchange_acq (futex, 2) != 0)
    {
      struct timeval tv;

      /* Get the current time.  */
      (void) __gettimeofday (&tv, NULL);

      /* Compute relative timeout.  */
      struct timespec rt;
      rt.tv_sec = abstime->tv_sec - tv.tv_sec;
      rt.tv_nsec = abstime->tv_nsec - tv.tv_usec * 1000;
      if (rt.tv_nsec < 0)
	{
	  rt.tv_nsec += 1000000000;
	  --rt.tv_sec;
	}

      if (rt.tv_sec < 0)
	return ETIMEDOUT;

      /* Wait.  */
      lll_futex_timed_wait (futex, 2, &rt, private);
    }

  return 0;
}


int
__lll_timedwait_tid (int *tidp, const struct timespec *abstime)
{
  int tid;

  if (abstime->tv_nsec < 0 || abstime->tv_nsec >= 1000000000)
    return EINVAL;

  /* Repeat until thread terminated.  */
  while ((tid = *tidp) != 0)
    {
      struct timeval tv;
      struct timespec rt;

      /* Get the current time.  */
      (void) __gettimeofday (&tv, NULL);

      /* Compute relative timeout.  */
      rt.tv_sec = abstime->tv_sec - tv.tv_sec;
      rt.tv_nsec = abstime->tv_nsec - tv.tv_usec * 1000;
      if (rt.tv_nsec < 0)
	{
	  rt.tv_nsec += 1000000000;
	  --rt.tv_sec;
	}

      /* Already timed out?  */
      if (rt.tv_sec < 0)
	return ETIMEDOUT;

      /* Wait until thread terminates.  The kernel so far does not use
	 the private futex operations for this.  */
      if (lll_futex_timed_wait (tidp, tid, &rt, LLL_SHARED) == -ETIMEDOUT)
	return ETIMEDOUT;
    }

  return 0;
}
#endif
#endif
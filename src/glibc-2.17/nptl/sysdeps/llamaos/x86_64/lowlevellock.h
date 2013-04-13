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

#ifndef glibc_nptl_sysdeps_llamaos_x86_64_lowlevellock_h
#define glibc_nptl_sysdeps_llamaos_x86_64_lowlevellock_h

#include <bits/atomic.h>

#define FUTEX_PRIVATE_FLAG        128

#define LLL_SHARED        FUTEX_PRIVATE_FLAG
#define LLL_PRIVATE    0

/* Initializer for lock.  */
#define LLL_LOCK_INITIALIZER		(0)
#define LLL_LOCK_INITIALIZER_LOCKED	(1)
#define LLL_LOCK_INITIALIZER_WAITERS	(2)

#define lll_futex_wait(futex, val, private) \
  lll_futex_timed_wait(futex, val, NULL, private)


#define lll_futex_timed_wait(futex, val, timeout, private) \
  do {									      \
  } while (0)
//  ({									      \
    register const struct timespec *__to __asm ("r10") = timeout;	      \
    int __status;							      \
    register __typeof (val) _val __asm ("edx") = (val);			      \
    __asm __volatile ("syscall"						      \
		      : "=a" (__status)					      \
		      : "0" (SYS_futex), "D" (futex),			      \
			"S" (__lll_private_flag (FUTEX_WAIT, private)),	      \
			"d" (_val), "r" (__to)				      \
		      : "memory", "cc", "r11", "cx");			      \
    __status;								      \
  })

#define lll_futex_wake(futex, nr, private) \
  do {									      \
  } while (0)
//    int __ignore;							      \
    register __typeof (nr) _nr __asm ("edx") = (nr);			      \
    LIBC_PROBE (lll_futex_wake, 3, futex, nr, private);                       \
    __asm __volatile ("syscall"						      \
		      : "=a" (__ignore)					      \
		      : "0" (SYS_futex), "D" (futex),			      \
			"S" (__lll_private_flag (FUTEX_WAKE, private)),	      \
			"d" (_nr)					      \
		      : "memory", "cc", "r10", "r11", "cx");		      \
  } while (0)

#define lll_trylock(futex) 0
//  ({ int ret;								      \
     __asm __volatile (__lll_trylock_asm				      \
		       : "=a" (ret), "=m" (futex)			      \
		       : "r" (LLL_LOCK_INITIALIZER_LOCKED), "m" (futex),      \
			 "0" (LLL_LOCK_INITIALIZER)			      \
		       : "memory");					      \
     ret; })

  #define lll_lock(futex, private) \
  (void)								      \
    ({									      \
    })
//    ({ int ignore1, ignore2, ignore3;					      \
       if (__builtin_constant_p (private) && (private) == LLL_PRIVATE)	      \
	 __asm __volatile (__lll_lock_asm_start				      \
			   ".subsection 1\n\t"				      \
			   ".type _L_lock_%=, @function\n"		      \
			   "_L_lock_%=:\n"				      \
			   "1:\tlea %2, %%" RDI_LP "\n"			      \
			   "2:\tsub $128, %%" RSP_LP "\n"		      \
			   "3:\tcallq __lll_lock_wait_private\n"	      \
			   "4:\tadd $128, %%" RSP_LP "\n"		      \
			   "5:\tjmp 24f\n"				      \
			   "6:\t.size _L_lock_%=, 6b-1b\n\t"		      \
			   ".previous\n"				      \
			   LLL_STUB_UNWIND_INFO_5			      \
			   "24:"					      \
			   : "=S" (ignore1), "=&D" (ignore2), "=m" (futex),   \
			     "=a" (ignore3)				      \
			   : "0" (1), "m" (futex), "3" (0)		      \
			   : "cx", "r11", "cc", "memory");		      \
       else								      \
	 __asm __volatile (__lll_lock_asm_start				      \
			   ".subsection 1\n\t"				      \
			   ".type _L_lock_%=, @function\n"		      \
			   "_L_lock_%=:\n"				      \
			   "1:\tlea %2, %%" RDI_LP "\n"			      \
			   "2:\tsub $128, %%" RSP_LP "\n"		      \
			   "3:\tcallq __lll_lock_wait\n"		      \
			   "4:\tadd $128, %%" RSP_LP "\n"		      \
			   "5:\tjmp 24f\n"				      \
			   "6:\t.size _L_lock_%=, 6b-1b\n\t"		      \
			   ".previous\n"				      \
			   LLL_STUB_UNWIND_INFO_5			      \
			   "24:"					      \
			   : "=S" (ignore1), "=D" (ignore2), "=m" (futex),    \
			     "=a" (ignore3)				      \
			   : "1" (1), "m" (futex), "3" (0), "0" (private)     \
			   : "cx", "r11", "cc", "memory");		      \
    })									      \

#define lll_unlock(futex, private) \
  (void)								      \
    ({									      \
    })
//    ({ int ignore;							      \
       if (__builtin_constant_p (private) && (private) == LLL_PRIVATE)	      \
	 __asm __volatile (__lll_unlock_asm_start			      \
			   ".subsection 1\n\t"				      \
			   ".type _L_unlock_%=, @function\n"		      \
			   "_L_unlock_%=:\n"				      \
			   "1:\tlea %0, %%" RDI_LP "\n"			      \
			   "2:\tsub $128, %%" RSP_LP "\n"		      \
			   "3:\tcallq __lll_unlock_wake_private\n"	      \
			   "4:\tadd $128, %%" RSP_LP "\n"		      \
			   "5:\tjmp 24f\n"				      \
			   "6:\t.size _L_unlock_%=, 6b-1b\n\t"		      \
			   ".previous\n"				      \
			   LLL_STUB_UNWIND_INFO_5			      \
			   "24:"					      \
			   : "=m" (futex), "=&D" (ignore)		      \
			   : "m" (futex)				      \
			   : "ax", "cx", "r11", "cc", "memory");	      \
       else								      \
	 __asm __volatile (__lll_unlock_asm_start			      \
			   ".subsection 1\n\t"				      \
			   ".type _L_unlock_%=, @function\n"		      \
			   "_L_unlock_%=:\n"				      \
			   "1:\tlea %0, %%" RDI_LP "\n"			      \
			   "2:\tsub $128, %%" RSP_LP "\n"		      \
			   "3:\tcallq __lll_unlock_wake\n"		      \
			   "4:\tadd $128, %%" RSP_LP "\n"		      \
			   "5:\tjmp 24f\n"				      \
			   "6:\t.size _L_unlock_%=, 6b-1b\n\t"		      \
			   ".previous\n"				      \
			   LLL_STUB_UNWIND_INFO_5			      \
			   "24:"					      \
			   : "=m" (futex), "=&D" (ignore)		      \
			   : "m" (futex), "S" (private)			      \
			   : "ax", "cx", "r11", "cc", "memory");	      \
    })

// #include_next <lowlevellock.h>

#endif	// glibc_nptl_sysdeps_llamaos_x86_64_lowlevellock_h


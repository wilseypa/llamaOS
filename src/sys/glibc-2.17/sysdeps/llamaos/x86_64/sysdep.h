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

#ifndef glibc_sysdeps_llamaos_x86_64_sysdep_h
#define glibc_sysdeps_llamaos_x86_64_sysdep_h

// !BAM where to get this?
#define __NR_arch_prctl 0

#include <bp-sym.h>

# define INTERNAL_SYSCALL_DECL(err) do { } while (0)
# undef INTERNAL_SYSCALL
# define INTERNAL_SYSCALL(name, err, nr, args...) (0)

# undef INTERNAL_SYSCALL_DECL
# define INTERNAL_SYSCALL_DECL(err) do { } while (0)

# define INTERNAL_SYSCALL_NCS(name, err, nr, args...) (0)
//  ({                                                                          \
    unsigned long int resultvar;                                              \
    LOAD_ARGS_##nr (args)                                                     \
    LOAD_REGS_##nr                                                            \
    asm volatile (                                                            \
    "syscall\n\t"                                                             \
    : "=a" (resultvar)                                                        \
    : "0" (name) ASM_ARGS_##nr : "memory", "cc", "r11", "cx");                \
    (long int) resultvar; })
# undef INTERNAL_SYSCALL
# define INTERNAL_SYSCALL(name, err, nr, args...) \
  INTERNAL_SYSCALL_NCS (__NR_##name, err, nr, ##args)

# define INTERNAL_SYSCALL_NCS_TYPES(name, err, nr, args...) (0)
//  ({                                                                          \
    unsigned long int resultvar;                                              \
    LOAD_ARGS_TYPES_##nr (args)                                               \
    LOAD_REGS_TYPES_##nr (args)                                               \
    asm volatile (                                                            \
    "syscall\n\t"                                                             \
    : "=a" (resultvar)                                                        \
    : "0" (name) ASM_ARGS_##nr : "memory", "cc", "r11", "cx");                \
    (long int) resultvar; })
# undef INTERNAL_SYSCALL_TYPES
# define INTERNAL_SYSCALL_TYPES(name, err, nr, args...) \
  INTERNAL_SYSCALL_NCS_TYPES (__NR_##name, err, nr, ##args)

# undef INTERNAL_SYSCALL_ERROR_P
# define INTERNAL_SYSCALL_ERROR_P(val, err) \
  ((unsigned long int) (long int) (val) >= -4095L)

  # undef INTERNAL_SYSCALL_ERRNO
# define INTERNAL_SYSCALL_ERRNO(val, err)       (-(val))

/* Define a macro which expands inline into the wrapper code for a system
   call.  */
# undef INLINE_SYSCALL
# define INLINE_SYSCALL(name, nr, args...) \
  ({                                                                          \
    unsigned long int resultvar = INTERNAL_SYSCALL (name, , nr, args);        \
    if (__builtin_expect (INTERNAL_SYSCALL_ERROR_P (resultvar, ), 0))         \
      {                                                                       \
        __set_errno (INTERNAL_SYSCALL_ERRNO (resultvar, ));                   \
        resultvar = (unsigned long int) -1;                                   \
      }                                                                       \
    (long int) resultvar; })

#include_next <sysdep.h>

#endif	// glibc_sysdeps_llamaos_x86_64_sysdep_h


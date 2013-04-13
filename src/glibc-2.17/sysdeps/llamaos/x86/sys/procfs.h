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

#ifndef glibc_sysdeps_llamaos_x86_sys_procfs_h
#define glibc_sysdeps_llamaos_x86_sys_procfs_h

#include <features.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/user.h>

/* Type for a general-purpose register.  */
#ifdef __x86_64__
typedef unsigned long long elf_greg_t;
#else
typedef unsigned long elf_greg_t;
#endif

/* And the whole bunch of them.  We could have used `struct
   user_regs_struct' directly in the typedef, but tradition says that
   the register set is an array, which does have some peculiar
   semantics, so leave it that way.  */
#define ELF_NGREG (sizeof (struct user_regs_struct) / sizeof(elf_greg_t))
typedef elf_greg_t elf_gregset_t[ELF_NGREG];

#ifndef __x86_64__
/* Register set for the floating-point registers.  */
typedef struct user_fpregs_struct elf_fpregset_t;

/* Register set for the extended floating-point registers.  Includes
   the Pentium III SSE registers in addition to the classic
   floating-point stuff.  */
typedef struct user_fpxregs_struct elf_fpxregset_t;
#else
/* Register set for the extended floating-point registers.  Includes
   the Pentium III SSE registers in addition to the classic
   floating-point stuff.  */
typedef struct user_fpregs_struct elf_fpregset_t;
#endif

typedef void *psaddr_t;
typedef __pid_t lwpid_t;
typedef elf_gregset_t prgregset_t;
typedef elf_fpregset_t prfpregset_t;

#include_next <sys/procfs.h>

#endif	// glibc_sysdeps_llamaos_x86_sys_procfs_h


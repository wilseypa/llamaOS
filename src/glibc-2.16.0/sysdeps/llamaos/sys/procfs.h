
#ifndef llamaos_sys_procfs_h
#define llamaos_sys_procfs_h

// portions taken from: file:///usr/src/glibc-2.16.0/sysdeps/unix/sysv/linux/x86/sys/procfs.h

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



/* Addresses.  */
typedef void *psaddr_t;

/* Register sets.  Linux has different names.  */
typedef elf_gregset_t prgregset_t;
typedef elf_fpregset_t prfpregset_t;

/* We don't have any differences between processes and threads,
   therefore have only one PID type.  */
typedef __pid_t lwpid_t;

#endif	// llamaos_sys_procfs_h


#ifndef llamaos_x86_64_sysdep_h
#define llamaos_x86_64_sysdep_h

#include_next <sysdep.h>

/* Define a macro with explicit types for arguments, which expands inline
   into the wrapper code for a system call.  It should be used when size
   of any argument > size of long int.  */
# undef INLINE_SYSCALL_TYPES
# define INLINE_SYSCALL_TYPES(name, nr, args...) \
  ({									      \
    unsigned long int resultvar = INTERNAL_SYSCALL_TYPES (name, , nr, args);  \
    if (__builtin_expect (INTERNAL_SYSCALL_ERROR_P (resultvar, ), 0))	      \
      {									      \
	__set_errno (INTERNAL_SYSCALL_ERRNO (resultvar, ));		      \
	resultvar = (unsigned long int) -1;				      \
      }									      \
    (long int) resultvar; })

# undef INTERNAL_SYSCALL_DECL
# define INTERNAL_SYSCALL_DECL(err) do { } while (0)

# define INTERNAL_SYSCALL_NCS(name, err, nr, args...) \
  ({									      \
    unsigned long int resultvar;					      \
    LOAD_ARGS_##nr (args)						      \
    LOAD_REGS_##nr							      \
    asm volatile (							      \
    "syscall\n\t"							      \
    : "=a" (resultvar)							      \
    : "0" (name) ASM_ARGS_##nr : "memory", "cc", "r11", "cx");		      \
    (long int) resultvar; })
# undef INTERNAL_SYSCALL
# define INTERNAL_SYSCALL(name, err, nr, args...) \
  INTERNAL_SYSCALL_NCS (__NR_##name, err, nr, ##args)

# define INTERNAL_SYSCALL_NCS_TYPES(name, err, nr, args...) \
  ({									      \
    unsigned long int resultvar;					      \
    LOAD_ARGS_TYPES_##nr (args)						      \
    LOAD_REGS_TYPES_##nr (args)						      \
    asm volatile (							      \
    "syscall\n\t"							      \
    : "=a" (resultvar)							      \
    : "0" (name) ASM_ARGS_##nr : "memory", "cc", "r11", "cx");		      \
    (long int) resultvar; })
# undef INTERNAL_SYSCALL_TYPES
# define INTERNAL_SYSCALL_TYPES(name, err, nr, args...) \
  INTERNAL_SYSCALL_NCS_TYPES (__NR_##name, err, nr, ##args)

# undef INTERNAL_SYSCALL_ERROR_P
# define INTERNAL_SYSCALL_ERROR_P(val, err) \
  ((unsigned long int) (long int) (val) >= -4095L)

# undef INTERNAL_SYSCALL_ERRNO
# define INTERNAL_SYSCALL_ERRNO(val, err)	(-(val))




# define LOAD_ARGS_0()
# define LOAD_REGS_0
# define ASM_ARGS_0

# define LOAD_ARGS_TYPES_1(t1, a1)					   \
  t1 __arg1 = (t1) (a1);						   \
  LOAD_ARGS_0 ()
# define LOAD_REGS_TYPES_1(t1, a1)					   \
  register t1 _a1 asm ("rdi") = __arg1;					   \
  LOAD_REGS_0
# define ASM_ARGS_1	ASM_ARGS_0, "r" (_a1)
# define LOAD_ARGS_1(a1)						   \
  LOAD_ARGS_TYPES_1 (long int, a1)
# define LOAD_REGS_1							   \
  LOAD_REGS_TYPES_1 (long int, a1)

# define LOAD_ARGS_TYPES_2(t1, a1, t2, a2)				   \
  t2 __arg2 = (t2) (a2);						   \
  LOAD_ARGS_TYPES_1 (t1, a1)
# define LOAD_REGS_TYPES_2(t1, a1, t2, a2)				   \
  register t2 _a2 asm ("rsi") = __arg2;					   \
  LOAD_REGS_TYPES_1(t1, a1)
# define ASM_ARGS_2	ASM_ARGS_1, "r" (_a2)
# define LOAD_ARGS_2(a1, a2)						   \
  LOAD_ARGS_TYPES_2 (long int, a1, long int, a2)
# define LOAD_REGS_2							   \
  LOAD_REGS_TYPES_2 (long int, a1, long int, a2)

# define LOAD_ARGS_TYPES_3(t1, a1, t2, a2, t3, a3)			   \
  t3 __arg3 = (t3) (a3);						   \
  LOAD_ARGS_TYPES_2 (t1, a1, t2, a2)
# define LOAD_REGS_TYPES_3(t1, a1, t2, a2, t3, a3)			   \
  register t3 _a3 asm ("rdx") = __arg3;					   \
  LOAD_REGS_TYPES_2(t1, a1, t2, a2)
# define ASM_ARGS_3	ASM_ARGS_2, "r" (_a3)
# define LOAD_ARGS_3(a1, a2, a3)					   \
  LOAD_ARGS_TYPES_3 (long int, a1, long int, a2, long int, a3)
# define LOAD_REGS_3							   \
  LOAD_REGS_TYPES_3 (long int, a1, long int, a2, long int, a3)

# define LOAD_ARGS_TYPES_4(t1, a1, t2, a2, t3, a3, t4, a4)		   \
  t4 __arg4 = (t4) (a4);						   \
  LOAD_ARGS_TYPES_3 (t1, a1, t2, a2, t3, a3)
# define LOAD_REGS_TYPES_4(t1, a1, t2, a2, t3, a3, t4, a4)		   \
  register t4 _a4 asm ("r10") = __arg4;					   \
  LOAD_REGS_TYPES_3(t1, a2, t2, a2, t3, a3)
# define ASM_ARGS_4	ASM_ARGS_3, "r" (_a4)
# define LOAD_ARGS_4(a1, a2, a3, a4)					   \
  LOAD_ARGS_TYPES_4 (long int, a1, long int, a2, long int, a3,		   \
		     long int, a4)
# define LOAD_REGS_4							   \
  LOAD_REGS_TYPES_4 (long int, a1, long int, a2, long int, a3,		   \
		     long int, a4)

# define LOAD_ARGS_TYPES_5(t1, a1, t2, a2, t3, a3, t4, a4, t5, a5)	   \
  t5 __arg5 = (t5) (a5);						   \
  LOAD_ARGS_TYPES_4 (t1, a1, t2, a2, t3, a3, t4, a4)
# define LOAD_REGS_TYPES_5(t1, a1, t2, a2, t3, a3, t4, a4, t5, a5)	   \
  register t5 _a5 asm ("r8") = __arg5;					   \
  LOAD_REGS_TYPES_4 (t1, a1, t2, a2, t3, a3, t4, a4)
# define ASM_ARGS_5	ASM_ARGS_4, "r" (_a5)
# define LOAD_ARGS_5(a1, a2, a3, a4, a5)				   \
  LOAD_ARGS_TYPES_5 (long int, a1, long int, a2, long int, a3,		   \
		     long int, a4, long int, a5)
# define LOAD_REGS_5							   \
  LOAD_REGS_TYPES_5 (long int, a1, long int, a2, long int, a3,		   \
		     long int, a4, long int, a5)

# define LOAD_ARGS_TYPES_6(t1, a1, t2, a2, t3, a3, t4, a4, t5, a5, t6, a6) \
  t6 __arg6 = (t6) (a6);						   \
  LOAD_ARGS_TYPES_5 (t1, a1, t2, a2, t3, a3, t4, a4, t5, a5)
# define LOAD_REGS_TYPES_6(t1, a1, t2, a2, t3, a3, t4, a4, t5, a5, t6, a6) \
  register t6 _a6 asm ("r9") = __arg6;					   \
  LOAD_REGS_TYPES_5 (t1, a1, t2, a2, t3, a3, t4, a4, t5, a5)
# define ASM_ARGS_6	ASM_ARGS_5, "r" (_a6)
# define LOAD_ARGS_6(a1, a2, a3, a4, a5, a6)				   \
  LOAD_ARGS_TYPES_6 (long int, a1, long int, a2, long int, a3,		   \
		     long int, a4, long int, a5, long int, a6)
# define LOAD_REGS_6							   \
  LOAD_REGS_TYPES_6 (long int, a1, long int, a2, long int, a3,		   \
		     long int, a4, long int, a5, long int, a6)

#endif  // llamaos_x86_64_sysdep_h

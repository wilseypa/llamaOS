/* -*- Mode: C; c-basic-offset:4 ; -*- */
/*
 *  (C) 2001 by Argonne National Laboratory.
 *      See COPYRIGHT in top-level directory.
 */
#ifndef MPICHTIMER_H
#define MPICHTIMER_H
/*
 * This include file provide the definitions that are necessary to use the
 * timer calls, including the definition of the time stamp type and 
 * any inlined timer calls.
 *
 * The include file timerconf.h (created by autoheader from configure.ac)
 * is needed only to build the function versions of the timers.
 */
/* Include the appropriate files */
#define USE_GETHRTIME               1
#define USE_CLOCK_GETTIME           2
#define USE_GETTIMEOFDAY            3
#define USE_LINUX86_CYCLE           4
#define USE_LINUXALPHA_CYCLE        5
#define USE_QUERYPERFORMANCECOUNTER 6
#define USE_WIN86_CYCLE             7
#define USE_GCC_IA64_CYCLE          8
/* The value "USE_DEVICE" means that the ADI device provides the timer */
#define USE_DEVICE                  9
#define USE_WIN64_CYCLE             10
#define USE_MACH_ABSOLUTE_TIME      11
#define MPICH_TIMER_KIND USE_GETTIMEOFDAY

#if MPICH_TIMER_KIND == USE_GETHRTIME 
#include <sys/time.h>
#elif MPICH_TIMER_KIND == USE_CLOCK_GETTIME
#include <time.h>
#ifdef NEEDS_SYS_TIME_H
/* Some OS'es mistakenly require sys/time.h to get the definition of 
   CLOCK_REALTIME (POSIX requires the definition to be in time.h) */
#include <sys/time.h> 
#endif
#elif MPICH_TIMER_KIND == USE_GETTIMEOFDAY
#include <sys/types.h>
#include <sys/time.h>
#elif MPICH_TIMER_KIND == USE_LINUX86_CYCLE
#elif MPICH_TIMER_KIND == USE_GCC_IA64_CYCLE
#elif MPICH_TIMER_KIND == USE_LINUXALPHA_CYCLE
#elif MPICH_TIMER_KIND == USE_QUERYPERFORMANCECOUNTER
#include <winsock2.h>
#include <windows.h>
#elif MPICH_TIMER_KIND == USE_MACH_ABSOLUTE_TIME
#include <mach/mach_time.h>
#elif MPICH_TIMER_KIND == USE_WIN86_CYCLE
#include <winsock2.h>
#include <windows.h>
#endif

/* Define a time stamp */
typedef struct timeval MPID_Time_t;

/* 
 * Prototypes.  These are defined here so that inlined timer calls can
 * use them, as well as any profiling and timing code that is built into
 * MPICH
 */
/*@
  MPID_Wtime - Return a time stamp
  
  Output Parameter:
. timeval - A pointer to an 'MPID_Wtime_t' variable.

  Notes:
  This routine returns an `opaque` time value.  This difference between two
  time values returned by 'MPID_Wtime' can be converted into an elapsed time
  in seconds with the routine 'MPID_Wtime_diff'.

  This routine is defined this way to simplify its implementation as a macro.
  For example, the for Intel x86 and gcc, 
.vb
#define MPID_Wtime(timeval) \
     __asm__ __volatile__("rdtsc" : "=A" (*timeval))
.ve

  For some purposes, it is important
  that the timer calls change the timing of the code as little as possible.
  This form of a timer routine provides for a very fast timer that has
  minimal impact on the rest of the code.  

  From a semantic standpoint, this format emphasizes that any particular
  timer value has no meaning; only the difference between two values is 
  meaningful.

  Module:
  Timer

  Question:
  MPI-2 allows 'MPI_Wtime' to be a macro.  We should make that easy; this
  version does not accomplish that.
  @*/
void MPID_Wtime( MPID_Time_t * timeval);

/*@
  MPID_Wtime_diff - Compute the difference between two time stamps

  Input Parameters:
. t1, t2 - Two time values set by 'MPID_Wtime' on this process.
 

  Output Parameter:
. diff - The different in time between t2 and t1, measured in seconds.

  Note: 
  If 't1' is null, then 't2' is assumed to be differences accumulated with
  'MPID_Wtime_acc', and the output value gives the number of seconds that
  were accumulated.

  Question:
  Instead of handling a null value of 't1', should we have a separate
  routine 'MPID_Wtime_todouble' that converts a single timestamp to a 
  double value?  

  Module:
  Timer
  @*/
void MPID_Wtime_diff( MPID_Time_t *t1, MPID_Time_t *t2, double *diff );

/*@
  MPID_Wtime_acc - Accumulate time values

  Input Parameters:
. t1,t2,t3 - Three time values.  't3' is updated with the difference between 
             't2' and 't1': '*t3 += (t2 - t1)'.

  Notes:
  This routine is used to accumulate the time spent with a block of code 
  without first converting the time stamps into a particular arithmetic
  type such as a 'double'.  For example, if the 'MPID_Wtime' routine accesses
  a cycle counter, this routine (or macro) can perform the accumulation using
  integer arithmetic.  

  To convert a time value accumulated with this routine, use 'MPID_Wtime_diff' 
  with a 't1' of zero.  

  Module:
  Timer
  @*/
void MPID_Wtime_acc( MPID_Time_t *t1, MPID_Time_t *t2, MPID_Time_t *t3 );

/*@
  MPID_Wtime_todouble - Converts an MPID timestamp to a double 

  Input Parameter:
. timeval - 'MPID_Time_t' time stamp

  Output Parameter:
. seconds - Time in seconds from an arbitrary (but fixed) time in the past

  Notes:
  This routine may be used to change a timestamp into a number of seconds,
  suitable for 'MPI_Wtime'.  

  @*/
void MPID_Wtime_todouble( MPID_Time_t *timeval, double *seconds );

/*@
  MPID_Wtick - Provide the resolution of the 'MPID_Wtime' timer

  Return value:
  Resolution of the timer in seconds.  In many cases, this is the 
  time between ticks of the clock that 'MPID_Wtime' returns.  In other
  words, the minimum significant difference that can be computed by 
  'MPID_Wtime_diff'.

  Note that in some cases, the resolution may be estimated.  No application
  should expect either the same estimate in different runs or the same
  value on different processes.

  Module:
  Timer
  @*/
double MPID_Wtick( void );

/*@
  MPID_Wtime_init - Initialize the timer

  Note:
  This routine should perform any steps needed to initialize the timer.
  In addition, it should set the value of the attribute 'MPI_WTIME_IS_GLOBAL'
  if the timer is known to be the same for all processes in 'MPI_COMM_WORLD'
  (the value is zero by default).

  If any operations need to be performed when the MPI program calls 
  'MPI_Finalize' this routine should register a handler with 'MPI_Finalize'
  (see the MPICH Design Document).
  
  Return Values:
  0 on success.  -1 on Failure.  1 means that the timer may not be used
  until after MPID_Init completes.  This allows the device to set up the
  timer (first needed for Blue Gene support).

  Module:
  Timer

  @*/
int MPID_Wtime_init(void);

/* Inlined timers.  Note that any definition of one of the functions
   prototyped above in terms of a macro will simply cause the compiler
   to use the macro instead of the function definition.

   Currently, all except the Windows performance counter timers
   define MPID_Wtime_init as null; by default, the value of
   MPI_WTIME_IS_GLOBAL is false.
 */

/* MPIDM_Wtime_todouble() is a hack to get a macro version
   of the todouble function.  

   The logging library should save the native MPID_Timer_t 
   structure to disk and use the todouble function in the 
   post-processsing step to convert the values to doubles.
   */

/* The timer kind is set using AC_SUBST in the MPICH configure */
#define MPICH_TIMER_KIND USE_GETTIMEOFDAY

#if MPICH_TIMER_KIND == USE_GETHRTIME 
#define MPID_Wtime_init() 0
#define MPIDM_Wtime_todouble MPID_Wtime_todouble

#elif MPICH_TIMER_KIND == USE_CLOCK_GETTIME
#define MPID_Wtime_init() 0
#define MPIDM_Wtime_todouble MPID_Wtime_todouble

#elif MPICH_TIMER_KIND == USE_GETTIMEOFDAY
#define MPID_Wtime_init() 0
#define MPIDM_Wtime_todouble MPID_Wtime_todouble

#elif MPICH_TIMER_KIND == USE_LINUX86_CYCLE
/* The rdtsc instruction is not a "serializing" instruction, so the
   processor is free to reorder it.  In order to get more accurate
   timing numbers with rdtsc, we need to put a serializing
   instruction, like cpuid, before rdtsc.  X86_64 architectures have
   the rdtscp instruction which is synchronizing, we use this when we
   can. */
#ifdef LINUX86_CYCLE_RDTSCP
#define MPID_Wtime(var_ptr) \
    __asm__ __volatile__("push %%rbx ; cpuid ; rdtsc ; pop %%rbx ; shl $32, %%rdx; or %%rdx, %%rax" : "=a" (*var_ptr) : : "ecx", "rdx")
#elif defined(LINUX86_CYCLE_CPUID_RDTSC64)
/* Here we have to save the rbx register for when the compiler is
   generating position independent code (e.g., when it's generating
   shared libraries) */
#define MPID_Wtime(var_ptr)                                                                     \
     __asm__ __volatile__("push %%rbx ; cpuid ; rdtsc ; pop %%rbx" : "=A" (*var_ptr) : : "ecx")
#elif defined(LINUX86_CYCLE_CPUID_RDTSC32)
/* Here we have to save the ebx register for when the compiler is
   generating position independent code (e.g., when it's generating
   shared libraries) */
#define MPID_Wtime(var_ptr)                                                                     \
     __asm__ __volatile__("push %%ebx ; cpuid ; rdtsc ; pop %%ebx" : "=A" (*var_ptr) : : "ecx")
#elif defined(LINUX86_CYCLE_RDTSC)
/* The configure test using cpuid must have failed, try just rdtsc by itself */
#define MPID_Wtime(var_ptr) __asm__ __volatile__("rdtsc" : "=A" (*var_ptr))
#else
#error Dont know which Linux timer to use
#endif

extern double MPID_Seconds_per_tick;
#define MPIDM_Wtime_todouble(t, d) *d = (double)*t * MPID_Seconds_per_tick

#elif MPICH_TIMER_KIND == USE_GCC_IA64_CYCLE
#ifdef __INTEL_COMPILER
#include "ia64regs.h"
#define MPID_Wtime(var_ptr) { MPID_Time_t t_val;\
	t_val=__getReg(_IA64_REG_AR_ITC); *var_ptr=t_val;}
#else
#define MPID_Wtime(var_ptr) { MPID_Time_t t_val;\
	__asm__ __volatile__("mov %0=ar.itc" : "=r" (t_val)); *var_ptr=t_val;}
#endif
extern double MPID_Seconds_per_tick;
#define MPIDM_Wtime_todouble(t, d) *d = (double)*t * MPID_Seconds_per_tick

#elif MPICH_TIMER_KIND == USE_LINUXALPHA_CYCLE
#define MPID_Wtime_init() 0
#define MPIDM_Wtime_todouble MPID_Wtime_todouble

#elif MPICH_TIMER_KIND == USE_QUERYPERFORMANCECOUNTER
#define MPID_Wtime(var) QueryPerformanceCounter(var)
extern double MPID_Seconds_per_tick;
#define MPIDM_Wtime_todouble( t, d ) \
  *d = (double)t->QuadPart * MPID_Seconds_per_tick /* convert to seconds */

#elif MPICH_TIMER_KIND == USE_WIN86_CYCLE
#define MPID_Wtime(var_ptr) \
{ \
    register int *f1 = (int*)var_ptr; \
    __asm cpuid \
    __asm rdtsc \
    __asm mov ecx, f1 \
    __asm mov [ecx], eax \
    __asm mov [ecx + TYPE int], edx \
}
extern double MPID_Seconds_per_tick;
#define MPIDM_Wtime_todouble(t, d) *d = (double)(__int64)*t * MPID_Seconds_per_tick
#define MPIDM_Wtime_diff(t1,t2,diff) *diff = (double)((__int64)( *t2 - *t1 )) * MPID_Seconds_per_tick

#elif MPICH_TIMER_KIND == USE_MACH_ABSOLUTE_TIME
#define MPIDM_Wtime_todouble MPID_Wtime_todouble

#endif

#endif

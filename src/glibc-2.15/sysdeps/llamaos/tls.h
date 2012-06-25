
#ifndef llamaos_tls_h
#define llamaos_tls_h

#include_next <tls.h>

# include <stddef.h>

/* Type for the dtv.  */
typedef union dtv
{
  size_t counter;
  struct
  {
    void *val;
    bool is_static;
  } pointer;
} dtv_t;

typedef struct
{
  void *tcb;		/* Pointer to the TCB.  Not necessarily the
			   thread descriptor used by libpthread.  */
  dtv_t *dtv;
  void *self;		/* Pointer to the thread descriptor.  */
  int multiple_threads;

} tcbhead_t;

/* This is the size of the initial TCB.  Can't be just sizeof (tcbhead_t),
   because NPTL getpid, __libc_alloca_cutoff etc. need (almost) the whole
   struct pthread even when not linked with -lpthread.  */
# define TLS_INIT_TCB_SIZE 0

/* Alignment requirements for the initial TCB.  */
# define TLS_INIT_TCB_ALIGN 0

/* This is the size of the TCB.  */
# define TLS_TCB_SIZE 0

/* Alignment requirements for the TCB.  */
# define TLS_TCB_ALIGN 1

#define TLS_TCB_AT_TP 1

#define TLS_INIT_TP(tcb, firstcall) 0

/* Alignment requirements for the TCB.  */
# define TLS_TCB_ALIGN 0

/* Install the dtv pointer.  The pointer passed is to the element with
   index -1 which contain the length.  */
# define INSTALL_DTV(descr, dtvp)

/* Return dtv of given thread descriptor.  */
# define GET_DTV(descr) \
  (((tcbhead_t *) (descr))->dtv)

  /* Return the address of the dtv for the current thread.  */
# define THREAD_DTV() 0

#endif  //  llamaos_tls_h

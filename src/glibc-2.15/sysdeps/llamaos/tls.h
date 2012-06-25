
#ifndef llamaos_tls_h
#define llamaos_tls_h

#include_next <tls.h>

typedef struct
{
  int multiple_threads;

} tcbhead_t;

#define TLS_TCB_AT_TP 1

#endif  //  llamaos_tls_h

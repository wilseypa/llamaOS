
#ifndef ucguest_tls_h
#define ucguest_tls_h

#include_next <tls.h>

typedef struct
{
  int multiple_threads;

} tcbhead_t;

#define TLS_TCB_AT_TP 1

#endif  //  ucguest_tls_h

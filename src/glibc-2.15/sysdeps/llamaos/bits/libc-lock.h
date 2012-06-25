
#ifndef llamaos_bits_libc_lock_h
#define llamaos_bits_libc_lock_h

typedef struct
{
   int lock;

} _IO_lock_t;

typedef struct
{
   int lock;

} __rtld_lock_recursive_t;

#define _LIBC_LOCK_RECURSIVE_INITIALIZER { 0 }

#define MUTEX_INITIALIZER 0

#include_next<bits/libc-lock.h>

#endif  // llamaos_bits_libc_lock_h


#ifndef ucguest_bits_fcntl_h
#define ucguest_bits_fcntl_h

#include <sys/stat.h>

#include_next<bits/fcntl.h>

#define O_LARGEFILE 0
#define __ASSUME_O_CLOEXEC

#endif  // ucguest_bits_fcntl_h

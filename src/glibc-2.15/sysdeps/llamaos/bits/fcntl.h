
#ifndef llamaos_bits_fcntl_h
#define llamaos_bits_fcntl_h

#include <sys/stat.h>

#include_next<bits/fcntl.h>

#define O_LARGEFILE 0
#define __ASSUME_O_CLOEXEC

#endif  // llamaos_bits_fcntl_h
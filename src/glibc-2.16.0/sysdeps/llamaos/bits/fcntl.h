
#ifndef llamaos_bits_fcntl_h
#define llamaos_bits_fcntl_h

#include <sys/stat.h>

// #include_next<bits/fcntl.h>

/* open/fcntl - O_SYNC is only implemented on blocks devices and on files
   located on a few file systems.  */
#define O_ACCMODE	   0003
#define O_RDONLY	     00
#define O_WRONLY	     01
#define O_RDWR		     02
#define O_CREAT		   0100	/* not fcntl */
#define O_EXCL		   0200	/* not fcntl */
#define O_NOCTTY	   0400	/* not fcntl */
#define O_TRUNC		  01000	/* not fcntl */
#define O_APPEND	  02000
#define O_NONBLOCK	  04000
#define O_NDELAY	O_NONBLOCK
#define O_SYNC	       04010000
#define O_FSYNC		 O_SYNC
#define O_ASYNC		 020000

#ifdef __USE_LARGEFILE64
# ifdef __x86_64__
#  define O_LARGEFILE	0
# else
#  define O_LARGEFILE	0100000
# endif
#endif

/* Values for the second argument to `fcntl'.  */
#define F_DUPFD		0	/* Duplicate file descriptor.  */
#define F_GETFD		1	/* Get file descriptor flags.  */
#define F_SETFD		2	/* Set file descriptor flags.  */
#define F_GETFL		3	/* Get file status flags.  */
#define F_SETFL		4	/* Set file status flags.  */

/* For F_[GET|SET]FD.  */
#define FD_CLOEXEC	1	/* actually anything with low bit set goes */

#define __ASSUME_O_CLOEXEC
# define O_CLOEXEC     02000000 /* Set close_on_exec.  */

#endif  // llamaos_bits_fcntl_h

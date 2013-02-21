/* Copyright (C) 1991, 1994, 1996, 1997 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <http://www.gnu.org/licenses/>.  */

/* This file defines the `errno' constants.  */

#ifdef _ERRNO_H
# ifndef __ASSEMBLER__
/* Function to get address of global `errno' variable.  */
extern int *__errno_location (void) __THROW __attribute__ ((__const__));

#  if !defined _LIBC || defined _LIBC_REENTRANT
/* When using threads, errno is a per-thread value.  */
#   define errno (*__errno_location ())
#  endif
# endif /* !__ASSEMBLER__ */
#endif /* _ERRNO_H */

#if !defined __Emath_defined && (defined _ERRNO_H || defined __need_Emath)
#undef	__need_Emath
#define	__Emath_defined	1

// # define EDOM	XXX	<--- fill in what is actually needed
// # define EILSEQ	XXX	<--- fill in what is actually needed
// # define ERANGE	XXX	<--- fill in what is actually needed

#define EDOM 1
#define EILSEQ 2
#define ERANGE 3

#endif

#ifndef errno
#  ifndef NOT_IN_libc
#   define errno __libc_errno
#  else
#   define errno errno		/* For #ifndef errno tests.  */
#  endif
#endif

#ifdef	_ERRNO_H
// # error "Define here all the missing error messages for the port.  These"
// # error "must match the numbers of the kernel."
// # define Exxxx	XXX

#define ENOSYS 4

#define EAFNOSUPPORT 5
#define EADDRINUSE 6
#define EADDRNOTAVAIL 7
#define EISCONN 8
#define E2BIG 9
// #define EDOM 10
#define EFAULT 11
#define EBADF 12
#define EBADMSG 13
#define EPIPE 14
#define ECONNABORTED 15
#define EALREADY 16
#define ECONNREFUSED 17
#define ECONNRESET 18
#define EXDEV 19
#define EDESTADDRREQ 20
#define EBUSY 21
#define ENOTEMPTY 22
#define ENOEXEC 23
#define EEXIST 24
#define EFBIG 25
#define ENAMETOOLONG 26
// #define ENOSYS 27
#define EHOSTUNREACH 28
#define EIDRM 29
// #define EILSEQ 30
#define ENOTTY 31
#define EINTR 32
#define EINVAL 33
#define ESPIPE 34
#define EIO 35
#define EISDIR 36
#define EMSGSIZE 37
#define ENETDOWN 38
#define ENETRESET 39
#define ENETUNREACH 40
#define ENOBUFS 41
#define ECHILD 42
#define ENOLINK 43
#define ENOLCK 44
#define ENODATA 45
#define ENOMSG 46
#define ENOPROTOOPT 47
#define ENOSPC 48
#define ENOSR 49
#define ENXIO 50
#define ENODEV 51
#define ENOENT 52
#define ESRCH 53
#define ENOTDIR 54
#define ENOTSOCK 55
#define ENOSTR 56
#define ENOTCONN 57
#define ENOMEM 58
#define ENOTSUP 59
#define ECANCELED 60
#define EINPROGRESS 61
#define EPERM 62
#define EOPNOTSUPP 63
#define EWOULDBLOCK 64
#define EOWNERDEAD 65
#define EACCES 66
#define EPROTO 67
#define EPROTONOSUPPORT 68
#define EROFS 69
#define EDEADLK 70
#define EAGAIN 71
// #define ERANGE 72
#define ENOTRECOVERABLE 73
#define ETIME 74
#define ETXTBSY 75
#define ETIMEDOUT 76
#define ENFILE 77
#define EMFILE 78
#define EMLINK 79
#define ELOOP 80
#define EOVERFLOW 81
#define EPROTOTYPE 82
// #define ETIMEDOUT 83
// #define EINVAL 84

#endif

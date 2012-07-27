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

#define EDOM 0
#define EILSEQ 0
#define ERANGE 0

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

#define ENOSYS 0

#define EAFNOSUPPORT 0
#define EADDRINUSE 0
#define EADDRNOTAVAIL 0
#define EISCONN 0
#define E2BIG 0
#define EDOM 0
#define EFAULT 0
#define EBADF 0
#define EBADMSG 0
#define EPIPE 0
#define ECONNABORTED 0
#define EALREADY 0
#define ECONNREFUSED 0
#define ECONNRESET 0
#define EXDEV 0
#define EDESTADDRREQ 0
#define EBUSY 0
#define ENOTEMPTY 0
#define ENOEXEC 0
#define EEXIST 0
#define EFBIG 0
#define ENAMETOOLONG 0
#define ENOSYS 0
#define EHOSTUNREACH 0
#define EIDRM 0
#define EILSEQ 0
#define ENOTTY 0
#define EINTR 0
#define EINVAL 0
#define ESPIPE 0
#define EIO 0
#define EISDIR 0
#define EMSGSIZE 0
#define ENETDOWN 0
#define ENETRESET 0
#define ENETUNREACH 0
#define ENOBUFS 0
#define ECHILD 0
#define ENOLINK 0
#define ENOLCK 0
#define ENODATA 0
#define ENOMSG 0
#define ENOPROTOOPT 0
#define ENOSPC 0
#define ENOSR 0
#define ENXIO 0
#define ENODEV 0
#define ENOENT 0
#define ESRCH 0
#define ENOTDIR 0
#define ENOTSOCK 0
#define ENOSTR 0
#define ENOTCONN 0
#define ENOMEM 0
#define ENOTSUP 0
#define ECANCELED 0
#define EINPROGRESS 0
#define EPERM 0
#define EOPNOTSUPP 0
#define EWOULDBLOCK 0
#define EOWNERDEAD 0
#define EACCES 0
#define EPROTO 0
#define EPROTONOSUPPORT 0
#define EROFS 0
#define EDEADLK 0
#define EAGAIN 0
#define ERANGE 0
#define ENOTRECOVERABLE 0
#define ETIME 0
#define ETXTBSY 0
#define ETIMEDOUT 0
#define ENFILE 0
#define EMFILE 0
#define EMLINK 0
#define ELOOP 0
#define EOVERFLOW 0
#define EPROTOTYPE 0
#define ETIMEDOUT 0
#define EINVAL 0

#endif

/*
Copyright (c) 2013, William Magato
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

   1. Redistributions of source code must retain the above copyright notice,
      this list of conditions and the following disclaimer.

   2. Redistributions in binary form must reproduce the above copyright notice,
      this list of conditions and the following disclaimer in the documentation
      and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDER(S) AND CONTRIBUTORS ''AS IS''
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER(S) OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

The views and conclusions contained in the software and documentation are those
of the authors and should not be interpreted as representing official policies,
either expressed or implied, of the copyright holder(s) or contributors.
*/

#ifndef glibc_sysdeps_llamaos_bits_errno_h
#define glibc_sysdeps_llamaos_bits_errno_h

# ifndef __ASSEMBLER__
/* Function to get address of global `errno' variable.  */
extern int *__errno_location (void) __THROW __attribute__ ((__const__));

#  if !defined _LIBC || defined _LIBC_REENTRANT
/* When using threads, errno is a per-thread value.  */
#   define errno (*__errno_location ())
#  endif
# endif /* !__ASSEMBLER__ */

#if !defined __Emath_defined && (defined _ERRNO_H || defined __need_Emath)
#undef	__need_Emath
#define	__Emath_defined	1

# define EDOM		0	// XXX	<--- fill in what is actually needed
# define EILSEQ		1	// XXX	<--- fill in what is actually needed
# define ERANGE		2	// XXX	<--- fill in what is actually needed
#endif

#ifdef	_ERRNO_H
// # error "Define here all the missing error messages for the port.  These"
// # error "must match the numbers of the kernel."
//# define Exxxx	XXX

# define EBADF			3
# define E2BIG			4
# define EINVAL			5
# define EINTR			6
# define ENOMSG			7
# define ENOENT			8
# define ENAMETOOLONG		9
# define ELOOP			10
# define ENOTDIR		11
# define ENOSYS			12
# define EBUSY			13
# define EEXIST			14
# define ENOSPC			15
# define EOVERFLOW		16
# define ESPIPE			17
# define EAGAIN			18
# define ENOMEM			19
# define EACCES			20
# define EPROTOTYPE		21
# define EISDIR			22
# define EFAULT			23
# define EROFS			24
# define EAFNOSUPPORT		25
# define EADDRINUSE		26
# define EADDRNOTAVAIL		27
# define EISCONN		28
# define EBADMSG		29
# define EPIPE			30
# define ECONNABORTED		31
# define EALREADY		32
# define ECONNREFUSED		33
# define ECONNRESET		34
# define EXDEV			35
# define EDESTADDRREQ		36
# define ENOTEMPTY		37
# define ENOEXEC		38
# define EFBIG			39
# define EHOSTUNREACH		40
# define EIDRM			41
# define ENOTTY			42
# define EIO			43
# define EMSGSIZE		44
# define ENETDOWN		45
# define ENETRESET		46
# define ENETUNREACH		47
# define ENOBUFS		48
# define ECHILD			49
# define ENOLINK		50
# define ENOLCK			51
# define ENODATA		52
# define ENOPROTOOPT		53
# define ENOSR			54
# define ENXIO			55
# define ENODEV			56
# define ESRCH			57
# define ENOTSOCK		58
# define ENOSTR			59
# define ENOTCONN		60
# define ENOTSUP		61
# define ECANCELED		62
# define EINPROGRESS		63
# define EPERM			64
# define EOPNOTSUPP		65
# define EWOULDBLOCK		66
# define EOWNERDEAD		67
# define EPROTONOSUPPORT	68
# define EDEADLK		69
# define ENOTRECOVERABLE	70
# define ETIME			71
# define ETXTBSY		72
# define ETIMEDOUT		73
# define ENFILE			74
# define EMFILE			75
# define EMLINK			76
# define EPROTO			77


#endif

#endif	// glibc_sysdeps_llamaos_bits_errno_h


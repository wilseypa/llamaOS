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

# define EDOM		1	// XXX	<--- fill in what is actually needed
# define EILSEQ		2	// XXX	<--- fill in what is actually needed
# define ERANGE		3	// XXX	<--- fill in what is actually needed
#endif

#ifdef	_ERRNO_H
// # error "Define here all the missing error messages for the port.  These"
// # error "must match the numbers of the kernel."
//# define Exxxx	XXX

# define EBADF			4
# define E2BIG			5
# define EINVAL			6
# define EINTR			7
# define ENOMSG			8
# define ENOENT			9
# define ENAMETOOLONG		10
# define ELOOP			11
# define ENOTDIR		12
# define ENOSYS			13
# define EBUSY			14
# define EEXIST			15
# define ENOSPC			16
# define EOVERFLOW		17
# define ESPIPE			18
# define EAGAIN			19
# define ENOMEM			20
# define EACCES			21
# define EPROTOTYPE		22
# define EISDIR			23
# define EFAULT			24
# define EROFS			25
# define EAFNOSUPPORT		26
# define EADDRINUSE		27
# define EADDRNOTAVAIL		28
# define EISCONN		29
# define EBADMSG		30
# define EPIPE			31
# define ECONNABORTED		32
# define EALREADY		33
# define ECONNREFUSED		34
# define ECONNRESET		35
# define EXDEV			36
# define EDESTADDRREQ		37
# define ENOTEMPTY		38
# define ENOEXEC		39
# define EFBIG			40
# define EHOSTUNREACH		41
# define EIDRM			42
# define ENOTTY			43
# define EIO			44
# define EMSGSIZE		45
# define ENETDOWN		46
# define ENETRESET		47
# define ENETUNREACH		48
# define ENOBUFS		49
# define ECHILD			50
# define ENOLINK		51
# define ENOLCK			52
# define ENODATA		53
# define ENOPROTOOPT		54
# define ENOSR			55
# define ENXIO			56
# define ENODEV			57
# define ESRCH			58
# define ENOTSOCK		59
# define ENOSTR			60
# define ENOTCONN		61
# define ENOTSUP		62
# define ECANCELED		63
# define EINPROGRESS		64
# define EPERM			65
# define EOPNOTSUPP		66
# define EWOULDBLOCK		67
# define EOWNERDEAD		68
# define EPROTONOSUPPORT	69
# define EDEADLK		70
# define ENOTRECOVERABLE	71
# define ETIME			72
# define ETXTBSY		73
# define ETIMEDOUT		74
# define ENFILE			75
# define EMFILE			76
# define EMLINK			77
# define EPROTO			78


#endif

#endif	// glibc_sysdeps_llamaos_bits_errno_h


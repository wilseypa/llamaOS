/*
Copyright (c) 2012, William Magato
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

#ifndef llamaos_xen_export_glibc_h_
#define llamaos_xen_export_glibc_h_

#include <stddef.h>
#include <signal.h>
#include <unistd.h>
#include <sys/poll.h>
#include <sys/types.h>
#include <sys/uio.h>

#ifdef __cplusplus
#define EXTERN extern "C"
#else
#define EXTERN
#endif  // __cplusplus

// !BAM
// why is this not defined?
typedef int64_t off64_t;

// void abort (void)
typedef void (*llamaos_abort_t) (void);
EXTERN void register_llamaos_abort (llamaos_abort_t abort);

// int brk (void *addr)
typedef void *(*llamaos_brk_t) (void *);
EXTERN void register_llamaos_brk (llamaos_brk_t brk);

// void _exit (int status)
typedef void (*llamaos_exit_t) (int);
EXTERN void register_llamaos_exit (llamaos_exit_t exit);

// long int get_avphys_pages (void)
typedef long int (*llamaos_get_avphys_pages_t) (void);
EXTERN void register_llamaos_get_avphys_pages (llamaos_get_avphys_pages_t get_avphys_pages);

// int __get_nprocs (void)
typedef int (*llamaos_get_nprocs_t) (void);
EXTERN void register_llamaos_get_nprocs (llamaos_get_nprocs_t get_nprocs);

// int get_nprocs_conf (void)
typedef int (*llamaos_get_nprocs_conf_t) (void);
EXTERN void register_llamaos_get_nprocs_conf (llamaos_get_nprocs_conf_t get_nprocs_conf);

// int getpagesize (void)
typedef int (*llamaos_getpagesize_t) (void);
EXTERN void register_llamaos_getpagesize (llamaos_getpagesize_t getpagesize);

// long int get_phys_pages (void)
typedef long int (*llamaos_get_phys_pages_t) (void);
EXTERN void register_llamaos_get_phys_pages (llamaos_get_phys_pages_t get_phys_pages);

// char *getcwd (char *buf, size_t size)
typedef char *(*llamaos_getcwd_t) (char *, size_t);
EXTERN void register_llamaos_getcwd (llamaos_getcwd_t getcwd);

// void __libc_fatal (const char *message)
typedef void (*llamaos_libc_fatal_t) (const char *);
EXTERN void register_llamaos_libc_fatal (llamaos_libc_fatal_t libc_fatal);

// int __libc_open (const char *file, int oflag, ...)
typedef int (*llamaos_libc_open_t) (const char *, int);
EXTERN void register_llamaos_libc_open (llamaos_libc_open_t libc_open);

// off64_t __libc_lseek64 (int fd, off64_t offset, int whence)
typedef off64_t (*llamaos_lseek64_t) (int, off64_t, int);
EXTERN void register_llamaos_lseek64 (llamaos_lseek64_t func);

// int madvise (__ptr_t addr, size_t len, int advice)
typedef int (*llamaos_madvise_t) (__ptr_t, size_t, int);
EXTERN void register_llamaos_madvise (llamaos_madvise_t madvise);

// long int pathconf (const char *path, int name)
typedef long int (*llamaos_pathconf_t) (const char *, int);
EXTERN void register_llamaos_pathconf (llamaos_pathconf_t madvise);

// int poll (struct pollfd *fds, nfds_t nfds, int timeout)
typedef int (*llamaos_poll_t) (struct pollfd *, nfds_t, int);
EXTERN void register_llamaos_poll (llamaos_poll_t func);

// int raise (int sig)
typedef int (*llamaos_raise_t) (int);
EXTERN void register_llamaos_raise (llamaos_raise_t raise);

// ssize_t __libc_read (int fd, void *buf, size_t nbytes)
typedef ssize_t (*llamaos_read_t) (int, void *, size_t);
EXTERN void register_llamaos_read (llamaos_read_t func);

// int sched_get_priority_max (int algorithm)
typedef int (*llamaos_sched_get_priority_max_t) (int);
EXTERN void register_llamaos_sched_get_priority_max (llamaos_sched_get_priority_max_t sched_get_priority_max);

// int sched_get_priority_min (int algorithm)
typedef int (*llamaos_sched_get_priority_min_t) (int);
EXTERN void register_llamaos_sched_get_priority_min (llamaos_sched_get_priority_min_t sched_get_priority_min);

// int sigsuspend (const sigset_t *set)
typedef int (*llamaos_sigsuspend_t) (const sigset_t *);
EXTERN void register_llamaos_sigsuspend (llamaos_sigsuspend_t sigsuspend);

// int __sigsuspend_nocancel (const sigset_t *set)
typedef int (*llamaos_sigsuspend_nocancel_t) (const sigset_t *);
EXTERN void register_llamaos_sigsuspend_nocancel (llamaos_sigsuspend_nocancel_t sigsuspend_nocancel);

// long int syscall (long int callno)
typedef long int (*llamaos_syscall_t) (long int);
EXTERN void register_llamaos_syscall (llamaos_syscall_t syscall);

// ssize_t libc_write (int fd, const void *buf, size_t nbytes)
typedef ssize_t (*llamaos_write_t) (int, const void *, size_t);
EXTERN void register_llamaos_write (llamaos_write_t write);

// ssize_t __libc_writev (int fd, const struct iovec *vector, int count)
typedef ssize_t (*llamaos_writev_t) (int, const struct iovec *, int);
EXTERN void register_llamaos_writev (llamaos_writev_t func);

#endif	//  llamaos_xen_export_glibc_h_

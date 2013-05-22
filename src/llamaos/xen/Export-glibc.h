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
#include <stddef.h>
#include <sys/poll.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <sys/stat.h>

#ifdef __cplusplus
#define EXTERN extern "C"
#else
#define EXTERN
#endif  // __cplusplus

// !BAM
// why is this not defined?
typedef int64_t off64_t;

#define stat64(fname, buf) __xstat64 (_STAT_VER, fname, buf)

// void abort (void)
typedef void (*llamaos_abort_t) (void);
EXTERN void register_llamaos_abort (llamaos_abort_t abort);

// int __access (const char *file, int type)
typedef int (*llamaos_access_t) (const char *, int);
EXTERN void register_llamaos_access (llamaos_access_t access);

// void __assert_perror_fail (int errnum, const char *file, unsigned int line, const char *function)
typedef void (*llamaos_assert_perror_fail_t) (int, const char *, unsigned int, const char *);
EXTERN void register_llamaos_assert_perror_fail (llamaos_assert_perror_fail_t assert);

// void __assert_fail (const char *assertion, const char *file, unsigned int line, const char *function)
typedef void (*llamaos_assert_fail_t) (const char *, const char *, unsigned int, const char *);
EXTERN void register_llamaos_assert_fail (llamaos_assert_fail_t assert);

// int brk (void *addr)
typedef void *(*llamaos_brk_t) (void *);
EXTERN void register_llamaos_brk (llamaos_brk_t brk);

// int __close (int fd)
typedef int (*llamaos_close_t) (int);
EXTERN void register_llamaos_close (llamaos_close_t close);

// int __dup (int fd)
typedef int (*llamaos_dup_t) (int);
EXTERN void register_llamaos_dup (llamaos_dup_t dup);

// int __dup2 (int fd, int fd2)
typedef int (*llamaos_dup2_t) (int, int);
EXTERN void register_llamaos_dup2 (llamaos_dup2_t dup2);

// void _exit (int status)
typedef void (*llamaos_exit_t) (int);
EXTERN void register_llamaos_exit (llamaos_exit_t exit);

// int __ftruncate (int fd, off_t length)
typedef int (*llamaos_ftruncate_t) (int, off_t);
EXTERN void register_llamaos_ftruncate (llamaos_ftruncate_t ftruncate);

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

// int getpid (void)
typedef int (*llamaos_getpid_t) (void);
EXTERN void register_llamaos_getpid (llamaos_getpid_t getpid);

// int __gettimeofday (struct timeval *tv, struct timezone *tz)
typedef int (*llamaos_gettimeofday_t) (struct timeval *, struct timezone *);
EXTERN void register_llamaos_gettimeofday (llamaos_gettimeofday_t func);

// int __isatty (int fd)
typedef int (*llamaos_isatty_t) (int);
EXTERN void register_llamaos_isatty (llamaos_isatty_t func);

// void __libc_fatal (const char *message)
typedef void (*llamaos_libc_fatal_t) (const char *);
EXTERN void register_llamaos_libc_fatal (llamaos_libc_fatal_t libc_fatal);

// int __libc_open (const char *file, int oflag, ...)
typedef int (*llamaos_libc_open_t) (const char *, int);
EXTERN void register_llamaos_libc_open (llamaos_libc_open_t libc_open);

// off_t __lseek (int fd, off_t offset, int whence)
typedef off_t (*llamaos_lseek_t) (int, off_t, int);
EXTERN void register_llamaos_lseek (llamaos_lseek_t func);

// off64_t __libc_lseek64 (int fd, off64_t offset, int whence)
typedef off64_t (*llamaos_lseek64_t) (int, off64_t, int);
EXTERN void register_llamaos_lseek64 (llamaos_lseek64_t func);

// int __lxstat64 (int vers, const char *file, struct stat64 *buf)
// typedef int (*llamaos_lxstat64_t) (int, const char *, struct stat64 *);
// EXTERN void register_llamaos_lxstat64 (llamaos_lxstat64_t func);

// int madvise (__ptr_t addr, size_t len, int advice)
typedef int (*llamaos_madvise_t) (__ptr_t, size_t, int);
EXTERN void register_llamaos_madvise (llamaos_madvise_t madvise);

// int __mkdir (const char *path, mode_t mode)
typedef int (*llamaos_mkdir_t) (const char *, mode_t);
EXTERN void register_llamaos_mkdir (llamaos_mkdir_t func);

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

// unsigned int sleep (unsigned int seconds)
typedef unsigned int (*llamaos_sleep_t) (unsigned int);
EXTERN void register_llamaos_sleep (llamaos_sleep_t sleep);

// long int syscall (long int callno)
typedef long int (*llamaos_syscall_t) (long int);
EXTERN void register_llamaos_syscall (llamaos_syscall_t syscall);

// int unlink (const char *name)
typedef int (*llamaos_unlink_t) (const char *);
EXTERN void register_llamaos_unlink (llamaos_unlink_t unlink);

// ssize_t libc_write (int fd, const void *buf, size_t nbytes)
typedef ssize_t (*llamaos_write_t) (int, const void *, size_t);
EXTERN void register_llamaos_write (llamaos_write_t write);

// ssize_t __libc_writev (int fd, const struct iovec *vector, int count)
typedef ssize_t (*llamaos_writev_t) (int, const struct iovec *, int);
EXTERN void register_llamaos_writev (llamaos_writev_t func);

// int __xstat (int vers, const char *file, struct stat *buf)
typedef int (*llamaos_xstat_t) (int, const char *, struct stat *);
EXTERN void register_llamaos_xstat (llamaos_xstat_t func);

// int __xstat64 (int vers, const char *file, struct stat64 *buf)
// typedef int (*llamaos_xstat64_t) (int, const char *, struct stat64 *);
// EXTERN void register_llamaos_xstat64 (llamaos_xstat64_t func);

#endif	//  llamaos_xen_export_glibc_h_

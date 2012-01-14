/*
Copyright (c) 2011, William Magato
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

#include <cstdio>
#include <sys/poll.h>

#include <stdexcept>
#include <sstream>

#include <xen/xen.h>
#include <xen/sched.h>

#include <llamaos/memory/memory.h>
#include <llamaos/xen/Console.h>
#include <llamaos/xen/Hypercall.h>
#include <llamaos/xen/Hypervisor.h>
#include <llamaos/config.h>
#include <llamaos/trace.h>

using namespace llamaos;
using namespace llamaos::xen;

/**
 * @brief void abort (void)
 *
 */
extern "C"
void llamaos_abort (void)
{
   trace ("glibc calling abort ()\n");

   Hypercall::sched_op_shutdown (SHUTDOWN_crash);
}

typedef void (*llamaos_abort_t) (void);
extern "C" int register_llamaos_abort (llamaos_abort_t);

/**
 * @brief int __brk (void *addr)
 *
 */
extern "C"
void *llamaos_brk (void *addr)
{
   trace ("glibc calling brk (%lx)\n", addr);

   return memory::set_program_break (addr);
}

typedef void *(*llamaos_brk_t) (void *);
extern "C" int register_llamaos_brk (llamaos_brk_t);

/**
 * @brief int __getpagesize (void)
 *
 */
extern "C"
int llamaos_getpagesize (void)
{
   trace ("glibc calling getpagesize ()\n");

   return LLAMAOS_PAGE_SIZE;
}

typedef int (*llamaos_getpagesize_t) (void);
extern "C" int register_llamaos_getpagesize (llamaos_getpagesize_t);

/**
 * @brief void __libc_fatal (const char *message)
 *
 */
extern "C"
void llamaos_libc_fatal (const char *message)
{
   trace ("glibc calling __libc_fatal (%s)\n", message);
}

typedef void (*llamaos_libc_fatal_t) (const char *);
extern "C" int register_llamaos_libc_fatal (llamaos_libc_fatal_t);

/**
 * @brief ssize_t __libc_write (int fd, const void *buf, size_t nbytes)
 *
 */
extern "C"
ssize_t llamaos_libc_write (int fd, const void *buf, size_t nbytes)
{
   trace ("glibc calling llamaos_libc_write (fd: %d, buf: ", fd);

   for (unsigned int i = 0; i < nbytes; i++)
   {
      trace ("%c", static_cast<const char *>(buf) [i]);
   }

   trace (", nbytes: %d)\n", nbytes);

   Hypervisor::get_instance ()->console.write (static_cast<const char *>(buf), nbytes);

   return nbytes;
}

typedef ssize_t (*llamaos_libc_write_t) (int, const void *, size_t);
extern "C" int register_llamaos_libc_write (llamaos_libc_write_t);

/**
 * @brief int madvise (__ptr_t addr, size_t len, int advice)
 *
 */
extern "C"
int llamaos_madvise (__ptr_t addr, size_t len, int advice)
{
   trace ("glibc calling madvise (%lx, %d, %d)\n", addr, len, advice);
   return 0;
}

typedef int (*llamaos_madvise_t) (__ptr_t, size_t, int);
extern "C" int register_llamaos_madvise (llamaos_madvise_t);

/**
 * @brief char * __getcwd (char *buf, size_t size)
 *
 */
extern "C"
char *llamaos_getcwd (char *buf, size_t size)
{
   trace ("glibc calling llamaos_getcwd (%lx, %d)\n", buf, size);

   if (size >= 2)
   {
      buf [0] = '/';
      buf [1] = '\0';

      return buf;
   }

   return 0;
}

typedef char *(*llamaos_getcwd_t) (char *, size_t);
extern "C" int register_llamaos_getcwd (llamaos_getcwd_t);

/**
 * @brief long int __pathconf (const char *path, int name)
 *
 */
extern "C"
long int llamaos_pathconf (const char *path, int name)
{
   trace ("glibc calling llamaos_pathconf (%lx, %d)\n", path, name);

   return 0;
}

typedef long int (*llamaos_pathconf_t) (const char *, int);
extern "C" int register_llamaos_pathconf (llamaos_pathconf_t);

/**
 * @brief off64_t __libc_lseek64 (int fd, off64_t offset, int whence)
 *
 */
off64_t llamaos_lseek64 (int fd, off64_t offset, int whence)
{
   trace ("glibc calling llamaos_lseek64 (%d, %lu, %d)\n", fd, offset, whence);

   return 0;
}

typedef off64_t (*llamaos_lseek64_t) (int, off64_t, int);
extern "C" int register_llamaos_lseek64 (llamaos_lseek64_t);

/**
 * @brief int poll (struct pollfd *fds, nfds_t nfds, int timeout)
 *
 */
int llamaos_poll (struct pollfd *fds, nfds_t nfds, int timeout)
{
   trace ("glibc calling llamaos_poll (%lx, %lx, %d)\n", fds, nfds, timeout);

   return 0;
}

typedef int (*llamaos_poll_t) (struct pollfd *, nfds_t, int);
extern "C" int register_llamaos_poll (llamaos_poll_t);

/**
 * @brief ssize_t __libc_read (int fd, void *buf, size_t nbytes)
 *
 */
ssize_t llamaos_read (int fd, void *buf, size_t nbytes)
{
   trace ("glibc calling read (%d, %lx, %lx)\n", fd, buf, nbytes);

   return -1;
}

typedef ssize_t (*llamaos_read_t) (int, void *, size_t);
extern "C" int register_llamaos_read (llamaos_read_t);

/**
 * @brief Initialize the glibc exports.
 *
 */
void register_glibc_exports ()
{
   register_llamaos_abort (llamaos_abort);
   register_llamaos_brk (llamaos_brk);
   register_llamaos_getpagesize (llamaos_getpagesize);
   register_llamaos_libc_fatal (llamaos_libc_fatal);
   register_llamaos_libc_write (llamaos_libc_write);
   register_llamaos_madvise (llamaos_madvise);
   register_llamaos_getcwd (llamaos_getcwd);
   register_llamaos_pathconf (llamaos_pathconf);
   register_llamaos_lseek64 (llamaos_lseek64);
   register_llamaos_poll (llamaos_poll);
   register_llamaos_read (llamaos_read);
}

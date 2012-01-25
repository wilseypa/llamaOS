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
//   trace ("glibc calling llamaos_libc_write (fd: %d, buf: ", fd);

//   for (unsigned int i = 0; i < nbytes; i++)
//   {
//      trace ("%c", static_cast<const char *>(buf) [i]);
//   }

//   trace (", nbytes: %d)\n", nbytes);

   if (stdout->_fileno == fd)
   {
      Hypervisor::get_instance ()->console.write (static_cast<const char *>(buf), nbytes);
      return nbytes;
   }

   return 0;
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



static inline uint64_t rdtsc ()
{
   uint32_t lo, hi;

   asm volatile ("rdtsc" : "=a" (lo), "=d" (hi));

   return (static_cast<uint64_t>(hi) << 32) | lo;
}

static inline uint64_t tsc_to_ns (const vcpu_time_info_t *time_info, uint64_t tsc)
{
   const uint64_t overflow = UINT64_MAX / time_info->tsc_to_system_mul;
   uint64_t time_ns = 0UL;

   uint64_t stsc = (time_info->tsc_shift < 0)
                 ? (tsc >> -time_info->tsc_shift) : (tsc << time_info->tsc_shift);

   // mul will overflow 64 bits
   while (stsc > overflow)
   {
      time_ns += ((overflow * time_info->tsc_to_system_mul) >> 32);
      stsc -= overflow;
   }

   time_ns += (stsc * time_info->tsc_to_system_mul) >> 32;

   return time_ns;
}

#define mb()  __asm__ __volatile__ ( "mfence" : : : "memory")

/**
 * @brief int __gettimeofday (struct timeval *tv, struct timezone *tz)
 *
 */
int llamaos_gettimeofday (struct timeval *tv, struct timezone * /* tz */)
{
   // trace ("glibc calling gettimeofday (%lx, %lx)\n", tv, tz);

   uint32_t wc_version = 0;
   uint32_t wc_sec = 0;
   uint32_t wc_nsec = 0;

   uint32_t version = 0;
   uint64_t tsc_timestamp = 0;
   uint64_t system_time = 0;

   shared_info_t *shared_info = Hypervisor::get_instance ()->shared_info;
   vcpu_time_info_t *time_info = &shared_info->vcpu_info [0].time;

   for (;;)
   {
      wc_version = shared_info->wc_version;
      version = time_info->version;
mb();
      if (   !(wc_version & 1)
          && !(version & 1))
      {
         wc_sec = shared_info->wc_sec;
         wc_nsec = shared_info->wc_nsec;
         tsc_timestamp = time_info->tsc_timestamp;
         system_time = time_info->system_time;
mb();

         if (   (wc_version == shared_info->wc_version)
             && (version == time_info->version))
         {
            break;
         }
      }
   }

   uint64_t tsc = rdtsc () - tsc_timestamp;
   uint64_t nsec = tsc_to_ns (time_info, tsc);

   nsec += system_time;

   wc_sec += (nsec / 1000000000UL);
   wc_nsec += (nsec % 1000000000UL);

   if (wc_nsec > 1000000000UL)
   {
      wc_sec += 1;
      wc_nsec -= 1000000000UL;
   }

   tv->tv_sec = wc_sec;
   tv->tv_usec = wc_nsec / 1000;

   return 0;
}

typedef int (*llamaos_gettimeofday_t) (struct timeval *, struct timezone *);
extern "C" int register_llamaos_gettimeofday (llamaos_gettimeofday_t);

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
   register_llamaos_gettimeofday (llamaos_gettimeofday);
}

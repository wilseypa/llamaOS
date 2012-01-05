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

#include <stdexcept>
#include <sstream>

#include <xen/xen.h>
#include <xen/sched.h>

#include <llamaos/xen/Hypercall.h>
#include <llamaos/xen/Hypervisor.h>
#include <llamaos/xen/Memory.h>
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

namespace {
   static int registered_abort = register_llamaos_abort (llamaos_abort);
}

/**
 * @brief int __brk (void *addr)
 *
 */
extern "C"
void *llamaos_brk (void *addr)
{
   trace ("glibc calling brk (%lx)\n", addr);

   return Hypervisor::get_instance ()->memory.brk (addr);
}

typedef void *(*llamaos_brk_t) (void *);
extern "C" int register_llamaos_brk (llamaos_brk_t);

namespace {
   static int registered_brk = register_llamaos_brk (llamaos_brk);
}

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

namespace {
   static int registered_getpagesize = register_llamaos_getpagesize (llamaos_getpagesize);
}

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

namespace {
   static int registered_libc_fatal = register_llamaos_libc_fatal (llamaos_libc_fatal);
}

/**
 * @brief ssize_t __libc_write (int fd, const void *buf, size_t nbytes)
 *
 */
static char libc_write_buffer [256];
extern "C"
ssize_t llamaos_libc_write (int fd, const void *buf, size_t nbytes)
{
   if (1 == fd)
   {
      unsigned int i = 0;

      while (   (i < nbytes)
             && (i < 256))
      {
         libc_write_buffer [i] = ((const char *)buf) [i];
      }

      libc_write_buffer [i] = '\0';
      return trace (libc_write_buffer);
   }

   return 0;
}

typedef ssize_t (*llamaos_libc_write_t) (int, const void *, size_t);
extern "C" int register_llamaos_libc_write (llamaos_libc_write_t);

namespace {
   static int registered_libc_write = register_llamaos_libc_write (llamaos_libc_write);
}













extern "C"
int madvise (__ptr_t addr, size_t len, int advice)
{
   trace ("glibc calling madvise (%lx, %d, %d)\n", addr, len, advice);
   return 0;
}

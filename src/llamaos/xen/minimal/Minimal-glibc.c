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

#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include <xen/xen.h>

#include <llamaos/xen/Hypercall-macros.h>
#include <llamaos/llamaOS.h>

// runtime stack memory
char RUNTIME_STACK [2 * LLAMAOS_STACK_SIZE];

static int verify_magic (const start_info_t *start_info)
{
   if (   (0 != start_info)
       && (0 == strncmp (start_info->magic, "xen-", 4)))
   {
      return 1;
   }

   return 0;
}

static char buffer [512] = { '\0' };

static int trace (const char *format, ...)
{
   // prep variable arguments
   va_list arg;
   va_start (arg, format);

   // copy formatted output to buffer
   int count = vsnprintf (buffer, sizeof(buffer)-1, format, arg);

   // term variable arguments
   va_end (arg);

   // write buffer to system output/log
   // xen::Hypercall::console_io (buffer);
   HYPERVISOR_console_io(CONSOLEIO_write, strlen(buffer), buffer);

   // return the number characters written
   return count;
}

static int ctrace (char *message)
{
   return HYPERVISOR_console_io(CONSOLEIO_write, strlen(message), message);
}

static void trace_startup (const start_info_t *start_info)
{
   trace ("\n\n\n*********************************\n");
   trace (      "****  starting llamaOS (Xen)  ***\n");
   trace (      "*********************************\n\n\n");

   trace ("%s\n\n", LLAMAOS_VERSION_TEXT);

   trace ("=== start_info ===\n");
   trace ("  magic: %s\n", start_info->magic);
   trace ("  nr_pages: %x\n", start_info->nr_pages);
   trace ("  shared_info: %x\n", start_info->shared_info);
   trace ("  flags: %x\n", start_info->flags);
   trace ("  store_mfn: %x\n", start_info->store_mfn);
   trace ("  store_evtchn: %x\n", start_info->store_evtchn);
   trace ("  console.domU.mfn: %x\n", start_info->console.domU.mfn);
   trace ("  console.domU.evtchn: %x\n", start_info->console.domU.evtchn);
   trace ("  pt_base: %x\n", start_info->pt_base);
   trace ("  nr_pt_frames: %x\n", start_info->nr_pt_frames);
   trace ("  mfn_list: %x\n", start_info->mfn_list);
   trace ("  mod_start: %x\n", start_info->mod_start);
   trace ("  mod_len: %x\n", start_info->mod_len);
   trace ("  cmd_line: %s\n", start_info->cmd_line);
   trace ("  first_p2m_pfn: %x\n", start_info->first_p2m_pfn);
   trace ("  nr_p2m_frames: %x\n", start_info->nr_p2m_frames);
   trace ("\n");
}

void llamaos_exit (int status)
{
   ctrace ("glibc calling llamaos_exit ()\n");

   for(;;);
}

typedef void (*llamaos_exit_t) (int);
void register_llamaos_exit (llamaos_exit_t);

char *llamaos_getcwd (char *buf, size_t size)
{
   ctrace ("glibc calling llamaos_getcwd ()\n");

   if (size >= 2)
   {
      buf [0] = '/';
      buf [1] = '\0';

      return buf;
   }

   return 0;
}

typedef char *(*llamaos_getcwd_t) (char *, size_t);
void register_llamaos_getcwd (llamaos_getcwd_t);

void llamaos_libc_fatal (const char *message)
{
   ctrace ("glibc calling libc_fatal ()\n");
}

typedef void (*llamaos_libc_fatal_t) (const char *);
void register_llamaos_libc_fatal (llamaos_libc_fatal_t);

int llamaos_libc_open (const char *format, int flags)
{
   ctrace ("glibc calling libc_open ()\n");
   return 0;
}

typedef int (*llamaos_libc_open_t) (const char *, int);
void register_llamaos_libc_open (llamaos_libc_open_t);

int llamaos_madvise (__ptr_t addr, size_t len, int advice)
{
   ctrace ("glibc calling madvise ()\n");
   return 0;
}

typedef int (*llamaos_madvise_t) (__ptr_t, size_t, int);
void register_llamaos_madvise (llamaos_madvise_t);

long int llamaos_pathconf (const char *path, int name)
{
   ctrace ("glibc calling llamaos_pathconf ()\n");

   return 0;
}

typedef long int (*llamaos_pathconf_t) (const char *, int);
void register_llamaos_pathconf (llamaos_pathconf_t);

int llamaos_raise (int sig)
{
   ctrace ("glibc calling llamaos_raise ()\n");

   return 0;
}

typedef int (*llamaos_raise_t) (int);
void register_llamaos_raise (llamaos_raise_t);

void register_glibc_exports ()
{
   register_llamaos_exit (llamaos_exit);
   register_llamaos_getcwd (llamaos_getcwd);
   register_llamaos_libc_fatal (llamaos_libc_fatal);
   register_llamaos_libc_open (llamaos_libc_open);
   register_llamaos_madvise (llamaos_madvise);
   register_llamaos_pathconf (llamaos_pathconf);
   register_llamaos_raise (llamaos_raise);
}

void minimal_c_kernel (start_info_t *start_info)
{
   if (verify_magic (start_info))
   {
      // make sure hypercalls are working
      ctrace ("\n\nStarting minimal-C Xen guest...\n\n");

      // print the info given from Xen
      trace_startup (start_info);

      // enable dynamic memory
      

      trace ("registering llamaOS glibc call-backs...\n");
      register_glibc_exports ();

      // loop forever
      for (;;);
   }

   // error finding memory, so just leave
}

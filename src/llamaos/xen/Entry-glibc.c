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

#include <stdint.h>
#include <string.h>

#include <xen/xen.h>

#include <llamaos/xen/Entry-gcc.h>
#include <llamaos/xen/Entry-glibc.h>
#include <llamaos/xen/Export-glibc.h>
#include <llamaos/xen/Hypercall-macros.h>
#include <llamaos/llamaOS.h>
#include <llamaos/Trace.h>

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

static void trace_startup (const start_info_t *start_info)
{
   trace ("\n\n\n**********************************\n");
   trace (      "****  Starting llamaOS (Xen)  ****\n");
   trace (      "**********************************\n\n\n");

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

static void glibc_exit (int status)
{
   trace("!!! ALERT: glibc calling exit().\n");

   sched_shutdown_t arg;
   arg.reason = SHUTDOWN_poweroff;
   HYPERVISOR_sched_op(SCHEDOP_shutdown, &arg);
}

static long int glibc_get_avphys_pages (void)
{
   trace("!!! ALERT: glibc calling get_avphys_pages() before memory management is enabled.\n");
   return -1;
}

static int glibc_get_nprocs (void)
{
   trace("!!! ALERT: glibc calling get_nprocs().\n");
   return 1;
}

static int glibc_get_nprocs_conf (void)
{
   trace("!!! ALERT: glibc calling get_nprocs_conf().\n");
   return 1;
}

static long int glibc_get_phys_pages (void)
{
   trace("!!! ALERT: glibc calling get_phys_pages() before memory management is enabled.\n");
   return -1;
}

static char *glibc_getcwd (char *buf, size_t size)
{
   trace("!!! ALERT: glibc calling getcwd() before file system support is enabled.\n");

   if (   (buf != 0)
       && (size >= 2))
   {
      buf [0] = '/';
      buf [1] = '\0';

      return buf;
   }

   return 0;
}

static void glibc_libc_fatal (const char *message)
{
   trace("!!! ALERT: glibc calling libc_fatal().\n");
   trace("           %s\n", message);

   sched_shutdown_t arg;
   arg.reason = SHUTDOWN_crash;
   HYPERVISOR_sched_op(SCHEDOP_shutdown, &arg);
}

static int glibc_libc_open (const char *file, int oflag)
{
   trace("!!! ALERT: glibc calling libc_open() before file system support is enabled.\n");
   return -1;
}

static int glibc_madvise (__ptr_t addr, size_t len, int advice)
{
   trace("!!! ALERT: glibc calling madvise() before memory management is enabled.\n");
   return -1;
}

static long int glibc_pathconf (const char *path, int name)
{
   trace("!!! ALERT: glibc calling pathconf() before file system support is enabled.\n");
   return -1;
}

static int glibc_raise (int sig)
{
   trace("!!! ALERT: glibc calling raise() before signal support is enabled.\n");
   return -1;
}

static int glibc_sched_get_priority_max (int algorithm)
{
   trace("!!! ALERT: glibc calling sched_get_priority_max() before threading support is enabled.\n");
   return -1;
}

static int glibc_sched_get_priority_min (int algorithm)
{
   trace("!!! ALERT: glibc calling sched_get_priority_min() before threading support is enabled.\n");
   return -1;
}

static int glibc_sigsuspend (const sigset_t *set)
{
   trace("!!! ALERT: glibc calling sigsuspend() before signal support is enabled.\n");
   return -1;
}

static int glibc_sigsuspend_nocancel (const sigset_t *set)
{
   trace("!!! ALERT: glibc calling sigsuspend_nocancel() before signal support is enabled.\n");
   return -1;
}

static long int glibc_syscall (long int callno)
{
   trace("!!! ALERT: glibc calling syscall() before syscall support is enabled.\n");
   return -1;
}

static ssize_t glibc_libc_write (int fd, const void *buf, size_t nbytes)
{
   trace("!!! ALERT: glibc calling libc_write() before file system support is enabled.\n");
   return -1;
}

static void register_glibc_exports (void)
{
   register_llamaos_exit (glibc_exit);
   register_llamaos_get_avphys_pages (glibc_get_avphys_pages);
   register_llamaos_get_nprocs (glibc_get_nprocs);
   register_llamaos_get_nprocs_conf (glibc_get_nprocs_conf);
   register_llamaos_get_phys_pages (glibc_get_phys_pages);
   register_llamaos_getcwd (glibc_getcwd);
   register_llamaos_libc_fatal (glibc_libc_fatal);
   register_llamaos_libc_open (glibc_libc_open);
   register_llamaos_madvise (glibc_madvise);
   register_llamaos_pathconf (glibc_pathconf);
   register_llamaos_raise (glibc_raise);
   register_llamaos_sched_get_priority_max (glibc_sched_get_priority_max);
   register_llamaos_sched_get_priority_min (glibc_sched_get_priority_min);
   register_llamaos_sigsuspend (glibc_sigsuspend);
   register_llamaos_sigsuspend_nocancel (glibc_sigsuspend_nocancel);
   register_llamaos_syscall (glibc_syscall);
   register_llamaos_write (glibc_libc_write);
}

// entry function called from Entry.S
void entry_glibc (start_info_t *start_info)
{
   // check to make sure the initial memory is good
   if (verify_magic (start_info))
   {
      // print the info given from Xen
      trace_startup (start_info);

      // register our export functions with glibc
      trace ("registering llamaOS glibc exports...\n");
      register_glibc_exports ();

      // initialize glibc
      // libc_init_first();

      // call the C++ entry function
      entry_gcc (start_info);

      // cleanup glibc

      // shutdown the hypervisor
   }
   // else
   // !!! ERROR finding Xen memory, so just quietly leave !!!
}

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

#include <xen/features.h>
#include <xen/version.h>
#include <xen/xen.h>

#include <llamaos/xen/Entry-gcc.h>
#include <llamaos/xen/Entry-glibc.h>
#include <llamaos/xen/Export-glibc.h>
#include <llamaos/xen/Hypercall-macros.h>
#include <llamaos/llamaOS.h>
#include <llamaos/Trace.h>

// runtime stack memory
// char RUNTIME_STACK [2 * LLAMAOS_STACK_SIZE];

// static int verify_magic (const start_info_t *start_info)
// {
//   if (   (0 != start_info)
//       && (0 == strncmp (start_info->magic, "xen-", 4)))
//   {
//      return 1;
//   }
//
//   return 0;
//}

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

static void glibc_abort (void)
{
   trace("!!! ALERT: glibc calling abort().\n");

   sched_shutdown_t arg;
   arg.reason = SHUTDOWN_crash;
   HYPERVISOR_sched_op(SCHEDOP_shutdown, &arg);
}

int glibc_access (const char *file, int type)
{
   if (strcmp (file, "fort.6") == 0)
   {
      return 0;
   }

   trace("!!! ALERT: glibc calling access() before file system support is enabled.\n");
   trace (" file %s, %x\n", file, type);

   errno = ENOENT;
   return -1;
}

static void *glibc_brk (void *addr)
{
   trace("!!! ALERT: glibc calling brk() before memory management is enabled.\n");
   return 0;
}

static int glibc_close (int fd)
{
   trace("!!! ALERT: glibc calling close() on %d.\n", fd);
   return 0;
}

static int glibc_dup (int fd)
{
   trace("!!! ALERT: glibc calling dup() on %d.\n", fd);

   errno = EBADF;
   return -1;
}

static int glibc_dup2 (int fd, int fd2)
{
   trace("!!! ALERT: glibc calling dup2() on %d and %d.\n", fd, fd2);

   errno = EBADF;
   return -1;
}

static void glibc_exit (int status)
{
   trace("!!! ALERT: glibc calling exit().\n");

   sched_shutdown_t arg;
   arg.reason = SHUTDOWN_poweroff;
   HYPERVISOR_sched_op(SCHEDOP_shutdown, &arg);
}

static int glibc_ftruncate (int fd, off_t length)
{
   if (fd == 6)
   {
      return 0;
   }

   trace("!!! ALERT: glibc calling glibc_ftruncate() %d, %d.\n", fd, length);
   return 0;
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

static int glibc_getpagesize (void)
{
   return LLAMAOS_PAGE_SIZE;
}

static long int glibc_get_phys_pages (void)
{
   trace("!!! ALERT: glibc calling get_phys_pages() before memory management is enabled.\n");
   return -1;
}

static char *glibc_getcwd (char *buf, size_t size)
{
   if (   (buf != 0)
       && (size >= 2))
   {
      buf [0] = '/';
      buf [1] = '\0';

      return buf;
   }

   trace("!!! ALERT: glibc calling getcwd() before file system support is enabled.\n");
   return 0;
}

static int glibc_getpid (void)
{
   trace("!!! ALERT: glibc calling getpid() before system support is enabled.\n");
   return -1;
}

static int glibc_gettimeofday (struct timeval *tv, struct timezone *tz)
{
   trace("!!! ALERT: glibc calling gettimeofday() before support is enabled.\n");
   return -1;
}

static int glibc_isatty (int fd)
{
   trace("!!! ALERT: glibc calling isatty().\n");
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
   if (strcmp (file, "fort.6") == 0)
   {
      return 6;
   }

   trace("!!! ALERT: glibc calling libc_open() before file system support is enabled.\n");
   trace (" opening file %s, %x\n", file, oflag);

   errno = ENOENT;
   return -1;
}

static off_t glibc_lseek (int fd, off_t offset, int whence)
{
   if (fd == 6)
   {
      return offset;
   }

   trace("!!! ALERT: glibc calling lseek() before file system support is enabled.\n");
   trace ("   fd: %d, offset: %d, whence: %d\n", fd, offset, whence);
   return -1;
}

static off64_t glibc_lseek64 (int fd, off64_t offset, int whence)
{
   trace("!!! ALERT: glibc calling lseek64() before file system support is enabled.\n");
   return -1;
}

static int glibc_lxstat64 (int vers, const char *file, struct stat64 *buf)
{
   trace("!!! ALERT: glibc calling lxstat64() before file system support is enabled.\n");
   trace ("  vers: %d, file: %s\n", vers, file);
   return -1;
}

static int glibc_madvise (__ptr_t addr, size_t len, int advice)
{
   trace("!!! ALERT: glibc calling madvise() before memory management is enabled.\n");
   return -1;
}

static int glibc_mkdir (const char *path, mode_t mode)
{
   trace("!!! ALERT: glibc calling mkdir() before file system support is enabled.\n");
   return -1;
}

static long int glibc_pathconf (const char *path, int name)
{
   trace("!!! ALERT: glibc calling pathconf() before file system support is enabled.\n");
   return -1;
}

static int glibc_poll (struct pollfd *fds, nfds_t nfds, int timeout)
{
   trace("!!! ALERT: glibc calling poll() before file system support is enabled.\n");
   return -1;
}

static int glibc_raise (int sig)
{
   trace("!!! ALERT: glibc calling raise() before signal support is enabled.\n");
   return -1;
}

static ssize_t glibc_read (int fd, void *buf, size_t nbytes)
{
   trace("!!! ALERT: glibc calling read() before file system support is enabled.\n");
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

static unsigned int glibc_sleep (unsigned int seconds)
{
   trace("!!! ALERT: glibc calling sleep() before sleep support is enabled.\n");
   return -1;
}

static long int glibc_syscall (long int callno)
{
   trace("!!! ALERT: glibc calling syscall() before syscall support is enabled.\n");
   return -1;
}

static int glibc_unlink (const char *name)
{
   trace("!!! ALERT: glibc calling unlink() before file system support is enabled.\n");
   trace (" unlinking file %s\n", name);

   errno = ENOENT;
   return -1;
}

static ssize_t glibc_libc_write (int fd, const void *buf, size_t nbytes)
{
   trace("!!! ALERT: glibc calling libc_write() before file system support is enabled.\n");
   return -1;
}

static ssize_t glibc_writev (int fd, const struct iovec *vector, int count)
{
   trace("!!! ALERT: glibc calling writev() before file system support is enabled.\n");
   return -1;
}

static int glibc_xstat (int vers, const char *file, struct stat *buf)
{
   trace("!!! ALERT: glibc calling xstat() before file system support is enabled.\n");
   trace ("  vers: %d, file: %s\n", vers, file);
   return -1;
}

static int glibc_xstat64 (int vers, const char *file, struct stat64 *buf)
{
   trace("!!! ALERT: glibc calling xstat64() before file system support is enabled.\n");
   trace ("  vers: %d, file: %s\n", vers, file);
   return -1;
}

static void register_glibc_exports (void)
{
   register_llamaos_abort (glibc_abort);
   register_llamaos_access (glibc_access);
   register_llamaos_brk (glibc_brk);
   register_llamaos_close (glibc_close);
   register_llamaos_dup (glibc_dup);
   register_llamaos_dup2 (glibc_dup2);
   register_llamaos_exit (glibc_exit);
   register_llamaos_ftruncate (glibc_ftruncate);
   register_llamaos_get_avphys_pages (glibc_get_avphys_pages);
   register_llamaos_get_nprocs (glibc_get_nprocs);
   register_llamaos_get_nprocs_conf (glibc_get_nprocs_conf);
   register_llamaos_getpagesize (glibc_getpagesize);
   register_llamaos_get_phys_pages (glibc_get_phys_pages);
   register_llamaos_getcwd (glibc_getcwd);
   register_llamaos_getpid (glibc_getpid);
   register_llamaos_gettimeofday (glibc_gettimeofday);
   register_llamaos_isatty (glibc_isatty);
   register_llamaos_libc_fatal (glibc_libc_fatal);
   register_llamaos_libc_open (glibc_libc_open);
   register_llamaos_lseek (glibc_lseek);
   register_llamaos_lseek64 (glibc_lseek64);
   register_llamaos_lxstat64 (glibc_lxstat64);
   register_llamaos_madvise (glibc_madvise);
   register_llamaos_mkdir (glibc_mkdir);
   register_llamaos_pathconf (glibc_pathconf);
   register_llamaos_poll (glibc_poll);
   register_llamaos_raise (glibc_raise);
   register_llamaos_read (glibc_read);
   register_llamaos_sched_get_priority_max (glibc_sched_get_priority_max);
   register_llamaos_sched_get_priority_min (glibc_sched_get_priority_min);
   register_llamaos_sigsuspend (glibc_sigsuspend);
   register_llamaos_sigsuspend_nocancel (glibc_sigsuspend_nocancel);
   register_llamaos_sleep (glibc_sleep);
   register_llamaos_syscall (glibc_syscall);
   register_llamaos_unlink (glibc_unlink);
   register_llamaos_write (glibc_libc_write);
   register_llamaos_writev (glibc_writev);
   register_llamaos_xstat (glibc_xstat);
   register_llamaos_xstat64 (glibc_xstat64);
}

#define MXCSR_DEFAULT 0x1f80

static void fpu_init(void)
{
   unsigned long val = MXCSR_DEFAULT;
   asm volatile ( "fninit; ldmxcsr %0" : : "m" (val) );
}

static char cmd_line [MAX_GUEST_CMDLINE];
static int argc;
static char *argv [64];
static char *name = "llamaOS";

int __libc_start_main (int (*main) (int, char **, char **),
                       int argc,
                       char ** ubp_av,
                       __typeof (main) init,
                       void (*fini) (void),
                       void (*rtld_fini) (void),
                       void *stack_end);// __attribute__ ((noreturn));

extern void *stack_bottom;

uint8_t xen_features[XENFEAT_NR_SUBMAPS * 32];

void setup_xen_features(void)
{
    xen_feature_info_t fi;
    int i, j;

    for (i = 0; i < XENFEAT_NR_SUBMAPS; i++) 
    {
        fi.submap_idx = i;
        if (HYPERVISOR_xen_version(XENVER_get_features, &fi) < 0)
            break;
        
        for (j=0; j<32; j++)
            xen_features[i*32+j] = !!(fi.submap & 1<<j);
    }
}

static start_info_t local_start_info;

// entry function called from Entry.S
void entry_glibc (start_info_t *start_info)
{
   // check to make sure the start_info_t is valid
   // at check for the magic string
   if (   (0 != start_info)
       && ('x' == start_info->magic [0])
       && ('e' == start_info->magic [1])
       && ('n' == start_info->magic [2])
       && ('-' == start_info->magic [3]))
   {
      // put this is assembly *.S
      fpu_init ();

      setup_xen_features ();

      // register our export functions with glibc
      register_glibc_exports ();

      // Before calling anything from glibc, call the startup
      // to initialize the library. We need the command line args
      // for this, which are stored as a string in the start_info
      argv [argc++] = name;
      int space = 0;

      for (int i = 0; i < MAX_GUEST_CMDLINE; i++)
      {
         cmd_line [i] = start_info->cmd_line [i];

         if (cmd_line [i] == '\0')
         {
            break;
         }
         else if (   (cmd_line [i] != ' ')
                  && (space))
         {
            argv [argc++] = &cmd_line [i];
            space = 0;
         }
         else
         {
            space = 1;
         }
      }

      // initialize the c-runtime library
      __libc_start_main(0, argc, argv, 0, 0, 0, stack_bottom);

      memcpy(&local_start_info, start_info, sizeof(start_info_t));
      // print the info given from Xen
      trace_startup (&local_start_info);

      // call the C++ entry function
      entry_gcc (&local_start_info);

      // cleanup glibc
   }
   // else
   // !!! ERROR finding Xen memory, so just quietly leave !!!
}

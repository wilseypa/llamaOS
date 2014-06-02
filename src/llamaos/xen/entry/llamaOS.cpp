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

#define __STDC_LIMIT_MACROS
#include <cerrno>
#include <cstdint>
#include <cstring>

#include <algorithm>
#include <iostream>
#include <iterator>
#include <sstream>
#include <vector>

#include <xen/xen.h>
#include <xen/features.h>

#include <llamaos/api/sleep.h>
#include <llamaos/memory/Memory.h>
#include <llamaos/xen/Export-glibc.h>
#include <llamaos/xen/Grant_map.h>
#include <llamaos/xen/Hypervisor.h>
#include <llamaos/llamaOS.h>
#include <llamaos/Trace.h>

#include <llamaos/xen/fs/ext2/vfs.h>

using namespace std;
using namespace llamaos;
using namespace llamaos::xen;

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

static void glibc_abort (void)
{
   cout << "!!! ALERT: glibc calling abort()." << endl;
   cout.flush();
   fflush(stdout);
   for(;;);
}

static void glibc_exit (int status)
{
   cout << "!!! ALERT: glibc calling exit(" << status << ")." << endl;
   cout.flush();
   fflush(stdout);
   for(;;);

//   sched_shutdown_t arg;
//   arg.reason = SHUTDOWN_poweroff;
//   HYPERVISOR_sched_op(SCHEDOP_shutdown, &arg);
}

static int glibc_gethostname (char *name, size_t len)
{
   cout << "calling gethostname...";
   stringstream ss;
   ss << Hypervisor::get_instance ()->name << "." << Hypervisor::get_instance ()->domid;

   if ((ss.str().size() + 1) > len)
   {
      errno = ENAMETOOLONG;
      return -1;
   }

//   memcpy(name, ss.str().c_str(), len < ss.str().size() + 1);
   strcpy(name, ss.str().c_str());
   cout << name << endl;
   return 0;
}

static int glibc_getpid ()
{
   return Hypervisor::get_instance ()->domid;
}

static uid_t glibc_getuid ()
{
   return 0;
}

static int glibc_gettimeofday (struct timeval *tv, struct timezone * /* tz */)
{
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

static unsigned int glibc_libc_sleep (unsigned int seconds)
{
   api::sleep (seconds);
   return 0;
}

static stringstream np_out;

static int glibc_libc_open (const char *file, int oflag)
{
//   cout << "glibc_libc_open: " << file << ", " << oflag << endl;
   if (strcmp (file, "fort.6") == 0)
   {
      return 6;
   }
   else if (   (strcmp (file, "np.out") == 0)
            || (strcmp (file, "hpccoutf.txt") == 0))
   {
      return 10;
   }
   else if (strcmp (file, "shmem-mpich-0") == 0)
   {
      return Hypervisor::get_instance ()->shared_memory->open(file);
   }
   else if (strncmp(file, "/dev/shm/mpich_shar_", 20) == 0)
   {
      cout << "fd = " << Hypervisor::get_instance ()->shared_memory->open(file) << endl;

      return Hypervisor::get_instance ()->shared_memory->open(file);
   }
   else
   {
      int fd = fs_open (file, oflag);

      return (fd < 0) ? fd : fd+100;
   }

//   trace("!!! ALERT: glibc calling libc_open() before file system support is enabled.\n");
   trace (" opening file %s, %x\n", file, oflag);

   errno = ENOENT;
   return -1;
}

static int glibc_close (int fd)
{
   trace("!!! ALERT: glibc calling close() on %d.\n", fd);

   if (fd == 10)
   {
      cout << "np.out:" << endl;
      cout << np_out.str() << endl;
   }
   else if (fd < 200)
   {
      if (fd >= 100)
      {
         return fs_close (fd-100);
      }
   }

   return 0;
}

static ssize_t glibc_read (int fd, void *buf, size_t nbytes)
{
   if (fd < 200)
   {
      if (fd >= 100)
      {
         return fs_read (fd-100, buf, nbytes);
      }
   }

  cout << "Alert: reading from fileno " << fd << ", " << nbytes << " bytes" << endl;
  return -1;
}

static ssize_t glibc_write (int fd, const void *buf, size_t nbytes)
{
   if (   (stdout->_fileno != fd)
       && (stderr->_fileno != fd)
       && (6 != fd)                     // fortran uses 6 for alt std output
       && (10 != fd))                    // fortran uses 6 for alt std output
   {
      cout << "Alert: writing to fileno " << fd << ", " << nbytes << " bytes" << endl;
   }

   if (fd == 10)
   {
      for (size_t i = 0; i < nbytes; i++)
      {
         np_out << static_cast<const char *>(buf) [i];
      }
   }
   else if (fd >= 200)
   {
      cout << "Alert: writing to fileno " << fd << ", " << nbytes << " bytes" << endl;

      memcpy(Hypervisor::get_instance ()->shared_memory->get(fd), buf, nbytes);
   }
   else if (fd >= 100)
   {
      // put write call here
      return fs_write (fd-100, buf, nbytes);
   }
   else
   {
      Hypervisor::get_instance ()->console.write (static_cast<const char *>(buf), nbytes);
   }

   return nbytes;
}

static off_t glibc_lseek (int fd, off_t offset, int whence)
{
   if (fd == 6)
   {
      return offset;
   }
   else if (fd == 12)
   {
      cout << "glibc_lseek: " << offset << ", " << whence << endl;
      return offset;
   }

   cout << "lseek " << fd << ", " << offset << ", " << whence << endl;

   if (fd < 200)
   {
      if (fd >= 100)
      {
         return fs_lseek (fd-100, offset, whence);
      }
   }

   trace("!!! ALERT: glibc calling lseek() before file system support is enabled.\n");
   trace ("   fd: %d, offset: %d, whence: %d\n", fd, offset, whence);
   return -1;
}

static off64_t glibc_lseek64 (int fd, off64_t offset, int whence)
{
   if (fd == 10)
   {
      switch (whence)
      {
      default:
      case SEEK_SET:
      case SEEK_CUR:
      case SEEK_END:
         break;
      }

      return np_out.str().size();
   }

   if (fd < 200)
   {
      if (fd >= 100)
      {
         return fs_lseek (fd-100, offset, whence);
      }
   }

   trace("!!! ALERT: glibc calling lseek64() before file system support is enabled.\n");
   return -1;
}

static __ptr_t glibc_mmap (__ptr_t /* addr */, size_t len, int /* prot */, int /* flags */, int fd, off_t /* offset */)
{
   if (fd >= 200)
   {
      cout << "glibc_mmap: " << fd << ", " << len << endl;
      return Hypervisor::get_instance ()->shared_memory->map(fd, len);
//      return static_cast<__ptr_t>(pshmem);
   }
   else if (fd == 12)
   {
//      cout << "glibc_mmap: " << fd << ", " << len <<  ", " << hex << (uint64_t)pshmem << endl;
//      return static_cast<__ptr_t>(pshmem);
   }

   return reinterpret_cast<__ptr_t>(-1);
}

static int glibc_unlink (const char *name)
{
   if (strncmp(name, "/dev/shm/mpich_shar_", 20) == 0)
   {
      cout << "glibc_unlink: " << name << endl;
      return 0;
   }

   errno = ENOENT;
   return -1;
}

static int glibc_munmap (__ptr_t /* addr */, size_t /* len */)
{
   return 0;
}

static void register_glibc_exports (void)
{
   register_llamaos_abort (glibc_abort);
   register_llamaos_exit (glibc_exit);
   register_llamaos_gethostname (glibc_gethostname);
   register_llamaos_getpid (glibc_getpid);
   register_llamaos_getuid (glibc_getuid);
   register_llamaos_gettimeofday (glibc_gettimeofday);
   register_llamaos_sleep (glibc_libc_sleep);
   register_llamaos_close (glibc_close);
   register_llamaos_libc_open (glibc_libc_open);
   register_llamaos_read (glibc_read);
   register_llamaos_write (glibc_write);
   register_llamaos_lseek (glibc_lseek);
   register_llamaos_lseek64 (glibc_lseek64);
   register_llamaos_mmap (glibc_mmap);
   register_llamaos_unlink (glibc_unlink);
   register_llamaos_munmap (glibc_munmap);
}

static vector<string> split (const string &input)
{
   vector<string> tokens;

   string::const_iterator first = input.begin ();
   string::const_iterator mark = input.begin ();
   string::const_iterator last = input.end ();

   while (first != last)
   {
      if (isspace (*first))
      {
         string token = string (mark, first);

         if (token.length () > 0)
         {
            tokens.push_back (token);
         }

         mark = first + 1;
      }

      first++;
   }

   string token = string (mark, first);

   if (token.length () > 0)
   {
      tokens.push_back (token);
   }

   return tokens;
}

extern "C"
int main (int argc, char *argv []);

extern "C"
int __main (int argc, char *argv [], char * /* env[] */)
{
   return main (argc, argv);
}

void entry_llamaOS (start_info_t *start_info)
{
//   try
   {
      // create the one and only hypervisor object
      trace ("Creating Hypervisor...\n");

      Hypervisor *hypervisor = new Hypervisor (start_info);
      register_glibc_exports ();
      hypervisor->initialize ();

      // read and create args
      string cmd_line (reinterpret_cast<char *>(start_info->cmd_line));
      vector<string> args = split (cmd_line);

      trace ("args size is %d\n", args.size ());
      for (unsigned int i = 0; i < args.size (); i++)
      {
         trace ("argv [%d] = %s\n", i, args [i].c_str ());
      }

      hypervisor->argc = static_cast<int>(args.size () + 1);
      hypervisor->argv [0] = const_cast<char *>(hypervisor->name.c_str ());

      for (unsigned int i = 0; i < args.size (); i++)
      {
         hypervisor->argv [i+1] = const_cast<char *>(args [i].c_str ());
      }

      fs_initialize ();

// static char *pshmem = nullptr;
//      int node = atoi(hypervisor->argv [1]);

//      if (node > 0)
//      {
//         node--;
//         Grant_map<char> shmem (hypervisor->domid-1-node, 16383 - (node * 1024), 1024);
//         pshmem = shmem.get_pointer ();
//      }

      trace ("Before application main()...\n");

      main (hypervisor->argc, hypervisor->argv);

      // get rid of all leftover console buffer
      cout.flush ();
      fflush (stdout);

      trace ("After application main()...\n");
      cout << "program break: " << memory::get_program_break () << endl;
      api::sleep(1);

      delete hypervisor;
   }
//   catch (const std::runtime_error &e)
//   {
//      trace ("*** runtime_error: %s ***\n", e.what ());
//   }
//   catch (...)
//   {
//      trace ("*** unknown exception ***\n");
//   }
}

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

#include <cstdint>
#include <cstring>

#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>

#include <xen/xen.h>
#include <xen/features.h>

#include <llamaos/api/sleep.h>
#include <llamaos/memory/Memory.h>
#include <llamaos/xen/Export-glibc.h>
#include <llamaos/xen/Hypervisor.h>
#include <bits/stringfwd.h>
#include <llamaos/llamaOS.h>
#include <llamaos/Trace.h>

using namespace std;
using namespace llamaos;
using namespace llamaos::xen;

uint8_t xen_features [XENFEAT_NR_SUBMAPS * 32];

static void *glibc_brk (void *addr)
{
   trace ("glibc calling brk (%lx)\n", addr);

   return memory::set_program_break (addr);
}

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

static int glibc_getpid ()
{
   return Hypervisor::get_instance ()->domid;
}

static int glibc_gettimeofday (struct timeval *tv, struct timezone *tz)
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

static ssize_t glibc_libc_write (int fd, const void *buf, size_t nbytes)
{
   if (stdout->_fileno == fd)
   {
      Hypervisor::get_instance ()->console.write (static_cast<const char *>(buf), nbytes);
      return nbytes;
   }

   return -1;
}

static void register_glibc_exports (void)
{
   register_llamaos_brk (glibc_brk);
   register_llamaos_getpid (glibc_getpid);
   register_llamaos_gettimeofday (glibc_gettimeofday);
   register_llamaos_write (glibc_libc_write);
}

extern "C"
int main (int argc, char *argv []);

static vector<string> split (const string &input)
{
   vector<string> tokens;

   string::const_iterator first = input.begin ();
   string::const_iterator mark = input.begin ();
   string::const_iterator last = input.end ();

   while (first != last)
   {
// !BAM isspace is NOT working. FUCK.
//      if (isspace (*first))
      if (*first == ' ')
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

// void set_args (int argc, char **argv);
//extern "C" void MAIN__ (void);
//extern "C" int main (int argc, char *argv[]);

void entry_llamaOS (start_info_t *start_info)
{
   register_glibc_exports ();

//   xen_features [XENFEAT_supervisor_mode_kernel] = 1;

   try
   {
      // create the one and only hypervisor object
      trace ("Creating Hypervisor...\n");

      Hypervisor hypervisor (start_info);

      // read and create args
      trace ("reading command-line args from extra string\n");
//      string cl (reinterpret_cast<char *>(start_info->cmd_line));
//      istringstream ss (cl, istringstream::in);
//      vector<string> args;

//      copy (stringstream_iterator<string> (ss),
//            stringstream_iterator<string> (),
//            back_inserter<vector<string> > (args));
//      string arg;

//      while (ss >> arg)
//      {
//         cout << "found arg: " << arg << endl;
//        args.push_back (arg);
//      }

      string cl (reinterpret_cast<char *>(start_info->cmd_line));
      vector<string> args = split (cl);

      trace ("args size is %d\n", args.size ());
      for (unsigned int i = 0; i < args.size (); i++)
      {
         trace ("argv [%d] = %s\n", i, args [i].c_str ());
      }

      char *argv [16] = { '\0' };
      argv [0] = const_cast<char *>(hypervisor.name.c_str ());

      for (unsigned int i = 0; i < args.size (); i++)
      {
         argv [i+1] = const_cast<char *>(args [i].c_str ());
      }

      trace ("Before application main()...\n");

      // start the application
//      fortran_main (args.size () + 1, argv);
  /* Set up the runtime environment.  */
//  set_args (args.size () + 1, argv);

  /* Call the Fortran main program.  Internally this is a function
     called MAIN__ */
//  MAIN__ ();
      main ((int)(args.size () + 1), argv);

      // get rid of all leftover console buffer
      cout.flush ();
      fflush (stdout);

      trace ("After application main()...\n");
      api::sleep(1);
   }
   catch (const std::runtime_error &e)
   {
      trace ("*** runtime_error: %s ***\n", e.what ());
   }
   catch (...)
   {
      trace ("*** unknown exception ***\n");
   }
}

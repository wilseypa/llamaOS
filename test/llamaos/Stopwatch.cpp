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
#include <sys/time.h>

#include <iostream>

#include <gtest/gtest.h>

#include <xen/xen.h>

#include <llamaos/xen/Hypervisor.h>

using namespace std;
using namespace llamaos::xen;

static inline uint64_t rdtsc ()
{
   uint32_t lo, hi;

   asm volatile ("rdtsc" : "=a" (lo), "=d" (hi));

   return (static_cast<uint64_t>(hi) << 32) | lo;
}

static inline uint64_t tsc_to_ns (uint64_t tsc)
{
   const vcpu_time_info_t *time_info = &Hypervisor::get_instance()->shared_info->vcpu_info [0].time;
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

GTEST_TEST(Stopwatch, NonzeroElapsedTime)
{
   struct timeval tv1, tv2;
   gettimeofday (&tv1, 0);
   uint64_t tsc1 = rdtsc ();
   cout << "   RDTSC: " << tsc1 << endl;

   for (unsigned long i = 0; i < 1000000000UL; i++)
   {
      rdtsc ();
   }

   cout << endl;

   uint64_t tsc2 = rdtsc ();
   cout << "   RDTSC: " << tsc2 << endl;

   cout << "   delta: " << tsc2 - tsc1 << endl;
   cout << "delta ns: " << tsc_to_ns (tsc2 - tsc1) << endl; 

   gettimeofday (&tv2, 0);

   cout << " tv1: " << tv1.tv_sec << ", " << tv1.tv_usec << endl;
   cout << " tv2: " << tv2.tv_sec << ", " << tv2.tv_usec << endl;
   cout << "dtime: " << (tv2.tv_sec * 1000 + tv2.tv_usec / 1000) -  (tv1.tv_sec * 1000 + tv1.tv_usec / 1000) << endl;
   EXPECT_EQ(0, 0);
}

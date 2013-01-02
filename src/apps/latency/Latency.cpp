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

#include <sys/time.h>

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <numeric>
#include <stdexcept>
#include <sstream>
#include <string>

#include <latency/Latency.h>

#include <latency/parse_args.cpp>

using namespace std;
using namespace latency;

static void compute_statistics (const vector<unsigned long> &results)
{
   unsigned long mean = accumulate (results.begin (), results.end (), 0UL) / results.size ();

   class Var_op
   {
   public:
      Var_op (unsigned long mean) : mean(mean) { }

      unsigned long operator() (unsigned long sum, unsigned long latency)
      {
         return sum + ((latency - mean) * (latency - mean));
      }

      const unsigned long mean;

   } var_op (mean);

   unsigned long variance = accumulate (results.begin (), results.end (), 0UL, var_op) / (results.size () - 1);
//   unsigned long std_dev = static_cast<unsigned long>(sqrt (variance));

   unsigned long min_latency = *min_element (results.begin (), results.end ());
   unsigned long max_latency = *max_element (results.begin (), results.end ());

   cout << dec << setw(6) << mean <<
           " " << setw(6) << variance <<
           " " << setw(6) << min_latency <<
           " " << setw(6) << max_latency << endl;
}

Latency::Latency (int argc, char *argv [])
   :  min_msg_size(parse<unsigned int>(argc, argv, "--min-msg-size", 0)),
      max_msg_size(parse<unsigned int>(argc, argv, "--max-msg-size", 2048)),
      inc_msg_size(parse<unsigned int>(argc, argv, "--inc-msg-size", 128)),
      num_trials(parse<unsigned int>(argc, argv, "--num_trials", 100000)),
      protocol(Protocol::create(argc, argv)),
      root_node(protocol->root_node ()),
      results()
{
   cout << "  " << num_trials << " trials of msg size range [" << min_msg_size << ", " << max_msg_size << "] in " << inc_msg_size << " increments" << endl << endl;

   if (root_node)
   {
      results.reserve (num_trials);

      cout << setw(6) << "size" << " " << setw(6) << "mean" << " " << setw(6) << "var" << " " << setw(6) << "min" << " " << setw(6) << "max" << endl;
   }
}

Latency::~Latency ()
{
   cout.flush ();
}

bool Latency::run ()
{
   if (!protocol->startup (max_msg_size))
   {
      cout << "failed to intitialize protocol." << endl;
      return false;
   }

   unsigned int msg_size = min_msg_size;

   while (msg_size <= max_msg_size)
   {
      if (!run (msg_size))
      {
         return false;
      }

      msg_size += inc_msg_size;
   }

   if (!protocol->cleanup ())
   {
      cout << "failed to cleanup protocol." << endl;
      return false;
   }

   return true;
}

bool Latency::run (unsigned int msg_size)
{
   if (!protocol->run_verify (msg_size))
   {
      cout << "failed to verify experiment data (first trial)." << endl;
   }
   else if (!run_trials (msg_size))
   {
      cout << "failed to complete all trials." << endl;
   }
   else if (!protocol->run_verify (msg_size))
   {
      cout << "failed to verify experiment data (last trial)." << endl;
   }
   else
   {
      if (root_node)
      {
         cout << setw (6) << msg_size << " ";
         compute_statistics (results);
      }

      return true;
   }

   return false;
}

bool Latency::run_trials (unsigned int msg_size)
{
   results.clear ();

   struct timeval tv1;
   struct timeval tv2;

   for (unsigned int i = 0; i < num_trials; i++)
   {
      if (root_node)
      {
         gettimeofday (&tv1, 0);
      }

      if (!protocol->run_trial (msg_size, i))
      {
         cout << "failed to complete trial " << i << endl;
         return false;
      }

      if (root_node)
      {
         gettimeofday (&tv2, 0);

         results.push_back (((tv2.tv_sec - tv1.tv_sec) * 1000000UL) + tv2.tv_usec - tv1.tv_usec);
      }
   }

   return true;
}

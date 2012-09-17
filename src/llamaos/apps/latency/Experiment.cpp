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

#include <iostream>
#include <sstream>

#include "Experiment.h"

using namespace std;
using namespace latency;

static string parse_name (int argc, char **argv)
{
   if (   (argc > 0)
       && (nullptr != argv [0]))
   {
      return string(argv[0]);
   }

   return string("");
}

static unsigned long parse_trials (int argc, char **argv)
{
   if (   (argc > 1)
       && (nullptr != argv [1]))
   {
      stringstream ss (argv [1]);
      unsigned long trials;
      ss >> trials;

      if (!ss.fail ())
      {
         return trials;
      }
   }

   return 0UL;
}

static unsigned long parse_length (int argc, char **argv)
{
   if (   (argc > 2)
       && (nullptr != argv [2]))
   {
      stringstream ss (argv [2]);
      unsigned long length;
      ss >> length;

      if (!ss.fail ())
      {
         return length;
      }
   }

   return 0UL;
}

Experiment::Experiment (int argc, char **argv)
   :  name(parse_name(argc, argv)),
      trials(parse_trials(argc, argv)),
      length(parse_length(argc, argv)),
      results(new unsigned long [trials])
{
   cout << "running experiment with " << dec << trials << " of " << length << " packets" << endl; 
}

Experiment::~Experiment ()
{
   delete results;
}

void Experiment::compute_statistics ()
{
   unsigned long mean = 0.0;
   unsigned long variance = 0.0;
   unsigned long latency = 0UL;
   unsigned long min_latency = 0xFFFFFFFFFFFFFFFFUL;
   unsigned long max_latency = 0UL;

   // iterate to compute mean
   for (unsigned long i = 0; i < trials; i++)
   {
      latency = results [i];

      mean += latency;

      min_latency = (latency < min_latency) ? latency : min_latency;
      max_latency = (latency > max_latency) ? latency : max_latency;
   }

   mean /= trials;

   // iterate to compute variance
   for (unsigned long i = 0; i < trials; i++)
   {
      latency = results [i];

      variance += ((latency - mean) * (latency - mean));
   }

   variance /= trials;

   cout << "  mean: " << dec << mean << ", var: " << variance << ", [" << min_latency << ", " << max_latency << "]" << endl;
}

void Experiment::mark_data_alpha (volatile unsigned char *buffer, unsigned long length)
{
   unsigned long j = 0;

   // put alpha data (A B C D ...)
   for (unsigned long i = 0; i < length; i++)
   {
      buffer [i] = ('A' + (++j % 26));
   }
}

bool Experiment::verify_data_alpha (const volatile unsigned char *buffer, unsigned long length)
{
   unsigned long j = 0;
   unsigned char c;

   for (unsigned long i = 0; i < length; i++)
   {
      c = 'A' + (++j % 26);

      if (buffer [i] != c)
      {
         cout << "verify alpha failed (" << buffer [i] << " != " << c << ") @ index " << i << endl;
         return false;
      }
   }

   return true;
}

void Experiment::mark_data_numeric (volatile unsigned char *buffer, unsigned long length)
{
   unsigned long j = 0;

   // put num data (0 1 2 3 ...)
   for (unsigned long i = 0; i < length; i++)
   {
      buffer [i] = ('0' + (++j % 10));
   }
}

bool Experiment::verify_data_numeric (const volatile unsigned char *buffer, unsigned long length)
{
   unsigned long j = 0;
   unsigned char c;

   for (unsigned long i = 0; i < length; i++)
   {
      c = '0' + (++j % 10);

      if (buffer [i] != c)
      {
         cout << "verify numeric failed (" << buffer [i] << " != " << c << ") @ index " << i << endl;
         return false;
      }
   }

   return true;
}

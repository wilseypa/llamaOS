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

#include "Experiment.h"

using namespace std;
using namespace latency;

int main (int argc, char *argv [])
{
   // most implementations will require more
   if (argc < 3)
   {
      cout << "too few program arguments." << endl;
   }
   else
   {
      Experiment *experiment = Experiment_factory::create (argc, argv);

      if (nullptr == experiment)
      {
         cout << "failed to create experiment instance." << endl;
      }
      // run once to test and sync multiple nodes
      else if (!experiment->verify ())
      {
         cout << "failed to verify experiment data (first trial)." << endl;
      }
      else if (!experiment->run_trials ())
      {
         cout << "failed to complete all trials." << endl;
      }
      // run again to ensure valid
      else if (!experiment->verify ())
      {
         cout << "failed to verify experiment data (last trial)." << endl;
      }
      else
      {
         delete experiment;
         return 0;
      }
   }

   return -1;
}


#if 0
#include <climits>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <sys/time.h>

#include <iostream>

#include "latency.h"
#include "latency_data.h"
#include "latency_time.h"

using namespace std;

// global/shared vars
static LATENCY_PARAM param;

// remove path part from file name
static void copy_name (char *name, char *path)
{
   int i;

   for (i = strlen (path); i >= 0 ; --i)
   {
      if (path [i] == '/')
      {
         strcpy (name, &path [i+1]);
         return;
      }
   }

   // no separators found, copy entire string
   strcpy (name, path);
}

static int init (int argc, char **argv)
{
   // init data struct
   memset (&param, 0, sizeof (LATENCY_PARAM));

   // most implementations will require more
   if (argc < 3)
   {
      printf ("too few program arguments\n");
   }
   else
   {
      // extract program name and data length
      copy_name (param.name, argv [0]);
      param.trials = atoi (argv [1]);
      param.length = atoi (argv [2]);

      if (   (param.trials <= 0)
          && (param.trials > LATENCY_MAX_TRIALS))
      {
         printf ("invalid trials argument (%d)\n", param.trials);
      }
      else if (param.length < 0)
      {
         printf ("invalid data length argument (%d)\n", param.length);
      }
      else
      {
         return LATENCY_SUCCESS;
      }
   }

//   latency_usage (&param);
   return LATENCY_FAILURE;
}

static int verify_experiment (void)
{
   // master initiates the trial
   if (param.master)
   {
      // marks all bytes with alpha chars (a,b,c,...)
      mark_data_alpha (&param);

      // send/recv and verify the data has been changed to numerals (1,2,3,...)
      if (   (latency_send_msg (&param))
          && (latency_recv_msg (&param))
          && (mark_data_numeric_verify (&param)))
      {
         return LATENCY_SUCCESS;
      }
   }
   else
   {
      // wait for mesg and verify alpha chars
      if (   (latency_recv_msg (&param))
          && (mark_data_alpha_verify (&param)))
      {
         // marks all bytes with numerals and send
         mark_data_numeric (&param);
         return latency_send_msg (&param);
      }
   }

   return LATENCY_FAILURE;
}

static int run_experiment (int trial)
{
}

static int run_experiments (void)
{
   int i;
   latency_time_t t1;
   latency_time_t t2;

   int ret = 0;

   // run timed trials
   for (i = 0; i < param.trials; i++)
   {
      memset(param.data, 0, param.length);

//      LATENCY_GET_TIME(t1);
      ret = run_experiment (i);
//      LATENCY_GET_TIME(t2);

      param.results [i] = latency_dif_time_usec (t1, t2);

      if (!ret)
      {
         printf ("failed to complete trial (%d)\n", i);
         return LATENCY_FAILURE;
      }
   }

   return LATENCY_SUCCESS;
}

static int run (void)
{
   // run once to test and sync multiple nodes
   if (!verify_experiment ())
   {
      printf ("failed to verify experiment data (first trial)\n");
   }
   else if (!run_experiments ())
   {
      printf ("failed to complete all experiments\n");
   }
   // run again to ensure valid
   else if (!verify_experiment ())
   {
      printf ("failed to verify experiment data (last trial)\n");
   }
   else
   {
      return LATENCY_SUCCESS;
   }

   return LATENCY_FAILURE;
}

/*
 * Automatically increment trial number in file name, format is
 * latency_*-<length>-<trial number>.dat.
 *    latency_net_udp-100-1.dat
 *    latency_net_udp-100-2.dat
 *    latency_net_udp-100-3.dat
 *    ...
 */
static FILE *open_results_file (const char *name, int length)
{
   int i;
   char file [256];

   for (i = 1; i <= 100; i++)
   {
      sprintf (file, "%s-%d-%d.dat", name, length, i);

      // open for reading to see if it already exists
      FILE *out = fopen (file, "r");

      if (!out)
      {
         printf ("writing results file (%s)\n", file);
         return fopen (file, "w");
      }

      fclose (out);
   }

   printf ("error opening results file\n");
   return 0;
}

/*
 * Write latency timing results to file, one data point per line. Matlab
 * or Octave can then read the file as a column vector.
 */
static void write_results (void)
{
   int i;

   FILE *out = open_results_file (param.name, param.length);

   if (out)
   {
      for (i = 0; i < param.trials; i++)
      {
         if (fprintf (out, "%d\n", param.results [i]) < 0)
         {
            printf ("error writing results file (%d)\n", i);
            break;
         }
      }

      fclose (out);
   }
}

static void compute_statistics (void)
{
   int i;
   double mean = 0;
   double variance = 0;
   int latency = 0;
   int min_latency = INT_MAX;
   int max_latency = 0;

   // iterate to compute mean
   for (i = 0; i < param.trials; i++)
   {
      latency = param.results [i];

      mean += latency;

      min_latency = (latency < min_latency) ? latency : min_latency;
      max_latency = (latency > max_latency) ? latency : max_latency;
   }

   mean /= param.trials;

   // iterate to compute variance
   for (i = 0; i < param.trials; i++)
   {
      latency = param.results [i];

      variance += ((latency - mean) * (latency - mean));
   }

   variance /= param.trials;

//   printf ("  mean: %.2f, stdev: %.2f, [%d, %d]\n",
//           mean, sqrt (variance), min_latency, max_latency);
}

int main (int argc, char *argv [])
{
   int error = 0;

   if (   (!init (argc, argv))
       || (!latency_init (&param, argc, argv))
       || (!run ()))
   {
      error = -1;
   }
   else if (param.master)
   {
      write_results ();
      compute_statistics ();
   }

   latency_exit (&param);
   return error;
}
#endif

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
   if (argc < 1)//3)
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
      else
      {
         if (!experiment->verify ())
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
            experiment->compute_statistics ();
         }

         delete experiment;
         return 0;
      }
   }

   return -1;
}

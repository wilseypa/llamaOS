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

#ifndef latency_experiment_h_
#define latency_experiment_h_

#include <string>

namespace latency {

class Experiment
{
public:
   Experiment (int argc, char **argv);
   virtual ~Experiment ();

   virtual bool verify () = 0;
   virtual bool run_trials () = 0;
   virtual bool run (unsigned long trial) = 0;

   void compute_statistics ();

   void mark_data_alpha (unsigned char *buffer, unsigned long length);
   bool verify_data_alpha (const unsigned char *buffer, unsigned long length);
   void mark_data_numeric (unsigned char *buffer, unsigned long length);
   bool verify_data_numeric (const unsigned char *buffer, unsigned long length);

   const std::string name;
   const unsigned long trials;
   const unsigned long length;
   unsigned long *const results;

private:
   Experiment ();
   Experiment (const Experiment &);
   Experiment &operator= (const Experiment &);

};

class Experiment_factory
{
public:
   static Experiment *create (int argc, char **argv);

};

}

#endif  // latency_experiment_h_

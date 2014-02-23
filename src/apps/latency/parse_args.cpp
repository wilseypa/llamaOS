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

#include <sstream>
#include <stdexcept>
#include <string>

template <typename T>
static T convert (const std::string &s)
{
   std::stringstream ss (s);
   T t;
   ss >> t;

   if (!ss.fail ())
   {
      return t;
   }

   std::stringstream err;
   err << "failed to convert string: " << s;
   // throw std::runtime_error (err.str ());
   return t;
}

template <typename T>
static T parse (int argc, char *argv [], const std::string &arg, const T &value)
{
   for (int i = 1; i < argc; i++)
   {
      if (arg == argv [i])
      {
         if ((i + 1) >= argc)
         {
            std::stringstream err;
            err << "missing argument value for " << arg;
            // throw std::runtime_error (err.str ());
         }

         return convert<T> (argv [i + 1]);
      }
   }

   return value;
}

template <>
bool parse (int argc, char *argv [], const std::string &arg, const bool &value)
{
   for (int i = 1; i < argc; i++)
   {
      if (arg == argv [i])
      {
         return true;
      }
   }

   return value;
}

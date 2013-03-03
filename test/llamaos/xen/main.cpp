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
#include <algorithm>    // std::for_each
#include <map>
#include <unordered_map>

//#include <gtest/gtest.h>

#include <llamaos/api/sleep.h>

using namespace std;

void print (std::pair<int, string> p)
{
   cout << ' ' <<  p.second << endl;
}

//GTEST_TEST(Default,Test1)
//{
//   int x = 0;
//
//   EXPECT_EQ(0, x);
//}
extern "C"
int main (int argc, char *argv [])
{
//   cout << "running test-xen..." << endl;
//   cout << "  argc: " << argc << ", argv[0]: " << argv [0] << endl;

//   ::testing::InitGoogleTest(&argc, argv);

//   cout << "  RUN_ALL_TESTS: " << RUN_ALL_TESTS() << endl << endl;
   struct timeval tv1;
   struct timeval tv2;

   gettimeofday (&tv1, 0);

   cout << "using doubles that cause SIMD error..." << endl;
   cout.flush ();

   volatile double d1 = 9.4553;
   volatile double d2 = (double)(int)d1;

   cout << "using doubles that cause SIMD error..." << endl;
   cout.flush ();

   d1 = 9.4553;
   d2 = (double)(int)d1;

   gettimeofday (&tv2, 0);

   cout << "gettimeofday: " <<  (((tv2.tv_sec - tv1.tv_sec) * 1000000UL) + tv2.tv_usec - tv1.tv_usec) << endl;

   timeval tv;
   gettimeofday(&tv, NULL);
   cout << "John's Wtime: " << ((double)tv.tv_sec) + ((double)tv.tv_usec)/(1000000.0) << endl;;

   map<int, string> map;
   map[0] = "bill";
   map[1] = "magato";
   for_each(map.begin(), map.end(), print); 

   unordered_map<int, string> umap;
   umap[0] = "isa";
   umap[1] = "braden";
   for_each(umap.begin(), umap.end(), print); 
   
   cout << "waiting 5 sec, then exit..." << endl;
   cout.flush ();
   llamaos::api::sleep (5);

   return 0;
}

//GTEST_TEST(LLAMAOS,TESTTEST)
//{
//   EXPECT_EQ(0, 0);
//}

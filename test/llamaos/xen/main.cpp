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

//#include <gtest/gtest.h>

#include <llamaos/api/sleep.h>

using namespace std;

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

volatile double d1 = 9.4553;
//printf("NOT CRASHED\n");
volatile double d2 = (double)(int)d1;

   cout << "waiting 5 sec, then exit..." << endl;
   cout.flush ();
   llamaos::api::sleep (5);

   return 0;
}

//GTEST_TEST(LLAMAOS,TESTTEST)
//{
//   EXPECT_EQ(0, 0);
//}

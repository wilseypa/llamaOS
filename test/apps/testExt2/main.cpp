/*
Copyright (c) 2014, William Magato
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

#include <cstdio>
#include <iostream>
#include <fcntl.h>
#include <unistd.h>

using namespace std;

int main (int argc, char *argv [])
{
   cout << endl << "hello llamaOS" << endl;
   cout << endl << "creating file create_test.txt" << endl;

   int fd = open ("create_test.txt", O_RDWR | O_CREAT, 0777); 
   //write( fd, "test\n", 5);
   close (fd);
   return 0;
   
   cout << endl << "opening create_test.txt" << endl;
   FILE *file = fopen ("create_test.txt", "r+");

   if (file == NULL)
   {
      cout << "failed to create file" << endl;
   }
   else
   {
      char buffer [513];
      int size = 0;
      int read = 0;

      while (!feof(file)) {
	read = fread (buffer, 1, 512, file);
	buffer [read] = '\0';
	cout << buffer;
	size += read;
      }
//      int size = fread (buffer, 1, 512, file);
//      buffer [size] = '\0';

      cout << "size is " << size << endl;
//      cout << "content is " << buffer << endl;

      for (int i = 0; i < 40; i++)
      {
	fwrite ("123456789012345\n", 1, 16, file);
      }
      
      //close (fd);
      fclose (file);

      file = fopen ("create_test.txt", "r+");
      size = 0;

      while (!feof(file)) {
         read = fread (buffer, 1, 512, file);
         buffer [read] = '\0';
         cout << buffer;
         size += read;
      }

//      size = fread (buffer, 1, 512, file);
//      buffer [size] = '\0';

      cout << "size is " << size << endl;
//      cout << "content is " << buffer << endl;
#if 0
      for (int i = 0; i < 513; i++)
      {
         buffer [i] = 'X';
      }

      cout << endl << "Write Test" << endl;
      fseek (file, 0, SEEK_SET);
      fwrite (buffer, 1, 513, file);
#endif
      fflush(file);
      fclose (file);
   }

   cout.flush ();   

   return 0;
}

/*
Copyright (c) 2011, William Magato
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

#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/uio.h>

ssize_t __libc_writev (int fd, const struct iovec *vector, int count)
{
   size_t bytes = 0;

   for (int i = 0; i < count; i++)
   {
      if ((SIZE_MAX - bytes) < vector [i].iov_len)
      {
         __set_errno (EINVAL);
         return -1;
      }

      bytes += vector [i].iov_len;
   }

   char *buffer = malloc (bytes);

   if (0 == buffer)
   {
      __set_errno (ENOMEM);
      return -1;
   }

   char *pbuffer = buffer;

   for (int i = 0; i < count; i++)
   {
      pbuffer = memcpy (pbuffer, vector [i].iov_base, vector [i].iov_len); 
   }

   ssize_t write_result = write (fd, buffer, bytes);
   free (buffer);
   return write_result;
}

strong_alias (__libc_writev, __writev)
weak_alias (__libc_writev, writev)

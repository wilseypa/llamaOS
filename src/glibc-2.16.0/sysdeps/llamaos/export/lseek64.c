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

#include <errno.h>
#include <unistd.h>
#include <sys/types.h>

// define function pointer
typedef off64_t (*llamaos_lseek64_t) (int, off64_t, int);

// function pointer variable
static llamaos_lseek64_t llamaos_lseek64 = 0;

// function called by llamaOS to register pointer
void register_llamaos_lseek64 (llamaos_lseek64_t func)
{
   llamaos_lseek64 = func;
}

/* Seek to OFFSET on FD, starting from WHENCE.  */
off64_t __libc_lseek64 (int fd, off64_t offset, int whence)
{
   if (0 != llamaos_lseek64)
   {
      if (fd < 0)
      {
         __set_errno (EBADF);
         return -1;
      }

      switch (whence)
      {
      case SEEK_SET:
      case SEEK_CUR:
      case SEEK_END:
         break;
      default:
         __set_errno (EINVAL);
         return -1;
      }

      return llamaos_lseek64 (fd, offset, whence);
   }

   __set_errno (ENOSYS);
   return -1;
}
weak_alias (__libc_lseek64, __lseek64)
weak_alias (__libc_lseek64, lseek64)

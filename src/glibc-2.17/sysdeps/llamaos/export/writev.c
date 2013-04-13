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
#include <sys/uio.h>

// define function pointer
typedef ssize_t (*llamaos_writev_t) (int, const struct iovec *, int);

// function pointer variable
static llamaos_writev_t llamaos_writev = 0;

// function called by llamaOS to register pointer
void register_llamaos_writev (llamaos_writev_t func)
{
   llamaos_writev = func;
}

/* Write data pointed by the buffers described by VECTOR, which
   is a vector of COUNT `struct iovec's, to file descriptor FD.
   The data is written in the order specified.
   Operates just like `write' (see <unistd.h>) except that the data
   are taken from VECTOR instead of a contiguous buffer.  */
ssize_t __libc_writev (int fd, const struct iovec *vector, int count)
{
   if (0 != llamaos_writev)
   {
      return llamaos_writev (fd, vector, count);
   }

   __set_errno (ENOSYS);
   return -1;
}
strong_alias (__libc_writev, __writev)
weak_alias (__libc_writev, writev)

/*
Copyright (c) 2013, William Magato
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
#include <stddef.h>
#include <sys/stat.h>

// define function pointer
typedef int (*llamaos_xstat64_t) (int, const char *, struct stat64 *);

// function pointer variable
static llamaos_xstat64_t llamaos_xstat64 = 0;

// function called by llamaOS to register pointer
void register_llamaos_xstat64 (llamaos_xstat64_t func)
{
   llamaos_xstat64 = func;
}

/* Get file information about FILE in BUF.  */
int
__xstat64 (int vers, const char *file, struct stat64 *buf)
{
   if (vers != _STAT_VER || file == NULL || buf == NULL)
   {
      __set_errno (EINVAL);
      return -1;
   }

   if (0 != llamaos_xstat64)
   {
      return llamaos_xstat64 (vers, file, buf);
   }

   __set_errno (ENOSYS);
   return -1;
}
hidden_def (__xstat64)

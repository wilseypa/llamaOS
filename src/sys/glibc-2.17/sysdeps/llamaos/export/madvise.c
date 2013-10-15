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

#include <sys/types.h>
#include <sys/mman.h>
#include <errno.h>

// define function pointer
typedef int (*llamaos_madvise_t) (__ptr_t, size_t, int);

// function pointer variable
static llamaos_madvise_t llamaos_madvise = 0;

// function called by llamaOS to register pointer
void register_llamaos_madvise (llamaos_madvise_t madvise)
{
   llamaos_madvise = madvise;
}

/* Advise the system about particular usage patterns the program follows
   for the region starting at ADDR and extending LEN bytes.  */

int
__madvise (void *addr, size_t len, int advice)
{
   if (0 != llamaos_madvise)
   {
      return llamaos_madvise (addr, len, advice);
   }

   __set_errno (ENOSYS);
   return -1;
}
libc_hidden_def (__madvise)
weak_alias (__madvise, madvise)

stub_warning (madvise)

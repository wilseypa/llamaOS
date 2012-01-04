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

#include <cstdio>

#include <stdexcept>
#include <sstream>

#include <xen/xen.h>

#include <llamaos/xen/Hypervisor.h>
#include <llamaos/xen/Memory.h>
#include <llamaos/trace.h>

using namespace llamaos;
using namespace llamaos::xen;

extern "C"
void *llamaos_brk (void *addr)
{
   trace ("glibc calling brk (%lx)\n", addr);

   return Hypervisor::get_instance ()->memory.brk (addr);
}

typedef void *(*llamaos_brk_t) (void *);
extern "C" int register_llamaos_brk (llamaos_brk_t);

namespace {
   int brk_registered = register_llamaos_brk (llamaos_brk);
}

extern "C"
int madvise (__ptr_t addr, size_t len, int advice)
{
   trace ("glibc calling madvise (%lx, %d, %d)\n", addr, len, advice);
   return 0;
}

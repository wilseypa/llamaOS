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

#include <cstdint>
#include <iostream>

#include <xen/xen.h>

#include <llamaos/xen/Hypercall.h>
#include <llamaos/xen/Traps.h>
#include <llamaos/memory/Memory.h>

using namespace llamaos::xen;
using namespace llamaos::memory;

// defined in Entry.S
extern "C"
void simd_coprocessor_error (void);

struct pt_regs {
        unsigned long r15;
        unsigned long r14;
        unsigned long r13;
        unsigned long r12;
        unsigned long rbp;
        unsigned long rbx;
/* arguments: non interrupts/non tracing syscalls only save upto here*/
        unsigned long r11;
        unsigned long r10;      
        unsigned long r9;
        unsigned long r8;
        unsigned long rax;
        unsigned long rcx;
        unsigned long rdx;
        unsigned long rsi;
        unsigned long rdi;
        unsigned long orig_rax;
/* end of arguments */  
/* cpu exception frame or undefined */
        unsigned long rip;
        unsigned long cs;
        unsigned long eflags; 
        unsigned long rsp; 
        unsigned long ss;
/* top of stack page */ 
};

// SIMD, gcc with Intel Core 2 Duo uses SSE2(4)
#define getmxcsr(x)    asm ("stmxcsr %0" : "=m" (x));
#define setmxcsr(x)    asm ("ldmxcsr %0" : "=m" (x));

extern "C"
void do_simd_coprocessor_error(struct pt_regs * /* regs */)
{

}

static trap_info_t table [1];

Traps::Traps ()
{
//   table [0].vector = 19;
//   table [0].flags = 0;
//   table [0].cs = 0xe033;
//   table [0].address = pointer_to_address(simd_coprocessor_error);

//   table [1].vector = 0;
//   table [1].flags = 0;
//   table [1].cs = 0;
//   table [1].address = 0;

   table [0].vector = 0;
   table [0].flags = 0;
   table [0].cs = 0;
   table [0].address = 0;

   Hypercall::set_trap_table (table);
}

Traps::~Traps ()
{
   Hypercall::set_trap_table (0);
}

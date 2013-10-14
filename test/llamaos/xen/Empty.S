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

.section __xen_guest
   .ascii  "GUEST_OS=llamaOS"
   .ascii  ",XEN_VER=xen-3.0"
   .ascii  ",VIRT_BASE=0x0"
   .ascii  ",ELF_PADDR_OFFSET=0x0"
   .ascii  ",HYPERCALL_PAGE=0x1"
   .ascii  ",LOADER=generic"
   .byte   0

.section .absolute

shared_info:
   .skip 0x1000

hypercall_page:
   .skip 0x1000

stack_bottom_buffer:
   .skip 0x1000

stack_bottom:
   .skip 0x400000
stack_top:

stack_top_buffer:
   .skip 0x1000

.section .text

_start:
   /* set the stack pointer */
   movq $stack_top, %rsp
   movq %rsp, %rbp

spin_forever:
   jmp spin_forever

   /* pass the start_info pointer as parameter to entry_start */
#   movq %rsi, %rdi
#   callq entry_glibc

   /* call the shutdown hypercall */
   movq $2, %rdi
   movq $0, sched_shutdown
   movq $sched_shutdown, %rsi
   callq hypercall_page+(__HYPERVISOR_sched_op*32)

   /* loop forever if not shutdown */
loop:
   jmp loop

.set __HYPERVISOR_sched_op, 29
.comm sched_shutdown, 8

.globl _start, shared_info, hypercall_page, stack_bottom

.data


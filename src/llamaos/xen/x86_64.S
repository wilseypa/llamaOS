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

*******************************************************************************

Some of this file's content copied from Xen mini-os (arch/x86_64.S),
copyright statement is as follows:

Copyright (c) 2009 Citrix Systems, Inc. All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions
are met:
1. Redistributions of source code must retain the above copyright
   notice, this list of conditions and the following disclaimer.
2. Redistributions in binary form must reproduce the above copyright
   notice, this list of conditions and the following disclaimer in the
   documentation and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY AUTHOR AND CONTRIBUTORS ``AS IS'' AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
ARE DISCLAIMED.  IN NO EVENT SHALL AUTHOR OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
SUCH DAMAGE.
*/

// #include <xen/features.h>
#include <xen/include/public/features.h>

#include <llamaos/config.h>

.section __xen_guest
   .ascii  "GUEST_OS=llamaOS"
   .ascii  ",XEN_VER=xen-3.0"
   .ascii  ",VIRT_BASE=0x0"
   .ascii  ",ELF_PADDR_OFFSET=0x0"
   .ascii  ",HYPERCALL_PAGE=0x2"
   .ascii  ",LOADER=generic"
   .byte   0

.text

#define ENTRY(X) .globl X ; X :
.globl _start, shared_info, hypercall_page

_start:
   cld                                  /* Clears the direction flag (DF) in the rFLAGS register to zero. */
   movq stack_start(%rip), %rsp         /* Setup the runtime stack position */
   andq $(~(LLAMAOS_STACK_SIZE-1)), %rsp      /* Align stack pointer */
   movq %rsi, %rdi                      /* Pass the start_info pointer to start_kernel */
   call start                     /* call the kernel entry function */

stack_start:
   .quad RUNTIME_STACK+(2*LLAMAOS_STACK_SIZE)

   /* Unpleasant -- the PTE that maps this page is actually overwritten */
   /* to map the real shared-info page! :-)                             */
   .org 0x1000
shared_info:

   .org 0x2000
hypercall_page:

   .org 0x3000

/* Offsets into shared_info_t. */
#define evtchn_upcall_pending           /* 0 */
#define evtchn_upcall_mask              1

NMI_MASK = 0x80000000

#define RDI 112
#define ORIG_RAX 120       /* + error_code */
#define EFLAGS 144

.macro RESTORE_ALL
        movq (%rsp),%r11
        movq 1*8(%rsp),%r10
        movq 2*8(%rsp),%r9
        movq 3*8(%rsp),%r8
        movq 4*8(%rsp),%rax
        movq 5*8(%rsp),%rcx
        movq 6*8(%rsp),%rdx
        movq 7*8(%rsp),%rsi
        movq 8*8(%rsp),%rdi
        addq $9*8+8,%rsp
.endm

# copied from xen.h
#define __HYPERVISOR_iret                 23 /* x86 only */

.macro HYPERVISOR_IRET flag
        testl $NMI_MASK,2*8(%rsp)
        jnz   2f

        testb $1,(xen_features+XENFEAT_supervisor_mode_kernel)
        jnz   1f

        /* Direct iret to kernel space. Correct CS and SS. */
        orb   $3,1*8(%rsp)
        orb   $3,4*8(%rsp)
1:      iretq

2:      /* Slow iret via hypervisor. */
        andl  $~NMI_MASK, 16(%rsp)
        pushq $\flag
        jmp  hypercall_page + (__HYPERVISOR_iret * 32)
.endm

/*
 * Exception entry point. This expects an error code/orig_rax on the stack
 * and the exception handler in %rax.
 */
ENTRY(error_entry)
        /* rdi slot contains rax, oldrax contains error code */
        cld
        subq  $14*8,%rsp
        movq %rsi,13*8(%rsp)
        movq 14*8(%rsp),%rsi    /* load rax from rdi slot */
        movq %rdx,12*8(%rsp)
        movq %rcx,11*8(%rsp)
        movq %rsi,10*8(%rsp)    /* store rax */
        movq %r8, 9*8(%rsp)
        movq %r9, 8*8(%rsp)
        movq %r10,7*8(%rsp)
        movq %r11,6*8(%rsp)
        movq %rbx,5*8(%rsp)
        movq %rbp,4*8(%rsp)
        movq %r12,3*8(%rsp)
        movq %r13,2*8(%rsp)
        movq %r14,1*8(%rsp)
        movq %r15,(%rsp)

error_call_handler:
        movq %rdi, RDI(%rsp)
        movq %rsp,%rdi
        movq ORIG_RAX(%rsp),%rsi        # get error code
        movq $-1,ORIG_RAX(%rsp)
        call *%rax
        jmp error_exit

.macro zeroentry sym
    movq (%rsp),%rcx
    movq 8(%rsp),%r11
    addq $0x10,%rsp /* skip rcx and r11 */
        pushq $0        /* push error code/oldrax */
        pushq %rax      /* push real oldrax to the rdi slot */
        leaq  \sym(%rip),%rax
        jmp error_entry
.endm

.macro errorentry sym
        movq (%rsp),%rcx
        movq 8(%rsp),%r11
        addq $0x10,%rsp /* rsp points to the error code */
        pushq %rax
        leaq  \sym(%rip),%rax
        jmp error_entry
.endm

#define XEN_GET_VCPU_INFO(reg)  movq HYPERVISOR_shared_info,reg
#define XEN_PUT_VCPU_INFO(reg)
#define XEN_PUT_VCPU_INFO_fixup
#define XEN_LOCKED_BLOCK_EVENTS(reg)    movb $1,evtchn_upcall_mask(reg)
#define XEN_LOCKED_UNBLOCK_EVENTS(reg)  movb $0,evtchn_upcall_mask(reg)
#define XEN_TEST_PENDING(reg)   testb $0xFF,evtchn_upcall_pending(reg)

#define XEN_BLOCK_EVENTS(reg)   XEN_GET_VCPU_INFO(reg)                  ; \
                                        XEN_LOCKED_BLOCK_EVENTS(reg)    ; \
                                            XEN_PUT_VCPU_INFO(reg)

#define XEN_UNBLOCK_EVENTS(reg) XEN_GET_VCPU_INFO(reg)                  ; \
                                                XEN_LOCKED_UNBLOCK_EVENTS(reg)  ; \
                                        XEN_PUT_VCPU_INFO(reg)

ENTRY(hypervisor_callback)
    zeroentry hypervisor_callback2

ENTRY(hypervisor_callback2)
        movq %rdi, %rsp
11:     movq %gs:8,%rax
        incl %gs:0
        cmovzq %rax,%rsp
        pushq %rdi
        call do_hypervisor_callback
        popq %rsp
        decl %gs:0
        jmp error_exit

restore_all_enable_events:
        XEN_UNBLOCK_EVENTS(%rsi)        # %rsi is already set up...

retint_kernel:
retint_restore_args:
        movl EFLAGS-6*8(%rsp), %eax
        shr $9, %eax                    # EAX[0] == IRET_EFLAGS.IF
        XEN_GET_VCPU_INFO(%rsi)
        andb evtchn_upcall_mask(%rsi),%al
        andb $1,%al                     # EAX[0] == IRET_EFLAGS.IF & event_mask
        jnz restore_all_enable_events   #        != 0 => enable event delivery
        XEN_PUT_VCPU_INFO(%rsi)

        RESTORE_ALL
        HYPERVISOR_IRET 0

error_exit:
        movq (%rsp),%r15
        movq 1*8(%rsp),%r14
        movq 2*8(%rsp),%r13
        movq 3*8(%rsp),%r12
        movq 4*8(%rsp),%rbp
        movq 5*8(%rsp),%rbx
        addq $6*8,%rsp
        XEN_BLOCK_EVENTS(%rsi)
        jmp retint_kernel

ENTRY(failsafe_callback)
        popq  %rcx
        popq  %r11
        iretq

ENTRY(simd_coprocessor_error)
        zeroentry do_simd_coprocessor_error

.globl _end
_end:

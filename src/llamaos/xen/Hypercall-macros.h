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

#ifndef llamaos_xen_hypercall_macros_h_
#define llamaos_xen_hypercall_macros_h_

#include <errno.h>
#include <string.h>

#include <xen/xen.h>
#include <xen/physdev.h>
#include <xen/sched.h>
#include <xen/tmem.h>
#include <xen/arch-x86/xen-mca.h>

typedef struct { unsigned long pte; } pte_t;
extern char hypercall_page [];

// Taken straight from Linux source
// linux-3.6-rc3/arch/x86/include/asm/xen/hypercall.h
#if 1

// extern struct { char _entry[32]; } hypercall_page[];

#define __HYPERCALL		"call hypercall_page+%c[offset]"
#define __HYPERCALL_ENTRY(x)						\
	[offset] "i" (__HYPERVISOR_##x * 32)
//	[offset] "i" (__HYPERVISOR_##x * sizeof(hypercall_page[0]))

#ifdef CONFIG_X86_32
#define __HYPERCALL_RETREG	"eax"
#define __HYPERCALL_ARG1REG	"ebx"
#define __HYPERCALL_ARG2REG	"ecx"
#define __HYPERCALL_ARG3REG	"edx"
#define __HYPERCALL_ARG4REG	"esi"
#define __HYPERCALL_ARG5REG	"edi"
#else
#define __HYPERCALL_RETREG	"rax"
#define __HYPERCALL_ARG1REG	"rdi"
#define __HYPERCALL_ARG2REG	"rsi"
#define __HYPERCALL_ARG3REG	"rdx"
#define __HYPERCALL_ARG4REG	"r10"
#define __HYPERCALL_ARG5REG	"r8"
#endif

#define __HYPERCALL_DECLS						\
	register unsigned long __res  asm(__HYPERCALL_RETREG);		\
	register unsigned long __arg1 asm(__HYPERCALL_ARG1REG) = __arg1; \
	register unsigned long __arg2 asm(__HYPERCALL_ARG2REG) = __arg2; \
	register unsigned long __arg3 asm(__HYPERCALL_ARG3REG) = __arg3; \
	register unsigned long __arg4 asm(__HYPERCALL_ARG4REG) = __arg4; \
	register unsigned long __arg5 asm(__HYPERCALL_ARG5REG) = __arg5;

#define __HYPERCALL_0PARAM	"=r" (__res)
#define __HYPERCALL_1PARAM	__HYPERCALL_0PARAM, "+r" (__arg1)
#define __HYPERCALL_2PARAM	__HYPERCALL_1PARAM, "+r" (__arg2)
#define __HYPERCALL_3PARAM	__HYPERCALL_2PARAM, "+r" (__arg3)
#define __HYPERCALL_4PARAM	__HYPERCALL_3PARAM, "+r" (__arg4)
#define __HYPERCALL_5PARAM	__HYPERCALL_4PARAM, "+r" (__arg5)

#define __HYPERCALL_0ARG()
#define __HYPERCALL_1ARG(a1)						\
	__HYPERCALL_0ARG()		__arg1 = (unsigned long)(a1);
#define __HYPERCALL_2ARG(a1,a2)						\
	__HYPERCALL_1ARG(a1)		__arg2 = (unsigned long)(a2);
#define __HYPERCALL_3ARG(a1,a2,a3)					\
	__HYPERCALL_2ARG(a1,a2)		__arg3 = (unsigned long)(a3);
#define __HYPERCALL_4ARG(a1,a2,a3,a4)					\
	__HYPERCALL_3ARG(a1,a2,a3)	__arg4 = (unsigned long)(a4);
#define __HYPERCALL_5ARG(a1,a2,a3,a4,a5)				\
	__HYPERCALL_4ARG(a1,a2,a3,a4)	__arg5 = (unsigned long)(a5);

#define __HYPERCALL_CLOBBER5	"memory"
#define __HYPERCALL_CLOBBER4	__HYPERCALL_CLOBBER5, __HYPERCALL_ARG5REG
#define __HYPERCALL_CLOBBER3	__HYPERCALL_CLOBBER4, __HYPERCALL_ARG4REG
#define __HYPERCALL_CLOBBER2	__HYPERCALL_CLOBBER3, __HYPERCALL_ARG3REG
#define __HYPERCALL_CLOBBER1	__HYPERCALL_CLOBBER2, __HYPERCALL_ARG2REG
#define __HYPERCALL_CLOBBER0	__HYPERCALL_CLOBBER1, __HYPERCALL_ARG1REG

#define _hypercall0(type, name)						\
({									\
	__HYPERCALL_DECLS;						\
	__HYPERCALL_0ARG();						\
	asm volatile (__HYPERCALL					\
		      : __HYPERCALL_0PARAM				\
		      : __HYPERCALL_ENTRY(name)				\
		      : __HYPERCALL_CLOBBER0);				\
	(type)__res;							\
})

#define _hypercall1(type, name, a1)					\
({									\
	__HYPERCALL_DECLS;						\
	__HYPERCALL_1ARG(a1);						\
	asm volatile (__HYPERCALL					\
		      : __HYPERCALL_1PARAM				\
		      : __HYPERCALL_ENTRY(name)				\
		      : __HYPERCALL_CLOBBER1);				\
	(type)__res;							\
})

#define _hypercall2(type, name, a1, a2)					\
({									\
	__HYPERCALL_DECLS;						\
	__HYPERCALL_2ARG(a1, a2);					\
	asm volatile (__HYPERCALL					\
		      : __HYPERCALL_2PARAM				\
		      : __HYPERCALL_ENTRY(name)				\
		      : __HYPERCALL_CLOBBER2);				\
	(type)__res;							\
})

#define _hypercall3(type, name, a1, a2, a3)				\
({									\
	__HYPERCALL_DECLS;						\
	__HYPERCALL_3ARG(a1, a2, a3);					\
	asm volatile (__HYPERCALL					\
		      : __HYPERCALL_3PARAM				\
		      : __HYPERCALL_ENTRY(name)				\
		      : __HYPERCALL_CLOBBER3);				\
	(type)__res;							\
})

#define _hypercall4(type, name, a1, a2, a3, a4)				\
({									\
	__HYPERCALL_DECLS;						\
	__HYPERCALL_4ARG(a1, a2, a3, a4);				\
	asm volatile (__HYPERCALL					\
		      : __HYPERCALL_4PARAM				\
		      : __HYPERCALL_ENTRY(name)				\
		      : __HYPERCALL_CLOBBER4);				\
	(type)__res;							\
})

#define _hypercall5(type, name, a1, a2, a3, a4, a5)			\
({									\
	__HYPERCALL_DECLS;						\
	__HYPERCALL_5ARG(a1, a2, a3, a4, a5);				\
	asm volatile (__HYPERCALL					\
		      : __HYPERCALL_5PARAM				\
		      : __HYPERCALL_ENTRY(name)				\
		      : __HYPERCALL_CLOBBER5);				\
	(type)__res;							\
})

static inline long
privcmd_call(unsigned call,
	     unsigned long a1, unsigned long a2,
	     unsigned long a3, unsigned long a4,
	     unsigned long a5)
{
	__HYPERCALL_DECLS;
	__HYPERCALL_5ARG(a1, a2, a3, a4, a5);

	asm volatile("call *%[call]"
		     : __HYPERCALL_5PARAM
		     : [call] "a" (&hypercall_page[call])
		     : __HYPERCALL_CLOBBER5);

	return (long)__res;
}
#else
#define __STR(x) #x
#define STR(x) __STR(x)

// extern char hypercall_page[PAGE_SIZE];

#define _hypercall0(type, name)                 \
({                                              \
        long __res;                             \
        asm volatile (                          \
                "call hypercall_page + (" STR(__HYPERVISOR_##name) " * 32)"\
                : "=a" (__res)                  \
                :                               \
                : "memory" );                   \
        (type)__res;                            \
})

#define _hypercall1(type, name, a1)                             \
({                                                              \
        long __res, __ign1;                                     \
        asm volatile (                                          \
                "call hypercall_page + (" STR(__HYPERVISOR_##name) " * 32)"\
                : "=a" (__res), "=D" (__ign1)                   \
                : "1" ((long)(a1))                              \
                : "memory" );                                   \
        (type)__res;                                            \
})

#define _hypercall2(type, name, a1, a2)                         \
({                                                              \
        long __res, __ign1, __ign2;                             \
        asm volatile (                                          \
                "call hypercall_page + (" STR(__HYPERVISOR_##name) " * 32)"\
                : "=a" (__res), "=D" (__ign1), "=S" (__ign2)    \
                : "1" ((long)(a1)), "2" ((long)(a2))            \
                : "memory" );                                   \
        (type)__res;                                            \
})

#define _hypercall3(type, name, a1, a2, a3)                     \
({                                                              \
        long __res, __ign1, __ign2, __ign3;                     \
        asm volatile (                                          \
                "call hypercall_page + (" STR(__HYPERVISOR_##name) " * 32)"\
                : "=a" (__res), "=D" (__ign1), "=S" (__ign2),   \
                "=d" (__ign3)                                   \
                : "1" ((long)(a1)), "2" ((long)(a2)),           \
                "3" ((long)(a3))                                \
                : "memory" );                                   \
        (type)__res;                                            \
})

#define _hypercall4(type, name, a1, a2, a3, a4)                 \
({                                                              \
        long __res, __ign1, __ign2, __ign3;                     \
        asm volatile (                                          \
                "movq %7,%%r10; "                               \
                "call hypercall_page + (" STR(__HYPERVISOR_##name) " * 32)"\
                : "=a" (__res), "=D" (__ign1), "=S" (__ign2),   \
                "=d" (__ign3)                                   \
                : "1" ((long)(a1)), "2" ((long)(a2)),           \
                "3" ((long)(a3)), "g" ((long)(a4))              \
                : "memory", "r10" );                            \
        (type)__res;                                            \
})

#define _hypercall5(type, name, a1, a2, a3, a4, a5)             \
({                                                              \
        long __res, __ign1, __ign2, __ign3;                     \
        asm volatile (                                          \
                "movq %7,%%r10; movq %8,%%r8; "                 \
                "call hypercall_page + (" STR(__HYPERVISOR_##name) " * 32)"\
                : "=a" (__res), "=D" (__ign1), "=S" (__ign2),   \
                "=d" (__ign3)                                   \
                : "1" ((long)(a1)), "2" ((long)(a2)),           \
                "3" ((long)(a3)), "g" ((long)(a4)),             \
                "g" ((long)(a5))                                \
                : "memory", "r10", "r8" );                      \
        (type)__res;                                            \
})

#endif

static inline int
HYPERVISOR_set_trap_table(struct trap_info *table)
{
	return _hypercall1(int, set_trap_table, table);
}

static inline int
HYPERVISOR_mmu_update(struct mmu_update *req, int count,
		      int *success_count, domid_t domid)
{
	return _hypercall4(int, mmu_update, req, count, success_count, domid);
}

static inline int
HYPERVISOR_mmuext_op(struct mmuext_op *op, int count,
		     int *success_count, domid_t domid)
{
	return _hypercall4(int, mmuext_op, op, count, success_count, domid);
}

static inline int
HYPERVISOR_set_gdt(unsigned long *frame_list, int entries)
{
	return _hypercall2(int, set_gdt, frame_list, entries);
}

static inline int
HYPERVISOR_stack_switch(unsigned long ss, unsigned long esp)
{
	return _hypercall2(int, stack_switch, ss, esp);
}

static inline int
HYPERVISOR_set_callbacks(unsigned long event_address,
			unsigned long failsafe_address,
			unsigned long syscall_address)
{
	return _hypercall3(int, set_callbacks,
			   event_address, failsafe_address,
			   syscall_address);
}

static inline int
HYPERVISOR_callback_op(int cmd, void *arg)
{
	return _hypercall2(int, callback_op, cmd, arg);
}

static inline int
HYPERVISOR_fpu_taskswitch(int set)
{
	return _hypercall1(int, fpu_taskswitch, set);
}

static inline int
HYPERVISOR_sched_op(int cmd, void *arg)
{
	return _hypercall2(int, sched_op, cmd, arg);
}

static inline long
HYPERVISOR_set_timer_op(uint64_t timeout)
{
	unsigned long timeout_hi = (unsigned long)(timeout>>32);
	unsigned long timeout_lo = (unsigned long)timeout;
	return _hypercall2(long, set_timer_op, timeout_lo, timeout_hi);
}

static inline int
HYPERVISOR_mca(struct xen_mc *mc_op)
{
	mc_op->interface_version = XEN_MCA_INTERFACE_VERSION;
	return _hypercall1(int, mca, mc_op);
}

#if __XEN_INTERFACE_VERSION__ < 0x00030204
static inline int
HYPERVISOR_dom0_op(struct xen_platform_op *platform_op)
{
	platform_op->interface_version = XENPF_INTERFACE_VERSION;
	return _hypercall1(int, dom0_op, platform_op);
}
#endif

static inline int
HYPERVISOR_set_debugreg(int reg, unsigned long value)
{
	return _hypercall2(int, set_debugreg, reg, value);
}

static inline unsigned long
HYPERVISOR_get_debugreg(int reg)
{
	return _hypercall1(unsigned long, get_debugreg, reg);
}

static inline int
HYPERVISOR_update_descriptor(uint64_t ma, uint64_t desc)
{
	if (sizeof(uint64_t) == sizeof(long))
		return _hypercall2(int, update_descriptor, ma, desc);
	return _hypercall4(int, update_descriptor, ma, ma>>32, desc, desc>>32);
}

static inline int
HYPERVISOR_memory_op(unsigned int cmd, void *arg)
{
	return _hypercall2(int, memory_op, cmd, arg);
}

static inline int
HYPERVISOR_multicall(void *call_list, int nr_calls)
{
	return _hypercall2(int, multicall, call_list, nr_calls);
}

static inline int
HYPERVISOR_update_va_mapping(unsigned long va, pte_t new_val,
			     unsigned long flags)
{
	if (sizeof(new_val) == sizeof(long))
		return _hypercall3(int, update_va_mapping, va,
				   new_val.pte, flags);
	else
		return _hypercall4(int, update_va_mapping, va,
				   new_val.pte, new_val.pte >> 32, flags);
}

//static inline int
//HYPERVISOR_update_va_mapping(unsigned long va, unsigned long new_val,
//			     unsigned long flags)
//{
//	return _hypercall3(int, update_va_mapping, va,
//				   new_val, flags);
//}

static inline int
HYPERVISOR_event_channel_op(int cmd, void *arg)
{
	int rc = _hypercall2(int, event_channel_op, cmd, arg);
//	if (unlikely(rc == -ENOSYS)) {
//		struct evtchn_op op;
//		op.cmd = cmd;
//		memcpy(&op.u, arg, sizeof(op.u));
//		rc = _hypercall1(int, event_channel_op_compat, &op);
//		memcpy(arg, &op.u, sizeof(op.u));
//	}
	return rc;
}

static inline int
HYPERVISOR_xen_version(int cmd, void *arg)
{
	return _hypercall2(int, xen_version, cmd, arg);
}

static inline int
HYPERVISOR_console_io(int cmd, int count, char *str)
{
	return _hypercall3(int, console_io, cmd, count, str);
}

static inline int
HYPERVISOR_physdev_op(int cmd, void *arg)
{
	int rc = _hypercall2(int, physdev_op, cmd, arg);
//	if (unlikely(rc == -ENOSYS)) {
	if (rc == -ENOSYS) {
		struct physdev_op op;
		op.cmd = cmd;
		memcpy(&op.u, arg, sizeof(op.u));
		rc = _hypercall1(int, physdev_op_compat, &op);
		memcpy(arg, &op.u, sizeof(op.u));
	}
	return rc;
}

static inline int
HYPERVISOR_grant_table_op(unsigned int cmd, void *uop, unsigned int count)
{
	return _hypercall3(int, grant_table_op, cmd, uop, count);
}

static inline int
HYPERVISOR_update_va_mapping_otherdomain(unsigned long va, pte_t new_val,
					 unsigned long flags, domid_t domid)
{
	if (sizeof(new_val) == sizeof(long))
		return _hypercall4(int, update_va_mapping_otherdomain, va,
				   new_val.pte, flags, domid);
	else
		return _hypercall5(int, update_va_mapping_otherdomain, va,
				   new_val.pte, new_val.pte >> 32,
				   flags, domid);
}

static inline int
HYPERVISOR_vm_assist(unsigned int cmd, unsigned int type)
{
	return _hypercall2(int, vm_assist, cmd, type);
}

static inline int
HYPERVISOR_vcpu_op(int cmd, int vcpuid, void *extra_args)
{
	return _hypercall3(int, vcpu_op, cmd, vcpuid, extra_args);
}

static inline int
HYPERVISOR_set_segment_base(int reg, unsigned long value)
{
	return _hypercall2(int, set_segment_base, reg, value);
}

static inline int
HYPERVISOR_suspend(unsigned long start_info_mfn)
{
	struct sched_shutdown r = { .reason = SHUTDOWN_suspend };

	/*
	 * For a PV guest the tools require that the start_info mfn be
	 * present in rdx/edx when the hypercall is made. Per the
	 * hypercall calling convention this is the third hypercall
	 * argument, which is start_info_mfn here.
	 */
	return _hypercall3(int, sched_op, SCHEDOP_shutdown, &r, start_info_mfn);
}

static inline int
HYPERVISOR_nmi_op(unsigned long op, unsigned long arg)
{
	return _hypercall2(int, nmi_op, op, arg);
}

// static inline unsigned long __must_check
static inline unsigned long
HYPERVISOR_hvm_op(int op, void *arg)
{
       return _hypercall2(unsigned long, hvm_op, op, arg);
}

static inline int
HYPERVISOR_tmem_op(
	struct tmem_op *op)
{
	return _hypercall1(int, tmem_op, op);
}

#if 0
static inline void
MULTI_fpu_taskswitch(struct multicall_entry *mcl, int set)
{
	mcl->op = __HYPERVISOR_fpu_taskswitch;
	mcl->args[0] = set;

	trace_xen_mc_entry(mcl, 1);
}

static inline void
MULTI_update_va_mapping(struct multicall_entry *mcl, unsigned long va,
			pte_t new_val, unsigned long flags)
{
	mcl->op = __HYPERVISOR_update_va_mapping;
	mcl->args[0] = va;
	if (sizeof(new_val) == sizeof(long)) {
		mcl->args[1] = new_val.pte;
		mcl->args[2] = flags;
	} else {
		mcl->args[1] = new_val.pte;
		mcl->args[2] = new_val.pte >> 32;
		mcl->args[3] = flags;
	}

	trace_xen_mc_entry(mcl, sizeof(new_val) == sizeof(long) ? 3 : 4);
}

static inline void
MULTI_grant_table_op(struct multicall_entry *mcl, unsigned int cmd,
		     void *uop, unsigned int count)
{
	mcl->op = __HYPERVISOR_grant_table_op;
	mcl->args[0] = cmd;
	mcl->args[1] = (unsigned long)uop;
	mcl->args[2] = count;

	trace_xen_mc_entry(mcl, 3);
}

static inline void
MULTI_update_va_mapping_otherdomain(struct multicall_entry *mcl, unsigned long va,
				    pte_t new_val, unsigned long flags,
				    domid_t domid)
{
	mcl->op = __HYPERVISOR_update_va_mapping_otherdomain;
	mcl->args[0] = va;
	if (sizeof(new_val) == sizeof(long)) {
		mcl->args[1] = new_val.pte;
		mcl->args[2] = flags;
		mcl->args[3] = domid;
	} else {
		mcl->args[1] = new_val.pte;
		mcl->args[2] = new_val.pte >> 32;
		mcl->args[3] = flags;
		mcl->args[4] = domid;
	}

	trace_xen_mc_entry(mcl, sizeof(new_val) == sizeof(long) ? 4 : 5);
}

static inline void
MULTI_update_descriptor(struct multicall_entry *mcl, uint64_t maddr,
			uint64_t desc)
{
	mcl->op = __HYPERVISOR_update_descriptor;
	if (sizeof(maddr) == sizeof(long)) {
		mcl->args[0] = maddr;
		mcl->args[1] = *(unsigned long *)&desc;
	} else {
		mcl->args[0] = maddr;
		mcl->args[1] = maddr >> 32;
		mcl->args[2] = desc.a;
		mcl->args[3] = desc.b;
	}

	trace_xen_mc_entry(mcl, sizeof(maddr) == sizeof(long) ? 2 : 4);
}

static inline void
MULTI_memory_op(struct multicall_entry *mcl, unsigned int cmd, void *arg)
{
	mcl->op = __HYPERVISOR_memory_op;
	mcl->args[0] = cmd;
	mcl->args[1] = (unsigned long)arg;

	trace_xen_mc_entry(mcl, 2);
}

static inline void
MULTI_mmu_update(struct multicall_entry *mcl, struct mmu_update *req,
		 int count, int *success_count, domid_t domid)
{
	mcl->op = __HYPERVISOR_mmu_update;
	mcl->args[0] = (unsigned long)req;
	mcl->args[1] = count;
	mcl->args[2] = (unsigned long)success_count;
	mcl->args[3] = domid;

	trace_xen_mc_entry(mcl, 4);
}

static inline void
MULTI_mmuext_op(struct multicall_entry *mcl, struct mmuext_op *op, int count,
		int *success_count, domid_t domid)
{
	mcl->op = __HYPERVISOR_mmuext_op;
	mcl->args[0] = (unsigned long)op;
	mcl->args[1] = count;
	mcl->args[2] = (unsigned long)success_count;
	mcl->args[3] = domid;

	trace_xen_mc_entry(mcl, 4);
}

static inline void
MULTI_set_gdt(struct multicall_entry *mcl, unsigned long *frames, int entries)
{
	mcl->op = __HYPERVISOR_set_gdt;
	mcl->args[0] = (unsigned long)frames;
	mcl->args[1] = entries;

	trace_xen_mc_entry(mcl, 2);
}

static inline void
MULTI_stack_switch(struct multicall_entry *mcl,
		   unsigned long ss, unsigned long esp)
{
	mcl->op = __HYPERVISOR_stack_switch;
	mcl->args[0] = ss;
	mcl->args[1] = esp;

	trace_xen_mc_entry(mcl, 2);
}
#endif

#endif	// llamaos_xen_hypercall_macros_h_

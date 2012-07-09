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
#include <cstring>

#ifndef __XEN_INTERFACE_VERSION__
#error __XEN_INTERFACE_VERSION__ not defined!!!
#endif

#include <xen/xen.h>
//#include <xen/include/public/grant_table.h>
#include <xen/sched.h>
//#include <xen/include/public/version.h>

#include <llamaos/xen/Hypercall.h>
#include <llamaos/config.h>
#include <llamaos/trace.h>

using namespace llamaos;
using namespace llamaos::xen;

extern char hypercall_page[PAGE_SIZE];

template <typename T> 
static T hypercall (uint64_t index)
{
   register uint64_t result asm("rax");

   asm volatile ("call hypercall_page + %c[offset]"
                 : "=r"(result)
                 : [offset] "i" (index * 32)
                 : "rdi", "rsi", "rdx", "r10", "r8" "memory"
                );

   return static_cast<T>(result);
}

template <typename T> 
static T hypercall (uint64_t index,
                    uint64_t a1)
{
   register uint64_t result asm("rax");
   register uint64_t arg1 asm("rdi") = a1;

   asm volatile ("call hypercall_page + %c[offset]"
                 : "=r"(result), "+r"(arg1)
                 : [offset] "i" (index * 32)
                 : "rsi", "rdx", "r10", "r8", "memory"
                );

   return static_cast<T>(result);
}

template <typename T> 
static T hypercall (uint64_t index,
                    uint64_t a1,
                    uint64_t a2)
{
   register uint64_t result asm("rax");
   register uint64_t arg1 asm("rdi") = a1;
   register uint64_t arg2 asm("rsi") = a2;

   asm volatile ("call hypercall_page + %c[offset]"
                 : "=r"(result), "+r"(arg1), "+r"(arg2)
                 : [offset] "i" (index * 32)
                 : "rdx", "r10", "r8", "memory"
                );

   return static_cast<T>(result);
}

template <typename T> 
static inline T hypercall (uint64_t index,
                           uint64_t a1,
                           uint64_t a2,
                           uint64_t a3)
{
   register uint64_t result asm("rax");
   register uint64_t arg1 asm("rdi") = a1;
   register uint64_t arg2 asm("rsi") = a2;
   register uint64_t arg3 asm("rdx") = a3;

   asm volatile ("call hypercall_page + %c[offset]"
                 : "=r"(result), "+r"(arg1), "+r"(arg2), "+r"(arg3)
                 : [offset] "i" (index * 32)
                 : "r10", "r8", "memory"
                );

   return static_cast<T>(result);
}

template <typename T> 
static inline T hypercall (uint64_t index,
                           uint64_t a1,
                           uint64_t a2,
                           uint64_t a3,
                           uint64_t a4)
{
   register uint64_t result asm("rax");
   register uint64_t arg1 asm("rdi") = a1;
   register uint64_t arg2 asm("rsi") = a2;
   register uint64_t arg3 asm("rdx") = a3;
   register uint64_t arg4 asm("r10") = a4;

   asm volatile ("call hypercall_page + %c[offset]"
                 : "=r"(result), "+r"(arg1), "+r"(arg2), "+r"(arg3)
                 : [offset] "i" (index * 32)
                 : "r8", "memory"
                );

   return static_cast<T>(result);
}

template <typename T> 
static inline T hypercall (uint64_t index,
                           uint64_t a1,
                           uint64_t a2,
                           uint64_t a3,
                           uint64_t a4,
                           uint64_t a5)
{
   register uint64_t result asm("rax");
   register uint64_t arg1 asm("rdi") = a1;
   register uint64_t arg2 asm("rsi") = a2;
   register uint64_t arg3 asm("rdx") = a3;
   register uint64_t arg4 asm("r10") = a4;
   register uint64_t arg5 asm("r8")  = a5;

   asm volatile ("call hypercall_page + %c[offset]"
                 : "=r"(result), "+r"(arg1), "+r"(arg2), "+r"(arg3)
                 : [offset] "i" (index * 32)
                 : "memory"
                );

   return static_cast<T>(result);
}

#if 0
bool Hypercall::console_io (const char *string)
{
   if (0 != hypercall<int>(__HYPERVISOR_console_io,
                           CONSOLEIO_write,
                           strlen (string),
                           reinterpret_cast<uint64_t>(string)))
   {
      // probably nothing can be done here since trace would just recall this
      return false;
   }

   return true;
}
#endif

bool Hypercall::console_io (const std::string &string)
{
   if (0 != hypercall<int>(__HYPERVISOR_console_io,
                           CONSOLEIO_write,
                           string.size (),
                           reinterpret_cast<uint64_t>(string.c_str ())))
   {
      // probably nothing can be done here since trace would just recall this
      return false;
   }

   return true;
}

bool Hypercall::sched_op_shutdown (unsigned int reason)
{
   sched_shutdown_t arg;
   arg.reason = reason;

   if (0 != hypercall<int>(__HYPERVISOR_sched_op,
                           SCHEDOP_shutdown,
			   reinterpret_cast<uint64_t>(&arg)))
   {
      trace ("HYPERVISOR_sched_op (SCHEDOP_shutdown, reason: %u) FAILED\n", reason);
      return false;
   }

   return true;
}

#if 0
// include the hypercall macros from mini-os
//typedef struct { unsigned long pte; } pte_t;
// extern char hypercall_page [LLAMAOS_PAGE_SIZE];
// #include <llamaos/xen/hypercall-x86_64.h>

#define _hypercall3(type, name, a1, a2, a3)			\
({								\
	long __res, __ign1, __ign2, __ign3;			\
	asm volatile (						\
		"call hypercall_page + (" STR(__HYPERVISOR_##name) " * 32)"\
		: "=a" (__res), "=D" (__ign1), "=S" (__ign2), 	\
		"=d" (__ign3)					\
		: "1" (static_cast<long>(a1)), "2" (static_cast<long>(a2)),		\
		"3" (reinterpret_cast<long>(a3))				\
		: "memory" );					\
	static_cast<type>(__res);						\
})

/*
 * The hypercall asms have to meet several constraints:
 * - Work on 32- and 64-bit.
 *    The two architectures put their arguments in different sets of
 *    registers.
 *
 * - Work around asm syntax quirks
 *    It isn't possible to specify one of the rNN registers in a
 *    constraint, so we use explicit register variables to get the
 *    args into the right place.
 *
 * - Mark all registers as potentially clobbered
 *    Even unused parameters can be clobbered by the hypervisor, so we
 *    need to make sure gcc knows it.
 *
 * - Avoid compiler bugs.
 *    This is the tricky part.  Because x86_32 has such a constrained
 *    register set, gcc versions below 4.3 have trouble generating
 *    code when all the arg registers and memory are trashed by the
 *    asm.  There are syntactically simpler ways of achieving the
 *    semantics below, but they cause the compiler to crash.
 *
 *    The only combination I found which works is:
 *     - assign the __argX variables first
 *     - list all actually used parameters as "+r" (__argX)
 *     - clobber the rest
 *
 * The result certainly isn't pretty, and it really shows up cpp's
 * weakness as as macro language.  Sorry.  (But let's just give thanks
 * there aren't more than 5 arguments...)
 */

extern struct { char _entry[32]; } hypercall_page[];

#define __HYPERCALL		"call hypercall_page+%c[offset]"
#define __HYPERCALL_ENTRY(x)						\
	[offset] "i" (__HYPERVISOR_##x * sizeof(hypercall_page[0]))

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

extern struct { char _entry[32]; } hypercall_page[];

#define __HYPERCALL		"call hypercall_page+%c[offset]"
#define __HYPERCALL_ENTRY(x)						\
	[offset] "i" (__HYPERVISOR_##x * sizeof(hypercall_page[0]))

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

#define __HYPERCALL_0ARG()
#define __HYPERCALL_1ARG(a1)						\
	__HYPERCALL_0ARG()		__arg1 = (unsigned long)(a1);
#define __HYPERCALL_2ARG(a1,a2)						\
	__HYPERCALL_1ARG(a1)		__arg2 = (unsigned long)(a2);
#define __HYPERCALL_3ARG(a1,a2,a3)					\
	__HYPERCALL_2ARG(a1,a2)		__arg3 = (unsigned long)(a3);

#define __HYPERCALL_CLOBBER5	"memory"
#define __HYPERCALL_CLOBBER4	__HYPERCALL_CLOBBER5, __HYPERCALL_ARG5REG
// #define __HYPERCALL_CLOBBER3	__HYPERCALL_CLOBBER4, __HYPERCALL_ARG4REG
#define __HYPERCALL_CLOBBER3	"memory"

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

using namespace llamaos;
using namespace llamaos::xen;

bool Hypercall::set_trap_table (const trap_info_t *table)
{
   if (0 != HYPERVISOR_set_trap_table(const_cast<trap_info_t *>(table)))
   {
      trace ("HYPERVISOR_set_trap_table (%lx) FAILED\n", table);
      return false;
   }

   return true;
}

bool Hypercall::mmu_update (uint64_t ptr, uint64_t val)
{
   mmu_update_t req;
   req.ptr = ptr;
   req.val = val;

   return mmu_update (&req, 1);
}

bool Hypercall::mmu_update (const mmu_update_t *req, unsigned int count)
{
   int request_count = count;
   int success_count = 0;

   if (0 != HYPERVISOR_mmu_update(const_cast<mmu_update_t *>(req), request_count, &success_count, DOMID_SELF))
   {
      trace ("HYPERVISOR_mmu_update (count: %d) FAILED\n", request_count);

      for (unsigned int i = 0; i < count; i++)
      {
         trace ("   [%u] ptr: %lx, val: %lx\n", i, req [i].ptr, req [i].val);
      }

      return false;
   }
   else if (success_count != request_count)
   {
      trace ("HYPERVISOR_mmu_update () FAILED: invalid success_count (%d != %d\n", success_count, request_count);
      return false;
   }

   return true;
}

bool Hypercall::set_callbacks (uint64_t event_address, uint64_t failsafe_address)
{
   if (0 != HYPERVISOR_set_callbacks (event_address, failsafe_address, 0UL))
   {
      trace ("HYPERVISOR_set_callbacks (event_address: %lx, failsafe_address: %lx) FAILED\n", event_address, failsafe_address);
      return false;
   }

   return true;
}

bool Hypercall::update_va_mapping (uint64_t virtual_address, uint64_t machine_address)
{
   pte_t val;
   val.pte = machine_address | 7;

   if (0 != HYPERVISOR_update_va_mapping (virtual_address, val, UVMF_INVLPG))
   {
      trace ("HYPERVISOR_update_va_mapping (pseudo_page: %lx, machine_page: %lx) FAILED\n", virtual_address, machine_address);
      return false;
   }

   return true;
}

bool Hypercall::update_va_mapping_nocache (uint64_t virtual_address, uint64_t machine_address)
{
   pte_t val;
   val.pte = machine_address | 0x17;

   if (0 != HYPERVISOR_update_va_mapping (virtual_address, val, UVMF_INVLPG))
   {
      trace ("HYPERVISOR_update_va_mapping (pseudo_page: %lx, machine_page: %lx) FAILED\n", virtual_address, machine_address);
      return false;
   }

   return true;
}

void Hypercall::xen_version (int &major, int &minor)
{
   uint32_t version = HYPERVISOR_xen_version (XENVER_version, 0);

   major = version >> 16;
   minor = version & 0xFFFF;
}

bool Hypercall::console_io (const char *str)
{
//   if (0 != HYPERVISOR_console_io (CONSOLEIO_write, strlen (str), const_cast<char *>(str)))
   if (0 != _hypercall3(int, console_io, CONSOLEIO_write, strlen (str), const_cast<char *>(str)))
   {
      // probably nothing can be done here since trace would just recall console_io
      return false;
   }

   return true;
}


bool Hypercall::grant_table_setup_table (unsigned int pages, unsigned long *frame_list)
{
   gnttab_setup_table_t setup_table;

   setup_table.dom = DOMID_SELF;
   setup_table.nr_frames = pages;
   set_xen_guest_handle(setup_table.frame_list, frame_list);

   if (0 != HYPERVISOR_grant_table_op (GNTTABOP_setup_table, &setup_table, 1))
   {
      trace ("HYPERVISOR_grant_table_op (GNTTABOP_setup_table) FAILED\n");
      return false;
   }
   else if (setup_table.status != GNTST_okay)
   {
      trace ("HYPERVISOR_grant_table_op (GNTTABOP_setup_table) FAILED (status: %d)\n", setup_table.status);
      return false;
   }

   return true;
}

bool Hypercall::grant_table_query_size (uint32_t &frames, uint32_t &max_frames, int16_t &status)
{
   gnttab_query_size_t query_size;
   query_size.dom = DOMID_SELF;

   if (0 != HYPERVISOR_grant_table_op (GNTTABOP_query_size, &query_size, 1))
   {
      trace ("HYPERVISOR_grant_table_op (GNTTABOP_query_size) FAILED\n");
      return false;
   }

   frames = query_size.nr_frames;
   max_frames = query_size.max_nr_frames;
   status = query_size.status;
   return true;
}

// needs __XEN_INTERFACE_VERSION__=0x0003020a
bool Hypercall::grant_table_get_version (uint32_t &version)
{
   gnttab_get_version_t get_version;
   get_version.dom = DOMID_SELF;

   if (0 != HYPERVISOR_grant_table_op (GNTTABOP_get_version, &get_version, 1))
   {
      trace ("HYPERVISOR_grant_table_op (GNTTABOP_get_version) FAILED\n");
      return false;
   }

   version = get_version.version;
   return true;
}

bool Hypercall::sched_op_yield ()
{
   if (0 != HYPERVISOR_sched_op (SCHEDOP_yield, 0))
   {
      trace ("HYPERVISOR_sched_op (SCHEDOP_yield) FAILED\n");
      return false;
   }

   return true;
}

bool Hypercall::sched_op_block ()
{
   if (0 != HYPERVISOR_sched_op (SCHEDOP_block, 0))
   {
      trace ("HYPERVISOR_sched_op (SCHEDOP_block) FAILED\n");
      return false;
   }

   return true;
}

bool Hypercall::sched_op_shutdown (unsigned int reason)
{
   sched_shutdown_t arg;
   arg.reason = reason;

   if (0 != HYPERVISOR_sched_op (SCHEDOP_shutdown, &arg))
   {
      trace ("HYPERVISOR_sched_op (SCHEDOP_shutdown, reason: %u) FAILED\n", reason);
      return false;
   }

   return true;
}

bool Hypercall::event_channel_send (evtchn_port_t port)
{
   evtchn_send_t op;
   op.port = port;

   if (0 != HYPERVISOR_event_channel_op (EVTCHNOP_send, &op))
   {
      trace ("HYPERVISOR_event_channel_op (EVTCHNOP_send, port: %u) FAILED\n", port);
      return false;
   }

   return true;
}

bool Hypercall::event_channel_bind_virq (uint32_t virq, evtchn_port_t &port)
{
   evtchn_bind_virq_t op;
   op.virq = virq;
   op.vcpu = 0;

   if (0 != HYPERVISOR_event_channel_op (EVTCHNOP_bind_virq, &op))
   {
      trace ("HYPERVISOR_event_channel_op (EVTCHNOP_bind_virq, virq: %u) FAILED\n", virq);
      return false;
   }

   port = op.port;
   return true;
}

bool Hypercall::event_channel_alloc_unbound (domid_t dom, evtchn_port_t &port)
{
   evtchn_alloc_unbound_t op;
   op.dom = DOMID_SELF;
   op.remote_dom = dom;

   if (0 != HYPERVISOR_event_channel_op (EVTCHNOP_alloc_unbound, &op))
   {
      trace ("HYPERVISOR_event_channel_op (EVTCHNOP_alloc_unbound) FAILED\n");
      return false;
   }

   port = op.port;
   return true;
}

#endif

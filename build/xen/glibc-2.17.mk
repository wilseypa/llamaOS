#
# Copyright (c) 2013, William Magato
# All rights reserved.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions are met:
#
#    1. Redistributions of source code must retain the above copyright notice,
#       this list of conditions and the following disclaimer.
#
#    2. Redistributions in binary form must reproduce the above copyright
#       notice, this list of conditions and the following disclaimer in the
#       documentation and/or other materials provided with the distribution.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDER(S) AND CONTRIBUTORS
# ''AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
# TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
# PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER(S) OR
# CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
# EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
# PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
# OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
# WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
# OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
# ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
# 
# The views and conclusions contained in the software and documentation are
# those of the authors and should not be interpreted as representing official
# policies, either expressed or implied, of the copyright holder(s) or
# contributors.
#

# include common variables
include common-vars.mk
include common-flags.mk

MAKEFILE_SOURCES += glibc-$(GLIBC_VERSION).mk

INCLUDES_DIRS = \
  -I $(SRCDIR)/glibc-$(GLIBC_VERSION)/include \
  -I $(SRCDIR)/glibc-$(GLIBC_VERSION)/sysdeps/llamaos/x86_64/64/nptl \
  -I $(SRCDIR)/glibc-$(GLIBC_VERSION)/sysdeps/llamaos/x86_64/64 \
  -I $(SRCDIR)/glibc-$(GLIBC_VERSION)/nptl/sysdeps/llamaos/x86_64 \
  -I $(SRCDIR)/glibc-$(GLIBC_VERSION)/nptl/sysdeps/llamaos/x86 \
  -I $(SRCDIR)/glibc-$(GLIBC_VERSION)/sysdeps/llamaos/x86_64 \
  -I $(SRCDIR)/glibc-$(GLIBC_VERSION)/sysdeps/llamaos/x86 \
  -I $(SRCDIR)/glibc-$(GLIBC_VERSION)/sysdeps/llamaos/wordsize-64 \
  -I $(SRCDIR)/glibc-$(GLIBC_VERSION)/nptl/sysdeps/llamaos \
  -I $(SRCDIR)/glibc-$(GLIBC_VERSION)/nptl/sysdeps/pthread \
  -I $(SRCDIR)/glibc-$(GLIBC_VERSION)/sysdeps/pthread \
  -I $(SRCDIR)/glibc-$(GLIBC_VERSION)/sysdeps/llamaos \
  -I $(SRCDIR)/glibc-$(GLIBC_VERSION)/sysdeps/gnu \
  -I $(SRCDIR)/glibc-$(GLIBC_VERSION)/sysdeps/posix \
  -I $(SRCDIR)/glibc-$(GLIBC_VERSION)/nptl/sysdeps/x86_64/64 \
  -I $(SRCDIR)/glibc-$(GLIBC_VERSION)/sysdeps/x86_64/64 \
  -I $(SRCDIR)/glibc-$(GLIBC_VERSION)/sysdeps/x86_64/fpu \
  -I $(SRCDIR)/glibc-$(GLIBC_VERSION)/sysdeps/x86/fpu \
  -I $(SRCDIR)/glibc-$(GLIBC_VERSION)/nptl/sysdeps/x86_64 \
  -I $(SRCDIR)/glibc-$(GLIBC_VERSION)/sysdeps/x86_64 \
  -I $(SRCDIR)/glibc-$(GLIBC_VERSION)/sysdeps/x86 \
  -I $(SRCDIR)/glibc-$(GLIBC_VERSION)/sysdeps/ieee754/ldbl-96 \
  -I $(SRCDIR)/glibc-$(GLIBC_VERSION)/sysdeps/ieee754/dbl-64/wordsize-64 \
  -I $(SRCDIR)/glibc-$(GLIBC_VERSION)/sysdeps/ieee754/dbl-64 \
  -I $(SRCDIR)/glibc-$(GLIBC_VERSION)/sysdeps/ieee754/flt-32 \
  -I $(SRCDIR)/glibc-$(GLIBC_VERSION)/sysdeps/wordsize-64 \
  -I $(SRCDIR)/glibc-$(GLIBC_VERSION)/sysdeps/ieee754 \
  -I $(SRCDIR)/glibc-$(GLIBC_VERSION)/sysdeps/generic \
  -I $(SRCDIR)/glibc-$(GLIBC_VERSION)/nptl \
  -I $(SRCDIR)/glibc-$(GLIBC_VERSION) \
  -I $(SRCDIR)/glibc-$(GLIBC_VERSION)/csu \
  -I $(SRCDIR)/glibc-$(GLIBC_VERSION)/elf \
  -I $(SRCDIR)/glibc-$(GLIBC_VERSION)/iconv \
  -I $(SRCDIR)/glibc-$(GLIBC_VERSION)/libio \
  -I $(SRCDIR)/glibc-$(GLIBC_VERSION)/locale \
  -I $(SRCDIR)/glibc-$(GLIBC_VERSION)/math \
  -I $(SRCDIR)/glibc-$(GLIBC_VERSION)/stdio-common \
  -I $(SRCDIR)/glibc-$(GLIBC_VERSION)/stdlib \
  -I $(SRCDIR)/glibc-$(GLIBC_VERSION)/wcsmbs \
  -I $(SRCDIR)/gcc-$(GCC_VERSION)/gcc/ginclude \
  -I $(SRCDIR)/gcc-$(GCC_VERSION)/gcc/include \
  -I $(SRCDIR)/gcc-$(GCC_VERSION)/gcc \
  -I $(SRCDIR)

ASMFLAGS += \
  -U_FORTIFY_SOURCE \
  -D__USE_FORTIFY_LEVEL=0 \
  -D_LIBC_REENTRANT \
  -DASSEMBLER \
  -Wa,--noexecstack \
  $(INCLUDES_DIRS) \
  -include  $(SRCDIR)/glibc-$(GLIBC_VERSION)/include/libc-symbols.h \
  -include $(SRCDIR)/llamaos/__thread.h


#  -Wbad-function-cast \
#  -Wcast-qual \
#  -Wcomment \
#  -Wcomments \
#  -Wfloat-equal \
#  -Winline \
#  -Wmissing-declarations \
#  -Wmissing-noreturn \
#  -Wmissing-prototypes \
#  -Wmultichar \
#  -Wsign-compare \
#  -Wtrigraphs \
#  -Wwrite-strings \

#  -DPER_THREAD

CFLAGS += \
  -fmerge-all-constants \
  -frounding-math \
  -Wstrict-prototypes \
  -U_FORTIFY_SOURCE \
  -D__USE_FORTIFY_LEVEL=0 \
  -DLOCALEDIR='""' \
  -DLOCALE_ALIAS_PATH='""' \
  -D_LIBC_REENTRANT \
  -DGCONV_DIR='""' \
  -DGCONV_PATH='""' \
  -DNLSPATH='""' \
  -DSYSCONFDIR='""' \
  -D_IO_MTSAFE_IO \
  -DMORECORE_CLEARS=2 \
  -DEXEC_PAGESIZE=4096 \
  -D HAVE_MREMAP=0 \
  $(INCLUDES_DIRS) \
  -include  $(SRCDIR)/glibc-$(GLIBC_VERSION)/include/libc-symbols.h \
  -include $(SRCDIR)/llamaos/__thread.h

#  -fexceptions \

VPATH = $(SRCDIR)

ASM_SOURCES = \
  glibc-$(GLIBC_VERSION)/csu/abi-note.S \
  glibc-$(GLIBC_VERSION)/sysdeps/x86_64/fpu/e_exp2l.S \
  glibc-$(GLIBC_VERSION)/sysdeps/x86_64/fpu/e_exp10l.S \
  glibc-$(GLIBC_VERSION)/sysdeps/x86_64/fpu/e_expl.S \
  glibc-$(GLIBC_VERSION)/sysdeps/x86_64/fpu/e_fmodl.S \
  glibc-$(GLIBC_VERSION)/sysdeps/x86_64/fpu/e_ilogbl.S \
  glibc-$(GLIBC_VERSION)/sysdeps/x86_64/fpu/e_log2l.S \
  glibc-$(GLIBC_VERSION)/sysdeps/x86_64/fpu/e_log10l.S \
  glibc-$(GLIBC_VERSION)/sysdeps/x86_64/fpu/e_logl.S \
  glibc-$(GLIBC_VERSION)/sysdeps/x86_64/fpu/e_powl.S \
  glibc-$(GLIBC_VERSION)/sysdeps/x86_64/fpu/e_remainderl.S \
  glibc-$(GLIBC_VERSION)/sysdeps/x86_64/fpu/e_scalbl.S \
  glibc-$(GLIBC_VERSION)/sysdeps/x86_64/fpu/s_ceill.S \
  glibc-$(GLIBC_VERSION)/sysdeps/x86_64/fpu/s_copysign.S \
  glibc-$(GLIBC_VERSION)/sysdeps/x86_64/fpu/s_copysignf.S \
  glibc-$(GLIBC_VERSION)/sysdeps/x86_64/fpu/s_copysignl.S \
  glibc-$(GLIBC_VERSION)/sysdeps/x86_64/fpu/s_cosf.S \
  glibc-$(GLIBC_VERSION)/sysdeps/x86_64/fpu/s_expm1l.S \
  glibc-$(GLIBC_VERSION)/sysdeps/x86_64/fpu/s_fabsl.S \
  glibc-$(GLIBC_VERSION)/sysdeps/x86_64/fpu/s_finitel.S \
  glibc-$(GLIBC_VERSION)/sysdeps/x86_64/fpu/s_floorl.S \
  glibc-$(GLIBC_VERSION)/sysdeps/x86_64/fpu/s_llrint.S \
  glibc-$(GLIBC_VERSION)/sysdeps/x86_64/fpu/s_llrintf.S \
  glibc-$(GLIBC_VERSION)/sysdeps/x86_64/fpu/s_llrintl.S \
  glibc-$(GLIBC_VERSION)/sysdeps/x86_64/fpu/s_log1pl.S \
  glibc-$(GLIBC_VERSION)/sysdeps/x86_64/fpu/s_lrint.S \
  glibc-$(GLIBC_VERSION)/sysdeps/x86_64/fpu/s_lrintf.S \
  glibc-$(GLIBC_VERSION)/sysdeps/x86_64/fpu/s_lrintl.S \
  glibc-$(GLIBC_VERSION)/sysdeps/x86_64/fpu/s_fdiml.S \
  glibc-$(GLIBC_VERSION)/sysdeps/x86_64/fpu/s_fmax.S \
  glibc-$(GLIBC_VERSION)/sysdeps/x86_64/fpu/s_fmaxf.S \
  glibc-$(GLIBC_VERSION)/sysdeps/x86_64/fpu/s_fmaxl.S \
  glibc-$(GLIBC_VERSION)/sysdeps/x86_64/fpu/s_fmin.S \
  glibc-$(GLIBC_VERSION)/sysdeps/x86_64/fpu/s_fminf.S \
  glibc-$(GLIBC_VERSION)/sysdeps/x86_64/fpu/s_fminl.S \
  glibc-$(GLIBC_VERSION)/sysdeps/x86_64/fpu/s_scalbnl.S \
  glibc-$(GLIBC_VERSION)/sysdeps/x86_64/fpu/s_signbit.S \
  glibc-$(GLIBC_VERSION)/sysdeps/x86_64/fpu/s_signbitf.S \
  glibc-$(GLIBC_VERSION)/sysdeps/x86_64/fpu/s_sincosf.S \
  glibc-$(GLIBC_VERSION)/sysdeps/x86_64/fpu/s_sinf.S \
  glibc-$(GLIBC_VERSION)/sysdeps/x86_64/fpu/s_truncl.S \
  glibc-$(GLIBC_VERSION)/sysdeps/x86_64/_mcount.S \
  glibc-$(GLIBC_VERSION)/sysdeps/x86_64/add_n.S \
  glibc-$(GLIBC_VERSION)/sysdeps/x86_64/addmul_1.S \
  glibc-$(GLIBC_VERSION)/sysdeps/x86_64/__longjmp.S \
  glibc-$(GLIBC_VERSION)/sysdeps/x86_64/bsd-_setjmp.S \
  glibc-$(GLIBC_VERSION)/sysdeps/x86_64/bsd-setjmp.S \
  glibc-$(GLIBC_VERSION)/sysdeps/x86_64/bzero.S \
  glibc-$(GLIBC_VERSION)/sysdeps/x86_64/crti.S \
  glibc-$(GLIBC_VERSION)/sysdeps/x86_64/crtn.S \
  glibc-$(GLIBC_VERSION)/sysdeps/x86_64/dl-tlsdesc.S \
  glibc-$(GLIBC_VERSION)/sysdeps/x86_64/dl-trampoline.S \
  glibc-$(GLIBC_VERSION)/sysdeps/x86_64/lshift.S \
  glibc-$(GLIBC_VERSION)/sysdeps/x86_64/memchr.S \
  glibc-$(GLIBC_VERSION)/sysdeps/x86_64/memcmp.S \
  glibc-$(GLIBC_VERSION)/sysdeps/x86_64/memcpy.S \
  glibc-$(GLIBC_VERSION)/sysdeps/x86_64/mempcpy.S \
  glibc-$(GLIBC_VERSION)/sysdeps/x86_64/memrchr.S \
  glibc-$(GLIBC_VERSION)/sysdeps/x86_64/memset.S \
  glibc-$(GLIBC_VERSION)/sysdeps/x86_64/mul_1.S \
  glibc-$(GLIBC_VERSION)/sysdeps/x86_64/rawmemchr.S \
  glibc-$(GLIBC_VERSION)/sysdeps/x86_64/rshift.S \
  glibc-$(GLIBC_VERSION)/sysdeps/x86_64/setjmp.S \
  glibc-$(GLIBC_VERSION)/sysdeps/x86_64/stpcpy.S \
  glibc-$(GLIBC_VERSION)/sysdeps/x86_64/strcasecmp.S \
  glibc-$(GLIBC_VERSION)/sysdeps/x86_64/strcat.S \
  glibc-$(GLIBC_VERSION)/sysdeps/x86_64/strchr.S \
  glibc-$(GLIBC_VERSION)/sysdeps/x86_64/strchrnul.S \
  glibc-$(GLIBC_VERSION)/sysdeps/x86_64/strcmp.S \
  glibc-$(GLIBC_VERSION)/sysdeps/x86_64/strcpy.S \
  glibc-$(GLIBC_VERSION)/sysdeps/x86_64/strcspn.S \
  glibc-$(GLIBC_VERSION)/sysdeps/x86_64/strlen.S \
  glibc-$(GLIBC_VERSION)/sysdeps/x86_64/strncase.S \
  glibc-$(GLIBC_VERSION)/sysdeps/x86_64/strncmp.S \
  glibc-$(GLIBC_VERSION)/sysdeps/x86_64/strnlen.S \
  glibc-$(GLIBC_VERSION)/sysdeps/x86_64/strpbrk.S \
  glibc-$(GLIBC_VERSION)/sysdeps/x86_64/strrchr.S \
  glibc-$(GLIBC_VERSION)/sysdeps/x86_64/strspn.S \
  glibc-$(GLIBC_VERSION)/sysdeps/x86_64/strtok.S \
  glibc-$(GLIBC_VERSION)/sysdeps/x86_64/strtok_r.S \
  glibc-$(GLIBC_VERSION)/sysdeps/x86_64/sub_n.S \
  glibc-$(GLIBC_VERSION)/sysdeps/x86_64/submul_1.S \
  glibc-$(GLIBC_VERSION)/sysdeps/x86_64/wcschr.S \
  glibc-$(GLIBC_VERSION)/sysdeps/x86_64/wcscmp.S \
  glibc-$(GLIBC_VERSION)/sysdeps/x86_64/wcslen.S \
  glibc-$(GLIBC_VERSION)/sysdeps/x86_64/wcsrchr.S

# these have TLS conflicts
#  glibc-$(GLIBC_VERSION)/sysdeps/x86_64/strcasecmp_l.S \
#  glibc-$(GLIBC_VERSION)/sysdeps/x86_64/strncase_l.S \

C_SOURCES = \
  glibc-$(GLIBC_VERSION)/assert/__assert.c \
  glibc-$(GLIBC_VERSION)/catgets/catgets.c \
  glibc-$(GLIBC_VERSION)/catgets/open_catalog.c \
  glibc-$(GLIBC_VERSION)/csu/dso_handle.c \
  glibc-$(GLIBC_VERSION)/csu/elf-init.c \
  glibc-$(GLIBC_VERSION)/csu/errno-loc.c \
  glibc-$(GLIBC_VERSION)/csu/errno.c \
  glibc-$(GLIBC_VERSION)/csu/gmon-start.c \
  glibc-$(GLIBC_VERSION)/csu/init-first.c \
  glibc-$(GLIBC_VERSION)/csu/init.c \
  glibc-$(GLIBC_VERSION)/csu/libc-start.c \
  glibc-$(GLIBC_VERSION)/csu/libc-tls.c \
  glibc-$(GLIBC_VERSION)/csu/version.c \
  glibc-$(GLIBC_VERSION)/ctype/ctype-extn.c \
  glibc-$(GLIBC_VERSION)/ctype/ctype-info.c \
  glibc-$(GLIBC_VERSION)/ctype/ctype.c \
  glibc-$(GLIBC_VERSION)/ctype/ctype_l.c \
  glibc-$(GLIBC_VERSION)/ctype/isctype.c \
  glibc-$(GLIBC_VERSION)/debug/asprintf_chk.c \
  glibc-$(GLIBC_VERSION)/debug/chk_fail.c \
  glibc-$(GLIBC_VERSION)/debug/confstr_chk.c \
  glibc-$(GLIBC_VERSION)/debug/dprintf_chk.c \
  glibc-$(GLIBC_VERSION)/debug/fdelt_chk.c \
  glibc-$(GLIBC_VERSION)/debug/fgets_chk.c \
  glibc-$(GLIBC_VERSION)/debug/fgets_u_chk.c \
  glibc-$(GLIBC_VERSION)/debug/fgetws_chk.c \
  glibc-$(GLIBC_VERSION)/debug/fgetws_u_chk.c \
  glibc-$(GLIBC_VERSION)/debug/fortify_fail.c \
  glibc-$(GLIBC_VERSION)/debug/fprintf_chk.c \
  glibc-$(GLIBC_VERSION)/debug/fread_chk.c \
  glibc-$(GLIBC_VERSION)/debug/fread_u_chk.c \
  glibc-$(GLIBC_VERSION)/debug/fwprintf_chk.c \
  glibc-$(GLIBC_VERSION)/debug/getcwd_chk.c \
  glibc-$(GLIBC_VERSION)/debug/getdomainname_chk.c \
  glibc-$(GLIBC_VERSION)/debug/getgroups_chk.c \
  glibc-$(GLIBC_VERSION)/debug/gethostname_chk.c \
  glibc-$(GLIBC_VERSION)/debug/getlogin_r_chk.c \
  glibc-$(GLIBC_VERSION)/debug/gets_chk.c \
  glibc-$(GLIBC_VERSION)/debug/getwd_chk.c \
  glibc-$(GLIBC_VERSION)/debug/longjmp_chk.c \
  glibc-$(GLIBC_VERSION)/debug/mbsnrtowcs_chk.c \
  glibc-$(GLIBC_VERSION)/debug/mbsrtowcs_chk.c \
  glibc-$(GLIBC_VERSION)/debug/mbstowcs_chk.c \
  glibc-$(GLIBC_VERSION)/debug/memcpy_chk.c \
  glibc-$(GLIBC_VERSION)/debug/memmove_chk.c \
  glibc-$(GLIBC_VERSION)/debug/mempcpy_chk.c \
  glibc-$(GLIBC_VERSION)/debug/memset_chk.c \
  glibc-$(GLIBC_VERSION)/debug/noophooks.c \
  glibc-$(GLIBC_VERSION)/debug/obprintf_chk.c \
  glibc-$(GLIBC_VERSION)/debug/poll_chk.c \
  glibc-$(GLIBC_VERSION)/debug/ppoll_chk.c \
  glibc-$(GLIBC_VERSION)/debug/pread64_chk.c \
  glibc-$(GLIBC_VERSION)/debug/pread_chk.c \
  glibc-$(GLIBC_VERSION)/debug/printf_chk.c \
  glibc-$(GLIBC_VERSION)/debug/ptsname_r_chk.c \
  glibc-$(GLIBC_VERSION)/debug/read_chk.c \
  glibc-$(GLIBC_VERSION)/debug/readlink_chk.c \
  glibc-$(GLIBC_VERSION)/debug/readlinkat_chk.c \
  glibc-$(GLIBC_VERSION)/debug/readonly-area.c \
  glibc-$(GLIBC_VERSION)/debug/realpath_chk.c \
  glibc-$(GLIBC_VERSION)/debug/recv_chk.c \
  glibc-$(GLIBC_VERSION)/debug/recvfrom_chk.c \
  glibc-$(GLIBC_VERSION)/debug/snprintf_chk.c \
  glibc-$(GLIBC_VERSION)/debug/sprintf_chk.c \
  glibc-$(GLIBC_VERSION)/debug/stack_chk_fail.c \
  glibc-$(GLIBC_VERSION)/debug/stack_chk_fail_local.c \
  glibc-$(GLIBC_VERSION)/debug/stpcpy_chk.c \
  glibc-$(GLIBC_VERSION)/debug/stpncpy_chk.c \
  glibc-$(GLIBC_VERSION)/debug/strcat_chk.c \
  glibc-$(GLIBC_VERSION)/debug/strcpy_chk.c \
  glibc-$(GLIBC_VERSION)/debug/strncat_chk.c \
  glibc-$(GLIBC_VERSION)/debug/strncpy_chk.c \
  glibc-$(GLIBC_VERSION)/debug/swprintf_chk.c \
  glibc-$(GLIBC_VERSION)/debug/ttyname_r_chk.c \
  glibc-$(GLIBC_VERSION)/debug/vasprintf_chk.c \
  glibc-$(GLIBC_VERSION)/debug/vdprintf_chk.c \
  glibc-$(GLIBC_VERSION)/debug/vfprintf_chk.c \
  glibc-$(GLIBC_VERSION)/debug/vfwprintf_chk.c \
  glibc-$(GLIBC_VERSION)/debug/vprintf_chk.c \
  glibc-$(GLIBC_VERSION)/debug/vsnprintf_chk.c \
  glibc-$(GLIBC_VERSION)/debug/vsprintf_chk.c \
  glibc-$(GLIBC_VERSION)/debug/vswprintf_chk.c \
  glibc-$(GLIBC_VERSION)/debug/vwprintf_chk.c \
  glibc-$(GLIBC_VERSION)/debug/wcpcpy_chk.c \
  glibc-$(GLIBC_VERSION)/debug/wcpncpy_chk.c \
  glibc-$(GLIBC_VERSION)/debug/wcrtomb_chk.c \
  glibc-$(GLIBC_VERSION)/debug/wcscat_chk.c \
  glibc-$(GLIBC_VERSION)/debug/wcscpy_chk.c \
  glibc-$(GLIBC_VERSION)/debug/wcsncat_chk.c \
  glibc-$(GLIBC_VERSION)/debug/wcsncpy_chk.c \
  glibc-$(GLIBC_VERSION)/debug/wcsnrtombs_chk.c \
  glibc-$(GLIBC_VERSION)/debug/wcsrtombs_chk.c \
  glibc-$(GLIBC_VERSION)/debug/wcstombs_chk.c \
  glibc-$(GLIBC_VERSION)/debug/wctomb_chk.c \
  glibc-$(GLIBC_VERSION)/debug/wmemcpy_chk.c \
  glibc-$(GLIBC_VERSION)/debug/wmemmove_chk.c \
  glibc-$(GLIBC_VERSION)/debug/wmempcpy_chk.c \
  glibc-$(GLIBC_VERSION)/debug/wmemset_chk.c \
  glibc-$(GLIBC_VERSION)/debug/wprintf_chk.c \
  glibc-$(GLIBC_VERSION)/elf/dl-addr.c \
  glibc-$(GLIBC_VERSION)/elf/dl-cache.c \
  glibc-$(GLIBC_VERSION)/elf/dl-close.c \
  glibc-$(GLIBC_VERSION)/elf/dl-conflict.c \
  glibc-$(GLIBC_VERSION)/elf/dl-debug.c \
  glibc-$(GLIBC_VERSION)/elf/dl-deps.c \
  glibc-$(GLIBC_VERSION)/elf/dl-error.c \
  glibc-$(GLIBC_VERSION)/elf/dl-execstack.c \
  glibc-$(GLIBC_VERSION)/elf/dl-fini.c \
  glibc-$(GLIBC_VERSION)/elf/dl-hwcaps.c \
  glibc-$(GLIBC_VERSION)/elf/dl-init.c \
  glibc-$(GLIBC_VERSION)/elf/dl-iteratephdr.c \
  glibc-$(GLIBC_VERSION)/elf/dl-libc.c \
  glibc-$(GLIBC_VERSION)/elf/dl-load.c \
  glibc-$(GLIBC_VERSION)/elf/dl-lookup.c \
  glibc-$(GLIBC_VERSION)/elf/dl-misc.c \
  glibc-$(GLIBC_VERSION)/elf/dl-object.c \
  glibc-$(GLIBC_VERSION)/elf/dl-open.c \
  glibc-$(GLIBC_VERSION)/elf/dl-origin.c \
  glibc-$(GLIBC_VERSION)/elf/dl-profile.c \
  glibc-$(GLIBC_VERSION)/elf/dl-profstub.c \
  glibc-$(GLIBC_VERSION)/elf/dl-reloc.c \
  glibc-$(GLIBC_VERSION)/elf/dl-scope.c \
  glibc-$(GLIBC_VERSION)/elf/dl-support.c \
  glibc-$(GLIBC_VERSION)/elf/dl-sym.c \
  glibc-$(GLIBC_VERSION)/elf/dl-sysdep.c \
  glibc-$(GLIBC_VERSION)/elf/dl-tls.c \
  glibc-$(GLIBC_VERSION)/elf/dl-tsd.c \
  glibc-$(GLIBC_VERSION)/elf/dl-version.c \
  glibc-$(GLIBC_VERSION)/elf/enbl-secure.c \
  glibc-$(GLIBC_VERSION)/gmon/bb_exit_func.c \
  glibc-$(GLIBC_VERSION)/gmon/bb_init_func.c \
  glibc-$(GLIBC_VERSION)/gmon/gmon.c \
  glibc-$(GLIBC_VERSION)/gmon/mcount.c \
  glibc-$(GLIBC_VERSION)/gmon/prof-freq.c \
  glibc-$(GLIBC_VERSION)/gmon/profil.c \
  glibc-$(GLIBC_VERSION)/gmon/sprofil.c \
  glibc-$(GLIBC_VERSION)/iconv/gconv.c \
  glibc-$(GLIBC_VERSION)/iconv/gconv_builtin.c \
  glibc-$(GLIBC_VERSION)/iconv/gconv_cache.c \
  glibc-$(GLIBC_VERSION)/iconv/gconv_close.c \
  glibc-$(GLIBC_VERSION)/iconv/gconv_conf.c \
  glibc-$(GLIBC_VERSION)/iconv/gconv_db.c \
  glibc-$(GLIBC_VERSION)/iconv/gconv_dl.c \
  glibc-$(GLIBC_VERSION)/iconv/gconv_open.c \
  glibc-$(GLIBC_VERSION)/iconv/gconv_simple.c \
  glibc-$(GLIBC_VERSION)/iconv/gconv_trans.c \
  glibc-$(GLIBC_VERSION)/iconv/iconv.c \
  glibc-$(GLIBC_VERSION)/iconv/iconv_close.c \
  glibc-$(GLIBC_VERSION)/iconv/iconv_open.c \
  glibc-$(GLIBC_VERSION)/intl/bindtextdom.c \
  glibc-$(GLIBC_VERSION)/intl/dcgettext.c \
  glibc-$(GLIBC_VERSION)/intl/dcigettext.c \
  glibc-$(GLIBC_VERSION)/intl/dcngettext.c \
  glibc-$(GLIBC_VERSION)/intl/dgettext.c \
  glibc-$(GLIBC_VERSION)/intl/dngettext.c \
  glibc-$(GLIBC_VERSION)/intl/explodename.c \
  glibc-$(GLIBC_VERSION)/intl/finddomain.c \
  glibc-$(GLIBC_VERSION)/intl/gettext.c \
  glibc-$(GLIBC_VERSION)/intl/hash-string.c \
  glibc-$(GLIBC_VERSION)/intl/loadmsgcat.c \
  glibc-$(GLIBC_VERSION)/intl/localealias.c \
  glibc-$(GLIBC_VERSION)/intl/ngettext.c \
  glibc-$(GLIBC_VERSION)/intl/plural-exp.c \
  glibc-$(GLIBC_VERSION)/intl/plural.c \
  glibc-$(GLIBC_VERSION)/intl/textdomain.c \
  glibc-$(GLIBC_VERSION)/io/fcntl.c \
  glibc-$(GLIBC_VERSION)/io/fxstat.c \
  glibc-$(GLIBC_VERSION)/io/fxstat64.c \
  glibc-$(GLIBC_VERSION)/io/fxstatat.c \
  glibc-$(GLIBC_VERSION)/io/fxstatat64.c \
  glibc-$(GLIBC_VERSION)/io/have_o_cloexec.c \
  glibc-$(GLIBC_VERSION)/io/open64.c \
  glibc-$(GLIBC_VERSION)/io/pipe.c \
  glibc-$(GLIBC_VERSION)/io/readlink.c \
  glibc-$(GLIBC_VERSION)/io/ttyname_r.c \
  glibc-$(GLIBC_VERSION)/io/umask.c \
  glibc-$(GLIBC_VERSION)/libio/__fbufsize.c \
  glibc-$(GLIBC_VERSION)/libio/__flbf.c \
  glibc-$(GLIBC_VERSION)/libio/__fpending.c \
  glibc-$(GLIBC_VERSION)/libio/__fpurge.c \
  glibc-$(GLIBC_VERSION)/libio/__freadable.c \
  glibc-$(GLIBC_VERSION)/libio/__freading.c \
  glibc-$(GLIBC_VERSION)/libio/__fsetlocking.c \
  glibc-$(GLIBC_VERSION)/libio/__fwritable.c \
  glibc-$(GLIBC_VERSION)/libio/__fwriting.c \
  glibc-$(GLIBC_VERSION)/libio/clearerr.c \
  glibc-$(GLIBC_VERSION)/libio/clearerr_u.c \
  glibc-$(GLIBC_VERSION)/libio/fcloseall.c \
  glibc-$(GLIBC_VERSION)/libio/feof.c \
  glibc-$(GLIBC_VERSION)/libio/feof_u.c \
  glibc-$(GLIBC_VERSION)/libio/ferror.c \
  glibc-$(GLIBC_VERSION)/libio/ferror_u.c \
  glibc-$(GLIBC_VERSION)/libio/filedoalloc.c \
  glibc-$(GLIBC_VERSION)/libio/fileno.c \
  glibc-$(GLIBC_VERSION)/libio/fileops.c \
  glibc-$(GLIBC_VERSION)/libio/fmemopen.c \
  glibc-$(GLIBC_VERSION)/libio/fputc.c \
  glibc-$(GLIBC_VERSION)/libio/fputc_u.c \
  glibc-$(GLIBC_VERSION)/libio/fputwc.c \
  glibc-$(GLIBC_VERSION)/libio/fputwc_u.c \
  glibc-$(GLIBC_VERSION)/libio/freopen.c \
  glibc-$(GLIBC_VERSION)/libio/freopen64.c \
  glibc-$(GLIBC_VERSION)/libio/fseek.c \
  glibc-$(GLIBC_VERSION)/libio/fseeko.c \
  glibc-$(GLIBC_VERSION)/libio/fseeko64.c \
  glibc-$(GLIBC_VERSION)/libio/ftello.c \
  glibc-$(GLIBC_VERSION)/libio/ftello64.c \
  glibc-$(GLIBC_VERSION)/libio/fwide.c \
  glibc-$(GLIBC_VERSION)/libio/fwprintf.c \
  glibc-$(GLIBC_VERSION)/libio/fwscanf.c \
  glibc-$(GLIBC_VERSION)/libio/genops.c \
  glibc-$(GLIBC_VERSION)/libio/getc.c \
  glibc-$(GLIBC_VERSION)/libio/getc_u.c \
  glibc-$(GLIBC_VERSION)/libio/getchar.c \
  glibc-$(GLIBC_VERSION)/libio/getchar_u.c \
  glibc-$(GLIBC_VERSION)/libio/getwc.c \
  glibc-$(GLIBC_VERSION)/libio/getwc_u.c \
  glibc-$(GLIBC_VERSION)/libio/getwchar.c \
  glibc-$(GLIBC_VERSION)/libio/getwchar_u.c \
  glibc-$(GLIBC_VERSION)/libio/iofclose.c \
  glibc-$(GLIBC_VERSION)/libio/iofdopen.c \
  glibc-$(GLIBC_VERSION)/libio/iofflush.c \
  glibc-$(GLIBC_VERSION)/libio/iofflush_u.c \
  glibc-$(GLIBC_VERSION)/libio/iofgetpos.c \
  glibc-$(GLIBC_VERSION)/libio/iofgetpos64.c \
  glibc-$(GLIBC_VERSION)/libio/iofgets.c \
  glibc-$(GLIBC_VERSION)/libio/iofgets_u.c \
  glibc-$(GLIBC_VERSION)/libio/iofgetws.c \
  glibc-$(GLIBC_VERSION)/libio/iofgetws_u.c \
  glibc-$(GLIBC_VERSION)/libio/iofopen.c \
  glibc-$(GLIBC_VERSION)/libio/iofopen64.c \
  glibc-$(GLIBC_VERSION)/libio/iofopncook.c \
  glibc-$(GLIBC_VERSION)/libio/iofputs.c \
  glibc-$(GLIBC_VERSION)/libio/iofputs_u.c \
  glibc-$(GLIBC_VERSION)/libio/iofputws.c \
  glibc-$(GLIBC_VERSION)/libio/iofputws_u.c \
  glibc-$(GLIBC_VERSION)/libio/iofread.c \
  glibc-$(GLIBC_VERSION)/libio/iofread_u.c \
  glibc-$(GLIBC_VERSION)/libio/iofsetpos.c \
  glibc-$(GLIBC_VERSION)/libio/iofsetpos64.c \
  glibc-$(GLIBC_VERSION)/libio/ioftell.c \
  glibc-$(GLIBC_VERSION)/libio/iofwide.c \
  glibc-$(GLIBC_VERSION)/libio/iofwrite.c \
  glibc-$(GLIBC_VERSION)/libio/iofwrite_u.c \
  glibc-$(GLIBC_VERSION)/libio/iogetdelim.c \
  glibc-$(GLIBC_VERSION)/libio/iogetline.c \
  glibc-$(GLIBC_VERSION)/libio/iogets.c \
  glibc-$(GLIBC_VERSION)/libio/iogetwline.c \
  glibc-$(GLIBC_VERSION)/libio/iopadn.c \
  glibc-$(GLIBC_VERSION)/libio/iopopen.c \
  glibc-$(GLIBC_VERSION)/libio/ioputs.c \
  glibc-$(GLIBC_VERSION)/libio/ioseekoff.c \
  glibc-$(GLIBC_VERSION)/libio/ioseekpos.c \
  glibc-$(GLIBC_VERSION)/libio/iosetbuffer.c \
  glibc-$(GLIBC_VERSION)/libio/iosetvbuf.c \
  glibc-$(GLIBC_VERSION)/libio/ioungetc.c \
  glibc-$(GLIBC_VERSION)/libio/ioungetwc.c \
  glibc-$(GLIBC_VERSION)/libio/iovdprintf.c \
  glibc-$(GLIBC_VERSION)/libio/iovsprintf.c \
  glibc-$(GLIBC_VERSION)/libio/iovsscanf.c \
  glibc-$(GLIBC_VERSION)/libio/iovswscanf.c \
  glibc-$(GLIBC_VERSION)/libio/iowpadn.c \
  glibc-$(GLIBC_VERSION)/libio/memstream.c \
  glibc-$(GLIBC_VERSION)/libio/obprintf.c \
  glibc-$(GLIBC_VERSION)/libio/pclose.c \
  glibc-$(GLIBC_VERSION)/libio/peekc.c \
  glibc-$(GLIBC_VERSION)/libio/putc.c \
  glibc-$(GLIBC_VERSION)/libio/putc_u.c \
  glibc-$(GLIBC_VERSION)/libio/putchar.c \
  glibc-$(GLIBC_VERSION)/libio/putchar_u.c \
  glibc-$(GLIBC_VERSION)/libio/putwc.c \
  glibc-$(GLIBC_VERSION)/libio/putwc_u.c \
  glibc-$(GLIBC_VERSION)/libio/putwchar.c \
  glibc-$(GLIBC_VERSION)/libio/putwchar_u.c \
  glibc-$(GLIBC_VERSION)/libio/rewind.c \
  glibc-$(GLIBC_VERSION)/libio/setbuf.c \
  glibc-$(GLIBC_VERSION)/libio/setlinebuf.c \
  glibc-$(GLIBC_VERSION)/libio/stdfiles.c \
  glibc-$(GLIBC_VERSION)/libio/stdio.c \
  glibc-$(GLIBC_VERSION)/libio/strops.c \
  glibc-$(GLIBC_VERSION)/libio/swprintf.c \
  glibc-$(GLIBC_VERSION)/libio/swscanf.c \
  glibc-$(GLIBC_VERSION)/libio/vasprintf.c \
  glibc-$(GLIBC_VERSION)/libio/vscanf.c \
  glibc-$(GLIBC_VERSION)/libio/vsnprintf.c \
  glibc-$(GLIBC_VERSION)/libio/vswprintf.c \
  glibc-$(GLIBC_VERSION)/libio/vwprintf.c \
  glibc-$(GLIBC_VERSION)/libio/vwscanf.c \
  glibc-$(GLIBC_VERSION)/libio/wfiledoalloc.c \
  glibc-$(GLIBC_VERSION)/libio/wfileops.c \
  glibc-$(GLIBC_VERSION)/libio/wgenops.c \
  glibc-$(GLIBC_VERSION)/libio/wmemstream.c \
  glibc-$(GLIBC_VERSION)/libio/wprintf.c \
  glibc-$(GLIBC_VERSION)/libio/wscanf.c \
  glibc-$(GLIBC_VERSION)/libio/wstrops.c \
  glibc-$(GLIBC_VERSION)/locale/C-address.c \
  glibc-$(GLIBC_VERSION)/locale/C-collate.c \
  glibc-$(GLIBC_VERSION)/locale/C-ctype.c \
  glibc-$(GLIBC_VERSION)/locale/C-identification.c \
  glibc-$(GLIBC_VERSION)/locale/C-measurement.c \
  glibc-$(GLIBC_VERSION)/locale/C-messages.c \
  glibc-$(GLIBC_VERSION)/locale/C-monetary.c \
  glibc-$(GLIBC_VERSION)/locale/C-name.c \
  glibc-$(GLIBC_VERSION)/locale/C-numeric.c \
  glibc-$(GLIBC_VERSION)/locale/C-paper.c \
  glibc-$(GLIBC_VERSION)/locale/C-telephone.c \
  glibc-$(GLIBC_VERSION)/locale/C-time.c \
  glibc-$(GLIBC_VERSION)/locale/C_name.c \
  glibc-$(GLIBC_VERSION)/locale/SYS_libc.c \
  glibc-$(GLIBC_VERSION)/locale/coll-lookup.c \
  glibc-$(GLIBC_VERSION)/locale/duplocale.c \
  glibc-$(GLIBC_VERSION)/locale/findlocale.c \
  glibc-$(GLIBC_VERSION)/locale/freelocale.c \
  glibc-$(GLIBC_VERSION)/locale/global-locale.c \
  glibc-$(GLIBC_VERSION)/locale/lc-address.c \
  glibc-$(GLIBC_VERSION)/locale/lc-collate.c \
  glibc-$(GLIBC_VERSION)/locale/lc-ctype.c \
  glibc-$(GLIBC_VERSION)/locale/lc-identification.c \
  glibc-$(GLIBC_VERSION)/locale/lc-measurement.c \
  glibc-$(GLIBC_VERSION)/locale/lc-messages.c \
  glibc-$(GLIBC_VERSION)/locale/lc-monetary.c \
  glibc-$(GLIBC_VERSION)/locale/lc-name.c \
  glibc-$(GLIBC_VERSION)/locale/lc-numeric.c \
  glibc-$(GLIBC_VERSION)/locale/lc-paper.c \
  glibc-$(GLIBC_VERSION)/locale/lc-telephone.c \
  glibc-$(GLIBC_VERSION)/locale/lc-time.c \
  glibc-$(GLIBC_VERSION)/locale/loadarchive.c \
  glibc-$(GLIBC_VERSION)/locale/loadlocale.c \
  glibc-$(GLIBC_VERSION)/locale/localeconv.c \
  glibc-$(GLIBC_VERSION)/locale/localename.c \
  glibc-$(GLIBC_VERSION)/locale/mb_cur_max.c \
  glibc-$(GLIBC_VERSION)/locale/newlocale.c \
  glibc-$(GLIBC_VERSION)/locale/nl_langinfo.c \
  glibc-$(GLIBC_VERSION)/locale/nl_langinfo_l.c \
  glibc-$(GLIBC_VERSION)/locale/setlocale.c \
  glibc-$(GLIBC_VERSION)/locale/uselocale.c \
  glibc-$(GLIBC_VERSION)/locale/xlocale.c \
  glibc-$(GLIBC_VERSION)/malloc/malloc.c \
  glibc-$(GLIBC_VERSION)/malloc/mcheck.c \
  glibc-$(GLIBC_VERSION)/malloc/morecore.c \
  glibc-$(GLIBC_VERSION)/malloc/mtrace.c \
  glibc-$(GLIBC_VERSION)/malloc/obstack.c \
  glibc-$(GLIBC_VERSION)/malloc/set-freeres.c \
  glibc-$(GLIBC_VERSION)/malloc/thread-freeres.c \
  glibc-$(GLIBC_VERSION)/math/cabs.c \
  glibc-$(GLIBC_VERSION)/math/cabsf.c \
  glibc-$(GLIBC_VERSION)/math/cabsl.c \
  glibc-$(GLIBC_VERSION)/math/carg.c \
  glibc-$(GLIBC_VERSION)/math/cargf.c \
  glibc-$(GLIBC_VERSION)/math/cargl.c \
  glibc-$(GLIBC_VERSION)/math/cimag.c \
  glibc-$(GLIBC_VERSION)/math/cimagf.c \
  glibc-$(GLIBC_VERSION)/math/cimagl.c \
  glibc-$(GLIBC_VERSION)/math/conj.c \
  glibc-$(GLIBC_VERSION)/math/conjf.c \
  glibc-$(GLIBC_VERSION)/math/conjl.c \
  glibc-$(GLIBC_VERSION)/math/creal.c \
  glibc-$(GLIBC_VERSION)/math/crealf.c \
  glibc-$(GLIBC_VERSION)/math/creall.c \
  glibc-$(GLIBC_VERSION)/math/e_exp10f.c \
  glibc-$(GLIBC_VERSION)/math/e_scalb.c \
  glibc-$(GLIBC_VERSION)/math/e_scalbf.c \
  glibc-$(GLIBC_VERSION)/math/fpu_control.c \
  glibc-$(GLIBC_VERSION)/math/ieee-math.c \
  glibc-$(GLIBC_VERSION)/math/k_sincosl.c \
  glibc-$(GLIBC_VERSION)/math/s_cacos.c \
  glibc-$(GLIBC_VERSION)/math/s_cacosf.c \
  glibc-$(GLIBC_VERSION)/math/s_cacosl.c \
  glibc-$(GLIBC_VERSION)/math/s_cacosh.c \
  glibc-$(GLIBC_VERSION)/math/s_cacoshf.c \
  glibc-$(GLIBC_VERSION)/math/s_cacoshl.c \
  glibc-$(GLIBC_VERSION)/math/s_casin.c \
  glibc-$(GLIBC_VERSION)/math/s_casinf.c \
  glibc-$(GLIBC_VERSION)/math/s_casinh.c \
  glibc-$(GLIBC_VERSION)/math/s_casinhf.c \
  glibc-$(GLIBC_VERSION)/math/s_casinhl.c \
  glibc-$(GLIBC_VERSION)/math/s_casinl.c \
  glibc-$(GLIBC_VERSION)/math/s_catan.c \
  glibc-$(GLIBC_VERSION)/math/s_catanf.c \
  glibc-$(GLIBC_VERSION)/math/s_catanl.c \
  glibc-$(GLIBC_VERSION)/math/s_catanh.c \
  glibc-$(GLIBC_VERSION)/math/s_catanhf.c \
  glibc-$(GLIBC_VERSION)/math/s_catanhl.c \
  glibc-$(GLIBC_VERSION)/math/s_ccos.c \
  glibc-$(GLIBC_VERSION)/math/s_ccosf.c \
  glibc-$(GLIBC_VERSION)/math/s_ccosh.c \
  glibc-$(GLIBC_VERSION)/math/s_ccoshf.c \
  glibc-$(GLIBC_VERSION)/math/s_ccoshl.c \
  glibc-$(GLIBC_VERSION)/math/s_ccosl.c \
  glibc-$(GLIBC_VERSION)/math/s_cexp.c \
  glibc-$(GLIBC_VERSION)/math/s_cexpf.c \
  glibc-$(GLIBC_VERSION)/math/s_cexpl.c \
  glibc-$(GLIBC_VERSION)/math/s_clog.c \
  glibc-$(GLIBC_VERSION)/math/s_clog10.c \
  glibc-$(GLIBC_VERSION)/math/s_clog10f.c \
  glibc-$(GLIBC_VERSION)/math/s_clog10l.c \
  glibc-$(GLIBC_VERSION)/math/s_clogf.c \
  glibc-$(GLIBC_VERSION)/math/s_clogl.c \
  glibc-$(GLIBC_VERSION)/math/s_cpow.c \
  glibc-$(GLIBC_VERSION)/math/s_cpowf.c \
  glibc-$(GLIBC_VERSION)/math/s_cpowl.c \
  glibc-$(GLIBC_VERSION)/math/s_cproj.c \
  glibc-$(GLIBC_VERSION)/math/s_cprojf.c \
  glibc-$(GLIBC_VERSION)/math/s_cprojl.c \
  glibc-$(GLIBC_VERSION)/math/s_csin.c \
  glibc-$(GLIBC_VERSION)/math/s_csinf.c \
  glibc-$(GLIBC_VERSION)/math/s_csinh.c \
  glibc-$(GLIBC_VERSION)/math/s_csinhf.c \
  glibc-$(GLIBC_VERSION)/math/s_csinhl.c \
  glibc-$(GLIBC_VERSION)/math/s_csinl.c \
  glibc-$(GLIBC_VERSION)/math/s_csqrt.c \
  glibc-$(GLIBC_VERSION)/math/s_csqrtf.c \
  glibc-$(GLIBC_VERSION)/math/s_csqrtl.c \
  glibc-$(GLIBC_VERSION)/math/s_ctan.c \
  glibc-$(GLIBC_VERSION)/math/s_ctanf.c \
  glibc-$(GLIBC_VERSION)/math/s_ctanh.c \
  glibc-$(GLIBC_VERSION)/math/s_ctanhf.c \
  glibc-$(GLIBC_VERSION)/math/s_ctanhl.c \
  glibc-$(GLIBC_VERSION)/math/s_ctanl.c \
  glibc-$(GLIBC_VERSION)/math/s_fdim.c \
  glibc-$(GLIBC_VERSION)/math/s_fdimf.c \
  glibc-$(GLIBC_VERSION)/math/s_ldexp.c \
  glibc-$(GLIBC_VERSION)/math/s_ldexpf.c \
  glibc-$(GLIBC_VERSION)/math/s_ldexpl.c \
  glibc-$(GLIBC_VERSION)/math/s_nan.c \
  glibc-$(GLIBC_VERSION)/math/s_nanf.c \
  glibc-$(GLIBC_VERSION)/math/s_nanl.c \
  glibc-$(GLIBC_VERSION)/math/s_nextafter.c \
  glibc-$(GLIBC_VERSION)/math/s_nexttowardl.c \
  glibc-$(GLIBC_VERSION)/math/s_significand.c \
  glibc-$(GLIBC_VERSION)/math/s_significandf.c \
  glibc-$(GLIBC_VERSION)/math/setfpucw.c \
  glibc-$(GLIBC_VERSION)/math/w_acos.c \
  glibc-$(GLIBC_VERSION)/math/w_acosf.c \
  glibc-$(GLIBC_VERSION)/math/w_acosh.c \
  glibc-$(GLIBC_VERSION)/math/w_acoshf.c \
  glibc-$(GLIBC_VERSION)/math/w_acoshl.c \
  glibc-$(GLIBC_VERSION)/math/w_acosl.c \
  glibc-$(GLIBC_VERSION)/math/w_asin.c \
  glibc-$(GLIBC_VERSION)/math/w_asinf.c \
  glibc-$(GLIBC_VERSION)/math/w_asinl.c \
  glibc-$(GLIBC_VERSION)/math/w_atan2.c \
  glibc-$(GLIBC_VERSION)/math/w_atan2f.c \
  glibc-$(GLIBC_VERSION)/math/w_atan2l.c \
  glibc-$(GLIBC_VERSION)/math/w_atanh.c \
  glibc-$(GLIBC_VERSION)/math/w_atanhf.c \
  glibc-$(GLIBC_VERSION)/math/w_atanhl.c \
  glibc-$(GLIBC_VERSION)/math/w_cosh.c \
  glibc-$(GLIBC_VERSION)/math/w_coshf.c \
  glibc-$(GLIBC_VERSION)/math/w_coshl.c \
  glibc-$(GLIBC_VERSION)/math/w_drem.c \
  glibc-$(GLIBC_VERSION)/math/w_dremf.c \
  glibc-$(GLIBC_VERSION)/math/w_dreml.c \
  glibc-$(GLIBC_VERSION)/math/w_exp10.c \
  glibc-$(GLIBC_VERSION)/math/w_exp10f.c \
  glibc-$(GLIBC_VERSION)/math/w_exp10l.c \
  glibc-$(GLIBC_VERSION)/math/w_exp2.c \
  glibc-$(GLIBC_VERSION)/math/w_exp2f.c \
  glibc-$(GLIBC_VERSION)/math/w_exp2l.c \
  glibc-$(GLIBC_VERSION)/math/w_fmod.c \
  glibc-$(GLIBC_VERSION)/math/w_fmodf.c \
  glibc-$(GLIBC_VERSION)/math/w_fmodl.c \
  glibc-$(GLIBC_VERSION)/math/w_hypot.c \
  glibc-$(GLIBC_VERSION)/math/w_hypotf.c \
  glibc-$(GLIBC_VERSION)/math/w_hypotl.c \
  glibc-$(GLIBC_VERSION)/math/w_ilogb.c \
  glibc-$(GLIBC_VERSION)/math/w_ilogbf.c \
  glibc-$(GLIBC_VERSION)/math/w_ilogbl.c \
  glibc-$(GLIBC_VERSION)/math/w_j0.c \
  glibc-$(GLIBC_VERSION)/math/w_j0f.c \
  glibc-$(GLIBC_VERSION)/math/w_j0l.c \
  glibc-$(GLIBC_VERSION)/math/w_j1.c \
  glibc-$(GLIBC_VERSION)/math/w_j1f.c \
  glibc-$(GLIBC_VERSION)/math/w_j1l.c \
  glibc-$(GLIBC_VERSION)/math/w_jn.c \
  glibc-$(GLIBC_VERSION)/math/w_jnf.c \
  glibc-$(GLIBC_VERSION)/math/w_jnl.c \
  glibc-$(GLIBC_VERSION)/math/w_lgamma.c \
  glibc-$(GLIBC_VERSION)/math/w_lgamma_r.c \
  glibc-$(GLIBC_VERSION)/math/w_lgammaf.c \
  glibc-$(GLIBC_VERSION)/math/w_lgammaf_r.c \
  glibc-$(GLIBC_VERSION)/math/w_lgammal.c \
  glibc-$(GLIBC_VERSION)/math/w_lgammal_r.c \
  glibc-$(GLIBC_VERSION)/math/w_log.c \
  glibc-$(GLIBC_VERSION)/math/w_log2.c \
  glibc-$(GLIBC_VERSION)/math/w_log2f.c \
  glibc-$(GLIBC_VERSION)/math/w_log2l.c \
  glibc-$(GLIBC_VERSION)/math/w_log10.c \
  glibc-$(GLIBC_VERSION)/math/w_log10f.c \
  glibc-$(GLIBC_VERSION)/math/w_logf.c \
  glibc-$(GLIBC_VERSION)/math/w_logl.c \
  glibc-$(GLIBC_VERSION)/math/w_pow.c \
  glibc-$(GLIBC_VERSION)/math/w_powf.c \
  glibc-$(GLIBC_VERSION)/math/w_powl.c \
  glibc-$(GLIBC_VERSION)/math/w_remainder.c \
  glibc-$(GLIBC_VERSION)/math/w_remainderf.c \
  glibc-$(GLIBC_VERSION)/math/w_remainderl.c \
  glibc-$(GLIBC_VERSION)/math/w_scalb.c \
  glibc-$(GLIBC_VERSION)/math/w_scalbf.c \
  glibc-$(GLIBC_VERSION)/math/w_scalbl.c \
  glibc-$(GLIBC_VERSION)/math/w_sinh.c \
  glibc-$(GLIBC_VERSION)/math/w_sinhf.c \
  glibc-$(GLIBC_VERSION)/math/w_sinhl.c \
  glibc-$(GLIBC_VERSION)/math/w_sqrt.c \
  glibc-$(GLIBC_VERSION)/math/w_sqrtf.c \
  glibc-$(GLIBC_VERSION)/math/w_sqrtl.c \
  glibc-$(GLIBC_VERSION)/math/w_tgamma.c \
  glibc-$(GLIBC_VERSION)/math/w_tgammaf.c \
  glibc-$(GLIBC_VERSION)/math/w_tgammal.c \
  glibc-$(GLIBC_VERSION)/misc/init-misc.c \
  glibc-$(GLIBC_VERSION)/misc/mkstemp.c \
  glibc-$(GLIBC_VERSION)/misc/mmap.c \
  glibc-$(GLIBC_VERSION)/misc/mmap64.c \
  glibc-$(GLIBC_VERSION)/misc/mprotect.c \
  glibc-$(GLIBC_VERSION)/misc/munmap.c \
  glibc-$(GLIBC_VERSION)/misc/sbrk.c \
  glibc-$(GLIBC_VERSION)/misc/tsearch.c \
  glibc-$(GLIBC_VERSION)/nptl/sysdeps/llamaos/flockfile.c \
  glibc-$(GLIBC_VERSION)/nptl/sysdeps/llamaos/funlockfile.c \
  glibc-$(GLIBC_VERSION)/nptl/sysdeps/llamaos/jmp-unwind.c \
  glibc-$(GLIBC_VERSION)/nptl/sysdeps/llamaos/pthread.c \
  glibc-$(GLIBC_VERSION)/nptl/sysdeps/pthread/flockfile.c \
  glibc-$(GLIBC_VERSION)/nptl/sysdeps/pthread/ftrylockfile.c \
  glibc-$(GLIBC_VERSION)/nptl/sysdeps/pthread/funlockfile.c \
  glibc-$(GLIBC_VERSION)/nptl/alloca_cutoff.c \
  glibc-$(GLIBC_VERSION)/posix/environ.c \
  glibc-$(GLIBC_VERSION)/posix/execve.c \
  glibc-$(GLIBC_VERSION)/posix/fork.c \
  glibc-$(GLIBC_VERSION)/posix/fpathconf.c \
  glibc-$(GLIBC_VERSION)/posix/getegid.c \
  glibc-$(GLIBC_VERSION)/posix/geteuid.c \
  glibc-$(GLIBC_VERSION)/posix/getgid.c \
  glibc-$(GLIBC_VERSION)/posix/getopt.c \
  glibc-$(GLIBC_VERSION)/posix/getuid.c \
  glibc-$(GLIBC_VERSION)/posix/wait.c \
  glibc-$(GLIBC_VERSION)/setjmp/longjmp.c \
  glibc-$(GLIBC_VERSION)/setjmp/sigjmp.c \
  glibc-$(GLIBC_VERSION)/signal/sigaction.c \
  glibc-$(GLIBC_VERSION)/signal/sigaddset.c \
  glibc-$(GLIBC_VERSION)/signal/signal.c \
  glibc-$(GLIBC_VERSION)/signal/sigprocmask.c \
  glibc-$(GLIBC_VERSION)/stdio-common/_itoa.c \
  glibc-$(GLIBC_VERSION)/stdio-common/_itowa.c \
  glibc-$(GLIBC_VERSION)/stdio-common/asprintf.c \
  glibc-$(GLIBC_VERSION)/stdio-common/dprintf.c \
  glibc-$(GLIBC_VERSION)/stdio-common/fprintf.c \
  glibc-$(GLIBC_VERSION)/stdio-common/fscanf.c \
  glibc-$(GLIBC_VERSION)/stdio-common/fxprintf.c \
  glibc-$(GLIBC_VERSION)/stdio-common/getline.c \
  glibc-$(GLIBC_VERSION)/stdio-common/getw.c \
  glibc-$(GLIBC_VERSION)/stdio-common/isoc99_fscanf.c \
  glibc-$(GLIBC_VERSION)/stdio-common/isoc99_scanf.c \
  glibc-$(GLIBC_VERSION)/stdio-common/isoc99_sscanf.c \
  glibc-$(GLIBC_VERSION)/stdio-common/isoc99_vfscanf.c \
  glibc-$(GLIBC_VERSION)/stdio-common/isoc99_vscanf.c \
  glibc-$(GLIBC_VERSION)/stdio-common/isoc99_vsscanf.c \
  glibc-$(GLIBC_VERSION)/stdio-common/itoa-digits.c \
  glibc-$(GLIBC_VERSION)/stdio-common/itoa-udigits.c \
  glibc-$(GLIBC_VERSION)/stdio-common/itowa-digits.c \
  glibc-$(GLIBC_VERSION)/stdio-common/perror.c \
  glibc-$(GLIBC_VERSION)/stdio-common/printf-parsemb.c \
  glibc-$(GLIBC_VERSION)/stdio-common/printf-parsewc.c \
  glibc-$(GLIBC_VERSION)/stdio-common/printf-prs.c \
  glibc-$(GLIBC_VERSION)/stdio-common/printf.c \
  glibc-$(GLIBC_VERSION)/stdio-common/printf_fp.c \
  glibc-$(GLIBC_VERSION)/stdio-common/printf_size.c \
  glibc-$(GLIBC_VERSION)/stdio-common/psiginfo.c \
  glibc-$(GLIBC_VERSION)/stdio-common/psignal.c \
  glibc-$(GLIBC_VERSION)/stdio-common/putw.c \
  glibc-$(GLIBC_VERSION)/stdio-common/reg-modifier.c \
  glibc-$(GLIBC_VERSION)/stdio-common/reg-printf.c \
  glibc-$(GLIBC_VERSION)/stdio-common/reg-type.c \
  glibc-$(GLIBC_VERSION)/stdio-common/remove.c \
  glibc-$(GLIBC_VERSION)/stdio-common/rename.c \
  glibc-$(GLIBC_VERSION)/stdio-common/renameat.c \
  glibc-$(GLIBC_VERSION)/stdio-common/scanf.c \
  glibc-$(GLIBC_VERSION)/stdio-common/snprintf.c \
  glibc-$(GLIBC_VERSION)/stdio-common/sprintf.c \
  glibc-$(GLIBC_VERSION)/stdio-common/sscanf.c \
  glibc-$(GLIBC_VERSION)/stdio-common/tempnam.c \
  glibc-$(GLIBC_VERSION)/stdio-common/tmpfile.c \
  glibc-$(GLIBC_VERSION)/stdio-common/tmpfile64.c \
  glibc-$(GLIBC_VERSION)/stdio-common/tmpnam.c \
  glibc-$(GLIBC_VERSION)/stdio-common/tmpnam_r.c \
  glibc-$(GLIBC_VERSION)/stdio-common/vfprintf.c \
  glibc-$(GLIBC_VERSION)/stdio-common/vfscanf.c \
  glibc-$(GLIBC_VERSION)/stdio-common/vfwprintf.c \
  glibc-$(GLIBC_VERSION)/stdio-common/vfwscanf.c \
  glibc-$(GLIBC_VERSION)/stdio-common/vprintf.c \
  glibc-$(GLIBC_VERSION)/stdlib/a64l.c \
  glibc-$(GLIBC_VERSION)/stdlib/abs.c \
  glibc-$(GLIBC_VERSION)/stdlib/at_quick_exit.c \
  glibc-$(GLIBC_VERSION)/stdlib/atexit.c \
  glibc-$(GLIBC_VERSION)/stdlib/atof.c \
  glibc-$(GLIBC_VERSION)/stdlib/atoi.c \
  glibc-$(GLIBC_VERSION)/stdlib/atol.c \
  glibc-$(GLIBC_VERSION)/stdlib/atoll.c \
  glibc-$(GLIBC_VERSION)/stdlib/bsearch.c \
  glibc-$(GLIBC_VERSION)/stdlib/canonicalize.c \
  glibc-$(GLIBC_VERSION)/stdlib/cmp.c \
  glibc-$(GLIBC_VERSION)/stdlib/cxa_at_quick_exit.c \
  glibc-$(GLIBC_VERSION)/stdlib/cxa_atexit.c \
  glibc-$(GLIBC_VERSION)/stdlib/cxa_finalize.c \
  glibc-$(GLIBC_VERSION)/stdlib/div.c \
  glibc-$(GLIBC_VERSION)/stdlib/divmod_1.c \
  glibc-$(GLIBC_VERSION)/stdlib/divrem.c \
  glibc-$(GLIBC_VERSION)/stdlib/drand48-iter.c \
  glibc-$(GLIBC_VERSION)/stdlib/drand48.c \
  glibc-$(GLIBC_VERSION)/stdlib/drand48_r.c \
  glibc-$(GLIBC_VERSION)/stdlib/erand48.c \
  glibc-$(GLIBC_VERSION)/stdlib/erand48_r.c \
  glibc-$(GLIBC_VERSION)/stdlib/exit.c \
  glibc-$(GLIBC_VERSION)/stdlib/fmtmsg.c \
  glibc-$(GLIBC_VERSION)/stdlib/fpioconst.c \
  glibc-$(GLIBC_VERSION)/stdlib/getcontext.c \
  glibc-$(GLIBC_VERSION)/stdlib/getenv.c \
  glibc-$(GLIBC_VERSION)/stdlib/getsubopt.c \
  glibc-$(GLIBC_VERSION)/stdlib/grouping.c \
  glibc-$(GLIBC_VERSION)/stdlib/groupingwc.c \
  glibc-$(GLIBC_VERSION)/stdlib/inlines.c \
  glibc-$(GLIBC_VERSION)/stdlib/jrand48.c \
  glibc-$(GLIBC_VERSION)/stdlib/jrand48_r.c \
  glibc-$(GLIBC_VERSION)/stdlib/l64a.c \
  glibc-$(GLIBC_VERSION)/stdlib/lcong48.c \
  glibc-$(GLIBC_VERSION)/stdlib/lcong48_r.c \
  glibc-$(GLIBC_VERSION)/stdlib/llabs.c \
  glibc-$(GLIBC_VERSION)/stdlib/lldiv.c \
  glibc-$(GLIBC_VERSION)/stdlib/lrand48.c \
  glibc-$(GLIBC_VERSION)/stdlib/lrand48_r.c \
  glibc-$(GLIBC_VERSION)/stdlib/makecontext.c \
  glibc-$(GLIBC_VERSION)/stdlib/mblen.c \
  glibc-$(GLIBC_VERSION)/stdlib/mbstowcs.c \
  glibc-$(GLIBC_VERSION)/stdlib/mbtowc.c \
  glibc-$(GLIBC_VERSION)/stdlib/mod_1.c \
  glibc-$(GLIBC_VERSION)/stdlib/mrand48.c \
  glibc-$(GLIBC_VERSION)/stdlib/mrand48_r.c \
  glibc-$(GLIBC_VERSION)/stdlib/msort.c \
  glibc-$(GLIBC_VERSION)/stdlib/mul.c \
  glibc-$(GLIBC_VERSION)/stdlib/mul_n.c \
  glibc-$(GLIBC_VERSION)/stdlib/nrand48.c \
  glibc-$(GLIBC_VERSION)/stdlib/nrand48_r.c \
  glibc-$(GLIBC_VERSION)/stdlib/old_atexit.c \
  glibc-$(GLIBC_VERSION)/stdlib/on_exit.c \
  glibc-$(GLIBC_VERSION)/stdlib/putenv.c \
  glibc-$(GLIBC_VERSION)/stdlib/qsort.c \
  glibc-$(GLIBC_VERSION)/stdlib/quick_exit.c \
  glibc-$(GLIBC_VERSION)/stdlib/rand.c \
  glibc-$(GLIBC_VERSION)/stdlib/rand_r.c \
  glibc-$(GLIBC_VERSION)/stdlib/random.c \
  glibc-$(GLIBC_VERSION)/stdlib/random_r.c \
  glibc-$(GLIBC_VERSION)/stdlib/rpmatch.c \
  glibc-$(GLIBC_VERSION)/stdlib/secure-getenv.c \
  glibc-$(GLIBC_VERSION)/stdlib/seed48.c \
  glibc-$(GLIBC_VERSION)/stdlib/seed48_r.c \
  glibc-$(GLIBC_VERSION)/stdlib/setcontext.c \
  glibc-$(GLIBC_VERSION)/stdlib/setenv.c \
  glibc-$(GLIBC_VERSION)/stdlib/srand48.c \
  glibc-$(GLIBC_VERSION)/stdlib/srand48_r.c \
  glibc-$(GLIBC_VERSION)/stdlib/strfmon.c \
  glibc-$(GLIBC_VERSION)/stdlib/strfmon_l.c \
  glibc-$(GLIBC_VERSION)/stdlib/strtod.c \
  glibc-$(GLIBC_VERSION)/stdlib/strtod_l.c \
  glibc-$(GLIBC_VERSION)/stdlib/strtof.c \
  glibc-$(GLIBC_VERSION)/stdlib/strtof_l.c \
  glibc-$(GLIBC_VERSION)/stdlib/strtold.c \
  glibc-$(GLIBC_VERSION)/stdlib/swapcontext.c \
  glibc-$(GLIBC_VERSION)/stdlib/tens_in_limb.c \
  glibc-$(GLIBC_VERSION)/stdlib/udiv_qrnnd.c \
  glibc-$(GLIBC_VERSION)/stdlib/wcstombs.c \
  glibc-$(GLIBC_VERSION)/stdlib/wctomb.c \
  glibc-$(GLIBC_VERSION)/stdlib/xpg_basename.c \
  glibc-$(GLIBC_VERSION)/string/_strerror.c \
  glibc-$(GLIBC_VERSION)/string/argz-addsep.c \
  glibc-$(GLIBC_VERSION)/string/argz-append.c \
  glibc-$(GLIBC_VERSION)/string/argz-count.c \
  glibc-$(GLIBC_VERSION)/string/argz-create.c \
  glibc-$(GLIBC_VERSION)/string/argz-ctsep.c \
  glibc-$(GLIBC_VERSION)/string/argz-delete.c \
  glibc-$(GLIBC_VERSION)/string/argz-extract.c \
  glibc-$(GLIBC_VERSION)/string/argz-insert.c \
  glibc-$(GLIBC_VERSION)/string/argz-next.c \
  glibc-$(GLIBC_VERSION)/string/argz-replace.c \
  glibc-$(GLIBC_VERSION)/string/argz-stringify.c \
  glibc-$(GLIBC_VERSION)/string/basename.c \
  glibc-$(GLIBC_VERSION)/string/bcopy.c \
  glibc-$(GLIBC_VERSION)/string/envz.c \
  glibc-$(GLIBC_VERSION)/string/memccpy.c \
  glibc-$(GLIBC_VERSION)/string/memfrob.c \
  glibc-$(GLIBC_VERSION)/string/memmem.c \
  glibc-$(GLIBC_VERSION)/string/stpncpy.c \
  glibc-$(GLIBC_VERSION)/string/strcasecmp.c \
  glibc-$(GLIBC_VERSION)/string/strcasecmp_l.c \
  glibc-$(GLIBC_VERSION)/string/strcasestr.c \
  glibc-$(GLIBC_VERSION)/string/strcoll.c \
  glibc-$(GLIBC_VERSION)/string/strcoll_l.c \
  glibc-$(GLIBC_VERSION)/string/strdup.c \
  glibc-$(GLIBC_VERSION)/string/strerror.c \
  glibc-$(GLIBC_VERSION)/string/strerror_l.c \
  glibc-$(GLIBC_VERSION)/string/strfry.c \
  glibc-$(GLIBC_VERSION)/string/string-inlines.c \
  glibc-$(GLIBC_VERSION)/string/strncase.c \
  glibc-$(GLIBC_VERSION)/string/strncase_l.c \
  glibc-$(GLIBC_VERSION)/string/strncat.c \
  glibc-$(GLIBC_VERSION)/string/strncpy.c \
  glibc-$(GLIBC_VERSION)/string/strndup.c \
  glibc-$(GLIBC_VERSION)/string/strsep.c \
  glibc-$(GLIBC_VERSION)/string/strsignal.c \
  glibc-$(GLIBC_VERSION)/string/strstr.c \
  glibc-$(GLIBC_VERSION)/string/strverscmp.c \
  glibc-$(GLIBC_VERSION)/string/strxfrm.c \
  glibc-$(GLIBC_VERSION)/string/strxfrm_l.c \
  glibc-$(GLIBC_VERSION)/string/swab.c \
  glibc-$(GLIBC_VERSION)/string/wordcopy.c \
  glibc-$(GLIBC_VERSION)/string/xpg-strerror.c \
  glibc-$(GLIBC_VERSION)/sysdeps/gnu/errlist.c \
  glibc-$(GLIBC_VERSION)/sysdeps/gnu/siglist.c \
  glibc-$(GLIBC_VERSION)/sysdeps/ieee754/dbl-64/wordsize-64/e_acosh.c \
  glibc-$(GLIBC_VERSION)/sysdeps/ieee754/dbl-64/wordsize-64/e_cosh.c \
  glibc-$(GLIBC_VERSION)/sysdeps/ieee754/dbl-64/wordsize-64/e_fmod.c \
  glibc-$(GLIBC_VERSION)/sysdeps/ieee754/dbl-64/wordsize-64/e_log2.c \
  glibc-$(GLIBC_VERSION)/sysdeps/ieee754/dbl-64/wordsize-64/e_log10.c \
  glibc-$(GLIBC_VERSION)/sysdeps/ieee754/dbl-64/wordsize-64/s_ceil.c \
  glibc-$(GLIBC_VERSION)/sysdeps/ieee754/dbl-64/wordsize-64/s_finite.c \
  glibc-$(GLIBC_VERSION)/sysdeps/ieee754/dbl-64/wordsize-64/s_floor.c \
  glibc-$(GLIBC_VERSION)/sysdeps/ieee754/dbl-64/wordsize-64/s_frexp.c \
  glibc-$(GLIBC_VERSION)/sysdeps/ieee754/dbl-64/wordsize-64/s_isinf.c \
  glibc-$(GLIBC_VERSION)/sysdeps/ieee754/dbl-64/wordsize-64/s_isinf_ns.c \
  glibc-$(GLIBC_VERSION)/sysdeps/ieee754/dbl-64/wordsize-64/s_isnan.c \
  glibc-$(GLIBC_VERSION)/sysdeps/ieee754/dbl-64/wordsize-64/s_llround.c \
  glibc-$(GLIBC_VERSION)/sysdeps/ieee754/dbl-64/wordsize-64/s_logb.c \
  glibc-$(GLIBC_VERSION)/sysdeps/ieee754/dbl-64/wordsize-64/s_lround.c \
  glibc-$(GLIBC_VERSION)/sysdeps/ieee754/dbl-64/wordsize-64/s_modf.c \
  glibc-$(GLIBC_VERSION)/sysdeps/ieee754/dbl-64/wordsize-64/s_nearbyint.c \
  glibc-$(GLIBC_VERSION)/sysdeps/ieee754/dbl-64/wordsize-64/s_remquo.c \
  glibc-$(GLIBC_VERSION)/sysdeps/ieee754/dbl-64/wordsize-64/s_rint.c \
  glibc-$(GLIBC_VERSION)/sysdeps/ieee754/dbl-64/wordsize-64/s_round.c \
  glibc-$(GLIBC_VERSION)/sysdeps/ieee754/dbl-64/wordsize-64/s_scalbln.c \
  glibc-$(GLIBC_VERSION)/sysdeps/ieee754/dbl-64/wordsize-64/s_scalbn.c \
  glibc-$(GLIBC_VERSION)/sysdeps/ieee754/dbl-64/wordsize-64/s_trunc.c \
  glibc-$(GLIBC_VERSION)/sysdeps/ieee754/dbl-64/branred.c \
  glibc-$(GLIBC_VERSION)/sysdeps/ieee754/dbl-64/doasin.c \
  glibc-$(GLIBC_VERSION)/sysdeps/ieee754/dbl-64/dosincos.c \
  glibc-$(GLIBC_VERSION)/sysdeps/ieee754/dbl-64/e_acos.c \
  glibc-$(GLIBC_VERSION)/sysdeps/ieee754/dbl-64/e_asin.c \
  glibc-$(GLIBC_VERSION)/sysdeps/ieee754/dbl-64/e_atan2.c \
  glibc-$(GLIBC_VERSION)/sysdeps/ieee754/dbl-64/e_atanh.c \
  glibc-$(GLIBC_VERSION)/sysdeps/ieee754/dbl-64/e_exp.c \
  glibc-$(GLIBC_VERSION)/sysdeps/ieee754/dbl-64/e_exp2.c \
  glibc-$(GLIBC_VERSION)/sysdeps/ieee754/dbl-64/e_exp10.c \
  glibc-$(GLIBC_VERSION)/sysdeps/ieee754/dbl-64/e_gamma_r.c \
  glibc-$(GLIBC_VERSION)/sysdeps/ieee754/dbl-64/e_hypot.c \
  glibc-$(GLIBC_VERSION)/sysdeps/ieee754/dbl-64/e_ilogb.c \
  glibc-$(GLIBC_VERSION)/sysdeps/ieee754/dbl-64/e_j0.c \
  glibc-$(GLIBC_VERSION)/sysdeps/ieee754/dbl-64/e_j1.c \
  glibc-$(GLIBC_VERSION)/sysdeps/ieee754/dbl-64/e_jn.c \
  glibc-$(GLIBC_VERSION)/sysdeps/ieee754/dbl-64/e_lgamma_r.c \
  glibc-$(GLIBC_VERSION)/sysdeps/ieee754/dbl-64/e_log.c \
  glibc-$(GLIBC_VERSION)/sysdeps/ieee754/dbl-64/e_pow.c \
  glibc-$(GLIBC_VERSION)/sysdeps/ieee754/dbl-64/e_rem_pio2.c \
  glibc-$(GLIBC_VERSION)/sysdeps/ieee754/dbl-64/e_remainder.c \
  glibc-$(GLIBC_VERSION)/sysdeps/ieee754/dbl-64/e_sinh.c \
  glibc-$(GLIBC_VERSION)/sysdeps/ieee754/dbl-64/halfulp.c \
  glibc-$(GLIBC_VERSION)/sysdeps/ieee754/dbl-64/k_cos.c \
  glibc-$(GLIBC_VERSION)/sysdeps/ieee754/dbl-64/k_rem_pio2.c \
  glibc-$(GLIBC_VERSION)/sysdeps/ieee754/dbl-64/k_sin.c \
  glibc-$(GLIBC_VERSION)/sysdeps/ieee754/dbl-64/k_tan.c \
  glibc-$(GLIBC_VERSION)/sysdeps/ieee754/dbl-64/mpa.c \
  glibc-$(GLIBC_VERSION)/sysdeps/ieee754/dbl-64/mpatan.c \
  glibc-$(GLIBC_VERSION)/sysdeps/ieee754/dbl-64/mpatan2.c \
  glibc-$(GLIBC_VERSION)/sysdeps/ieee754/dbl-64/mpexp.c \
  glibc-$(GLIBC_VERSION)/sysdeps/ieee754/dbl-64/mplog.c \
  glibc-$(GLIBC_VERSION)/sysdeps/ieee754/dbl-64/dbl2mpn.c \
  glibc-$(GLIBC_VERSION)/sysdeps/ieee754/dbl-64/mpn2dbl.c \
  glibc-$(GLIBC_VERSION)/sysdeps/ieee754/dbl-64/mpsqrt.c \
  glibc-$(GLIBC_VERSION)/sysdeps/ieee754/dbl-64/mptan.c \
  glibc-$(GLIBC_VERSION)/sysdeps/ieee754/dbl-64/s_asinh.c \
  glibc-$(GLIBC_VERSION)/sysdeps/ieee754/dbl-64/s_atan.c \
  glibc-$(GLIBC_VERSION)/sysdeps/ieee754/dbl-64/s_cbrt.c \
  glibc-$(GLIBC_VERSION)/sysdeps/ieee754/dbl-64/s_cos.c \
  glibc-$(GLIBC_VERSION)/sysdeps/ieee754/dbl-64/s_erf.c \
  glibc-$(GLIBC_VERSION)/sysdeps/ieee754/dbl-64/s_expm1.c \
  glibc-$(GLIBC_VERSION)/sysdeps/ieee754/dbl-64/s_fabs.c \
  glibc-$(GLIBC_VERSION)/sysdeps/ieee754/dbl-64/s_fmaf.c \
  glibc-$(GLIBC_VERSION)/sysdeps/ieee754/dbl-64/s_fpclassify.c \
  glibc-$(GLIBC_VERSION)/sysdeps/ieee754/dbl-64/s_log1p.c \
  glibc-$(GLIBC_VERSION)/sysdeps/ieee754/dbl-64/s_sin.c \
  glibc-$(GLIBC_VERSION)/sysdeps/ieee754/dbl-64/s_sincos.c \
  glibc-$(GLIBC_VERSION)/sysdeps/ieee754/dbl-64/s_tan.c \
  glibc-$(GLIBC_VERSION)/sysdeps/ieee754/dbl-64/s_tanh.c \
  glibc-$(GLIBC_VERSION)/sysdeps/ieee754/dbl-64/sincos32.c \
  glibc-$(GLIBC_VERSION)/sysdeps/ieee754/dbl-64/sincostab.c \
  glibc-$(GLIBC_VERSION)/sysdeps/ieee754/dbl-64/slowexp.c \
  glibc-$(GLIBC_VERSION)/sysdeps/ieee754/dbl-64/slowpow.c \
  glibc-$(GLIBC_VERSION)/sysdeps/ieee754/dbl-64/t_exp.c \
  glibc-$(GLIBC_VERSION)/sysdeps/ieee754/dbl-64/w_exp.c \
  glibc-$(GLIBC_VERSION)/sysdeps/ieee754/dbl-64/x2y2m1f.c \
  glibc-$(GLIBC_VERSION)/sysdeps/ieee754/flt-32/e_acosf.c \
  glibc-$(GLIBC_VERSION)/sysdeps/ieee754/flt-32/e_acoshf.c \
  glibc-$(GLIBC_VERSION)/sysdeps/ieee754/flt-32/e_asinf.c \
  glibc-$(GLIBC_VERSION)/sysdeps/ieee754/flt-32/e_atan2f.c \
  glibc-$(GLIBC_VERSION)/sysdeps/ieee754/flt-32/e_atanhf.c \
  glibc-$(GLIBC_VERSION)/sysdeps/ieee754/flt-32/e_coshf.c \
  glibc-$(GLIBC_VERSION)/sysdeps/ieee754/flt-32/e_exp2f.c \
  glibc-$(GLIBC_VERSION)/sysdeps/ieee754/flt-32/e_expf.c \
  glibc-$(GLIBC_VERSION)/sysdeps/ieee754/flt-32/e_fmodf.c \
  glibc-$(GLIBC_VERSION)/sysdeps/ieee754/flt-32/e_gammaf_r.c \
  glibc-$(GLIBC_VERSION)/sysdeps/ieee754/flt-32/e_hypotf.c \
  glibc-$(GLIBC_VERSION)/sysdeps/ieee754/flt-32/e_ilogbf.c \
  glibc-$(GLIBC_VERSION)/sysdeps/ieee754/flt-32/e_j0f.c \
  glibc-$(GLIBC_VERSION)/sysdeps/ieee754/flt-32/e_j1f.c \
  glibc-$(GLIBC_VERSION)/sysdeps/ieee754/flt-32/e_jnf.c \
  glibc-$(GLIBC_VERSION)/sysdeps/ieee754/flt-32/e_lgammaf_r.c \
  glibc-$(GLIBC_VERSION)/sysdeps/ieee754/flt-32/e_log2f.c \
  glibc-$(GLIBC_VERSION)/sysdeps/ieee754/flt-32/e_log10f.c \
  glibc-$(GLIBC_VERSION)/sysdeps/ieee754/flt-32/e_logf.c \
  glibc-$(GLIBC_VERSION)/sysdeps/ieee754/flt-32/e_powf.c \
  glibc-$(GLIBC_VERSION)/sysdeps/ieee754/flt-32/e_rem_pio2f.c \
  glibc-$(GLIBC_VERSION)/sysdeps/ieee754/flt-32/e_remainderf.c \
  glibc-$(GLIBC_VERSION)/sysdeps/ieee754/flt-32/e_sinhf.c \
  glibc-$(GLIBC_VERSION)/sysdeps/ieee754/flt-32/e_sqrtf.c \
  glibc-$(GLIBC_VERSION)/sysdeps/ieee754/flt-32/k_cosf.c \
  glibc-$(GLIBC_VERSION)/sysdeps/ieee754/flt-32/k_rem_pio2f.c \
  glibc-$(GLIBC_VERSION)/sysdeps/ieee754/flt-32/k_sinf.c \
  glibc-$(GLIBC_VERSION)/sysdeps/ieee754/flt-32/k_tanf.c \
  glibc-$(GLIBC_VERSION)/sysdeps/ieee754/flt-32/mpn2flt.c \
  glibc-$(GLIBC_VERSION)/sysdeps/ieee754/flt-32/s_asinhf.c \
  glibc-$(GLIBC_VERSION)/sysdeps/ieee754/flt-32/s_atanf.c \
  glibc-$(GLIBC_VERSION)/sysdeps/ieee754/flt-32/s_cbrtf.c \
  glibc-$(GLIBC_VERSION)/sysdeps/ieee754/flt-32/s_ceilf.c \
  glibc-$(GLIBC_VERSION)/sysdeps/ieee754/flt-32/s_copysignf.c \
  glibc-$(GLIBC_VERSION)/sysdeps/ieee754/flt-32/s_erff.c \
  glibc-$(GLIBC_VERSION)/sysdeps/ieee754/flt-32/s_expm1f.c \
  glibc-$(GLIBC_VERSION)/sysdeps/ieee754/flt-32/s_fabsf.c \
  glibc-$(GLIBC_VERSION)/sysdeps/ieee754/flt-32/s_finitef.c \
  glibc-$(GLIBC_VERSION)/sysdeps/ieee754/flt-32/s_floorf.c \
  glibc-$(GLIBC_VERSION)/sysdeps/ieee754/flt-32/s_fpclassifyf.c \
  glibc-$(GLIBC_VERSION)/sysdeps/ieee754/flt-32/s_frexpf.c \
  glibc-$(GLIBC_VERSION)/sysdeps/ieee754/flt-32/s_isinf_nsf.c \
  glibc-$(GLIBC_VERSION)/sysdeps/ieee754/flt-32/s_isinff.c \
  glibc-$(GLIBC_VERSION)/sysdeps/ieee754/flt-32/s_isnanf.c \
  glibc-$(GLIBC_VERSION)/sysdeps/ieee754/flt-32/s_llroundf.c \
  glibc-$(GLIBC_VERSION)/sysdeps/ieee754/flt-32/s_log1pf.c \
  glibc-$(GLIBC_VERSION)/sysdeps/ieee754/flt-32/s_logbf.c \
  glibc-$(GLIBC_VERSION)/sysdeps/ieee754/flt-32/s_lroundf.c \
  glibc-$(GLIBC_VERSION)/sysdeps/ieee754/flt-32/s_modff.c \
  glibc-$(GLIBC_VERSION)/sysdeps/ieee754/flt-32/s_nearbyintf.c \
  glibc-$(GLIBC_VERSION)/sysdeps/ieee754/flt-32/s_nextafterf.c \
  glibc-$(GLIBC_VERSION)/sysdeps/ieee754/flt-32/s_remquof.c \
  glibc-$(GLIBC_VERSION)/sysdeps/ieee754/flt-32/s_rintf.c \
  glibc-$(GLIBC_VERSION)/sysdeps/ieee754/flt-32/s_roundf.c \
  glibc-$(GLIBC_VERSION)/sysdeps/ieee754/flt-32/s_scalblnf.c \
  glibc-$(GLIBC_VERSION)/sysdeps/ieee754/flt-32/s_scalbnf.c \
  glibc-$(GLIBC_VERSION)/sysdeps/ieee754/flt-32/s_tanf.c \
  glibc-$(GLIBC_VERSION)/sysdeps/ieee754/flt-32/s_tanhf.c \
  glibc-$(GLIBC_VERSION)/sysdeps/ieee754/flt-32/s_truncf.c \
  glibc-$(GLIBC_VERSION)/sysdeps/ieee754/flt-32/w_expf.c \
  glibc-$(GLIBC_VERSION)/sysdeps/ieee754/ldbl-96/e_acoshl.c \
  glibc-$(GLIBC_VERSION)/sysdeps/ieee754/ldbl-96/e_asinl.c \
  glibc-$(GLIBC_VERSION)/sysdeps/ieee754/ldbl-96/e_atanhl.c \
  glibc-$(GLIBC_VERSION)/sysdeps/ieee754/ldbl-96/e_coshl.c \
  glibc-$(GLIBC_VERSION)/sysdeps/ieee754/ldbl-96/e_gammal_r.c \
  glibc-$(GLIBC_VERSION)/sysdeps/ieee754/ldbl-96/e_hypotl.c \
  glibc-$(GLIBC_VERSION)/sysdeps/ieee754/ldbl-96/e_j0l.c \
  glibc-$(GLIBC_VERSION)/sysdeps/ieee754/ldbl-96/e_j1l.c \
  glibc-$(GLIBC_VERSION)/sysdeps/ieee754/ldbl-96/e_jnl.c \
  glibc-$(GLIBC_VERSION)/sysdeps/ieee754/ldbl-96/e_lgammal_r.c \
  glibc-$(GLIBC_VERSION)/sysdeps/ieee754/ldbl-96/e_rem_pio2l.c \
  glibc-$(GLIBC_VERSION)/sysdeps/ieee754/ldbl-96/e_sinhl.c \
  glibc-$(GLIBC_VERSION)/sysdeps/ieee754/ldbl-96/k_cosl.c \
  glibc-$(GLIBC_VERSION)/sysdeps/ieee754/ldbl-96/k_sinl.c \
  glibc-$(GLIBC_VERSION)/sysdeps/ieee754/ldbl-96/k_tanl.c \
  glibc-$(GLIBC_VERSION)/sysdeps/ieee754/ldbl-96/mpn2ldbl.c \
  glibc-$(GLIBC_VERSION)/sysdeps/ieee754/ldbl-96/s_asinhl.c \
  glibc-$(GLIBC_VERSION)/sysdeps/ieee754/ldbl-96/s_cbrtl.c \
  glibc-$(GLIBC_VERSION)/sysdeps/ieee754/ldbl-96/s_cosl.c \
  glibc-$(GLIBC_VERSION)/sysdeps/ieee754/ldbl-96/s_erfl.c \
  glibc-$(GLIBC_VERSION)/sysdeps/ieee754/ldbl-96/s_fma.c \
  glibc-$(GLIBC_VERSION)/sysdeps/ieee754/ldbl-96/s_fmal.c \
  glibc-$(GLIBC_VERSION)/sysdeps/ieee754/ldbl-96/s_frexpl.c \
  glibc-$(GLIBC_VERSION)/sysdeps/ieee754/ldbl-96/s_isinf_nsl.c \
  glibc-$(GLIBC_VERSION)/sysdeps/ieee754/ldbl-96/s_llroundl.c \
  glibc-$(GLIBC_VERSION)/sysdeps/ieee754/ldbl-96/s_lroundl.c \
  glibc-$(GLIBC_VERSION)/sysdeps/ieee754/ldbl-96/s_modfl.c \
  glibc-$(GLIBC_VERSION)/sysdeps/ieee754/ldbl-96/s_nearbyintl.c \
  glibc-$(GLIBC_VERSION)/sysdeps/ieee754/ldbl-96/s_remquol.c \
  glibc-$(GLIBC_VERSION)/sysdeps/ieee754/ldbl-96/s_roundl.c \
  glibc-$(GLIBC_VERSION)/sysdeps/ieee754/ldbl-96/s_scalbnl.c \
  glibc-$(GLIBC_VERSION)/sysdeps/ieee754/ldbl-96/s_signbitl.c \
  glibc-$(GLIBC_VERSION)/sysdeps/ieee754/ldbl-96/s_sincosl.c \
  glibc-$(GLIBC_VERSION)/sysdeps/ieee754/ldbl-96/s_sinl.c \
  glibc-$(GLIBC_VERSION)/sysdeps/ieee754/ldbl-96/s_tanhl.c \
  glibc-$(GLIBC_VERSION)/sysdeps/ieee754/ldbl-96/s_tanl.c \
  glibc-$(GLIBC_VERSION)/sysdeps/ieee754/ldbl-96/strtold_l.c \
  glibc-$(GLIBC_VERSION)/sysdeps/ieee754/ldbl-96/t_sincosl.c \
  glibc-$(GLIBC_VERSION)/sysdeps/ieee754/ldbl-96/w_expl.c \
  glibc-$(GLIBC_VERSION)/sysdeps/ieee754/ldbl-96/x2y2m1.c \
  glibc-$(GLIBC_VERSION)/sysdeps/ieee754/ldbl-96/x2y2m1l.c \
  glibc-$(GLIBC_VERSION)/sysdeps/ieee754/k_standard.c \
  glibc-$(GLIBC_VERSION)/sysdeps/ieee754/s_lib_version.c \
  glibc-$(GLIBC_VERSION)/sysdeps/ieee754/s_matherr.c \
  glibc-$(GLIBC_VERSION)/sysdeps/ieee754/s_signgam.c \
  glibc-$(GLIBC_VERSION)/sysdeps/llamaos/export/_exit.c \
  glibc-$(GLIBC_VERSION)/sysdeps/llamaos/export/abort.c \
  glibc-$(GLIBC_VERSION)/sysdeps/llamaos/export/access.c \
  glibc-$(GLIBC_VERSION)/sysdeps/llamaos/export/assert-perr.c \
  glibc-$(GLIBC_VERSION)/sysdeps/llamaos/export/assert.c \
  glibc-$(GLIBC_VERSION)/sysdeps/llamaos/export/brk.c \
  glibc-$(GLIBC_VERSION)/sysdeps/llamaos/export/close.c \
  glibc-$(GLIBC_VERSION)/sysdeps/llamaos/export/dup.c \
  glibc-$(GLIBC_VERSION)/sysdeps/llamaos/export/dup2.c \
  glibc-$(GLIBC_VERSION)/sysdeps/llamaos/export/ftruncate.c \
  glibc-$(GLIBC_VERSION)/sysdeps/llamaos/export/get_avphys_pages.c \
  glibc-$(GLIBC_VERSION)/sysdeps/llamaos/export/get_nprocs.c \
  glibc-$(GLIBC_VERSION)/sysdeps/llamaos/export/get_nprocs_conf.c \
  glibc-$(GLIBC_VERSION)/sysdeps/llamaos/export/get_phys_pages.c \
  glibc-$(GLIBC_VERSION)/sysdeps/llamaos/export/getcwd.c \
  glibc-$(GLIBC_VERSION)/sysdeps/llamaos/export/gethostname.c \
  glibc-$(GLIBC_VERSION)/sysdeps/llamaos/export/getpagesize.c \
  glibc-$(GLIBC_VERSION)/sysdeps/llamaos/export/getpid.c \
  glibc-$(GLIBC_VERSION)/sysdeps/llamaos/export/isatty.c \
  glibc-$(GLIBC_VERSION)/sysdeps/llamaos/export/libc_fatal.c \
  glibc-$(GLIBC_VERSION)/sysdeps/llamaos/export/lseek.c \
  glibc-$(GLIBC_VERSION)/sysdeps/llamaos/export/lseek64.c \
  glibc-$(GLIBC_VERSION)/sysdeps/llamaos/export/libc_open.c \
  glibc-$(GLIBC_VERSION)/sysdeps/llamaos/export/lxstat64.c \
  glibc-$(GLIBC_VERSION)/sysdeps/llamaos/export/madvise.c \
  glibc-$(GLIBC_VERSION)/sysdeps/llamaos/export/mkdir.c \
  glibc-$(GLIBC_VERSION)/sysdeps/llamaos/export/pathconf.c \
  glibc-$(GLIBC_VERSION)/sysdeps/llamaos/export/poll.c \
  glibc-$(GLIBC_VERSION)/sysdeps/llamaos/export/raise.c \
  glibc-$(GLIBC_VERSION)/sysdeps/llamaos/export/read.c \
  glibc-$(GLIBC_VERSION)/sysdeps/llamaos/export/sched_primax.c \
  glibc-$(GLIBC_VERSION)/sysdeps/llamaos/export/sched_primin.c \
  glibc-$(GLIBC_VERSION)/sysdeps/llamaos/export/sigsuspend.c \
  glibc-$(GLIBC_VERSION)/sysdeps/llamaos/export/sigsuspend_nocancel.c \
  glibc-$(GLIBC_VERSION)/sysdeps/llamaos/export/sleep.c \
  glibc-$(GLIBC_VERSION)/sysdeps/llamaos/export/syscall.c \
  glibc-$(GLIBC_VERSION)/sysdeps/llamaos/export/gettimeofday.c \
  glibc-$(GLIBC_VERSION)/sysdeps/llamaos/export/time.c \
  glibc-$(GLIBC_VERSION)/sysdeps/llamaos/export/uname.c \
  glibc-$(GLIBC_VERSION)/sysdeps/llamaos/export/unlink.c \
  glibc-$(GLIBC_VERSION)/sysdeps/llamaos/export/write.c \
  glibc-$(GLIBC_VERSION)/sysdeps/llamaos/export/writev.c \
  glibc-$(GLIBC_VERSION)/sysdeps/llamaos/export/xstat.c \
  glibc-$(GLIBC_VERSION)/sysdeps/llamaos/export/xstat64.c \
  glibc-$(GLIBC_VERSION)/sysdeps/llamaos/dlerror.c \
  glibc-$(GLIBC_VERSION)/sysdeps/llamaos/gcc_personality_v0.c \
  glibc-$(GLIBC_VERSION)/sysdeps/llamaos/mremap.c \
  glibc-$(GLIBC_VERSION)/sysdeps/llamaos/powidf2.c \
  glibc-$(GLIBC_VERSION)/sysdeps/llamaos/register-atfork.c \
  glibc-$(GLIBC_VERSION)/sysdeps/llamaos/sigaddset.c \
  glibc-$(GLIBC_VERSION)/sysdeps/llamaos/sysconf.c \
  glibc-$(GLIBC_VERSION)/sysdeps/llamaos/syslog.c \
  glibc-$(GLIBC_VERSION)/sysdeps/llamaos/system.c \
  glibc-$(GLIBC_VERSION)/sysdeps/posix/ctermid.c \
  glibc-$(GLIBC_VERSION)/sysdeps/posix/cuserid.c \
  glibc-$(GLIBC_VERSION)/sysdeps/posix/tempname.c \
  glibc-$(GLIBC_VERSION)/sysdeps/wordsize-64/labs.c \
  glibc-$(GLIBC_VERSION)/sysdeps/wordsize-64/ldiv.c \
  glibc-$(GLIBC_VERSION)/sysdeps/wordsize-64/strtoimax.c \
  glibc-$(GLIBC_VERSION)/sysdeps/wordsize-64/strtol.c \
  glibc-$(GLIBC_VERSION)/sysdeps/wordsize-64/strtol_l.c \
  glibc-$(GLIBC_VERSION)/sysdeps/wordsize-64/strtoll.c \
  glibc-$(GLIBC_VERSION)/sysdeps/wordsize-64/strtoll_l.c \
  glibc-$(GLIBC_VERSION)/sysdeps/wordsize-64/strtoul.c \
  glibc-$(GLIBC_VERSION)/sysdeps/wordsize-64/strtoul_l.c \
  glibc-$(GLIBC_VERSION)/sysdeps/wordsize-64/strtoull.c \
  glibc-$(GLIBC_VERSION)/sysdeps/wordsize-64/strtoull_l.c \
  glibc-$(GLIBC_VERSION)/sysdeps/wordsize-64/strtoumax.c \
  glibc-$(GLIBC_VERSION)/sysdeps/wordsize-64/wcstoimax.c \
  glibc-$(GLIBC_VERSION)/sysdeps/wordsize-64/wcstol.c \
  glibc-$(GLIBC_VERSION)/sysdeps/wordsize-64/wcstol_l.c \
  glibc-$(GLIBC_VERSION)/sysdeps/wordsize-64/wcstoll.c \
  glibc-$(GLIBC_VERSION)/sysdeps/wordsize-64/wcstoll_l.c \
  glibc-$(GLIBC_VERSION)/sysdeps/wordsize-64/wcstoul.c \
  glibc-$(GLIBC_VERSION)/sysdeps/wordsize-64/wcstoul_l.c \
  glibc-$(GLIBC_VERSION)/sysdeps/wordsize-64/wcstoull.c \
  glibc-$(GLIBC_VERSION)/sysdeps/wordsize-64/wcstoull_l.c \
  glibc-$(GLIBC_VERSION)/sysdeps/wordsize-64/wcstoumax.c \
  glibc-$(GLIBC_VERSION)/sysdeps/x86/fpu/powl_helper.c \
  glibc-$(GLIBC_VERSION)/sysdeps/x86_64/fpu/e_acosl.c \
  glibc-$(GLIBC_VERSION)/sysdeps/x86_64/fpu/e_atan2l.c \
  glibc-$(GLIBC_VERSION)/sysdeps/x86_64/fpu/e_sqrt.c \
  glibc-$(GLIBC_VERSION)/sysdeps/x86_64/fpu/e_sqrtl.c \
  glibc-$(GLIBC_VERSION)/sysdeps/x86_64/fpu/fclrexcpt.c \
  glibc-$(GLIBC_VERSION)/sysdeps/x86_64/fpu/fedisblxcpt.c \
  glibc-$(GLIBC_VERSION)/sysdeps/x86_64/fpu/feenablxcpt.c \
  glibc-$(GLIBC_VERSION)/sysdeps/x86_64/fpu/fegetenv.c \
  glibc-$(GLIBC_VERSION)/sysdeps/x86_64/fpu/fegetexcept.c \
  glibc-$(GLIBC_VERSION)/sysdeps/x86_64/fpu/fegetround.c \
  glibc-$(GLIBC_VERSION)/sysdeps/x86_64/fpu/feholdexcpt.c \
  glibc-$(GLIBC_VERSION)/sysdeps/x86_64/fpu/fesetenv.c \
  glibc-$(GLIBC_VERSION)/sysdeps/x86_64/fpu/fesetround.c \
  glibc-$(GLIBC_VERSION)/sysdeps/x86_64/fpu/feupdateenv.c \
  glibc-$(GLIBC_VERSION)/sysdeps/x86_64/fpu/fgetexcptflg.c \
  glibc-$(GLIBC_VERSION)/sysdeps/x86_64/fpu/fraiseexcpt.c \
  glibc-$(GLIBC_VERSION)/sysdeps/x86_64/fpu/fsetexcptflg.c \
  glibc-$(GLIBC_VERSION)/sysdeps/x86_64/fpu/ftestexcept.c \
  glibc-$(GLIBC_VERSION)/sysdeps/x86_64/fpu/k_rem_pio2l.c \
  glibc-$(GLIBC_VERSION)/sysdeps/x86_64/fpu/printf_fphex.c \
  glibc-$(GLIBC_VERSION)/sysdeps/x86_64/fpu/s_atanl.c \
  glibc-$(GLIBC_VERSION)/sysdeps/x86_64/fpu/s_fpclassifyl.c \
  glibc-$(GLIBC_VERSION)/sysdeps/x86_64/fpu/s_isinfl.c \
  glibc-$(GLIBC_VERSION)/sysdeps/x86_64/fpu/s_isnanl.c \
  glibc-$(GLIBC_VERSION)/sysdeps/x86_64/fpu/s_logbl.c \
  glibc-$(GLIBC_VERSION)/sysdeps/x86_64/fpu/s_nextafterl.c \
  glibc-$(GLIBC_VERSION)/sysdeps/x86_64/fpu/s_nexttoward.c \
  glibc-$(GLIBC_VERSION)/sysdeps/x86_64/fpu/s_nexttowardf.c \
  glibc-$(GLIBC_VERSION)/sysdeps/x86_64/fpu/s_rintl.c \
  glibc-$(GLIBC_VERSION)/sysdeps/x86_64/fpu/s_significandl.c \
  glibc-$(GLIBC_VERSION)/sysdeps/x86_64/cacheinfo.c \
  glibc-$(GLIBC_VERSION)/sysdeps/x86_64/dl-runtime.c \
  glibc-$(GLIBC_VERSION)/sysdeps/x86_64/ffs.c \
  glibc-$(GLIBC_VERSION)/sysdeps/x86_64/ffsll.c \
  glibc-$(GLIBC_VERSION)/sysdeps/x86_64/hp-timing.c \
  glibc-$(GLIBC_VERSION)/sysdeps/x86_64/l10nflist.c \
  glibc-$(GLIBC_VERSION)/sysdeps/x86_64/ldbl2mpn.c \
  glibc-$(GLIBC_VERSION)/sysdeps/x86_64/memmove.c \
  glibc-$(GLIBC_VERSION)/sysdeps/x86_64/mp_clz_tab.c \
  glibc-$(GLIBC_VERSION)/sysdeps/x86_64/strcasecmp_l-nonascii.c \
  glibc-$(GLIBC_VERSION)/sysdeps/x86_64/strncase_l-nonascii.c \
  glibc-$(GLIBC_VERSION)/sysdeps/x86_64/tlsdesc.c \
  glibc-$(GLIBC_VERSION)/time/adjtime.c \
  glibc-$(GLIBC_VERSION)/time/alt_digit.c \
  glibc-$(GLIBC_VERSION)/time/asctime.c \
  glibc-$(GLIBC_VERSION)/time/clock.c \
  glibc-$(GLIBC_VERSION)/time/ctime.c \
  glibc-$(GLIBC_VERSION)/time/ctime_r.c \
  glibc-$(GLIBC_VERSION)/time/difftime.c \
  glibc-$(GLIBC_VERSION)/time/dysize.c \
  glibc-$(GLIBC_VERSION)/time/era.c \
  glibc-$(GLIBC_VERSION)/time/ftime.c \
  glibc-$(GLIBC_VERSION)/time/getdate.c \
  glibc-$(GLIBC_VERSION)/time/getitimer.c \
  glibc-$(GLIBC_VERSION)/time/gmtime.c \
  glibc-$(GLIBC_VERSION)/time/lc-time-cleanup.c \
  glibc-$(GLIBC_VERSION)/time/localtime.c \
  glibc-$(GLIBC_VERSION)/time/mktime.c \
  glibc-$(GLIBC_VERSION)/time/offtime.c \
  glibc-$(GLIBC_VERSION)/time/setitimer.c \
  glibc-$(GLIBC_VERSION)/time/settimeofday.c \
  glibc-$(GLIBC_VERSION)/time/stime.c \
  glibc-$(GLIBC_VERSION)/time/strftime.c \
  glibc-$(GLIBC_VERSION)/time/strftime_l.c \
  glibc-$(GLIBC_VERSION)/time/strptime.c \
  glibc-$(GLIBC_VERSION)/time/strptime_l.c \
  glibc-$(GLIBC_VERSION)/time/timegm.c \
  glibc-$(GLIBC_VERSION)/time/timespec_get.c \
  glibc-$(GLIBC_VERSION)/time/tzfile.c \
  glibc-$(GLIBC_VERSION)/time/tzset.c \
  glibc-$(GLIBC_VERSION)/time/wcsftime.c \
  glibc-$(GLIBC_VERSION)/time/wcsftime_l.c \
  glibc-$(GLIBC_VERSION)/wcsmbs/btowc.c \
  glibc-$(GLIBC_VERSION)/wcsmbs/c16rtomb.c \
  glibc-$(GLIBC_VERSION)/wcsmbs/isoc99_fwscanf.c \
  glibc-$(GLIBC_VERSION)/wcsmbs/isoc99_swscanf.c \
  glibc-$(GLIBC_VERSION)/wcsmbs/isoc99_vfwscanf.c \
  glibc-$(GLIBC_VERSION)/wcsmbs/isoc99_vswscanf.c \
  glibc-$(GLIBC_VERSION)/wcsmbs/isoc99_vwscanf.c \
  glibc-$(GLIBC_VERSION)/wcsmbs/isoc99_wscanf.c \
  glibc-$(GLIBC_VERSION)/wcsmbs/mbrlen.c \
  glibc-$(GLIBC_VERSION)/wcsmbs/mbrtoc16.c \
  glibc-$(GLIBC_VERSION)/wcsmbs/mbrtowc.c \
  glibc-$(GLIBC_VERSION)/wcsmbs/mbsinit.c \
  glibc-$(GLIBC_VERSION)/wcsmbs/mbsnrtowcs.c \
  glibc-$(GLIBC_VERSION)/wcsmbs/mbsrtowcs.c \
  glibc-$(GLIBC_VERSION)/wcsmbs/mbsrtowcs_l.c \
  glibc-$(GLIBC_VERSION)/wcsmbs/wcpcpy.c \
  glibc-$(GLIBC_VERSION)/wcsmbs/wcpncpy.c \
  glibc-$(GLIBC_VERSION)/wcsmbs/wcrtomb.c \
  glibc-$(GLIBC_VERSION)/wcsmbs/wcscasecmp.c \
  glibc-$(GLIBC_VERSION)/wcsmbs/wcscasecmp_l.c \
  glibc-$(GLIBC_VERSION)/wcsmbs/wcscat.c \
  glibc-$(GLIBC_VERSION)/wcsmbs/wcschrnul.c \
  glibc-$(GLIBC_VERSION)/wcsmbs/wcscoll.c \
  glibc-$(GLIBC_VERSION)/wcsmbs/wcscoll_l.c \
  glibc-$(GLIBC_VERSION)/wcsmbs/wcscpy.c \
  glibc-$(GLIBC_VERSION)/wcsmbs/wcscspn.c \
  glibc-$(GLIBC_VERSION)/wcsmbs/wcsdup.c \
  glibc-$(GLIBC_VERSION)/wcsmbs/wcsmbsload.c \
  glibc-$(GLIBC_VERSION)/wcsmbs/wcsncase.c \
  glibc-$(GLIBC_VERSION)/wcsmbs/wcsncase_l.c \
  glibc-$(GLIBC_VERSION)/wcsmbs/wcsncat.c \
  glibc-$(GLIBC_VERSION)/wcsmbs/wcsncmp.c \
  glibc-$(GLIBC_VERSION)/wcsmbs/wcsncpy.c \
  glibc-$(GLIBC_VERSION)/wcsmbs/wcsnlen.c \
  glibc-$(GLIBC_VERSION)/wcsmbs/wcsnrtombs.c \
  glibc-$(GLIBC_VERSION)/wcsmbs/wcspbrk.c \
  glibc-$(GLIBC_VERSION)/wcsmbs/wcsrtombs.c \
  glibc-$(GLIBC_VERSION)/wcsmbs/wcsspn.c \
  glibc-$(GLIBC_VERSION)/wcsmbs/wcsstr.c \
  glibc-$(GLIBC_VERSION)/wcsmbs/wcstod.c \
  glibc-$(GLIBC_VERSION)/wcsmbs/wcstod_l.c \
  glibc-$(GLIBC_VERSION)/wcsmbs/wcstof.c \
  glibc-$(GLIBC_VERSION)/wcsmbs/wcstof_l.c \
  glibc-$(GLIBC_VERSION)/wcsmbs/wcstok.c \
  glibc-$(GLIBC_VERSION)/wcsmbs/wcstol.c \
  glibc-$(GLIBC_VERSION)/wcsmbs/wcstol_l.c \
  glibc-$(GLIBC_VERSION)/wcsmbs/wcstold.c \
  glibc-$(GLIBC_VERSION)/wcsmbs/wcstold_l.c \
  glibc-$(GLIBC_VERSION)/wcsmbs/wcstoul.c \
  glibc-$(GLIBC_VERSION)/wcsmbs/wcstoul_l.c \
  glibc-$(GLIBC_VERSION)/wcsmbs/wcswidth.c \
  glibc-$(GLIBC_VERSION)/wcsmbs/wcsxfrm.c \
  glibc-$(GLIBC_VERSION)/wcsmbs/wcsxfrm_l.c \
  glibc-$(GLIBC_VERSION)/wcsmbs/wctob.c \
  glibc-$(GLIBC_VERSION)/wcsmbs/wcwidth.c \
  glibc-$(GLIBC_VERSION)/wcsmbs/wmemchr.c \
  glibc-$(GLIBC_VERSION)/wcsmbs/wmemcmp.c \
  glibc-$(GLIBC_VERSION)/wcsmbs/wmemcpy.c \
  glibc-$(GLIBC_VERSION)/wcsmbs/wmemmove.c \
  glibc-$(GLIBC_VERSION)/wcsmbs/wmempcpy.c \
  glibc-$(GLIBC_VERSION)/wcsmbs/wmemset.c \
  glibc-$(GLIBC_VERSION)/wctype/iswctype.c \
  glibc-$(GLIBC_VERSION)/wctype/iswctype_l.c \
  glibc-$(GLIBC_VERSION)/wctype/towctrans.c \
  glibc-$(GLIBC_VERSION)/wctype/towctrans_l.c \
  glibc-$(GLIBC_VERSION)/wctype/wcfuncs.c \
  glibc-$(GLIBC_VERSION)/wctype/wcfuncs_l.c \
  glibc-$(GLIBC_VERSION)/wctype/wctrans.c \
  glibc-$(GLIBC_VERSION)/wctype/wctrans_l.c \
  glibc-$(GLIBC_VERSION)/wctype/wctype.c \
  glibc-$(GLIBC_VERSION)/wctype/wctype_l.c

# replaced with llamaOS export
#  glibc-$(GLIBC_VERSION)/assert/assert-perr.c
#  glibc-$(GLIBC_VERSION)/assert/assert.c
#  glibc-$(GLIBC_VERSION)/elf/static-stubs.c
#  glibc-$(GLIBC_VERSION)/io/access.c
#  glibc-$(GLIBC_VERSION)/io/close.c
#  glibc-$(GLIBC_VERSION)/io/dup.c
#  glibc-$(GLIBC_VERSION)/io/dup2.c
#  glibc-$(GLIBC_VERSION)/io/getcwd.c
#  glibc-$(GLIBC_VERSION)/io/isatty.c
#  glibc-$(GLIBC_VERSION)/io/lseek.c
#  glibc-$(GLIBC_VERSION)/io/lseek64.c
#  glibc-$(GLIBC_VERSION)/io/lxstat64.c
#  glibc-$(GLIBC_VERSION)/io/open.c
#  glibc-$(GLIBC_VERSION)/io/read.c
#  glibc-$(GLIBC_VERSION)/io/unlink.c
#  glibc-$(GLIBC_VERSION)/io/write.c
#  glibc-$(GLIBC_VERSION)/io/xstat.c
#  glibc-$(GLIBC_VERSION)/io/xstat64.c
#  glibc-$(GLIBC_VERSION)/misc/brk.c
#  glibc-$(GLIBC_VERSION)/misc/ftruncate.c
#  glibc-$(GLIBC_VERSION)/misc/gethostname.c
#  glibc-$(GLIBC_VERSION)/misc/getpagesize.c
#  glibc-$(GLIBC_VERSION)/misc/getsysstats.c
#  glibc-$(GLIBC_VERSION)/misc/madvise.c
#  glibc-$(GLIBC_VERSION)/misc/writev.c
#  glibc-$(GLIBC_VERSION)/posix/_exit.c
#  glibc-$(GLIBC_VERSION)/posix/getpid.c
#  glibc-$(GLIBC_VERSION)/posix/sleep.c
#  glibc-$(GLIBC_VERSION)/posix/pathconf.c
#  glibc-$(GLIBC_VERSION)/signal/raise.c
#  glibc-$(GLIBC_VERSION)/stdlib/abort.c
#  glibc-$(GLIBC_VERSION)/time/gettimeofday.c
#  glibc-$(GLIBC_VERSION)/time/time.c

HEADERS = \
  $(INCDIR)/arpa/inet.h \
  $(INCDIR)/bits/byteswap.h \
  $(INCDIR)/bits/byteswap-16.h \
  $(INCDIR)/bits/cmathcalls.h \
  $(INCDIR)/bits/confname.h \
  $(INCDIR)/bits/endian.h \
  $(INCDIR)/bits/environments.h \
  $(INCDIR)/bits/errno.h \
  $(INCDIR)/bits/fcntl.h \
  $(INCDIR)/bits/fcntl2.h \
  $(INCDIR)/bits/huge_val.h \
  $(INCDIR)/bits/huge_valf.h \
  $(INCDIR)/bits/huge_vall.h \
  $(INCDIR)/bits/in.h \
  $(INCDIR)/bits/inf.h \
  $(INCDIR)/bits/ioctl-types.h \
  $(INCDIR)/bits/ioctls.h \
  $(INCDIR)/bits/locale.h \
  $(INCDIR)/bits/mathcalls.h \
  $(INCDIR)/bits/mathdef.h \
  $(INCDIR)/bits/mathinline.h \
  $(INCDIR)/bits/mman.h \
  $(INCDIR)/bits/nan.h \
  $(INCDIR)/bits/param.h \
  $(INCDIR)/bits/poll.h \
  $(INCDIR)/bits/poll2.h \
  $(INCDIR)/bits/posix_opt.h \
  $(INCDIR)/bits/pthreadtypes.h \
  $(INCDIR)/bits/resource.h \
  $(INCDIR)/bits/sched.h \
  $(INCDIR)/bits/select.h \
  $(INCDIR)/bits/select2.h \
  $(INCDIR)/bits/setjmp.h \
  $(INCDIR)/bits/sigaction.h \
  $(INCDIR)/bits/sigcontext.h \
  $(INCDIR)/bits/siginfo.h \
  $(INCDIR)/bits/signum.h \
  $(INCDIR)/bits/sigset.h \
  $(INCDIR)/bits/sigstack.h \
  $(INCDIR)/bits/sigthread.h \
  $(INCDIR)/bits/sockaddr.h \
  $(INCDIR)/bits/socket.h \
  $(INCDIR)/bits/stat.h \
  $(INCDIR)/bits/stdio.h \
  $(INCDIR)/bits/stdio2.h \
  $(INCDIR)/bits/stdio_lim.h \
  $(INCDIR)/bits/stdlib-float.h \
  $(INCDIR)/bits/stdlib.h \
  $(INCDIR)/bits/string.h \
  $(INCDIR)/bits/string2.h \
  $(INCDIR)/bits/string3.h \
  $(INCDIR)/bits/sys_errlist.h \
  $(INCDIR)/bits/time.h \
  $(INCDIR)/bits/types.h \
  $(INCDIR)/bits/typesizes.h \
  $(INCDIR)/bits/uio.h \
  $(INCDIR)/bits/unistd.h \
  $(INCDIR)/bits/utsname.h \
  $(INCDIR)/bits/waitflags.h \
  $(INCDIR)/bits/waitstatus.h \
  $(INCDIR)/bits/wchar.h \
  $(INCDIR)/bits/wchar2.h \
  $(INCDIR)/bits/wordsize.h \
  $(INCDIR)/gnu/stubs.h \
  $(INCDIR)/netinet/in.h \
  $(INCDIR)/netinet/tcp.h \
  $(INCDIR)/sys/cdefs.h \
  $(INCDIR)/sys/ioctl.h \
  $(INCDIR)/sys/mman.h \
  $(INCDIR)/sys/param.h \
  $(INCDIR)/sys/poll.h \
  $(INCDIR)/sys/resource.h \
  $(INCDIR)/sys/select.h \
  $(INCDIR)/sys/socket.h \
  $(INCDIR)/sys/stat.h \
  $(INCDIR)/sys/syscall.h \
  $(INCDIR)/sys/sysinfo.h \
  $(INCDIR)/sys/sysmacros.h \
  $(INCDIR)/sys/time.h \
  $(INCDIR)/sys/times.h \
  $(INCDIR)/sys/ttydefaults.h \
  $(INCDIR)/sys/types.h \
  $(INCDIR)/sys/ucontext.h \
  $(INCDIR)/sys/uio.h \
  $(INCDIR)/sys/utsname.h \
  $(INCDIR)/sys/wait.h \
  $(INCDIR)/_G_config.h \
  $(INCDIR)/alloca.h \
  $(INCDIR)/assert.h \
  $(INCDIR)/complex.h \
  $(INCDIR)/ctype.h \
  $(INCDIR)/endian.h \
  $(INCDIR)/errno.h \
  $(INCDIR)/fcntl.h \
  $(INCDIR)/features.h \
  $(INCDIR)/float.h \
  $(INCDIR)/getopt.h \
  $(INCDIR)/glimits.h \
  $(INCDIR)/gmp.h \
  $(INCDIR)/inttypes.h \
  $(INCDIR)/iso646.h \
  $(INCDIR)/langinfo.h \
  $(INCDIR)/libintl.h \
  $(INCDIR)/libio.h \
  $(INCDIR)/limits.h \
  $(INCDIR)/locale.h \
  $(INCDIR)/malloc.h \
  $(INCDIR)/math.h \
  $(INCDIR)/netdb.h \
  $(INCDIR)/nl_types.h \
  $(INCDIR)/poll.h \
  $(INCDIR)/pthread.h \
  $(INCDIR)/pwd.h \
  $(INCDIR)/sched.h \
  $(INCDIR)/signal.h \
  $(INCDIR)/stdalign.h \
  $(INCDIR)/stdarg.h \
  $(INCDIR)/stdbool.h \
  $(INCDIR)/stdc-predef.h \
  $(INCDIR)/stddef.h \
  $(INCDIR)/stdfix.h \
  $(INCDIR)/stdint-gcc.h \
  $(INCDIR)/stdint-wrap.h \
  $(INCDIR)/stdint.h \
  $(INCDIR)/stdio.h \
  $(INCDIR)/stdlib.h \
  $(INCDIR)/stdnoreturn.h \
  $(INCDIR)/string.h \
  $(INCDIR)/strings.h \
  $(INCDIR)/syscall.h \
  $(INCDIR)/time.h \
  $(INCDIR)/unistd.h \
  $(INCDIR)/varargs.h \
  $(INCDIR)/wchar.h \
  $(INCDIR)/wctype.h \
  $(INCDIR)/xlocale.h

OBJECTS  = $(ASM_SOURCES:%.S=$(OBJDIR)/%.o)
OBJECTS += $(C_SOURCES:%.c=$(OBJDIR)/%.o)
DEPENDS += $(OBJECTS:%.o=%.d)

.PHONY: all
all : $(LIBDIR)/glibc.a $(HEADERS)

.PHONY: headers
headers : $(HEADERS)

$(LIBDIR)/glibc.a: $(OBJECTS)
	@[ -d $(@D) ] || (mkdir -p $(@D))
	@echo linking: $@
	@$(AR) r $@ $(OBJECTS)
	@echo successfully built: $@
	@echo

$(INCDIR)/% : $(SRCDIR)/glibc-$(GLIBC_VERSION)/nptl/sysdeps/llamaos/x86/%
	@[ -d $(@D) ] || (mkdir -p $(@D))
	@echo copying: $@ from $<
	cp $< $@

$(INCDIR)/% : $(SRCDIR)/glibc-$(GLIBC_VERSION)/sysdeps/llamaos/x86/%
	@[ -d $(@D) ] || (mkdir -p $(@D))
	@echo copying: $@ from $<
	cp $< $@

$(INCDIR)/% : $(SRCDIR)/glibc-$(GLIBC_VERSION)/nptl/sysdeps/pthread/%
	@[ -d $(@D) ] || (mkdir -p $(@D))
	@echo copying: $@ from $<
	cp $< $@

$(INCDIR)/% : $(SRCDIR)/glibc-$(GLIBC_VERSION)/sysdeps/llamaos/%
	@[ -d $(@D) ] || (mkdir -p $(@D))
	@echo copying: $@ from $<
	cp $< $@

$(INCDIR)/% : $(SRCDIR)/glibc-$(GLIBC_VERSION)/sysdeps/x86/fpu/%
	@[ -d $(@D) ] || (mkdir -p $(@D))
	@echo copying: $@ from $<
	cp $< $@

$(INCDIR)/% : $(SRCDIR)/glibc-$(GLIBC_VERSION)/sysdeps/x86/%
	@[ -d $(@D) ] || (mkdir -p $(@D))
	@echo copying: $@ from $<
	cp $< $@

$(INCDIR)/% : $(SRCDIR)/glibc-$(GLIBC_VERSION)/sysdeps/wordsize-64/%
	@[ -d $(@D) ] || (mkdir -p $(@D))
	@echo copying: $@ from $<
	cp $< $@

$(INCDIR)/% : $(SRCDIR)/glibc-$(GLIBC_VERSION)/sysdeps/ieee754/%
	@[ -d $(@D) ] || (mkdir -p $(@D))
	@echo copying: $@ from $<
	cp $< $@

$(INCDIR)/% : $(SRCDIR)/glibc-$(GLIBC_VERSION)/sysdeps/generic/%
	@[ -d $(@D) ] || (mkdir -p $(@D))
	@echo copying: $@ from $<
	cp $< $@

$(INCDIR)/% : $(SRCDIR)/glibc-$(GLIBC_VERSION)/assert/%
	@[ -d $(@D) ] || (mkdir -p $(@D))
	@echo copying: $@ from $<
	cp $< $@

$(INCDIR)/% : $(SRCDIR)/glibc-$(GLIBC_VERSION)/catgets/%
	@[ -d $(@D) ] || (mkdir -p $(@D))
	@echo copying: $@ from $<
	cp $< $@

$(INCDIR)/% : $(SRCDIR)/glibc-$(GLIBC_VERSION)/ctype/%
	@[ -d $(@D) ] || (mkdir -p $(@D))
	@echo copying: $@ from $<
	cp $< $@

$(INCDIR)/% : $(SRCDIR)/glibc-$(GLIBC_VERSION)/inet/%
	@[ -d $(@D) ] || (mkdir -p $(@D))
	@echo copying: $@ from $<
	cp $< $@

$(INCDIR)/% : $(SRCDIR)/glibc-$(GLIBC_VERSION)/intl/%
	@[ -d $(@D) ] || (mkdir -p $(@D))
	@echo copying: $@ from $<
	cp $< $@

$(INCDIR)/% : $(SRCDIR)/glibc-$(GLIBC_VERSION)/io/%
	@[ -d $(@D) ] || (mkdir -p $(@D))
	@echo copying: $@ from $<
	cp $< $@

$(INCDIR)/% : $(SRCDIR)/glibc-$(GLIBC_VERSION)/locale/%
	@[ -d $(@D) ] || (mkdir -p $(@D))
	@echo copying: $@ from $<
	cp $< $@

$(INCDIR)/% : $(SRCDIR)/glibc-$(GLIBC_VERSION)/libio/%
	@[ -d $(@D) ] || (mkdir -p $(@D))
	@echo copying: $@ from $<
	cp $< $@

$(INCDIR)/% : $(SRCDIR)/glibc-$(GLIBC_VERSION)/malloc/%
	@[ -d $(@D) ] || (mkdir -p $(@D))
	@echo copying: $@ from $<
	cp $< $@

$(INCDIR)/% : $(SRCDIR)/glibc-$(GLIBC_VERSION)/math/%
	@[ -d $(@D) ] || (mkdir -p $(@D))
	@echo copying: $@ from $<
	cp $< $@

$(INCDIR)/% : $(SRCDIR)/glibc-$(GLIBC_VERSION)/misc/%
	@[ -d $(@D) ] || (mkdir -p $(@D))
	@echo copying: $@ from $<
	cp $< $@

$(INCDIR)/% : $(SRCDIR)/glibc-$(GLIBC_VERSION)/posix/%
	@[ -d $(@D) ] || (mkdir -p $(@D))
	@echo copying: $@ from $<
	cp $< $@

$(INCDIR)/% : $(SRCDIR)/glibc-$(GLIBC_VERSION)/pwd/%
	@[ -d $(@D) ] || (mkdir -p $(@D))
	@echo copying: $@ from $<
	cp $< $@

$(INCDIR)/% : $(SRCDIR)/glibc-$(GLIBC_VERSION)/resource/%
	@[ -d $(@D) ] || (mkdir -p $(@D))
	@echo copying: $@ from $<
	cp $< $@

$(INCDIR)/% : $(SRCDIR)/glibc-$(GLIBC_VERSION)/signal/%
	@[ -d $(@D) ] || (mkdir -p $(@D))
	@echo copying: $@ from $<
	cp $< $@

$(INCDIR)/% : $(SRCDIR)/glibc-$(GLIBC_VERSION)/socket/%
	@[ -d $(@D) ] || (mkdir -p $(@D))
	@echo copying: $@ from $<
	cp $< $@

$(INCDIR)/% : $(SRCDIR)/glibc-$(GLIBC_VERSION)/stdlib/%
	@[ -d $(@D) ] || (mkdir -p $(@D))
	@echo copying: $@ from $<
	cp $< $@

$(INCDIR)/% : $(SRCDIR)/glibc-$(GLIBC_VERSION)/string/%
	@[ -d $(@D) ] || (mkdir -p $(@D))
	@echo copying: $@ from $<
	cp $< $@

$(INCDIR)/% : $(SRCDIR)/glibc-$(GLIBC_VERSION)/time/%
	@[ -d $(@D) ] || (mkdir -p $(@D))
	@echo copying: $@ from $<
	cp $< $@

$(INCDIR)/% : $(SRCDIR)/glibc-$(GLIBC_VERSION)/wcsmbs/%
	@[ -d $(@D) ] || (mkdir -p $(@D))
	@echo copying: $@ from $<
	cp $< $@

$(INCDIR)/% : $(SRCDIR)/glibc-$(GLIBC_VERSION)/wctype/%
	@[ -d $(@D) ] || (mkdir -p $(@D))
	@echo copying: $@ from $<
	cp $< $@

# catches things like bits/*.h that specify path
$(INCDIR)/% : $(SRCDIR)/glibc-$(GLIBC_VERSION)/%
	@[ -d $(@D) ] || (mkdir -p $(@D))
	@echo copying: $@ from $<
	cp $< $@

$(INCDIR)/gnu/stubs.h : $(SRCDIR)/glibc-$(GLIBC_VERSION)/include/gnu/stubs.h
	@[ -d $(@D) ] || (mkdir -p $(@D))
	@echo copying: $@ from $<
	cp $< $@

$(INCDIR)/features.h : $(SRCDIR)/glibc-$(GLIBC_VERSION)/include/features.h
	@[ -d $(@D) ] || (mkdir -p $(@D))
	@echo copying: $@ from $<
	cp $< $@

$(INCDIR)/stdc-predef.h : $(SRCDIR)/glibc-$(GLIBC_VERSION)/include/stdc-predef.h
	@[ -d $(@D) ] || (mkdir -p $(@D))
	@echo copying: $@ from $<
	cp $< $@

# some files come from the gcc source
$(INCDIR)/float.h : $(SRCDIR)/gcc-$(GCC_VERSION)/gcc/ginclude/float.h
	@[ -d $(@D) ] || (mkdir -p $(@D))
	@echo copying: $@ from $<
	cp $< $@

$(INCDIR)/iso646.h : $(SRCDIR)/gcc-$(GCC_VERSION)/gcc/ginclude/iso646.h
	@[ -d $(@D) ] || (mkdir -p $(@D))
	@echo copying: $@ from $<
	cp $< $@

$(INCDIR)/stdalign.h : $(SRCDIR)/gcc-$(GCC_VERSION)/gcc/ginclude/stdalign.h
	@[ -d $(@D) ] || (mkdir -p $(@D))
	@echo copying: $@ from $<
	cp $< $@

$(INCDIR)/stdarg.h : $(SRCDIR)/gcc-$(GCC_VERSION)/gcc/ginclude/stdarg.h
	@[ -d $(@D) ] || (mkdir -p $(@D))
	@echo copying: $@ from $<
	cp $< $@

$(INCDIR)/stdbool.h : $(SRCDIR)/gcc-$(GCC_VERSION)/gcc/ginclude/stdbool.h
	@[ -d $(@D) ] || (mkdir -p $(@D))
	@echo copying: $@ from $<
	cp $< $@

$(INCDIR)/stddef.h : $(SRCDIR)/gcc-$(GCC_VERSION)/gcc/ginclude/stddef.h
	@[ -d $(@D) ] || (mkdir -p $(@D))
	@echo copying: $@ from $<
	cp $< $@

$(INCDIR)/stdfix.h : $(SRCDIR)/gcc-$(GCC_VERSION)/gcc/ginclude/stdfix.h
	@[ -d $(@D) ] || (mkdir -p $(@D))
	@echo copying: $@ from $<
	cp $< $@

$(INCDIR)/stdint-gcc.h : $(SRCDIR)/gcc-$(GCC_VERSION)/gcc/ginclude/stdint-gcc.h
	@[ -d $(@D) ] || (mkdir -p $(@D))
	@echo copying: $@ from $<
	cp $< $@

$(INCDIR)/stdint-wrap.h : $(SRCDIR)/gcc-$(GCC_VERSION)/gcc/ginclude/stdint-wrap.h
	@[ -d $(@D) ] || (mkdir -p $(@D))
	@echo copying: $@ from $<
	cp $< $@

$(INCDIR)/stdnoreturn.h : $(SRCDIR)/gcc-$(GCC_VERSION)/gcc/ginclude/stdnoreturn.h
	@[ -d $(@D) ] || (mkdir -p $(@D))
	@echo copying: $@ from $<
	cp $< $@

$(INCDIR)/varargs.h : $(SRCDIR)/gcc-$(GCC_VERSION)/gcc/ginclude/varargs.h
	@[ -d $(@D) ] || (mkdir -p $(@D))
	@echo copying: $@ from $<
	cp $< $@

$(INCDIR)/glimits.h : $(SRCDIR)/gcc-$(GCC_VERSION)/gcc/glimits.h
	@[ -d $(@D) ] || (mkdir -p $(@D))
	@echo copying: $@ from $<
	cp $< $@

include rules.mk

# include auto-generated dependencies
-include $(DEPENDS)

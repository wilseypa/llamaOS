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

MAKEFILE_SOURCES += sys/glibc-$(GLIBC_VERSION).mk

INCLUDES_DIRS = \
  -I $(SRCDIR)/sys/glibc-$(GLIBC_VERSION)/include \
  -I $(SRCDIR)/sys/glibc-$(GLIBC_VERSION)/sysdeps/llamaos/x86_64/64/nptl \
  -I $(SRCDIR)/sys/glibc-$(GLIBC_VERSION)/sysdeps/llamaos/x86_64/64 \
  -I $(SRCDIR)/sys/glibc-$(GLIBC_VERSION)/nptl/sysdeps/llamaos/x86_64 \
  -I $(SRCDIR)/sys/glibc-$(GLIBC_VERSION)/nptl/sysdeps/llamaos/x86 \
  -I $(SRCDIR)/sys/glibc-$(GLIBC_VERSION)/sysdeps/llamaos/x86_64 \
  -I $(SRCDIR)/sys/glibc-$(GLIBC_VERSION)/sysdeps/llamaos/x86 \
  -I $(SRCDIR)/sys/glibc-$(GLIBC_VERSION)/sysdeps/llamaos/wordsize-64 \
  -I $(SRCDIR)/sys/glibc-$(GLIBC_VERSION)/nptl/sysdeps/llamaos \
  -I $(SRCDIR)/sys/glibc-$(GLIBC_VERSION)/nptl/sysdeps/pthread \
  -I $(SRCDIR)/sys/glibc-$(GLIBC_VERSION)/sysdeps/pthread \
  -I $(SRCDIR)/sys/glibc-$(GLIBC_VERSION)/sysdeps/llamaos \
  -I $(SRCDIR)/sys/glibc-$(GLIBC_VERSION)/sysdeps/gnu \
  -I $(SRCDIR)/sys/glibc-$(GLIBC_VERSION)/sysdeps/posix \
  -I $(SRCDIR)/sys/glibc-$(GLIBC_VERSION)/nptl/sysdeps/x86_64/64 \
  -I $(SRCDIR)/sys/glibc-$(GLIBC_VERSION)/sysdeps/x86_64/64 \
  -I $(SRCDIR)/sys/glibc-$(GLIBC_VERSION)/sysdeps/x86_64/fpu \
  -I $(SRCDIR)/sys/glibc-$(GLIBC_VERSION)/sysdeps/x86/fpu \
  -I $(SRCDIR)/sys/glibc-$(GLIBC_VERSION)/nptl/sysdeps/x86_64 \
  -I $(SRCDIR)/sys/glibc-$(GLIBC_VERSION)/sysdeps/x86_64 \
  -I $(SRCDIR)/sys/glibc-$(GLIBC_VERSION)/sysdeps/x86 \
  -I $(SRCDIR)/sys/glibc-$(GLIBC_VERSION)/sysdeps/ieee754/ldbl-96 \
  -I $(SRCDIR)/sys/glibc-$(GLIBC_VERSION)/sysdeps/ieee754/dbl-64/wordsize-64 \
  -I $(SRCDIR)/sys/glibc-$(GLIBC_VERSION)/sysdeps/ieee754/dbl-64 \
  -I $(SRCDIR)/sys/glibc-$(GLIBC_VERSION)/sysdeps/ieee754/flt-32 \
  -I $(SRCDIR)/sys/glibc-$(GLIBC_VERSION)/sysdeps/wordsize-64 \
  -I $(SRCDIR)/sys/glibc-$(GLIBC_VERSION)/sysdeps/ieee754 \
  -I $(SRCDIR)/sys/glibc-$(GLIBC_VERSION)/sysdeps/generic \
  -I $(SRCDIR)/sys/glibc-$(GLIBC_VERSION)/nptl \
  -I $(SRCDIR)/sys/glibc-$(GLIBC_VERSION) \
  -I $(SRCDIR)/sys/glibc-$(GLIBC_VERSION)/csu \
  -I $(SRCDIR)/sys/glibc-$(GLIBC_VERSION)/elf \
  -I $(SRCDIR)/sys/glibc-$(GLIBC_VERSION)/iconv \
  -I $(SRCDIR)/sys/glibc-$(GLIBC_VERSION)/libio \
  -I $(SRCDIR)/sys/glibc-$(GLIBC_VERSION)/locale \
  -I $(SRCDIR)/sys/glibc-$(GLIBC_VERSION)/math \
  -I $(SRCDIR)/sys/glibc-$(GLIBC_VERSION)/stdio-common \
  -I $(SRCDIR)/sys/glibc-$(GLIBC_VERSION)/stdlib \
  -I $(SRCDIR)/sys/glibc-$(GLIBC_VERSION)/wcsmbs \
  -I $(SRCDIR)/sys/gcc-$(GCC_VERSION)/gcc/ginclude \
  -I $(SRCDIR)/sys/gcc-$(GCC_VERSION)/gcc/include \
  -I $(SRCDIR)/sys/gcc-$(GCC_VERSION)/gcc \
  -I $(SRCDIR)

ASMFLAGS += \
  -U_FORTIFY_SOURCE \
  -D__USE_FORTIFY_LEVEL=0 \
  -D_LIBC_REENTRANT \
  -DASSEMBLER \
  -Wa,--noexecstack \
  $(INCLUDES_DIRS) \
  -include  $(SRCDIR)/sys/glibc-$(GLIBC_VERSION)/include/libc-symbols.h \
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
  -include  $(SRCDIR)/sys/glibc-$(GLIBC_VERSION)/include/libc-symbols.h \
  -include $(SRCDIR)/llamaos/__thread.h

#  -fexceptions \

VPATH = $(SRCDIR)

ASM_SOURCES = \
  sys/glibc-$(GLIBC_VERSION)/csu/abi-note.S \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/x86_64/fpu/e_exp2l.S \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/x86_64/fpu/e_exp10l.S \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/x86_64/fpu/e_expl.S \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/x86_64/fpu/e_fmodl.S \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/x86_64/fpu/e_ilogbl.S \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/x86_64/fpu/e_log2l.S \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/x86_64/fpu/e_log10l.S \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/x86_64/fpu/e_logl.S \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/x86_64/fpu/e_powl.S \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/x86_64/fpu/e_remainderl.S \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/x86_64/fpu/e_scalbl.S \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/x86_64/fpu/s_ceill.S \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/x86_64/fpu/s_copysign.S \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/x86_64/fpu/s_copysignf.S \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/x86_64/fpu/s_copysignl.S \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/x86_64/fpu/s_cosf.S \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/x86_64/fpu/s_expm1l.S \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/x86_64/fpu/s_fabsl.S \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/x86_64/fpu/s_finitel.S \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/x86_64/fpu/s_floorl.S \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/x86_64/fpu/s_llrint.S \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/x86_64/fpu/s_llrintf.S \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/x86_64/fpu/s_llrintl.S \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/x86_64/fpu/s_log1pl.S \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/x86_64/fpu/s_lrint.S \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/x86_64/fpu/s_lrintf.S \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/x86_64/fpu/s_lrintl.S \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/x86_64/fpu/s_fdiml.S \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/x86_64/fpu/s_fmax.S \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/x86_64/fpu/s_fmaxf.S \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/x86_64/fpu/s_fmaxl.S \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/x86_64/fpu/s_fmin.S \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/x86_64/fpu/s_fminf.S \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/x86_64/fpu/s_fminl.S \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/x86_64/fpu/s_scalbnl.S \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/x86_64/fpu/s_signbit.S \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/x86_64/fpu/s_signbitf.S \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/x86_64/fpu/s_sincosf.S \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/x86_64/fpu/s_sinf.S \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/x86_64/fpu/s_truncl.S \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/x86_64/_mcount.S \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/x86_64/add_n.S \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/x86_64/addmul_1.S \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/x86_64/__longjmp.S \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/x86_64/bsd-_setjmp.S \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/x86_64/bsd-setjmp.S \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/x86_64/bzero.S \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/x86_64/crti.S \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/x86_64/crtn.S \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/x86_64/dl-tlsdesc.S \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/x86_64/dl-trampoline.S \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/x86_64/lshift.S \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/x86_64/memchr.S \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/x86_64/memcmp.S \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/x86_64/memcpy.S \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/x86_64/mempcpy.S \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/x86_64/memrchr.S \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/x86_64/memset.S \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/x86_64/mul_1.S \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/x86_64/rawmemchr.S \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/x86_64/rshift.S \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/x86_64/setjmp.S \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/x86_64/stpcpy.S \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/x86_64/strcasecmp.S \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/x86_64/strcat.S \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/x86_64/strchr.S \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/x86_64/strchrnul.S \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/x86_64/strcmp.S \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/x86_64/strcpy.S \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/x86_64/strcspn.S \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/x86_64/strlen.S \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/x86_64/strncase.S \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/x86_64/strncmp.S \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/x86_64/strnlen.S \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/x86_64/strpbrk.S \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/x86_64/strrchr.S \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/x86_64/strspn.S \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/x86_64/strtok.S \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/x86_64/strtok_r.S \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/x86_64/sub_n.S \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/x86_64/submul_1.S \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/x86_64/wcschr.S \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/x86_64/wcscmp.S \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/x86_64/wcslen.S \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/x86_64/wcsrchr.S

# these have TLS conflicts
#  sys/glibc-$(GLIBC_VERSION)/sysdeps/x86_64/strcasecmp_l.S \
#  sys/glibc-$(GLIBC_VERSION)/sysdeps/x86_64/strncase_l.S \

C_SOURCES = \
  sys/glibc-$(GLIBC_VERSION)/assert/__assert.c \
  sys/glibc-$(GLIBC_VERSION)/catgets/catgets.c \
  sys/glibc-$(GLIBC_VERSION)/catgets/open_catalog.c \
  sys/glibc-$(GLIBC_VERSION)/csu/dso_handle.c \
  sys/glibc-$(GLIBC_VERSION)/csu/elf-init.c \
  sys/glibc-$(GLIBC_VERSION)/csu/errno-loc.c \
  sys/glibc-$(GLIBC_VERSION)/csu/errno.c \
  sys/glibc-$(GLIBC_VERSION)/csu/gmon-start.c \
  sys/glibc-$(GLIBC_VERSION)/csu/init-first.c \
  sys/glibc-$(GLIBC_VERSION)/csu/init.c \
  sys/glibc-$(GLIBC_VERSION)/csu/libc-start.c \
  sys/glibc-$(GLIBC_VERSION)/csu/libc-tls.c \
  sys/glibc-$(GLIBC_VERSION)/csu/version.c \
  sys/glibc-$(GLIBC_VERSION)/ctype/ctype-extn.c \
  sys/glibc-$(GLIBC_VERSION)/ctype/ctype-info.c \
  sys/glibc-$(GLIBC_VERSION)/ctype/ctype.c \
  sys/glibc-$(GLIBC_VERSION)/ctype/ctype_l.c \
  sys/glibc-$(GLIBC_VERSION)/ctype/isctype.c \
  sys/glibc-$(GLIBC_VERSION)/debug/asprintf_chk.c \
  sys/glibc-$(GLIBC_VERSION)/debug/chk_fail.c \
  sys/glibc-$(GLIBC_VERSION)/debug/confstr_chk.c \
  sys/glibc-$(GLIBC_VERSION)/debug/dprintf_chk.c \
  sys/glibc-$(GLIBC_VERSION)/debug/fdelt_chk.c \
  sys/glibc-$(GLIBC_VERSION)/debug/fgets_chk.c \
  sys/glibc-$(GLIBC_VERSION)/debug/fgets_u_chk.c \
  sys/glibc-$(GLIBC_VERSION)/debug/fgetws_chk.c \
  sys/glibc-$(GLIBC_VERSION)/debug/fgetws_u_chk.c \
  sys/glibc-$(GLIBC_VERSION)/debug/fortify_fail.c \
  sys/glibc-$(GLIBC_VERSION)/debug/fprintf_chk.c \
  sys/glibc-$(GLIBC_VERSION)/debug/fread_chk.c \
  sys/glibc-$(GLIBC_VERSION)/debug/fread_u_chk.c \
  sys/glibc-$(GLIBC_VERSION)/debug/fwprintf_chk.c \
  sys/glibc-$(GLIBC_VERSION)/debug/getcwd_chk.c \
  sys/glibc-$(GLIBC_VERSION)/debug/getdomainname_chk.c \
  sys/glibc-$(GLIBC_VERSION)/debug/getgroups_chk.c \
  sys/glibc-$(GLIBC_VERSION)/debug/gethostname_chk.c \
  sys/glibc-$(GLIBC_VERSION)/debug/getlogin_r_chk.c \
  sys/glibc-$(GLIBC_VERSION)/debug/gets_chk.c \
  sys/glibc-$(GLIBC_VERSION)/debug/getwd_chk.c \
  sys/glibc-$(GLIBC_VERSION)/debug/longjmp_chk.c \
  sys/glibc-$(GLIBC_VERSION)/debug/mbsnrtowcs_chk.c \
  sys/glibc-$(GLIBC_VERSION)/debug/mbsrtowcs_chk.c \
  sys/glibc-$(GLIBC_VERSION)/debug/mbstowcs_chk.c \
  sys/glibc-$(GLIBC_VERSION)/debug/memcpy_chk.c \
  sys/glibc-$(GLIBC_VERSION)/debug/memmove_chk.c \
  sys/glibc-$(GLIBC_VERSION)/debug/mempcpy_chk.c \
  sys/glibc-$(GLIBC_VERSION)/debug/memset_chk.c \
  sys/glibc-$(GLIBC_VERSION)/debug/noophooks.c \
  sys/glibc-$(GLIBC_VERSION)/debug/obprintf_chk.c \
  sys/glibc-$(GLIBC_VERSION)/debug/poll_chk.c \
  sys/glibc-$(GLIBC_VERSION)/debug/ppoll_chk.c \
  sys/glibc-$(GLIBC_VERSION)/debug/pread64_chk.c \
  sys/glibc-$(GLIBC_VERSION)/debug/pread_chk.c \
  sys/glibc-$(GLIBC_VERSION)/debug/printf_chk.c \
  sys/glibc-$(GLIBC_VERSION)/debug/ptsname_r_chk.c \
  sys/glibc-$(GLIBC_VERSION)/debug/read_chk.c \
  sys/glibc-$(GLIBC_VERSION)/debug/readlink_chk.c \
  sys/glibc-$(GLIBC_VERSION)/debug/readlinkat_chk.c \
  sys/glibc-$(GLIBC_VERSION)/debug/readonly-area.c \
  sys/glibc-$(GLIBC_VERSION)/debug/realpath_chk.c \
  sys/glibc-$(GLIBC_VERSION)/debug/recv_chk.c \
  sys/glibc-$(GLIBC_VERSION)/debug/recvfrom_chk.c \
  sys/glibc-$(GLIBC_VERSION)/debug/snprintf_chk.c \
  sys/glibc-$(GLIBC_VERSION)/debug/sprintf_chk.c \
  sys/glibc-$(GLIBC_VERSION)/debug/stack_chk_fail.c \
  sys/glibc-$(GLIBC_VERSION)/debug/stack_chk_fail_local.c \
  sys/glibc-$(GLIBC_VERSION)/debug/stpcpy_chk.c \
  sys/glibc-$(GLIBC_VERSION)/debug/stpncpy_chk.c \
  sys/glibc-$(GLIBC_VERSION)/debug/strcat_chk.c \
  sys/glibc-$(GLIBC_VERSION)/debug/strcpy_chk.c \
  sys/glibc-$(GLIBC_VERSION)/debug/strncat_chk.c \
  sys/glibc-$(GLIBC_VERSION)/debug/strncpy_chk.c \
  sys/glibc-$(GLIBC_VERSION)/debug/swprintf_chk.c \
  sys/glibc-$(GLIBC_VERSION)/debug/ttyname_r_chk.c \
  sys/glibc-$(GLIBC_VERSION)/debug/vasprintf_chk.c \
  sys/glibc-$(GLIBC_VERSION)/debug/vdprintf_chk.c \
  sys/glibc-$(GLIBC_VERSION)/debug/vfprintf_chk.c \
  sys/glibc-$(GLIBC_VERSION)/debug/vfwprintf_chk.c \
  sys/glibc-$(GLIBC_VERSION)/debug/vprintf_chk.c \
  sys/glibc-$(GLIBC_VERSION)/debug/vsnprintf_chk.c \
  sys/glibc-$(GLIBC_VERSION)/debug/vsprintf_chk.c \
  sys/glibc-$(GLIBC_VERSION)/debug/vswprintf_chk.c \
  sys/glibc-$(GLIBC_VERSION)/debug/vwprintf_chk.c \
  sys/glibc-$(GLIBC_VERSION)/debug/wcpcpy_chk.c \
  sys/glibc-$(GLIBC_VERSION)/debug/wcpncpy_chk.c \
  sys/glibc-$(GLIBC_VERSION)/debug/wcrtomb_chk.c \
  sys/glibc-$(GLIBC_VERSION)/debug/wcscat_chk.c \
  sys/glibc-$(GLIBC_VERSION)/debug/wcscpy_chk.c \
  sys/glibc-$(GLIBC_VERSION)/debug/wcsncat_chk.c \
  sys/glibc-$(GLIBC_VERSION)/debug/wcsncpy_chk.c \
  sys/glibc-$(GLIBC_VERSION)/debug/wcsnrtombs_chk.c \
  sys/glibc-$(GLIBC_VERSION)/debug/wcsrtombs_chk.c \
  sys/glibc-$(GLIBC_VERSION)/debug/wcstombs_chk.c \
  sys/glibc-$(GLIBC_VERSION)/debug/wctomb_chk.c \
  sys/glibc-$(GLIBC_VERSION)/debug/wmemcpy_chk.c \
  sys/glibc-$(GLIBC_VERSION)/debug/wmemmove_chk.c \
  sys/glibc-$(GLIBC_VERSION)/debug/wmempcpy_chk.c \
  sys/glibc-$(GLIBC_VERSION)/debug/wmemset_chk.c \
  sys/glibc-$(GLIBC_VERSION)/debug/wprintf_chk.c \
  sys/glibc-$(GLIBC_VERSION)/elf/dl-addr.c \
  sys/glibc-$(GLIBC_VERSION)/elf/dl-cache.c \
  sys/glibc-$(GLIBC_VERSION)/elf/dl-close.c \
  sys/glibc-$(GLIBC_VERSION)/elf/dl-conflict.c \
  sys/glibc-$(GLIBC_VERSION)/elf/dl-debug.c \
  sys/glibc-$(GLIBC_VERSION)/elf/dl-deps.c \
  sys/glibc-$(GLIBC_VERSION)/elf/dl-error.c \
  sys/glibc-$(GLIBC_VERSION)/elf/dl-execstack.c \
  sys/glibc-$(GLIBC_VERSION)/elf/dl-fini.c \
  sys/glibc-$(GLIBC_VERSION)/elf/dl-hwcaps.c \
  sys/glibc-$(GLIBC_VERSION)/elf/dl-init.c \
  sys/glibc-$(GLIBC_VERSION)/elf/dl-iteratephdr.c \
  sys/glibc-$(GLIBC_VERSION)/elf/dl-libc.c \
  sys/glibc-$(GLIBC_VERSION)/elf/dl-load.c \
  sys/glibc-$(GLIBC_VERSION)/elf/dl-lookup.c \
  sys/glibc-$(GLIBC_VERSION)/elf/dl-misc.c \
  sys/glibc-$(GLIBC_VERSION)/elf/dl-object.c \
  sys/glibc-$(GLIBC_VERSION)/elf/dl-open.c \
  sys/glibc-$(GLIBC_VERSION)/elf/dl-origin.c \
  sys/glibc-$(GLIBC_VERSION)/elf/dl-profile.c \
  sys/glibc-$(GLIBC_VERSION)/elf/dl-profstub.c \
  sys/glibc-$(GLIBC_VERSION)/elf/dl-reloc.c \
  sys/glibc-$(GLIBC_VERSION)/elf/dl-scope.c \
  sys/glibc-$(GLIBC_VERSION)/elf/dl-support.c \
  sys/glibc-$(GLIBC_VERSION)/elf/dl-sym.c \
  sys/glibc-$(GLIBC_VERSION)/elf/dl-sysdep.c \
  sys/glibc-$(GLIBC_VERSION)/elf/dl-tls.c \
  sys/glibc-$(GLIBC_VERSION)/elf/dl-tsd.c \
  sys/glibc-$(GLIBC_VERSION)/elf/dl-version.c \
  sys/glibc-$(GLIBC_VERSION)/elf/enbl-secure.c \
  sys/glibc-$(GLIBC_VERSION)/gmon/bb_exit_func.c \
  sys/glibc-$(GLIBC_VERSION)/gmon/bb_init_func.c \
  sys/glibc-$(GLIBC_VERSION)/gmon/gmon.c \
  sys/glibc-$(GLIBC_VERSION)/gmon/mcount.c \
  sys/glibc-$(GLIBC_VERSION)/gmon/prof-freq.c \
  sys/glibc-$(GLIBC_VERSION)/gmon/profil.c \
  sys/glibc-$(GLIBC_VERSION)/gmon/sprofil.c \
  sys/glibc-$(GLIBC_VERSION)/iconv/gconv.c \
  sys/glibc-$(GLIBC_VERSION)/iconv/gconv_builtin.c \
  sys/glibc-$(GLIBC_VERSION)/iconv/gconv_cache.c \
  sys/glibc-$(GLIBC_VERSION)/iconv/gconv_close.c \
  sys/glibc-$(GLIBC_VERSION)/iconv/gconv_conf.c \
  sys/glibc-$(GLIBC_VERSION)/iconv/gconv_db.c \
  sys/glibc-$(GLIBC_VERSION)/iconv/gconv_dl.c \
  sys/glibc-$(GLIBC_VERSION)/iconv/gconv_open.c \
  sys/glibc-$(GLIBC_VERSION)/iconv/gconv_simple.c \
  sys/glibc-$(GLIBC_VERSION)/iconv/gconv_trans.c \
  sys/glibc-$(GLIBC_VERSION)/iconv/iconv.c \
  sys/glibc-$(GLIBC_VERSION)/iconv/iconv_close.c \
  sys/glibc-$(GLIBC_VERSION)/iconv/iconv_open.c \
  sys/glibc-$(GLIBC_VERSION)/intl/bindtextdom.c \
  sys/glibc-$(GLIBC_VERSION)/intl/dcgettext.c \
  sys/glibc-$(GLIBC_VERSION)/intl/dcigettext.c \
  sys/glibc-$(GLIBC_VERSION)/intl/dcngettext.c \
  sys/glibc-$(GLIBC_VERSION)/intl/dgettext.c \
  sys/glibc-$(GLIBC_VERSION)/intl/dngettext.c \
  sys/glibc-$(GLIBC_VERSION)/intl/explodename.c \
  sys/glibc-$(GLIBC_VERSION)/intl/finddomain.c \
  sys/glibc-$(GLIBC_VERSION)/intl/gettext.c \
  sys/glibc-$(GLIBC_VERSION)/intl/hash-string.c \
  sys/glibc-$(GLIBC_VERSION)/intl/loadmsgcat.c \
  sys/glibc-$(GLIBC_VERSION)/intl/localealias.c \
  sys/glibc-$(GLIBC_VERSION)/intl/ngettext.c \
  sys/glibc-$(GLIBC_VERSION)/intl/plural-exp.c \
  sys/glibc-$(GLIBC_VERSION)/intl/plural.c \
  sys/glibc-$(GLIBC_VERSION)/intl/textdomain.c \
  sys/glibc-$(GLIBC_VERSION)/io/fcntl.c \
  sys/glibc-$(GLIBC_VERSION)/io/fxstat.c \
  sys/glibc-$(GLIBC_VERSION)/io/fxstat64.c \
  sys/glibc-$(GLIBC_VERSION)/io/fxstatat.c \
  sys/glibc-$(GLIBC_VERSION)/io/fxstatat64.c \
  sys/glibc-$(GLIBC_VERSION)/io/have_o_cloexec.c \
  sys/glibc-$(GLIBC_VERSION)/io/open64.c \
  sys/glibc-$(GLIBC_VERSION)/io/pipe.c \
  sys/glibc-$(GLIBC_VERSION)/io/readlink.c \
  sys/glibc-$(GLIBC_VERSION)/io/ttyname_r.c \
  sys/glibc-$(GLIBC_VERSION)/io/umask.c \
  sys/glibc-$(GLIBC_VERSION)/libio/__fbufsize.c \
  sys/glibc-$(GLIBC_VERSION)/libio/__flbf.c \
  sys/glibc-$(GLIBC_VERSION)/libio/__fpending.c \
  sys/glibc-$(GLIBC_VERSION)/libio/__fpurge.c \
  sys/glibc-$(GLIBC_VERSION)/libio/__freadable.c \
  sys/glibc-$(GLIBC_VERSION)/libio/__freading.c \
  sys/glibc-$(GLIBC_VERSION)/libio/__fsetlocking.c \
  sys/glibc-$(GLIBC_VERSION)/libio/__fwritable.c \
  sys/glibc-$(GLIBC_VERSION)/libio/__fwriting.c \
  sys/glibc-$(GLIBC_VERSION)/libio/clearerr.c \
  sys/glibc-$(GLIBC_VERSION)/libio/clearerr_u.c \
  sys/glibc-$(GLIBC_VERSION)/libio/fcloseall.c \
  sys/glibc-$(GLIBC_VERSION)/libio/feof.c \
  sys/glibc-$(GLIBC_VERSION)/libio/feof_u.c \
  sys/glibc-$(GLIBC_VERSION)/libio/ferror.c \
  sys/glibc-$(GLIBC_VERSION)/libio/ferror_u.c \
  sys/glibc-$(GLIBC_VERSION)/libio/filedoalloc.c \
  sys/glibc-$(GLIBC_VERSION)/libio/fileno.c \
  sys/glibc-$(GLIBC_VERSION)/libio/fileops.c \
  sys/glibc-$(GLIBC_VERSION)/libio/fmemopen.c \
  sys/glibc-$(GLIBC_VERSION)/libio/fputc.c \
  sys/glibc-$(GLIBC_VERSION)/libio/fputc_u.c \
  sys/glibc-$(GLIBC_VERSION)/libio/fputwc.c \
  sys/glibc-$(GLIBC_VERSION)/libio/fputwc_u.c \
  sys/glibc-$(GLIBC_VERSION)/libio/freopen.c \
  sys/glibc-$(GLIBC_VERSION)/libio/freopen64.c \
  sys/glibc-$(GLIBC_VERSION)/libio/fseek.c \
  sys/glibc-$(GLIBC_VERSION)/libio/fseeko.c \
  sys/glibc-$(GLIBC_VERSION)/libio/fseeko64.c \
  sys/glibc-$(GLIBC_VERSION)/libio/ftello.c \
  sys/glibc-$(GLIBC_VERSION)/libio/ftello64.c \
  sys/glibc-$(GLIBC_VERSION)/libio/fwide.c \
  sys/glibc-$(GLIBC_VERSION)/libio/fwprintf.c \
  sys/glibc-$(GLIBC_VERSION)/libio/fwscanf.c \
  sys/glibc-$(GLIBC_VERSION)/libio/genops.c \
  sys/glibc-$(GLIBC_VERSION)/libio/getc.c \
  sys/glibc-$(GLIBC_VERSION)/libio/getc_u.c \
  sys/glibc-$(GLIBC_VERSION)/libio/getchar.c \
  sys/glibc-$(GLIBC_VERSION)/libio/getchar_u.c \
  sys/glibc-$(GLIBC_VERSION)/libio/getwc.c \
  sys/glibc-$(GLIBC_VERSION)/libio/getwc_u.c \
  sys/glibc-$(GLIBC_VERSION)/libio/getwchar.c \
  sys/glibc-$(GLIBC_VERSION)/libio/getwchar_u.c \
  sys/glibc-$(GLIBC_VERSION)/libio/iofclose.c \
  sys/glibc-$(GLIBC_VERSION)/libio/iofdopen.c \
  sys/glibc-$(GLIBC_VERSION)/libio/iofflush.c \
  sys/glibc-$(GLIBC_VERSION)/libio/iofflush_u.c \
  sys/glibc-$(GLIBC_VERSION)/libio/iofgetpos.c \
  sys/glibc-$(GLIBC_VERSION)/libio/iofgetpos64.c \
  sys/glibc-$(GLIBC_VERSION)/libio/iofgets.c \
  sys/glibc-$(GLIBC_VERSION)/libio/iofgets_u.c \
  sys/glibc-$(GLIBC_VERSION)/libio/iofgetws.c \
  sys/glibc-$(GLIBC_VERSION)/libio/iofgetws_u.c \
  sys/glibc-$(GLIBC_VERSION)/libio/iofopen.c \
  sys/glibc-$(GLIBC_VERSION)/libio/iofopen64.c \
  sys/glibc-$(GLIBC_VERSION)/libio/iofopncook.c \
  sys/glibc-$(GLIBC_VERSION)/libio/iofputs.c \
  sys/glibc-$(GLIBC_VERSION)/libio/iofputs_u.c \
  sys/glibc-$(GLIBC_VERSION)/libio/iofputws.c \
  sys/glibc-$(GLIBC_VERSION)/libio/iofputws_u.c \
  sys/glibc-$(GLIBC_VERSION)/libio/iofread.c \
  sys/glibc-$(GLIBC_VERSION)/libio/iofread_u.c \
  sys/glibc-$(GLIBC_VERSION)/libio/iofsetpos.c \
  sys/glibc-$(GLIBC_VERSION)/libio/iofsetpos64.c \
  sys/glibc-$(GLIBC_VERSION)/libio/ioftell.c \
  sys/glibc-$(GLIBC_VERSION)/libio/iofwide.c \
  sys/glibc-$(GLIBC_VERSION)/libio/iofwrite.c \
  sys/glibc-$(GLIBC_VERSION)/libio/iofwrite_u.c \
  sys/glibc-$(GLIBC_VERSION)/libio/iogetdelim.c \
  sys/glibc-$(GLIBC_VERSION)/libio/iogetline.c \
  sys/glibc-$(GLIBC_VERSION)/libio/iogets.c \
  sys/glibc-$(GLIBC_VERSION)/libio/iogetwline.c \
  sys/glibc-$(GLIBC_VERSION)/libio/iopadn.c \
  sys/glibc-$(GLIBC_VERSION)/libio/iopopen.c \
  sys/glibc-$(GLIBC_VERSION)/libio/ioputs.c \
  sys/glibc-$(GLIBC_VERSION)/libio/ioseekoff.c \
  sys/glibc-$(GLIBC_VERSION)/libio/ioseekpos.c \
  sys/glibc-$(GLIBC_VERSION)/libio/iosetbuffer.c \
  sys/glibc-$(GLIBC_VERSION)/libio/iosetvbuf.c \
  sys/glibc-$(GLIBC_VERSION)/libio/ioungetc.c \
  sys/glibc-$(GLIBC_VERSION)/libio/ioungetwc.c \
  sys/glibc-$(GLIBC_VERSION)/libio/iovdprintf.c \
  sys/glibc-$(GLIBC_VERSION)/libio/iovsprintf.c \
  sys/glibc-$(GLIBC_VERSION)/libio/iovsscanf.c \
  sys/glibc-$(GLIBC_VERSION)/libio/iovswscanf.c \
  sys/glibc-$(GLIBC_VERSION)/libio/iowpadn.c \
  sys/glibc-$(GLIBC_VERSION)/libio/memstream.c \
  sys/glibc-$(GLIBC_VERSION)/libio/obprintf.c \
  sys/glibc-$(GLIBC_VERSION)/libio/pclose.c \
  sys/glibc-$(GLIBC_VERSION)/libio/peekc.c \
  sys/glibc-$(GLIBC_VERSION)/libio/putc.c \
  sys/glibc-$(GLIBC_VERSION)/libio/putc_u.c \
  sys/glibc-$(GLIBC_VERSION)/libio/putchar.c \
  sys/glibc-$(GLIBC_VERSION)/libio/putchar_u.c \
  sys/glibc-$(GLIBC_VERSION)/libio/putwc.c \
  sys/glibc-$(GLIBC_VERSION)/libio/putwc_u.c \
  sys/glibc-$(GLIBC_VERSION)/libio/putwchar.c \
  sys/glibc-$(GLIBC_VERSION)/libio/putwchar_u.c \
  sys/glibc-$(GLIBC_VERSION)/libio/rewind.c \
  sys/glibc-$(GLIBC_VERSION)/libio/setbuf.c \
  sys/glibc-$(GLIBC_VERSION)/libio/setlinebuf.c \
  sys/glibc-$(GLIBC_VERSION)/libio/stdfiles.c \
  sys/glibc-$(GLIBC_VERSION)/libio/stdio.c \
  sys/glibc-$(GLIBC_VERSION)/libio/strops.c \
  sys/glibc-$(GLIBC_VERSION)/libio/swprintf.c \
  sys/glibc-$(GLIBC_VERSION)/libio/swscanf.c \
  sys/glibc-$(GLIBC_VERSION)/libio/vasprintf.c \
  sys/glibc-$(GLIBC_VERSION)/libio/vscanf.c \
  sys/glibc-$(GLIBC_VERSION)/libio/vsnprintf.c \
  sys/glibc-$(GLIBC_VERSION)/libio/vswprintf.c \
  sys/glibc-$(GLIBC_VERSION)/libio/vwprintf.c \
  sys/glibc-$(GLIBC_VERSION)/libio/vwscanf.c \
  sys/glibc-$(GLIBC_VERSION)/libio/wfiledoalloc.c \
  sys/glibc-$(GLIBC_VERSION)/libio/wfileops.c \
  sys/glibc-$(GLIBC_VERSION)/libio/wgenops.c \
  sys/glibc-$(GLIBC_VERSION)/libio/wmemstream.c \
  sys/glibc-$(GLIBC_VERSION)/libio/wprintf.c \
  sys/glibc-$(GLIBC_VERSION)/libio/wscanf.c \
  sys/glibc-$(GLIBC_VERSION)/libio/wstrops.c \
  sys/glibc-$(GLIBC_VERSION)/locale/C-address.c \
  sys/glibc-$(GLIBC_VERSION)/locale/C-collate.c \
  sys/glibc-$(GLIBC_VERSION)/locale/C-ctype.c \
  sys/glibc-$(GLIBC_VERSION)/locale/C-identification.c \
  sys/glibc-$(GLIBC_VERSION)/locale/C-measurement.c \
  sys/glibc-$(GLIBC_VERSION)/locale/C-messages.c \
  sys/glibc-$(GLIBC_VERSION)/locale/C-monetary.c \
  sys/glibc-$(GLIBC_VERSION)/locale/C-name.c \
  sys/glibc-$(GLIBC_VERSION)/locale/C-numeric.c \
  sys/glibc-$(GLIBC_VERSION)/locale/C-paper.c \
  sys/glibc-$(GLIBC_VERSION)/locale/C-telephone.c \
  sys/glibc-$(GLIBC_VERSION)/locale/C-time.c \
  sys/glibc-$(GLIBC_VERSION)/locale/C_name.c \
  sys/glibc-$(GLIBC_VERSION)/locale/SYS_libc.c \
  sys/glibc-$(GLIBC_VERSION)/locale/coll-lookup.c \
  sys/glibc-$(GLIBC_VERSION)/locale/duplocale.c \
  sys/glibc-$(GLIBC_VERSION)/locale/findlocale.c \
  sys/glibc-$(GLIBC_VERSION)/locale/freelocale.c \
  sys/glibc-$(GLIBC_VERSION)/locale/global-locale.c \
  sys/glibc-$(GLIBC_VERSION)/locale/lc-address.c \
  sys/glibc-$(GLIBC_VERSION)/locale/lc-collate.c \
  sys/glibc-$(GLIBC_VERSION)/locale/lc-ctype.c \
  sys/glibc-$(GLIBC_VERSION)/locale/lc-identification.c \
  sys/glibc-$(GLIBC_VERSION)/locale/lc-measurement.c \
  sys/glibc-$(GLIBC_VERSION)/locale/lc-messages.c \
  sys/glibc-$(GLIBC_VERSION)/locale/lc-monetary.c \
  sys/glibc-$(GLIBC_VERSION)/locale/lc-name.c \
  sys/glibc-$(GLIBC_VERSION)/locale/lc-numeric.c \
  sys/glibc-$(GLIBC_VERSION)/locale/lc-paper.c \
  sys/glibc-$(GLIBC_VERSION)/locale/lc-telephone.c \
  sys/glibc-$(GLIBC_VERSION)/locale/lc-time.c \
  sys/glibc-$(GLIBC_VERSION)/locale/loadarchive.c \
  sys/glibc-$(GLIBC_VERSION)/locale/loadlocale.c \
  sys/glibc-$(GLIBC_VERSION)/locale/localeconv.c \
  sys/glibc-$(GLIBC_VERSION)/locale/localename.c \
  sys/glibc-$(GLIBC_VERSION)/locale/mb_cur_max.c \
  sys/glibc-$(GLIBC_VERSION)/locale/newlocale.c \
  sys/glibc-$(GLIBC_VERSION)/locale/nl_langinfo.c \
  sys/glibc-$(GLIBC_VERSION)/locale/nl_langinfo_l.c \
  sys/glibc-$(GLIBC_VERSION)/locale/setlocale.c \
  sys/glibc-$(GLIBC_VERSION)/locale/uselocale.c \
  sys/glibc-$(GLIBC_VERSION)/locale/xlocale.c \
  sys/glibc-$(GLIBC_VERSION)/malloc/malloc.c \
  sys/glibc-$(GLIBC_VERSION)/malloc/mcheck.c \
  sys/glibc-$(GLIBC_VERSION)/malloc/morecore.c \
  sys/glibc-$(GLIBC_VERSION)/malloc/mtrace.c \
  sys/glibc-$(GLIBC_VERSION)/malloc/obstack.c \
  sys/glibc-$(GLIBC_VERSION)/malloc/set-freeres.c \
  sys/glibc-$(GLIBC_VERSION)/malloc/thread-freeres.c \
  sys/glibc-$(GLIBC_VERSION)/math/cabs.c \
  sys/glibc-$(GLIBC_VERSION)/math/cabsf.c \
  sys/glibc-$(GLIBC_VERSION)/math/cabsl.c \
  sys/glibc-$(GLIBC_VERSION)/math/carg.c \
  sys/glibc-$(GLIBC_VERSION)/math/cargf.c \
  sys/glibc-$(GLIBC_VERSION)/math/cargl.c \
  sys/glibc-$(GLIBC_VERSION)/math/cimag.c \
  sys/glibc-$(GLIBC_VERSION)/math/cimagf.c \
  sys/glibc-$(GLIBC_VERSION)/math/cimagl.c \
  sys/glibc-$(GLIBC_VERSION)/math/conj.c \
  sys/glibc-$(GLIBC_VERSION)/math/conjf.c \
  sys/glibc-$(GLIBC_VERSION)/math/conjl.c \
  sys/glibc-$(GLIBC_VERSION)/math/creal.c \
  sys/glibc-$(GLIBC_VERSION)/math/crealf.c \
  sys/glibc-$(GLIBC_VERSION)/math/creall.c \
  sys/glibc-$(GLIBC_VERSION)/math/e_exp10f.c \
  sys/glibc-$(GLIBC_VERSION)/math/e_scalb.c \
  sys/glibc-$(GLIBC_VERSION)/math/e_scalbf.c \
  sys/glibc-$(GLIBC_VERSION)/math/fpu_control.c \
  sys/glibc-$(GLIBC_VERSION)/math/ieee-math.c \
  sys/glibc-$(GLIBC_VERSION)/math/k_sincosl.c \
  sys/glibc-$(GLIBC_VERSION)/math/s_cacos.c \
  sys/glibc-$(GLIBC_VERSION)/math/s_cacosf.c \
  sys/glibc-$(GLIBC_VERSION)/math/s_cacosl.c \
  sys/glibc-$(GLIBC_VERSION)/math/s_cacosh.c \
  sys/glibc-$(GLIBC_VERSION)/math/s_cacoshf.c \
  sys/glibc-$(GLIBC_VERSION)/math/s_cacoshl.c \
  sys/glibc-$(GLIBC_VERSION)/math/s_casin.c \
  sys/glibc-$(GLIBC_VERSION)/math/s_casinf.c \
  sys/glibc-$(GLIBC_VERSION)/math/s_casinh.c \
  sys/glibc-$(GLIBC_VERSION)/math/s_casinhf.c \
  sys/glibc-$(GLIBC_VERSION)/math/s_casinhl.c \
  sys/glibc-$(GLIBC_VERSION)/math/s_casinl.c \
  sys/glibc-$(GLIBC_VERSION)/math/s_catan.c \
  sys/glibc-$(GLIBC_VERSION)/math/s_catanf.c \
  sys/glibc-$(GLIBC_VERSION)/math/s_catanl.c \
  sys/glibc-$(GLIBC_VERSION)/math/s_catanh.c \
  sys/glibc-$(GLIBC_VERSION)/math/s_catanhf.c \
  sys/glibc-$(GLIBC_VERSION)/math/s_catanhl.c \
  sys/glibc-$(GLIBC_VERSION)/math/s_ccos.c \
  sys/glibc-$(GLIBC_VERSION)/math/s_ccosf.c \
  sys/glibc-$(GLIBC_VERSION)/math/s_ccosh.c \
  sys/glibc-$(GLIBC_VERSION)/math/s_ccoshf.c \
  sys/glibc-$(GLIBC_VERSION)/math/s_ccoshl.c \
  sys/glibc-$(GLIBC_VERSION)/math/s_ccosl.c \
  sys/glibc-$(GLIBC_VERSION)/math/s_cexp.c \
  sys/glibc-$(GLIBC_VERSION)/math/s_cexpf.c \
  sys/glibc-$(GLIBC_VERSION)/math/s_cexpl.c \
  sys/glibc-$(GLIBC_VERSION)/math/s_clog.c \
  sys/glibc-$(GLIBC_VERSION)/math/s_clog10.c \
  sys/glibc-$(GLIBC_VERSION)/math/s_clog10f.c \
  sys/glibc-$(GLIBC_VERSION)/math/s_clog10l.c \
  sys/glibc-$(GLIBC_VERSION)/math/s_clogf.c \
  sys/glibc-$(GLIBC_VERSION)/math/s_clogl.c \
  sys/glibc-$(GLIBC_VERSION)/math/s_cpow.c \
  sys/glibc-$(GLIBC_VERSION)/math/s_cpowf.c \
  sys/glibc-$(GLIBC_VERSION)/math/s_cpowl.c \
  sys/glibc-$(GLIBC_VERSION)/math/s_cproj.c \
  sys/glibc-$(GLIBC_VERSION)/math/s_cprojf.c \
  sys/glibc-$(GLIBC_VERSION)/math/s_cprojl.c \
  sys/glibc-$(GLIBC_VERSION)/math/s_csin.c \
  sys/glibc-$(GLIBC_VERSION)/math/s_csinf.c \
  sys/glibc-$(GLIBC_VERSION)/math/s_csinh.c \
  sys/glibc-$(GLIBC_VERSION)/math/s_csinhf.c \
  sys/glibc-$(GLIBC_VERSION)/math/s_csinhl.c \
  sys/glibc-$(GLIBC_VERSION)/math/s_csinl.c \
  sys/glibc-$(GLIBC_VERSION)/math/s_csqrt.c \
  sys/glibc-$(GLIBC_VERSION)/math/s_csqrtf.c \
  sys/glibc-$(GLIBC_VERSION)/math/s_csqrtl.c \
  sys/glibc-$(GLIBC_VERSION)/math/s_ctan.c \
  sys/glibc-$(GLIBC_VERSION)/math/s_ctanf.c \
  sys/glibc-$(GLIBC_VERSION)/math/s_ctanh.c \
  sys/glibc-$(GLIBC_VERSION)/math/s_ctanhf.c \
  sys/glibc-$(GLIBC_VERSION)/math/s_ctanhl.c \
  sys/glibc-$(GLIBC_VERSION)/math/s_ctanl.c \
  sys/glibc-$(GLIBC_VERSION)/math/s_fdim.c \
  sys/glibc-$(GLIBC_VERSION)/math/s_fdimf.c \
  sys/glibc-$(GLIBC_VERSION)/math/s_ldexp.c \
  sys/glibc-$(GLIBC_VERSION)/math/s_ldexpf.c \
  sys/glibc-$(GLIBC_VERSION)/math/s_ldexpl.c \
  sys/glibc-$(GLIBC_VERSION)/math/s_nan.c \
  sys/glibc-$(GLIBC_VERSION)/math/s_nanf.c \
  sys/glibc-$(GLIBC_VERSION)/math/s_nanl.c \
  sys/glibc-$(GLIBC_VERSION)/math/s_nextafter.c \
  sys/glibc-$(GLIBC_VERSION)/math/s_nexttowardl.c \
  sys/glibc-$(GLIBC_VERSION)/math/s_significand.c \
  sys/glibc-$(GLIBC_VERSION)/math/s_significandf.c \
  sys/glibc-$(GLIBC_VERSION)/math/setfpucw.c \
  sys/glibc-$(GLIBC_VERSION)/math/w_acos.c \
  sys/glibc-$(GLIBC_VERSION)/math/w_acosf.c \
  sys/glibc-$(GLIBC_VERSION)/math/w_acosh.c \
  sys/glibc-$(GLIBC_VERSION)/math/w_acoshf.c \
  sys/glibc-$(GLIBC_VERSION)/math/w_acoshl.c \
  sys/glibc-$(GLIBC_VERSION)/math/w_acosl.c \
  sys/glibc-$(GLIBC_VERSION)/math/w_asin.c \
  sys/glibc-$(GLIBC_VERSION)/math/w_asinf.c \
  sys/glibc-$(GLIBC_VERSION)/math/w_asinl.c \
  sys/glibc-$(GLIBC_VERSION)/math/w_atan2.c \
  sys/glibc-$(GLIBC_VERSION)/math/w_atan2f.c \
  sys/glibc-$(GLIBC_VERSION)/math/w_atan2l.c \
  sys/glibc-$(GLIBC_VERSION)/math/w_atanh.c \
  sys/glibc-$(GLIBC_VERSION)/math/w_atanhf.c \
  sys/glibc-$(GLIBC_VERSION)/math/w_atanhl.c \
  sys/glibc-$(GLIBC_VERSION)/math/w_cosh.c \
  sys/glibc-$(GLIBC_VERSION)/math/w_coshf.c \
  sys/glibc-$(GLIBC_VERSION)/math/w_coshl.c \
  sys/glibc-$(GLIBC_VERSION)/math/w_drem.c \
  sys/glibc-$(GLIBC_VERSION)/math/w_dremf.c \
  sys/glibc-$(GLIBC_VERSION)/math/w_dreml.c \
  sys/glibc-$(GLIBC_VERSION)/math/w_exp10.c \
  sys/glibc-$(GLIBC_VERSION)/math/w_exp10f.c \
  sys/glibc-$(GLIBC_VERSION)/math/w_exp10l.c \
  sys/glibc-$(GLIBC_VERSION)/math/w_exp2.c \
  sys/glibc-$(GLIBC_VERSION)/math/w_exp2f.c \
  sys/glibc-$(GLIBC_VERSION)/math/w_exp2l.c \
  sys/glibc-$(GLIBC_VERSION)/math/w_fmod.c \
  sys/glibc-$(GLIBC_VERSION)/math/w_fmodf.c \
  sys/glibc-$(GLIBC_VERSION)/math/w_fmodl.c \
  sys/glibc-$(GLIBC_VERSION)/math/w_hypot.c \
  sys/glibc-$(GLIBC_VERSION)/math/w_hypotf.c \
  sys/glibc-$(GLIBC_VERSION)/math/w_hypotl.c \
  sys/glibc-$(GLIBC_VERSION)/math/w_ilogb.c \
  sys/glibc-$(GLIBC_VERSION)/math/w_ilogbf.c \
  sys/glibc-$(GLIBC_VERSION)/math/w_ilogbl.c \
  sys/glibc-$(GLIBC_VERSION)/math/w_j0.c \
  sys/glibc-$(GLIBC_VERSION)/math/w_j0f.c \
  sys/glibc-$(GLIBC_VERSION)/math/w_j0l.c \
  sys/glibc-$(GLIBC_VERSION)/math/w_j1.c \
  sys/glibc-$(GLIBC_VERSION)/math/w_j1f.c \
  sys/glibc-$(GLIBC_VERSION)/math/w_j1l.c \
  sys/glibc-$(GLIBC_VERSION)/math/w_jn.c \
  sys/glibc-$(GLIBC_VERSION)/math/w_jnf.c \
  sys/glibc-$(GLIBC_VERSION)/math/w_jnl.c \
  sys/glibc-$(GLIBC_VERSION)/math/w_lgamma.c \
  sys/glibc-$(GLIBC_VERSION)/math/w_lgamma_r.c \
  sys/glibc-$(GLIBC_VERSION)/math/w_lgammaf.c \
  sys/glibc-$(GLIBC_VERSION)/math/w_lgammaf_r.c \
  sys/glibc-$(GLIBC_VERSION)/math/w_lgammal.c \
  sys/glibc-$(GLIBC_VERSION)/math/w_lgammal_r.c \
  sys/glibc-$(GLIBC_VERSION)/math/w_log.c \
  sys/glibc-$(GLIBC_VERSION)/math/w_log2.c \
  sys/glibc-$(GLIBC_VERSION)/math/w_log2f.c \
  sys/glibc-$(GLIBC_VERSION)/math/w_log2l.c \
  sys/glibc-$(GLIBC_VERSION)/math/w_log10.c \
  sys/glibc-$(GLIBC_VERSION)/math/w_log10f.c \
  sys/glibc-$(GLIBC_VERSION)/math/w_logf.c \
  sys/glibc-$(GLIBC_VERSION)/math/w_logl.c \
  sys/glibc-$(GLIBC_VERSION)/math/w_pow.c \
  sys/glibc-$(GLIBC_VERSION)/math/w_powf.c \
  sys/glibc-$(GLIBC_VERSION)/math/w_powl.c \
  sys/glibc-$(GLIBC_VERSION)/math/w_remainder.c \
  sys/glibc-$(GLIBC_VERSION)/math/w_remainderf.c \
  sys/glibc-$(GLIBC_VERSION)/math/w_remainderl.c \
  sys/glibc-$(GLIBC_VERSION)/math/w_scalb.c \
  sys/glibc-$(GLIBC_VERSION)/math/w_scalbf.c \
  sys/glibc-$(GLIBC_VERSION)/math/w_scalbl.c \
  sys/glibc-$(GLIBC_VERSION)/math/w_sinh.c \
  sys/glibc-$(GLIBC_VERSION)/math/w_sinhf.c \
  sys/glibc-$(GLIBC_VERSION)/math/w_sinhl.c \
  sys/glibc-$(GLIBC_VERSION)/math/w_sqrt.c \
  sys/glibc-$(GLIBC_VERSION)/math/w_sqrtf.c \
  sys/glibc-$(GLIBC_VERSION)/math/w_sqrtl.c \
  sys/glibc-$(GLIBC_VERSION)/math/w_tgamma.c \
  sys/glibc-$(GLIBC_VERSION)/math/w_tgammaf.c \
  sys/glibc-$(GLIBC_VERSION)/math/w_tgammal.c \
  sys/glibc-$(GLIBC_VERSION)/misc/init-misc.c \
  sys/glibc-$(GLIBC_VERSION)/misc/mkstemp.c \
  sys/glibc-$(GLIBC_VERSION)/misc/mmap.c \
  sys/glibc-$(GLIBC_VERSION)/misc/mmap64.c \
  sys/glibc-$(GLIBC_VERSION)/misc/mprotect.c \
  sys/glibc-$(GLIBC_VERSION)/misc/munmap.c \
  sys/glibc-$(GLIBC_VERSION)/misc/sbrk.c \
  sys/glibc-$(GLIBC_VERSION)/misc/tsearch.c \
  sys/glibc-$(GLIBC_VERSION)/nptl/sysdeps/llamaos/flockfile.c \
  sys/glibc-$(GLIBC_VERSION)/nptl/sysdeps/llamaos/funlockfile.c \
  sys/glibc-$(GLIBC_VERSION)/nptl/sysdeps/llamaos/jmp-unwind.c \
  sys/glibc-$(GLIBC_VERSION)/nptl/sysdeps/llamaos/pthread.c \
  sys/glibc-$(GLIBC_VERSION)/nptl/sysdeps/pthread/flockfile.c \
  sys/glibc-$(GLIBC_VERSION)/nptl/sysdeps/pthread/ftrylockfile.c \
  sys/glibc-$(GLIBC_VERSION)/nptl/sysdeps/pthread/funlockfile.c \
  sys/glibc-$(GLIBC_VERSION)/nptl/alloca_cutoff.c \
  sys/glibc-$(GLIBC_VERSION)/posix/environ.c \
  sys/glibc-$(GLIBC_VERSION)/posix/execve.c \
  sys/glibc-$(GLIBC_VERSION)/posix/fork.c \
  sys/glibc-$(GLIBC_VERSION)/posix/fpathconf.c \
  sys/glibc-$(GLIBC_VERSION)/posix/getegid.c \
  sys/glibc-$(GLIBC_VERSION)/posix/geteuid.c \
  sys/glibc-$(GLIBC_VERSION)/posix/getgid.c \
  sys/glibc-$(GLIBC_VERSION)/posix/getopt.c \
  sys/glibc-$(GLIBC_VERSION)/posix/getuid.c \
  sys/glibc-$(GLIBC_VERSION)/posix/regex.c \
  sys/glibc-$(GLIBC_VERSION)/posix/wait.c \
  sys/glibc-$(GLIBC_VERSION)/setjmp/longjmp.c \
  sys/glibc-$(GLIBC_VERSION)/setjmp/sigjmp.c \
  sys/glibc-$(GLIBC_VERSION)/signal/sigaction.c \
  sys/glibc-$(GLIBC_VERSION)/signal/sigaddset.c \
  sys/glibc-$(GLIBC_VERSION)/signal/signal.c \
  sys/glibc-$(GLIBC_VERSION)/signal/sigprocmask.c \
  sys/glibc-$(GLIBC_VERSION)/stdio-common/_itoa.c \
  sys/glibc-$(GLIBC_VERSION)/stdio-common/_itowa.c \
  sys/glibc-$(GLIBC_VERSION)/stdio-common/asprintf.c \
  sys/glibc-$(GLIBC_VERSION)/stdio-common/dprintf.c \
  sys/glibc-$(GLIBC_VERSION)/stdio-common/fprintf.c \
  sys/glibc-$(GLIBC_VERSION)/stdio-common/fscanf.c \
  sys/glibc-$(GLIBC_VERSION)/stdio-common/fxprintf.c \
  sys/glibc-$(GLIBC_VERSION)/stdio-common/getline.c \
  sys/glibc-$(GLIBC_VERSION)/stdio-common/getw.c \
  sys/glibc-$(GLIBC_VERSION)/stdio-common/isoc99_fscanf.c \
  sys/glibc-$(GLIBC_VERSION)/stdio-common/isoc99_scanf.c \
  sys/glibc-$(GLIBC_VERSION)/stdio-common/isoc99_sscanf.c \
  sys/glibc-$(GLIBC_VERSION)/stdio-common/isoc99_vfscanf.c \
  sys/glibc-$(GLIBC_VERSION)/stdio-common/isoc99_vscanf.c \
  sys/glibc-$(GLIBC_VERSION)/stdio-common/isoc99_vsscanf.c \
  sys/glibc-$(GLIBC_VERSION)/stdio-common/itoa-digits.c \
  sys/glibc-$(GLIBC_VERSION)/stdio-common/itoa-udigits.c \
  sys/glibc-$(GLIBC_VERSION)/stdio-common/itowa-digits.c \
  sys/glibc-$(GLIBC_VERSION)/stdio-common/perror.c \
  sys/glibc-$(GLIBC_VERSION)/stdio-common/printf-parsemb.c \
  sys/glibc-$(GLIBC_VERSION)/stdio-common/printf-parsewc.c \
  sys/glibc-$(GLIBC_VERSION)/stdio-common/printf-prs.c \
  sys/glibc-$(GLIBC_VERSION)/stdio-common/printf.c \
  sys/glibc-$(GLIBC_VERSION)/stdio-common/printf_fp.c \
  sys/glibc-$(GLIBC_VERSION)/stdio-common/printf_size.c \
  sys/glibc-$(GLIBC_VERSION)/stdio-common/psiginfo.c \
  sys/glibc-$(GLIBC_VERSION)/stdio-common/psignal.c \
  sys/glibc-$(GLIBC_VERSION)/stdio-common/putw.c \
  sys/glibc-$(GLIBC_VERSION)/stdio-common/reg-modifier.c \
  sys/glibc-$(GLIBC_VERSION)/stdio-common/reg-printf.c \
  sys/glibc-$(GLIBC_VERSION)/stdio-common/reg-type.c \
  sys/glibc-$(GLIBC_VERSION)/stdio-common/remove.c \
  sys/glibc-$(GLIBC_VERSION)/stdio-common/rename.c \
  sys/glibc-$(GLIBC_VERSION)/stdio-common/renameat.c \
  sys/glibc-$(GLIBC_VERSION)/stdio-common/scanf.c \
  sys/glibc-$(GLIBC_VERSION)/stdio-common/snprintf.c \
  sys/glibc-$(GLIBC_VERSION)/stdio-common/sprintf.c \
  sys/glibc-$(GLIBC_VERSION)/stdio-common/sscanf.c \
  sys/glibc-$(GLIBC_VERSION)/stdio-common/tempnam.c \
  sys/glibc-$(GLIBC_VERSION)/stdio-common/tmpfile.c \
  sys/glibc-$(GLIBC_VERSION)/stdio-common/tmpfile64.c \
  sys/glibc-$(GLIBC_VERSION)/stdio-common/tmpnam.c \
  sys/glibc-$(GLIBC_VERSION)/stdio-common/tmpnam_r.c \
  sys/glibc-$(GLIBC_VERSION)/stdio-common/vfprintf.c \
  sys/glibc-$(GLIBC_VERSION)/stdio-common/vfscanf.c \
  sys/glibc-$(GLIBC_VERSION)/stdio-common/vfwprintf.c \
  sys/glibc-$(GLIBC_VERSION)/stdio-common/vfwscanf.c \
  sys/glibc-$(GLIBC_VERSION)/stdio-common/vprintf.c \
  sys/glibc-$(GLIBC_VERSION)/stdlib/a64l.c \
  sys/glibc-$(GLIBC_VERSION)/stdlib/abs.c \
  sys/glibc-$(GLIBC_VERSION)/stdlib/at_quick_exit.c \
  sys/glibc-$(GLIBC_VERSION)/stdlib/atexit.c \
  sys/glibc-$(GLIBC_VERSION)/stdlib/atof.c \
  sys/glibc-$(GLIBC_VERSION)/stdlib/atoi.c \
  sys/glibc-$(GLIBC_VERSION)/stdlib/atol.c \
  sys/glibc-$(GLIBC_VERSION)/stdlib/atoll.c \
  sys/glibc-$(GLIBC_VERSION)/stdlib/bsearch.c \
  sys/glibc-$(GLIBC_VERSION)/stdlib/canonicalize.c \
  sys/glibc-$(GLIBC_VERSION)/stdlib/cmp.c \
  sys/glibc-$(GLIBC_VERSION)/stdlib/cxa_at_quick_exit.c \
  sys/glibc-$(GLIBC_VERSION)/stdlib/cxa_atexit.c \
  sys/glibc-$(GLIBC_VERSION)/stdlib/cxa_finalize.c \
  sys/glibc-$(GLIBC_VERSION)/stdlib/div.c \
  sys/glibc-$(GLIBC_VERSION)/stdlib/divmod_1.c \
  sys/glibc-$(GLIBC_VERSION)/stdlib/divrem.c \
  sys/glibc-$(GLIBC_VERSION)/stdlib/drand48-iter.c \
  sys/glibc-$(GLIBC_VERSION)/stdlib/drand48.c \
  sys/glibc-$(GLIBC_VERSION)/stdlib/drand48_r.c \
  sys/glibc-$(GLIBC_VERSION)/stdlib/erand48.c \
  sys/glibc-$(GLIBC_VERSION)/stdlib/erand48_r.c \
  sys/glibc-$(GLIBC_VERSION)/stdlib/exit.c \
  sys/glibc-$(GLIBC_VERSION)/stdlib/fmtmsg.c \
  sys/glibc-$(GLIBC_VERSION)/stdlib/fpioconst.c \
  sys/glibc-$(GLIBC_VERSION)/stdlib/getcontext.c \
  sys/glibc-$(GLIBC_VERSION)/stdlib/getenv.c \
  sys/glibc-$(GLIBC_VERSION)/stdlib/getsubopt.c \
  sys/glibc-$(GLIBC_VERSION)/stdlib/grouping.c \
  sys/glibc-$(GLIBC_VERSION)/stdlib/groupingwc.c \
  sys/glibc-$(GLIBC_VERSION)/stdlib/inlines.c \
  sys/glibc-$(GLIBC_VERSION)/stdlib/jrand48.c \
  sys/glibc-$(GLIBC_VERSION)/stdlib/jrand48_r.c \
  sys/glibc-$(GLIBC_VERSION)/stdlib/l64a.c \
  sys/glibc-$(GLIBC_VERSION)/stdlib/lcong48.c \
  sys/glibc-$(GLIBC_VERSION)/stdlib/lcong48_r.c \
  sys/glibc-$(GLIBC_VERSION)/stdlib/llabs.c \
  sys/glibc-$(GLIBC_VERSION)/stdlib/lldiv.c \
  sys/glibc-$(GLIBC_VERSION)/stdlib/lrand48.c \
  sys/glibc-$(GLIBC_VERSION)/stdlib/lrand48_r.c \
  sys/glibc-$(GLIBC_VERSION)/stdlib/makecontext.c \
  sys/glibc-$(GLIBC_VERSION)/stdlib/mblen.c \
  sys/glibc-$(GLIBC_VERSION)/stdlib/mbstowcs.c \
  sys/glibc-$(GLIBC_VERSION)/stdlib/mbtowc.c \
  sys/glibc-$(GLIBC_VERSION)/stdlib/mod_1.c \
  sys/glibc-$(GLIBC_VERSION)/stdlib/mrand48.c \
  sys/glibc-$(GLIBC_VERSION)/stdlib/mrand48_r.c \
  sys/glibc-$(GLIBC_VERSION)/stdlib/msort.c \
  sys/glibc-$(GLIBC_VERSION)/stdlib/mul.c \
  sys/glibc-$(GLIBC_VERSION)/stdlib/mul_n.c \
  sys/glibc-$(GLIBC_VERSION)/stdlib/nrand48.c \
  sys/glibc-$(GLIBC_VERSION)/stdlib/nrand48_r.c \
  sys/glibc-$(GLIBC_VERSION)/stdlib/old_atexit.c \
  sys/glibc-$(GLIBC_VERSION)/stdlib/on_exit.c \
  sys/glibc-$(GLIBC_VERSION)/stdlib/putenv.c \
  sys/glibc-$(GLIBC_VERSION)/stdlib/qsort.c \
  sys/glibc-$(GLIBC_VERSION)/stdlib/quick_exit.c \
  sys/glibc-$(GLIBC_VERSION)/stdlib/rand.c \
  sys/glibc-$(GLIBC_VERSION)/stdlib/rand_r.c \
  sys/glibc-$(GLIBC_VERSION)/stdlib/random.c \
  sys/glibc-$(GLIBC_VERSION)/stdlib/random_r.c \
  sys/glibc-$(GLIBC_VERSION)/stdlib/rpmatch.c \
  sys/glibc-$(GLIBC_VERSION)/stdlib/secure-getenv.c \
  sys/glibc-$(GLIBC_VERSION)/stdlib/seed48.c \
  sys/glibc-$(GLIBC_VERSION)/stdlib/seed48_r.c \
  sys/glibc-$(GLIBC_VERSION)/stdlib/setcontext.c \
  sys/glibc-$(GLIBC_VERSION)/stdlib/setenv.c \
  sys/glibc-$(GLIBC_VERSION)/stdlib/srand48.c \
  sys/glibc-$(GLIBC_VERSION)/stdlib/srand48_r.c \
  sys/glibc-$(GLIBC_VERSION)/stdlib/strfmon.c \
  sys/glibc-$(GLIBC_VERSION)/stdlib/strfmon_l.c \
  sys/glibc-$(GLIBC_VERSION)/stdlib/strtod.c \
  sys/glibc-$(GLIBC_VERSION)/stdlib/strtod_l.c \
  sys/glibc-$(GLIBC_VERSION)/stdlib/strtof.c \
  sys/glibc-$(GLIBC_VERSION)/stdlib/strtof_l.c \
  sys/glibc-$(GLIBC_VERSION)/stdlib/strtold.c \
  sys/glibc-$(GLIBC_VERSION)/stdlib/swapcontext.c \
  sys/glibc-$(GLIBC_VERSION)/stdlib/tens_in_limb.c \
  sys/glibc-$(GLIBC_VERSION)/stdlib/udiv_qrnnd.c \
  sys/glibc-$(GLIBC_VERSION)/stdlib/wcstombs.c \
  sys/glibc-$(GLIBC_VERSION)/stdlib/wctomb.c \
  sys/glibc-$(GLIBC_VERSION)/stdlib/xpg_basename.c \
  sys/glibc-$(GLIBC_VERSION)/string/_strerror.c \
  sys/glibc-$(GLIBC_VERSION)/string/argz-addsep.c \
  sys/glibc-$(GLIBC_VERSION)/string/argz-append.c \
  sys/glibc-$(GLIBC_VERSION)/string/argz-count.c \
  sys/glibc-$(GLIBC_VERSION)/string/argz-create.c \
  sys/glibc-$(GLIBC_VERSION)/string/argz-ctsep.c \
  sys/glibc-$(GLIBC_VERSION)/string/argz-delete.c \
  sys/glibc-$(GLIBC_VERSION)/string/argz-extract.c \
  sys/glibc-$(GLIBC_VERSION)/string/argz-insert.c \
  sys/glibc-$(GLIBC_VERSION)/string/argz-next.c \
  sys/glibc-$(GLIBC_VERSION)/string/argz-replace.c \
  sys/glibc-$(GLIBC_VERSION)/string/argz-stringify.c \
  sys/glibc-$(GLIBC_VERSION)/string/basename.c \
  sys/glibc-$(GLIBC_VERSION)/string/bcopy.c \
  sys/glibc-$(GLIBC_VERSION)/string/envz.c \
  sys/glibc-$(GLIBC_VERSION)/string/memccpy.c \
  sys/glibc-$(GLIBC_VERSION)/string/memfrob.c \
  sys/glibc-$(GLIBC_VERSION)/string/memmem.c \
  sys/glibc-$(GLIBC_VERSION)/string/stpncpy.c \
  sys/glibc-$(GLIBC_VERSION)/string/strcasecmp.c \
  sys/glibc-$(GLIBC_VERSION)/string/strcasecmp_l.c \
  sys/glibc-$(GLIBC_VERSION)/string/strcasestr.c \
  sys/glibc-$(GLIBC_VERSION)/string/strcoll.c \
  sys/glibc-$(GLIBC_VERSION)/string/strcoll_l.c \
  sys/glibc-$(GLIBC_VERSION)/string/strdup.c \
  sys/glibc-$(GLIBC_VERSION)/string/strerror.c \
  sys/glibc-$(GLIBC_VERSION)/string/strerror_l.c \
  sys/glibc-$(GLIBC_VERSION)/string/strfry.c \
  sys/glibc-$(GLIBC_VERSION)/string/string-inlines.c \
  sys/glibc-$(GLIBC_VERSION)/string/strncase.c \
  sys/glibc-$(GLIBC_VERSION)/string/strncase_l.c \
  sys/glibc-$(GLIBC_VERSION)/string/strncat.c \
  sys/glibc-$(GLIBC_VERSION)/string/strncpy.c \
  sys/glibc-$(GLIBC_VERSION)/string/strndup.c \
  sys/glibc-$(GLIBC_VERSION)/string/strsep.c \
  sys/glibc-$(GLIBC_VERSION)/string/strsignal.c \
  sys/glibc-$(GLIBC_VERSION)/string/strstr.c \
  sys/glibc-$(GLIBC_VERSION)/string/strverscmp.c \
  sys/glibc-$(GLIBC_VERSION)/string/strxfrm.c \
  sys/glibc-$(GLIBC_VERSION)/string/strxfrm_l.c \
  sys/glibc-$(GLIBC_VERSION)/string/swab.c \
  sys/glibc-$(GLIBC_VERSION)/string/wordcopy.c \
  sys/glibc-$(GLIBC_VERSION)/string/xpg-strerror.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/gnu/errlist.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/gnu/siglist.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/ieee754/dbl-64/wordsize-64/e_acosh.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/ieee754/dbl-64/wordsize-64/e_cosh.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/ieee754/dbl-64/wordsize-64/e_fmod.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/ieee754/dbl-64/wordsize-64/e_log2.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/ieee754/dbl-64/wordsize-64/e_log10.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/ieee754/dbl-64/wordsize-64/s_ceil.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/ieee754/dbl-64/wordsize-64/s_finite.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/ieee754/dbl-64/wordsize-64/s_floor.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/ieee754/dbl-64/wordsize-64/s_frexp.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/ieee754/dbl-64/wordsize-64/s_isinf.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/ieee754/dbl-64/wordsize-64/s_isinf_ns.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/ieee754/dbl-64/wordsize-64/s_isnan.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/ieee754/dbl-64/wordsize-64/s_llround.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/ieee754/dbl-64/wordsize-64/s_logb.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/ieee754/dbl-64/wordsize-64/s_lround.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/ieee754/dbl-64/wordsize-64/s_modf.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/ieee754/dbl-64/wordsize-64/s_nearbyint.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/ieee754/dbl-64/wordsize-64/s_remquo.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/ieee754/dbl-64/wordsize-64/s_rint.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/ieee754/dbl-64/wordsize-64/s_round.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/ieee754/dbl-64/wordsize-64/s_scalbln.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/ieee754/dbl-64/wordsize-64/s_scalbn.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/ieee754/dbl-64/wordsize-64/s_trunc.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/ieee754/dbl-64/branred.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/ieee754/dbl-64/doasin.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/ieee754/dbl-64/dosincos.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/ieee754/dbl-64/e_acos.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/ieee754/dbl-64/e_asin.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/ieee754/dbl-64/e_atan2.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/ieee754/dbl-64/e_atanh.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/ieee754/dbl-64/e_exp.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/ieee754/dbl-64/e_exp2.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/ieee754/dbl-64/e_exp10.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/ieee754/dbl-64/e_gamma_r.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/ieee754/dbl-64/e_hypot.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/ieee754/dbl-64/e_ilogb.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/ieee754/dbl-64/e_j0.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/ieee754/dbl-64/e_j1.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/ieee754/dbl-64/e_jn.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/ieee754/dbl-64/e_lgamma_r.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/ieee754/dbl-64/e_log.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/ieee754/dbl-64/e_pow.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/ieee754/dbl-64/e_rem_pio2.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/ieee754/dbl-64/e_remainder.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/ieee754/dbl-64/e_sinh.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/ieee754/dbl-64/halfulp.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/ieee754/dbl-64/k_cos.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/ieee754/dbl-64/k_rem_pio2.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/ieee754/dbl-64/k_sin.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/ieee754/dbl-64/k_tan.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/ieee754/dbl-64/mpa.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/ieee754/dbl-64/mpatan.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/ieee754/dbl-64/mpatan2.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/ieee754/dbl-64/mpexp.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/ieee754/dbl-64/mplog.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/ieee754/dbl-64/dbl2mpn.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/ieee754/dbl-64/mpn2dbl.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/ieee754/dbl-64/mpsqrt.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/ieee754/dbl-64/mptan.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/ieee754/dbl-64/s_asinh.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/ieee754/dbl-64/s_atan.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/ieee754/dbl-64/s_cbrt.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/ieee754/dbl-64/s_cos.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/ieee754/dbl-64/s_erf.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/ieee754/dbl-64/s_expm1.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/ieee754/dbl-64/s_fabs.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/ieee754/dbl-64/s_fmaf.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/ieee754/dbl-64/s_fpclassify.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/ieee754/dbl-64/s_log1p.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/ieee754/dbl-64/s_sin.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/ieee754/dbl-64/s_sincos.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/ieee754/dbl-64/s_tan.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/ieee754/dbl-64/s_tanh.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/ieee754/dbl-64/sincos32.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/ieee754/dbl-64/sincostab.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/ieee754/dbl-64/slowexp.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/ieee754/dbl-64/slowpow.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/ieee754/dbl-64/t_exp.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/ieee754/dbl-64/w_exp.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/ieee754/dbl-64/x2y2m1f.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/ieee754/flt-32/e_acosf.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/ieee754/flt-32/e_acoshf.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/ieee754/flt-32/e_asinf.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/ieee754/flt-32/e_atan2f.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/ieee754/flt-32/e_atanhf.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/ieee754/flt-32/e_coshf.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/ieee754/flt-32/e_exp2f.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/ieee754/flt-32/e_expf.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/ieee754/flt-32/e_fmodf.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/ieee754/flt-32/e_gammaf_r.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/ieee754/flt-32/e_hypotf.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/ieee754/flt-32/e_ilogbf.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/ieee754/flt-32/e_j0f.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/ieee754/flt-32/e_j1f.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/ieee754/flt-32/e_jnf.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/ieee754/flt-32/e_lgammaf_r.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/ieee754/flt-32/e_log2f.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/ieee754/flt-32/e_log10f.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/ieee754/flt-32/e_logf.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/ieee754/flt-32/e_powf.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/ieee754/flt-32/e_rem_pio2f.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/ieee754/flt-32/e_remainderf.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/ieee754/flt-32/e_sinhf.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/ieee754/flt-32/e_sqrtf.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/ieee754/flt-32/k_cosf.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/ieee754/flt-32/k_rem_pio2f.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/ieee754/flt-32/k_sinf.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/ieee754/flt-32/k_tanf.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/ieee754/flt-32/mpn2flt.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/ieee754/flt-32/s_asinhf.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/ieee754/flt-32/s_atanf.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/ieee754/flt-32/s_cbrtf.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/ieee754/flt-32/s_ceilf.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/ieee754/flt-32/s_copysignf.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/ieee754/flt-32/s_erff.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/ieee754/flt-32/s_expm1f.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/ieee754/flt-32/s_fabsf.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/ieee754/flt-32/s_finitef.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/ieee754/flt-32/s_floorf.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/ieee754/flt-32/s_fpclassifyf.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/ieee754/flt-32/s_frexpf.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/ieee754/flt-32/s_isinf_nsf.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/ieee754/flt-32/s_isinff.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/ieee754/flt-32/s_isnanf.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/ieee754/flt-32/s_llroundf.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/ieee754/flt-32/s_log1pf.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/ieee754/flt-32/s_logbf.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/ieee754/flt-32/s_lroundf.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/ieee754/flt-32/s_modff.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/ieee754/flt-32/s_nearbyintf.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/ieee754/flt-32/s_nextafterf.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/ieee754/flt-32/s_remquof.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/ieee754/flt-32/s_rintf.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/ieee754/flt-32/s_roundf.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/ieee754/flt-32/s_scalblnf.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/ieee754/flt-32/s_scalbnf.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/ieee754/flt-32/s_tanf.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/ieee754/flt-32/s_tanhf.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/ieee754/flt-32/s_truncf.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/ieee754/flt-32/w_expf.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/ieee754/ldbl-96/e_acoshl.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/ieee754/ldbl-96/e_asinl.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/ieee754/ldbl-96/e_atanhl.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/ieee754/ldbl-96/e_coshl.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/ieee754/ldbl-96/e_gammal_r.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/ieee754/ldbl-96/e_hypotl.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/ieee754/ldbl-96/e_j0l.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/ieee754/ldbl-96/e_j1l.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/ieee754/ldbl-96/e_jnl.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/ieee754/ldbl-96/e_lgammal_r.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/ieee754/ldbl-96/e_rem_pio2l.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/ieee754/ldbl-96/e_sinhl.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/ieee754/ldbl-96/k_cosl.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/ieee754/ldbl-96/k_sinl.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/ieee754/ldbl-96/k_tanl.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/ieee754/ldbl-96/mpn2ldbl.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/ieee754/ldbl-96/s_asinhl.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/ieee754/ldbl-96/s_cbrtl.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/ieee754/ldbl-96/s_cosl.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/ieee754/ldbl-96/s_erfl.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/ieee754/ldbl-96/s_fma.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/ieee754/ldbl-96/s_fmal.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/ieee754/ldbl-96/s_frexpl.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/ieee754/ldbl-96/s_isinf_nsl.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/ieee754/ldbl-96/s_llroundl.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/ieee754/ldbl-96/s_lroundl.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/ieee754/ldbl-96/s_modfl.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/ieee754/ldbl-96/s_nearbyintl.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/ieee754/ldbl-96/s_remquol.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/ieee754/ldbl-96/s_roundl.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/ieee754/ldbl-96/s_scalbnl.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/ieee754/ldbl-96/s_signbitl.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/ieee754/ldbl-96/s_sincosl.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/ieee754/ldbl-96/s_sinl.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/ieee754/ldbl-96/s_tanhl.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/ieee754/ldbl-96/s_tanl.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/ieee754/ldbl-96/strtold_l.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/ieee754/ldbl-96/t_sincosl.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/ieee754/ldbl-96/w_expl.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/ieee754/ldbl-96/x2y2m1.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/ieee754/ldbl-96/x2y2m1l.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/ieee754/k_standard.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/ieee754/s_lib_version.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/ieee754/s_matherr.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/ieee754/s_signgam.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/llamaos/export/_exit.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/llamaos/export/abort.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/llamaos/export/access.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/llamaos/export/assert-perr.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/llamaos/export/assert.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/llamaos/export/brk.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/llamaos/export/close.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/llamaos/export/dup.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/llamaos/export/dup2.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/llamaos/export/ftruncate.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/llamaos/export/get_avphys_pages.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/llamaos/export/get_nprocs.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/llamaos/export/get_nprocs_conf.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/llamaos/export/get_phys_pages.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/llamaos/export/getcwd.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/llamaos/export/gethostname.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/llamaos/export/getpagesize.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/llamaos/export/getpid.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/llamaos/export/isatty.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/llamaos/export/libc_fatal.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/llamaos/export/lseek.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/llamaos/export/lseek64.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/llamaos/export/libc_open.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/llamaos/export/lxstat64.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/llamaos/export/madvise.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/llamaos/export/mkdir.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/llamaos/export/pathconf.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/llamaos/export/poll.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/llamaos/export/raise.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/llamaos/export/read.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/llamaos/export/sched_primax.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/llamaos/export/sched_primin.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/llamaos/export/sigsuspend.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/llamaos/export/sigsuspend_nocancel.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/llamaos/export/sleep.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/llamaos/export/syscall.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/llamaos/export/gettimeofday.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/llamaos/export/time.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/llamaos/export/uname.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/llamaos/export/unlink.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/llamaos/export/write.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/llamaos/export/writev.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/llamaos/export/xstat.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/llamaos/export/xstat64.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/llamaos/x86_64/longjmp_chk.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/llamaos/dlerror.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/llamaos/gcc_personality_v0.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/llamaos/mremap.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/llamaos/powidf2.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/llamaos/register-atfork.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/llamaos/sigaddset.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/llamaos/sysconf.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/llamaos/syslog.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/llamaos/system.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/posix/ctermid.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/posix/cuserid.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/posix/tempname.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/wordsize-64/labs.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/wordsize-64/ldiv.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/wordsize-64/strtoimax.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/wordsize-64/strtol.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/wordsize-64/strtol_l.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/wordsize-64/strtoll.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/wordsize-64/strtoll_l.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/wordsize-64/strtoul.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/wordsize-64/strtoul_l.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/wordsize-64/strtoull.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/wordsize-64/strtoull_l.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/wordsize-64/strtoumax.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/wordsize-64/wcstoimax.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/wordsize-64/wcstol.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/wordsize-64/wcstol_l.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/wordsize-64/wcstoll.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/wordsize-64/wcstoll_l.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/wordsize-64/wcstoul.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/wordsize-64/wcstoul_l.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/wordsize-64/wcstoull.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/wordsize-64/wcstoull_l.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/wordsize-64/wcstoumax.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/x86/fpu/powl_helper.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/x86_64/fpu/e_acosl.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/x86_64/fpu/e_atan2l.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/x86_64/fpu/e_sqrt.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/x86_64/fpu/e_sqrtl.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/x86_64/fpu/fclrexcpt.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/x86_64/fpu/fedisblxcpt.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/x86_64/fpu/feenablxcpt.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/x86_64/fpu/fegetenv.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/x86_64/fpu/fegetexcept.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/x86_64/fpu/fegetround.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/x86_64/fpu/feholdexcpt.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/x86_64/fpu/fesetenv.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/x86_64/fpu/fesetround.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/x86_64/fpu/feupdateenv.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/x86_64/fpu/fgetexcptflg.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/x86_64/fpu/fraiseexcpt.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/x86_64/fpu/fsetexcptflg.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/x86_64/fpu/ftestexcept.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/x86_64/fpu/k_rem_pio2l.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/x86_64/fpu/printf_fphex.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/x86_64/fpu/s_atanl.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/x86_64/fpu/s_fpclassifyl.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/x86_64/fpu/s_isinfl.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/x86_64/fpu/s_isnanl.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/x86_64/fpu/s_logbl.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/x86_64/fpu/s_nextafterl.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/x86_64/fpu/s_nexttoward.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/x86_64/fpu/s_nexttowardf.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/x86_64/fpu/s_rintl.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/x86_64/fpu/s_significandl.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/x86_64/cacheinfo.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/x86_64/dl-runtime.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/x86_64/ffs.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/x86_64/ffsll.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/x86_64/hp-timing.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/x86_64/l10nflist.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/x86_64/ldbl2mpn.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/x86_64/memmove.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/x86_64/mp_clz_tab.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/x86_64/strcasecmp_l-nonascii.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/x86_64/strncase_l-nonascii.c \
  sys/glibc-$(GLIBC_VERSION)/sysdeps/x86_64/tlsdesc.c \
  sys/glibc-$(GLIBC_VERSION)/time/adjtime.c \
  sys/glibc-$(GLIBC_VERSION)/time/alt_digit.c \
  sys/glibc-$(GLIBC_VERSION)/time/asctime.c \
  sys/glibc-$(GLIBC_VERSION)/time/clock.c \
  sys/glibc-$(GLIBC_VERSION)/time/ctime.c \
  sys/glibc-$(GLIBC_VERSION)/time/ctime_r.c \
  sys/glibc-$(GLIBC_VERSION)/time/difftime.c \
  sys/glibc-$(GLIBC_VERSION)/time/dysize.c \
  sys/glibc-$(GLIBC_VERSION)/time/era.c \
  sys/glibc-$(GLIBC_VERSION)/time/ftime.c \
  sys/glibc-$(GLIBC_VERSION)/time/getdate.c \
  sys/glibc-$(GLIBC_VERSION)/time/getitimer.c \
  sys/glibc-$(GLIBC_VERSION)/time/gmtime.c \
  sys/glibc-$(GLIBC_VERSION)/time/lc-time-cleanup.c \
  sys/glibc-$(GLIBC_VERSION)/time/localtime.c \
  sys/glibc-$(GLIBC_VERSION)/time/mktime.c \
  sys/glibc-$(GLIBC_VERSION)/time/offtime.c \
  sys/glibc-$(GLIBC_VERSION)/time/setitimer.c \
  sys/glibc-$(GLIBC_VERSION)/time/settimeofday.c \
  sys/glibc-$(GLIBC_VERSION)/time/stime.c \
  sys/glibc-$(GLIBC_VERSION)/time/strftime.c \
  sys/glibc-$(GLIBC_VERSION)/time/strftime_l.c \
  sys/glibc-$(GLIBC_VERSION)/time/strptime.c \
  sys/glibc-$(GLIBC_VERSION)/time/strptime_l.c \
  sys/glibc-$(GLIBC_VERSION)/time/timegm.c \
  sys/glibc-$(GLIBC_VERSION)/time/timespec_get.c \
  sys/glibc-$(GLIBC_VERSION)/time/tzfile.c \
  sys/glibc-$(GLIBC_VERSION)/time/tzset.c \
  sys/glibc-$(GLIBC_VERSION)/time/wcsftime.c \
  sys/glibc-$(GLIBC_VERSION)/time/wcsftime_l.c \
  sys/glibc-$(GLIBC_VERSION)/wcsmbs/btowc.c \
  sys/glibc-$(GLIBC_VERSION)/wcsmbs/c16rtomb.c \
  sys/glibc-$(GLIBC_VERSION)/wcsmbs/isoc99_fwscanf.c \
  sys/glibc-$(GLIBC_VERSION)/wcsmbs/isoc99_swscanf.c \
  sys/glibc-$(GLIBC_VERSION)/wcsmbs/isoc99_vfwscanf.c \
  sys/glibc-$(GLIBC_VERSION)/wcsmbs/isoc99_vswscanf.c \
  sys/glibc-$(GLIBC_VERSION)/wcsmbs/isoc99_vwscanf.c \
  sys/glibc-$(GLIBC_VERSION)/wcsmbs/isoc99_wscanf.c \
  sys/glibc-$(GLIBC_VERSION)/wcsmbs/mbrlen.c \
  sys/glibc-$(GLIBC_VERSION)/wcsmbs/mbrtoc16.c \
  sys/glibc-$(GLIBC_VERSION)/wcsmbs/mbrtowc.c \
  sys/glibc-$(GLIBC_VERSION)/wcsmbs/mbsinit.c \
  sys/glibc-$(GLIBC_VERSION)/wcsmbs/mbsnrtowcs.c \
  sys/glibc-$(GLIBC_VERSION)/wcsmbs/mbsrtowcs.c \
  sys/glibc-$(GLIBC_VERSION)/wcsmbs/mbsrtowcs_l.c \
  sys/glibc-$(GLIBC_VERSION)/wcsmbs/wcpcpy.c \
  sys/glibc-$(GLIBC_VERSION)/wcsmbs/wcpncpy.c \
  sys/glibc-$(GLIBC_VERSION)/wcsmbs/wcrtomb.c \
  sys/glibc-$(GLIBC_VERSION)/wcsmbs/wcscasecmp.c \
  sys/glibc-$(GLIBC_VERSION)/wcsmbs/wcscasecmp_l.c \
  sys/glibc-$(GLIBC_VERSION)/wcsmbs/wcscat.c \
  sys/glibc-$(GLIBC_VERSION)/wcsmbs/wcschrnul.c \
  sys/glibc-$(GLIBC_VERSION)/wcsmbs/wcscoll.c \
  sys/glibc-$(GLIBC_VERSION)/wcsmbs/wcscoll_l.c \
  sys/glibc-$(GLIBC_VERSION)/wcsmbs/wcscpy.c \
  sys/glibc-$(GLIBC_VERSION)/wcsmbs/wcscspn.c \
  sys/glibc-$(GLIBC_VERSION)/wcsmbs/wcsdup.c \
  sys/glibc-$(GLIBC_VERSION)/wcsmbs/wcsmbsload.c \
  sys/glibc-$(GLIBC_VERSION)/wcsmbs/wcsncase.c \
  sys/glibc-$(GLIBC_VERSION)/wcsmbs/wcsncase_l.c \
  sys/glibc-$(GLIBC_VERSION)/wcsmbs/wcsncat.c \
  sys/glibc-$(GLIBC_VERSION)/wcsmbs/wcsncmp.c \
  sys/glibc-$(GLIBC_VERSION)/wcsmbs/wcsncpy.c \
  sys/glibc-$(GLIBC_VERSION)/wcsmbs/wcsnlen.c \
  sys/glibc-$(GLIBC_VERSION)/wcsmbs/wcsnrtombs.c \
  sys/glibc-$(GLIBC_VERSION)/wcsmbs/wcspbrk.c \
  sys/glibc-$(GLIBC_VERSION)/wcsmbs/wcsrtombs.c \
  sys/glibc-$(GLIBC_VERSION)/wcsmbs/wcsspn.c \
  sys/glibc-$(GLIBC_VERSION)/wcsmbs/wcsstr.c \
  sys/glibc-$(GLIBC_VERSION)/wcsmbs/wcstod.c \
  sys/glibc-$(GLIBC_VERSION)/wcsmbs/wcstod_l.c \
  sys/glibc-$(GLIBC_VERSION)/wcsmbs/wcstof.c \
  sys/glibc-$(GLIBC_VERSION)/wcsmbs/wcstof_l.c \
  sys/glibc-$(GLIBC_VERSION)/wcsmbs/wcstok.c \
  sys/glibc-$(GLIBC_VERSION)/wcsmbs/wcstol.c \
  sys/glibc-$(GLIBC_VERSION)/wcsmbs/wcstol_l.c \
  sys/glibc-$(GLIBC_VERSION)/wcsmbs/wcstold.c \
  sys/glibc-$(GLIBC_VERSION)/wcsmbs/wcstold_l.c \
  sys/glibc-$(GLIBC_VERSION)/wcsmbs/wcstoul.c \
  sys/glibc-$(GLIBC_VERSION)/wcsmbs/wcstoul_l.c \
  sys/glibc-$(GLIBC_VERSION)/wcsmbs/wcswidth.c \
  sys/glibc-$(GLIBC_VERSION)/wcsmbs/wcsxfrm.c \
  sys/glibc-$(GLIBC_VERSION)/wcsmbs/wcsxfrm_l.c \
  sys/glibc-$(GLIBC_VERSION)/wcsmbs/wctob.c \
  sys/glibc-$(GLIBC_VERSION)/wcsmbs/wcwidth.c \
  sys/glibc-$(GLIBC_VERSION)/wcsmbs/wmemchr.c \
  sys/glibc-$(GLIBC_VERSION)/wcsmbs/wmemcmp.c \
  sys/glibc-$(GLIBC_VERSION)/wcsmbs/wmemcpy.c \
  sys/glibc-$(GLIBC_VERSION)/wcsmbs/wmemmove.c \
  sys/glibc-$(GLIBC_VERSION)/wcsmbs/wmempcpy.c \
  sys/glibc-$(GLIBC_VERSION)/wcsmbs/wmemset.c \
  sys/glibc-$(GLIBC_VERSION)/wctype/iswctype.c \
  sys/glibc-$(GLIBC_VERSION)/wctype/iswctype_l.c \
  sys/glibc-$(GLIBC_VERSION)/wctype/towctrans.c \
  sys/glibc-$(GLIBC_VERSION)/wctype/towctrans_l.c \
  sys/glibc-$(GLIBC_VERSION)/wctype/wcfuncs.c \
  sys/glibc-$(GLIBC_VERSION)/wctype/wcfuncs_l.c \
  sys/glibc-$(GLIBC_VERSION)/wctype/wctrans.c \
  sys/glibc-$(GLIBC_VERSION)/wctype/wctrans_l.c \
  sys/glibc-$(GLIBC_VERSION)/wctype/wctype.c \
  sys/glibc-$(GLIBC_VERSION)/wctype/wctype_l.c

# replaced with llamaOS export
#  sys/glibc-$(GLIBC_VERSION)/assert/assert-perr.c
#  sys/glibc-$(GLIBC_VERSION)/assert/assert.c
#  sys/glibc-$(GLIBC_VERSION)/elf/static-stubs.c
#  sys/glibc-$(GLIBC_VERSION)/io/access.c
#  sys/glibc-$(GLIBC_VERSION)/io/close.c
#  sys/glibc-$(GLIBC_VERSION)/io/dup.c
#  sys/glibc-$(GLIBC_VERSION)/io/dup2.c
#  sys/glibc-$(GLIBC_VERSION)/io/getcwd.c
#  sys/glibc-$(GLIBC_VERSION)/io/isatty.c
#  sys/glibc-$(GLIBC_VERSION)/io/lseek.c
#  sys/glibc-$(GLIBC_VERSION)/io/lseek64.c
#  sys/glibc-$(GLIBC_VERSION)/io/lxstat64.c
#  sys/glibc-$(GLIBC_VERSION)/io/open.c
#  sys/glibc-$(GLIBC_VERSION)/io/read.c
#  sys/glibc-$(GLIBC_VERSION)/io/unlink.c
#  sys/glibc-$(GLIBC_VERSION)/io/write.c
#  sys/glibc-$(GLIBC_VERSION)/io/xstat.c
#  sys/glibc-$(GLIBC_VERSION)/io/xstat64.c
#  sys/glibc-$(GLIBC_VERSION)/misc/brk.c
#  sys/glibc-$(GLIBC_VERSION)/misc/ftruncate.c
#  sys/glibc-$(GLIBC_VERSION)/misc/gethostname.c
#  sys/glibc-$(GLIBC_VERSION)/misc/getpagesize.c
#  sys/glibc-$(GLIBC_VERSION)/misc/getsysstats.c
#  sys/glibc-$(GLIBC_VERSION)/misc/madvise.c
#  sys/glibc-$(GLIBC_VERSION)/misc/writev.c
#  sys/glibc-$(GLIBC_VERSION)/posix/_exit.c
#  sys/glibc-$(GLIBC_VERSION)/posix/getpid.c
#  sys/glibc-$(GLIBC_VERSION)/posix/sleep.c
#  sys/glibc-$(GLIBC_VERSION)/posix/pathconf.c
#  sys/glibc-$(GLIBC_VERSION)/signal/raise.c
#  sys/glibc-$(GLIBC_VERSION)/stdlib/abort.c
#  sys/glibc-$(GLIBC_VERSION)/time/gettimeofday.c
#  sys/glibc-$(GLIBC_VERSION)/time/time.c

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
  $(INCDIR)/bits/setjmp2.h \
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
  $(INCDIR)/sys/bitypes.h \
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
  $(INCDIR)/regex.h \
  $(INCDIR)/sched.h \
  $(INCDIR)/setjmp.h \
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
all : $(LIBDIR)/sys/glibc.a $(HEADERS)

.PHONY: headers
headers : $(HEADERS)

$(LIBDIR)/sys/glibc.a: $(OBJECTS)
	@[ -d $(@D) ] || (mkdir -p $(@D))
	@echo linking: $@
	@$(AR) r $@ $(OBJECTS)
	@echo successfully built: $@
	@echo

$(INCDIR)/% : $(SRCDIR)/sys/glibc-$(GLIBC_VERSION)/nptl/sysdeps/llamaos/x86/%
	@[ -d $(@D) ] || (mkdir -p $(@D))
	@echo copying: $@ from $<
	cp $< $@

$(INCDIR)/% : $(SRCDIR)/sys/glibc-$(GLIBC_VERSION)/sysdeps/llamaos/x86/%
	@[ -d $(@D) ] || (mkdir -p $(@D))
	@echo copying: $@ from $<
	cp $< $@

$(INCDIR)/% : $(SRCDIR)/sys/glibc-$(GLIBC_VERSION)/nptl/sysdeps/pthread/%
	@[ -d $(@D) ] || (mkdir -p $(@D))
	@echo copying: $@ from $<
	cp $< $@

$(INCDIR)/% : $(SRCDIR)/sys/glibc-$(GLIBC_VERSION)/sysdeps/llamaos/%
	@[ -d $(@D) ] || (mkdir -p $(@D))
	@echo copying: $@ from $<
	cp $< $@

$(INCDIR)/% : $(SRCDIR)/sys/glibc-$(GLIBC_VERSION)/sysdeps/x86/fpu/%
	@[ -d $(@D) ] || (mkdir -p $(@D))
	@echo copying: $@ from $<
	cp $< $@

$(INCDIR)/% : $(SRCDIR)/sys/glibc-$(GLIBC_VERSION)/sysdeps/x86/%
	@[ -d $(@D) ] || (mkdir -p $(@D))
	@echo copying: $@ from $<
	cp $< $@

$(INCDIR)/% : $(SRCDIR)/sys/glibc-$(GLIBC_VERSION)/sysdeps/wordsize-64/%
	@[ -d $(@D) ] || (mkdir -p $(@D))
	@echo copying: $@ from $<
	cp $< $@

$(INCDIR)/% : $(SRCDIR)/sys/glibc-$(GLIBC_VERSION)/sysdeps/ieee754/%
	@[ -d $(@D) ] || (mkdir -p $(@D))
	@echo copying: $@ from $<
	cp $< $@

$(INCDIR)/% : $(SRCDIR)/sys/glibc-$(GLIBC_VERSION)/sysdeps/generic/%
	@[ -d $(@D) ] || (mkdir -p $(@D))
	@echo copying: $@ from $<
	cp $< $@

$(INCDIR)/% : $(SRCDIR)/sys/glibc-$(GLIBC_VERSION)/assert/%
	@[ -d $(@D) ] || (mkdir -p $(@D))
	@echo copying: $@ from $<
	cp $< $@

$(INCDIR)/% : $(SRCDIR)/sys/glibc-$(GLIBC_VERSION)/catgets/%
	@[ -d $(@D) ] || (mkdir -p $(@D))
	@echo copying: $@ from $<
	cp $< $@

$(INCDIR)/% : $(SRCDIR)/sys/glibc-$(GLIBC_VERSION)/ctype/%
	@[ -d $(@D) ] || (mkdir -p $(@D))
	@echo copying: $@ from $<
	cp $< $@

$(INCDIR)/% : $(SRCDIR)/sys/glibc-$(GLIBC_VERSION)/inet/%
	@[ -d $(@D) ] || (mkdir -p $(@D))
	@echo copying: $@ from $<
	cp $< $@

$(INCDIR)/% : $(SRCDIR)/sys/glibc-$(GLIBC_VERSION)/intl/%
	@[ -d $(@D) ] || (mkdir -p $(@D))
	@echo copying: $@ from $<
	cp $< $@

$(INCDIR)/% : $(SRCDIR)/sys/glibc-$(GLIBC_VERSION)/io/%
	@[ -d $(@D) ] || (mkdir -p $(@D))
	@echo copying: $@ from $<
	cp $< $@

$(INCDIR)/% : $(SRCDIR)/sys/glibc-$(GLIBC_VERSION)/locale/%
	@[ -d $(@D) ] || (mkdir -p $(@D))
	@echo copying: $@ from $<
	cp $< $@

$(INCDIR)/% : $(SRCDIR)/sys/glibc-$(GLIBC_VERSION)/libio/%
	@[ -d $(@D) ] || (mkdir -p $(@D))
	@echo copying: $@ from $<
	cp $< $@

$(INCDIR)/% : $(SRCDIR)/sys/glibc-$(GLIBC_VERSION)/malloc/%
	@[ -d $(@D) ] || (mkdir -p $(@D))
	@echo copying: $@ from $<
	cp $< $@

$(INCDIR)/% : $(SRCDIR)/sys/glibc-$(GLIBC_VERSION)/math/%
	@[ -d $(@D) ] || (mkdir -p $(@D))
	@echo copying: $@ from $<
	cp $< $@

$(INCDIR)/% : $(SRCDIR)/sys/glibc-$(GLIBC_VERSION)/misc/%
	@[ -d $(@D) ] || (mkdir -p $(@D))
	@echo copying: $@ from $<
	cp $< $@

$(INCDIR)/% : $(SRCDIR)/sys/glibc-$(GLIBC_VERSION)/posix/%
	@[ -d $(@D) ] || (mkdir -p $(@D))
	@echo copying: $@ from $<
	cp $< $@

$(INCDIR)/% : $(SRCDIR)/sys/glibc-$(GLIBC_VERSION)/pwd/%
	@[ -d $(@D) ] || (mkdir -p $(@D))
	@echo copying: $@ from $<
	cp $< $@

$(INCDIR)/% : $(SRCDIR)/sys/glibc-$(GLIBC_VERSION)/resolv/%
	@[ -d $(@D) ] || (mkdir -p $(@D))
	@echo copying: $@ from $<
	cp $< $@

$(INCDIR)/% : $(SRCDIR)/sys/glibc-$(GLIBC_VERSION)/resource/%
	@[ -d $(@D) ] || (mkdir -p $(@D))
	@echo copying: $@ from $<
	cp $< $@

$(INCDIR)/% : $(SRCDIR)/sys/glibc-$(GLIBC_VERSION)/setjmp/%
	@[ -d $(@D) ] || (mkdir -p $(@D))
	@echo copying: $@ from $<
	cp $< $@

$(INCDIR)/% : $(SRCDIR)/sys/glibc-$(GLIBC_VERSION)/signal/%
	@[ -d $(@D) ] || (mkdir -p $(@D))
	@echo copying: $@ from $<
	cp $< $@

$(INCDIR)/% : $(SRCDIR)/sys/glibc-$(GLIBC_VERSION)/socket/%
	@[ -d $(@D) ] || (mkdir -p $(@D))
	@echo copying: $@ from $<
	cp $< $@

$(INCDIR)/% : $(SRCDIR)/sys/glibc-$(GLIBC_VERSION)/stdlib/%
	@[ -d $(@D) ] || (mkdir -p $(@D))
	@echo copying: $@ from $<
	cp $< $@

$(INCDIR)/% : $(SRCDIR)/sys/glibc-$(GLIBC_VERSION)/string/%
	@[ -d $(@D) ] || (mkdir -p $(@D))
	@echo copying: $@ from $<
	cp $< $@

$(INCDIR)/% : $(SRCDIR)/sys/glibc-$(GLIBC_VERSION)/time/%
	@[ -d $(@D) ] || (mkdir -p $(@D))
	@echo copying: $@ from $<
	cp $< $@

$(INCDIR)/% : $(SRCDIR)/sys/glibc-$(GLIBC_VERSION)/wcsmbs/%
	@[ -d $(@D) ] || (mkdir -p $(@D))
	@echo copying: $@ from $<
	cp $< $@

$(INCDIR)/% : $(SRCDIR)/sys/glibc-$(GLIBC_VERSION)/wctype/%
	@[ -d $(@D) ] || (mkdir -p $(@D))
	@echo copying: $@ from $<
	cp $< $@

# catches things like bits/*.h that specify path
$(INCDIR)/% : $(SRCDIR)/sys/glibc-$(GLIBC_VERSION)/%
	@[ -d $(@D) ] || (mkdir -p $(@D))
	@echo copying: $@ from $<
	cp $< $@

$(INCDIR)/gnu/stubs.h : $(SRCDIR)/sys/glibc-$(GLIBC_VERSION)/include/gnu/stubs.h
	@[ -d $(@D) ] || (mkdir -p $(@D))
	@echo copying: $@ from $<
	cp $< $@

$(INCDIR)/features.h : $(SRCDIR)/sys/glibc-$(GLIBC_VERSION)/include/features.h
	@[ -d $(@D) ] || (mkdir -p $(@D))
	@echo copying: $@ from $<
	cp $< $@

$(INCDIR)/stdc-predef.h : $(SRCDIR)/sys/glibc-$(GLIBC_VERSION)/include/stdc-predef.h
	@[ -d $(@D) ] || (mkdir -p $(@D))
	@echo copying: $@ from $<
	cp $< $@

# some files come from the gcc source
$(INCDIR)/float.h : $(SRCDIR)/sys/gcc-$(GCC_VERSION)/gcc/ginclude/float.h
	@[ -d $(@D) ] || (mkdir -p $(@D))
	@echo copying: $@ from $<
	cp $< $@

$(INCDIR)/iso646.h : $(SRCDIR)/sys/gcc-$(GCC_VERSION)/gcc/ginclude/iso646.h
	@[ -d $(@D) ] || (mkdir -p $(@D))
	@echo copying: $@ from $<
	cp $< $@

$(INCDIR)/stdalign.h : $(SRCDIR)/sys/gcc-$(GCC_VERSION)/gcc/ginclude/stdalign.h
	@[ -d $(@D) ] || (mkdir -p $(@D))
	@echo copying: $@ from $<
	cp $< $@

$(INCDIR)/stdarg.h : $(SRCDIR)/sys/gcc-$(GCC_VERSION)/gcc/ginclude/stdarg.h
	@[ -d $(@D) ] || (mkdir -p $(@D))
	@echo copying: $@ from $<
	cp $< $@

$(INCDIR)/stdbool.h : $(SRCDIR)/sys/gcc-$(GCC_VERSION)/gcc/ginclude/stdbool.h
	@[ -d $(@D) ] || (mkdir -p $(@D))
	@echo copying: $@ from $<
	cp $< $@

$(INCDIR)/stddef.h : $(SRCDIR)/sys/gcc-$(GCC_VERSION)/gcc/ginclude/stddef.h
	@[ -d $(@D) ] || (mkdir -p $(@D))
	@echo copying: $@ from $<
	cp $< $@

$(INCDIR)/stdfix.h : $(SRCDIR)/sys/gcc-$(GCC_VERSION)/gcc/ginclude/stdfix.h
	@[ -d $(@D) ] || (mkdir -p $(@D))
	@echo copying: $@ from $<
	cp $< $@

$(INCDIR)/stdint-gcc.h : $(SRCDIR)/sys/gcc-$(GCC_VERSION)/gcc/ginclude/stdint-gcc.h
	@[ -d $(@D) ] || (mkdir -p $(@D))
	@echo copying: $@ from $<
	cp $< $@

$(INCDIR)/stdint-wrap.h : $(SRCDIR)/sys/gcc-$(GCC_VERSION)/gcc/ginclude/stdint-wrap.h
	@[ -d $(@D) ] || (mkdir -p $(@D))
	@echo copying: $@ from $<
	cp $< $@

$(INCDIR)/stdnoreturn.h : $(SRCDIR)/sys/gcc-$(GCC_VERSION)/gcc/ginclude/stdnoreturn.h
	@[ -d $(@D) ] || (mkdir -p $(@D))
	@echo copying: $@ from $<
	cp $< $@

$(INCDIR)/varargs.h : $(SRCDIR)/sys/gcc-$(GCC_VERSION)/gcc/ginclude/varargs.h
	@[ -d $(@D) ] || (mkdir -p $(@D))
	@echo copying: $@ from $<
	cp $< $@

$(INCDIR)/glimits.h : $(SRCDIR)/sys/gcc-$(GCC_VERSION)/gcc/glimits.h
	@[ -d $(@D) ] || (mkdir -p $(@D))
	@echo copying: $@ from $<
	cp $< $@

include rules.mk

# include auto-generated dependencies
-include $(DEPENDS)

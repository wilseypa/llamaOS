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
  -I $(SRCDIR)/glibc-$(GLIBC_VERSION) \
  -I $(SRCDIR)/glibc-$(GLIBC_VERSION)/sysdeps/llamaos/x86_64/64/nptl \
  -I $(SRCDIR)/glibc-$(GLIBC_VERSION)/sysdeps/llamaos/x86_64/64 \
  -I $(SRCDIR)/glibc-$(GLIBC_VERSION)/sysdeps/llamaos/x86_64 \
  -I $(SRCDIR)/glibc-$(GLIBC_VERSION)/nptl/sysdeps/llamaos/x86_64 \
  -I $(SRCDIR)/glibc-$(GLIBC_VERSION)/nptl/sysdeps/llamaos/x86 \
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
  -I $(SRCDIR)/glibc-$(GLIBC_VERSION)/libio \
  -I $(SRCDIR)/glibc-$(GLIBC_VERSION)/locale \
  -I $(SRCDIR)/glibc-$(GLIBC_VERSION)/stdio-common \
  -I $(SRCDIR)/glibc-$(GLIBC_VERSION)/stdlib \
  -I $(SRCDIR)/glibc-$(GLIBC_VERSION)/wcsmbs \
  -I $(SRCDIR)/gcc-$(GCC_VERSION)/gcc/ginclude \
  -I $(SRCDIR)/gcc-$(GCC_VERSION)/gcc/include \
  -I $(SRCDIR)

ASMFLAGS += \
  -U_FORTIFY_SOURCE \
  -D_LIBC_REENTRANT \
  -DASSEMBLER \
  -Wa,--noexecstack \
  $(INCLUDES_DIRS) \
  -include  $(SRCDIR)/glibc-$(GLIBC_VERSION)/include/libc-symbols.h

  CFLAGS += \
  -Wbad-function-cast \
  -Wcast-qual \
  -Wcomment \
  -Wcomments \
  -Wfloat-equal \
  -Winline \
  -Wmissing-declarations \
  -Wmissing-noreturn \
  -Wmissing-prototypes \
  -Wmultichar \
  -Wsign-compare \
  -Wtrigraphs \
  -Wwrite-strings \
  -fmerge-all-constants \
  -frounding-math \
  -Wstrict-prototypes \
  -U_FORTIFY_SOURCE \
  -DLOCALEDIR='""' \
  -DLOCALE_ALIAS_PATH='""' \
  -D_LIBC_REENTRANT \
  $(INCLUDES_DIRS) \
  -include  $(SRCDIR)/glibc-$(GLIBC_VERSION)/include/libc-symbols.h

VPATH = $(SRCDIR)

ASM_SOURCES = \
  glibc-$(GLIBC_VERSION)/csu/abi-note.S \
  glibc-$(GLIBC_VERSION)/sysdeps/x86_64/crti.S \
  glibc-$(GLIBC_VERSION)/sysdeps/x86_64/crtn.S

#  glibc-$(GLIBC_VERSION)/sysdeps/x86_64/add_n.S \
  glibc-$(GLIBC_VERSION)/sysdeps/x86_64/addmul_1.S \
  glibc-$(GLIBC_VERSION)/sysdeps/x86_64/bzero.S \
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
  glibc-$(GLIBC_VERSION)/sysdeps/x86_64/stpcpy.S \
  glibc-$(GLIBC_VERSION)/sysdeps/x86_64/strcasecmp.S \
  glibc-$(GLIBC_VERSION)/sysdeps/x86_64/strcasecmp_l.S \
  glibc-$(GLIBC_VERSION)/sysdeps/x86_64/strcat.S \
  glibc-$(GLIBC_VERSION)/sysdeps/x86_64/strchr.S \
  glibc-$(GLIBC_VERSION)/sysdeps/x86_64/strchrnul.S \
  glibc-$(GLIBC_VERSION)/sysdeps/x86_64/strcmp.S \
  glibc-$(GLIBC_VERSION)/sysdeps/x86_64/strcpy.S \
  glibc-$(GLIBC_VERSION)/sysdeps/x86_64/strcspn.S \
  glibc-$(GLIBC_VERSION)/sysdeps/x86_64/strlen.S \
  glibc-$(GLIBC_VERSION)/sysdeps/x86_64/strncase.S \
  glibc-$(GLIBC_VERSION)/sysdeps/x86_64/strncase_l.S \
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

C_SOURCES = \
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
  glibc-$(GLIBC_VERSION)/sysdeps/x86_64/hp-timing.c

  
  
  
#  glibc-$(GLIBC_VERSION)/assert/__assert.c \
  glibc-$(GLIBC_VERSION)/assert/assert-perr.c \
  glibc-$(GLIBC_VERSION)/assert/assert.c \
  glibc-$(GLIBC_VERSION)/csu/gmon-start.c \
  glibc-$(GLIBC_VERSION)/csu/init.c \
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
  glibc-$(GLIBC_VERSION)/malloc/morecore.c \
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
  glibc-$(GLIBC_VERSION)/stdlib/abort.c \
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
  glibc-$(GLIBC_VERSION)/stdlib/rpmatch.c \
  glibc-$(GLIBC_VERSION)/stdlib/secure-getenv.c \
  glibc-$(GLIBC_VERSION)/stdlib/seed48.c \
  glibc-$(GLIBC_VERSION)/stdlib/seed48_r.c \
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
  glibc-$(GLIBC_VERSION)/string/memmove.c \
  glibc-$(GLIBC_VERSION)/string/stpncpy.c \
  glibc-$(GLIBC_VERSION)/string/strcasecmp.c \
  glibc-$(GLIBC_VERSION)/string/strcasestr.c \
  glibc-$(GLIBC_VERSION)/string/strcoll_l.c \
  glibc-$(GLIBC_VERSION)/string/strdup.c \
  glibc-$(GLIBC_VERSION)/string/strerror.c \
  glibc-$(GLIBC_VERSION)/string/strerror_l.c \
  glibc-$(GLIBC_VERSION)/string/strfry.c \
  glibc-$(GLIBC_VERSION)/string/string-inlines.c \
  glibc-$(GLIBC_VERSION)/string/strncase.c \
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
  glibc-$(GLIBC_VERSION)/sysdeps/ieee754/dbl-64/dbl2mpn.c \
  glibc-$(GLIBC_VERSION)/sysdeps/ieee754/dbl-64/mpn2dbl.c \
  glibc-$(GLIBC_VERSION)/sysdeps/ieee754/flt-32/mpn2flt.c \
  glibc-$(GLIBC_VERSION)/sysdeps/ieee754/ldbl-96/mpn2ldbl.c \
  glibc-$(GLIBC_VERSION)/sysdeps/ieee754/ldbl-96/strtold_l.c \
  glibc-$(GLIBC_VERSION)/sysdeps/llamaos/errno.c \
  glibc-$(GLIBC_VERSION)/sysdeps/llamaos/init-first.c \
  glibc-$(GLIBC_VERSION)/sysdeps/posix/ctermid.c \
  glibc-$(GLIBC_VERSION)/sysdeps/posix/cuserid.c \
  glibc-$(GLIBC_VERSION)/sysdeps/posix/remove.c \
  glibc-$(GLIBC_VERSION)/sysdeps/posix/tempname.c \
  glibc-$(GLIBC_VERSION)/sysdeps/x86_64/fpu/printf_fphex.c \
  glibc-$(GLIBC_VERSION)/sysdeps/x86_64/cacheinfo.c \
  glibc-$(GLIBC_VERSION)/sysdeps/x86_64/ffs.c \
  glibc-$(GLIBC_VERSION)/sysdeps/x86_64/ldbl2mpn.c \
  glibc-$(GLIBC_VERSION)/sysdeps/x86_64/memmove.c \
  glibc-$(GLIBC_VERSION)/sysdeps/x86_64/mp_clz_tab.c \
  glibc-$(GLIBC_VERSION)/sysdeps/x86_64/strcasecmp_l-nonascii.c \
  glibc-$(GLIBC_VERSION)/sysdeps/x86_64/strncase_l-nonascii.c \
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
  glibc-$(GLIBC_VERSION)/wcsmbs/wcstold.c \
  glibc-$(GLIBC_VERSION)/wcsmbs/wcstold_l.c \
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
  glibc-$(GLIBC_VERSION)/wcsmbs/wmemset.c

HEADERS = \
  $(INCDIR)/bits/stdio.h \
  $(INCDIR)/bits/stdio_lim.h \
  $(INCDIR)/bits/string.h \
  $(INCDIR)/bits/string2.h \
  $(INCDIR)/bits/sys_errlist.h \
  $(INCDIR)/bits/types.h \
  $(INCDIR)/bits/typesizes.h \
  $(INCDIR)/bits/wchar.h \
  $(INCDIR)/bits/wordsize.h \
  $(INCDIR)/gnu/stubs.h \
  $(INCDIR)/sys/cdefs.h \
  $(INCDIR)/_G_config.h \
  $(INCDIR)/features.h \
  $(INCDIR)/libio.h \
  $(INCDIR)/stdc-predef.h \
  $(INCDIR)/stdarg.h \
  $(INCDIR)/stddef.h \
  $(INCDIR)/stdint.h \
  $(INCDIR)/stdio.h \
  $(INCDIR)/stdlib.h \
  $(INCDIR)/string.h \
  $(INCDIR)/wchar.h \
  $(INCDIR)/xlocale.h

OBJECTS  = $(ASM_SOURCES:%.S=$(OBJDIR)/%.o)
OBJECTS += $(C_SOURCES:%.c=$(OBJDIR)/%.o)
DEPENDS += $(OBJECTS:%.o=%.d)

.PHONY: all
all : $(LIBDIR)/glibc.a $(HEADERS)

$(LIBDIR)/glibc.a: $(OBJECTS)
	@[ -d $(@D) ] || (mkdir -p $(@D))
	@echo linking: $@
	@$(AR) r $@ $(OBJECTS)
	@echo successfully built: $@
	@echo

$(INCDIR)/% : $(SRCDIR)/glibc-$(GLIBC_VERSION)/sysdeps/gnu/%
	@[ -d $(@D) ] || (mkdir -p $(@D))
	@echo copying: $@ from $<
	cp $< $@

$(INCDIR)/% : $(SRCDIR)/glibc-$(GLIBC_VERSION)/sysdeps/wordsize-64/%
	@[ -d $(@D) ] || (mkdir -p $(@D))
	@echo copying: $@ from $<
	cp $< $@

$(INCDIR)/% : $(SRCDIR)/glibc-$(GLIBC_VERSION)/sysdeps/generic/%
	@[ -d $(@D) ] || (mkdir -p $(@D))
	@echo copying: $@ from $<
	cp $< $@

$(INCDIR)/% : $(SRCDIR)/glibc-$(GLIBC_VERSION)/libio/%
	@[ -d $(@D) ] || (mkdir -p $(@D))
	@echo copying: $@ from $<
	cp $< $@

$(INCDIR)/% : $(SRCDIR)/glibc-$(GLIBC_VERSION)/locale/%
	@[ -d $(@D) ] || (mkdir -p $(@D))
	@echo copying: $@ from $<
	cp $< $@

$(INCDIR)/% : $(SRCDIR)/glibc-$(GLIBC_VERSION)/misc/%
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

$(INCDIR)/% : $(SRCDIR)/glibc-$(GLIBC_VERSION)/wcsmbs/%
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
$(INCDIR)/stdarg.h : $(SRCDIR)/gcc-$(GCC_VERSION)/gcc/ginclude/stdarg.h
	@[ -d $(@D) ] || (mkdir -p $(@D))
	@echo copying: $@ from $<
	cp $< $@

$(INCDIR)/stddef.h : $(SRCDIR)/gcc-$(GCC_VERSION)/gcc/ginclude/stddef.h
	@[ -d $(@D) ] || (mkdir -p $(@D))
	@echo copying: $@ from $<
	cp $< $@

include rules.mk

# include auto-generated dependencies
-include $(DEPENDS)

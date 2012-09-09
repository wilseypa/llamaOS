#
# Copyright (c) 2012, William Magato
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
include common.mk

MAKEFILE_SOURCES += glibc-$(GLIBC_VERSION).mk

#  -D__ASSUME_PRIVATE_FUTEX \

#  -I $(SRCDIR)/glibc-$(GLIBC_VERSION)/nptl/sysdeps/llamaOS/x86_64 \
#  -I $(SRCDIR)/glibc-$(GLIBC_VERSION)/nptl/sysdeps/llamaOS/x86 \
#  -I $(SRCDIR)/glibc-$(GLIBC_VERSION)/nptl/sysdeps/llamaOS/i386 \
#  -I $(SRCDIR)/glibc-$(GLIBC_VERSION)/nptl/sysdeps/llamaOS \
#  -I $(SRCDIR)/glibc-$(GLIBC_VERSION)/nptl \

ASMFLAGS += \
  -I $(SRCDIR)/glibc-$(GLIBC_VERSION)/nptl/sysdeps/pthread \
  -I $(SRCDIR)/glibc-$(GLIBC_VERSION)/nptl/sysdeps/x86_64 \
  -I $(SRCDIR)/glibc-$(GLIBC_VERSION)/sysdeps/llamaos/x86_64 \
  -I $(SRCDIR)/glibc-$(GLIBC_VERSION)/sysdeps/llamaos \
  -I $(SRCDIR)/glibc-$(GLIBC_VERSION)/sysdeps/x86_64 \
  -I $(SRCDIR)/glibc-$(GLIBC_VERSION)/sysdeps/x86 \
  -I $(SRCDIR)/glibc-$(GLIBC_VERSION)/sysdeps/i386 \
  -I $(SRCDIR)/glibc-$(GLIBC_VERSION)/sysdeps/ieee754/ldbl-128 \
  -I $(SRCDIR)/glibc-$(GLIBC_VERSION)/sysdeps/ieee754 \
  -I $(SRCDIR)/glibc-$(GLIBC_VERSION)/sysdeps/generic \
  -I $(SRCDIR)/glibc-$(GLIBC_VERSION)/include \
  -I $(SRCDIR)/glibc-$(GLIBC_VERSION) \
  -include $(SRCDIR)/glibc-$(GLIBC_VERSION)/include/libc-symbols.h

#  -I $(SRCDIR)/glibc-$(GLIBC_VERSION)/nptl/sysdeps/llamaOS/x86_64 \
#  -I $(SRCDIR)/glibc-$(GLIBC_VERSION)/nptl/sysdeps/llamaOS/x86 \
#  -I $(SRCDIR)/glibc-$(GLIBC_VERSION)/nptl/sysdeps/llamaOS/i386 \
#  -I $(SRCDIR)/glibc-$(GLIBC_VERSION)/nptl/sysdeps/x86_64 \
#  -I $(SRCDIR)/glibc-$(GLIBC_VERSION)/nptl \

#  -D__NR_futex=0 \
#  -D__NR_writev=0 \
#  -D__NR_pause=0 \

#  -Wno-unused-parameter \
#  -D__EXCEPTIONS \
#  -DHAVE_MREMAP=0 \

# from original glibc.a
# CFLAGS += -DHAVE_MREMAP=0 -D'LOCALEDIR=""' -D'GCONV_PATH=""' -D'GCONV_DIR=""' -D'LOCALE_ALIAS_PATH=""'

#  -I $(SRCDIR)/glibc-$(GLIBC_VERSION)/sysdeps/llamaos/include \

#  -I $(SRCDIR)/glibc-$(GLIBC_VERSION)/nptl/sysdeps/llamaOS/x86_64 \
#  -I $(SRCDIR)/glibc-$(GLIBC_VERSION)/nptl/sysdeps/llamaOS/x86 \
#  -I $(SRCDIR)/glibc-$(GLIBC_VERSION)/nptl/sysdeps/llamaOS \
#  -I $(SRCDIR)/glibc-$(GLIBC_VERSION)/nptl \

#  -D HAVE_MMAP \
#  -D HAVE_MUNMAP \

CFLAGS += \
  -D _IO_MTSAFE_IO \
  -D 'GCONV_DIR=""' \
  -D 'GCONV_PATH=""' \
  -D HAVE_MREMAP=0 \
  -D 'LOCALE_ALIAS_PATH=""' \
  -D 'LOCALEDIR=""' \
  -I $(SRCDIR)/gcc-$(GCC_VERSION)/gcc/include-fixed \
  -I $(SRCDIR)/gcc-$(GCC_VERSION)/gcc/ginclude \
  -I $(SRCDIR)/gcc-$(GCC_VERSION)/gcc/include \
  -I $(SRCDIR)/gcc-$(GCC_VERSION)/include \
  -I $(SRCDIR)/glibc-$(GLIBC_VERSION)/include \
  -I $(SRCDIR)/glibc-$(GLIBC_VERSION)/nptl/sysdeps/pthread \
  -I $(SRCDIR)/glibc-$(GLIBC_VERSION)/nptl/sysdeps/x86_64 \
  -I $(SRCDIR)/glibc-$(GLIBC_VERSION)/sysdeps/llamaos/x86_64 \
  -I $(SRCDIR)/glibc-$(GLIBC_VERSION)/sysdeps/llamaos \
  -I $(SRCDIR)/glibc-$(GLIBC_VERSION)/sysdeps/x86_64 \
  -I $(SRCDIR)/glibc-$(GLIBC_VERSION)/sysdeps/x86 \
  -I $(SRCDIR)/glibc-$(GLIBC_VERSION)/sysdeps/i386 \
  -I $(SRCDIR)/glibc-$(GLIBC_VERSION)/sysdeps/ieee754/ldbl-128 \
  -I $(SRCDIR)/glibc-$(GLIBC_VERSION)/sysdeps/ieee754 \
  -I $(SRCDIR)/glibc-$(GLIBC_VERSION)/sysdeps/generic \
  -I $(SRCDIR)/glibc-$(GLIBC_VERSION)/csu \
  -I $(SRCDIR)/glibc-$(GLIBC_VERSION)/elf \
  -I $(SRCDIR)/glibc-$(GLIBC_VERSION)/iconv \
  -I $(SRCDIR)/glibc-$(GLIBC_VERSION)/libio \
  -I $(SRCDIR)/glibc-$(GLIBC_VERSION)/stdlib \
  -I $(SRCDIR)/glibc-$(GLIBC_VERSION)/stdio-common \
  -I $(SRCDIR)/glibc-$(GLIBC_VERSION)/wcsmbs \
  -I $(SRCDIR)/glibc-$(GLIBC_VERSION) \
  -include $(SRCDIR)/glibc-$(GLIBC_VERSION)/include/libc-symbols.h \
  -include $(SRCDIR)/llamaos/__thread.h

HEADERS = \
  $(INCDIR)/asm/unistd.h \
  $(INCDIR)/asm/unistd_32.h \
  $(INCDIR)/asm/unistd_64.h \
  $(INCDIR)/bits/confname.h \
  $(INCDIR)/bits/byteswap.h \
  $(INCDIR)/bits/byteswap-16.h \
  $(INCDIR)/bits/endian.h \
  $(INCDIR)/bits/environments.h \
  $(INCDIR)/bits/errno.h \
  $(INCDIR)/bits/fcntl.h \
  $(INCDIR)/bits/huge_val.h \
  $(INCDIR)/bits/huge_valf.h \
  $(INCDIR)/bits/huge_vall.h \
  $(INCDIR)/bits/ioctl-types.h \
  $(INCDIR)/bits/ioctls.h \
  $(INCDIR)/bits/inf.h \
  $(INCDIR)/bits/local_lim.h \
  $(INCDIR)/bits/locale.h \
  $(INCDIR)/bits/mathcalls.h \
  $(INCDIR)/bits/mathdef.h \
  $(INCDIR)/bits/mathinline.h \
  $(INCDIR)/bits/nan.h \
  $(INCDIR)/bits/poll.h \
  $(INCDIR)/bits/posix_opt.h \
  $(INCDIR)/bits/posix1_lim.h \
  $(INCDIR)/bits/posix2_lim.h \
  $(INCDIR)/bits/pthreadtypes.h \
  $(INCDIR)/bits/sched.h \
  $(INCDIR)/bits/select.h \
  $(INCDIR)/bits/stdio_lim.h \
  $(INCDIR)/bits/setjmp.h \
  $(INCDIR)/bits/sigaction.h \
  $(INCDIR)/bits/sigcontext.h \
  $(INCDIR)/bits/siginfo.h \
  $(INCDIR)/bits/signum.h \
  $(INCDIR)/bits/sigset.h \
  $(INCDIR)/bits/sigstack.h \
  $(INCDIR)/bits/sigthread.h \
  $(INCDIR)/bits/stat.h \
  $(INCDIR)/bits/stdio.h \
  $(INCDIR)/bits/string.h \
  $(INCDIR)/bits/string2.h \
  $(INCDIR)/bits/sys_errlist.h \
  $(INCDIR)/bits/syscall.h \
  $(INCDIR)/bits/time.h \
  $(INCDIR)/bits/types.h \
  $(INCDIR)/bits/typesizes.h \
  $(INCDIR)/bits/uio.h \
  $(INCDIR)/bits/waitflags.h \
  $(INCDIR)/bits/waitstatus.h \
  $(INCDIR)/bits/wchar.h \
  $(INCDIR)/bits/wordsize.h \
  $(INCDIR)/bits/xopen_lim.h \
  $(INCDIR)/gnu/stubs.h \
  $(INCDIR)/sys/cdefs.h \
  $(INCDIR)/sys/ioctl.h \
  $(INCDIR)/sys/poll.h \
  $(INCDIR)/sys/sysmacros.h \
  $(INCDIR)/sys/select.h \
  $(INCDIR)/sys/stat.h \
  $(INCDIR)/sys/syscall.h \
  $(INCDIR)/sys/sysinfo.h \
  $(INCDIR)/sys/time.h \
  $(INCDIR)/sys/ttydefaults.h \
  $(INCDIR)/sys/types.h \
  $(INCDIR)/sys/ucontext.h \
  $(INCDIR)/sys/uio.h \
  $(INCDIR)/_G_config.h \
  $(INCDIR)/alloca.h \
  $(INCDIR)/assert.h \
  $(INCDIR)/config.h \
  $(INCDIR)/ctype.h \
  $(INCDIR)/errno.h \
  $(INCDIR)/endian.h \
  $(INCDIR)/fcntl.h \
  $(INCDIR)/features.h \
  $(INCDIR)/float.h \
  $(INCDIR)/getopt.h \
  $(INCDIR)/libintl.h \
  $(INCDIR)/libio.h \
  $(INCDIR)/limits.h \
  $(INCDIR)/locale.h \
  $(INCDIR)/math.h \
  $(INCDIR)/malloc.h \
  $(INCDIR)/poll.h \
  $(INCDIR)/pthread.h \
  $(INCDIR)/resolv.h \
  $(INCDIR)/sched.h \
  $(INCDIR)/setjmp.h \
  $(INCDIR)/signal.h \
  $(INCDIR)/stdarg.h \
  $(INCDIR)/stdbool.h \
  $(INCDIR)/stdc-predef.h \
  $(INCDIR)/stddef.h \
  $(INCDIR)/stdint.h \
  $(INCDIR)/stdio.h \
  $(INCDIR)/stdlib.h \
  $(INCDIR)/string.h \
  $(INCDIR)/syscall.h \
  $(INCDIR)/unistd.h \
  $(INCDIR)/time.h \
  $(INCDIR)/wchar.h \
  $(INCDIR)/wctype.h \
  $(INCDIR)/xlocale.h \
  include-fixed/limits.h

ASM_SOURCES = \
  glibc-$(GLIBC_VERSION)/sysdeps/x86_64/lshift.S \
  glibc-$(GLIBC_VERSION)/sysdeps/x86_64/mul_1.S \
  glibc-$(GLIBC_VERSION)/sysdeps/x86_64/rshift.S

#  glibc-$(GLIBC_VERSION)/nptl/sysdeps/llamaOS/lowlevellock.c \
#  glibc-$(GLIBC_VERSION)/nptl/sysdeps/llamaOS/pthread_mutex_lock.c \
#  glibc-$(GLIBC_VERSION)/nptl/sysdeps/llamaOS/register-atfork.c \
#  glibc-$(GLIBC_VERSION)/nptl/pthread_mutex_unlock.c \
#  glibc-$(GLIBC_VERSION)/nptl/pthread_once.c \
#  glibc-$(GLIBC_VERSION)/nptl/tpp.c \
#  glibc-$(GLIBC_VERSION)/nptl/vars.c \

C_SOURCES = \
  glibc-$(GLIBC_VERSION)/assert/assert.c \
  glibc-$(GLIBC_VERSION)/csu/dso_handle.c \
  glibc-$(GLIBC_VERSION)/csu/errno-loc.c \
  glibc-$(GLIBC_VERSION)/csu/errno.c \
  glibc-$(GLIBC_VERSION)/ctype/ctype-info.c \
  glibc-$(GLIBC_VERSION)/ctype/ctype.c \
  glibc-$(GLIBC_VERSION)/debug/fortify_fail.c \
  glibc-$(GLIBC_VERSION)/debug/readonly-area.c \
  glibc-$(GLIBC_VERSION)/elf/enbl-secure.c \
  glibc-$(GLIBC_VERSION)/gmon/prof-freq.c \
  glibc-$(GLIBC_VERSION)/gmon/profil.c \
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
  glibc-$(GLIBC_VERSION)/intl/dcgettext.c \
  glibc-$(GLIBC_VERSION)/intl/dcigettext.c \
  glibc-$(GLIBC_VERSION)/intl/explodename.c \
  glibc-$(GLIBC_VERSION)/intl/finddomain.c \
  glibc-$(GLIBC_VERSION)/intl/gettext.c \
  glibc-$(GLIBC_VERSION)/intl/hash-string.c \
  glibc-$(GLIBC_VERSION)/intl/l10nflist.c \
  glibc-$(GLIBC_VERSION)/intl/loadmsgcat.c \
  glibc-$(GLIBC_VERSION)/intl/localealias.c \
  glibc-$(GLIBC_VERSION)/intl/plural-exp.c \
  glibc-$(GLIBC_VERSION)/intl/plural.c \
  glibc-$(GLIBC_VERSION)/io/access.c \
  glibc-$(GLIBC_VERSION)/io/close.c \
  glibc-$(GLIBC_VERSION)/io/fcntl.c \
  glibc-$(GLIBC_VERSION)/io/fxstat.c \
  glibc-$(GLIBC_VERSION)/io/fxstat64.c \
  glibc-$(GLIBC_VERSION)/io/isatty.c \
  glibc-$(GLIBC_VERSION)/io/open.c \
  glibc-$(GLIBC_VERSION)/io/open64.c \
  glibc-$(GLIBC_VERSION)/io/xstat.c \
  glibc-$(GLIBC_VERSION)/io/xstat64.c \
  glibc-$(GLIBC_VERSION)/libio/fcloseall.c \
  glibc-$(GLIBC_VERSION)/libio/filedoalloc.c \
  glibc-$(GLIBC_VERSION)/libio/fileno.c \
  glibc-$(GLIBC_VERSION)/libio/fileops.c \
  glibc-$(GLIBC_VERSION)/libio/fputc.c \
  glibc-$(GLIBC_VERSION)/libio/fputwc.c \
  glibc-$(GLIBC_VERSION)/libio/fseek.c \
  glibc-$(GLIBC_VERSION)/libio/fseeko.c \
  glibc-$(GLIBC_VERSION)/libio/fseeko64.c \
  glibc-$(GLIBC_VERSION)/libio/ftello.c \
  glibc-$(GLIBC_VERSION)/libio/ftello64.c \
  glibc-$(GLIBC_VERSION)/libio/genops.c \
  glibc-$(GLIBC_VERSION)/libio/getc.c \
  glibc-$(GLIBC_VERSION)/libio/getwc.c \
  glibc-$(GLIBC_VERSION)/libio/iofclose.c \
  glibc-$(GLIBC_VERSION)/libio/iofdopen.c \
  glibc-$(GLIBC_VERSION)/libio/iofflush.c \
  glibc-$(GLIBC_VERSION)/libio/iofgets.c \
  glibc-$(GLIBC_VERSION)/libio/iofgets_u.c \
  glibc-$(GLIBC_VERSION)/libio/iofgetws.c \
  glibc-$(GLIBC_VERSION)/libio/iofgetws_u.c \
  glibc-$(GLIBC_VERSION)/libio/iofopen.c \
  glibc-$(GLIBC_VERSION)/libio/iofopen64.c \
  glibc-$(GLIBC_VERSION)/libio/iofputs.c \
  glibc-$(GLIBC_VERSION)/libio/iofputws.c \
  glibc-$(GLIBC_VERSION)/libio/iofread.c \
  glibc-$(GLIBC_VERSION)/libio/iofread_u.c \
  glibc-$(GLIBC_VERSION)/libio/iofwide.c \
  glibc-$(GLIBC_VERSION)/libio/iofwrite.c \
  glibc-$(GLIBC_VERSION)/libio/iogetdelim.c \
  glibc-$(GLIBC_VERSION)/libio/iogetline.c \
  glibc-$(GLIBC_VERSION)/libio/iopadn.c \
  glibc-$(GLIBC_VERSION)/libio/ioseekoff.c \
  glibc-$(GLIBC_VERSION)/libio/iosetvbuf.c \
  glibc-$(GLIBC_VERSION)/libio/ioungetc.c \
  glibc-$(GLIBC_VERSION)/libio/ioungetwc.c \
  glibc-$(GLIBC_VERSION)/libio/iovsprintf.c \
  glibc-$(GLIBC_VERSION)/libio/iovsscanf.c \
  glibc-$(GLIBC_VERSION)/libio/iowpadn.c \
  glibc-$(GLIBC_VERSION)/libio/putc.c \
  glibc-$(GLIBC_VERSION)/libio/putwc.c \
  glibc-$(GLIBC_VERSION)/libio/stdfiles.c \
  glibc-$(GLIBC_VERSION)/libio/stdio.c \
  glibc-$(GLIBC_VERSION)/libio/strops.c \
  glibc-$(GLIBC_VERSION)/libio/vasprintf.c \
  glibc-$(GLIBC_VERSION)/libio/vsnprintf.c \
  glibc-$(GLIBC_VERSION)/libio/wfiledoalloc.c \
  glibc-$(GLIBC_VERSION)/libio/wfileops.c \
  glibc-$(GLIBC_VERSION)/libio/wgenops.c \
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
  glibc-$(GLIBC_VERSION)/locale/coll-lookup.c \
  glibc-$(GLIBC_VERSION)/locale/findlocale.c \
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
  glibc-$(GLIBC_VERSION)/locale/localename.c \
  glibc-$(GLIBC_VERSION)/locale/mb_cur_max.c \
  glibc-$(GLIBC_VERSION)/locale/setlocale.c \
  glibc-$(GLIBC_VERSION)/locale/SYS_libc.c \
  glibc-$(GLIBC_VERSION)/locale/uselocale.c \
  glibc-$(GLIBC_VERSION)/locale/xlocale.c \
  glibc-$(GLIBC_VERSION)/nptl/sysdeps/pthread/flockfile.c \
  glibc-$(GLIBC_VERSION)/nptl/sysdeps/pthread/funlockfile.c \
  glibc-$(GLIBC_VERSION)/nptl/sysdeps/pthread/pthread.c \
  glibc-$(GLIBC_VERSION)/malloc/malloc.c \
  glibc-$(GLIBC_VERSION)/malloc/memusage.c \
  glibc-$(GLIBC_VERSION)/malloc/morecore.c \
  glibc-$(GLIBC_VERSION)/misc/getclktck.c \
  glibc-$(GLIBC_VERSION)/misc/getdtsz.c \
  glibc-$(GLIBC_VERSION)/misc/init-misc.c \
  glibc-$(GLIBC_VERSION)/misc/lseek.c \
  glibc-$(GLIBC_VERSION)/misc/mmap.c \
  glibc-$(GLIBC_VERSION)/misc/mmap64.c \
  glibc-$(GLIBC_VERSION)/misc/mprotect.c \
  glibc-$(GLIBC_VERSION)/misc/munmap.c \
  glibc-$(GLIBC_VERSION)/misc/readv.c \
  glibc-$(GLIBC_VERSION)/misc/sbrk.c \
  glibc-$(GLIBC_VERSION)/misc/tsearch.c \
  glibc-$(GLIBC_VERSION)/posix/environ.c \
  glibc-$(GLIBC_VERSION)/posix/fpathconf.c \
  glibc-$(GLIBC_VERSION)/posix/get_child_max.c \
  glibc-$(GLIBC_VERSION)/posix/getegid.c \
  glibc-$(GLIBC_VERSION)/posix/geteuid.c \
  glibc-$(GLIBC_VERSION)/posix/getgid.c \
  glibc-$(GLIBC_VERSION)/posix/getuid.c \
  glibc-$(GLIBC_VERSION)/posix/pause.c \
  glibc-$(GLIBC_VERSION)/posix/sched_getp.c \
  glibc-$(GLIBC_VERSION)/posix/sched_gets.c \
  glibc-$(GLIBC_VERSION)/posix/sched_setp.c \
  glibc-$(GLIBC_VERSION)/posix/sched_sets.c \
  glibc-$(GLIBC_VERSION)/signal/sigaction.c \
  glibc-$(GLIBC_VERSION)/signal/sigprocmask.c \
  glibc-$(GLIBC_VERSION)/stdio-common/_itoa.c \
  glibc-$(GLIBC_VERSION)/stdio-common/_itowa.c \
  glibc-$(GLIBC_VERSION)/stdio-common/asprintf.c \
  glibc-$(GLIBC_VERSION)/stdio-common/fprintf.c \
  glibc-$(GLIBC_VERSION)/stdio-common/funlockfile.c \
  glibc-$(GLIBC_VERSION)/stdio-common/fxprintf.c \
  glibc-$(GLIBC_VERSION)/stdio-common/itoa-digits.c \
  glibc-$(GLIBC_VERSION)/stdio-common/itoa-udigits.c \
  glibc-$(GLIBC_VERSION)/stdio-common/itowa-digits.c \
  glibc-$(GLIBC_VERSION)/stdio-common/printf-parsemb.c \
  glibc-$(GLIBC_VERSION)/stdio-common/printf-parsewc.c \
  glibc-$(GLIBC_VERSION)/stdio-common/printf.c \
  glibc-$(GLIBC_VERSION)/stdio-common/printf_fp.c \
  glibc-$(GLIBC_VERSION)/stdio-common/printf_fphex.c \
  glibc-$(GLIBC_VERSION)/stdio-common/reg-modifier.c \
  glibc-$(GLIBC_VERSION)/stdio-common/reg-printf.c \
  glibc-$(GLIBC_VERSION)/stdio-common/reg-type.c \
  glibc-$(GLIBC_VERSION)/stdio-common/snprintf.c \
  glibc-$(GLIBC_VERSION)/stdio-common/sprintf.c \
  glibc-$(GLIBC_VERSION)/stdio-common/sscanf.c \
  glibc-$(GLIBC_VERSION)/stdio-common/vfprintf.c \
  glibc-$(GLIBC_VERSION)/stdio-common/vfscanf.c \
  glibc-$(GLIBC_VERSION)/stdio-common/vfwprintf.c \
  glibc-$(GLIBC_VERSION)/stdio-common/vfwscanf.c \
  glibc-$(GLIBC_VERSION)/stdlib/abs.c \
  glibc-$(GLIBC_VERSION)/stdlib/add_n.c \
  glibc-$(GLIBC_VERSION)/stdlib/addmul_1.c \
  glibc-$(GLIBC_VERSION)/stdlib/bsearch.c \
  glibc-$(GLIBC_VERSION)/stdlib/cmp.c \
  glibc-$(GLIBC_VERSION)/stdlib/cxa_atexit.c \
  glibc-$(GLIBC_VERSION)/stdlib/divmod_1.c \
  glibc-$(GLIBC_VERSION)/stdlib/divrem.c \
  glibc-$(GLIBC_VERSION)/stdlib/exit.c \
  glibc-$(GLIBC_VERSION)/stdlib/fpioconst.c \
  glibc-$(GLIBC_VERSION)/stdlib/getenv.c \
  glibc-$(GLIBC_VERSION)/stdlib/grouping.c \
  glibc-$(GLIBC_VERSION)/stdlib/mp_clz_tab.c \
  glibc-$(GLIBC_VERSION)/stdlib/msort.c \
  glibc-$(GLIBC_VERSION)/stdlib/mul.c \
  glibc-$(GLIBC_VERSION)/stdlib/mul_1.c \
  glibc-$(GLIBC_VERSION)/stdlib/mul_n.c \
  glibc-$(GLIBC_VERSION)/stdlib/qsort.c \
  glibc-$(GLIBC_VERSION)/stdlib/setenv.c \
  glibc-$(GLIBC_VERSION)/stdlib/strtod.c \
  glibc-$(GLIBC_VERSION)/stdlib/strtod_l.c \
  glibc-$(GLIBC_VERSION)/stdlib/strtof.c \
  glibc-$(GLIBC_VERSION)/stdlib/strtof_l.c \
  glibc-$(GLIBC_VERSION)/stdlib/strtold.c \
  glibc-$(GLIBC_VERSION)/stdlib/strtold_l.c \
  glibc-$(GLIBC_VERSION)/stdlib/sub_n.c \
  glibc-$(GLIBC_VERSION)/stdlib/submul_1.c \
  glibc-$(GLIBC_VERSION)/stdlib/tens_in_limb.c \
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
  glibc-$(GLIBC_VERSION)/string/memccpy.c \
  glibc-$(GLIBC_VERSION)/string/memchr.c \
  glibc-$(GLIBC_VERSION)/string/memcmp.c \
  glibc-$(GLIBC_VERSION)/string/memcpy.c \
  glibc-$(GLIBC_VERSION)/string/memfrob.c \
  glibc-$(GLIBC_VERSION)/string/memmem.c \
  glibc-$(GLIBC_VERSION)/string/memmove.c \
  glibc-$(GLIBC_VERSION)/string/mempcpy.c \
  glibc-$(GLIBC_VERSION)/string/memrchr.c \
  glibc-$(GLIBC_VERSION)/string/memset.c \
  glibc-$(GLIBC_VERSION)/string/rawmemchr.c \
  glibc-$(GLIBC_VERSION)/string/stpcpy.c \
  glibc-$(GLIBC_VERSION)/string/stpncpy.c \
  glibc-$(GLIBC_VERSION)/string/strcasecmp.c \
  glibc-$(GLIBC_VERSION)/string/strcasecmp_l.c \
  glibc-$(GLIBC_VERSION)/string/strcasestr.c \
  glibc-$(GLIBC_VERSION)/string/strcat.c \
  glibc-$(GLIBC_VERSION)/string/strchr.c \
  glibc-$(GLIBC_VERSION)/string/strchrnul.c \
  glibc-$(GLIBC_VERSION)/string/strcmp.c \
  glibc-$(GLIBC_VERSION)/string/strcoll.c \
  glibc-$(GLIBC_VERSION)/string/strcoll_l.c \
  glibc-$(GLIBC_VERSION)/string/strcpy.c \
  glibc-$(GLIBC_VERSION)/string/strcspn.c \
  glibc-$(GLIBC_VERSION)/string/strdup.c \
  glibc-$(GLIBC_VERSION)/string/strerror.c \
  glibc-$(GLIBC_VERSION)/string/strerror_l.c \
  glibc-$(GLIBC_VERSION)/string/strfry.c \
  glibc-$(GLIBC_VERSION)/string/strlen.c \
  glibc-$(GLIBC_VERSION)/string/strncase.c \
  glibc-$(GLIBC_VERSION)/string/strncase_l.c \
  glibc-$(GLIBC_VERSION)/string/strncat.c \
  glibc-$(GLIBC_VERSION)/string/strncmp.c \
  glibc-$(GLIBC_VERSION)/string/strncpy.c \
  glibc-$(GLIBC_VERSION)/string/strndup.c \
  glibc-$(GLIBC_VERSION)/string/strnlen.c \
  glibc-$(GLIBC_VERSION)/string/strpbrk.c \
  glibc-$(GLIBC_VERSION)/string/strrchr.c \
  glibc-$(GLIBC_VERSION)/string/strsep.c \
  glibc-$(GLIBC_VERSION)/string/strspn.c \
  glibc-$(GLIBC_VERSION)/string/strstr.c \
  glibc-$(GLIBC_VERSION)/string/strtok.c \
  glibc-$(GLIBC_VERSION)/string/strtok_r.c \
  glibc-$(GLIBC_VERSION)/string/strxfrm.c \
  glibc-$(GLIBC_VERSION)/string/strxfrm_l.c \
  glibc-$(GLIBC_VERSION)/sysdeps/ieee754/dbl-64/dbl2mpn.c \
  glibc-$(GLIBC_VERSION)/sysdeps/ieee754/dbl-64/mpn2dbl.c \
  glibc-$(GLIBC_VERSION)/sysdeps/ieee754/dbl-64/s_isinf.c \
  glibc-$(GLIBC_VERSION)/sysdeps/ieee754/dbl-64/s_isnan.c \
  glibc-$(GLIBC_VERSION)/sysdeps/ieee754/dbl-64/s_signbit.c \
  glibc-$(GLIBC_VERSION)/sysdeps/ieee754/flt-32/mpn2flt.c \
  glibc-$(GLIBC_VERSION)/sysdeps/ieee754/ldbl-128/ldbl2mpn.c \
  glibc-$(GLIBC_VERSION)/sysdeps/ieee754/ldbl-128/mpn2ldbl.c \
  glibc-$(GLIBC_VERSION)/sysdeps/ieee754/ldbl-128/s_isinfl.c \
  glibc-$(GLIBC_VERSION)/sysdeps/ieee754/ldbl-128/s_isnanl.c \
  glibc-$(GLIBC_VERSION)/sysdeps/ieee754/ldbl-128/s_signbitl.c \
  glibc-$(GLIBC_VERSION)/sysdeps/llamaos/export/_exit.c \
  glibc-$(GLIBC_VERSION)/sysdeps/llamaos/export/abort.c \
  glibc-$(GLIBC_VERSION)/sysdeps/llamaos/export/brk.c \
  glibc-$(GLIBC_VERSION)/sysdeps/llamaos/export/get_avphys_pages.c \
  glibc-$(GLIBC_VERSION)/sysdeps/llamaos/export/get_nprocs.c \
  glibc-$(GLIBC_VERSION)/sysdeps/llamaos/export/get_nprocs_conf.c \
  glibc-$(GLIBC_VERSION)/sysdeps/llamaos/export/getpagesize.c \
  glibc-$(GLIBC_VERSION)/sysdeps/llamaos/export/get_phys_pages.c \
  glibc-$(GLIBC_VERSION)/sysdeps/llamaos/export/getcwd.c \
  glibc-$(GLIBC_VERSION)/sysdeps/llamaos/export/libc_fatal.c \
  glibc-$(GLIBC_VERSION)/sysdeps/llamaos/export/lseek64.c \
  glibc-$(GLIBC_VERSION)/sysdeps/llamaos/export/libc_open.c \
  glibc-$(GLIBC_VERSION)/sysdeps/llamaos/export/madvise.c \
  glibc-$(GLIBC_VERSION)/sysdeps/llamaos/export/pathconf.c \
  glibc-$(GLIBC_VERSION)/sysdeps/llamaos/export/poll.c \
  glibc-$(GLIBC_VERSION)/sysdeps/llamaos/export/raise.c \
  glibc-$(GLIBC_VERSION)/sysdeps/llamaos/export/read.c \
  glibc-$(GLIBC_VERSION)/sysdeps/llamaos/export/sched_primax.c \
  glibc-$(GLIBC_VERSION)/sysdeps/llamaos/export/sched_primin.c \
  glibc-$(GLIBC_VERSION)/sysdeps/llamaos/export/sigsuspend.c \
  glibc-$(GLIBC_VERSION)/sysdeps/llamaos/export/sigsuspend_nocancel.c \
  glibc-$(GLIBC_VERSION)/sysdeps/llamaos/export/syscall.c \
  glibc-$(GLIBC_VERSION)/sysdeps/llamaos/export/gettimeofday.c \
  glibc-$(GLIBC_VERSION)/sysdeps/llamaos/export/write.c \
  glibc-$(GLIBC_VERSION)/sysdeps/llamaos/export/writev.c \
  glibc-$(GLIBC_VERSION)/sysdeps/llamaos/dl-libc.c \
  glibc-$(GLIBC_VERSION)/sysdeps/llamaos/dl-profstub.c \
  glibc-$(GLIBC_VERSION)/sysdeps/llamaos/dl-support.c \
  glibc-$(GLIBC_VERSION)/sysdeps/llamaos/errlist.c \
  glibc-$(GLIBC_VERSION)/sysdeps/llamaos/init-first.c \
  glibc-$(GLIBC_VERSION)/sysdeps/llamaos/libc_message.c \
  glibc-$(GLIBC_VERSION)/sysdeps/posix/pause.c \
  glibc-$(GLIBC_VERSION)/sysdeps/posix/sysconf.c \
  glibc-$(GLIBC_VERSION)/sysdeps/wordsize-64/strtol.c \
  glibc-$(GLIBC_VERSION)/sysdeps/wordsize-64/strtol_l.c \
  glibc-$(GLIBC_VERSION)/sysdeps/wordsize-64/strtoul.c \
  glibc-$(GLIBC_VERSION)/sysdeps/wordsize-64/strtoul_l.c \
  glibc-$(GLIBC_VERSION)/time/alt_digit.c \
  glibc-$(GLIBC_VERSION)/time/era.c \
  glibc-$(GLIBC_VERSION)/time/lc-time-cleanup.c \
  glibc-$(GLIBC_VERSION)/time/localtime.c \
  glibc-$(GLIBC_VERSION)/time/mktime.c \
  glibc-$(GLIBC_VERSION)/time/offtime.c \
  glibc-$(GLIBC_VERSION)/time/settimeofday.c \
  glibc-$(GLIBC_VERSION)/time/strftime.c \
  glibc-$(GLIBC_VERSION)/time/strftime_l.c \
  glibc-$(GLIBC_VERSION)/time/tzfile.c \
  glibc-$(GLIBC_VERSION)/time/tzset.c \
  glibc-$(GLIBC_VERSION)/time/wcsftime.c \
  glibc-$(GLIBC_VERSION)/time/wcsftime_l.c \
  glibc-$(GLIBC_VERSION)/wcsmbs/btowc.c \
  glibc-$(GLIBC_VERSION)/wcsmbs/mbrlen.c \
  glibc-$(GLIBC_VERSION)/wcsmbs/mbrtowc.c \
  glibc-$(GLIBC_VERSION)/wcsmbs/mbsnrtowcs.c \
  glibc-$(GLIBC_VERSION)/wcsmbs/mbsrtowcs.c \
  glibc-$(GLIBC_VERSION)/wcsmbs/mbsrtowcs_l.c \
  glibc-$(GLIBC_VERSION)/wcsmbs/wcpcpy.c \
  glibc-$(GLIBC_VERSION)/wcsmbs/wcpncpy.c \
  glibc-$(GLIBC_VERSION)/wcsmbs/wcrtomb.c \
  glibc-$(GLIBC_VERSION)/wcsmbs/wcscat.c \
  glibc-$(GLIBC_VERSION)/wcsmbs/wcschr.c \
  glibc-$(GLIBC_VERSION)/wcsmbs/wcschrnul.c \
  glibc-$(GLIBC_VERSION)/wcsmbs/wcscmp.c \
  glibc-$(GLIBC_VERSION)/wcsmbs/wcscoll.c \
  glibc-$(GLIBC_VERSION)/wcsmbs/wcscoll_l.c \
  glibc-$(GLIBC_VERSION)/wcsmbs/wcscpy.c \
  glibc-$(GLIBC_VERSION)/wcsmbs/wcscspn.c \
  glibc-$(GLIBC_VERSION)/wcsmbs/wcsdup.c \
  glibc-$(GLIBC_VERSION)/wcsmbs/wcslen.c \
  glibc-$(GLIBC_VERSION)/wcsmbs/wcsmbsload.c \
  glibc-$(GLIBC_VERSION)/wcsmbs/wcsncase.c \
  glibc-$(GLIBC_VERSION)/wcsmbs/wcsncat.c \
  glibc-$(GLIBC_VERSION)/wcsmbs/wcsncmp.c \
  glibc-$(GLIBC_VERSION)/wcsmbs/wcsncpy.c \
  glibc-$(GLIBC_VERSION)/wcsmbs/wcsnlen.c \
  glibc-$(GLIBC_VERSION)/wcsmbs/wcsnrtombs.c \
  glibc-$(GLIBC_VERSION)/wcsmbs/wcsrtombs.c \
  glibc-$(GLIBC_VERSION)/wcsmbs/wcstol.c \
  glibc-$(GLIBC_VERSION)/wcsmbs/wcstol_l.c \
  glibc-$(GLIBC_VERSION)/wcsmbs/wcstoll.c \
  glibc-$(GLIBC_VERSION)/wcsmbs/wcstoll_l.c \
  glibc-$(GLIBC_VERSION)/wcsmbs/wcsxfrm.c \
  glibc-$(GLIBC_VERSION)/wcsmbs/wcsxfrm_l.c \
  glibc-$(GLIBC_VERSION)/wcsmbs/wctob.c \
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

# are these really needed?
#  glibc-$(GLIBC_VERSION)/setjmp/__longjmp.c \
#  glibc-$(GLIBC_VERSION)/setjmp/longjmp.c \
#  glibc-$(GLIBC_VERSION)/setjmp/setjmp.c \
#  glibc-$(GLIBC_VERSION)/setjmp/sigjmp.c \

# llamaOS export provided
#  glibc-$(GLIBC_VERSION)/io/getcwd.c \
#  glibc-$(GLIBC_VERSION)/io/lseek64.c \
#  glibc-$(GLIBC_VERSION)/io/poll.c \
#  glibc-$(GLIBC_VERSION)/io/read.c \
#  glibc-$(GLIBC_VERSION)/io/write.c \
#  glibc-$(GLIBC_VERSION)/misc/brk.c \
#  glibc-$(GLIBC_VERSION)/misc/getpagesize.c \
#  glibc-$(GLIBC_VERSION)/misc/getsysstats.c \
#  glibc-$(GLIBC_VERSION)/misc/madvise.c \
#  glibc-$(GLIBC_VERSION)/misc/syscall.c \
#  glibc-$(GLIBC_VERSION)/misc/writev.c \
#  glibc-$(GLIBC_VERSION)/posix/_exit.c \
#  glibc-$(GLIBC_VERSION)/posix/pathconf.c \
#  glibc-$(GLIBC_VERSION)/posix/sched_primax.c \
#  glibc-$(GLIBC_VERSION)/posix/sched_primin.c \
#  glibc-$(GLIBC_VERSION)/stdlib/abort.c \
#  glibc-$(GLIBC_VERSION)/signal/raise.c \
#  glibc-$(GLIBC_VERSION)/signal/sigsuspend.c \
#  glibc-$(GLIBC_VERSION)/time/gettimeofday.c \

# are these really needed? 
#  glibc-$(GLIBC_VERSION)/sysdeps/llamaos/abort.c \
#  glibc-$(GLIBC_VERSION)/sysdeps/llamaos/libc-fatal.c \
#  glibc-$(GLIBC_VERSION)/sysdeps/llamaos/libc_open.c \
#  glibc-$(GLIBC_VERSION)/sysdeps/llamaos/sigsuspend.c \

OBJECTS  = $(ASM_SOURCES:%.S=$(OBJDIR)/%.o)
OBJECTS += $(C_SOURCES:%.c=$(OBJDIR)/%.o)

.PHONY: all
all : $(LIBDIR)/glibc.a $(HEADERS)

$(LIBDIR)/glibc.a: $(OBJECTS)
	@[ -d $(@D) ] || (mkdir -p $(@D))
	@echo linking: $@
	@$(AR) r $@ $(OBJECTS)
	@echo successfully built: $@
	@echo

$(INCDIR)/% : $(SRCDIR)/glibc-$(GLIBC_VERSION)/sysdeps/llamaos/%
	@[ -d $(@D) ] || (mkdir -p $(@D))
	@echo copying: $@ from $<
	cp $< $@

$(INCDIR)/% : $(SRCDIR)/glibc-$(GLIBC_VERSION)/sysdeps/ieee754/ldbl-128/%
	@[ -d $(@D) ] || (mkdir -p $(@D))
	@echo copying: $@ from $<
	cp $< $@

$(INCDIR)/% : $(SRCDIR)/glibc-$(GLIBC_VERSION)/sysdeps/ieee754/%
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

$(INCDIR)/% : $(SRCDIR)/glibc-$(GLIBC_VERSION)/sysdeps/i386/%
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

$(INCDIR)/% : $(SRCDIR)/glibc-$(GLIBC_VERSION)/ctype/%
	@[ -d $(@D) ] || (mkdir -p $(@D))
	@echo copying: $@ from $<
	cp $< $@

$(INCDIR)/% : $(SRCDIR)/glibc-$(GLIBC_VERSION)/io/%
	@[ -d $(@D) ] || (mkdir -p $(@D))
	@echo copying: $@ from $<
	cp $< $@

$(INCDIR)/% : $(SRCDIR)/glibc-$(GLIBC_VERSION)/intl/%
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

$(INCDIR)/% : $(SRCDIR)/glibc-$(GLIBC_VERSION)/math/%
	@[ -d $(@D) ] || (mkdir -p $(@D))
	@echo copying: $@ from $<
	cp $< $@

$(INCDIR)/% : $(SRCDIR)/glibc-$(GLIBC_VERSION)/malloc/%
	@[ -d $(@D) ] || (mkdir -p $(@D))
	@echo copying: $@ from $<
	cp $< $@

$(INCDIR)/% : $(SRCDIR)/glibc-$(GLIBC_VERSION)/misc/%
	@[ -d $(@D) ] || (mkdir -p $(@D))
	@echo copying: $@ from $<
	cp $< $@

$(INCDIR)/% : $(SRCDIR)/glibc-$(GLIBC_VERSION)/nptl/sysdeps/llamaOS/x86/%
	@[ -d $(@D) ] || (mkdir -p $(@D))
	@echo copying: $@ from $<
	cp $< $@

$(INCDIR)/% : $(SRCDIR)/glibc-$(GLIBC_VERSION)/nptl/sysdeps/pthread/%
	@[ -d $(@D) ] || (mkdir -p $(@D))
	@echo copying: $@ from $<
	cp $< $@

$(INCDIR)/% : $(SRCDIR)/glibc-$(GLIBC_VERSION)/posix/%
	@[ -d $(@D) ] || (mkdir -p $(@D))
	@echo copying: $@ from $<
	cp $< $@

$(INCDIR)/% : $(SRCDIR)/glibc-$(GLIBC_VERSION)/resolv/%
	@[ -d $(@D) ] || (mkdir -p $(@D))
	@echo copying: $@ from $<
	cp $< $@

$(INCDIR)/% : $(SRCDIR)/glibc-$(GLIBC_VERSION)/setjmp/%
	@[ -d $(@D) ] || (mkdir -p $(@D))
	@echo copying: $@ from $<
	cp $< $@

$(INCDIR)/% : $(SRCDIR)/glibc-$(GLIBC_VERSION)/signal/%
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

$(INCDIR)/% : $(SRCDIR)/glibc-$(GLIBC_VERSION)/%
	@[ -d $(@D) ] || (mkdir -p $(@D))
	@echo copying: $@ from $<
	cp $< $@

#$(INCDIR)/% : $(SRCDIR)/glibc-$(GLIBC_VERSION)/include/%
#	@[ -d $(@D) ] || (mkdir -p $(@D))
#	@echo copying: $@ from $<
#	cp $< $@

$(INCDIR)/asm/% : $(SRCDIR)/glibc-$(GLIBC_VERSION)/include/asm/%
	@[ -d $(@D) ] || (mkdir -p $(@D))
	@echo copying: $@ from $<
	cp $< $@

$(INCDIR)/bits/xopen_lim.h : $(SRCDIR)/glibc-$(GLIBC_VERSION)/include/bits/xopen_lim.h
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

$(INCDIR)/limits.h : $(SRCDIR)/glibc-$(GLIBC_VERSION)/include/limits.h
	@[ -d $(@D) ] || (mkdir -p $(@D))
	@echo copying: $@ from $<
	cp $< $@

$(INCDIR)/stdc-predef.h : $(SRCDIR)/glibc-$(GLIBC_VERSION)/include/stdc-predef.h
	@[ -d $(@D) ] || (mkdir -p $(@D))
	@echo copying: $@ from $<
	cp $< $@

# get a few files from the gcc source
$(INCDIR)/% : $(SRCDIR)/gcc-$(GCC_VERSION)/gcc/ginclude/%
	@[ -d $(@D) ] || (mkdir -p $(@D))
	@echo copying: $@ from $<
	cp $< $@

include-fixed/% : $(SRCDIR)/gcc-$(GCC_VERSION)/gcc/include-fixed/%
	@[ -d $(@D) ] || (mkdir -p $(@D))
	@echo copying: $@ from $<
	cp $< $@

include rules.mk

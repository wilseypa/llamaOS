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

# requires this to already be included
# include common.mk

# MAKEFILE_SOURCES += glibc-obj-$(GLIBC_VERSION).mk

#  glibc-$(GLIBC_VERSION)/nptl/sysdeps/llamaOS/x86_64/lowlevellock.S \
#  glibc-$(GLIBC_VERSION)/nptl/sysdeps/llamaOS/x86_64/lowlevelrobustlock.S \

#  glibc-$(GLIBC_VERSION)/nptl/sysdeps/llamaOS/libc_multiple_threads.c \
#  glibc-$(GLIBC_VERSION)/nptl/sysdeps/llamaOS/lowlevellock.c \
#  glibc-$(GLIBC_VERSION)/nptl/sysdeps/llamaOS/x86_64/fork.c \
#  glibc-$(GLIBC_VERSION)/nptl/sysdeps/llamaOS/pthread_mutex_condition_lock.c \
#  glibc-$(GLIBC_VERSION)/nptl/sysdeps/llamaOS/register-atfork.c \
#  glibc-$(GLIBC_VERSION)/nptl/nptl-init.c \
#  glibc-$(GLIBC_VERSION)/nptl/tpp.c \
#  glibc-$(GLIBC_VERSION)/nptl/vars.c \

GLIBC_SOURCES_ASM = \
  glibc-$(GLIBC_VERSION)/sysdeps/x86_64/lshift.S \
  glibc-$(GLIBC_VERSION)/sysdeps/x86_64/mul_1.S \
  glibc-$(GLIBC_VERSION)/sysdeps/x86_64/rshift.S

#  glibc-$(GLIBC_VERSION)/sysdeps/x86_64/__longjmp.S \
#  glibc-$(GLIBC_VERSION)/sysdeps/x86_64/setjmp.S
#  glibc-$(GLIBC_VERSION)/elf/dl-load.c \
#  glibc-$(GLIBC_VERSION)/csu/libc-tls.c \

#  glibc-$(GLIBC_VERSION)/dlfcn/dlerror.c \
#  glibc-$(GLIBC_VERSION)/dlfcn/dlopen.c \
#  glibc-$(GLIBC_VERSION)/elf/dl-close.c \
#  glibc-$(GLIBC_VERSION)/elf/dl-error.c \
#  glibc-$(GLIBC_VERSION)/elf/dl-execstack.c \
#  glibc-$(GLIBC_VERSION)/elf/dl-libc.c \
#  glibc-$(GLIBC_VERSION)/elf/dl-lookup.c \
#  glibc-$(GLIBC_VERSION)/elf/dl-misc.c \
#  glibc-$(GLIBC_VERSION)/elf/dl-open.c \
#  glibc-$(GLIBC_VERSION)/elf/dl-profile.c \
#  glibc-$(GLIBC_VERSION)/elf/dl-profstub.c \
#  glibc-$(GLIBC_VERSION)/elf/dl-reloc.c \
#  glibc-$(GLIBC_VERSION)/elf/dl-support.c \

GLIBC_SOURCES_C = \
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
  glibc-$(GLIBC_VERSION)/io/getcwd.c \
  glibc-$(GLIBC_VERSION)/io/isatty.c \
  glibc-$(GLIBC_VERSION)/io/lseek64.c \
  glibc-$(GLIBC_VERSION)/io/open.c \
  glibc-$(GLIBC_VERSION)/io/open64.c \
  glibc-$(GLIBC_VERSION)/io/poll.c \
  glibc-$(GLIBC_VERSION)/io/read.c \
  glibc-$(GLIBC_VERSION)/io/write.c \
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
  glibc-$(GLIBC_VERSION)/malloc/malloc.c \
  glibc-$(GLIBC_VERSION)/malloc/memusage.c \
  glibc-$(GLIBC_VERSION)/malloc/morecore.c \
  glibc-$(GLIBC_VERSION)/misc/brk.c \
  glibc-$(GLIBC_VERSION)/misc/getclktck.c \
  glibc-$(GLIBC_VERSION)/misc/getdtsz.c \
  glibc-$(GLIBC_VERSION)/misc/getpagesize.c \
  glibc-$(GLIBC_VERSION)/misc/getsysstats.c \
  glibc-$(GLIBC_VERSION)/misc/madvise.c \
  glibc-$(GLIBC_VERSION)/misc/init-misc.c \
  glibc-$(GLIBC_VERSION)/misc/lseek.c \
  glibc-$(GLIBC_VERSION)/misc/mmap.c \
  glibc-$(GLIBC_VERSION)/misc/mmap64.c \
  glibc-$(GLIBC_VERSION)/misc/mprotect.c \
  glibc-$(GLIBC_VERSION)/misc/munmap.c \
  glibc-$(GLIBC_VERSION)/misc/readv.c \
  glibc-$(GLIBC_VERSION)/misc/sbrk.c \
  glibc-$(GLIBC_VERSION)/misc/syscall.c \
  glibc-$(GLIBC_VERSION)/misc/tsearch.c \
  glibc-$(GLIBC_VERSION)/misc/writev.c \
  glibc-$(GLIBC_VERSION)/nptl/sysdeps/llamaOS/lowlevellock.c \
  glibc-$(GLIBC_VERSION)/nptl/sysdeps/llamaOS/register-atfork.c \
  glibc-$(GLIBC_VERSION)/nptl/sysdeps/pthread/flockfile.c \
  glibc-$(GLIBC_VERSION)/nptl/sysdeps/pthread/funlockfile.c \
  glibc-$(GLIBC_VERSION)/nptl/pthread_mutex_lock.c \
  glibc-$(GLIBC_VERSION)/nptl/pthread_mutex_unlock.c \
  glibc-$(GLIBC_VERSION)/nptl/pthread_once.c \
  glibc-$(GLIBC_VERSION)/nptl/tpp.c \
  glibc-$(GLIBC_VERSION)/nptl/vars.c \
  glibc-$(GLIBC_VERSION)/posix/_exit.c \
  glibc-$(GLIBC_VERSION)/posix/environ.c \
  glibc-$(GLIBC_VERSION)/posix/fpathconf.c \
  glibc-$(GLIBC_VERSION)/posix/get_child_max.c \
  glibc-$(GLIBC_VERSION)/posix/getegid.c \
  glibc-$(GLIBC_VERSION)/posix/geteuid.c \
  glibc-$(GLIBC_VERSION)/posix/getgid.c \
  glibc-$(GLIBC_VERSION)/posix/getuid.c \
  glibc-$(GLIBC_VERSION)/posix/pathconf.c \
  glibc-$(GLIBC_VERSION)/posix/pause.c \
  glibc-$(GLIBC_VERSION)/posix/sched_getp.c \
  glibc-$(GLIBC_VERSION)/posix/sched_gets.c \
  glibc-$(GLIBC_VERSION)/posix/sched_primax.c \
  glibc-$(GLIBC_VERSION)/posix/sched_primin.c \
  glibc-$(GLIBC_VERSION)/posix/sched_setp.c \
  glibc-$(GLIBC_VERSION)/posix/sched_sets.c \
  glibc-$(GLIBC_VERSION)/setjmp/__longjmp.c \
  glibc-$(GLIBC_VERSION)/setjmp/longjmp.c \
  glibc-$(GLIBC_VERSION)/setjmp/setjmp.c \
  glibc-$(GLIBC_VERSION)/setjmp/sigjmp.c \
  glibc-$(GLIBC_VERSION)/signal/raise.c \
  glibc-$(GLIBC_VERSION)/signal/sigaction.c \
  glibc-$(GLIBC_VERSION)/signal/sigprocmask.c \
  glibc-$(GLIBC_VERSION)/signal/sigsuspend.c \
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
  glibc-$(GLIBC_VERSION)/stdlib/abort.c \
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
  glibc-$(GLIBC_VERSION)/sysdeps/llamaos/abort.c \
  glibc-$(GLIBC_VERSION)/sysdeps/llamaos/dl-libc.c \
  glibc-$(GLIBC_VERSION)/sysdeps/llamaos/dl-profstub.c \
  glibc-$(GLIBC_VERSION)/sysdeps/llamaos/dl-support.c \
  glibc-$(GLIBC_VERSION)/sysdeps/llamaos/errlist.c \
  glibc-$(GLIBC_VERSION)/sysdeps/llamaos/errno.c \
  glibc-$(GLIBC_VERSION)/sysdeps/llamaos/init-first.c \
  glibc-$(GLIBC_VERSION)/sysdeps/llamaos/libc-fatal.c \
  glibc-$(GLIBC_VERSION)/sysdeps/llamaos/libc_open.c \
  glibc-$(GLIBC_VERSION)/sysdeps/llamaos/sigsuspend.c \
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


GLIBC_OBJECTS  = $(GLIBC_SOURCES_ASM:%.S=$(OBJDIR)/%.o)
GLIBC_OBJECTS += $(GLIBC_SOURCES_C:%.c=$(OBJDIR)/%.o)

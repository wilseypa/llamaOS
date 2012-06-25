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

LLAMAOS_SOURCES_C = \
  glibc-2.15/csu/libc-tls.c \
  glibc-2.15/debug/fortify_fail.c \
  glibc-2.15/elf/dl-debug.c \
  glibc-2.15/elf/dl-error.c \
  glibc-2.15/elf/dl-load.c \
  glibc-2.15/elf/dl-misc.c \
  glibc-2.15/elf/dl-object.c \
  glibc-2.15/elf/dl-profile.c \
  glibc-2.15/elf/dl-profstub.c \
  glibc-2.15/elf/dl-support.c \
  glibc-2.15/elf/dl-tls.c \
  glibc-2.15/gmon/prof-freq.c \
  glibc-2.15/gmon/profil.c \
  glibc-2.15/io/close.c \
  glibc-2.15/io/fxstat.c \
  glibc-2.15/io/fxstat64.c \
  glibc-2.15/io/isatty.c \
  glibc-2.15/io/open.c \
  glibc-2.15/io/read.c \
  glibc-2.15/io/write.c \
  glibc-2.15/io/xstat.c \
  glibc-2.15/io/xstat64.c \
  glibc-2.15/libio/filedoalloc.c \
  glibc-2.15/libio/fileops.c \
  glibc-2.15/libio/genops.c \
  glibc-2.15/libio/iofflush.c \
  glibc-2.15/libio/iofwide.c \
  glibc-2.15/libio/iovsprintf.c \
  glibc-2.15/libio/stdfiles.c \
  glibc-2.15/libio/stdio.c \
  glibc-2.15/libio/strops.c \
  glibc-2.15/libio/vsnprintf.c \
  glibc-2.15/libio/wfileops.c \
  glibc-2.15/libio/wgenops.c \
  glibc-2.15/locale/xlocale.c \
  glibc-2.15/malloc/malloc.c \
  glibc-2.15/malloc/morecore.c \
  glibc-2.15/misc/brk.c \
  glibc-2.15/misc/getpagesize.c \
  glibc-2.15/misc/init-misc.c \
  glibc-2.15/misc/lseek.c \
  glibc-2.15/misc/madvise.c \
  glibc-2.15/misc/mmap.c \
  glibc-2.15/misc/munmap.c \
  glibc-2.15/misc/sbrk.c \
  glibc-2.15/misc/writev.c \
  glibc-2.15/posix/getpid.c \
  glibc-2.15/stdio-common/_itoa.c \
  glibc-2.15/stdio-common/_itowa.c \
  glibc-2.15/stdio-common/asprintf.c \
  glibc-2.15/stdio-common/fxprintf.c \
  glibc-2.15/stdio-common/itoa-digits.c \
  glibc-2.15/stdio-common/itoa-udigits.c \
  glibc-2.15/stdio-common/itowa-digits.c \
  glibc-2.15/stdio-common/snprintf.c \
  glibc-2.15/stdio-common/vfprintf.c \
  glibc-2.15/stdlib/exit.c \
  glibc-2.15/stdlib/getenv.c \
  glibc-2.15/stdlib/setenv.c \
  glibc-2.15/stdlib/strtol.c \
  glibc-2.15/stdlib/strtol_l.c \
  glibc-2.15/string/_strerror.c \
  glibc-2.15/string/memccpy.c \
  glibc-2.15/string/memchr.c \
  glibc-2.15/string/memcmp.c \
  glibc-2.15/string/memcpy.c \
  glibc-2.15/string/memfrob.c \
  glibc-2.15/string/memmem.c \
  glibc-2.15/string/memmove.c \
  glibc-2.15/string/mempcpy.c \
  glibc-2.15/string/memrchr.c \
  glibc-2.15/string/memset.c \
  glibc-2.15/string/rawmemchr.c \
  glibc-2.15/string/stpcpy.c \
  glibc-2.15/string/strcasecmp.c \
  glibc-2.15/string/strcasecmp_l.c \
  glibc-2.15/string/strcasestr.c \
  glibc-2.15/string/strcat.c \
  glibc-2.15/string/strchr.c \
  glibc-2.15/string/strchrnul.c \
  glibc-2.15/string/strcmp.c \
  glibc-2.15/string/strcoll.c \
  glibc-2.15/string/strcoll_l.c \
  glibc-2.15/string/strcpy.c \
  glibc-2.15/string/strcspn.c \
  glibc-2.15/string/strdup.c \
  glibc-2.15/string/strerror.c \
  glibc-2.15/string/strerror_l.c \
  glibc-2.15/string/strlen.c \
  glibc-2.15/string/strerror.c \
  glibc-2.15/string/strncase.c \
  glibc-2.15/string/strncase_l.c \
  glibc-2.15/string/strncat.c \
  glibc-2.15/string/strncmp.c \
  glibc-2.15/string/strncpy.c \
  glibc-2.15/string/strndup.c \
  glibc-2.15/string/strnlen.c \
  glibc-2.15/string/strpbrk.c \
  glibc-2.15/string/strrchr.c \
  glibc-2.15/string/strspn.c \
  glibc-2.15/string/strstr.c \
  glibc-2.15/string/strtok.c \
  glibc-2.15/string/strtok_r.c \
  glibc-2.15/string/wordcopy.c \
  glibc-2.15/sysdeps/llamaos/assert.c \
  glibc-2.15/sysdeps/llamaos/errno.c \
  glibc-2.15/sysdeps/llamaos/flockfile.c \
  glibc-2.15/sysdeps/llamaos/funlockfile.c \
  glibc-2.15/wcsmbs/wcsmbsload.c \
  glibc-2.15/wcsmbs/wmemchr.c \
  glibc-2.15/wcsmbs/wmemcmp.c \
  glibc-2.15/wcsmbs/wmemcpy.c \
  glibc-2.15/wcsmbs/wmemmove.c \
  glibc-2.15/wcsmbs/wmempcpy.c \
  glibc-2.15/wcsmbs/wmemset.c

LLAMAOS_SOURCES_CPP = \
  llamaos/xen/kernel.cpp \
  llamaos/xen/trace.cpp

LLAMAOS_OBJECTS  = $(LLAMAOS_SOURCES_C:%.c=$(OBJDIR)/%.o)
LLAMAOS_OBJECTS += $(LLAMAOS_SOURCES_CPP:%.cpp=$(OBJDIR)/%.o)

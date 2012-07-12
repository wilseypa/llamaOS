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

MAKEFILE_SOURCES += glibc-obj-$(GLIBC_VERSION).mk

GLIBC_SOURCES_C = \
  glibc-$(GLIBC_VERSION)/ctype/ctype-info.c \
  glibc-$(GLIBC_VERSION)/ctype/ctype.c \
  glibc-$(GLIBC_VERSION)/libio/stdio.c \
  glibc-$(GLIBC_VERSION)/libio/vsnprintf.c \
  glibc-$(GLIBC_VERSION)/locale/setlocale.c \
  glibc-$(GLIBC_VERSION)/nptl/pthread_once.c \
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
  glibc-$(GLIBC_VERSION)/sysdeps/llamaos/abort.c \
  glibc-$(GLIBC_VERSION)/sysdeps/llamaos/init-first.c \
  glibc-$(GLIBC_VERSION)/wcsmbs/wmemchr.c \
  glibc-$(GLIBC_VERSION)/wcsmbs/wmemcmp.c \
  glibc-$(GLIBC_VERSION)/wcsmbs/wmemcpy.c \
  glibc-$(GLIBC_VERSION)/wcsmbs/wmemmove.c \
  glibc-$(GLIBC_VERSION)/wcsmbs/wmempcpy.c \
  glibc-$(GLIBC_VERSION)/wcsmbs/wmemset.c \
  glibc-$(GLIBC_VERSION)/wctype/wctype.c

GLIBC_OBJECTS  = $(GLIBC_SOURCES_C:%.c=$(OBJDIR)/%.o)

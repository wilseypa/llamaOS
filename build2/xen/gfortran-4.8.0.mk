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

MAKEFILE_SOURCES += gfortran-$(GCC_VERSION).mk

# -iquote/usr/src/gcc-4.8.0/libgfortran/io
CFLAGS += \
  -DHAVE_CONFIG_H \
  -Wall \
  -Wstrict-prototypes \
  -Wmissing-prototypes \
  -Wold-style-definition \
  -Wextra \
  -Wwrite-strings \
  -fcx-fortran-rules \
  -I $(SRCDIR)/gcc-$(GCC_VERSION)/libgfortran \
  -I $(SRCDIR)/gcc-$(GCC_VERSION)/gcc \
  -I $(SRCDIR)/gcc-$(GCC_VERSION)/gcc/config \
  -I $(SRCDIR)/gcc-$(GCC_VERSION)/libquadmath \
  -I $(SRCDIR)/gcc-$(GCC_VERSION)/libgcc \
  -I $(INCDIR)

VPATH = $(SRCDIR)

SOURCES = \
  gcc-$(GCC_VERSION)/libgfortran/runtime/backtrace.c \
  gcc-$(GCC_VERSION)/libgfortran/runtime/bounds.c \
  gcc-$(GCC_VERSION)/libgfortran/runtime/compile_options.c \
  gcc-$(GCC_VERSION)/libgfortran/runtime/convert_char.c \
  gcc-$(GCC_VERSION)/libgfortran/runtime/environ.c \
  gcc-$(GCC_VERSION)/libgfortran/runtime/error.c \
  gcc-$(GCC_VERSION)/libgfortran/runtime/fpu.c \
  gcc-$(GCC_VERSION)/libgfortran/runtime/main.c \
  gcc-$(GCC_VERSION)/libgfortran/runtime/memory.c \
  gcc-$(GCC_VERSION)/libgfortran/runtime/pause.c \
  gcc-$(GCC_VERSION)/libgfortran/runtime/select.c \
  gcc-$(GCC_VERSION)/libgfortran/runtime/stop.c \
  gcc-$(GCC_VERSION)/libgfortran/runtime/string.c

OBJECTS  = $(SOURCES:%.c=$(OBJDIR)/%.o)
DEPENDS += $(OBJECTS:%.o=%.d)

.PHONY: all
all : $(LIBDIR)/gfortran.a

$(LIBDIR)/gfortran.a: $(OBJECTS)
	@[ -d $(@D) ] || (mkdir -p $(@D))
	@echo linking: $@
	@$(AR) r $@ $(OBJECTS)
	@echo successfully built: $@
	@echo

include rules.mk

# include auto-generated dependencies
-include $(DEPENDS)





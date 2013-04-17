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

MAKEFILE_SOURCES += gcc-$(GCC_VERSION).mk

# gcc-4.7.1 doesn't know this one
#  -mlong-double-80
CFLAGS += \
  -DIN_GCC \
  -DIN_LIBGCC2 \
  -fbuilding-libgcc \
  -fno-stack-protector \
  -fexceptions \
  -fvisibility=hidden \
  -I $(SRCDIR)/gcc-$(GCC_VERSION)/gcc \
  -I $(SRCDIR)/gcc-$(GCC_VERSION)/libgcc \
  -I $(SRCDIR)/gcc-$(GCC_VERSION)/include \
  -I $(SRCDIR)/gcc-$(GCC_VERSION)/libgcc/config/libbid \
  -I $(SRCDIR)/gcc-$(GCC_VERSION)/gcc/config/spu \
  -I $(SRCDIR)/gcc-$(GCC_VERSION)/libcpp/include \
  -I $(INCDIR) \
  -include $(SRCDIR)/llamaos/__thread.h

VPATH = $(SRCDIR)

SOURCES = \
  gcc-$(GCC_VERSION)/libgcc/soft-fp/addtf3.c \
  gcc-$(GCC_VERSION)/libgcc/soft-fp/divtf3.c \
  gcc-$(GCC_VERSION)/libgcc/soft-fp/eqtf2.c \
  gcc-$(GCC_VERSION)/libgcc/soft-fp/floatunditf.c \
  gcc-$(GCC_VERSION)/libgcc/soft-fp/getf2.c \
  gcc-$(GCC_VERSION)/libgcc/soft-fp/letf2.c \
  gcc-$(GCC_VERSION)/libgcc/soft-fp/multf3.c \
  gcc-$(GCC_VERSION)/libgcc/soft-fp/subtf3.c \
  gcc-$(GCC_VERSION)/libgcc/soft-fp/trunctfdf2.c \
  gcc-$(GCC_VERSION)/libgcc/soft-fp/unordtf2.c \
  gcc-$(GCC_VERSION)/libgcc/config/i386/sfp-exceptions.c \
  gcc-$(GCC_VERSION)/libgcc/config/spu/divmodti4.c \
  gcc-$(GCC_VERSION)/libgcc/udivmodsi4.c \
  gcc-$(GCC_VERSION)/libgcc/unwind-dw2-fde.c \
  gcc-$(GCC_VERSION)/libgcc/unwind-dw2.c

HEADERS = 

OBJECTS  = $(SOURCES:%.c=$(OBJDIR)/%.o)
DEPENDS += $(OBJECTS:%.o=%.d)

.PHONY: all
all : $(LIBDIR)/gcc.a $(HEADERS)

$(LIBDIR)/gcc.a: $(OBJECTS)
	@[ -d $(@D) ] || (mkdir -p $(@D))
	@echo linking: $@
	@$(AR) r $@ $(OBJECTS)
	@echo successfully built: $@
	@echo

include rules.mk

# include auto-generated dependencies
-include $(DEPENDS)

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
  -U_FORTIFY_SOURCE \
  -D__USE_FORTIFY_LEVEL=0 \
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

# add gcc functions embedded in libgcc2.c
OBJECTS += $(OBJDIR)/gcc-$(GCC_VERSION)/libgcc/libgcc2/muldi3.o \
           $(OBJDIR)/gcc-$(GCC_VERSION)/libgcc/libgcc2/negdi2.o \
           $(OBJDIR)/gcc-$(GCC_VERSION)/libgcc/libgcc2/lshrdi3.o \
           $(OBJDIR)/gcc-$(GCC_VERSION)/libgcc/libgcc2/ashldi3.o \
           $(OBJDIR)/gcc-$(GCC_VERSION)/libgcc/libgcc2/ashrdi3.o \
           $(OBJDIR)/gcc-$(GCC_VERSION)/libgcc/libgcc2/cmpdi2.o \
           $(OBJDIR)/gcc-$(GCC_VERSION)/libgcc/libgcc2/ucmpdi2.o \
           $(OBJDIR)/gcc-$(GCC_VERSION)/libgcc/libgcc2/clear_cache.o \
           $(OBJDIR)/gcc-$(GCC_VERSION)/libgcc/libgcc2/trampoline.o \
           $(OBJDIR)/gcc-$(GCC_VERSION)/libgcc/libgcc2/absvsi2.o \
           $(OBJDIR)/gcc-$(GCC_VERSION)/libgcc/libgcc2/absvdi2.o \
           $(OBJDIR)/gcc-$(GCC_VERSION)/libgcc/libgcc2/addvsi3.o \
           $(OBJDIR)/gcc-$(GCC_VERSION)/libgcc/libgcc2/addvdi3.o \
           $(OBJDIR)/gcc-$(GCC_VERSION)/libgcc/libgcc2/subvsi3.o \
           $(OBJDIR)/gcc-$(GCC_VERSION)/libgcc/libgcc2/subvdi3.o \
           $(OBJDIR)/gcc-$(GCC_VERSION)/libgcc/libgcc2/mulvsi3.o \
           $(OBJDIR)/gcc-$(GCC_VERSION)/libgcc/libgcc2/mulvdi3.o \
           $(OBJDIR)/gcc-$(GCC_VERSION)/libgcc/libgcc2/negvsi2.o \
           $(OBJDIR)/gcc-$(GCC_VERSION)/libgcc/libgcc2/negvdi2.o \
           $(OBJDIR)/gcc-$(GCC_VERSION)/libgcc/libgcc2/ffssi2.o \
           $(OBJDIR)/gcc-$(GCC_VERSION)/libgcc/libgcc2/ffsdi2.o \
           $(OBJDIR)/gcc-$(GCC_VERSION)/libgcc/libgcc2/clzsi2.o \
           $(OBJDIR)/gcc-$(GCC_VERSION)/libgcc/libgcc2/clzdi2.o \
           $(OBJDIR)/gcc-$(GCC_VERSION)/libgcc/libgcc2/ctzsi2.o \
           $(OBJDIR)/gcc-$(GCC_VERSION)/libgcc/libgcc2/ctzdi2.o \
           $(OBJDIR)/gcc-$(GCC_VERSION)/libgcc/libgcc2/popcount_tab.o \
           $(OBJDIR)/gcc-$(GCC_VERSION)/libgcc/libgcc2/popcountsi2.o \
           $(OBJDIR)/gcc-$(GCC_VERSION)/libgcc/libgcc2/popcountdi2.o \
           $(OBJDIR)/gcc-$(GCC_VERSION)/libgcc/libgcc2/paritysi2.o \
           $(OBJDIR)/gcc-$(GCC_VERSION)/libgcc/libgcc2/paritydi2.o \
           $(OBJDIR)/gcc-$(GCC_VERSION)/libgcc/libgcc2/powisf2.o \
           $(OBJDIR)/gcc-$(GCC_VERSION)/libgcc/libgcc2/powidf2.o \
           $(OBJDIR)/gcc-$(GCC_VERSION)/libgcc/libgcc2/powixf2.o \
           $(OBJDIR)/gcc-$(GCC_VERSION)/libgcc/libgcc2/mulsc3.o \
           $(OBJDIR)/gcc-$(GCC_VERSION)/libgcc/libgcc2/muldc3.o \
           $(OBJDIR)/gcc-$(GCC_VERSION)/libgcc/libgcc2/mulxc3.o \
           $(OBJDIR)/gcc-$(GCC_VERSION)/libgcc/libgcc2/divsc3.o \
           $(OBJDIR)/gcc-$(GCC_VERSION)/libgcc/libgcc2/divdc3.o \
           $(OBJDIR)/gcc-$(GCC_VERSION)/libgcc/libgcc2/divxc3.o \
           $(OBJDIR)/gcc-$(GCC_VERSION)/libgcc/libgcc2/bswapsi2.o \
           $(OBJDIR)/gcc-$(GCC_VERSION)/libgcc/libgcc2/bswapdi2.o \
           $(OBJDIR)/gcc-$(GCC_VERSION)/libgcc/libgcc2/clrsbsi2.o \
           $(OBJDIR)/gcc-$(GCC_VERSION)/libgcc/libgcc2/clrsbdi2.o \
           $(OBJDIR)/gcc-$(GCC_VERSION)/libgcc/libgcc2/fixunssfsi.o \
           $(OBJDIR)/gcc-$(GCC_VERSION)/libgcc/libgcc2/fixunsdfsi.o \
           $(OBJDIR)/gcc-$(GCC_VERSION)/libgcc/libgcc2/fixunsxfsi.o \
           $(OBJDIR)/gcc-$(GCC_VERSION)/libgcc/libgcc2/fixsfdi.o \
           $(OBJDIR)/gcc-$(GCC_VERSION)/libgcc/libgcc2/fixdfdi.o \
           $(OBJDIR)/gcc-$(GCC_VERSION)/libgcc/libgcc2/fixxfdi.o \
           $(OBJDIR)/gcc-$(GCC_VERSION)/libgcc/libgcc2/fixunssfdi.o \
           $(OBJDIR)/gcc-$(GCC_VERSION)/libgcc/libgcc2/fixunsdfdi.o \
           $(OBJDIR)/gcc-$(GCC_VERSION)/libgcc/libgcc2/fixunsxfdi.o \
           $(OBJDIR)/gcc-$(GCC_VERSION)/libgcc/libgcc2/floatdisf.o \
           $(OBJDIR)/gcc-$(GCC_VERSION)/libgcc/libgcc2/floatdidf.o \
           $(OBJDIR)/gcc-$(GCC_VERSION)/libgcc/libgcc2/floatdixf.o \
           $(OBJDIR)/gcc-$(GCC_VERSION)/libgcc/libgcc2/floatundisf.o \
           $(OBJDIR)/gcc-$(GCC_VERSION)/libgcc/libgcc2/floatundidf.o \
           $(OBJDIR)/gcc-$(GCC_VERSION)/libgcc/libgcc2/floatundixf.o \
           $(OBJDIR)/gcc-$(GCC_VERSION)/libgcc/libgcc2/eprintf.o \
           $(OBJDIR)/gcc-$(GCC_VERSION)/libgcc/libgcc2/_gcc_bcmp.o \
           $(OBJDIR)/gcc-$(GCC_VERSION)/libgcc/libgcc2/divdi3.o \
           $(OBJDIR)/gcc-$(GCC_VERSION)/libgcc/libgcc2/moddi3.o \
           $(OBJDIR)/gcc-$(GCC_VERSION)/libgcc/libgcc2/udivdi3.o \
           $(OBJDIR)/gcc-$(GCC_VERSION)/libgcc/libgcc2/udiv_w_sdiv.o \
           $(OBJDIR)/gcc-$(GCC_VERSION)/libgcc/libgcc2/udivmoddi4.o

DEPENDS += $(OBJECTS:%.o=%.d)

.PHONY: all
all : $(LIBDIR)/gcc.a $(HEADERS)

$(LIBDIR)/gcc.a: $(OBJECTS)
	@[ -d $(@D) ] || (mkdir -p $(@D))
	@echo linking: $@
	@$(AR) r $@ $(OBJECTS)
	@echo successfully built: $@
	@echo

$(OBJDIR)/gcc-$(GCC_VERSION)/libgcc/libgcc2/%.o : gcc-$(GCC_VERSION)/libgcc/libgcc2.c $(MAKEFILE_SOURCES)
	@[ -d $(@D) ] || (mkdir -p $(@D))
	@echo compiling: $< $(*F)
	@$(CC) -c $(CFLAGS) -o $@ -DL_$(*F) $<

include rules.mk

# include auto-generated dependencies
-include $(DEPENDS)

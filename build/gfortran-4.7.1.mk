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

MAKEFILE_SOURCES += gcc-$(GCC_VERSION).mk

CFLAGS += \
  -I $(SRCDIR)/gcc-$(GCC_VERSION)/gcc \
  -I $(SRCDIR)/gcc-$(GCC_VERSION)/gcc/config/spu \
  -I $(SRCDIR)/gcc-$(GCC_VERSION)/gcc/ginclude \
  -I $(SRCDIR)/gcc-$(GCC_VERSION)/gcc/include \
  -I $(SRCDIR)/gcc-$(GCC_VERSION)/gcc/include-fixed \
  -I $(SRCDIR)/gcc-$(GCC_VERSION)/libcpp/include \
  -I $(SRCDIR)/gcc-$(GCC_VERSION)/libgcc \
  -I $(SRCDIR)/gcc-$(GCC_VERSION)/libgfortran \
  -I $(SRCDIR)/gcc-$(GCC_VERSION)/libquadmath \
  -I $(SRCDIR)/gcc-$(GCC_VERSION)/include \
  -I $(INCDIR) \
  -include $(SRCDIR)/llamaos/__thread.h \
  -D HAVE_CONFIG_H \
  -D HAVE_STDLIB_H \
  -D HAVE_STRING_H \
  -D HAVE_ALLOCA_H \
  -DFIRST_PSEUDO_REGISTER=53 \
  -DIN_GLIBCPP_V3

CPPFLAGS += \
  -I $(SRCDIR)/gcc-$(GCC_VERSION)/libstdc++-v3/include/backward \
  -I $(SRCDIR)/gcc-$(GCC_VERSION)/libstdc++-v3/include/c_global \
  -I $(SRCDIR)/gcc-$(GCC_VERSION)/libstdc++-v3/include/std \
  -I $(SRCDIR)/gcc-$(GCC_VERSION)/libstdc++-v3/include \
  -I $(SRCDIR)/gcc-$(GCC_VERSION)/libstdc++-v3/libsupc++ \
  -I $(SRCDIR)/gcc-$(GCC_VERSION)/gcc/include-fixed \
  -I $(SRCDIR)/gcc-$(GCC_VERSION)/gcc/ginclude \
  -I $(SRCDIR)/gcc-$(GCC_VERSION)/include \
  -I $(INCDIR) \
  -U_GLIBCXX_ATOMIC_BUILTINS \
  -include $(SRCDIR)/llamaos/__thread.h

#  gcc-$(GCC_VERSION)/libgcc/soft-fp/divdf3.c \
#  gcc-$(GCC_VERSION)/libgcc/soft-fp/divsf3.c \
#  gcc-$(GCC_VERSION)/libgcc/soft-fp/muldf3.c \
#  gcc-$(GCC_VERSION)/libgcc/soft-fp/mulsf3.c \

#  gcc-$(GCC_VERSION)/gcc/config/spu/spu.c \

C_SOURCES = \
  gcc-$(GCC_VERSION)/libgfortran/generated/exponent_r10.c \
  gcc-$(GCC_VERSION)/libgfortran/generated/exponent_r16.c \
  gcc-$(GCC_VERSION)/libgfortran/generated/exponent_r4.c \
  gcc-$(GCC_VERSION)/libgfortran/generated/exponent_r8.c \
  gcc-$(GCC_VERSION)/libgfortran/generated/pow_i4_i4.c \
  gcc-$(GCC_VERSION)/libgfortran/intrinsics/abort.c \
  gcc-$(GCC_VERSION)/libgfortran/intrinsics/args.c \
  gcc-$(GCC_VERSION)/libgfortran/intrinsics/bit_intrinsics.c \
  gcc-$(GCC_VERSION)/libgfortran/intrinsics/c99_functions.c \
  gcc-$(GCC_VERSION)/libgfortran/intrinsics/clock.c \
  gcc-$(GCC_VERSION)/libgfortran/intrinsics/cpu_time.c \
  gcc-$(GCC_VERSION)/libgfortran/intrinsics/cshift0.c \
  gcc-$(GCC_VERSION)/libgfortran/intrinsics/ctime.c \
  gcc-$(GCC_VERSION)/libgfortran/intrinsics/date_and_time.c \
  gcc-$(GCC_VERSION)/libgfortran/intrinsics/ierrno.c \
  gcc-$(GCC_VERSION)/libgfortran/intrinsics/ishftc.c \
  gcc-$(GCC_VERSION)/libgfortran/intrinsics/iso_c_binding.c \
  gcc-$(GCC_VERSION)/libgfortran/intrinsics/iso_c_generated_procs.c \
  gcc-$(GCC_VERSION)/libgfortran/intrinsics/malloc.c \
  gcc-$(GCC_VERSION)/libgfortran/intrinsics/move_alloc.c \
  gcc-$(GCC_VERSION)/libgfortran/intrinsics/mvbits.c \
  gcc-$(GCC_VERSION)/libgfortran/intrinsics/pack_generic.c \
  gcc-$(GCC_VERSION)/libgfortran/intrinsics/perror.c \
  gcc-$(GCC_VERSION)/libgfortran/intrinsics/rand.c \
  gcc-$(GCC_VERSION)/libgfortran/intrinsics/random.c \
  gcc-$(GCC_VERSION)/libgfortran/intrinsics/signal.c \
  gcc-$(GCC_VERSION)/libgfortran/intrinsics/sleep.c \
  gcc-$(GCC_VERSION)/libgfortran/intrinsics/string_intrinsics.c \
  gcc-$(GCC_VERSION)/libgfortran/intrinsics/system.c \
  gcc-$(GCC_VERSION)/libgfortran/intrinsics/system_clock.c \
  gcc-$(GCC_VERSION)/libgfortran/intrinsics/time.c \
  gcc-$(GCC_VERSION)/libgfortran/intrinsics/transpose_generic.c \
  gcc-$(GCC_VERSION)/libgfortran/intrinsics/unpack_generic.c \
  gcc-$(GCC_VERSION)/libgfortran/io/close.c \
  gcc-$(GCC_VERSION)/libgfortran/io/fbuf.c \
  gcc-$(GCC_VERSION)/libgfortran/io/file_pos.c \
  gcc-$(GCC_VERSION)/libgfortran/io/format.c \
  gcc-$(GCC_VERSION)/libgfortran/io/inquire.c \
  gcc-$(GCC_VERSION)/libgfortran/io/intrinsics.c \
  gcc-$(GCC_VERSION)/libgfortran/io/list_read.c \
  gcc-$(GCC_VERSION)/libgfortran/io/lock.c \
  gcc-$(GCC_VERSION)/libgfortran/io/open.c \
  gcc-$(GCC_VERSION)/libgfortran/io/read.c \
  gcc-$(GCC_VERSION)/libgfortran/io/size_from_kind.c \
  gcc-$(GCC_VERSION)/libgfortran/io/transfer.c \
  gcc-$(GCC_VERSION)/libgfortran/io/transfer128.c \
  gcc-$(GCC_VERSION)/libgfortran/io/unit.c \
  gcc-$(GCC_VERSION)/libgfortran/io/unix.c \
  gcc-$(GCC_VERSION)/libgfortran/io/write.c \
  gcc-$(GCC_VERSION)/libgfortran/io/write.c \
  gcc-$(GCC_VERSION)/libgfortran/runtime/backtrace.c \
  gcc-$(GCC_VERSION)/libgfortran/runtime/compile_options.c \
  gcc-$(GCC_VERSION)/libgfortran/runtime/environ.c \
  gcc-$(GCC_VERSION)/libgfortran/runtime/error.c \
  gcc-$(GCC_VERSION)/libgfortran/runtime/fpu.c \
  gcc-$(GCC_VERSION)/libgfortran/runtime/main.c \
  gcc-$(GCC_VERSION)/libgfortran/runtime/memory.c \
  gcc-$(GCC_VERSION)/libgfortran/runtime/stop.c \
  gcc-$(GCC_VERSION)/libgfortran/runtime/string.c \
  gcc-$(GCC_VERSION)/libgfortran/fmain.c

OBJECTS  = $(C_SOURCES:%.c=$(OBJDIR)/%.o)

.PHONY: all
all : $(LIBDIR)/gfortran.a

$(LIBDIR)/gfortran.a : $(OBJECTS)
	@[ -d $(@D) ] || (mkdir -p $(@D))
	@echo linking: $@
	@$(AR) r $@ $(OBJECTS)
	@echo successfully built: $@
	@echo

$(INCDIR)/% : $(SRCDIR)/gcc-$(GCC_VERSION)/libstdc++-v3/include/c_global/%
	@[ -d $(@D) ] || (mkdir -p $(@D))
	@echo copying: $@ from $<
	cp $< $@

$(INCDIR)/% : $(SRCDIR)/gcc-$(GCC_VERSION)/gcc/ginclude/%
	@[ -d $(@D) ] || (mkdir -p $(@D))
	@echo copying: $@ from $<
	cp $< $@

$(INCDIR)/% : $(SRCDIR)/gcc-$(GCC_VERSION)/libstdc++-v3/include/std/%
	@[ -d $(@D) ] || (mkdir -p $(@D))
	@echo copying: $@ from $<
	cp $< $@

$(INCDIR)/% : $(SRCDIR)/gcc-$(GCC_VERSION)/libstdc++-v3/libsupc++/%
	@[ -d $(@D) ] || (mkdir -p $(@D))
	@echo copying: $@ from $<
	cp $< $@

$(INCDIR)/% : $(SRCDIR)/gcc-$(GCC_VERSION)/libstdc++-v3/include/%
	@[ -d $(@D) ] || (mkdir -p $(@D))
	@echo copying: $@ from $<
	cp $< $@

include rules.mk

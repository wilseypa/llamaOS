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

# /home/wmagato/Builds/gcc-4.8.0/./gcc/xgcc -B/home/wmagato/Builds/gcc-4.8.0/./gcc/ -B/opt/gcc-4.8.0/x86_64-unknown-linux-gnu/bin/ -B/opt/gcc-4.8.0/x86_64-unknown-linux-gnu/lib/ -isystem /opt/gcc-4.8.0/x86_64-unknown-linux-gnu/include -isystem /opt/gcc-4.8.0/x86_64-unknown-linux-gnu/sys-include    -g -O2 -m32 -O2  -g -O2 -DIN_GCC   -W -Wall -Wwrite-strings -Wcast-qual -Wstrict-prototypes -Wmissing-prototypes -Wold-style-definition  -isystem ./include   -fpic -mlong-double-80 -g -DIN_LIBGCC2 -fbuilding-libgcc -fno-stack-protector   -fpic -mlong-double-80 -I. -I. -I../../.././gcc -I/usr/src/gcc-4.8.0/libgcc -I/usr/src/gcc-4.8.0/libgcc/. -I/usr/src/gcc-4.8.0/libgcc/../gcc -I/usr/src/gcc-4.8.0/libgcc/../include -I/usr/src/gcc-4.8.0/libgcc/config/libbid -DENABLE_DECIMAL_BID_FORMAT -DHAVE_CC_TLS  -DUSE_TLS -o unwind-dw2.o -MT unwind-dw2.o -MD -MP -MF unwind-dw2.dep -fexceptions -c /usr/src/gcc-4.8.0/libgcc/unwind-dw2.c -fvisibility=hidden -DHIDE_EXPORTS

# -fpic -mlong-double-80
# -DHAVE_CC_TLS
# -DUSE_TLS

CFLAGS += \
  -Wno-narrowing \
  -Wwrite-strings \
  -Wcast-qual \
  -Wstrict-prototypes \
  -Wmissing-prototypes \
  -Wold-style-definition \
  -DIN_GCC \
  -DIN_LIBGCC2 \
  -DENABLE_DECIMAL_BID_FORMAT \
  -DHIDE_EXPORTS \
  -fbuilding-libgcc \
  -fno-stack-protector \
  -fexceptions \
  -fvisibility=hidden \
  -I $(SRCDIR)/gcc-$(GCC_VERSION)/gcc \
  -I $(SRCDIR)/gcc-$(GCC_VERSION)/libcpp \
  -I $(SRCDIR)/gcc-$(GCC_VERSION)/include \
  -I $(SRCDIR)/gcc-$(GCC_VERSION)/libgcc/config/libbid \
  -I $(INCDIR)

VPATH = $(SRCDIR)

SOURCES = \
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

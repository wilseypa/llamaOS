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

# make file list
MAKEFILE_SOURCES += llamaOS.mk

ASMFLAGS += \
  -I $(INCDIR) \
  -I $(SRCDIR) \
  -D__XEN_INTERFACE_VERSION__=0x0003020a

CFLAGS += \
  -I $(INCDIR) \
  -I $(SRCDIR) \
  -include $(SRCDIR)/llamaos/__thread.h \
  -D__XEN_INTERFACE_VERSION__=0x0003020a

CPPFLAGS += \
  -I $(INCDIR) \
  -I $(SRCDIR) \
  -include $(SRCDIR)/llamaos/__thread.h \
  -D__XEN_INTERFACE_VERSION__=0x0003020a

# xen specific source files
ifeq ($(MAKECMDGOALS),xen)
C_SOURCES += \
  llamaos/xen/Entry-glibc.c \
  llamaos/xen/Trace.c

CPP_SOURCES += \
  llamaos/memory/Entry.cpp \
  llamaos/memory/Memory.cpp \
  llamaos/xen/Console.cpp \
  llamaos/xen/Entry-gcc.cpp \
  llamaos/xen/Entry-llamaOS.cpp \
  llamaos/xen/Events.cpp \
  llamaos/xen/Grant_table.cpp \
  llamaos/xen/Hypercall.cpp \
  llamaos/xen/Hypervisor.cpp \
  llamaos/xen/Memory.cpp \
  llamaos/xen/PCI.cpp \
  llamaos/xen/Traps.cpp \
  llamaos/xen/Xenstore.cpp
endif

# generate object list
OBJECTS  = $(C_SOURCES:%.c=$(OBJDIR)/%.o)
OBJECTS += $(CPP_SOURCES:%.cpp=$(OBJDIR)/%.o)
DEPENDS = $(OBJECTS:%.o=%.d)

.PHONY: xen
xen : $(OBJDIR)/llamaos/xen/Entry.o $(LIBDIR)/xen/llamaOS.a

# $(LIBDIR)/xen/Entry.o: llamaos/xen/Entry.S

$(LIBDIR)/xen/llamaOS.a: $(OBJECTS)
	@[ -d $(@D) ] || (mkdir -p $(@D))
	@echo copying Entry object...
	@cp $(OBJDIR)/llamaos/xen/Entry.o $(LIBDIR)/xen/Entry.o
	@echo linking: $@
	@$(AR) r $@ $^
	@echo successfully built: $@
	@echo

include rules.mk

# include auto-generated dependencies
-include $(DEPENDS)

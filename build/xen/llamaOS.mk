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

MAKEFILE_SOURCES += llamaOS.mk

ASMFLAGS += \
  -I $(INCDIR) \
  -I $(SRCDIR) \
  -include $(SRCDIR)/llamaos/__thread.h \
  -D__XEN_INTERFACE_VERSION__=0x00030205

CFLAGS += \
  -I $(INCDIR) \
  -I $(SRCDIR) \
  -include $(SRCDIR)/llamaos/__thread.h \
  -D__XEN_INTERFACE_VERSION__=0x00030205

CPPFLAGS += \
  -Wextra \
  -Weffc++ \
  -I $(INCDIR) \
  -I $(SRCDIR) \
  -include $(SRCDIR)/llamaos/__thread.h \
  -D__XEN_INTERFACE_VERSION__=0x00030205

VPATH = $(SRCDIR)

ASM_SOURCES = \
  llamaos/xen/entry/start.S

C_SOURCES = \
  llamaos/xen/entry/glibc.c \
  llamaos/xen/fs/ext2/vfs.c \
  llamaos/xen/fs/ext2/ext2.c \
  llamaos/xen/fs/ext2/fd.c \
  llamaos/xen/Trace.c

CPP_SOURCES = \
  llamaos/api/pci/BAR.cpp \
  llamaos/api/pci/Command.cpp \
  llamaos/api/pci/PCI.cpp \
  llamaos/api/pci/Status.cpp \
  llamaos/memory/Entry.cpp \
  llamaos/memory/Memory.cpp \
  llamaos/net/llamaNET.cpp \
  llamaos/xen/entry/gcc.cpp \
  llamaos/xen/entry/llamaOS.cpp \
  llamaos/xen/Block.cpp \
  llamaos/xen/Console.cpp \
  llamaos/xen/Events.cpp \
  llamaos/xen/Grant_map.cpp \
  llamaos/xen/Grant_table.cpp \
  llamaos/xen/Hypercall.cpp \
  llamaos/xen/Hypervisor.cpp \
  llamaos/xen/Memory.cpp \
  llamaos/xen/PCI.cpp \
  llamaos/xen/Traps.cpp \
  llamaos/xen/Xenstore.cpp

HEADERS = \
  $(INCDIR)/llamaos/api/io.h \
  $(INCDIR)/llamaos/api/sleep.h \
  $(INCDIR)/llamaos/memory/Memory.h \
  $(INCDIR)/llamaos/net/llamaNET.h \
  $(INCDIR)/llamaos/xen/Console.h \
  $(INCDIR)/llamaos/xen/Events.h \
  $(INCDIR)/llamaos/xen/Grant_map.h \
  $(INCDIR)/llamaos/xen/Grant_table.h \
  $(INCDIR)/llamaos/xen/Hypercall.h \
  $(INCDIR)/llamaos/xen/Hypervisor.h \
  $(INCDIR)/llamaos/xen/Traps.h \
  $(INCDIR)/llamaos/xen/Xenstore.h \
  $(INCDIR)/llamaos/__thread.h \
  $(INCDIR)/llamaos/Trace.h

OBJECTS  = $(ASM_SOURCES:%.S=$(OBJDIR)/%.o)
OBJECTS += $(C_SOURCES:%.c=$(OBJDIR)/%.o)
OBJECTS += $(CPP_SOURCES:%.cpp=$(OBJDIR)/%.o)
DEPENDS += $(OBJECTS:%.o=%.d)

.PHONY: all
all : $(LIBDIR)/llamaOS.a headers

.PHONY: headers
headers : $(HEADERS)

.PHONY: check
check :
	@echo running cppcheck on llamaos namespace...
	cppcheck $(SRCDIR)/llamaos

$(LIBDIR)/llamaOS.a: $(OBJECTS)
	@[ -d $(@D) ] || (mkdir -p $(@D))
	@echo linking: $@
	@$(AR) r $@ $^
	@echo successfully built: $@
	@echo

$(INCDIR)/% : $(SRCDIR)/%
	@[ -d $(@D) ] || (mkdir -p $(@D))
	@echo copying: $@ from $<
	cp $< $@

include rules.mk

# include auto-generated dependencies
-include $(DEPENDS)

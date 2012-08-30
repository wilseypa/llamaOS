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

# include the glibc object list
include glibc-obj-$(GLIBC_VERSION).mk

# include the gcc object list
include gcc-obj-$(GCC_VERSION).mk

# make file list
MAKEFILE_SOURCES += llamaOS.mk

CPPFLAGS += \
  -I $(INCDIR) \
  -I $(SRCDIR) \
  -D__XEN_INTERFACE_VERSION__=0x0003020a

LLAMAOS_SOURCES_ASM = 
LLAMAOS_SOURCES_C = 
LLAMAOS_SOURCES_CPP = 

# xen specific source files
ifeq ($(MAKECMDGOALS),xen)
LLAMAOS_SOURCES_CPP += \
  llamaos/xen/glibc-export.cpp \
  llamaos/xen/Hypercall.cpp \
  llamaos/xen/kernel.cpp \
  llamaos/xen/trace.cpp
endif

# generate object list
LLAMAOS_OBJECTS  = $(LLAMAOS_SOURCES_ASM:%.S=$(OBJDIR)/%.o)
LLAMAOS_OBJECTS += $(LLAMAOS_SOURCES_C:%.c=$(OBJDIR)/%.o)
LLAMAOS_OBJECTS += $(LLAMAOS_SOURCES_CPP:%.cpp=$(OBJDIR)/%.o)

.PHONY: xen
xen : glibc gcc xen-headers $(LIBDIR)/xen/llamaOS.a

.PHONY: glibc
glibc:
	@$(MAKE) -f glibc-$(GLIBC_VERSION).mk

.PHONY: gcc
gcc:
	@$(MAKE) -f gcc-$(GCC_VERSION).mk

.PHONY: xen-headers
xen-headers:
	@$(MAKE) -f xen-$(XEN_VERSION).mk

$(LIBDIR)/xen/llamaOS.a: $(GLIBC_OBJECTS) $(GCC_OBJECTS) $(LLAMAOS_OBJECTS)
	@[ -d $(@D) ] || (mkdir -p $(@D))
	@echo linking: $@
	@$(AR) r $@ $^
	@echo successfully built: $@
	@echo

include rules.mk

# include auto-generated dependencies
-include $(DEPENDS)

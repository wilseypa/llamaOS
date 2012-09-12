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

# template makefile for llamaOS applications

MAKEFILE_SOURCES = example_app.mk

LLAMAOS_INSTALL_DIR = /opt/llamaOS-1.0

# include common flag variables
include $(LLAMAOS_INSTALL_DIR)/llamaOS-flags.mk

LLAMAOS_LIBDIR = $(LLAMAOS_INSTALL_DIR)/lib
LLAMAOS_INCDIR = $(LLAMAOS_INSTALL_DIR)/include
LLAMAOS_INC2DIR = $(LLAMAOS_INSTALL_DIR)/include-fixed

BINDIR = bin
LIBDIR = lib
OBJDIR = obj

CPPFLAGS += \
  -I $(LLAMAOS_INCDIR) \
  -I $(LLAMAOS_INC2DIR) \
  -include $(LLAMAOS_INCDIR)/llamaos/__thread.h

SOURCES = \
  main.cpp

OBJECTS = $(SOURCES:%.cpp=$(OBJDIR)/%.o)
DEPENDS = $(OBJECTS:%.o=%.d)

.PHONY: all
all : $(BINDIR)/example_app

.PHONY: clean
clean:
	@rm -rf $(BINDIR)
	@rm -rf $(OBJDIR)

# the entry object must be the first object listed here or the guest will crash!
$(BINDIR)/example_app : $(LLAMAOS_LIBDIR)/xen/Entry.o $(OBJECTS) $(LLAMAOS_LIBDIR)/xen/llamaOS.a $(LLAMAOS_LIBDIR)/gcc.a $(LLAMAOS_LIBDIR)/glibc.a
	@[ -d $(@D) ] || (mkdir -p $(@D))
	@echo linking: $@
	@$(LD) $(LDFLAGS) -T $(LLAMAOS_INSTALL_DIR)/llamaOS.lds -o $@ $^
	@gzip -c -f --best $@ >$@.gz
	@echo successfully built: $@
	@echo

include rules.mk

# include auto-generated dependencies
-include $(DEPENDS)

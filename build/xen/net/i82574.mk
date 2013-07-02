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
include common-vars.mk
include common-flags.mk

# make file list
MAKEFILE_SOURCES += net/i82574.mk

CPPFLAGS += \
  -I $(INCDIR) \
  -I $(SRCDIR) \
  -D__XEN_INTERFACE_VERSION__=0x00030205 \
  -include $(SRCDIR)/llamaos/__thread.h

VPATH = $(SRCDIR)

SOURCES = \
  llamaos/net/i82574/CSR.cpp \
  llamaos/net/i82574/CTRL.cpp \
  llamaos/net/i82574/CTRL_EXT.cpp \
  llamaos/net/i82574/EXTCNF_CTRL.cpp \
  llamaos/net/i82574/GCR.cpp \
  llamaos/net/i82574/IMC.cpp \
  llamaos/net/i82574/IMS.cpp \
  llamaos/net/i82574/RCTL.cpp \
  llamaos/net/i82574/RXDCTL.cpp \
  llamaos/net/i82574/STATUS.cpp \
  llamaos/net/i82574/SWSM.cpp \
  llamaos/net/i82574/TCTL.cpp \
  llamaos/net/i82574/TXDCTL.cpp

OBJECTS = $(SOURCES:%.cpp=$(OBJDIR)/%.o)
DEPENDS = $(OBJECTS:%.o=%.d)

.PHONY: all
all: $(BINDIR)/i82574_buffered $(BINDIR)/i82574_lo $(BINDIR)/i82574_rdma

$(BINDIR)/i82574_buffered: $(OBJDIR)/llamaos/net/i82574/main_buffered.o $(OBJECTS) $(LIBDIR)/llamaOS.a $(LIBDIR)/stdc++.a $(LIBDIR)/gcc.a $(LIBDIR)/glibc.a
	@[ -d $(@D) ] || (mkdir -p $(@D))
	@echo linking: $@
	@$(LD) $(LDFLAGS) -T llamaOS.lds -o $@ $^
	@gzip -c -f --best $@ >$@.gz
	@echo successfully built: $@
	@echo

$(BINDIR)/i82574_lo: $(OBJDIR)/llamaos/net/i82574/main_lo.o $(OBJECTS) $(LIBDIR)/llamaOS.a $(LIBDIR)/stdc++.a $(LIBDIR)/gcc.a $(LIBDIR)/glibc.a
	@[ -d $(@D) ] || (mkdir -p $(@D))
	@echo linking: $@
	@$(LD) $(LDFLAGS) -T llamaOS.lds -o $@ $^
	@gzip -c -f --best $@ >$@.gz
	@echo successfully built: $@
	@echo

$(BINDIR)/i82574_rdma: $(OBJDIR)/llamaos/net/i82574/main_rdma.o $(OBJECTS) $(LIBDIR)/llamaOS.a $(LIBDIR)/stdc++.a $(LIBDIR)/gcc.a $(LIBDIR)/glibc.a
	@[ -d $(@D) ] || (mkdir -p $(@D))
	@echo linking: $@
	@$(LD) $(LDFLAGS) -T llamaOS.lds -o $@ $^
	@gzip -c -f --best $@ >$@.gz
	@echo successfully built: $@
	@echo

include rules.mk

# include auto-generated dependencies
-include $(DEPENDS)

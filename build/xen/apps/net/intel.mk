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

# make file list
MAKEFILE_SOURCES += apps/net/intel.mk

CPPFLAGS += \
  -I $(INCDIR) \
  -I $(SRCDIR)

VPATH = $(SRCDIR)

SOURCES = \
  apps/net/intel/regs/CSR.cpp \
  apps/net/intel/regs/CTRL.cpp \
  apps/net/intel/regs/CTRL_EXT.cpp \
  apps/net/intel/regs/EXTCNF_CTRL.cpp \
  apps/net/intel/regs/FCAH.cpp \
  apps/net/intel/regs/FCAL.cpp \
  apps/net/intel/regs/FCRTH.cpp \
  apps/net/intel/regs/FCRTL.cpp \
  apps/net/intel/regs/FCRTV.cpp \
  apps/net/intel/regs/FCT.cpp \
  apps/net/intel/regs/FCTTV.cpp \
  apps/net/intel/regs/IMC.cpp \
  apps/net/intel/regs/IMS.cpp \
  apps/net/intel/regs/PBA.cpp \
  apps/net/intel/regs/PSRCTL.cpp \
  apps/net/intel/regs/RCTL.cpp \
  apps/net/intel/regs/RDBAH.cpp \
  apps/net/intel/regs/RDBAL.cpp \
  apps/net/intel/regs/RDH.cpp \
  apps/net/intel/regs/RDLEN.cpp \
  apps/net/intel/regs/RDT.cpp \
  apps/net/intel/regs/RXDCTL.cpp \
  apps/net/intel/regs/STATUS.cpp \
  apps/net/intel/regs/SWSM.cpp \
  apps/net/intel/regs/TCTL.cpp \
  apps/net/intel/regs/TDBAH.cpp \
  apps/net/intel/regs/TDBAL.cpp \
  apps/net/intel/regs/TDH.cpp \
  apps/net/intel/regs/TDLEN.cpp \
  apps/net/intel/regs/TDT.cpp \
  apps/net/intel/regs/VET.cpp

OBJECTS = $(SOURCES:%.cpp=$(OBJDIR)/%.o)
DEPENDS = $(OBJECTS:%.o=%.d)

RDMA_SOURCES = \
  apps/net/intel/RDMA.cpp

RDMA_OBJECTS = $(RDMA_SOURCES:%.cpp=$(OBJDIR)/%.o)
DEPENDS += $(RDMA_OBJECTS:%.o=%.d)

LINKS = \
  $(LIBDIR)/llamaOS.a \
  $(LIBDIR)/stdc++.a \
  $(LIBDIR)/gcc.a \
  $(LIBDIR)/glibc.a

.PHONY: all
all: $(BINDIR)/net-intel-rdma

$(BINDIR)/net-intel-rdma: $(RDMA_OBJECTS) $(OBJECTS) $(LINKS)
	@[ -d $(@D) ] || (mkdir -p $(@D))
	@echo linking: $@
	@$(LD) $(LDFLAGS) -T llamaOS.lds -o $@ $^
	@gzip -c -f --best $@ >$@.gz
	@echo successfully built: $@
	@echo

include rules.mk

# include auto-generated dependencies
-include $(DEPENDS)

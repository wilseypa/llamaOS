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

MAKEFILE_SOURCES += apps/WARPED/raid-llamaWARPED.mk

WARPED_PATH = $(PDES_ROOT_PATH)/warped/src
WARPED_UTILS_PATH = $(PDES_ROOT_PATH)/utils/src
RAID_PATH = $(PDES_ROOT_PATH)/warped/simulationmodels/raid/factory/src

CPPFLAGS += \
  -I $(INCDIR) \
  -I $(INCDIR)/llamaos/mpi \
  -I $(WARPED_PATH) \
  -I $(WARPED_PATH)/warped \
  -I $(WARPED_UTILS_PATH) \
  -I $(PCCTS_ROOT_PATH)/h \
  -I $(RAID_PATH) \
  -D__XEN_INTERFACE_VERSION__=0x00030205 \
  -include $(SRCDIR)/llamaos/__thread.h \
  -Wno-reorder

VPATH = $(PDES_ROOT_PATH)

CPP_SOURCES = \
   $(RAID_PATH)/RAIDApplication.cpp \
   $(RAID_PATH)/RAIDDisk.cpp \
   $(RAID_PATH)/RAIDDiskState.cpp \
   $(RAID_PATH)/RAIDDiskStub.cpp \
   $(RAID_PATH)/RAIDFactoryManager.cpp \
   $(RAID_PATH)/RAIDFork.cpp \
   $(RAID_PATH)/RAIDForkState.cpp \
   $(RAID_PATH)/RAIDForkStub.cpp \
   $(RAID_PATH)/RAIDMain.cpp \
   $(RAID_PATH)/RAIDProcess.cpp \
   $(RAID_PATH)/RAIDProcessState.cpp \
   $(RAID_PATH)/RAIDProcessStub.cpp

OBJECTS = $(CPP_SOURCES:%.cpp=$(OBJDIR)/%.o)
DEPENDS = $(OBJECTS:%.o=%.d)

$(BINDIR)/WARPED/raid-llamaWARPED: $(OBJECTS) $(LIBDIR)/llamaWARPED.a $(LIBDIR)/llamaMPI.a $(LIBDIR)/llamaOS.a $(LIBDIR)/stdc++.a $(LIBDIR)/gcc.a $(LIBDIR)/glibc.a
	@[ -d $(@D) ] || (mkdir -p $(@D))
	@echo linking: $@
	@$(LD) $(LDFLAGS) -T llamaOS.lds -o $@ $^
	@gzip -c -f --best $@ >$@.gz
	@echo successfully built: $@
	@echo

include rules.mk

# include auto-generated dependencies
-include $(DEPENDS)

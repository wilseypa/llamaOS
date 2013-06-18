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

MAKEFILE_SOURCES += apps/WARPED/smmp-llamaWARPED.mk

WARPED_PATH = $(PDES_ROOT_PATH)/warped/src
WARPED_UTILS_PATH = $(PDES_ROOT_PATH)/utils/src
SMMP_PATH = $(PDES_ROOT_PATH)/warped/simulationmodels/smmp

CPPFLAGS += \
  -I $(INCDIR) \
  -I $(INCDIR)/llamaos/mpi \
  -I $(WARPED_PATH) \
  -I $(WARPED_PATH)/warped \
  -I $(WARPED_UTILS_PATH) \
  -I $(PCCTS_ROOT_PATH)/h \
  -I $(SMMP_PATH) \
  -D__XEN_INTERFACE_VERSION__=0x00030205 \
  -include $(SRCDIR)/llamaos/__thread.h \
  -Wno-reorder

VPATH = $(PDES_ROOT_PATH)

CPP_SOURCES = \
   $(SMMP_PATH)/MemRouterObject.cpp \
   $(SMMP_PATH)/MemSourceObject.cpp \
   $(SMMP_PATH)/SMMPApplication.cpp \
   $(SMMP_PATH)/SMMPForkObject.cpp \
   $(SMMP_PATH)/SMMPJoinObject.cpp \
   $(SMMP_PATH)/SMMPMain.cpp \
   $(SMMP_PATH)/SMMPPartitioner.cpp \
   $(SMMP_PATH)/SMMPQueueObject.cpp \
   $(SMMP_PATH)/SMMPServerObject.cpp

OBJECTS = $(CPP_SOURCES:%.cpp=$(OBJDIR)/%.o)
DEPENDS = $(OBJECTS:%.o=%.d)

$(BINDIR)/WARPED/smmp-llamaWARPED: $(OBJECTS) $(LIBDIR)/llamaWARPED.a $(LIBDIR)/llamaMPI.a $(LIBDIR)/llamaOS.a $(LIBDIR)/stdc++.a $(LIBDIR)/gcc.a $(LIBDIR)/glibc.a
	@[ -d $(@D) ] || (mkdir -p $(@D))
	@echo linking: $@
	@$(LD) $(LDFLAGS) -T llamaOS.lds -o $@ $^
	@gzip -c -f --best $@ >$@.gz
	@echo successfully built: $@
	@echo

include rules.mk

# include auto-generated dependencies
-include $(DEPENDS)

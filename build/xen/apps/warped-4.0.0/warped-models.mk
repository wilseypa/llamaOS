#
# Copyright (c) 2014, William Magato
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

# WARPED_VERSION should be defined in custom-vars.mk
# WARPED_MODELS_DIR should be defined in custom-vars.mk

OBJDIR = obj/apps/warped-$(WARPED_VERSION)

MAKEFILE_SOURCES += apps/warped-$(WARPED_VERSION)/warped-models.mk

CPPFLAGS += \
  -I $(INCDIR) \
  -I $(INCDIR)/warped \
  -I $(WARPED_MODELS_DIR)/src \
  -I $(WARPED_MODELS_DIR)/thirdparty \
  -fexceptions \
  -include $(SRCDIR)/llamaos/__thread.h

VPATH = $(WARPED_MODELS_DIR)/src

PINGPONG_SOURCES = \
  pingPong/PingEvent.cpp \
  pingPong/PingObject.cpp \
  pingPong/PingPongApplication.cpp \
  pingPong/main.cpp

PINGPONG_OBJECTS = $(PINGPONG_SOURCES:%.cpp=$(OBJDIR)/%.o)
PINGPONG_DEPENDS = $(PINGPONG_OBJECTS:%.o=%.d)

EPIDEMICSIM_SOURCES = \
  epidemic/EpidemicApplication.cpp \
  epidemic/EpidemicMain.cpp \
  epidemic/EpidemicPartitioner.cpp \
  epidemic/LocationObject.cpp \
  epidemic/tinyxml2.cpp

EPIDEMICSIM_OBJECTS = $(EPIDEMICSIM_SOURCES:%.cpp=$(OBJDIR)/%.o)
EPIDEMICSIM_DEPENDS = $(EPIDEMICSIM_OBJECTS:%.o=%.d)

.PHONY: all
all: pingpong epidemicsim

.PHONY: pingpong
pingpong: $(BINDIR)/apps/warped-models/pingpong

$(BINDIR)/apps/warped-models/pingpong: $(PINGPONG_OBJECTS) $(LIBDIR)/apps/warped/warped.a $(LIBDIR)/tools/mpich.a $(LIBDIR)/llamaOS.a $(LIBDIR)/sys/stdc++.a $(LIBDIR)/sys/gcc.a $(LIBDIR)/sys/glibc.a
	@[ -d $(@D) ] || (mkdir -p $(@D))
	@echo linking: $@
	@$(LD) $(LDFLAGS) -T llamaOS.lds -o $@ $^
	@gzip -c -f --best $@ >$@.gz
	@echo successfully built: $@
	@echo

.PHONY: epidemicsim
epidemicsim: $(BINDIR)/apps/warped-models/epidemicSim

$(BINDIR)/apps/warped-models/epidemicSim: $(EPIDEMICSIM_OBJECTS) $(LIBDIR)/apps/warped/warped.a $(LIBDIR)/tools/mpich.a $(LIBDIR)/llamaOS.a $(LIBDIR)/sys/stdc++.a $(LIBDIR)/sys/gcc.a $(LIBDIR)/sys/glibc.a
	@[ -d $(@D) ] || (mkdir -p $(@D))
	@echo linking: $@
	@$(LD) $(LDFLAGS) -T llamaOS.lds -o $@ $^
	@gzip -c -f --best $@ >$@.gz
	@echo successfully built: $@
	@echo

include rules.mk

# include auto-generated dependencies
-include $(PINGPONG_DEPENDS)
-include $(EPIDEMICSIM_DEPENDS)

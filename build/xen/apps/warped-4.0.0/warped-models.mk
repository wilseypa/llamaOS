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
  -I $(WARPED_MODELS_DIR)/thirdparty/re2 \
  -fexceptions \
  -include $(SRCDIR)/llamaos/__thread.h

VPATH = $(WARPED_MODELS_DIR)/src:$(WARPED_MODELS_DIR)/thirdparty

EPIDEMICSIM_SOURCES = \
  epidemic/EpidemicApplication.cpp \
  epidemic/EpidemicMain.cpp \
  epidemic/EpidemicPartitioner.cpp \
  epidemic/LocationObject.cpp \
  epidemic/tinyxml2.cpp

EPIDEMICSIM_OBJECTS = $(EPIDEMICSIM_SOURCES:%.cpp=$(OBJDIR)/%.o)
EPIDEMICSIM_DEPENDS = $(EPIDEMICSIM_OBJECTS:%.o=%.d)

#  re2/util/sparse_array_test.cc
ISCAS_CC_SOURCES = \
  re2/util/arena.cc \
  re2/util/benchmark.cc \
  re2/util/hash.cc \
  re2/util/pcre.cc \
  re2/util/random.cc \
  re2/util/rune.cc \
  re2/util/stringpiece.cc \
  re2/util/stringprintf.cc \
  re2/util/strutil.cc \
  re2/util/test.cc \
  re2/util/thread.cc \
  re2/util/valgrind.cc \
  re2/re2/bitstate.cc \
  re2/re2/compile.cc \
  re2/re2/dfa.cc \
  re2/re2/filtered_re2.cc \
  re2/re2/mimics_pcre.cc \
  re2/re2/nfa.cc \
  re2/re2/onepass.cc \
  re2/re2/parse.cc \
  re2/re2/perl_groups.cc \
  re2/re2/prefilter.cc \
  re2/re2/prefilter_tree.cc \
  re2/re2/prog.cc \
  re2/re2/re2.cc \
  re2/re2/regexp.cc \
  re2/re2/set.cc \
  re2/re2/simplify.cc \
  re2/re2/tostring.cc \
  re2/re2/unicode_casefold.cc \
  re2/re2/unicode_groups.cc

ISCAS_CPP_SOURCES = \
  iscas/ClockEvent.cpp \
  iscas/Component.cpp \
  iscas/DFlipFlop.cpp \
  iscas/ISCASApplication.cpp \
  iscas/InputObject.cpp \
  iscas/LogicGate.cpp \
  iscas/SignalEvent.cpp \
  iscas/main.cpp

ISCAS_OBJECTS = $(ISCAS_CC_SOURCES:%.cc=$(OBJDIR)/%.o)
ISCAS_OBJECTS += $(ISCAS_CPP_SOURCES:%.cpp=$(OBJDIR)/%.o)
ISCAS_DEPENDS = $(ISCAS_OBJECTS:%.o=%.d)

PHOLD_CC_SOURCES = \
  rnd/Binomial.cc \
  rnd/builtin.cc \
  rnd/DiscUnif.cc \
  rnd/gcd.cc \
  rnd/MLCG.cc \
  rnd/NegExp.cc \
  rnd/Normal.cc \
  rnd/Poisson.cc \
  rnd/Random.cc \
  rnd/RNG.cc \
  rnd/Uniform.cc

PHOLD_CPP_SOURCES = \
  phold/factory/src/PHOLDApplication.cpp \
  phold/factory/src/PHOLDEvent.cpp \
  phold/factory/src/PHOLDFactoryManager.cpp \
  phold/factory/src/PHOLDMain.cpp \
  phold/factory/src/Process.cpp \
  phold/factory/src/ProcessState.cpp \
  phold/factory/src/ProcessStub.cpp

PHOLD_OBJECTS = $(PHOLD_CC_SOURCES:%.cc=$(OBJDIR)/%.o)
PHOLD_OBJECTS += $(PHOLD_CPP_SOURCES:%.cpp=$(OBJDIR)/%.o)
PHOLD_DEPENDS = $(PHOLD_OBJECTS:%.o=%.d)

PINGPONG_SOURCES = \
  pingPong/PingEvent.cpp \
  pingPong/PingObject.cpp \
  pingPong/PingPongApplication.cpp \
  pingPong/main.cpp

PINGPONG_OBJECTS = $(PINGPONG_SOURCES:%.cpp=$(OBJDIR)/%.o)
PINGPONG_DEPENDS = $(PINGPONG_OBJECTS:%.o=%.d)

RAID_CC_SOURCES = \
  rnd/Binomial.cc \
  rnd/builtin.cc \
  rnd/DiscUnif.cc \
  rnd/gcd.cc \
  rnd/MLCG.cc \
  rnd/NegExp.cc \
  rnd/Normal.cc \
  rnd/Poisson.cc \
  rnd/Random.cc \
  rnd/RNG.cc \
  rnd/Uniform.cc

RAID_CPP_SOURCES = \
  raid/factory/src/RAIDApplication.cpp \
  raid/factory/src/RAIDDisk.cpp \
  raid/factory/src/RAIDDiskState.cpp \
  raid/factory/src/RAIDDiskStub.cpp \
  raid/factory/src/RAIDFactoryManager.cpp \
  raid/factory/src/RAIDFork.cpp \
  raid/factory/src/RAIDForkState.cpp \
  raid/factory/src/RAIDForkStub.cpp \
  raid/factory/src/RAIDMain.cpp \
  raid/factory/src/RAIDProcess.cpp \
  raid/factory/src/RAIDProcessState.cpp \
  raid/factory/src/RAIDProcessStub.cpp

RAID_OBJECTS = $(RAID_CC_SOURCES:%.cc=$(OBJDIR)/%.o)
RAID_OBJECTS += $(RAID_CPP_SOURCES:%.cpp=$(OBJDIR)/%.o)
RAID_DEPENDS = $(RAID_OBJECTS:%.o=%.d)

SMMP_CC_SOURCES = \
  rnd/Binomial.cc \
  rnd/builtin.cc \
  rnd/DiscUnif.cc \
  rnd/gcd.cc \
  rnd/MLCG.cc \
  rnd/NegExp.cc \
  rnd/Normal.cc \
  rnd/Poisson.cc \
  rnd/Random.cc \
  rnd/RNG.cc \
  rnd/Uniform.cc

SMMP_CPP_SOURCES = \
  smmp/MemRouterObject.cpp \
  smmp/MemSourceObject.cpp \
  smmp/SMMPApplication.cpp \
  smmp/SMMPForkObject.cpp \
  smmp/SMMPJoinObject.cpp \
  smmp/SMMPMain.cpp \
  smmp/SMMPPartitioner.cpp \
  smmp/SMMPQueueObject.cpp \
  smmp/SMMPServerObject.cpp

SMMP_OBJECTS = $(SMMP_CC_SOURCES:%.cc=$(OBJDIR)/%.o)
SMMP_OBJECTS += $(SMMP_CPP_SOURCES:%.cpp=$(OBJDIR)/%.o)
SMMP_DEPENDS = $(SMMP_OBJECTS:%.o=%.d)

LINKS = \
  $(LIBDIR)/apps/warped/warped.a \
  $(LIBDIR)/tools/mpich.a \
  $(LIBDIR)/llamaOS.a \
  $(LIBDIR)/sys/stdc++.a \
  $(LIBDIR)/sys/gcc.a \
  $(LIBDIR)/sys/glibc.a

.PHONY: all
all: epidemic phold pingpong raid smmp

.PHONY: epidemic
epidemic: $(BINDIR)/apps/warped-models/epidemicSim

$(BINDIR)/apps/warped-models/epidemicSim: $(EPIDEMICSIM_OBJECTS) $(LINKS)
	@[ -d $(@D) ] || (mkdir -p $(@D))
	@echo linking: $@
	@$(LD) $(LDFLAGS) -T llamaOS.lds -o $@ $^
	@gzip -c -f --best $@ >$@.gz
	@echo successfully built: $@
	@echo

.PHONY: iscas
iscas: $(BINDIR)/apps/warped-models/iscasSim

$(BINDIR)/apps/warped-models/iscasSim: $(ISCAS_OBJECTS) $(LINKS)
	@[ -d $(@D) ] || (mkdir -p $(@D))
	@echo linking: $@
	@$(LD) $(LDFLAGS) -T llamaOS.lds -o $@ $^
	@gzip -c -f --best $@ >$@.gz
	@echo successfully built: $@
	@echo

.PHONY: phold
phold: $(BINDIR)/apps/warped-models/pholdSim

$(BINDIR)/apps/warped-models/pholdSim: $(PHOLD_OBJECTS) $(LINKS)
	@[ -d $(@D) ] || (mkdir -p $(@D))
	@echo linking: $@
	@$(LD) $(LDFLAGS) -T llamaOS.lds -o $@ $^
	@gzip -c -f --best $@ >$@.gz
	@echo successfully built: $@
	@echo

.PHONY: pingpong
pingpong: $(BINDIR)/apps/warped-models/pingpong

$(BINDIR)/apps/warped-models/pingpong: $(PINGPONG_OBJECTS) $(LINKS)
	@[ -d $(@D) ] || (mkdir -p $(@D))
	@echo linking: $@
	@$(LD) $(LDFLAGS) -T llamaOS.lds -o $@ $^
	@gzip -c -f --best $@ >$@.gz
	@echo successfully built: $@
	@echo

.PHONY: raid
raid: $(BINDIR)/apps/warped-models/raidSim

$(BINDIR)/apps/warped-models/raidSim: $(RAID_OBJECTS) $(LINKS)
	@[ -d $(@D) ] || (mkdir -p $(@D))
	@echo linking: $@
	@$(LD) $(LDFLAGS) -T llamaOS.lds -o $@ $^
	@gzip -c -f --best $@ >$@.gz
	@echo successfully built: $@
	@echo

.PHONY: smmp
raid: $(BINDIR)/apps/warped-models/smmpSim

$(BINDIR)/apps/warped-models/smmpSim: $(SMMP_OBJECTS) $(LINKS)
	@[ -d $(@D) ] || (mkdir -p $(@D))
	@echo linking: $@
	@$(LD) $(LDFLAGS) -T llamaOS.lds -o $@ $^
	@gzip -c -f --best $@ >$@.gz
	@echo successfully built: $@
	@echo

include rules.mk

# include auto-generated dependencies
-include $(EPIDEMICSIM_DEPENDS)
-include $(ISCAS_DEPENDS)
-include $(PHOLD_DEPENDS)
-include $(PINGPONG_DEPENDS)
-include $(RAID_DEPENDS)
-include $(SMMP_DEPENDS)

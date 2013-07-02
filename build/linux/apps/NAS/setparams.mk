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

MAKEFILE_SOURCES += apps/NAS/setparams.mk

CFLAGS += \
  -I $(INCDIR) \
  -I $(SRCDIR) \
  -I $(SRCDIR)/apps/NPB3.2-MPI/sys

VPATH = $(SRCDIR)

SOURCES = \
  apps/NPB3.2-MPI/sys/setparams.c

OBJECTS = $(SOURCES:%.c=$(OBJDIR)/%.o)
DEPENDS = $(OBJECTS:%.o=%.d)

SETPARAMS = $(BINDIR)/setparams

HEADERS = \
  $(INCDIR)/NAS/cg/npbparams.h \
  $(INCDIR)/NAS/dt/npbparams.h \
  $(INCDIR)/NAS/ep/npbparams.h \
  $(INCDIR)/NAS/ft/npbparams.h \
  $(INCDIR)/NAS/is/npbparams.h \
  $(INCDIR)/NAS/lu/npbparams.h \
  $(INCDIR)/NAS/mg/npbparams.h \
  $(INCDIR)/NAS/sp/npbparams.h

.PHONY: all
all: $(SETPARAMS) $(HEADERS)

$(SETPARAMS): $(OBJECTS)
	echo $(OBJECTS)
	@[ -d $(@D) ] || (mkdir -p $(@D))
	@echo linking: $@
	@$(CC) -o $@ $^
	@echo successfully built: $@
	@echo

$(INCDIR)/NAS/cg/npbparams.h: apps/NAS/params.def
	echo Creating cg benchmark header
	$(SETPARAMS) `grep CG apps/NAS/params.def`
	@[ -d $(@D) ] || (mkdir -p $(@D))
	mv util/NAS/npbparams.h $@

$(INCDIR)/NAS/dt/npbparams.h: apps/NAS/params.def
	echo Creating dt benchmark header
	$(SETPARAMS) `grep DT apps/NAS/params.def`
	@[ -d $(@D) ] || (mkdir -p $(@D))
	mv util/NAS/npbparams.h $@

$(INCDIR)/NAS/ep/npbparams.h: apps/NAS/params.def
	echo Creating ep benchmark header
	$(SETPARAMS) `grep EP apps/NAS/params.def`
	@[ -d $(@D) ] || (mkdir -p $(@D))
	mv util/NAS/npbparams.h $@

$(INCDIR)/NAS/ft/npbparams.h: apps/NAS/params.def
	echo Creating ft benchmark header
	$(SETPARAMS) `grep FT apps/NAS/params.def`
	@[ -d $(@D) ] || (mkdir -p $(@D))
	mv util/NAS/npbparams.h $@

$(INCDIR)/NAS/is/npbparams.h: apps/NAS/params.def
	echo Creating is benchmark header
	$(SETPARAMS) `grep IS apps/NAS/params.def`
	@[ -d $(@D) ] || (mkdir -p $(@D))
	mv util/NAS/npbparams.h $@

$(INCDIR)/NAS/lu/npbparams.h: apps/NAS/params.def
	echo Creating lu benchmark header
	$(SETPARAMS) `grep LU apps/NAS/params.def`
	@[ -d $(@D) ] || (mkdir -p $(@D))
	mv util/NAS/npbparams.h $@

$(INCDIR)/NAS/mg/npbparams.h: apps/NAS/params.def
	echo Creating mg benchmark header
	$(SETPARAMS) `grep MG apps/NAS/params.def`
	@[ -d $(@D) ] || (mkdir -p $(@D))
	mv util/NAS/npbparams.h $@

$(INCDIR)/NAS/sp/npbparams.h: apps/NAS/params.def
	echo Creating sp benchmark header
	$(SETPARAMS) `grep SP apps/NAS/params.def`
	@[ -d $(@D) ] || (mkdir -p $(@D))
	mv util/NAS/npbparams.h $@

include rules.mk

# include auto-generated dependencies
-include $(DEPENDS)

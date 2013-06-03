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

util/NAS/*/npbparams.h: apps/NAS/params.def util/NAS/setparams
	echo Creating benchmark headers
	util/NAS/setparams `grep CG apps/NAS/params.def`
	mkdir -p util/NAS/cg
	mv util/NAS/npbparams.h util/NAS/cg/npbparams.h
	util/NAS/setparams `grep DT apps/NAS/params.def`
	mkdir -p util/NAS/dt
	mv util/NAS/npbparams.h util/NAS/dt/npbparams.h
	util/NAS/setparams `grep EP apps/NAS/params.def`
	mkdir -p util/NAS/ep
	mv util/NAS/npbparams.h util/NAS/ep/npbparams.h
	util/NAS/setparams `grep FT apps/NAS/params.def`
	mkdir -p util/NAS/ft
	mv util/NAS/npbparams.h util/NAS/ft/npbparams.h
	util/NAS/setparams `grep IS apps/NAS/params.def`
	mkdir -p util/NAS/is
	mv util/NAS/npbparams.h util/NAS/is/npbparams.h
	util/NAS/setparams `grep LU apps/NAS/params.def`
	mkdir -p util/NAS/lu
	mv util/NAS/npbparams.h util/NAS/lu/npbparams.h
	util/NAS/setparams `grep MG apps/NAS/params.def`
	mkdir -p util/NAS/mg
	mv util/NAS/npbparams.h util/NAS/mg/npbparams.h
	util/NAS/setparams `grep SP apps/NAS/params.def`
	mkdir -p util/NAS/sp
	mv util/NAS/npbparams.h util/NAS/sp/npbparams.h

util/NAS/setparams: $(OBJECTS)
	echo $(OBJECTS)
	@[ -d $(@D) ] || (mkdir -p $(@D))
	@echo linking: $@
	@$(CC) -o $@ $^
	@echo successfully built: $@
	@echo

include rules.mk

# include auto-generated dependencies
-include $(DEPENDS)

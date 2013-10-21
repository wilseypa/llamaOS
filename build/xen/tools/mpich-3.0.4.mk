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

MAKEFILE_SOURCES += tools/mpich-$(MPICH_VERSION).mk

CFLAGS += \
  -I $(SRCDIR)/tools/mpich-$(MPICH_VERSION)/src/include \
  -I $(SRCDIR)/tools/mpich-$(MPICH_VERSION)/src/include.build \
  -I $(SRCDIR)/tools/mpich-$(MPICH_VERSION)/src/mpi/romio/include.build \
  -I $(SRCDIR)/tools/mpich-$(MPICH_VERSION)/src/mpid/ch3/include \
  -I $(SRCDIR)/tools/mpich-$(MPICH_VERSION)/src/mpid/ch3/channels/nemesis/include \
  -I $(SRCDIR)/tools/mpich-$(MPICH_VERSION)/src/mpid/ch3/channels/nemesis/include.build \
  -I $(SRCDIR)/tools/mpich-$(MPICH_VERSION)/src/mpid/common/datatype \
  -I $(SRCDIR)/tools/mpich-$(MPICH_VERSION)/src/mpid/common/sched \
  -I $(SRCDIR)/tools/mpich-$(MPICH_VERSION)/src/mpl/include \
  -I $(SRCDIR)/tools/mpich-$(MPICH_VERSION)/src/mpl/include.build \
  -I $(SRCDIR)/tools/mpich-$(MPICH_VERSION)/src/openpa/src \
  -I $(SRCDIR)/tools/mpich-$(MPICH_VERSION)/src/openpa/src.build \
  -I $(SRCDIR)/tools/mpich-$(MPICH_VERSION)/src/util/wrappers \
  -I $(INCDIR) \
  -include $(SRCDIR)/llamaos/__thread.h

VPATH = $(SRCDIR)

SOURCES = \
  tools/mpich-$(MPICH_VERSION)/src/mpi/pt2pt/recv.c \
  tools/mpich-$(MPICH_VERSION)/src/mpi/pt2pt/send.c

HEADERS = 

OBJECTS  = $(SOURCES:%.c=$(OBJDIR)/%.o)
DEPENDS += $(OBJECTS:%.o=%.d)

.PHONY: all
all : $(LIBDIR)/tools/mpich.a $(HEADERS)

$(LIBDIR)/tools/mpich.a: $(OBJECTS)
	@[ -d $(@D) ] || (mkdir -p $(@D))
	@echo linking: $@
	@$(AR) r $@ $(OBJECTS)
	@echo successfully built: $@
	@echo

include rules.mk

# include auto-generated dependencies
-include $(DEPENDS)

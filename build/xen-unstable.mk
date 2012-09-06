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
include common.mk

MAKEFILE_SOURCES += xen-$(XEN_VERSION).mk

HEADERS = \
  $(INCDIR)/xen/arch-x86/xen-mca.h \
  $(INCDIR)/xen/arch-x86/xen-x86_64.h \
  $(INCDIR)/xen/arch-x86/xen.h \
  $(INCDIR)/xen/io/console.h \
  $(INCDIR)/xen/io/pciif.h \
  $(INCDIR)/xen/io/xenbus.h \
  $(INCDIR)/xen/io/xs_wire.h \
  $(INCDIR)/xen/event_channel.h \
  $(INCDIR)/xen/features.h \
  $(INCDIR)/xen/grant_table.h \
  $(INCDIR)/xen/physdev.h \
  $(INCDIR)/xen/platform.h \
  $(INCDIR)/xen/sched.h \
  $(INCDIR)/xen/tmem.h \
  $(INCDIR)/xen/version.h \
  $(INCDIR)/xen/xen-compat.h \
  $(INCDIR)/xen/xen.h

.PHONY: all
all : $(HEADERS)

$(INCDIR)/xen/% : $(SRCDIR)/xen-$(XEN_VERSION)/xen/include/public/%
	@[ -d $(@D) ] || (mkdir -p $(@D))
	@echo copying: $@ from $<
	cp $< $@

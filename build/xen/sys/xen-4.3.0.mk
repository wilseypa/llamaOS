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

MAKEFILE_SOURCES += sys/xen-$(XEN_VERSION).mk

HEADERS = \
  $(INCDIR)/xen/arch-arm/hvm/save.h \
  $(INCDIR)/xen/arch-x86/hvm/save.h \
  $(INCDIR)/xen/arch-x86/cpuid.h \
  $(INCDIR)/xen/arch-x86/xen-mca.h \
  $(INCDIR)/xen/arch-x86/xen-x86_32.h \
  $(INCDIR)/xen/arch-x86/xen-x86_64.h \
  $(INCDIR)/xen/arch-x86/xen.h \
  $(INCDIR)/xen/hvm/e820.h \
  $(INCDIR)/xen/hvm/hvm_info_table.h \
  $(INCDIR)/xen/hvm/hvm_op.h \
  $(INCDIR)/xen/hvm/hvm_xs_strings.h \
  $(INCDIR)/xen/hvm/ioreq.h \
  $(INCDIR)/xen/hvm/params.h \
  $(INCDIR)/xen/hvm/pvdrivers.h \
  $(INCDIR)/xen/hvm/save.h \
  $(INCDIR)/xen/io/blkif.h \
  $(INCDIR)/xen/io/console.h \
  $(INCDIR)/xen/io/fbif.h \
  $(INCDIR)/xen/io/fsif.h \
  $(INCDIR)/xen/io/kbdif.h \
  $(INCDIR)/xen/io/libxenvchan.h \
  $(INCDIR)/xen/io/netif.h \
  $(INCDIR)/xen/io/pciif.h \
  $(INCDIR)/xen/io/protocols.h \
  $(INCDIR)/xen/io/ring.h \
  $(INCDIR)/xen/io/tpmif.h \
  $(INCDIR)/xen/io/usbif.h \
  $(INCDIR)/xen/io/vscsiif.h \
  $(INCDIR)/xen/io/xenbus.h \
  $(INCDIR)/xen/io/xs_wire.h \
  $(INCDIR)/xen/xsm/flask_op.h \
  $(INCDIR)/xen/arch-arm.h \
  $(INCDIR)/xen/arch-x86_32.h \
  $(INCDIR)/xen/arch-x86_64.h \
  $(INCDIR)/xen/callback.h \
  $(INCDIR)/xen/dom0_ops.h \
  $(INCDIR)/xen/domctl.h \
  $(INCDIR)/xen/elfnote.h \
  $(INCDIR)/xen/event_channel.h \
  $(INCDIR)/xen/features.h \
  $(INCDIR)/xen/gcov.h \
  $(INCDIR)/xen/grant_table.h \
  $(INCDIR)/xen/kexec.h \
  $(INCDIR)/xen/mem_event.h \
  $(INCDIR)/xen/memory.h \
  $(INCDIR)/xen/nmi.h \
  $(INCDIR)/xen/physdev.h \
  $(INCDIR)/xen/platform.h \
  $(INCDIR)/xen/sched.h \
  $(INCDIR)/xen/sysctl.h \
  $(INCDIR)/xen/tmem.h \
  $(INCDIR)/xen/trace.h \
  $(INCDIR)/xen/vcpu.h \
  $(INCDIR)/xen/version.h \
  $(INCDIR)/xen/xen-compat.h \
  $(INCDIR)/xen/xen.h \
  $(INCDIR)/xen/xencomm.h \
  $(INCDIR)/xen/xenoprof.h

.PHONY: all
all : $(HEADERS)

$(INCDIR)/xen/% : $(SRCDIR)/sys/xen-$(XEN_VERSION)/%
	@[ -d $(@D) ] || (mkdir -p $(@D))
	@echo copying: $@ from $<
	cp $< $@

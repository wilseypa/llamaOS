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

MAKEFILE_SOURCES += glibc-$(GLIBC_VERSION).mk

HEADERS = \
  $(INCDIR)/bits/byteswap.h \
  $(INCDIR)/bits/byteswap-16.h \
  $(INCDIR)/bits/confname.h \
  $(INCDIR)/bits/endian.h \
  $(INCDIR)/bits/environments.h \
  $(INCDIR)/bits/errno.h \
  $(INCDIR)/bits/local_lim.h \
  $(INCDIR)/bits/locale.h \
  $(INCDIR)/bits/posix_opt.h \
  $(INCDIR)/bits/posix1_lim.h \
  $(INCDIR)/bits/posix2_lim.h \
  $(INCDIR)/bits/pthreadtypes.h \
  $(INCDIR)/bits/select.h \
  $(INCDIR)/bits/sigset.h \
  $(INCDIR)/bits/stdio_lim.h \
  $(INCDIR)/bits/sys_errlist.h \
  $(INCDIR)/bits/time.h \
  $(INCDIR)/bits/sigaction.h \
  $(INCDIR)/bits/sigcontext.h \
  $(INCDIR)/bits/siginfo.h \
  $(INCDIR)/bits/signum.h \
  $(INCDIR)/bits/sigstack.h \
  $(INCDIR)/bits/sigthread.h \
  $(INCDIR)/bits/stdio.h \
  $(INCDIR)/bits/string.h \
  $(INCDIR)/bits/string2.h \
  $(INCDIR)/bits/types.h \
  $(INCDIR)/bits/typesizes.h \
  $(INCDIR)/bits/waitflags.h \
  $(INCDIR)/bits/waitstatus.h \
  $(INCDIR)/bits/wordsize.h \
  $(INCDIR)/bits/wchar.h \
  $(INCDIR)/bits/xopen_lim.h \
  $(INCDIR)/gnu/stubs.h \
  $(INCDIR)/sys/cdefs.h \
  $(INCDIR)/sys/sysmacros.h \
  $(INCDIR)/sys/select.h \
  $(INCDIR)/sys/types.h \
  $(INCDIR)/sys/ucontext.h \
  $(INCDIR)/_G_config.h \
  $(INCDIR)/alloca.h \
  $(INCDIR)/ctype.h \
  $(INCDIR)/errno.h \
  $(INCDIR)/endian.h \
  $(INCDIR)/features.h \
  $(INCDIR)/getopt.h \
  $(INCDIR)/libio.h \
  $(INCDIR)/limits.h \
  $(INCDIR)/locale.h \
  $(INCDIR)/signal.h \
  $(INCDIR)/stdc-predef.h \
  $(INCDIR)/stdint.h \
  $(INCDIR)/stdio.h \
  $(INCDIR)/stdlib.h \
  $(INCDIR)/string.h \
  $(INCDIR)/unistd.h \
  $(INCDIR)/time.h \
  $(INCDIR)/wchar.h \
  $(INCDIR)/wctype.h \
  $(INCDIR)/xlocale.h

.PHONY: all
all : $(GLIBC_OBJECTS) $(HEADERS)

$(INCDIR)/% : $(SRCDIR)/glibc-$(GLIBC_VERSION)/sysdeps/llamaos/%
	@[ -d $(@D) ] || (mkdir -p $(@D))
	@echo copying: $@ from $<
	cp $< $@

$(INCDIR)/% : $(SRCDIR)/glibc-$(GLIBC_VERSION)/sysdeps/x86/%
	@[ -d $(@D) ] || (mkdir -p $(@D))
	@echo copying: $@ from $<
	cp $< $@

$(INCDIR)/% : $(SRCDIR)/glibc-$(GLIBC_VERSION)/sysdeps/i386/%
	@[ -d $(@D) ] || (mkdir -p $(@D))
	@echo copying: $@ from $<
	cp $< $@

$(INCDIR)/% : $(SRCDIR)/glibc-$(GLIBC_VERSION)/sysdeps/generic/%
	@[ -d $(@D) ] || (mkdir -p $(@D))
	@echo copying: $@ from $<
	cp $< $@

$(INCDIR)/% : $(SRCDIR)/glibc-$(GLIBC_VERSION)/ctype/%
	@[ -d $(@D) ] || (mkdir -p $(@D))
	@echo copying: $@ from $<
	cp $< $@

$(INCDIR)/% : $(SRCDIR)/glibc-$(GLIBC_VERSION)/libio/%
	@[ -d $(@D) ] || (mkdir -p $(@D))
	@echo copying: $@ from $<
	cp $< $@

$(INCDIR)/% : $(SRCDIR)/glibc-$(GLIBC_VERSION)/locale/%
	@[ -d $(@D) ] || (mkdir -p $(@D))
	@echo copying: $@ from $<
	cp $< $@

$(INCDIR)/% : $(SRCDIR)/glibc-$(GLIBC_VERSION)/misc/%
	@[ -d $(@D) ] || (mkdir -p $(@D))
	@echo copying: $@ from $<
	cp $< $@

$(INCDIR)/% : $(SRCDIR)/glibc-$(GLIBC_VERSION)/posix/%
	@[ -d $(@D) ] || (mkdir -p $(@D))
	@echo copying: $@ from $<
	cp $< $@

$(INCDIR)/% : $(SRCDIR)/glibc-$(GLIBC_VERSION)/signal/%
	@[ -d $(@D) ] || (mkdir -p $(@D))
	@echo copying: $@ from $<
	cp $< $@


$(INCDIR)/% : $(SRCDIR)/glibc-$(GLIBC_VERSION)/stdlib/%
	@[ -d $(@D) ] || (mkdir -p $(@D))
	@echo copying: $@ from $<
	cp $< $@

$(INCDIR)/% : $(SRCDIR)/glibc-$(GLIBC_VERSION)/string/%
	@[ -d $(@D) ] || (mkdir -p $(@D))
	@echo copying: $@ from $<
	cp $< $@

$(INCDIR)/% : $(SRCDIR)/glibc-$(GLIBC_VERSION)/time/%
	@[ -d $(@D) ] || (mkdir -p $(@D))
	@echo copying: $@ from $<
	cp $< $@

$(INCDIR)/% : $(SRCDIR)/glibc-$(GLIBC_VERSION)/wcsmbs/%
	@[ -d $(@D) ] || (mkdir -p $(@D))
	@echo copying: $@ from $<
	cp $< $@

$(INCDIR)/% : $(SRCDIR)/glibc-$(GLIBC_VERSION)/wctype/%
	@[ -d $(@D) ] || (mkdir -p $(@D))
	@echo copying: $@ from $<
	cp $< $@

$(INCDIR)/% : $(SRCDIR)/glibc-$(GLIBC_VERSION)/%
	@[ -d $(@D) ] || (mkdir -p $(@D))
	@echo copying: $@ from $<
	cp $< $@

$(INCDIR)/% : $(SRCDIR)/glibc-$(GLIBC_VERSION)/include/%
	@[ -d $(@D) ] || (mkdir -p $(@D))
	@echo copying: $@ from $<
	cp $< $@

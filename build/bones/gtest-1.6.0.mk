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

MAKEFILE_SOURCES += gtest-$(GTEST_VERSION).mk

CPPFLAGS += \
  -I $(SRCDIR)/gtest-$(GTEST_VERSION)/include \
  -I $(SRCDIR)/gtest-$(GTEST_VERSION) \
  -I $(INCDIR) \
  -I include-fixed \
  -DGTEST_HAS_PTHREAD=0 \
  -DGTEST_HAS_STREAM_REDIRECTION=0 \
  -DGTEST_DONT_DEFINE_TEST=1\
  -include $(SRCDIR)/llamaos/__thread.h

HEADERS = \
  $(INCDIR)/gtest/internal/gtest-death-test-internal.h \
  $(INCDIR)/gtest/internal/gtest-filepath.h \
  $(INCDIR)/gtest/internal/gtest-internal.h \
  $(INCDIR)/gtest/internal/gtest-linked_ptr.h \
  $(INCDIR)/gtest/internal/gtest-param-util.h \
  $(INCDIR)/gtest/internal/gtest-param-util-generated.h \
  $(INCDIR)/gtest/internal/gtest-port.h \
  $(INCDIR)/gtest/internal/gtest-string.h \
  $(INCDIR)/gtest/internal/gtest-tuple.h \
  $(INCDIR)/gtest/internal/gtest-type-util.h \
  $(INCDIR)/gtest/gtest-death-test.h \
  $(INCDIR)/gtest/gtest-message.h \
  $(INCDIR)/gtest/gtest-param-test.h \
  $(INCDIR)/gtest/gtest-printers.h \
  $(INCDIR)/gtest/gtest-spi.h \
  $(INCDIR)/gtest/gtest-test-part.h \
  $(INCDIR)/gtest/gtest-typed-test.h \
  $(INCDIR)/gtest/gtest.h \
  $(INCDIR)/gtest/gtest_pred_impl.h \
  $(INCDIR)/gtest/gtest_prod.h

SOURCES = \
  gtest-$(GTEST_VERSION)/src/gtest-all.cc

OBJECTS = $(SOURCES:%.cc=$(OBJDIR)/%.o)

.PHONY: all
all : $(LIBDIR)/gtest.a $(HEADERS)

$(LIBDIR)/gtest.a : $(OBJECTS)
	@[ -d $(@D) ] || (mkdir -p $(@D))
	@echo linking: $@
	@$(AR) r $@ $(OBJECTS)
	@echo successfully built: $@
	@echo

$(INCDIR)/% : $(SRCDIR)/gtest-$(GTEST_VERSION)/include/%
	@[ -d $(@D) ] || (mkdir -p $(@D))
	@echo copying: $@ from $<
	cp $< $@

include rules.mk

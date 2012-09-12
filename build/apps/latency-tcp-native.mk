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
# include common.mk
# don;t include common.mk since this is not llamaOS
# but try to make the build as similar as possible
MAKEFLAGS = --silent

# compiler tools
CC = /opt/gcc-4.7.1/bin/g++
LD = /opt/gcc-4.7.1/bin/g++

CPPFLAGS = \
  -m64 -g -O1 \
  -Wall \
  -fno-common \
  -std=gnu++11

LDFLAGS =

# shared common paths
BINDIR = bin
LIBDIR = lib
OBJDIR = obj
INCDIR = include
INC2DIR = include-fixed

SRCDIR = ../src
VPATH = $(SRCDIR)

GLIBC_VERSION = 2.16.0
GCC_VERSION = 4.7.1
# XEN_VERSION = 4.1.2
XEN_VERSION = 4.1.3
# XEN_VERSION = unstable
GTEST_VERSION = 1.6.0

# auto dependency generation
DEPENDS = 

MAKEFILE_SOURCES += apps/latency-tcp-native.mk

CPPFLAGS += \
  -I $(INCDIR) \
  -include $(SRCDIR)/llamaos/__thread.h

SOURCES = \
  llamaos/apps/latency/Experiment.cpp \
  llamaos/apps/latency/protocols/Experiment_tcp.cpp \
  llamaos/apps/latency/main.cpp

OBJECTS = $(SOURCES:%.cpp=$(OBJDIR)/%.o)
DEPENDS = $(OBJECTS:%.o=%.d)

$(BINDIR)/native/latency-tcp: $(OBJECTS)
	@[ -d $(@D) ] || (mkdir -p $(@D))
	@echo linking: $@
	@$(LD) $(LDFLAGS) -o $@ $^
	@echo successfully built: $@
	@echo

include rules.mk

# include auto-generated dependencies
-include $(DEPENDS)

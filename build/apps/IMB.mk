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
include native-flags.mk

# compiler tools
CC = mpicc
CXX = mpicxx
LD = mpicxx

# include custom flags if exists
-include custom-mpi-flags.mk

MAKEFILE_SOURCES += apps/IMB.mk

# shared common paths
BINDIR = bin
LIBDIR = lib
OBJDIR = obj/native

CFLAGS += -DMPI1

# source paths
SRCDIR = ../src
VPATH = $(SRCDIR)

# auto dependency generation
DEPENDS = 

SOURCES = \
  apps/imb-3.2.3/src/IMB.c \
  apps/imb-3.2.3/src/IMB_allgather.c \
  apps/imb-3.2.3/src/IMB_allgatherv.c \
  apps/imb-3.2.3/src/IMB_allreduce.c \
  apps/imb-3.2.3/src/IMB_alltoall.c \
  apps/imb-3.2.3/src/IMB_alltoallv.c \
  apps/imb-3.2.3/src/IMB_barrier.c \
  apps/imb-3.2.3/src/IMB_bcast.c \
  apps/imb-3.2.3/src/IMB_benchlist.c \
  apps/imb-3.2.3/src/IMB_cpu_exploit.c \
  apps/imb-3.2.3/src/IMB_declare.c \
  apps/imb-3.2.3/src/IMB_err_handler.c \
  apps/imb-3.2.3/src/IMB_exchange.c \
  apps/imb-3.2.3/src/IMB_g_info.c \
  apps/imb-3.2.3/src/IMB_gather.c \
  apps/imb-3.2.3/src/IMB_gatherv.c \
  apps/imb-3.2.3/src/IMB_init.c \
  apps/imb-3.2.3/src/IMB_init_transfer.c \
  apps/imb-3.2.3/src/IMB_mem_manager.c \
  apps/imb-3.2.3/src/IMB_output.c \
  apps/imb-3.2.3/src/IMB_parse_name_mpi1.c \
  apps/imb-3.2.3/src/IMB_pingpong.c \
  apps/imb-3.2.3/src/IMB_pingping.c \
  apps/imb-3.2.3/src/IMB_reduce.c \
  apps/imb-3.2.3/src/IMB_reduce_scatter.c \
  apps/imb-3.2.3/src/IMB_scatter.c \
  apps/imb-3.2.3/src/IMB_scatterv.c \
  apps/imb-3.2.3/src/IMB_sendrecv.c \
  apps/imb-3.2.3/src/IMB_strgs.c \
  apps/imb-3.2.3/src/IMB_warm_up.c

OBJECTS = $(SOURCES:%.c=$(OBJDIR)/%.o)
DEPENDS = $(OBJECTS:%.o=%.d)

$(BINDIR)/native/IMB: $(OBJECTS)
	@[ -d $(@D) ] || (mkdir -p $(@D))
	@echo linking: $@
	@$(CXX) $(LDFLAGS) -o $@ $^
	@echo successfully built: $@
	@echo

include rules.mk

# include auto-generated dependencies
-include $(DEPENDS)

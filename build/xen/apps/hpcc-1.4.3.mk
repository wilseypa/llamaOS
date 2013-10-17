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

MAKEFILE_SOURCES += apps/hpcc-$(HPCC_VERSION).mk

CFLAGS += \
  -I $(INCDIR)/llamaos/mpi \
  -I $(INCDIR) \
  -I $(SRCDIR)/apps/hpcc-$(HPCC_VERSION)/include \
  -I $(SRCDIR)/apps/hpcc-$(HPCC_VERSION)/hpl/include \
  -D__XEN_INTERFACE_VERSION__=0x00030205 \
  -include $(SRCDIR)/llamaos/__thread.h \
  -D LONG_IS_64BITS \
  -D HPL_USE_CLOCK

VPATH = $(SRCDIR)

SOURCES = \
  apps/hpcc-$(HPCC_VERSION)/FFT/bcnrand.c \
  apps/hpcc-$(HPCC_VERSION)/FFT/fft235.c \
  apps/hpcc-$(HPCC_VERSION)/FFT/mpifft.c \
  apps/hpcc-$(HPCC_VERSION)/FFT/pzfft1d.c \
  apps/hpcc-$(HPCC_VERSION)/FFT/wrapmpifftw.c \
  apps/hpcc-$(HPCC_VERSION)/FFT/zfft1d.c \
  apps/hpcc-$(HPCC_VERSION)/hpl/src/grid/HPL_all_reduce.c \
  apps/hpcc-$(HPCC_VERSION)/hpl/src/grid/HPL_barrier.c \
  apps/hpcc-$(HPCC_VERSION)/hpl/src/grid/HPL_broadcast.c \
  apps/hpcc-$(HPCC_VERSION)/hpl/src/grid/HPL_grid_exit.c \
  apps/hpcc-$(HPCC_VERSION)/hpl/src/grid/HPL_grid_info.c \
  apps/hpcc-$(HPCC_VERSION)/hpl/src/grid/HPL_grid_init.c \
  apps/hpcc-$(HPCC_VERSION)/hpl/src/grid/HPL_max.c \
  apps/hpcc-$(HPCC_VERSION)/hpl/src/grid/HPL_min.c \
  apps/hpcc-$(HPCC_VERSION)/hpl/src/grid/HPL_pnum.c \
  apps/hpcc-$(HPCC_VERSION)/hpl/src/grid/HPL_reduce.c \
  apps/hpcc-$(HPCC_VERSION)/hpl/src/grid/HPL_sum.c \
  apps/hpcc-$(HPCC_VERSION)/hpl/src/pauxil/HPL_pabort.c \
  apps/hpcc-$(HPCC_VERSION)/hpl/src/pauxil/HPL_pdlamch.c \
  apps/hpcc-$(HPCC_VERSION)/hpl/src/pauxil/HPL_pwarn.c \
  apps/hpcc-$(HPCC_VERSION)/hpl/src/HPL_dlamch.c \
  apps/hpcc-$(HPCC_VERSION)/hpl/src/HPL_fprintf.c \
  apps/hpcc-$(HPCC_VERSION)/hpl/src/HPL_warn.c \
  apps/hpcc-$(HPCC_VERSION)/hpl/testing/ptest/HPL_pdinfo.c \
  apps/hpcc-$(HPCC_VERSION)/hpl/testing/timer/HPL_timer_cputime.c \
  apps/hpcc-$(HPCC_VERSION)/RandomAccess/buckets.c \
  apps/hpcc-$(HPCC_VERSION)/RandomAccess/heap.c \
  apps/hpcc-$(HPCC_VERSION)/RandomAccess/MPIRandomAccess.c \
  apps/hpcc-$(HPCC_VERSION)/RandomAccess/pool.c \
  apps/hpcc-$(HPCC_VERSION)/RandomAccess/time_bound.c \
  apps/hpcc-$(HPCC_VERSION)/RandomAccess/utility.c \
  apps/hpcc-$(HPCC_VERSION)/RandomAccess/verification.c \
  apps/hpcc-$(HPCC_VERSION)/src/bench_lat_bw_1.5.2.c \
  apps/hpcc-$(HPCC_VERSION)/src/extfinalize.c \
  apps/hpcc-$(HPCC_VERSION)/src/extinit.c \
  apps/hpcc-$(HPCC_VERSION)/src/hpcc.c \
  apps/hpcc-$(HPCC_VERSION)/src/HPL_slamch.c \
  apps/hpcc-$(HPCC_VERSION)/src/io.c \
  apps/hpcc-$(HPCC_VERSION)/src/noopt.c

OBJECTS = $(SOURCES:%.c=$(OBJDIR)/%.o)
DEPENDS = $(OBJECTS:%.o=%.d)

$(BINDIR)/apps/hpcc: $(OBJECTS) $(LIBDIR)/llamaMPI.a $(LIBDIR)/llamaOS.a $(LIBDIR)/sys/stdc++.a $(LIBDIR)/sys/gcc.a $(LIBDIR)/sys/glibc.a
	@[ -d $(@D) ] || (mkdir -p $(@D))
	@echo linking: $@
	@$(LD) $(LDFLAGS) -T llamaOS.lds -o $@ $^
	@gzip -c -f --best $@ >$@.gz
	@echo successfully built: $@
	@echo

include rules.mk

# include auto-generated dependencies
-include $(DEPENDS)

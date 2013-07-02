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

MAKEFILE_SOURCES += apps/NAS/NAS-lu.mk

F77FLAGS += \
  -I $(INCDIR) \
  -I $(INCDIR)/llamaos/mpi \
  -I util/NAS/lu \
  -D__XEN_INTERFACE_VERSION__=0x00030205 \
  -include $(SRCDIR)/llamaos/__thread.h

VPATH = $(SRCDIR)

SOURCES = \
  apps/NPB3.2-MPI/LU/bcast_inputs.f \
  apps/NPB3.2-MPI/LU/blts.f \
  apps/NPB3.2-MPI/LU/buts.f \
  apps/NPB3.2-MPI/LU/erhs.f \
  apps/NPB3.2-MPI/LU/error.f \
  apps/NPB3.2-MPI/LU/exact.f \
  apps/NPB3.2-MPI/LU/exchange_1.f \
  apps/NPB3.2-MPI/LU/exchange_3.f \
  apps/NPB3.2-MPI/LU/exchange_4.f \
  apps/NPB3.2-MPI/LU/exchange_5.f \
  apps/NPB3.2-MPI/LU/exchange_6.f \
  apps/NPB3.2-MPI/LU/init_comm.f \
  apps/NPB3.2-MPI/LU/jacld.f \
  apps/NPB3.2-MPI/LU/jacu.f \
  apps/NPB3.2-MPI/LU/l2norm.f \
  apps/NPB3.2-MPI/LU/lu.f \
  apps/NPB3.2-MPI/LU/neighbors.f \
  apps/NPB3.2-MPI/LU/nodedim.f \
  apps/NPB3.2-MPI/LU/pintgr.f \
  apps/NPB3.2-MPI/LU/proc_grid.f \
  apps/NPB3.2-MPI/LU/read_input.f \
  apps/NPB3.2-MPI/LU/rhs.f \
  apps/NPB3.2-MPI/LU/setbv.f \
  apps/NPB3.2-MPI/LU/setcoeff.f \
  apps/NPB3.2-MPI/LU/sethyper.f \
  apps/NPB3.2-MPI/LU/setiv.f \
  apps/NPB3.2-MPI/LU/ssor.f \
  apps/NPB3.2-MPI/LU/subdomain.f \
  apps/NPB3.2-MPI/LU/verify.f \
  apps/NPB3.2-MPI/common/timers.f \
  apps/NPB3.2-MPI/common/randi8.f \
  apps/NPB3.2-MPI/common/print_results.f

OBJECTS = $(SOURCES:%.f=$(OBJDIR)/%.o)
DEPENDS = $(OBJECTS:%.o=%.d)

$(BINDIR)/NAS/lu: $(OBJECTS) $(LIBDIR)/llamaMPIF.a $(LIBDIR)/llamaMPI.a $(LIBDIR)/llamaOS.a $(LIBDIR)/stdc++.a $(LIBDIR)/gfortran.a $(LIBDIR)/gcc.a $(LIBDIR)/glibc.a
	@[ -d $(@D) ] || (mkdir -p $(@D))
	@echo linking: $@
	@$(LD) $(LDFLAGS) -T llamaOS.lds -o $@ $^
	@gzip -c -f --best $@ >$@.gz
	@echo successfully built: $@
	@echo

include rules.mk

# include auto-generated dependencies
-include $(DEPENDS)

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

.PHONY: all
all:
	@$(MAKE) -f apps/hello-f77.mk
	@$(MAKE) -f apps/hello-f90.mk
	@$(MAKE) -f apps/latency-TCPIP.mk
	@$(MAKE) -f apps/netpipe-$(NETPIPE_VERSION)-memcpy.mk
	@$(MAKE) -f apps/netpipe-$(NETPIPE_VERSION)-tcp.mk
	@-command -v $(MPICC) >/dev/null && ($(MAKE) -f apps/IMB-$(IMB_VERSION).mk)
	@-command -v $(MPICC) >/dev/null && ($(MAKE) -f apps/latency-MPI.mk)
	@-command -v $(MPICC) >/dev/null && ($(MAKE) -f apps/netpipe-$(NETPIPE_VERSION)-mpi.mk)
#	@$(MAKE) -f test/memory.mk

#	@$(MAKE) -f apps/NAS/NAS.mk

.PHONY: install
install:

.PHONY: clean
clean:
	@echo cleaning build folder...
	@echo removing: $(OBJDIR)
	@rm -rf $(OBJDIR)
	@echo removing: $(BINDIR)
	@rm -rf $(BINDIR)
	@echo removing: $(LIBDIR)
	@rm -rf $(LIBDIR)
	@echo removing: $(INCDIR)
	@rm -rf $(INCDIR)

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

# make parameters
MAKEFLAGS = --silent

# include common variables
include common-vars.mk

MAKEFILE_SOURCES += Makefile

INSTALL_DIR = ~
INSTALL_FOLDER = $(INSTALL_DIR)/llamaOS-$(LLAMAOS_VERSION)

.PHONY: all
all: sys llamaOS tools apps-imb apps-net apps-netpipe

# apps-warped

.PHONY: sys
sys:
	@$(MAKE) -f sys/glibc-$(GLIBC_VERSION).mk
	@$(MAKE) -f sys/stdc++-$(GCC_VERSION).mk
	@$(MAKE) -f sys/gfortran-$(GCC_VERSION).mk
	@$(MAKE) -f sys/gcc-$(GCC_VERSION).mk
	@$(MAKE) -f sys/xen-$(XEN_VERSION).mk

.PHONY: llamaOS
llamaOS: sys
	@$(MAKE) -f llamaOS.mk

.PHONY: tools
tools: llamaOS
	@$(MAKE) -f tools/blas.mk
	@$(MAKE) -f tools/cblas.mk
	@$(MAKE) -f tools/gtest-$(GTEST_VERSION).mk
	@$(MAKE) -f tools/tinyxml-$(TINYXML_VERSION).mk
	@$(MAKE) -f tools/mpich-$(MPICH_VERSION).mk

.PHONY: apps-bonnie
apps-bonnie: llamaOS
	@$(MAKE) -f apps/bonnie/bonnie.mk

.PHONY: apps-hpcc
apps-hpcc: tools llamaOS
	@$(MAKE) -f apps/hpcc-$(HPCC_VERSION).mk

.PHONY: apps-imb
apps-imb: tools llamaOS
	@$(MAKE) -f apps/imb-$(IMB_VERSION)/imb.mk

.PHONY: apps-net
apps-net: llamaOS
#	@$(MAKE) -f apps/net/intel.mk
	@$(MAKE) -f apps/net/shmem.mk

.PHONY: apps-mpich-examples
apps-mpich-examples: tools llamaOS
	@$(MAKE) -f apps/mpich-$(MPICH_VERSION)/examples/f77/fpi.mk
	@$(MAKE) -f apps/mpich-$(MPICH_VERSION)/examples/f77/hellow.mk
	@$(MAKE) -f apps/mpich-$(MPICH_VERSION)/examples/f90/pi3f90.mk
	@$(MAKE) -f apps/mpich-$(MPICH_VERSION)/examples/cpi.mk
	@$(MAKE) -f apps/mpich-$(MPICH_VERSION)/examples/hellow.mk
	@$(MAKE) -f apps/mpich-$(MPICH_VERSION)/examples/srtest.mk

.PHONY: apps-netpipe
apps-netpipe: tools llamaOS
	@$(MAKE) -f apps/netpipe-$(NETPIPE_VERSION)/llamaNET.mk
	@$(MAKE) -f apps/netpipe-$(NETPIPE_VERSION)/memcpy.mk
	@$(MAKE) -f apps/netpipe-$(NETPIPE_VERSION)/nothing.mk
	@$(MAKE) -f apps/netpipe-$(NETPIPE_VERSION)/mpi.mk

.PHONY: apps-unixbench
apps-unixbench: llamaOS
	@$(MAKE) -f apps/unixbench-5.1.3/syscall.mk
	@$(MAKE) -f apps/unixbench-5.1.3/whetstone.mk

.PHONY: apps-warped
apps-warped: tools llamaOS
	@[ -z $(WARPED_VERSION) -a -z $(WARPED_DIR) ] || ($(MAKE) -f apps/warped-$(WARPED_VERSION)/warped.mk)
	@[ -z $(WARPED_VERSION) -a -z $(WARPED_MODELS_DIR) ] || ($(MAKE) -f apps/warped-$(WARPED_VERSION)/warped-models.mk)

.PHONY: test-apps
test-apps: llamaOS
	@$(MAKE) -f test/apps/hello-c.mk
	@$(MAKE) -f test/apps/hello-cpp.mk
	@$(MAKE) -f test/apps/hello-f77.mk
	@$(MAKE) -f test/apps/hello-f90.mk
	@$(MAKE) -f test/apps/memory.mk
	@$(MAKE) -f test/apps/mpich.mk
	@$(MAKE) -f test/apps/testExt2.mk
	@$(MAKE) -f test/apps/time.mk
	@$(MAKE) -f test/apps/tinyxml.mk

#	@$(MAKE) -f llamaMPI.mk
#	@$(MAKE) -f llamaMPIF.mk
#	@$(MAKE) -f apps/latency-MPI.mk
#	@$(MAKE) -f apps/latency-llamaNET.mk
#	@$(MAKE) -f apps/pingPongNB-MPI.mk
#	@$(MAKE) -f net/i82574.mk
#	@$(MAKE) -f net/lspci.mk
#	@$(MAKE) -f test/apps/testMPI.mk
#	@$(MAKE) -f test/apps/testMPIF.mk
#	@$(MAKE) -f test/empty.mk
#	@$(MAKE) -f test/memory.mk
#	@$(MAKE) -f apps/NAS/NAS.mk
#	@$(MAKE) -f apps/WARPED/WARPED.mk

#	@$(MAKE) -f test/memory.mk

.PHONY: install
install:
	@echo installing llamaOS into $(INSTALL_FOLDER)...
	@[ -d $(INSTALL_FOLDER) ] || (mkdir -p $(INSTALL_FOLDER))
	@cp -r bin $(INSTALL_FOLDER)/bin
	@cp -r lib $(INSTALL_FOLDER)/lib
	@cp -r include $(INSTALL_FOLDER)/include
	@cp -r ../../script $(INSTALL_FOLDER)/script
	@cp llamaOS.lds $(INSTALL_FOLDER)/llamaOS.lds
	@echo adjusting file attributes...
	@chmod -R o+r $(INSTALL_FOLDER)
	@echo install complete.
	@echo 

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

.PHONY: check
check:
	@$(MAKE) -f llamaOS.mk check

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
INSTALL_FOLDER = $(INSTALL_DIR)/llamaOS-1.0

.PHONY: all
all:
	@$(MAKE) -f glibc-$(GLIBC_VERSION).mk
	@$(MAKE) -f stdc++-$(GCC_VERSION).mk
	@$(MAKE) -f gfortran-$(GCC_VERSION).mk
	@$(MAKE) -f gcc-$(GCC_VERSION).mk
	@$(MAKE) -f tinyxml-$(TINYXML_VERSION).mk
	@$(MAKE) -f xen-$(XEN_VERSION).mk
	@$(MAKE) -f llamaOS.mk
	@$(MAKE) -f llamaMPI.mk
	@$(MAKE) -f llamaMPIF.mk
	@$(MAKE) -f apps/NAS/NAS.mk
	@$(MAKE) -f apps/hello-c.mk
	@$(MAKE) -f apps/hello-cpp.mk
	@$(MAKE) -f apps/hello-f77-llamaOS.mk
	@$(MAKE) -f apps/hello-f90-llamaOS.mk
	@$(MAKE) -f apps/IMB-llamaMPI.mk
	@$(MAKE) -f apps/latency-llamaMPI.mk
	@$(MAKE) -f apps/latency-llamaNET.mk
	@$(MAKE) -f apps/netpipe-3.7.2-llamaNET.mk
	@$(MAKE) -f apps/netpipe-3.7.2-memcpy.mk
	@$(MAKE) -f apps/netpipe-3.7.2-mpi.mk
	@$(MAKE) -f apps/testMPI-llamaMPI.mk
	@$(MAKE) -f apps/testMPIF-llamaMPI.mk
	@$(MAKE) -f apps/pingPongNB-llamaMPI.mk
	@$(MAKE) -f apps/tinyxml.mk
	@$(MAKE) -f apps/WARPED/WARPED.mk
	@$(MAKE) -f net/i82574.mk
	@$(MAKE) -f net/lspci.mk
	@$(MAKE) -f tests/empty.mk

#	@$(MAKE) -f test/memory.mk

.PHONY: install
install:
	@echo installing llamaOS into $(INSTALL_FOLDER) folder...
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

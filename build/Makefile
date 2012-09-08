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

MAKEFILE_SOURCES += Makefile

.PHONY: all
all:
	@$(MAKE) -f glibc-$(GLIBC_VERSION).mk
	@$(MAKE) -f gcc-$(GCC_VERSION).mk
	@$(MAKE) -f xen-$(XEN_VERSION).mk
	@$(MAKE) -f llamaOS.mk xen
	@$(MAKE) -f apps/hello.mk xen
	@$(MAKE) -f minimal/minimal.mk xen
	@$(MAKE) -f minimal/minimal-glibc.mk xen
	@$(MAKE) -f minimal/minimal-gcc.mk xen

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
	@echo removing: include-fixed
	@rm -rf include-fixed

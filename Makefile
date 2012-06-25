
# include common makefile variables
include common.mk
MAKEFILE_SOURCES += Makefile

# list of system libraries ported to llamaOS
SYSLIBS = \
  stdc++ \
  supc++ \
  unwind \
  glibc

SYSLIB_LINKS = $(SYSLIBS:%=$(LIBDIR)/%.a)
export SYSLIB_LINKS

# list of compatible hypervisor interfaces
VMMLIBS = \
  xen \
  hvm \
  kvm

# list of standard llamaNET drivers
NETS = \
  i82574

# list of standard llamaOS apps
APPS = \
  hello \
  latency-tcp-linux

# include list of custom llamaOS apps
-include apps.mk

.PHONY: all
all: syslibs vmmlibs llamaos nets apps gtest test-xen

.PHONY: clean
clean:
	@echo removing: $(OBJDIR)
	@rm -rf $(OBJDIR)
	@echo removing: $(BINDIR)
	@rm -rf $(BINDIR)
	@echo removing: $(LIBDIR)
	@rm -rf $(LIBDIR)

.PHONY: check
check:
	@echo running cppcheck on src
	@cppcheck src

.PHONY: syslibs
syslibs:
	@$(MAKE) $(SYSLIBS)

.PHONY: $(SYSLIBS)
$(SYSLIBS):
	@$(MAKE) -f $@.mk

.PHONY: vmmlibs
vmmlibs:
	@$(MAKE) $(VMMLIBS)

.PHONY: $(VMMLIBS)
$(VMMLIBS):
	@$(MAKE) -f $@.mk

.PHONY: llamaos
llamaos:
	@$(MAKE) -f $@.mk

.PHONY: nets
nets:
	@$(MAKE) $(NETS)

.PHONY: $(NETS)
$(NETS):
	@$(MAKE) -f $@.mk VMM=xen

.PHONY: apps
apps:
	@$(MAKE) $(APPS)

.PHONY: $(APPS)
$(APPS):
	@$(MAKE) -f $@.mk VMM=xen

.PHONY: gtest
gtest:
	@$(MAKE) -f $@.mk

.PHONY: test-xen
test-xen:
	@$(MAKE) -f $@.mk VMM=xen

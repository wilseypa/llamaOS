
# include common makefile variables
include common.mk

# list of makefiles that should cause a total rebuild
MAKE_SOURCES = \
  Makefile \
  common.mk \
  custom.mk \
  rules

# list of system libraries ported to llamaOS
SYSLIBS = \
  glibc \
  unwind \
  supc++ \
  stdc++

# list of compatible hypervisor interfaces
VMMLIBS = \
  xen

# list of standard llamaOS apps
APPS = \
  hello

# include list of custom llamaOS apps
-include apps.mk

.PHONY: all
all: syslibs vmmlibs llamaos apps

.PHONY: clean
clean:
	@echo removing: $(OBJDIR)
	@rm -rf $(OBJDIR)
	@echo removing: $(BINDIR)
	@rm -rf $(BINDIR)
	@echo removing: $(LIBDIR)
	@rm -rf $(LIBDIR)

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

.PHONY: apps
apps:
	@$(MAKE) $(APPS)

.PHONY: $(APPS)
$(APPS):
	@$(MAKE) -f $@.mk VMM=xen

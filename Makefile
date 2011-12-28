
include common.mk

MAKE_SOURCES = \
  Makefile \
  common.mk \
  custom.mk \
  rules

SYSLIBS = \
  glibc \
  unwind \
  supc++ \
  stdc++

VMMLIBS = \
  xen

.PHONY: all
all: syslibs vmmlibs

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

.PHONY: vmmlibs
vmmlibs:
	@$(MAKE) $(VMMLIBS)

.PHONY: $(SYSLIBS)
$(SYSLIBS):
	@$(MAKE) -f $@.mk

.PHONY: $(VMMLIBS)
$(VMMLIBS):
	@$(MAKE) -f $@.mk


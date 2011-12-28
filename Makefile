
MAKE_SOURCES = Makefile common.mk rules.mk

include common.mk

.PHONY: all
all: llamaOS

# all: ewarped-xen $(BINDIR)/domain_config check test doc

.PHONY: clean
clean: 
	@echo removing: $(OBJDIR)
	@rm -rf $(OBJDIR)
	@echo removing: $(BINDIR)
	@rm -rf $(BINDIR)
	@echo removing: $(LIBDIR)
	@rm -rf $(LIBDIR)

.PHONY: llamaOS
llamaOS: glibc unwind
	@echo building llamaOS...

.PHONY: glibc
glibc:
	@$(MAKE) -f glibc.mk

.PHONY: unwind
unwind:
	@$(MAKE) -f unwind.mk

include rules.mk

# include auto-generated dependencies
ifneq ($(MAKECMDGOALS),clean)
-include $(DEPENDS)
endif

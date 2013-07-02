
# include common variables
include common-vars.mk

MAKEFILE_SOURCES += apps/NAS/NAS.mk

.PHONY: all
all:
	@$(MAKE) -f apps/NAS/setparams.mk
	@$(MAKE) -f apps/NAS/NAS-cg.mk
	@$(MAKE) -f apps/NAS/NAS-dt.mk
	@$(MAKE) -f apps/NAS/NAS-ep.mk
	@$(MAKE) -f apps/NAS/NAS-ft.mk	
	@$(MAKE) -f apps/NAS/NAS-is.mk
	@$(MAKE) -f apps/NAS/NAS-lu.mk
	@$(MAKE) -f apps/NAS/NAS-mg.mk
	@$(MAKE) -f apps/NAS/NAS-sp.mk

# include common variables
include common.mk

MAKEFILE_SOURCES += apps/NAS/NAS.mk

.PHONY: all
all:
	echo building NAS...
	@$(MAKE) -f apps/NAS/setparams.mk
	$(eval MAKEFILE_SOURCES := util/NAS/npbparams.h)
	@$(MAKE) -f apps/NAS/NAS-dt.mk
	@$(MAKE) -f apps/NAS/NAS-is.mk
	@$(MAKE) -f apps/NAS/NAS-ft.mk

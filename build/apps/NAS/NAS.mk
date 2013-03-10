# include common variables
include common.mk

MAKEFILE_SOURCES += NAS.mk

.PHONY: all
all:
	@$(MAKE) -f apps/NAS/setparams.mk
	$(eval MAKEFILE_SOURCES := util/NAS/npbparams.h)
	@$(MAKE) -f apps/NAS/NAS-dt.mk
	@$(MAKE) -f apps/NAS/NAS-is.mk

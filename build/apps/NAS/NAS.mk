# include common variables
include common.mk

MAKEFILE_SOURCES += NAS.mk

.PHONY: all
all:
	@$(MAKE) -f apps/NAS/setparams.mk
	@$(MAKE) -f apps/NAS/NAS-dt.mk

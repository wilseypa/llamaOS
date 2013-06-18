
# include common variables
include common-vars.mk

MAKEFILE_SOURCES += apps/WARPED/WARPED.mk

.PHONY: all
all:
	@$(MAKE) -f apps/WARPED/llamaWARPED.mk
	@$(MAKE) -f apps/WARPED/phold-llamaWARPED.mk
	@$(MAKE) -f apps/WARPED/raid-llamaWARPED.mk
	@$(MAKE) -f apps/WARPED/smmp-llamaWARPED.mk


# include common variables
include common.mk

VPATH = src

SOURCES = \
  llamaos/apps/hello/main.cpp

include rules.mk

# include auto-generated dependencies
ifneq ($(MAKECMDGOALS),clean)
-include $(DEPENDS)
endif


include common.mk
MAKEFILE_SOURCES += unwind.mk

CFLAGS += -DFIRST_PSEUDO_REGISTER=53
#         -DFIRST_PSEUDO_REGISTER=17

VPATH = gcc

SOURCES = \
  unwind-dw2-fde.c \
  unwind-dw2.c

BINARY = unwind.a
OBJECTS = $(SOURCES:%.c=$(OBJDIR)/%.o)
DEPENDS = $(OBJECTS:%.o=%.d)

$(LIBDIR)/$(BINARY) : $(OBJECTS)
	@[ -d $(@D) ] || (mkdir -p $(@D))
	@echo linking: $@
	@$(AR) r $@ $(OBJECTS)
	@echo successfully built: $@
	@echo

include rules.mk

# include auto-generated dependencies
ifneq ($(MAKECMDGOALS),clean)
-include $(DEPENDS)
endif

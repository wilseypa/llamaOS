
include common.mk
MAKEFILE_SOURCES += xen.mk

INCLUDES = \
  xen/include \
  src

CPPFLAGS += -Wall -Wextra -Weffc++ \
             $(INCLUDES:%=-I %) \
            -D__XEN_INTERFACE_VERSION__=0x00030205

VPATH = src/llamaos/xen

SOURCES = \
  Hypercall.cpp \
  Hypervisor.cpp \
  trace.cpp

BINARY = xen.a
OBJECTS = $(SOURCES:%.cpp=$(OBJDIR)/%.o)
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
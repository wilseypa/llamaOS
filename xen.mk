
include common.mk
MAKEFILE_SOURCES += xen.mk

INCLUDES = \
  xen/include \
  src

CPPFLAGS += -Wall -Wextra -Weffc++ \
             $(INCLUDES:%=-I %) \
            -D__XEN_INTERFACE_VERSION__=0x00030205

VPATH = src

SOURCES = \
  llamaos/memory/Entry.cpp \
  llamaos/memory/memory.cpp \
  llamaos/xen/Console.cpp \
  llamaos/xen/Events.cpp \
  llamaos/xen/glibc_export.cpp \
  llamaos/xen/Grant_table.cpp \
  llamaos/xen/Hypercall.cpp \
  llamaos/xen/Hypervisor.cpp \
  llamaos/xen/memory.cpp \
  llamaos/xen/start.cpp \
  llamaos/xen/trace.cpp \
  llamaos/xen/Traps.cpp \
  llamaos/xen/Xenstore.cpp

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

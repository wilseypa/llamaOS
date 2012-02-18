
include common.mk
MAKEFILE_SOURCES += llamaos.mk

INCLUDES = \
  src

CPPFLAGS += -Wall -Wextra -Weffc++ \
             $(INCLUDES:%=-I %)

VPATH = src

SOURCES = \
  llamaos/api/pci/BAR.cpp \
  llamaos/api/pci/Command.cpp \
  llamaos/api/pci/PCI.cpp \
  llamaos/api/pci/Status.cpp

BINARY = llamaos.a
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

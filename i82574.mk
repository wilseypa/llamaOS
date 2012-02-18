
include common.mk
MAKEFILE_SOURCES += i82574.mk

INCLUDES = \
  xen/include \
  src

ASMFLAGS += $(INCLUDES:%=-I %)
CPPFLAGS += -Wall -Wextra -Weffc++ \
             $(INCLUDES:%=-I %) \
            -D__XEN_INTERFACE_VERSION__=0x00030205

VPATH = src

SOURCES = \
  llamaos/net/i82574/main.cpp

OBJECTS = $(SOURCES:%.cpp=$(OBJDIR)/%.o)
DEPENDS = $(OBJECTS:%.o=%.d)

# the entry object must be the first object listed here or the guest will crash!
$(BINDIR)/i82574-$(VMM): $(OBJDIR)/llamaos/$(VMM)/x86_64.o $(OBJECTS) $(LIBDIR)/$(VMM).a $(LIBDIR)/llamaos.a $(SYSLIB_LINKS)
	@[ -d $(@D) ] || (mkdir -p $(@D))
	@echo linking: $@
	@$(LD) $(LDFLAGS) -T x86_64.lds -o $@ $^
	@gzip -c -f --best $@ >$@.gz
	@echo successfully built: $@
	@echo

include rules.mk

# include auto-generated dependencies
ifneq ($(MAKECMDGOALS),clean)
-include $(DEPENDS)
endif

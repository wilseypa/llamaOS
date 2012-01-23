
include common.mk
MAKEFILE_SOURCES += gtest.mk

# put gtest into its own folder
# OBJDIR += /gtest

INCLUDES = \
  gtest/include \
  gtest

CPPFLAGS += $(INCLUDES:%=-I %) \
            -DGTEST_HAS_PTHREAD=0 -DGTEST_HAS_STREAM_REDIRECTION=0


VPATH = gtest/src

SOURCES = \
  gtest-all.cc

BINARY = gtest.a
OBJECTS = $(SOURCES:%.cc=$(OBJDIR)/%.o)
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

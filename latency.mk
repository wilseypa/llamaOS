
include common.mk
MAKEFILE_SOURCES += latency.mk

INCLUDES = \
  src

ASMFLAGS += $(INCLUDES:%=-I %)
CPPFLAGS += -Wall -Wextra -Weffc++ \
             $(INCLUDES:%=-I %)

VPATH = src

#  llamaos/apps/latency/latency_data.cpp \
#  llamaos/apps/latency/latency_null.cpp \
#  llamaos/apps/latency/latency_time.cpp \

SOURCES = \
  llamaos/apps/latency/main.cpp \
  llamaos/apps/latency/Param.cpp

OBJECTS = $(SOURCES:%.cpp=$(OBJDIR)/%.o)
DEPENDS = $(OBJECTS:%.o=%.d)

# the entry object must be the first object listed here or the guest will crash!
$(BINDIR)/latency-$(VMM): $(OBJDIR)/llamaos/$(VMM)/x86_64.o $(OBJECTS) $(LIBDIR)/$(VMM).a $(LIBDIR)/llamaos.a $(SYSLIB_LINKS)
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

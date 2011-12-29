
include common.mk

CPPFLAGS += -include glibc/include/libc-symbols.h \
            -Wall -Wextra -Weffc++ \
            -D__XEN_INTERFACE_VERSION__=0x00030205

INCLUDES = \
  glibc/include \
  glibc/sysdeps/llamaos \
  glibc/sysdeps/x86_64 \
  glibc/sysdeps/generic \
  glibc/libio \
  glibc \
  gcc/include \
  gcc/libstdc++-v3/include/c_global \
  gcc/libstdc++-v3/include/std \
  gcc/libstdc++-v3/include \
  gcc/libstdc++-v3/libsupc++ \
  xen/include \
  src

CPPFLAGS += $(INCLUDES:%=-I %)

VPATH = src

SOURCES = \
  llamaos/xen/Hypercall.cpp \
  llamaos/xen/Hypervisor.cpp \
  llamaos/xen/trace.cpp

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

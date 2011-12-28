
MAKE_SOURCES = unwind.mk common.mk rules.mk

include common.mk

CFLAGS += -include glibc/include/libc-symbols.h \
          -DFIRST_PSEUDO_REGISTER=53
#          -DFIRST_PSEUDO_REGISTER=17

INCLUDES = \
  glibc/include \
  glibc/sysdeps/llamaos \
  glibc/sysdeps/x86_64 \
  glibc/sysdeps/ieee754/ldbl-128 \
  glibc/sysdeps/ieee754 \
  glibc/sysdeps/generic \
  glibc/libio \
  glibc \
  gcc/include \
  gcc

CFLAGS += $(INCLUDES:%=-I %)

VPATH = src

SOURCES = \
  gcc/unwind-dw2-fde.c \
  gcc/unwind-dw2.c

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

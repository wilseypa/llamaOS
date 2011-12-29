
include common.mk

CPPFLAGS += -include glibc/include/libc-symbols.h \
            -Wall -Wextra -Weffc++

INCLUDES = \
  glibc/include \
  glibc/sysdeps/ucguest \
  glibc/sysdeps/x86_64 \
  glibc/sysdeps/generic \
  glibc/libio \
  glibc \
  gcc/include \
  gcc/libstdc++-v3/include/c_global \
  gcc/libstdc++-v3/include/std \
  gcc/libstdc++-v3/include \
  gcc/libstdc++-v3/libsupc++ \
  xen \
  src

ASMFLAGS += $(INCLUDES:%=-I %)
CPPFLAGS += $(INCLUDES:%=-I %)

VPATH = src

SOURCES = 

OBJECTS = $(SOURCES:%.cpp=$(OBJDIR)/%.o)
DEPENDS = $(OBJECTS:%.o=%.d)

# the entry object must be the first object listed here or the guest will crash!
$(BINDIR)/hello-xen : $(OBJDIR)/llamaos/xen/Entry.o $(OBJECTS) $(LIBDIR)/xen.a $(LIBDIR)/llamaos.a $(LIBDIR)/stdc++.a $(LIBDIR)/supc++.a $(LIBDIR)/unwind.a $(LIBDIR)/glibc.a
	@[ -d $(@D) ] || (mkdir -p $(@D))
	@echo linking: $@
	@$(LD) $(LDFLAGS) -T x86_64.lds -o $@ --start-group $^ --end-group
	@gzip -c -f --best $@ >$@.gz
	@echo successfully built: $@
	@echo

include rules.mk
 
# include auto-generated dependencies
ifneq ($(MAKECMDGOALS),clean)
-include $(DEPENDS)
endif

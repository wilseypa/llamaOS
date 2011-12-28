
MAKE_SOURCES = stdc++.mk common.mk rules.mk

include common.mk

CPPFLAGS += -include glibc/include/libc-symbols.h

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
  gcc \
  gcc/libstdc++-v3/include/c_global \
  gcc/libstdc++-v3/include/std \
  gcc/libstdc++-v3/include \
  gcc/libstdc++-v3/libsupc++

CPPFLAGS += $(INCLUDES:%=-I %)

VPATH = src

SOURCES = \
  gcc/libstdc++-v3/src/allocator-inst.cc \
  gcc/libstdc++-v3/src/c++locale.cc \
  gcc/libstdc++-v3/src/codecvt.cc \
  gcc/libstdc++-v3/src/codecvt_members.cc \
  gcc/libstdc++-v3/src/collate_members.cc \
  gcc/libstdc++-v3/src/compatibility.cc \
  gcc/libstdc++-v3/src/ctype.cc \
  gcc/libstdc++-v3/src/ctype_members.cc \
  gcc/libstdc++-v3/src/functexcept.cc \
  gcc/libstdc++-v3/src/functional.cc \
  gcc/libstdc++-v3/src/future.cc \
  gcc/libstdc++-v3/src/ios-inst.cc \
  gcc/libstdc++-v3/src/ios.cc \
  gcc/libstdc++-v3/src/ios_failure.cc \
  gcc/libstdc++-v3/src/ios.cc \
  gcc/libstdc++-v3/src/ios_init.cc \
  gcc/libstdc++-v3/src/ios_locale.cc \
  gcc/libstdc++-v3/src/iostream-inst.cc \
  gcc/libstdc++-v3/src/istream-inst.cc \
  gcc/libstdc++-v3/src/istream.cc \
  gcc/libstdc++-v3/src/locale-inst.cc \
  gcc/libstdc++-v3/src/locale.cc \
  gcc/libstdc++-v3/src/locale_facets.cc \
  gcc/libstdc++-v3/src/locale_init.cc \
  gcc/libstdc++-v3/src/localename.cc \
  gcc/libstdc++-v3/src/messages_members.cc \
  gcc/libstdc++-v3/src/monetary_members.cc \
  gcc/libstdc++-v3/src/numeric_members.cc \
  gcc/libstdc++-v3/src/ostream-inst.cc \
  gcc/libstdc++-v3/src/regex.cc \
  gcc/libstdc++-v3/src/sstream-inst.cc \
  gcc/libstdc++-v3/src/stdexcept.cc \
  gcc/libstdc++-v3/src/streambuf-inst.cc \
  gcc/libstdc++-v3/src/streambuf.cc \
  gcc/libstdc++-v3/src/string-inst.cc \
  gcc/libstdc++-v3/src/system_error.cc \
  gcc/libstdc++-v3/src/time_members.cc \
  gcc/libstdc++-v3/src/wlocale-inst.cc \
  gcc/libstdc++-v3/src/wstring-inst.cc

BINARY = stdc++.a
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


include common.mk
MAKEFILE_SOURCES += stdc++.mk

VPATH = 

# compile these later
#  ext-inst.cc \
#  strstream.cc \

SOURCES = \
  gcc/libstdc++-v3/src/allocator-inst.cc \
  gcc/libstdc++-v3/src/basic_file.cc \
  gcc/libstdc++-v3/src/bitmap_allocator.cc \
  gcc/libstdc++-v3/src/chrono.cc \
  gcc/libstdc++-v3/src/c++locale.cc \
  gcc/libstdc++-v3/src/codecvt.cc \
  gcc/libstdc++-v3/src/codecvt_members.cc \
  gcc/libstdc++-v3/src/collate_members.cc \
  gcc/libstdc++-v3/src/compatibility.cc \
  gcc/libstdc++-v3/src/complex_io.cc \
  gcc/libstdc++-v3/src/concept-inst.cc \
  gcc/libstdc++-v3/src/ctype.cc \
  gcc/libstdc++-v3/src/ctype_members.cc \
  gcc/libstdc++-v3/src/debug.cc \
  gcc/libstdc++-v3/src/fstream-inst.cc \
  gcc/libstdc++-v3/src/functexcept.cc \
  gcc/libstdc++-v3/src/functional.cc \
  gcc/libstdc++-v3/src/future.cc \
  gcc/libstdc++-v3/src/globals_io.cc \
  gcc/libstdc++-v3/src/ios-inst.cc \
  gcc/libstdc++-v3/src/ios.cc \
  gcc/libstdc++-v3/src/ios_failure.cc \
  gcc/libstdc++-v3/src/ios.cc \
  gcc/libstdc++-v3/src/ios_init.cc \
  gcc/libstdc++-v3/src/ios_locale.cc \
  gcc/libstdc++-v3/src/iostream-inst.cc \
  gcc/libstdc++-v3/src/istream-inst.cc \
  gcc/libstdc++-v3/src/istream.cc \
  gcc/libstdc++-v3/src/limits.cc \
  gcc/libstdc++-v3/src/list.cc \
  gcc/libstdc++-v3/src/locale-inst.cc \
  gcc/libstdc++-v3/src/locale.cc \
  gcc/libstdc++-v3/src/locale_facets.cc \
  gcc/libstdc++-v3/src/locale_init.cc \
  gcc/libstdc++-v3/src/localename.cc \
  gcc/libstdc++-v3/src/messages_members.cc \
  gcc/libstdc++-v3/src/misc-inst.cc \
  gcc/libstdc++-v3/src/monetary_members.cc \
  gcc/libstdc++-v3/src/numeric_members.cc \
  gcc/libstdc++-v3/src/ostream-inst.cc \
  gcc/libstdc++-v3/src/placeholders.cc \
  gcc/libstdc++-v3/src/pool_allocator.cc \
  gcc/libstdc++-v3/src/regex.cc \
  gcc/libstdc++-v3/src/sstream-inst.cc \
  gcc/libstdc++-v3/src/stdexcept.cc \
  gcc/libstdc++-v3/src/streambuf-inst.cc \
  gcc/libstdc++-v3/src/streambuf.cc \
  gcc/libstdc++-v3/src/string-inst.cc \
  gcc/libstdc++-v3/src/system_error.cc \
  gcc/libstdc++-v3/src/time_members.cc \
  gcc/libstdc++-v3/src/tree.cc \
  gcc/libstdc++-v3/src/valarray.cc \
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

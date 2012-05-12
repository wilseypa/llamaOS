
include common.mk
MAKEFILE_SOURCES += stdc++.mk

VPATH = 

# compile these later
#  ext-inst.cc \
#  strstream.cc \

SOURCES = \
  gcc/libstdc++-v3/src/c++98/allocator-inst.cc \
  gcc/libstdc++-v3/src/c++98/basic_file.cc \
  gcc/libstdc++-v3/src/c++98/bitmap_allocator.cc \
  gcc/libstdc++-v3/src/c++11/chrono.cc \
  gcc/libstdc++-v3/src/c++98/c++locale.cc \
  gcc/libstdc++-v3/src/c++98/codecvt.cc \
  gcc/libstdc++-v3/src/c++98/codecvt_members.cc \
  gcc/libstdc++-v3/src/c++98/collate_members.cc \
  gcc/libstdc++-v3/src/c++98/compatibility.cc \
  gcc/libstdc++-v3/src/c++98/complex_io.cc \
  gcc/libstdc++-v3/src/c++98/concept-inst.cc \
  gcc/libstdc++-v3/src/c++98/ctype.cc \
  gcc/libstdc++-v3/src/c++98/ctype_configure_char.cc \
  gcc/libstdc++-v3/src/c++98/ctype_members.cc \
  gcc/libstdc++-v3/src/c++11/debug.cc \
  gcc/libstdc++-v3/src/c++11/fstream-inst.cc \
  gcc/libstdc++-v3/src/c++11/functexcept.cc \
  gcc/libstdc++-v3/src/c++11/functional.cc \
  gcc/libstdc++-v3/src/c++11/future.cc \
  gcc/libstdc++-v3/src/c++98/globals_io.cc \
  gcc/libstdc++-v3/src/c++98/ios-inst.cc \
  gcc/libstdc++-v3/src/c++98/ios.cc \
  gcc/libstdc++-v3/src/c++98/ios_failure.cc \
  gcc/libstdc++-v3/src/c++98/ios_init.cc \
  gcc/libstdc++-v3/src/c++98/ios_locale.cc \
  gcc/libstdc++-v3/src/c++98/iostream-inst.cc \
  gcc/libstdc++-v3/src/c++98/istream-inst.cc \
  gcc/libstdc++-v3/src/c++98/istream.cc \
  gcc/libstdc++-v3/src/c++11/limits.cc \
  gcc/libstdc++-v3/src/c++98/list.cc \
  gcc/libstdc++-v3/src/c++98/locale-inst.cc \
  gcc/libstdc++-v3/src/c++98/locale.cc \
  gcc/libstdc++-v3/src/c++98/locale_facets.cc \
  gcc/libstdc++-v3/src/c++98/locale_init.cc \
  gcc/libstdc++-v3/src/c++98/localename.cc \
  gcc/libstdc++-v3/src/c++98/messages_members.cc \
  gcc/libstdc++-v3/src/c++98/misc-inst.cc \
  gcc/libstdc++-v3/src/c++98/monetary_members.cc \
  gcc/libstdc++-v3/src/c++98/numeric_members.cc \
  gcc/libstdc++-v3/src/c++98/ostream-inst.cc \
  gcc/libstdc++-v3/src/c++11/placeholders.cc \
  gcc/libstdc++-v3/src/c++98/pool_allocator.cc \
  gcc/libstdc++-v3/src/c++11/regex.cc \
  gcc/libstdc++-v3/src/c++98/sstream-inst.cc \
  gcc/libstdc++-v3/src/c++98/stdexcept.cc \
  gcc/libstdc++-v3/src/c++98/streambuf-inst.cc \
  gcc/libstdc++-v3/src/c++98/streambuf.cc \
  gcc/libstdc++-v3/src/c++11/string-inst.cc \
  gcc/libstdc++-v3/src/c++11/system_error.cc \
  gcc/libstdc++-v3/src/c++98/time_members.cc \
  gcc/libstdc++-v3/src/c++98/tree.cc \
  gcc/libstdc++-v3/src/c++98/valarray.cc \
  gcc/libstdc++-v3/src/c++98/wlocale-inst.cc \
  gcc/libstdc++-v3/src/c++11/wstring-inst.cc

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

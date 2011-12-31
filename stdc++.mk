
include common.mk
MAKEFILE_SOURCES += stdc++.mk

VPATH = gcc/libstdc++-v3/src

# compile these later
#  ext-inst.cc \
#  strstream.cc \

SOURCES = \
  allocator-inst.cc \
  basic_file.cc \
  bitmap_allocator.cc \
  chrono.cc \
  c++locale.cc \
  codecvt.cc \
  codecvt_members.cc \
  collate_members.cc \
  compatibility.cc \
  complex_io.cc \
  concept-inst.cc \
  ctype.cc \
  ctype_members.cc \
  debug.cc \
  fstream-inst.cc \
  functexcept.cc \
  functional.cc \
  future.cc \
  globals_io.cc \
  ios-inst.cc \
  ios.cc \
  ios_failure.cc \
  ios.cc \
  ios_init.cc \
  ios_locale.cc \
  iostream-inst.cc \
  istream-inst.cc \
  istream.cc \
  limits.cc \
  list.cc \
  locale-inst.cc \
  locale.cc \
  locale_facets.cc \
  locale_init.cc \
  localename.cc \
  messages_members.cc \
  misc-inst.cc \
  monetary_members.cc \
  numeric_members.cc \
  ostream-inst.cc \
  placeholders.cc \
  pool_allocator.cc \
  regex.cc \
  sstream-inst.cc \
  stdexcept.cc \
  streambuf-inst.cc \
  streambuf.cc \
  string-inst.cc \
  system_error.cc \
  time_members.cc \
  tree.cc \
  valarray.cc \
  wlocale-inst.cc \
  wstring-inst.cc

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

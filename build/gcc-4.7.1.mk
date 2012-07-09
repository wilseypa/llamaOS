#
# Copyright (c) 2012, William Magato
# All rights reserved.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions are met:
#
#    1. Redistributions of source code must retain the above copyright notice,
#       this list of conditions and the following disclaimer.
#
#    2. Redistributions in binary form must reproduce the above copyright
#       notice, this list of conditions and the following disclaimer in the
#       documentation and/or other materials provided with the distribution.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDER(S) AND CONTRIBUTORS
# ''AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
# TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
# PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER(S) OR
# CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
# EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
# PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
# OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
# WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
# OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
# ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
# 
# The views and conclusions contained in the software and documentation are
# those of the authors and should not be interpreted as representing official
# policies, either expressed or implied, of the copyright holder(s) or
# contributors.
#

# include common variables
include common.mk

# include the gcc object list
include gcc-obj-$(GCC_VERSION).mk

MAKEFILE_SOURCES += gcc-$(GCC_VERSION).mk

CFLAGS += \
  -I $(SRCDIR)/gcc-$(GCC_VERSION)/gcc \
  -I $(SRCDIR)/gcc-$(GCC_VERSION)/gcc/ginclude \
  -I $(SRCDIR)/gcc-$(GCC_VERSION)/gcc/include \
  -I $(SRCDIR)/gcc-$(GCC_VERSION)/gcc/include-fixed \
  -I $(SRCDIR)/gcc-$(GCC_VERSION)/include \
  -I $(INCDIR) \
  -DFIRST_PSEUDO_REGISTER=53

CPPFLAGS += \
  -I $(SRCDIR)/gcc-$(GCC_VERSION)/libstdc++-v3/include/backward \
  -I $(SRCDIR)/gcc-$(GCC_VERSION)/libstdc++-v3/include/c_global \
  -I $(SRCDIR)/gcc-$(GCC_VERSION)/libstdc++-v3/include/std \
  -I $(SRCDIR)/gcc-$(GCC_VERSION)/libstdc++-v3/include \
  -I $(SRCDIR)/gcc-$(GCC_VERSION)/libstdc++-v3/libsupc++ \
  -I $(SRCDIR)/gcc-$(GCC_VERSION)/gcc/include-fixed \
  -I $(SRCDIR)/gcc-$(GCC_VERSION)/gcc/ginclude \
  -I $(SRCDIR)/gcc-$(GCC_VERSION)/include \
  -I $(INCDIR)

HEADERS = \
  $(INCDIR)/backward/binders.h \
  $(INCDIR)/bits/allocator.h \
  $(INCDIR)/bits/atomic_lockfree_defines.h \
  $(INCDIR)/bits/atomic_word.h \
  $(INCDIR)/bits/basic_ios.h \
  $(INCDIR)/bits/basic_ios.tcc \
  $(INCDIR)/bits/basic_string.h \
  $(INCDIR)/bits/basic_string.tcc \
  $(INCDIR)/bits/c++allocator.h \
  $(INCDIR)/bits/c++config.h \
  $(INCDIR)/bits/c++locale.h \
  $(INCDIR)/bits/char_traits.h \
  $(INCDIR)/bits/concept_check.h \
  $(INCDIR)/bits/cpp_type_traits.h \
  $(INCDIR)/bits/cpu_defines.h \
  $(INCDIR)/bits/ctype_base.h \
  $(INCDIR)/bits/ctype_inline.h \
  $(INCDIR)/bits/cxxabi_forced.h \
  $(INCDIR)/bits/exception_defines.h \
  $(INCDIR)/bits/exception_ptr.h \
  $(INCDIR)/bits/functexcept.h \
  $(INCDIR)/bits/functional_hash.h \
  $(INCDIR)/bits/gthr.h \
  $(INCDIR)/bits/gthr-default.h \
  $(INCDIR)/bits/hash_bytes.h \
  $(INCDIR)/bits/ios_base.h \
  $(INCDIR)/bits/istream.tcc \
  $(INCDIR)/bits/locale_classes.h \
  $(INCDIR)/bits/locale_classes.tcc \
  $(INCDIR)/bits/locale_facets.h \
  $(INCDIR)/bits/locale_facets.tcc \
  $(INCDIR)/bits/localefwd.h \
  $(INCDIR)/bits/move.h \
  $(INCDIR)/bits/nested_exception.h \
  $(INCDIR)/bits/os_defines.h \
  $(INCDIR)/bits/ostream.tcc \
  $(INCDIR)/bits/ostream_insert.h \
  $(INCDIR)/bits/postypes.h \
  $(INCDIR)/bits/range_access.h \
  $(INCDIR)/bits/stl_algobase.h \
  $(INCDIR)/bits/stl_function.h \
  $(INCDIR)/bits/stl_iterator.h \
  $(INCDIR)/bits/stl_iterator_base_funcs.h \
  $(INCDIR)/bits/stl_iterator_base_types.h \
  $(INCDIR)/bits/stl_pair.h \
  $(INCDIR)/bits/streambuf.tcc \
  $(INCDIR)/bits/streambuf_iterator.h \
  $(INCDIR)/bits/stringfwd.h \
  $(INCDIR)/debug/debug.h \
  $(INCDIR)/ext/atomicity.h \
  $(INCDIR)/ext/new_allocator.h \
  $(INCDIR)/ext/numeric_traits.h \
  $(INCDIR)/ext/string_conversions.h \
  $(INCDIR)/ext/type_traits.h \
  $(INCDIR)/cassert \
  $(INCDIR)/cctype \
  $(INCDIR)/cerrno \
  $(INCDIR)/clocale \
  $(INCDIR)/cstdarg \
  $(INCDIR)/cstdint \
  $(INCDIR)/cstdio \
  $(INCDIR)/cstdlib \
  $(INCDIR)/cstring \
  $(INCDIR)/ctime \
  $(INCDIR)/cwctype \
  $(INCDIR)/cwchar \
  $(INCDIR)/exception \
  $(INCDIR)/float.h \
  $(INCDIR)/initializer_list \
  $(INCDIR)/ios \
  $(INCDIR)/iosfwd \
  $(INCDIR)/iostream \
  $(INCDIR)/istream \
  $(INCDIR)/new \
  $(INCDIR)/ostream \
  $(INCDIR)/stdarg.h \
  $(INCDIR)/stddef.h \
  $(INCDIR)/streambuf \
  $(INCDIR)/string \
  $(INCDIR)/type_traits

#  $(INCDIR)/bits/basic_file.h \
#  $(INCDIR)/bits/c++io.h \
#  $(INCDIR)/bits/codecvt.h \
#  $(INCDIR)/bits/fstream.tcc \
#  $(INCDIR)/bits/locale_facets_nonio.h \
#  $(INCDIR)/bits/locale_facets_nonio.tcc \
#  $(INCDIR)/bits/messages_members.h \
#  $(INCDIR)/bits/time_members.h \
#  $(INCDIR)/ext/stdio_filebuf.h \
#  $(INCDIR)/ext/stdio_sync_filebuf.h \
#  $(INCDIR)/fstream \
#  $(INCDIR)/limits \
#  $(INCDIR)/locale \

.PHONY: all
all : $(GCC_OBJECTS) $(HEADERS)

$(INCDIR)/% : $(SRCDIR)/gcc-$(GCC_VERSION)/libstdc++-v3/include/c_global/%
	@[ -d $(@D) ] || (mkdir -p $(@D))
	@echo copying: $@ from $<
	cp $< $@

$(INCDIR)/% : $(SRCDIR)/gcc-$(GCC_VERSION)/gcc/ginclude/%
	@[ -d $(@D) ] || (mkdir -p $(@D))
	@echo copying: $@ from $<
	cp $< $@

$(INCDIR)/% : $(SRCDIR)/gcc-$(GCC_VERSION)/libstdc++-v3/include/std/%
	@[ -d $(@D) ] || (mkdir -p $(@D))
	@echo copying: $@ from $<
	cp $< $@

$(INCDIR)/% : $(SRCDIR)/gcc-$(GCC_VERSION)/libstdc++-v3/libsupc++/%
	@[ -d $(@D) ] || (mkdir -p $(@D))
	@echo copying: $@ from $<
	cp $< $@

$(INCDIR)/% : $(SRCDIR)/gcc-$(GCC_VERSION)/libstdc++-v3/include/%
	@[ -d $(@D) ] || (mkdir -p $(@D))
	@echo copying: $@ from $<
	cp $< $@

include rules.mk

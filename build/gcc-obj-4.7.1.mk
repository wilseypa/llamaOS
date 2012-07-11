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

# requires this to already be included
# include common.mk

MAKEFILE_SOURCES += gcc-obj-$(GCC_VERSION).mk

GCC_SOURCES_C = \
  gcc-$(GCC_VERSION)/libgcc/unwind-dw2-fde.c \
  gcc-$(GCC_VERSION)/libgcc/unwind-dw2.c

GCC_SOURCES_CC = \
  gcc-$(GCC_VERSION)/libstdc++-v3/libsupc++/array_type_info.cc \
  gcc-$(GCC_VERSION)/libstdc++-v3/libsupc++/bad_alloc.cc \
  gcc-$(GCC_VERSION)/libstdc++-v3/libsupc++/bad_cast.cc \
  gcc-$(GCC_VERSION)/libstdc++-v3/libsupc++/bad_typeid.cc \
  gcc-$(GCC_VERSION)/libstdc++-v3/libsupc++/class_type_info.cc \
  gcc-$(GCC_VERSION)/libstdc++-v3/libsupc++/del_op.cc \
  gcc-$(GCC_VERSION)/libstdc++-v3/libsupc++/del_opnt.cc \
  gcc-$(GCC_VERSION)/libstdc++-v3/libsupc++/del_opv.cc \
  gcc-$(GCC_VERSION)/libstdc++-v3/libsupc++/del_opvnt.cc \
  gcc-$(GCC_VERSION)/libstdc++-v3/libsupc++/dyncast.cc \
  gcc-$(GCC_VERSION)/libstdc++-v3/libsupc++/eh_alloc.cc \
  gcc-$(GCC_VERSION)/libstdc++-v3/libsupc++/eh_aux_runtime.cc \
  gcc-$(GCC_VERSION)/libstdc++-v3/libsupc++/eh_call.cc \
  gcc-$(GCC_VERSION)/libstdc++-v3/libsupc++/eh_catch.cc \
  gcc-$(GCC_VERSION)/libstdc++-v3/libsupc++/eh_exception.cc \
  gcc-$(GCC_VERSION)/libstdc++-v3/libsupc++/eh_globals.cc \
  gcc-$(GCC_VERSION)/libstdc++-v3/libsupc++/eh_ptr.cc \
  gcc-$(GCC_VERSION)/libstdc++-v3/libsupc++/eh_term_handler.cc \
  gcc-$(GCC_VERSION)/libstdc++-v3/libsupc++/eh_personality.cc \
  gcc-$(GCC_VERSION)/libstdc++-v3/libsupc++/eh_terminate.cc \
  gcc-$(GCC_VERSION)/libstdc++-v3/libsupc++/eh_throw.cc \
  gcc-$(GCC_VERSION)/libstdc++-v3/libsupc++/eh_tm.cc \
  gcc-$(GCC_VERSION)/libstdc++-v3/libsupc++/eh_type.cc \
  gcc-$(GCC_VERSION)/libstdc++-v3/libsupc++/eh_unex_handler.cc \
  gcc-$(GCC_VERSION)/libstdc++-v3/libsupc++/enum_type_info.cc \
  gcc-$(GCC_VERSION)/libstdc++-v3/libsupc++/function_type_info.cc \
  gcc-$(GCC_VERSION)/libstdc++-v3/libsupc++/fundamental_type_info.cc \
  gcc-$(GCC_VERSION)/libstdc++-v3/libsupc++/hash_bytes.cc \
  gcc-$(GCC_VERSION)/libstdc++-v3/libsupc++/nested_exception.cc \
  gcc-$(GCC_VERSION)/libstdc++-v3/libsupc++/new_handler.cc \
  gcc-$(GCC_VERSION)/libstdc++-v3/libsupc++/new_op.cc \
  gcc-$(GCC_VERSION)/libstdc++-v3/libsupc++/new_opnt.cc \
  gcc-$(GCC_VERSION)/libstdc++-v3/libsupc++/new_opv.cc \
  gcc-$(GCC_VERSION)/libstdc++-v3/libsupc++/new_opvnt.cc \
  gcc-$(GCC_VERSION)/libstdc++-v3/libsupc++/pbase_type_info.cc \
  gcc-$(GCC_VERSION)/libstdc++-v3/libsupc++/pmem_type_info.cc \
  gcc-$(GCC_VERSION)/libstdc++-v3/libsupc++/pointer_type_info.cc \
  gcc-$(GCC_VERSION)/libstdc++-v3/libsupc++/pure.cc \
  gcc-$(GCC_VERSION)/libstdc++-v3/libsupc++/si_class_type_info.cc \
  gcc-$(GCC_VERSION)/libstdc++-v3/libsupc++/tinfo.cc \
  gcc-$(GCC_VERSION)/libstdc++-v3/libsupc++/tinfo2.cc \
  gcc-$(GCC_VERSION)/libstdc++-v3/libsupc++/vec.cc \
  gcc-$(GCC_VERSION)/libstdc++-v3/libsupc++/vmi_class_type_info.cc \
  gcc-$(GCC_VERSION)/libstdc++-v3/libsupc++/vterminate.cc \
  gcc-$(GCC_VERSION)/libstdc++-v3/src/c++11/chrono.cc \
  gcc-$(GCC_VERSION)/libstdc++-v3/src/c++11/condition_variable.cc \
  gcc-$(GCC_VERSION)/libstdc++-v3/src/c++11/debug.cc \
  gcc-$(GCC_VERSION)/libstdc++-v3/src/c++11/fstream-inst.cc \
  gcc-$(GCC_VERSION)/libstdc++-v3/src/c++11/functexcept.cc \
  gcc-$(GCC_VERSION)/libstdc++-v3/src/c++11/functional.cc \
  gcc-$(GCC_VERSION)/libstdc++-v3/src/c++11/future.cc \
  gcc-$(GCC_VERSION)/libstdc++-v3/src/c++11/limits.cc \
  gcc-$(GCC_VERSION)/libstdc++-v3/src/c++11/mutex.cc \
  gcc-$(GCC_VERSION)/libstdc++-v3/src/c++11/placeholders.cc \
  gcc-$(GCC_VERSION)/libstdc++-v3/src/c++11/regex.cc \
  gcc-$(GCC_VERSION)/libstdc++-v3/src/c++11/shared_ptr.cc \
  gcc-$(GCC_VERSION)/libstdc++-v3/src/c++11/string-inst.cc \
  gcc-$(GCC_VERSION)/libstdc++-v3/src/c++11/system_error.cc \
  gcc-$(GCC_VERSION)/libstdc++-v3/src/c++11/thread.cc \
  gcc-$(GCC_VERSION)/libstdc++-v3/src/c++11/wstring-inst.cc \
  gcc-$(GCC_VERSION)/libstdc++-v3/src/c++98/atomicity.cc \
  gcc-$(GCC_VERSION)/libstdc++-v3/src/c++98/allocator-inst.cc \
  gcc-$(GCC_VERSION)/libstdc++-v3/src/c++98/basic_file.cc \
  gcc-$(GCC_VERSION)/libstdc++-v3/src/c++98/bitmap_allocator.cc \
  gcc-$(GCC_VERSION)/libstdc++-v3/src/c++98/c++locale.cc \
  gcc-$(GCC_VERSION)/libstdc++-v3/src/c++98/codecvt_members.cc \
  gcc-$(GCC_VERSION)/libstdc++-v3/src/c++98/codecvt.cc \
  gcc-$(GCC_VERSION)/libstdc++-v3/src/c++98/collate_members.cc \
  gcc-$(GCC_VERSION)/libstdc++-v3/src/c++98/compatibility-ldbl.cc \
  gcc-$(GCC_VERSION)/libstdc++-v3/src/c++98/compatibility.cc \
  gcc-$(GCC_VERSION)/libstdc++-v3/src/c++98/complex_io.cc \
  gcc-$(GCC_VERSION)/libstdc++-v3/src/c++98/concept-inst.cc \
  gcc-$(GCC_VERSION)/libstdc++-v3/src/c++98/ctype_configure_char.cc \
  gcc-$(GCC_VERSION)/libstdc++-v3/src/c++98/ctype_members.cc \
  gcc-$(GCC_VERSION)/libstdc++-v3/src/c++98/ctype.cc \
  gcc-$(GCC_VERSION)/libstdc++-v3/src/c++98/ext-inst.cc \
  gcc-$(GCC_VERSION)/libstdc++-v3/src/c++98/globals_io.cc \
  gcc-$(GCC_VERSION)/libstdc++-v3/src/c++98/ios-inst.cc \
  gcc-$(GCC_VERSION)/libstdc++-v3/src/c++98/ios.cc \
  gcc-$(GCC_VERSION)/libstdc++-v3/src/c++98/ios_failure.cc \
  gcc-$(GCC_VERSION)/libstdc++-v3/src/c++98/ios_init.cc \
  gcc-$(GCC_VERSION)/libstdc++-v3/src/c++98/ios_locale.cc \
  gcc-$(GCC_VERSION)/libstdc++-v3/src/c++98/iostream-inst.cc \
  gcc-$(GCC_VERSION)/libstdc++-v3/src/c++98/istream-inst.cc \
  gcc-$(GCC_VERSION)/libstdc++-v3/src/c++98/istream.cc \
  gcc-$(GCC_VERSION)/libstdc++-v3/src/c++98/list.cc \
  gcc-$(GCC_VERSION)/libstdc++-v3/src/c++98/locale-inst.cc \
  gcc-$(GCC_VERSION)/libstdc++-v3/src/c++98/locale.cc \
  gcc-$(GCC_VERSION)/libstdc++-v3/src/c++98/locale_facets.cc \
  gcc-$(GCC_VERSION)/libstdc++-v3/src/c++98/locale_init.cc \
  gcc-$(GCC_VERSION)/libstdc++-v3/src/c++98/localename.cc \
  gcc-$(GCC_VERSION)/libstdc++-v3/src/c++98/messages_members.cc \
  gcc-$(GCC_VERSION)/libstdc++-v3/src/c++98/monetary_members.cc \
  gcc-$(GCC_VERSION)/libstdc++-v3/src/c++98/mt_allocator.cc \
  gcc-$(GCC_VERSION)/libstdc++-v3/src/c++98/misc-inst.cc \
  gcc-$(GCC_VERSION)/libstdc++-v3/src/c++98/numeric_members.cc \
  gcc-$(GCC_VERSION)/libstdc++-v3/src/c++98/ostream-inst.cc \
  gcc-$(GCC_VERSION)/libstdc++-v3/src/c++98/parallel_settings.cc \
  gcc-$(GCC_VERSION)/libstdc++-v3/src/c++98/pool_allocator.cc \
  gcc-$(GCC_VERSION)/libstdc++-v3/src/c++98/sstream-inst.cc \
  gcc-$(GCC_VERSION)/libstdc++-v3/src/c++98/stdexcept.cc \
  gcc-$(GCC_VERSION)/libstdc++-v3/src/c++98/streambuf-inst.cc \
  gcc-$(GCC_VERSION)/libstdc++-v3/src/c++98/streambuf.cc \
  gcc-$(GCC_VERSION)/libstdc++-v3/src/c++98/strstream.cc \
  gcc-$(GCC_VERSION)/libstdc++-v3/src/c++98/time_members.cc \
  gcc-$(GCC_VERSION)/libstdc++-v3/src/c++98/tree.cc \
  gcc-$(GCC_VERSION)/libstdc++-v3/src/c++98/valarray.cc \
  gcc-$(GCC_VERSION)/libstdc++-v3/src/c++98/locale-inst.cc

GCC_OBJECTS  = $(GCC_SOURCES_C:%.c=$(OBJDIR)/%.o)
GCC_OBJECTS += $(GCC_SOURCES_CC:%.cc=$(OBJDIR)/%.o)

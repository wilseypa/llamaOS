#
# Copyright (c) 2013, William Magato
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
include common-vars.mk
include common-flags.mk

MAKEFILE_SOURCES += stdc++-$(GCC_VERSION).mk

CFLAGS += \
  -Wno-error \
  -U_FORTIFY_SOURCE \
  -D__USE_FORTIFY_LEVEL=0 \
  -DIN_GLIBCPP_V3 \
  -DHAVE_CONFIG_H \
  -I $(SRCDIR)/gcc-$(GCC_VERSION)/libstdc++-v3 \
  -I $(SRCDIR)/gcc-$(GCC_VERSION)/libiberty \
  -I $(SRCDIR)/gcc-$(GCC_VERSION)/include \
  -I $(SRCDIR)/gcc-$(GCC_VERSION)/libstdc++-v3/include \
  -I $(SRCDIR)/gcc-$(GCC_VERSION)/libcpp/include \
  -I $(SRCDIR)/gcc-$(GCC_VERSION)/gcc \
  -I $(INCDIR)

CPPFLAGS += \
  -Wall \
  -Wextra \
  -Wwrite-strings \
  -Wcast-qual \
  -Wabi \
  -Wno-deprecated \
  -U_FORTIFY_SOURCE \
  -D__USE_FORTIFY_LEVEL=0 \
  -D_GNU_SOURCE \
  -I $(SRCDIR)/gcc-$(GCC_VERSION)/libgcc \
  -I $(SRCDIR)/gcc-$(GCC_VERSION)/libstdc++-v3/include/backward \
  -I $(SRCDIR)/gcc-$(GCC_VERSION)/libstdc++-v3/include \
  -I $(SRCDIR)/gcc-$(GCC_VERSION)/libstdc++-v3/libsupc++ \
  -I $(SRCDIR)/gcc-$(GCC_VERSION)/gcc/include \
  -I $(INCDIR)

VPATH = $(SRCDIR)

C_SOURCES = \
  gcc-$(GCC_VERSION)/libiberty/cp-demangle.c

CC_SOURCES = \
  gcc-$(GCC_VERSION)/libstdc++-v3/libsupc++/array_type_info.cc \
  gcc-$(GCC_VERSION)/libstdc++-v3/libsupc++/atexit_arm.cc \
  gcc-$(GCC_VERSION)/libstdc++-v3/libsupc++/atexit_thread.cc \
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
  gcc-$(GCC_VERSION)/libstdc++-v3/libsupc++/eh_arm.cc \
  gcc-$(GCC_VERSION)/libstdc++-v3/libsupc++/eh_aux_runtime.cc \
  gcc-$(GCC_VERSION)/libstdc++-v3/libsupc++/eh_call.cc \
  gcc-$(GCC_VERSION)/libstdc++-v3/libsupc++/eh_catch.cc \
  gcc-$(GCC_VERSION)/libstdc++-v3/libsupc++/eh_exception.cc \
  gcc-$(GCC_VERSION)/libstdc++-v3/libsupc++/eh_globals.cc \
  gcc-$(GCC_VERSION)/libstdc++-v3/libsupc++/eh_personality.cc \
  gcc-$(GCC_VERSION)/libstdc++-v3/libsupc++/eh_ptr.cc \
  gcc-$(GCC_VERSION)/libstdc++-v3/libsupc++/eh_term_handler.cc \
  gcc-$(GCC_VERSION)/libstdc++-v3/libsupc++/eh_terminate.cc \
  gcc-$(GCC_VERSION)/libstdc++-v3/libsupc++/eh_throw.cc \
  gcc-$(GCC_VERSION)/libstdc++-v3/libsupc++/eh_tm.cc \
  gcc-$(GCC_VERSION)/libstdc++-v3/libsupc++/eh_type.cc \
  gcc-$(GCC_VERSION)/libstdc++-v3/libsupc++/eh_unex_handler.cc \
  gcc-$(GCC_VERSION)/libstdc++-v3/libsupc++/enum_type_info.cc \
  gcc-$(GCC_VERSION)/libstdc++-v3/libsupc++/function_type_info.cc \
  gcc-$(GCC_VERSION)/libstdc++-v3/libsupc++/fundamental_type_info.cc \
  gcc-$(GCC_VERSION)/libstdc++-v3/libsupc++/guard.cc \
  gcc-$(GCC_VERSION)/libstdc++-v3/libsupc++/guard_error.cc \
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
  gcc-$(GCC_VERSION)/libstdc++-v3/src/c++11/compatibility-atomic-c++0x.cc \
  gcc-$(GCC_VERSION)/libstdc++-v3/src/c++11/compatibility-c++0x.cc \
  gcc-$(GCC_VERSION)/libstdc++-v3/src/c++11/compatibility-thread-c++0x.cc \
  gcc-$(GCC_VERSION)/libstdc++-v3/src/c++11/condition_variable.cc \
  gcc-$(GCC_VERSION)/libstdc++-v3/src/c++11/debug.cc \
  gcc-$(GCC_VERSION)/libstdc++-v3/src/c++11/fstream-inst.cc \
  gcc-$(GCC_VERSION)/libstdc++-v3/src/c++11/functexcept.cc \
  gcc-$(GCC_VERSION)/libstdc++-v3/src/c++11/functional.cc \
  gcc-$(GCC_VERSION)/libstdc++-v3/src/c++11/future.cc \
  gcc-$(GCC_VERSION)/libstdc++-v3/src/c++11/hash_c++0x.cc \
  gcc-$(GCC_VERSION)/libstdc++-v3/src/c++11/hashtable_c++0x.cc \
  gcc-$(GCC_VERSION)/libstdc++-v3/src/c++11/limits.cc \
  gcc-$(GCC_VERSION)/libstdc++-v3/src/c++11/mutex.cc \
  gcc-$(GCC_VERSION)/libstdc++-v3/src/c++11/placeholders.cc \
  gcc-$(GCC_VERSION)/libstdc++-v3/src/c++11/random.cc \
  gcc-$(GCC_VERSION)/libstdc++-v3/src/c++11/regex.cc \
  gcc-$(GCC_VERSION)/libstdc++-v3/src/c++11/shared_ptr.cc \
  gcc-$(GCC_VERSION)/libstdc++-v3/src/c++11/string-inst.cc \
  gcc-$(GCC_VERSION)/libstdc++-v3/src/c++11/system_error.cc \
  gcc-$(GCC_VERSION)/libstdc++-v3/src/c++11/thread.cc \
  gcc-$(GCC_VERSION)/libstdc++-v3/src/c++11/wstring-inst.cc \
  gcc-$(GCC_VERSION)/libstdc++-v3/src/c++98/allocator-inst.cc \
  gcc-$(GCC_VERSION)/libstdc++-v3/src/c++98/atomicity.cc \
  gcc-$(GCC_VERSION)/libstdc++-v3/src/c++98/basic_file.cc \
  gcc-$(GCC_VERSION)/libstdc++-v3/src/c++98/bitmap_allocator.cc \
  gcc-$(GCC_VERSION)/libstdc++-v3/src/c++98/c++locale.cc \
  gcc-$(GCC_VERSION)/libstdc++-v3/src/c++98/codecvt.cc \
  gcc-$(GCC_VERSION)/libstdc++-v3/src/c++98/codecvt_members.cc \
  gcc-$(GCC_VERSION)/libstdc++-v3/src/c++98/collate_members.cc \
  gcc-$(GCC_VERSION)/libstdc++-v3/src/c++98/compatibility-debug_list-2.cc \
  gcc-$(GCC_VERSION)/libstdc++-v3/src/c++98/compatibility-debug_list.cc \
  gcc-$(GCC_VERSION)/libstdc++-v3/src/c++98/compatibility.cc \
  gcc-$(GCC_VERSION)/libstdc++-v3/src/c++98/complex_io.cc \
  gcc-$(GCC_VERSION)/libstdc++-v3/src/c++98/concept-inst.cc \
  gcc-$(GCC_VERSION)/libstdc++-v3/src/c++98/ctype.cc \
  gcc-$(GCC_VERSION)/libstdc++-v3/src/c++98/ctype_configure_char.cc \
  gcc-$(GCC_VERSION)/libstdc++-v3/src/c++98/ctype_members.cc \
  gcc-$(GCC_VERSION)/libstdc++-v3/src/c++98/ext-inst.cc \
  gcc-$(GCC_VERSION)/libstdc++-v3/src/c++98/globals_io.cc \
  gcc-$(GCC_VERSION)/libstdc++-v3/src/c++98/hash_tr1.cc \
  gcc-$(GCC_VERSION)/libstdc++-v3/src/c++98/hashtable_tr1.cc \
  gcc-$(GCC_VERSION)/libstdc++-v3/src/c++98/ios-inst.cc \
  gcc-$(GCC_VERSION)/libstdc++-v3/src/c++98/ios.cc \
  gcc-$(GCC_VERSION)/libstdc++-v3/src/c++98/ios_failure.cc \
  gcc-$(GCC_VERSION)/libstdc++-v3/src/c++98/ios_init.cc \
  gcc-$(GCC_VERSION)/libstdc++-v3/src/c++98/ios_locale.cc \
  gcc-$(GCC_VERSION)/libstdc++-v3/src/c++98/iostream-inst.cc \
  gcc-$(GCC_VERSION)/libstdc++-v3/src/c++98/istream-inst.cc \
  gcc-$(GCC_VERSION)/libstdc++-v3/src/c++98/istream.cc \
  gcc-$(GCC_VERSION)/libstdc++-v3/src/c++98/list-aux-2.cc \
  gcc-$(GCC_VERSION)/libstdc++-v3/src/c++98/list-aux.cc \
  gcc-$(GCC_VERSION)/libstdc++-v3/src/c++98/list.cc \
  gcc-$(GCC_VERSION)/libstdc++-v3/src/c++98/list_associated-2.cc \
  gcc-$(GCC_VERSION)/libstdc++-v3/src/c++98/list_associated.cc \
  gcc-$(GCC_VERSION)/libstdc++-v3/src/c++98/locale-inst.cc \
  gcc-$(GCC_VERSION)/libstdc++-v3/src/c++98/locale.cc \
  gcc-$(GCC_VERSION)/libstdc++-v3/src/c++98/locale_facets.cc \
  gcc-$(GCC_VERSION)/libstdc++-v3/src/c++98/locale_init.cc \
  gcc-$(GCC_VERSION)/libstdc++-v3/src/c++98/localename.cc \
  gcc-$(GCC_VERSION)/libstdc++-v3/src/c++98/math_stubs_float.cc \
  gcc-$(GCC_VERSION)/libstdc++-v3/src/c++98/math_stubs_long_double.cc \
  gcc-$(GCC_VERSION)/libstdc++-v3/src/c++98/messages_members.cc \
  gcc-$(GCC_VERSION)/libstdc++-v3/src/c++98/misc-inst.cc \
  gcc-$(GCC_VERSION)/libstdc++-v3/src/c++98/monetary_members.cc \
  gcc-$(GCC_VERSION)/libstdc++-v3/src/c++98/mt_allocator.cc \
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
  gcc-$(GCC_VERSION)/libstdc++-v3/src/c++98/wlocale-inst.cc

HEADERS = \
  $(INCDIR)/backward/auto_ptr.h \
  $(INCDIR)/backward/backward_warning.h \
  $(INCDIR)/backward/binders.h \
  $(INCDIR)/backward/strstream \
  $(INCDIR)/bits/algorithmfwd.h \
  $(INCDIR)/bits/alloc_traits.h \
  $(INCDIR)/bits/allocator.h \
  $(INCDIR)/bits/atomic_base.h \
  $(INCDIR)/bits/atomic_lockfree_defines.h \
  $(INCDIR)/bits/atomic_word.h \
  $(INCDIR)/bits/basic_file.h \
  $(INCDIR)/bits/basic_ios.h \
  $(INCDIR)/bits/basic_ios.tcc \
  $(INCDIR)/bits/basic_string.h \
  $(INCDIR)/bits/basic_string.tcc \
  $(INCDIR)/bits/boost_concept_check.h \
  $(INCDIR)/bits/c++0x_warning.h \
  $(INCDIR)/bits/c++allocator.h \
  $(INCDIR)/bits/c++config.h \
  $(INCDIR)/bits/c++io.h \
  $(INCDIR)/bits/c++locale.h \
  $(INCDIR)/bits/c++locale_internal.h \
  $(INCDIR)/bits/char_traits.h \
  $(INCDIR)/bits/codecvt.h \
  $(INCDIR)/bits/compatibility.h \
  $(INCDIR)/bits/concept_check.h \
  $(INCDIR)/bits/cpp_type_traits.h \
  $(INCDIR)/bits/cpu_defines.h \
  $(INCDIR)/bits/ctype_base.h \
  $(INCDIR)/bits/ctype_inline.h \
  $(INCDIR)/bits/cxxabi_forced.h \
  $(INCDIR)/bits/cxxabi_tweaks.h \
  $(INCDIR)/bits/deque.tcc \
  $(INCDIR)/bits/error_constants.h \
  $(INCDIR)/bits/exception_defines.h \
  $(INCDIR)/bits/exception_ptr.h \
  $(INCDIR)/bits/extc++.h \
  $(INCDIR)/bits/forward_list.h \
  $(INCDIR)/bits/forward_list.tcc \
  $(INCDIR)/bits/fstream.tcc \
  $(INCDIR)/bits/functexcept.h \
  $(INCDIR)/bits/functional_hash.h \
  $(INCDIR)/bits/gslice.h \
  $(INCDIR)/bits/gslice_array.h \
  $(INCDIR)/bits/gthr-default.h \
  $(INCDIR)/bits/gthr.h \
  $(INCDIR)/bits/hash_bytes.h \
  $(INCDIR)/bits/hashtable.h \
  $(INCDIR)/bits/hashtable_policy.h \
  $(INCDIR)/bits/indirect_array.h \
  $(INCDIR)/bits/ios_base.h \
  $(INCDIR)/bits/istream.tcc \
  $(INCDIR)/bits/list.tcc \
  $(INCDIR)/bits/locale_classes.h \
  $(INCDIR)/bits/locale_classes.tcc \
  $(INCDIR)/bits/locale_facets.h \
  $(INCDIR)/bits/locale_facets.tcc \
  $(INCDIR)/bits/locale_facets_nonio.h \
  $(INCDIR)/bits/locale_facets_nonio.tcc \
  $(INCDIR)/bits/localefwd.h \
  $(INCDIR)/bits/mask_array.h \
  $(INCDIR)/bits/memoryfwd.h \
  $(INCDIR)/bits/messages_members.cc \
  $(INCDIR)/bits/messages_members.h \
  $(INCDIR)/bits/move.h \
  $(INCDIR)/bits/nested_exception.h \
  $(INCDIR)/bits/opt_random.h \
  $(INCDIR)/bits/os_defines.h \
  $(INCDIR)/bits/ostream.tcc \
  $(INCDIR)/bits/ostream_insert.h \
  $(INCDIR)/bits/postypes.h \
  $(INCDIR)/bits/ptr_traits.h \
  $(INCDIR)/bits/random.h \
  $(INCDIR)/bits/random.tcc \
  $(INCDIR)/bits/range_access.h \
  $(INCDIR)/bits/regex.h \
  $(INCDIR)/bits/regex_compiler.h \
  $(INCDIR)/bits/regex_constants.h \
  $(INCDIR)/bits/regex_cursor.h \
  $(INCDIR)/bits/regex_error.h \
  $(INCDIR)/bits/regex_grep_matcher.h \
  $(INCDIR)/bits/regex_grep_matcher.tcc \
  $(INCDIR)/bits/regex_nfa.h \
  $(INCDIR)/bits/regex_nfa.tcc \
  $(INCDIR)/bits/shared_ptr.h \
  $(INCDIR)/bits/shared_ptr_base.h \
  $(INCDIR)/bits/slice_array.h \
  $(INCDIR)/bits/sstream.tcc \
  $(INCDIR)/bits/stdc++.h \
  $(INCDIR)/bits/stdtr1c++.h \
  $(INCDIR)/bits/stl_algo.h \
  $(INCDIR)/bits/stl_algobase.h \
  $(INCDIR)/bits/stl_bvector.h \
  $(INCDIR)/bits/stl_construct.h \
  $(INCDIR)/bits/stl_deque.h \
  $(INCDIR)/bits/stl_function.h \
  $(INCDIR)/bits/stl_heap.h \
  $(INCDIR)/bits/stl_iterator.h \
  $(INCDIR)/bits/stl_iterator_base_funcs.h \
  $(INCDIR)/bits/stl_iterator_base_types.h \
  $(INCDIR)/bits/stl_list.h \
  $(INCDIR)/bits/stl_map.h \
  $(INCDIR)/bits/stl_multimap.h \
  $(INCDIR)/bits/stl_multiset.h \
  $(INCDIR)/bits/stl_numeric.h \
  $(INCDIR)/bits/stl_pair.h \
  $(INCDIR)/bits/stl_queue.h \
  $(INCDIR)/bits/stl_raw_storage_iter.h \
  $(INCDIR)/bits/stl_relops.h \
  $(INCDIR)/bits/stl_set.h \
  $(INCDIR)/bits/stl_stack.h \
  $(INCDIR)/bits/stl_tempbuf.h \
  $(INCDIR)/bits/stl_tree.h \
  $(INCDIR)/bits/stl_uninitialized.h \
  $(INCDIR)/bits/stl_vector.h \
  $(INCDIR)/bits/stream_iterator.h \
  $(INCDIR)/bits/streambuf.tcc \
  $(INCDIR)/bits/streambuf_iterator.h \
  $(INCDIR)/bits/stringfwd.h \
  $(INCDIR)/bits/time_members.h \
  $(INCDIR)/bits/unique_ptr.h \
  $(INCDIR)/bits/unordered_map.h \
  $(INCDIR)/bits/unordered_set.h \
  $(INCDIR)/bits/uses_allocator.h \
  $(INCDIR)/bits/valarray_after.h \
  $(INCDIR)/bits/valarray_array.h \
  $(INCDIR)/bits/valarray_array.tcc \
  $(INCDIR)/bits/valarray_before.h \
  $(INCDIR)/bits/vector.tcc \
  $(INCDIR)/debug/array \
  $(INCDIR)/debug/bitset \
  $(INCDIR)/debug/debug.h \
  $(INCDIR)/debug/deque \
  $(INCDIR)/debug/formatter.h \
  $(INCDIR)/debug/forward_list \
  $(INCDIR)/debug/functions.h \
  $(INCDIR)/debug/list \
  $(INCDIR)/debug/macros.h \
  $(INCDIR)/debug/map \
  $(INCDIR)/debug/map.h \
  $(INCDIR)/debug/multimap.h \
  $(INCDIR)/debug/multiset.h \
  $(INCDIR)/debug/safe_base.h \
  $(INCDIR)/debug/safe_iterator.h \
  $(INCDIR)/debug/safe_iterator.tcc \
  $(INCDIR)/debug/safe_local_iterator.h \
  $(INCDIR)/debug/safe_local_iterator.tcc \
  $(INCDIR)/debug/safe_sequence.h \
  $(INCDIR)/debug/safe_sequence.tcc \
  $(INCDIR)/debug/safe_unordered_base.h \
  $(INCDIR)/debug/safe_unordered_container.h \
  $(INCDIR)/debug/safe_unordered_container.tcc \
  $(INCDIR)/debug/set \
  $(INCDIR)/debug/set.h \
  $(INCDIR)/debug/string \
  $(INCDIR)/debug/unordered_map \
  $(INCDIR)/debug/unordered_set \
  $(INCDIR)/debug/vector \
  $(INCDIR)/ext/algorithm \
  $(INCDIR)/ext/alloc_traits.h \
  $(INCDIR)/ext/array_allocator.h \
  $(INCDIR)/ext/atomicity.h \
  $(INCDIR)/ext/bitmap_allocator.h \
  $(INCDIR)/ext/cast.h \
  $(INCDIR)/ext/cmath \
  $(INCDIR)/ext/codecvt_specializations.h \
  $(INCDIR)/ext/concurrence.h \
  $(INCDIR)/ext/debug_allocator.h \
  $(INCDIR)/ext/enc_filebuf.h \
  $(INCDIR)/ext/extptr_allocator.h \
  $(INCDIR)/ext/functional \
  $(INCDIR)/ext/hash_map \
  $(INCDIR)/ext/hash_set \
  $(INCDIR)/ext/iterator \
  $(INCDIR)/ext/malloc_allocator.h \
  $(INCDIR)/ext/memory \
  $(INCDIR)/ext/mt_allocator.h \
  $(INCDIR)/ext/new_allocator.h \
  $(INCDIR)/ext/numeric \
  $(INCDIR)/ext/numeric_traits.h \
  $(INCDIR)/ext/opt_random.h \
  $(INCDIR)/ext/pod_char_traits.h \
  $(INCDIR)/ext/pointer.h \
  $(INCDIR)/ext/pool_allocator.h \
  $(INCDIR)/ext/random \
  $(INCDIR)/ext/random.tcc \
  $(INCDIR)/ext/rb_tree \
  $(INCDIR)/ext/rc_string_base.h \
  $(INCDIR)/ext/rope \
  $(INCDIR)/ext/ropeimpl.h \
  $(INCDIR)/ext/slist \
  $(INCDIR)/ext/sso_string_base.h \
  $(INCDIR)/ext/stdio_filebuf.h \
  $(INCDIR)/ext/stdio_sync_filebuf.h \
  $(INCDIR)/ext/string_conversions.h \
  $(INCDIR)/ext/throw_allocator.h \
  $(INCDIR)/ext/type_traits.h \
  $(INCDIR)/ext/typelist.h \
  $(INCDIR)/ext/vstring.h \
  $(INCDIR)/ext/vstring.tcc \
  $(INCDIR)/ext/vstring_fwd.h \
  $(INCDIR)/ext/vstring_util.h \
  $(INCDIR)/tr1/array \
  $(INCDIR)/tr1/bessel_function.tcc \
  $(INCDIR)/tr1/beta_function.tcc \
  $(INCDIR)/tr1/ccomplex \
  $(INCDIR)/tr1/cctype \
  $(INCDIR)/tr1/cfenv \
  $(INCDIR)/tr1/cfloat \
  $(INCDIR)/tr1/cinttypes \
  $(INCDIR)/tr1/climits \
  $(INCDIR)/tr1/cmath \
  $(INCDIR)/tr1/complex \
  $(INCDIR)/tr1/complex.h \
  $(INCDIR)/tr1/cstdarg \
  $(INCDIR)/tr1/cstdbool \
  $(INCDIR)/tr1/cstdint \
  $(INCDIR)/tr1/cstdio \
  $(INCDIR)/tr1/cstdlib \
  $(INCDIR)/tr1/ctgmath \
  $(INCDIR)/tr1/ctime \
  $(INCDIR)/tr1/ctype.h \
  $(INCDIR)/tr1/cwchar \
  $(INCDIR)/tr1/cwctype \
  $(INCDIR)/tr1/ell_integral.tcc \
  $(INCDIR)/tr1/exp_integral.tcc \
  $(INCDIR)/tr1/fenv.h \
  $(INCDIR)/tr1/float.h \
  $(INCDIR)/tr1/functional \
  $(INCDIR)/tr1/functional_hash.h \
  $(INCDIR)/tr1/gamma.tcc \
  $(INCDIR)/tr1/hashtable.h \
  $(INCDIR)/tr1/hashtable_policy.h \
  $(INCDIR)/tr1/hypergeometric.tcc \
  $(INCDIR)/tr1/inttypes.h \
  $(INCDIR)/tr1/legendre_function.tcc \
  $(INCDIR)/tr1/limits.h \
  $(INCDIR)/tr1/math.h \
  $(INCDIR)/tr1/memory \
  $(INCDIR)/tr1/modified_bessel_func.tcc \
  $(INCDIR)/tr1/poly_hermite.tcc \
  $(INCDIR)/tr1/poly_laguerre.tcc \
  $(INCDIR)/tr1/random \
  $(INCDIR)/tr1/random.h \
  $(INCDIR)/tr1/random.tcc \
  $(INCDIR)/tr1/regex \
  $(INCDIR)/tr1/riemann_zeta.tcc \
  $(INCDIR)/tr1/shared_ptr.h \
  $(INCDIR)/tr1/special_function_util.h \
  $(INCDIR)/tr1/stdarg.h \
  $(INCDIR)/tr1/stdbool.h \
  $(INCDIR)/tr1/stdint.h \
  $(INCDIR)/tr1/stdio.h \
  $(INCDIR)/tr1/stdlib.h \
  $(INCDIR)/tr1/tgmath.h \
  $(INCDIR)/tr1/tuple \
  $(INCDIR)/tr1/type_traits \
  $(INCDIR)/tr1/unordered_map \
  $(INCDIR)/tr1/unordered_map.h \
  $(INCDIR)/tr1/unordered_set \
  $(INCDIR)/tr1/unordered_set.h \
  $(INCDIR)/tr1/utility \
  $(INCDIR)/tr1/wchar.h \
  $(INCDIR)/tr1/wctype.h \
  $(INCDIR)/algorithm \
  $(INCDIR)/array \
  $(INCDIR)/atomic \
  $(INCDIR)/bitset \
  $(INCDIR)/cassert \
  $(INCDIR)/ccomplex \
  $(INCDIR)/cctype \
  $(INCDIR)/cerrno \
  $(INCDIR)/cfenv \
  $(INCDIR)/cfloat \
  $(INCDIR)/chrono \
  $(INCDIR)/cinttypes \
  $(INCDIR)/ciso646 \
  $(INCDIR)/climits \
  $(INCDIR)/clocale \
  $(INCDIR)/cmath \
  $(INCDIR)/complex \
  $(INCDIR)/complex.h \
  $(INCDIR)/condition_variable \
  $(INCDIR)/csetjmp \
  $(INCDIR)/csignal \
  $(INCDIR)/cstdalign \
  $(INCDIR)/cstdarg \
  $(INCDIR)/cstdbool \
  $(INCDIR)/cstddef \
  $(INCDIR)/cstdint \
  $(INCDIR)/cstdio \
  $(INCDIR)/cstdlib \
  $(INCDIR)/cstring \
  $(INCDIR)/ctgmath \
  $(INCDIR)/ctime \
  $(INCDIR)/cwchar \
  $(INCDIR)/cwctype \
  $(INCDIR)/cxxabi_forced.h \
  $(INCDIR)/deque \
  $(INCDIR)/exception \
  $(INCDIR)/fenv.h \
  $(INCDIR)/forward_list \
  $(INCDIR)/fstream \
  $(INCDIR)/functional \
  $(INCDIR)/future \
  $(INCDIR)/gstdint.h \
  $(INCDIR)/initializer_list \
  $(INCDIR)/iomanip \
  $(INCDIR)/ios \
  $(INCDIR)/iosfwd \
  $(INCDIR)/iostream \
  $(INCDIR)/istream \
  $(INCDIR)/iterator \
  $(INCDIR)/limits \
  $(INCDIR)/list \
  $(INCDIR)/locale \
  $(INCDIR)/map \
  $(INCDIR)/memory \
  $(INCDIR)/mutex \
  $(INCDIR)/new \
  $(INCDIR)/numeric \
  $(INCDIR)/ostream \
  $(INCDIR)/queue \
  $(INCDIR)/random \
  $(INCDIR)/ratio \
  $(INCDIR)/regex \
  $(INCDIR)/scoped_allocator \
  $(INCDIR)/set \
  $(INCDIR)/sstream \
  $(INCDIR)/stack \
  $(INCDIR)/stdexcept \
  $(INCDIR)/streambuf \
  $(INCDIR)/string \
  $(INCDIR)/system_error \
  $(INCDIR)/tgmath.h \
  $(INCDIR)/thread \
  $(INCDIR)/tuple \
  $(INCDIR)/type_traits \
  $(INCDIR)/typeindex \
  $(INCDIR)/typeinfo \
  $(INCDIR)/unordered_map \
  $(INCDIR)/unordered_set \
  $(INCDIR)/utility \
  $(INCDIR)/valarray \
  $(INCDIR)/vector

OBJECTS  = $(C_SOURCES:%.c=$(OBJDIR)/%.o)
OBJECTS += $(CC_SOURCES:%.cc=$(OBJDIR)/%.o)
DEPENDS += $(OBJECTS:%.o=%.d)

.PHONY: all
all : $(LIBDIR)/stdc++.a $(HEADERS)

$(LIBDIR)/stdc++.a: $(OBJECTS)
	@[ -d $(@D) ] || (mkdir -p $(@D))
	@echo linking: $@
	@$(AR) r $@ $(OBJECTS)
	@echo successfully built: $@
	@echo

$(INCDIR)/% : $(SRCDIR)/gcc-$(GCC_VERSION)/libstdc++-v3/libsupc++/%
	@[ -d $(@D) ] || (mkdir -p $(@D))
	@echo copying: $@ from $<
	cp $< $@

$(INCDIR)/% : $(SRCDIR)/gcc-$(GCC_VERSION)/libstdc++-v3/include/%
	@[ -d $(@D) ] || (mkdir -p $(@D))
	@echo copying: $@ from $<
	cp $< $@

include rules.mk

# include auto-generated dependencies
-include $(DEPENDS)

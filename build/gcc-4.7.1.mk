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

MAKEFILE_SOURCES += gcc-$(GCC_VERSION).mk

CFLAGS += \
  -I $(SRCDIR)/gcc-$(GCC_VERSION)/gcc \
  -I $(SRCDIR)/gcc-$(GCC_VERSION)/gcc/config/spu \
  -I $(SRCDIR)/gcc-$(GCC_VERSION)/gcc/ginclude \
  -I $(SRCDIR)/gcc-$(GCC_VERSION)/gcc/include \
  -I $(SRCDIR)/gcc-$(GCC_VERSION)/gcc/include-fixed \
  -I $(SRCDIR)/gcc-$(GCC_VERSION)/libcpp/include \
  -I $(SRCDIR)/gcc-$(GCC_VERSION)/libgcc \
  -I $(SRCDIR)/gcc-$(GCC_VERSION)/libgfortran \
  -I $(SRCDIR)/gcc-$(GCC_VERSION)/libquadmath \
  -I $(SRCDIR)/gcc-$(GCC_VERSION)/include \
  -I $(INCDIR) \
  -include $(SRCDIR)/llamaos/__thread.h \
  -D HAVE_CONFIG_H \
  -D HAVE_STDLIB_H \
  -D HAVE_STRING_H \
  -D HAVE_ALLOCA_H \
  -DFIRST_PSEUDO_REGISTER=53 \
  -DIN_GLIBCPP_V3

CPPFLAGS += \
  -I $(SRCDIR)/gcc-$(GCC_VERSION)/libstdc++-v3/include/backward \
  -I $(SRCDIR)/gcc-$(GCC_VERSION)/libstdc++-v3/include/c_global \
  -I $(SRCDIR)/gcc-$(GCC_VERSION)/libstdc++-v3/include/std \
  -I $(SRCDIR)/gcc-$(GCC_VERSION)/libstdc++-v3/include \
  -I $(SRCDIR)/gcc-$(GCC_VERSION)/libstdc++-v3/libsupc++ \
  -I $(SRCDIR)/gcc-$(GCC_VERSION)/gcc/include-fixed \
  -I $(SRCDIR)/gcc-$(GCC_VERSION)/gcc/ginclude \
  -I $(SRCDIR)/gcc-$(GCC_VERSION)/include \
  -I $(INCDIR) \
  -include $(SRCDIR)/llamaos/__thread.h

HEADERS = \
  $(INCDIR)/backward/auto_ptr.h \
  $(INCDIR)/backward/binders.h \
  $(INCDIR)/bits/algorithmfwd.h \
  $(INCDIR)/bits/alloc_traits.h \
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
  $(INCDIR)/bits/codecvt.h \
  $(INCDIR)/bits/concept_check.h \
  $(INCDIR)/bits/cpp_type_traits.h \
  $(INCDIR)/bits/cpu_defines.h \
  $(INCDIR)/bits/ctype_base.h \
  $(INCDIR)/bits/ctype_inline.h \
  $(INCDIR)/bits/cxxabi_forced.h \
  $(INCDIR)/bits/cxxabi_tweaks.h \
  $(INCDIR)/bits/deque.tcc \
  $(INCDIR)/bits/exception_defines.h \
  $(INCDIR)/bits/exception_ptr.h \
  $(INCDIR)/bits/functexcept.h \
  $(INCDIR)/bits/functional_hash.h \
  $(INCDIR)/bits/gthr.h \
  $(INCDIR)/bits/gthr-default.h \
  $(INCDIR)/bits/hash_bytes.h \
  $(INCDIR)/bits/hashtable.h \
  $(INCDIR)/bits/hashtable_policy.h \
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
  $(INCDIR)/bits/messages_members.h \
  $(INCDIR)/bits/move.h \
  $(INCDIR)/bits/nested_exception.h \
  $(INCDIR)/bits/os_defines.h \
  $(INCDIR)/bits/ostream.tcc \
  $(INCDIR)/bits/ostream_insert.h \
  $(INCDIR)/bits/postypes.h \
  $(INCDIR)/bits/ptr_traits.h \
  $(INCDIR)/bits/random.h \
  $(INCDIR)/bits/random.tcc \
  $(INCDIR)/bits/range_access.h \
  $(INCDIR)/bits/shared_ptr.h \
  $(INCDIR)/bits/shared_ptr_base.h \
  $(INCDIR)/bits/sstream.tcc \
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
  $(INCDIR)/bits/vector.tcc \
  $(INCDIR)/debug/debug.h \
  $(INCDIR)/ext/alloc_traits.h \
  $(INCDIR)/ext/atomicity.h \
  $(INCDIR)/ext/concurrence.h \
  $(INCDIR)/ext/new_allocator.h \
  $(INCDIR)/ext/numeric_traits.h \
  $(INCDIR)/ext/string_conversions.h \
  $(INCDIR)/ext/type_traits.h \
  $(INCDIR)/tr1/tuple \
  $(INCDIR)/algorithm \
  $(INCDIR)/array \
  $(INCDIR)/bitset \
  $(INCDIR)/cassert \
  $(INCDIR)/cctype \
  $(INCDIR)/cerrno \
  $(INCDIR)/climits \
  $(INCDIR)/clocale \
  $(INCDIR)/cmath \
  $(INCDIR)/complex \
  $(INCDIR)/cstdarg \
  $(INCDIR)/cstdint \
  $(INCDIR)/cstdio \
  $(INCDIR)/cstdlib \
  $(INCDIR)/cstring \
  $(INCDIR)/ctime \
  $(INCDIR)/cwctype \
  $(INCDIR)/cwchar \
  $(INCDIR)/cxxabi.h \
  $(INCDIR)/deque \
  $(INCDIR)/exception \
  $(INCDIR)/float.h \
  $(INCDIR)/forward_list \
  $(INCDIR)/fstream \
  $(INCDIR)/functional \
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
  $(INCDIR)/stdarg.h \
  $(INCDIR)/stddef.h \
  $(INCDIR)/stdexcept \
  $(INCDIR)/streambuf \
  $(INCDIR)/string \
  $(INCDIR)/system_error \
  $(INCDIR)/tuple \
  $(INCDIR)/type_traits \
  $(INCDIR)/typeinfo \
  $(INCDIR)/unordered_map \
  $(INCDIR)/unordered_set \
  $(INCDIR)/utility \
  $(INCDIR)/valarray \
  $(INCDIR)/vector

#  gcc-$(GCC_VERSION)/libgcc/soft-fp/divdf3.c \
#  gcc-$(GCC_VERSION)/libgcc/soft-fp/divsf3.c \
#  gcc-$(GCC_VERSION)/libgcc/soft-fp/muldf3.c \
#  gcc-$(GCC_VERSION)/libgcc/soft-fp/mulsf3.c \

#  gcc-$(GCC_VERSION)/gcc/config/spu/spu.c \

C_SOURCES = \
  gcc-$(GCC_VERSION)/libgcc/config/spu/divmodti4.c \
  gcc-$(GCC_VERSION)/libgcc/soft-fp/adddf3.c \
  gcc-$(GCC_VERSION)/libgcc/soft-fp/addsf3.c \
  gcc-$(GCC_VERSION)/libgcc/soft-fp/addtf3.c \
  gcc-$(GCC_VERSION)/libgcc/soft-fp/divtf3.c \
  gcc-$(GCC_VERSION)/libgcc/soft-fp/eqdf2.c \
  gcc-$(GCC_VERSION)/libgcc/soft-fp/eqsf2.c \
  gcc-$(GCC_VERSION)/libgcc/soft-fp/eqtf2.c \
  gcc-$(GCC_VERSION)/libgcc/soft-fp/extenddftf2.c \
  gcc-$(GCC_VERSION)/libgcc/soft-fp/extendsfdf2.c \
  gcc-$(GCC_VERSION)/libgcc/soft-fp/extendsftf2.c \
  gcc-$(GCC_VERSION)/libgcc/soft-fp/extendxftf2.c \
  gcc-$(GCC_VERSION)/libgcc/soft-fp/fixdfdi.c \
  gcc-$(GCC_VERSION)/libgcc/soft-fp/fixdfsi.c \
  gcc-$(GCC_VERSION)/libgcc/soft-fp/fixdfti.c \
  gcc-$(GCC_VERSION)/libgcc/soft-fp/fixsfdi.c \
  gcc-$(GCC_VERSION)/libgcc/soft-fp/fixsfsi.c \
  gcc-$(GCC_VERSION)/libgcc/soft-fp/fixsfti.c \
  gcc-$(GCC_VERSION)/libgcc/soft-fp/fixtfdi.c \
  gcc-$(GCC_VERSION)/libgcc/soft-fp/fixtfsi.c \
  gcc-$(GCC_VERSION)/libgcc/soft-fp/fixtfti.c \
  gcc-$(GCC_VERSION)/libgcc/soft-fp/fixunsdfdi.c \
  gcc-$(GCC_VERSION)/libgcc/soft-fp/fixunsdfsi.c \
  gcc-$(GCC_VERSION)/libgcc/soft-fp/fixunsdfti.c \
  gcc-$(GCC_VERSION)/libgcc/soft-fp/fixunssfdi.c \
  gcc-$(GCC_VERSION)/libgcc/soft-fp/fixunssfsi.c \
  gcc-$(GCC_VERSION)/libgcc/soft-fp/fixunssfti.c \
  gcc-$(GCC_VERSION)/libgcc/soft-fp/fixunstfdi.c \
  gcc-$(GCC_VERSION)/libgcc/soft-fp/fixunstfsi.c \
  gcc-$(GCC_VERSION)/libgcc/soft-fp/fixunstfti.c \
  gcc-$(GCC_VERSION)/libgcc/soft-fp/floatdidf.c \
  gcc-$(GCC_VERSION)/libgcc/soft-fp/floatdisf.c \
  gcc-$(GCC_VERSION)/libgcc/soft-fp/floatditf.c \
  gcc-$(GCC_VERSION)/libgcc/soft-fp/floatsidf.c \
  gcc-$(GCC_VERSION)/libgcc/soft-fp/floatsisf.c \
  gcc-$(GCC_VERSION)/libgcc/soft-fp/floatsitf.c \
  gcc-$(GCC_VERSION)/libgcc/soft-fp/floattidf.c \
  gcc-$(GCC_VERSION)/libgcc/soft-fp/floattisf.c \
  gcc-$(GCC_VERSION)/libgcc/soft-fp/floattitf.c \
  gcc-$(GCC_VERSION)/libgcc/soft-fp/floatundidf.c \
  gcc-$(GCC_VERSION)/libgcc/soft-fp/floatundisf.c \
  gcc-$(GCC_VERSION)/libgcc/soft-fp/floatunditf.c \
  gcc-$(GCC_VERSION)/libgcc/soft-fp/floatunsidf.c \
  gcc-$(GCC_VERSION)/libgcc/soft-fp/floatunsisf.c \
  gcc-$(GCC_VERSION)/libgcc/soft-fp/floatunsitf.c \
  gcc-$(GCC_VERSION)/libgcc/soft-fp/floatuntidf.c \
  gcc-$(GCC_VERSION)/libgcc/soft-fp/floatuntisf.c \
  gcc-$(GCC_VERSION)/libgcc/soft-fp/floatuntitf.c \
  gcc-$(GCC_VERSION)/libgcc/soft-fp/gedf2.c \
  gcc-$(GCC_VERSION)/libgcc/soft-fp/gesf2.c \
  gcc-$(GCC_VERSION)/libgcc/soft-fp/getf2.c \
  gcc-$(GCC_VERSION)/libgcc/soft-fp/ledf2.c \
  gcc-$(GCC_VERSION)/libgcc/soft-fp/lesf2.c \
  gcc-$(GCC_VERSION)/libgcc/soft-fp/letf2.c \
  gcc-$(GCC_VERSION)/libgcc/soft-fp/multf3.c \
  gcc-$(GCC_VERSION)/libgcc/soft-fp/negdf2.c \
  gcc-$(GCC_VERSION)/libgcc/soft-fp/negsf2.c \
  gcc-$(GCC_VERSION)/libgcc/soft-fp/negtf2.c \
  gcc-$(GCC_VERSION)/libgcc/soft-fp/subdf3.c \
  gcc-$(GCC_VERSION)/libgcc/soft-fp/subsf3.c \
  gcc-$(GCC_VERSION)/libgcc/soft-fp/subtf3.c \
  gcc-$(GCC_VERSION)/libgcc/soft-fp/truncdfsf2.c \
  gcc-$(GCC_VERSION)/libgcc/soft-fp/trunctfdf2.c \
  gcc-$(GCC_VERSION)/libgcc/soft-fp/trunctfsf2.c \
  gcc-$(GCC_VERSION)/libgcc/soft-fp/trunctfxf2.c \
  gcc-$(GCC_VERSION)/libgcc/soft-fp/unorddf2.c \
  gcc-$(GCC_VERSION)/libgcc/soft-fp/unordsf2.c \
  gcc-$(GCC_VERSION)/libgcc/soft-fp/unordtf2.c \
  gcc-$(GCC_VERSION)/libgcc/unwind-dw2-fde.c \
  gcc-$(GCC_VERSION)/libgcc/unwind-dw2.c \
  gcc-$(GCC_VERSION)/libiberty/cp-demangle.c \
  gcc-$(GCC_VERSION)/libgfortran/intrinsics/random.c \
  gcc-$(GCC_VERSION)/libgfortran/intrinsics/signal.c \
  gcc-$(GCC_VERSION)/libgfortran/io/fbuf.c \
  gcc-$(GCC_VERSION)/libgfortran/io/format.c \
  gcc-$(GCC_VERSION)/libgfortran/io/list_read.c \
  gcc-$(GCC_VERSION)/libgfortran/io/lock.c \
  gcc-$(GCC_VERSION)/libgfortran/io/open.c \
  gcc-$(GCC_VERSION)/libgfortran/io/read.c \
  gcc-$(GCC_VERSION)/libgfortran/io/size_from_kind.c \
  gcc-$(GCC_VERSION)/libgfortran/io/transfer.c \
  gcc-$(GCC_VERSION)/libgfortran/io/unit.c \
  gcc-$(GCC_VERSION)/libgfortran/io/unix.c \
  gcc-$(GCC_VERSION)/libgfortran/io/write.c \
  gcc-$(GCC_VERSION)/libgfortran/runtime/backtrace.c \
  gcc-$(GCC_VERSION)/libgfortran/runtime/compile_options.c \
  gcc-$(GCC_VERSION)/libgfortran/runtime/environ.c \
  gcc-$(GCC_VERSION)/libgfortran/runtime/error.c \
  gcc-$(GCC_VERSION)/libgfortran/runtime/fpu.c \
  gcc-$(GCC_VERSION)/libgfortran/runtime/main.c \
  gcc-$(GCC_VERSION)/libgfortran/runtime/memory.c \
  gcc-$(GCC_VERSION)/libgfortran/runtime/string.c
#  gcc-$(GCC_VERSION)/libgfortran/fmain.c

CC_SOURCES = \
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
  gcc-$(GCC_VERSION)/libstdc++-v3/src/c++98/compatibility-debug_list-2.cc \
  gcc-$(GCC_VERSION)/libstdc++-v3/src/c++98/compatibility-debug_list.cc \
  gcc-$(GCC_VERSION)/libstdc++-v3/src/c++98/compatibility-ldbl.cc \
  gcc-$(GCC_VERSION)/libstdc++-v3/src/c++98/compatibility-list-2.cc \
  gcc-$(GCC_VERSION)/libstdc++-v3/src/c++98/compatibility-list.cc \
  gcc-$(GCC_VERSION)/libstdc++-v3/src/c++98/compatibility-parallel_list-2.cc \
  gcc-$(GCC_VERSION)/libstdc++-v3/src/c++98/compatibility-parallel_list.cc \
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
  gcc-$(GCC_VERSION)/libstdc++-v3/src/c++98/wlocale-inst.cc

OBJECTS  = $(C_SOURCES:%.c=$(OBJDIR)/%.o)
OBJECTS += $(CC_SOURCES:%.cc=$(OBJDIR)/%.o)

.PHONY: all
all : $(LIBDIR)/gcc.a $(HEADERS)

$(LIBDIR)/gcc.a : $(OBJECTS)
	@[ -d $(@D) ] || (mkdir -p $(@D))
	@echo linking: $@
	@$(AR) r $@ $(OBJECTS)
	@echo successfully built: $@
	@echo

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

#!/usr/bin/env python3
# copies GCC files used by llamaOS from source

import sys, os, shutil

# source folders
SRC_DIR = "/usr/src/gcc-4.7.0/"
BUILD_DIR = "/home/wmagato/builds/gcc-4.7.0/"
DEST_DIR = "/home/wmagato/builds/llamaOS/gcc/"

# create path if not exists
def create_path(path):
   if not os.path.isdir(path):
      print("creating " + path)
      os.makedirs(path)

print("\nllamaOS gcc-4.7.0 update script...\n")

# verify source folder
if not os.path.isdir(SRC_DIR):
   print("source folder not found: " + SRC_DIR)
   sys.exit(1)

# verify build folder
if not os.path.isdir(BUILD_DIR):
   print("build folder not found: " + BUILD_DIR)
   sys.exit(1)

#create destination folder
create_path(DEST_DIR)

SOURCES = [
 "include/dwarf2.h",
 "include/filenames.h",
 "libstdc++-v3/include/backward/auto_ptr.h",
 "libstdc++-v3/include/backward/backward_warning.h",
 "libstdc++-v3/include/backward/binders.h",
 "libstdc++-v3/include/backward/strstream",
 "libstdc++-v3/include/bits/algorithmfwd.h",
 "libstdc++-v3/include/bits/alloc_traits.h",
 "libstdc++-v3/include/bits/allocator.h",
 "libstdc++-v3/include/bits/atomic_base.h",
 "libstdc++-v3/include/bits/basic_ios.h",
 "libstdc++-v3/include/bits/basic_ios.tcc",
 "libstdc++-v3/include/bits/basic_string.h",
 "libstdc++-v3/include/bits/basic_string.tcc",
 "libstdc++-v3/include/bits/c++0x_warning.h",
 "libstdc++-v3/include/bits/char_traits.h",
 "libstdc++-v3/include/bits/codecvt.h",
 "libstdc++-v3/include/bits/concept_check.h",
 "libstdc++-v3/include/bits/cpp_type_traits.h",
 "libstdc++-v3/include/bits/deque.tcc",
 "libstdc++-v3/include/bits/fstream.tcc",
 "libstdc++-v3/include/bits/functexcept.h",
 "libstdc++-v3/include/bits/functional_hash.h",
 "libstdc++-v3/include/bits/gslice.h",
 "libstdc++-v3/include/bits/gslice_array.h",
 "libstdc++-v3/include/bits/indirect_array.h",
 "libstdc++-v3/include/bits/ios_base.h",
 "libstdc++-v3/include/bits/istream.tcc",
 "libstdc++-v3/include/bits/list.tcc",
 "libstdc++-v3/include/bits/locale_classes.h",
 "libstdc++-v3/include/bits/locale_classes.tcc",
 "libstdc++-v3/include/bits/locale_facets.h",
 "libstdc++-v3/include/bits/locale_facets.tcc",
 "libstdc++-v3/include/bits/locale_facets_nonio.h",
 "libstdc++-v3/include/bits/locale_facets_nonio.tcc",
 "libstdc++-v3/include/bits/localefwd.h",
 "libstdc++-v3/include/bits/mask_array.h",
 "libstdc++-v3/include/bits/move.h",
 "libstdc++-v3/include/bits/ostream.tcc",
 "libstdc++-v3/include/bits/ostream_insert.h",
 "libstdc++-v3/include/bits/postypes.h",
 "libstdc++-v3/include/bits/ptr_traits.h",
 "libstdc++-v3/include/bits/random.h",
 "libstdc++-v3/include/bits/random.tcc",
 "libstdc++-v3/include/bits/range_access.h",
 "libstdc++-v3/include/bits/regex.h",
 "libstdc++-v3/include/bits/regex_compiler.h",
 "libstdc++-v3/include/bits/regex_constants.h",
 "libstdc++-v3/include/bits/regex_cursor.h",
 "libstdc++-v3/include/bits/regex_error.h",
 "libstdc++-v3/include/bits/regex_grep_matcher.h",
 "libstdc++-v3/include/bits/regex_grep_matcher.tcc",
 "libstdc++-v3/include/bits/regex_nfa.h",
 "libstdc++-v3/include/bits/regex_nfa.tcc",
 "libstdc++-v3/include/bits/shared_ptr.h",
 "libstdc++-v3/include/bits/shared_ptr_base.h",
 "libstdc++-v3/include/bits/slice_array.h",
 "libstdc++-v3/include/bits/sstream.tcc",
 "libstdc++-v3/include/bits/stl_algo.h",
 "libstdc++-v3/include/bits/stl_algobase.h",
 "libstdc++-v3/include/bits/stl_bvector.h",
 "libstdc++-v3/include/bits/stl_construct.h",
 "libstdc++-v3/include/bits/stl_deque.h",
 "libstdc++-v3/include/bits/stl_function.h",
 "libstdc++-v3/include/bits/stl_heap.h",
 "libstdc++-v3/include/bits/stl_iterator.h",
 "libstdc++-v3/include/bits/stl_iterator_base_funcs.h",
 "libstdc++-v3/include/bits/stl_iterator_base_types.h",
 "libstdc++-v3/include/bits/stl_list.h",
 "libstdc++-v3/include/bits/stl_map.h",
 "libstdc++-v3/include/bits/stl_multimap.h",
 "libstdc++-v3/include/bits/stl_multiset.h",
 "libstdc++-v3/include/bits/stl_numeric.h",
 "libstdc++-v3/include/bits/stl_pair.h",
 "libstdc++-v3/include/bits/stl_queue.h",
 "libstdc++-v3/include/bits/stl_raw_storage_iter.h",
 "libstdc++-v3/include/bits/stl_relops.h",
 "libstdc++-v3/include/bits/stl_set.h",
 "libstdc++-v3/include/bits/stl_stack.h",
 "libstdc++-v3/include/bits/stl_tempbuf.h",
 "libstdc++-v3/include/bits/stl_tree.h",
 "libstdc++-v3/include/bits/stl_uninitialized.h",
 "libstdc++-v3/include/bits/stl_vector.h",
 "libstdc++-v3/include/bits/stream_iterator.h",
 "libstdc++-v3/include/bits/streambuf.tcc",
 "libstdc++-v3/include/bits/streambuf_iterator.h",
 "libstdc++-v3/include/bits/stringfwd.h",
 "libstdc++-v3/include/bits/unique_ptr.h",
 "libstdc++-v3/include/bits/uses_allocator.h",
 "libstdc++-v3/include/bits/valarray_after.h",
 "libstdc++-v3/include/bits/valarray_array.h",
 "libstdc++-v3/include/bits/valarray_array.tcc",
 "libstdc++-v3/include/bits/valarray_before.h",
 "libstdc++-v3/include/bits/vector.tcc",
 "libstdc++-v3/include/c_global/cassert",
 "libstdc++-v3/include/c_global/cctype",
 "libstdc++-v3/include/c_global/cerrno",
 "libstdc++-v3/include/c_global/climits",
 "libstdc++-v3/include/c_global/clocale",
 "libstdc++-v3/include/c_global/cmath",
 "libstdc++-v3/include/c_global/cstdarg",
 "libstdc++-v3/include/c_global/cstddef",
 "libstdc++-v3/include/c_global/cstdint",
 "libstdc++-v3/include/c_global/cstdio",
 "libstdc++-v3/include/c_global/cstdlib",
 "libstdc++-v3/include/c_global/cstring",
 "libstdc++-v3/include/c_global/ctime",
 "libstdc++-v3/include/c_global/cwchar",
 "libstdc++-v3/include/c_global/cwctype",
 "libstdc++-v3/include/debug/debug.h",
 "libstdc++-v3/include/debug/formatter.h",
 "libstdc++-v3/include/debug/functions.h",
 "libstdc++-v3/include/debug/macros.h",
 "libstdc++-v3/include/debug/safe_base.h",
 "libstdc++-v3/include/debug/safe_iterator.h",
 "libstdc++-v3/include/debug/safe_iterator.tcc",
 "libstdc++-v3/include/debug/safe_local_iterator.h",
 "libstdc++-v3/include/debug/safe_local_iterator.tcc",
 "libstdc++-v3/include/debug/safe_sequence.h",
 "libstdc++-v3/include/debug/safe_sequence.tcc",
 "libstdc++-v3/include/debug/safe_unordered_base.h",
 "libstdc++-v3/include/debug/safe_unordered_container.h",
 "libstdc++-v3/include/debug/safe_unordered_container.tcc",
 "libstdc++-v3/include/ext/alloc_traits.h",
 "libstdc++-v3/include/ext/atomicity.h",
 "libstdc++-v3/include/ext/bitmap_allocator.h",
 "libstdc++-v3/include/ext/concurrence.h",
 "libstdc++-v3/include/ext/new_allocator.h",
 "libstdc++-v3/include/ext/numeric_traits.h",
 "libstdc++-v3/include/ext/pool_allocator.h",
 "libstdc++-v3/include/ext/rope",
 "libstdc++-v3/include/ext/stdio_filebuf.h",
 "libstdc++-v3/include/ext/stdio_sync_filebuf.h",
 "libstdc++-v3/include/ext/string_conversions.h",
 "libstdc++-v3/include/ext/type_traits.h",
 "libstdc++-v3/include/std/algorithm",
 "libstdc++-v3/include/std/array",
 "libstdc++-v3/include/std/atomic",
 "libstdc++-v3/include/std/bitset",
 "libstdc++-v3/include/std/chrono",
 "libstdc++-v3/include/std/complex",
 "libstdc++-v3/include/std/condition_variable",
 "libstdc++-v3/include/std/deque",
 "libstdc++-v3/include/std/forward_list",
 "libstdc++-v3/include/std/fstream",
 "libstdc++-v3/include/std/functional",
 "libstdc++-v3/include/std/future",
 "libstdc++-v3/include/std/iomanip",
 "libstdc++-v3/include/std/ios",
 "libstdc++-v3/include/std/iosfwd",
 "libstdc++-v3/include/std/iostream",
 "libstdc++-v3/include/std/istream",
 "libstdc++-v3/include/std/iterator",
 "libstdc++-v3/include/std/limits",
 "libstdc++-v3/include/std/list",
 "libstdc++-v3/include/std/locale",
 "libstdc++-v3/include/std/map",
 "libstdc++-v3/include/std/memory",
 "libstdc++-v3/include/std/mutex",
 "libstdc++-v3/include/std/numeric",
 "libstdc++-v3/include/std/ostream",
 "libstdc++-v3/include/std/queue",
 "libstdc++-v3/include/std/random",
 "libstdc++-v3/include/std/ratio",
 "libstdc++-v3/include/std/regex",
 "libstdc++-v3/include/std/set",
 "libstdc++-v3/include/std/sstream",
 "libstdc++-v3/include/std/stack",
 "libstdc++-v3/include/std/stdexcept",
 "libstdc++-v3/include/std/streambuf",
 "libstdc++-v3/include/std/string",
 "libstdc++-v3/include/std/system_error",
 "libstdc++-v3/include/std/thread",
 "libstdc++-v3/include/std/tuple",
 "libstdc++-v3/include/std/type_traits",
 "libstdc++-v3/include/std/typeindex",
 "libstdc++-v3/include/std/unordered_map",
 "libstdc++-v3/include/std/unordered_set",
 "libstdc++-v3/include/std/utility",
 "libstdc++-v3/include/std/valarray",
 "libstdc++-v3/include/std/vector",
 "libstdc++-v3/include/tr1/tuple",
 "libstdc++-v3/libsupc++/array_type_info.cc",
 "libstdc++-v3/libsupc++/atomic_lockfree_defines.h",
 "libstdc++-v3/libsupc++/bad_alloc.cc",
 "libstdc++-v3/libsupc++/bad_cast.cc",
 "libstdc++-v3/libsupc++/bad_typeid.cc",
 "libstdc++-v3/libsupc++/class_type_info.cc",
 "libstdc++-v3/libsupc++/cxxabi.h",
 "libstdc++-v3/libsupc++/cxxabi_forced.h",
 "libstdc++-v3/libsupc++/del_op.cc",
 "libstdc++-v3/libsupc++/del_opnt.cc",
 "libstdc++-v3/libsupc++/del_opv.cc",
 "libstdc++-v3/libsupc++/del_opvnt.cc",
 "libstdc++-v3/libsupc++/dyncast.cc",
 "libstdc++-v3/libsupc++/eh_alloc.cc",
 "libstdc++-v3/libsupc++/eh_aux_runtime.cc",
 "libstdc++-v3/libsupc++/eh_call.cc",
 "libstdc++-v3/libsupc++/eh_catch.cc",
 "libstdc++-v3/libsupc++/eh_exception.cc",
 "libstdc++-v3/libsupc++/eh_globals.cc",
 "libstdc++-v3/libsupc++/eh_personality.cc",
 "libstdc++-v3/libsupc++/eh_ptr.cc",
 "libstdc++-v3/libsupc++/eh_term_handler.cc",
 "libstdc++-v3/libsupc++/eh_terminate.cc",
 "libstdc++-v3/libsupc++/eh_throw.cc",
 "libstdc++-v3/libsupc++/eh_type.cc",
 "libstdc++-v3/libsupc++/eh_unex_handler.cc",
 "libstdc++-v3/libsupc++/enum_type_info.cc",
 "libstdc++-v3/libsupc++/exception",
 "libstdc++-v3/libsupc++/exception_defines.h",
 "libstdc++-v3/libsupc++/exception_ptr.h",
 "libstdc++-v3/libsupc++/function_type_info.cc",
 "libstdc++-v3/libsupc++/fundamental_type_info.cc",
 "libstdc++-v3/libsupc++/guard.cc",
 "libstdc++-v3/libsupc++/guard_error.cc",
 "libstdc++-v3/libsupc++/hash_bytes.cc",
 "libstdc++-v3/libsupc++/hash_bytes.h",
 "libstdc++-v3/libsupc++/initializer_list",
 "libstdc++-v3/libsupc++/nested_exception.cc",
 "libstdc++-v3/libsupc++/nested_exception.h",
 "libstdc++-v3/libsupc++/new",
 "libstdc++-v3/libsupc++/new_handler.cc",
 "libstdc++-v3/libsupc++/new_op.cc",
 "libstdc++-v3/libsupc++/new_opnt.cc",
 "libstdc++-v3/libsupc++/new_opv.cc",
 "libstdc++-v3/libsupc++/new_opvnt.cc",
 "libstdc++-v3/libsupc++/pbase_type_info.cc",
 "libstdc++-v3/libsupc++/pmem_type_info.cc",
 "libstdc++-v3/libsupc++/pointer_type_info.cc",
 "libstdc++-v3/libsupc++/pure.cc",
 "libstdc++-v3/libsupc++/si_class_type_info.cc",
 "libstdc++-v3/libsupc++/tinfo.cc",
 "libstdc++-v3/libsupc++/tinfo.h",
 "libstdc++-v3/libsupc++/tinfo2.cc",
 "libstdc++-v3/libsupc++/typeinfo",
 "libstdc++-v3/libsupc++/unwind-cxx.h",
 "libstdc++-v3/libsupc++/vec.cc",
 "libstdc++-v3/libsupc++/vmi_class_type_info.cc",
 "libstdc++-v3/libsupc++/vterminate.cc",
 "libstdc++-v3/src/c++11/chrono.cc",
 "libstdc++-v3/src/c++11/debug.cc",
 "libstdc++-v3/src/c++11/fstream-inst.cc",
 "libstdc++-v3/src/c++11/functexcept.cc",
 "libstdc++-v3/src/c++11/functional.cc",
 "libstdc++-v3/src/c++11/future.cc",
 "libstdc++-v3/src/c++11/limits.cc",
 "libstdc++-v3/src/c++11/placeholders.cc",
 "libstdc++-v3/src/c++11/regex.cc",
 "libstdc++-v3/src/c++11/string-inst.cc",
 "libstdc++-v3/src/c++11/system_error.cc",
 "libstdc++-v3/src/c++11/wstring-inst.cc",
 "libstdc++-v3/src/c++98/allocator-inst.cc",
 "libstdc++-v3/src/c++98/bitmap_allocator.cc",
 "libstdc++-v3/src/c++98/codecvt.cc",
 "libstdc++-v3/src/c++98/compatibility.cc",
 "libstdc++-v3/src/c++98/complex_io.cc",
 "libstdc++-v3/src/c++98/concept-inst.cc",
 "libstdc++-v3/src/c++98/ctype.cc",
 "libstdc++-v3/src/c++98/ext-inst.cc",
 "libstdc++-v3/src/c++98/globals_io.cc",
 "libstdc++-v3/src/c++98/ios-inst.cc",
 "libstdc++-v3/src/c++98/ios.cc",
 "libstdc++-v3/src/c++98/ios_failure.cc",
 "libstdc++-v3/src/c++98/ios_init.cc",
 "libstdc++-v3/src/c++98/ios_locale.cc",
 "libstdc++-v3/src/c++98/iostream-inst.cc",
 "libstdc++-v3/src/c++98/istream-inst.cc",
 "libstdc++-v3/src/c++98/istream.cc",
 "libstdc++-v3/src/c++98/list.cc",
 "libstdc++-v3/src/c++98/locale-inst.cc",
 "libstdc++-v3/src/c++98/locale.cc",
 "libstdc++-v3/src/c++98/locale_facets.cc",
 "libstdc++-v3/src/c++98/locale_init.cc",
 "libstdc++-v3/src/c++98/localename.cc",
 "libstdc++-v3/src/c++98/misc-inst.cc",
 "libstdc++-v3/src/c++98/ostream-inst.cc",
 "libstdc++-v3/src/c++98/pool_allocator.cc",
 "libstdc++-v3/src/c++98/sstream-inst.cc",
 "libstdc++-v3/src/c++98/stdexcept.cc",
 "libstdc++-v3/src/c++98/streambuf-inst.cc",
 "libstdc++-v3/src/c++98/streambuf.cc",
 "libstdc++-v3/src/c++98/strstream.cc",
 "libstdc++-v3/src/c++98/tree.cc",
 "libstdc++-v3/src/c++98/valarray.cc",
 "libstdc++-v3/src/c++98/wlocale-inst.cc",
]

# copy the sources to the destination folder
for file in SOURCES:
   create_path(DEST_DIR + os.path.dirname(file))
   print("  copying " + file)
   shutil.copyfile(SRC_DIR + file, DEST_DIR + file)

SOURCES = [
 ("libstdc++-v3/include/bits/atomic_lockfree_defines.h", "libstdc++-v3/libsupc++/atomic_lockfree_defines.h"),
 ("libstdc++-v3/include/bits/atomic_word.h", "libstdc++-v3/config/cpu/generic/atomic_word.h"),
 ("libstdc++-v3/include/bits/basic_file.h", "libstdc++-v3/config/io/basic_file_stdio.h"),
 ("libstdc++-v3/include/bits/c++allocator.h", "libstdc++-v3/config/allocator/new_allocator_base.h"),
 ("libstdc++-v3/include/bits/c++io.h", "libstdc++-v3/config/io/c_io_stdio.h"),
 ("libstdc++-v3/include/bits/c++locale.h", "libstdc++-v3/config/locale/gnu/c_locale.h"),
 ("libstdc++-v3/include/bits/c++locale_internal.h", "libstdc++-v3/config/locale/gnu/c++locale_internal.h"),
 ("libstdc++-v3/include/bits/cpu_defines.h", "libstdc++-v3/config/cpu/generic/cpu_defines.h"),
 ("libstdc++-v3/include/bits/ctype_base.h", "libstdc++-v3/config/os/generic/ctype_base.h"),
 ("libstdc++-v3/include/bits/ctype_inline.h", "libstdc++-v3/config/os/generic/ctype_inline.h"),
 ("libstdc++-v3/include/bits/cxxabi_forced.h", "libstdc++-v3/libsupc++/cxxabi_forced.h"),
 ("libstdc++-v3/include/bits/cxxabi_tweaks.h", "libstdc++-v3/config/cpu/generic/cxxabi_tweaks.h"),
 ("libstdc++-v3/include/bits/error_constants.h", "libstdc++-v3/config/os/generic/error_constants.h"),
 ("libstdc++-v3/include/bits/exception_defines.h", "libstdc++-v3/libsupc++/exception_defines.h"),
 ("libstdc++-v3/include/bits/exception_ptr.h", "libstdc++-v3/libsupc++/exception_ptr.h"),
 ("libstdc++-v3/include/bits/hash_bytes.h", "libstdc++-v3/libsupc++/hash_bytes.h"),
 ("libstdc++-v3/include/bits/messages_members.h", "libstdc++-v3/config/locale/generic/messages_members.h"),
 ("libstdc++-v3/include/bits/nested_exception.h", "libstdc++-v3/libsupc++/nested_exception.h"),
 ("libstdc++-v3/include/bits/os_defines.h", "libstdc++-v3/config/os/generic/os_defines.h"),
 ("libstdc++-v3/include/bits/time_members.h", "libstdc++-v3/config/locale/generic/time_members.h"),
 ("libstdc++-v3/src/c++98/basic_file.cc", "libstdc++-v3/config/io/basic_file_stdio.cc"),
 ("libstdc++-v3/src/c++98/c++locale.cc", "libstdc++-v3/config/locale/generic/c_locale.cc"),
 ("libstdc++-v3/src/c++98/codecvt_members.cc", "libstdc++-v3/config/locale/generic/codecvt_members.cc"),
 ("libstdc++-v3/src/c++98/collate_members.cc", "libstdc++-v3/config/locale/generic/collate_members.cc"),
 ("libstdc++-v3/src/c++98/ctype_configure_char.cc", "libstdc++-v3/config/os/generic/ctype_configure_char.cc"),
 ("libstdc++-v3/src/c++98/ctype_members.cc", "libstdc++-v3/config/locale/generic/ctype_members.cc"),
 ("libstdc++-v3/src/c++98/messages_members.cc", "libstdc++-v3/config/locale/generic/messages_members.cc"),
 ("libstdc++-v3/src/c++98/monetary_members.cc", "libstdc++-v3/config/locale/generic/monetary_members.cc"),
 ("libstdc++-v3/src/c++98/numeric_members.cc", "libstdc++-v3/config/locale/generic/numeric_members.cc"),
 ("libstdc++-v3/src/c++98/time_members.cc", "libstdc++-v3/config/locale/generic/time_members.cc"),
 ("coretypes.h", "gcc/coretypes.h"),
 ("defaults.h", "gcc/defaults.h"),
 ("gthr-default.h", "libgcc/gthr-single.h"),
 ("gthr-single.h", "libgcc/gthr-single.h"),
 ("gthr.h", "libgcc/gthr.h"),
 ("tsystem.h", "gcc/tsystem.h"),
 ("unwind-dw2-fde.c", "libgcc/unwind-dw2-fde.c"),
 ("unwind-dw2-fde.h", "libgcc/unwind-dw2-fde.h"),
 ("unwind-dw2.c", "libgcc/unwind-dw2.c"),
 ("unwind-dw2.h", "libgcc/unwind-dw2.h"),
 ("unwind-pe.h", "libgcc/unwind-pe.h"),
 ("unwind.inc", "libgcc/unwind.inc"),
 ("md-unwind-support.h", "libgcc/config/i386/linux-unwind.h"),
]

# libstdc++-v3/include/bits/atomic_lockfree_defines.h \
# "coretypes.h",
# "defaults.h",
# "tsystem.h",

# copy the sources to the destination folder
for (dest, src) in SOURCES:
   create_path(DEST_DIR + os.path.dirname(dest))
   print("  copying " + dest + " from " + src)
   shutil.copyfile(SRC_DIR + src, DEST_DIR + dest)

SOURCES = [
 ("include/float.h", "gcc/include/float.h"),
 ("include/limits.h", "gcc/include-fixed/limits.h"),
 ("include/stdarg.h", "gcc/include/stdarg.h"),
 ("include/stdbool.h", "gcc/include/stdbool.h"),
 ("include/stddef.h", "gcc/include/stddef.h"),
 ("include/unwind.h", "gcc/include/unwind.h"),
 ("libstdc++-v3/include/bits/c++config.h", "x86_64-unknown-linux-gnu/libstdc++-v3/include/x86_64-unknown-linux-gnu/bits/c++config.h"),
 ("libstdc++-v3/include/bits/gthr-default.h", "x86_64-unknown-linux-gnu/libstdc++-v3/include/x86_64-unknown-linux-gnu/bits/gthr-default.h"),
 ("libstdc++-v3/include/bits/gthr-single.h", "x86_64-unknown-linux-gnu/libstdc++-v3/include/x86_64-unknown-linux-gnu/bits/gthr-single.h"),
 ("libstdc++-v3/include/bits/gthr.h", "x86_64-unknown-linux-gnu/libstdc++-v3/include/x86_64-unknown-linux-gnu/bits/gthr.h"),
 ("auto-host.h", "gcc/auto-host.h"),
 ("tconfig.h", "gcc/tconfig.h"),
 ("tm.h", "gcc/tm.h"),
 ("libgcc_tm.h", "x86_64-unknown-linux-gnu/libgcc/libgcc_tm.h"),
]

# copy the sources to the destination folder
for (dest, src) in SOURCES:
   create_path(DEST_DIR + os.path.dirname(dest))
   print("  copying " + dest + " from " + src)
   shutil.copyfile(BUILD_DIR + src, DEST_DIR + dest)
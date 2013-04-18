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

# make parameters
MAKEFLAGS = --silent

# assembler/compiler/linker options
# notes from manual:

# ### C Language Options ###

# -std=
# Determine the language standard. See Language Standards Supported by GCC, for
# details of these standard versions. This option is currently only supported
# when compiling C or C++.
#
# `gnu11'
# `gnu1x'
# GNU dialect of ISO C11. Support is incomplete and experimental. The name
# `gnu1x' is deprecated. 
#
# `gnu++11'
# GNU dialect of -std=c++11. Support for C++11 is still experimental, and may
# change in incompatible ways in future releases.

# -ffreestanding
# Assert that compilation takes place in a freestanding environment. This
# implies -fno-builtin. A freestanding environment is one in which the standard
# library may not exist, and program startup may not necessarily be at main.
# The most obvious example is an OS kernel. This is equivalent to -fno-hosted.

# By default, GCC provides some extensions to the C language that on rare
# occasions conflict with the C standard. See Extensions to the C Language
# Family. Use of the -std options listed above will disable these extensions
# where they conflict with the C standard version selected. You may also select
# an extended version of the C language explicitly with -std=gnu90 (for C90 with
# GNU extensions), -std=gnu99 (for C99 with GNU extensions) or -std=gnu11 (for
# C11 with GNU extensions). The default, if no C language dialect options are
# given, is -std=gnu90; this will change to -std=gnu99 or -std=gnu11 in some
# future release when the C99 or C11 support is complete. Some features that are
# part of the C99 standard are accepted as extensions in C90 mode, and some
# features that are part of the C11 standard are accepted as extensions in C90
# and C99 modes.

# The ISO C standard defines (in clause 4) two classes of conforming
# implementation. A conforming hosted implementation supports the whole standard
# including all the library facilities; a conforming freestanding implementation
# is only required to provide certain library facilities: those in <float.h>,
# <limits.h>, <stdarg.h>, and <stddef.h>; since AMD1, also those in <iso646.h>;
# since C99, also those in <stdbool.h> and <stdint.h>; and since C11, also those
# in <stdalign.h> and <stdnoreturn.h>. In addition, complex types, added in C99,
# are not required for freestanding implementations. The standard also defines
# two environments for programs, a freestanding environment, required of all
# implementations and which may not have library facilities beyond those
# required of freestanding implementations, where the handling of program
# startup and termination are implementation-defined, and a hosted environment,
# which is not required, in which all the library facilities are provided and
# startup is through a function int main (void) or int main (int, char *[]).
# An OS kernel would be a freestanding environment; a program using the
# facilities of an operating system would normally be in a hosted
# implementation.

# GCC aims towards being usable as a conforming freestanding implementation, or
# as the compiler for a conforming hosted implementation. By default, it will
# act as the compiler for a hosted implementation, defining __STDC_HOSTED__ as 1
# and presuming that when the names of ISO C functions are used, they have the
# semantics defined in the standard. To make it act as a conforming freestanding
# implementation for a freestanding environment, use the option -ffreestanding;
# it will then define __STDC_HOSTED__ to 0 and not make assumptions about the
# meanings of function names from the standard library, with exceptions noted
# below. To build an OS kernel, you may well still need to make your own
# arrangements for linking and startup. See Options Controlling C Dialect.

# ### C++ Language Options ###

# -fuse-cxa-atexit
# Register destructors for objects with static storage duration with the
# __cxa_atexit function rather than the atexit function. This option is required
# for fully standards-compliant handling of static destructors, but will only
# work if your C library supports __cxa_atexit. 

# -nostdinc++
# Do not search for header files in the standard directories specific to C++,
# but do still search the other standard directories. (This option is used when
# building the C++ library.)

# -Weffc++ (C++ and Objective-C++ only)
# Warn about violations of the following style guidelines from Scott Meyers'
# Effective C++, Second Edition book:
#   Item 11: Define a copy constructor and an assignment operator for classes
#            with dynamically allocated memory.
#   Item 12: Prefer initialization to assignment in constructors.
#   Item 14: Make destructors virtual in base classes.
#   Item 15: Have operator= return a reference to *this.
#   Item 23: Don't try to return a reference when you must return an object.
# Also warn about violations of the following style guidelines from Scott
# Meyers' More Effective C++ book:
#   Item 6: Distinguish between prefix and postfix forms of increment and
#           decrement operators.
#   Item 7: Never overload &&, ||, or ,.
# When selecting this option, be aware that the standard library headers do not
# obey all of these guidelines; use `grep -v' to filter out those warnings. 

# -Wold-style-cast (C++ and Objective-C++ only)
# Warn if an old-style (C-style) cast to a non-void type is used within a C++
# program. The new-style casts (`dynamic_cast', `static_cast',
# `reinterpret_cast', and `const_cast') are less vulnerable to unintended
# effects and much easier to search for. 

# -Woverloaded-virtual (C++ and Objective-C++ only)
# Warn when a function declaration hides virtual functions from a base class.
# For example, in:
#           struct A {
#             virtual void f();
#           };
#           
#           struct B: public A {
#             void f(int);
#           };
#      
# the A class version of f is hidden in B, and code like:
# 
#           B* b;
#           b->f();
#      
# will fail to compile. 

# ### Warning Options ###

# -Werror
# Make all warnings into errors. 

# -Wall
# This enables all the warnings about constructions that some users consider
# questionable, and that are easy to avoid (or modify to prevent the warning),
# even in conjunction with macros. This also enables some language-specific
# warnings described in C++ Dialect Options and Objective-C and Objective-C++
# Dialect Options.

# -Wextra
# This enables some extra warning flags that are not enabled by -Wall. (This
# option used to be called -W. The older name is still supported, but the newer
# name is more descriptive.)

# -Wstack-usage=len
# Warn if the stack usage of a function might be larger than len bytes. The
# computation done to determine the stack usage is conservative. Any space
# allocated via alloca, variable-length arrays, or related constructs is
# included by the compiler when determining whether or not to issue a warning.

# -Wzero-as-null-pointer-constant (C++ and Objective-C++ only)
# Warn when a literal '0' is used as null pointer constant. This can be useful
# to facilitate the conversion to nullptr in C++11. 

# -Wstack-protector
# This option is only active when -fstack-protector is active. It warns about
# functions that will not be protected against stack smashing. 

# ### Debugging Options ###

# -g
# Produce debugging information in the operating system's native format (stabs,
# COFF, XCOFF, or DWARF 2). GDB can work with this debugging information.

# ### Optimization Options ###

# -O0
# Reduce compilation time and make debugging produce the expected results. This
# is the default. 
# -O1
# Optimize. Optimizing compilation takes somewhat more time, and a lot more
# memory for a large function. With -O, the compiler tries to reduce code size
# and execution time, without performing any optimizations that take a great
# deal of compilation time.

# -fstack-protector
# Emit extra code to check for buffer overflows, such as stack smashing attacks.
# This is done by adding a guard variable to functions with vulnerable objects.
# This includes functions that call alloca, and functions with buffers larger
# than 8 bytes. The guards are initialized when a function is entered and then
# checked when the function exits. If a guard check fails, an error message is
# printed and the program exits. 
# -fstack-protector-all
# Like -fstack-protector except that all functions are protected. 

# ### Preprocessor Options ###

# -nostdinc
# Do not search the standard system directories for header files. Only the
# directories you have specified with -I options (and the directory of the
# current file, if appropriate) are searched. 

# ### Linker Options ###

# -nostdlib
# Do not use the standard system startup files or libraries when linking. No
# startup files and only the libraries you specify will be passed to the linker,
# options specifying linkage of the system libraries, such as -static-libgcc or
# -shared-libgcc, will be ignored. The compiler may generate calls to memcmp,
# memset, memcpy and memmove. These entries are usually resolved by entries in
# libc. These entry points should be supplied through some other mechanism when
# this option is specified.

# ### Machine Dependent Options ###

# -m32
# -m64
# -mx32
# Generate code for a 32-bit or 64-bit environment. The -m32 option sets int,
# long and pointer to 32 bits and generates code that runs on any i386 system.
# The -m64 option sets int to 32 bits and long and pointer to 64 bits and
# generates code for AMD's x86-64 architecture. The -mx32 option sets int, long
# and pointer to 32 bits and generates code for AMD's x86-64 architecture. For
# darwin only the -m64 option turns off the -fno-pic and -mdynamic-no-pic
# options. 

# ### Code Generation Options ###

# -fexceptions
# Enable exception handling. Generates extra code needed to propagate
# exceptions. For some targets, this implies GCC will generate frame unwind
# information for all functions, which can produce significant data size
# overhead, although it does not affect execution. If you do not specify this
# option, GCC will enable it by default for languages like C++ that normally
# require exception handling, and disable it for languages like C that do not
# normally require it. However, you may need to enable this option when
# compiling C code that needs to interoperate properly with exception handlers
# written in C++. You may also wish to disable this option if you are compiling
# older C++ programs that don't use exception handling. 
# -fnon-call-exceptions
# Generate code that allows trapping instructions to throw exceptions. Note that
# this requires platform-specific runtime support that does not exist
# everywhere. Moreover, it only allows trapping instructions to throw
# exceptions, i.e. memory references or floating-point instructions. It does not
# allow exceptions to be thrown from arbitrary signal handlers such as SIGALRM.
# -funwind-tables
# Similar to -fexceptions, except that it will just generate any needed static
# data, but will not affect the generated code in any other way. You will
# normally not enable this option; instead, a language processor that needs this
# handling would enable it on your behalf. 
# -fasynchronous-unwind-tables
# Generate unwind table in dwarf2 format, if supported by target machine. The
# table is exact at each instruction boundary, so it can be used for stack
# unwinding from asynchronous events (such as debugger or garbage collector).

# -fno-common
# In C code, controls the placement of uninitialized global variables. Unix C
# compilers have traditionally permitted multiple definitions of such variables
# in different compilation units by placing the variables in a common block.
# This is the behavior specified by -fcommon, and is the default for GCC on most
# targets. On the other hand, this behavior is not required by ISO C, and on
# some targets may carry a speed or code size penalty on variable references.
# The -fno-common option specifies that the compiler should place uninitialized
# global variables in the data section of the object file, rather than
# generating them as common blocks. This has the effect that if the same
# variable is declared (without extern) in two different compilations, you will
# get a multiple-definition error when you link them. In this case, you must
# compile with -fcommon instead. Compiling with -fno-common is useful on targets
# for which it provides better performance, or if you wish to verify that the
# program will work on other systems that always treat uninitialized variable
# declarations this way. 

# -fstack-check
# Generate code to verify that you do not go beyond the boundary of the stack.
# You should specify this flag if you are running in an environment with
# multiple threads, but only rarely need to specify it in a single-threaded
# environment since stack overflow is automatically detected on nearly all
# systems if there is only one stack.
# Note that this switch does not actually cause checking to be done; the
# operating system or the language runtime must do that. The switch causes
# generation of code to ensure that they see the stack being extended.

# -fstack-limit-register=reg
# -fstack-limit-symbol=sym
# -fno-stack-limit
# Generate code to ensure that the stack does not grow beyond a certain value,
# either the value of a register or the address of a symbol. If the stack would
# grow beyond the value, a signal is raised. For most targets, the signal is
# raised before the stack overruns the boundary, so it is possible to catch the
# signal without taking special precautions.
# For instance, if the stack starts at absolute address `0x80000000' and grows
# downwards, you can use the flags -fstack-limit-symbol=__stack_limit and
# -Wl,--defsym,__stack_limit=0x7ffe0000 to enforce a stack limit of 128KB. Note
# that this may only work with the GNU linker. 

# -fsplit-stack
# Generate code to automatically split the stack before it overflows. The
# resulting program has a discontiguous stack which can only overflow if the
# program is unable to allocate any more memory. This is most useful when
# running threaded programs, as it is no longer necessary to calculate a good
# stack size to use for each thread. This is currently only implemented for the
# i386 and x86_64 back ends running GNU/Linux.

# COMMON FLAGS
XFLAGS = \
  -m64 -g -O1 \
  -Wall \
  -fno-common \
  -mno-red-zone \
  -fno-reorder-blocks \
  -fno-asynchronous-unwind-tables \
  -include $(SRCDIR)/llamaos/__thread.h

# -Wextra
# -ffreestanding

ASMFLAGS = $(XFLAGS)

CFLAGS = $(XFLAGS) \
  -nostdinc \
  -std=gnu99 -fgnu89-inline
#  -ffreestanding
#  -std=gnu99 -fgnu89-inline

CPPFLAGS = $(XFLAGS) \
  -std=gnu++11 \
  -nostdinc -nostdinc++ \
  -fuse-cxa-atexit
#  -Wold-style-cast -Wzero-as-null-pointer-constant \

F90FLAGS = $(XFLAGS) \
  -nostdinc

LDFLAGS = -nostdlib \
 -nostartfiles -nodefaultlibs 

-include custom-flags.mk

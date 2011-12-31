
# make parameters
MAKEFLAGS = --silent

# compiler tools
AR = ar
CC = gcc
LD = ld

# assembler/compiler/linker options
ASMFLAGS =
CFLAGS = -m64 -g -O1 -std=gnu99 -fgnu89-inline -nostdinc
CPPFLAGS = -m64 -g -O1 -std=gnu++0x -nostdinc -nostdinc++

LDFLAGS = -nostdlib

# system lib include list
SYSLIB_INCLUDES = \
  glibc/include \
  glibc/sysdeps/llamaos \
  glibc/sysdeps/llamaos/elf \
  glibc/sysdeps/x86_64 \
  glibc/sysdeps/x86_64/fpu \
  glibc/sysdeps/ieee754/ldbl-128 \
  glibc/sysdeps/ieee754 \
  glibc/sysdeps/generic \
  glibc/elf \
  glibc/iconv \
  glibc/libio \
  glibc/stdlib \
  glibc/string \
  glibc/wcsmbs \
  glibc \
  gcc/libstdc++-v3/include/c_global \
  gcc/libstdc++-v3/include/std \
  gcc/libstdc++-v3/include \
  gcc/libstdc++-v3/libsupc++ \
  gcc/include \
  gcc

CFLAGS += -include glibc/include/libc-symbols.h -include stdbool.h $(SYSLIB_INCLUDES:%=-I %)
CPPFLAGS += -include glibc/include/libc-symbols.h $(SYSLIB_INCLUDES:%=-I %)

# projects paths
BINDIR = bin
LIBDIR = lib
OBJDIR = obj

# list of makefiles that should cause a total rebuild
MAKEFILE_SOURCES = \
  common.mk \
  rules.mk

# possible project specific overrides of make variables
-include custom.mk

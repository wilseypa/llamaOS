
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

# projects paths
BINDIR = bin
LIBDIR = lib
OBJDIR = obj

# possible project specific overrides of make variables
-include custom.mk

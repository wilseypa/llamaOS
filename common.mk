
# make parameters
# MAKEFLAGS += -s

# compiler tools
AR = ar
CC = /opt/gcc-4.6.2/bin/gcc
LD = ld

# -fno-exceptions -fno-rtti
# assembler/compiler/linker options
ASMFLAGS =
CFLAGS = -m64 -g -O1 -std=gnu99 -fgnu89-inline -nostdinc
CPPFLAGS = -m64 -g -O1 -std=gnu++0x -nostdinc -nostdinc++
LDFLAGS = -nostdlib

# projects paths
BINDIR = bin
LIBDIR = lib
OBJDIR = obj

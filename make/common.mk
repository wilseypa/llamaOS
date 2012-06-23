
# make parameters
MAKEFLAGS = --silent

# compiler tools
CC = gcc
LD = gcc

# assembler/compiler/linker options
ASMFLAGS =
CFLAGS = -m64 -g -O1 -fno-common -std=gnu99 -fgnu89-inline -nostdinc
CPPFLAGS = -m64 -g -O1 -fno-common -std=gnu++0x -nostdinc -nostdinc++
LDFLAGS = -nostdlib

# projects paths
BINDIR = bin
LIBDIR = lib
OBJDIR = obj

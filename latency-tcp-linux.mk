
# not including the common file!

# make parameters
MAKEFLAGS = --silent

# compiler tools
CC = /opt/gcc-4.6.2/bin/g++
LD = /opt/gcc-4.6.2/bin/g++

# assembler/compiler/linker options
CPPFLAGS = -m64 -g -O1 -fno-common -std=gnu++0x
LDFLAGS = 

# projects paths
BINDIR = bin
LIBDIR = lib
OBJDIR = obj

# list of makefiles that should cause a total rebuild
MAKEFILE_SOURCES = \
  rules.mk

MAKEFILE_SOURCES += latency-tcp-linux.mk

INCLUDES = \
  src

CPPFLAGS += -Wall -Wextra -Weffc++ \
             $(INCLUDES:%=-I %)

VPATH = src

SOURCES = \
  llamaos/apps/latency/Experiment.cpp \
  llamaos/apps/latency/protocols/Experiment_tcp.cpp \
  llamaos/apps/latency/main.cpp

OBJECTS = $(SOURCES:%.cpp=$(OBJDIR)/%.o)
DEPENDS = $(OBJECTS:%.o=%.d)

# the entry object must be the first object listed here or the guest will crash!
$(BINDIR)/latency-tcp-linux: $(OBJECTS)
	@[ -d $(@D) ] || (mkdir -p $(@D))
	@echo linking: $@
	@$(LD) $(LDFLAGS) -o $@ $^
	@echo successfully built: $@
	@echo

include rules.mk

# include auto-generated dependencies
ifneq ($(MAKECMDGOALS),clean)
-include $(DEPENDS)
endif

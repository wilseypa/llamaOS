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
include common.mk

# make file list
MAKEFILE_SOURCES += llamaOS.mk

CPPFLAGS += \
  -I $(INCDIR) \
  -I $(SRCDIR) \
  -I $(SRCDIR)/llamaos/mpi \
  -include $(SRCDIR)/llamaos/__thread.h \
  -D__XEN_INTERFACE_VERSION__=0x00030205

CPP_SOURCES += \
  llamaos/mpi/mpi.cpp \
  llamaos/mpi/iGlobals.cpp \
  llamaos/mpi/iSizeof.cpp \
  llamaos/mpi/iGroup.cpp \
  llamaos/mpi/iRxBuffer.cpp \
  llamaos/mpi/llamaConn.cpp \
  llamaos/mpi/iComm.cpp \
  llamaos/mpi/iReceive.cpp \
  llamaos/mpi/iSend.cpp \
  llamaos/mpi/tools.cpp \
  llamaos/mpi/api/pt2pt/MPI_Recv.cpp \
  llamaos/mpi/api/pt2pt/MPI_Send.cpp \
  llamaos/mpi/api/comm/MPI_Comm_rank.cpp \
  llamaos/mpi/api/comm/MPI_Comm_size.cpp \
  llamaos/mpi/api/sys/MPI_Init.cpp \
  llamaos/mpi/api/sys/MPI_Finalize.cpp \
  llamaos/mpi/api/collective/MPI_Barrier.cpp \
  llamaos/mpi/api/collective/MPI_Bcast.cpp \
  llamaos/mpi/api/collective/MPI_Scatter.cpp \
  llamaos/mpi/api/collective/MPI_Gather.cpp \
  llamaos/mpi/api/collective/MPI_Allgather.cpp \
  llamaos/mpi/api/collective/MPI_Alltoall.cpp  

HEADERS = \
  $(INCDIR)/llamaos/mpi/mpi.h
 
# generate object list
OBJECTS = $(CPP_SOURCES:%.cpp=$(OBJDIR)/%.o)
DEPENDS = $(OBJECTS:%.o=%.d)

$(LIBDIR)/xen/llamaMPI.a: $(OBJECTS)
	@[ -d $(@D) ] || (mkdir -p $(@D))
	@echo linking: $@
	@$(AR) r $@ $^
	@echo successfully built: $@
	@echo

$(INCDIR)/% : $(SRCDIR)/%
	@[ -d $(@D) ] || (mkdir -p $(@D))
	@echo copying: $@ from $<
	cp $< $@

include rules.mk

# include auto-generated dependencies
-include $(DEPENDS)

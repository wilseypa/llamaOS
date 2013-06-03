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

# make file list
MAKEFILE_SOURCES += llamaMPI.mk

CPPFLAGS += \
  -I $(INCDIR) \
  -I $(SRCDIR) \
  -I $(SRCDIR)/llamaos/mpi \
  -include $(SRCDIR)/llamaos/__thread.h \
  -D__XEN_INTERFACE_VERSION__=0x00030205

VPATH = $(SRCDIR)

CPP_SOURCES += \
  llamaos/mpi/iGlobals.cpp \
  llamaos/mpi/iSizeof.cpp \
  llamaos/mpi/iGroup.cpp \
  llamaos/mpi/iRxBuffer.cpp \
  llamaos/mpi/llamaConn.cpp \
  llamaos/mpi/iComm.cpp \
  llamaos/mpi/iRequest.cpp \
  llamaos/mpi/iProbe.cpp \
  llamaos/mpi/iGetMessage.cpp \
  llamaos/mpi/iReceive.cpp \
  llamaos/mpi/iSend.cpp \
  llamaos/mpi/iProbeNB.cpp \
  llamaos/mpi/tools.cpp \
  llamaos/mpi/iReceiveNB.cpp \
  llamaos/mpi/op/iPerformOp.cpp \
  llamaos/mpi/api/pt2pt/MPI_Recv.cpp \
  llamaos/mpi/api/pt2pt/MPI_Send.cpp \
  llamaos/mpi/api/pt2pt/MPI_Sendrecv.cpp \
  llamaos/mpi/api/pt2pt/MPI_Probe.cpp \
  llamaos/mpi/api/pt2pt/MPI_Iprobe.cpp \
  llamaos/mpi/api/pt2pt/MPI_Get_count.cpp \
  llamaos/mpi/api/pt2pt/MPI_Isend.cpp \
  llamaos/mpi/api/pt2pt/MPI_Irecv.cpp \
  llamaos/mpi/api/pt2pt/MPI_Request_free.cpp \
  llamaos/mpi/api/pt2pt/MPI_Wait.cpp \
  llamaos/mpi/api/pt2pt/MPI_Waitall.cpp \
  llamaos/mpi/api/pt2pt/MPI_Waitany.cpp \
  llamaos/mpi/api/pt2pt/MPI_Waitsome.cpp \
  llamaos/mpi/api/pt2pt/MPI_Test.cpp \
  llamaos/mpi/api/pt2pt/MPI_Testall.cpp \
  llamaos/mpi/api/pt2pt/MPI_Testany.cpp \
  llamaos/mpi/api/pt2pt/MPI_Testsome.cpp \
  llamaos/mpi/api/group/MPI_Group_rank.cpp \
  llamaos/mpi/api/group/MPI_Group_size.cpp \
  llamaos/mpi/api/group/MPI_Group_incl.cpp \
  llamaos/mpi/api/group/MPI_Group_excl.cpp \
  llamaos/mpi/api/group/MPI_Group_union.cpp \
  llamaos/mpi/api/group/MPI_Group_intersection.cpp \
  llamaos/mpi/api/group/MPI_Group_difference.cpp \
  llamaos/mpi/api/group/MPI_Group_translate_ranks.cpp \
  llamaos/mpi/api/group/MPI_Group_compare.cpp \
  llamaos/mpi/api/group/MPI_Group_free.cpp \
  llamaos/mpi/api/comm/MPI_Comm_rank.cpp \
  llamaos/mpi/api/comm/MPI_Comm_size.cpp \
  llamaos/mpi/api/comm/MPI_Comm_compare.cpp \
  llamaos/mpi/api/comm/MPI_Comm_group.cpp \
  llamaos/mpi/api/comm/MPI_Comm_dup.cpp \
  llamaos/mpi/api/comm/MPI_Comm_create.cpp \
  llamaos/mpi/api/comm/MPI_Comm_split.cpp \
  llamaos/mpi/api/comm/MPI_Comm_free.cpp \
  llamaos/mpi/api/sys/MPI_Init.cpp \
  llamaos/mpi/api/sys/MPI_Finalize.cpp \
  llamaos/mpi/api/sys/MPI_Abort.cpp \
  llamaos/mpi/api/sys/MPI_Get_version.cpp \
  llamaos/mpi/api/collective/MPI_Barrier.cpp \
  llamaos/mpi/api/collective/MPI_Bcast.cpp \
  llamaos/mpi/api/collective/MPI_Scatter.cpp \
  llamaos/mpi/api/collective/MPI_Gather.cpp \
  llamaos/mpi/api/collective/MPI_Allgather.cpp \
  llamaos/mpi/api/collective/MPI_Alltoall.cpp \
  llamaos/mpi/api/collective/MPI_Alltoallv.cpp \
  llamaos/mpi/api/collective/MPI_Reduce.cpp \
  llamaos/mpi/api/collective/MPI_Allreduce.cpp \
  llamaos/mpi/api/time/MPI_Wtime.cpp \
  llamaos/mpi/api/time/MPI_Wtick.cpp \
  llamaos/mpi/api/error/MPI_Error_string.cpp \
  llamaos/mpi/api/type/MPI_Type_size.cpp 

HEADERS = \
  $(INCDIR)/llamaos/mpi/mpi.h
 
# generate object list
OBJECTS = $(CPP_SOURCES:%.cpp=$(OBJDIR)/%.o)
DEPENDS = $(OBJECTS:%.o=%.d)

.PHONY: all
all : $(LIBDIR)/llamaMPI.a headers

.PHONY: headers
headers : $(HEADERS)

$(LIBDIR)/llamaMPI.a: $(OBJECTS)
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

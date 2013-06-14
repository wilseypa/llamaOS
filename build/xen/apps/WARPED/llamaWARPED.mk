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

MAKEFILE_SOURCES += apps/WARPED/llamaWARPED.mk

# move to custom-vars.mk
# WARPED_PATH = /home/gideonjn/pdes/warped/src
# WARPED_RND_PATH = /home/gideonjn/pdes/warped/simulationmodels/rnd
# WARPED_UTILS_PATH = /home/gideonjn/pdes/utils/src
# PCCTS_PATH = /home/gideonjn/pccts/h

# WARPED_PATH = $(PDES_ROOT_PATH)/warped/src
# WARPED_RND_PATH = $(PDES_ROOT_PATH)/warped/simulationmodels/rnd
# WARPED_UTILS_PATH = $(PDES_ROOT_PATH)/utils/src
# PCCTS_PATH = $(PCCTS_ROOT_PATH)/h

CPPFLAGS += \
  -I $(INCDIR) \
  -I $(SRCDIR) \
  -I $(SRCDIR)/llamaos/mpi \
  -I ../src/apps \
  -I $(WARPED_PATH) \
  -I $(WARPED_RND_PATH) \
  -I $(WARPED_UTILS_PATH) \
  -I $(WARPED_PATH)/warped \
  -I $(PCCTS_PATH) \
  -I ../src/apps/WARPED \
  -D__XEN_INTERFACE_VERSION__=0x00030205 \
  -include $(SRCDIR)/llamaos/__thread.h \
  -Wno-reorder

VPATH = $(WARPED_PATH)

CPP_SOURCES = \
   warped/AdaptiveOutputManager.cpp \
   warped/AdaptiveStateManagerBase.cpp \
   warped/AggressiveOutputManager.cpp \
   warped/CentralizedEventSetSchedulingManager.cpp \
   warped/ChebyFossilCollManager.cpp \
   warped/CirculateInitializationMessage.cpp \
   warped/CommunicationManager.cpp \
   warped/CommunicationManagerFactory.cpp \
   warped/CommunicationManagerImplementationBase.cpp \
   warped/Configurable.cpp \
   warped/ConfigurationManagerFactory.cpp \
   warped/Configurer.cpp \
   warped/ConsoleIO.cpp \
   warped/ControlManager.cpp \
   warped/CostAdaptiveStateManager.cpp \
   warped/DecentralizedEventSetSchedulingManager.cpp \
   warped/DefaultCommunicationManager.cpp \
   warped/DefaultEvent.cpp \
   warped/DefaultPartitioner.cpp \
   warped/DefaultPhysicalCommunicationLayer.cpp \
   warped/DefaultSchedulingManager.cpp \
   warped/DefaultTimeWarpEventContainer.cpp \
   warped/DefaultTimeWarpEventContOneAntiMsg.cpp \
   warped/DefaultTimeWarpEventSet.cpp \
   warped/DeserializerManager.cpp \
   warped/DistributedDVFSManager.cpp \
   warped/DVFSManagerFactory.cpp \
   warped/DVFSManagerImplementationBase.cpp \
   warped/eclmplConfigFileTable.cpp \
   warped/eclmplConnectionInterface.cpp \
   warped/eclmplConnectionInterfaceImplementationBase.cpp \
   warped/eclmplPhysicalCommunicationLayer.cpp \
   warped/eclmplTimer.cpp \
   warped/Event.cpp \
   warped/EventMessage.cpp \
   warped/EventMessageBase.cpp \
   warped/EventSetFactory.cpp \
   warped/FactoryImplementationBase.cpp \
   warped/FactoryManager.cpp \
   warped/FactorySymbolTable.cpp \
   warped/FileManager.cpp \
   warped/FileQueue.cpp \
   warped/FlatState.cpp \
   warped/GVTManagerFactory.cpp \
   warped/GVTManagerImplementationBase.cpp \
   warped/GVTUpdateMessage.cpp \
   warped/InFileQueue.cpp \
   warped/InitializationMessage.cpp \
   warped/IntVTime.cpp \
   warped/KernelMessage.cpp \
   warped/LazyOutputManager.cpp \
   warped/MatternGVTManager.cpp \
   warped/MatternGVTMessage.cpp \
   warped/MessageManager.cpp \
   warped/MPIMessage.cpp \
   warped/MPIPhysicalCommunicationLayer.cpp \
   warped/MsgAggregatingCommunicationManager.cpp \
   warped/NegativeEvent.cpp \
   warped/NegativeEventMessage.cpp \
   warped/NetworkMessage.cpp \
   warped/ObjectStub.cpp \
   warped/OptFossilCollManager.cpp \
   warped/OptFossilCollManagerFactory.cpp \
   warped/OutputEvents.cpp \
   warped/OutputManagerFactory.cpp \
   warped/OutputManagerImplementationBase.cpp \
   warped/Partitioner.cpp \
   warped/PartitionInfo.cpp \
   warped/PeriodicStateManager.cpp \
   warped/RestoreCkptMessage.cpp \
   warped/RoundRobinPartitioner.cpp \
   warped/SchedulingManagerFactory.cpp \
   warped/SequentialConfigurationManager.cpp \
   warped/SequentialFileManager.cpp \
   warped/SequentialSimulationManager.cpp \
   warped/SequentialSimulationStream.cpp \
   warped/Serializable.cpp \
   warped/SerializedInstance.cpp \
   warped/SharedDVFSManager.cpp \
   warped/Simulation.cpp \
   warped/SimulationConfiguration.cpp \
   warped/SimulationManager.cpp \
   warped/SimulationManagerImplementationBase.cpp \
   warped/SimulationObject.cpp \
   warped/SimulationObjectProxy.cpp \
   warped/SimulationStream.cpp \
   warped/SingleLinkedList.cpp \
   warped/SinkObject.cpp \
   warped/SourceObject.cpp \
   warped/Spinner.cpp \
   warped/SplayTree.cpp \
   warped/StartMessage.cpp \
   warped/State.cpp \
   warped/StateManagerFactory.cpp \
   warped/StateManagerImplementationBase.cpp \
   warped/StopWatch.cpp \
   warped/StragglerEvent.cpp \
   warped/TerminateToken.cpp \
   warped/TimeWarpCentralizedEventSetFactory.cpp \
   warped/TimeWarpConfigurationManager.cpp \
   warped/TimeWarpDecentralizedEventSetFactory.cpp \
   warped/TimeWarpEventSet.cpp \
   warped/TimeWarpEventSetFactory.cpp \
   warped/TimeWarpMultiSet.cpp \
   warped/TimeWarpMultiSetOneAntiMsg.cpp \
   warped/TimeWarpMultiSetSchedulingManager.cpp \
   warped/TimeWarpSenderQueue.cpp \
   warped/TimeWarpSimulationManager.cpp \
   warped/TimeWarpSimulationManagerFactory.cpp \
   warped/TimeWarpSimulationObjectQueue.cpp \
   warped/TimeWarpSimulationObjectQueueFactory.cpp \
   warped/TimeWarpSimulationStream.cpp \
   warped/TokenPassingTerminationManager.cpp \
   warped/Transceiver.cpp \
   warped/UsefulWorkMessage.cpp \
   warped/VTime.cpp \
   warped/warped.cpp \
   warped/WarpedMain.cpp \
   $(PCCTS_PATH)/AParser.cpp \
   $(PCCTS_PATH)/ASTBase.cpp \
   $(PCCTS_PATH)/ATokenBuffer.cpp \
   $(PCCTS_PATH)/BufFileInput.cpp \
   $(PCCTS_PATH)/DLexerBase.cpp \
   $(PCCTS_PATH)/PCCTSAST.cpp \
   $(PCCTS_PATH)/slist.cpp \
   $(WARPED_UTILS_PATH)/utils/ArgumentParser.cpp \
   $(WARPED_UTILS_PATH)/utils/ConfigurationChoice.cpp \
   $(WARPED_UTILS_PATH)/utils/ConfigurationScope.cpp \
   $(WARPED_UTILS_PATH)/utils/ConfigurationValue.cpp \
   $(WARPED_UTILS_PATH)/utils/Debug.cpp \
   $(WARPED_UTILS_PATH)/utils/ConfigurationParserHandle.cpp \
   $(WARPED_UTILS_PATH)/utils/ConfigurationParser.cpp \
   $(WARPED_UTILS_PATH)/utils/StringUtilities.cpp \
   $(WARPED_UTILS_PATH)/utils/ConfigurationLexer.cpp
   
CC_SOURCES = \
   $(WARPED_RND_PATH)/Binomial.cc \
   $(WARPED_RND_PATH)/builtin.cc \
   $(WARPED_RND_PATH)/DiscUnif.cc \
   $(WARPED_RND_PATH)/gcd.cc \
   $(WARPED_RND_PATH)/MLCG.cc \
   $(WARPED_RND_PATH)/NegExp.cc \
   $(WARPED_RND_PATH)/Normal.cc \
   $(WARPED_RND_PATH)/Poisson.cc \
   $(WARPED_RND_PATH)/Random.cc \
   $(WARPED_RND_PATH)/RNG.cc \
   $(WARPED_RND_PATH)/Uniform.cc

OBJECTS = $(CPP_SOURCES:%.cpp=$(OBJDIR)/%.o)
OBJECTS += $(CC_SOURCES:%.cc=$(OBJDIR)/%.o)
DEPENDS = $(OBJECTS:%.o=%.d)

.PHONY: all
all : $(LIBDIR)/llamaWARPED.a headers

.PHONY: headers
headers : $(HEADERS)

$(LIBDIR)/llamaWARPED.a: $(OBJECTS)
	@[ -d $(@D) ] || (mkdir -p $(@D))
	@echo linking: $@
	@$(AR) r $@ $^
	@echo successfully built: $@
	@echo

include rules.mk

# include auto-generated dependencies
-include $(DEPENDS)

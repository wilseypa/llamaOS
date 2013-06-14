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

MAKEFILE_SOURCES += apps/llamaWARPED.mk

WARPED_PATH = $(PDES_ROOT_PATH)/warped/src
WARPED_RND_PATH = $(PDES_ROOT_PATH)/warped/simulationmodels/rnd
WARPED_UTILS_PATH = $(PDES_ROOT_PATH)/utils/src
PCCTS_PATH = $(PCCTS_ROOT_PATH)/h

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

VPATH = $(SRCDIR)

CPP_SOURCES = \
   $(WARPED_PATH)/warped/AdaptiveOutputManager.cpp \
   $(WARPED_PATH)/warped/AdaptiveStateManagerBase.cpp \
   $(WARPED_PATH)/warped/AggressiveOutputManager.cpp \
   $(WARPED_PATH)/warped/CentralizedEventSetSchedulingManager.cpp \
   $(WARPED_PATH)/warped/ChebyFossilCollManager.cpp \
   $(WARPED_PATH)/warped/CirculateInitializationMessage.cpp \
   $(WARPED_PATH)/warped/CommunicationManager.cpp \
   $(WARPED_PATH)/warped/CommunicationManagerFactory.cpp \
   $(WARPED_PATH)/warped/CommunicationManagerImplementationBase.cpp \
   $(WARPED_PATH)/warped/Configurable.cpp \
   $(WARPED_PATH)/warped/ConfigurationManagerFactory.cpp \
   $(WARPED_PATH)/warped/Configurer.cpp \
   $(WARPED_PATH)/warped/ConsoleIO.cpp \
   $(WARPED_PATH)/warped/ControlManager.cpp \
   $(WARPED_PATH)/warped/CostAdaptiveStateManager.cpp \
   $(WARPED_PATH)/warped/DecentralizedEventSetSchedulingManager.cpp \
   $(WARPED_PATH)/warped/DefaultCommunicationManager.cpp \
   $(WARPED_PATH)/warped/DefaultEvent.cpp \
   $(WARPED_PATH)/warped/DefaultPartitioner.cpp \
   $(WARPED_PATH)/warped/DefaultPhysicalCommunicationLayer.cpp \
   $(WARPED_PATH)/warped/DefaultSchedulingManager.cpp \
   $(WARPED_PATH)/warped/DefaultTimeWarpEventContainer.cpp \
   $(WARPED_PATH)/warped/DefaultTimeWarpEventContOneAntiMsg.cpp \
   $(WARPED_PATH)/warped/DefaultTimeWarpEventSet.cpp \
   $(WARPED_PATH)/warped/DeserializerManager.cpp \
   $(WARPED_PATH)/warped/DistributedDVFSManager.cpp \
   $(WARPED_PATH)/warped/DVFSManagerFactory.cpp \
   $(WARPED_PATH)/warped/DVFSManagerImplementationBase.cpp \
   $(WARPED_PATH)/warped/eclmplConfigFileTable.cpp \
   $(WARPED_PATH)/warped/eclmplConnectionInterface.cpp \
   $(WARPED_PATH)/warped/eclmplConnectionInterfaceImplementationBase.cpp \
   $(WARPED_PATH)/warped/eclmplPhysicalCommunicationLayer.cpp \
   $(WARPED_PATH)/warped/eclmplTimer.cpp \
   $(WARPED_PATH)/warped/Event.cpp \
   $(WARPED_PATH)/warped/EventMessage.cpp \
   $(WARPED_PATH)/warped/EventMessageBase.cpp \
   $(WARPED_PATH)/warped/EventSetFactory.cpp \
   $(WARPED_PATH)/warped/FactoryImplementationBase.cpp \
   $(WARPED_PATH)/warped/FactoryManager.cpp \
   $(WARPED_PATH)/warped/FactorySymbolTable.cpp \
   $(WARPED_PATH)/warped/FileManager.cpp \
   $(WARPED_PATH)/warped/FileQueue.cpp \
   $(WARPED_PATH)/warped/FlatState.cpp \
   $(WARPED_PATH)/warped/GVTManagerFactory.cpp \
   $(WARPED_PATH)/warped/GVTManagerImplementationBase.cpp \
   $(WARPED_PATH)/warped/GVTUpdateMessage.cpp \
   $(WARPED_PATH)/warped/InFileQueue.cpp \
   $(WARPED_PATH)/warped/InitializationMessage.cpp \
   $(WARPED_PATH)/warped/IntVTime.cpp \
   $(WARPED_PATH)/warped/KernelMessage.cpp \
   $(WARPED_PATH)/warped/LazyOutputManager.cpp \
   $(WARPED_PATH)/warped/MatternGVTManager.cpp \
   $(WARPED_PATH)/warped/MatternGVTMessage.cpp \
   $(WARPED_PATH)/warped/MessageManager.cpp \
   $(WARPED_PATH)/warped/MPIMessage.cpp \
   $(WARPED_PATH)/warped/MPIPhysicalCommunicationLayer.cpp \
   $(WARPED_PATH)/warped/MsgAggregatingCommunicationManager.cpp \
   $(WARPED_PATH)/warped/NegativeEvent.cpp \
   $(WARPED_PATH)/warped/NegativeEventMessage.cpp \
   $(WARPED_PATH)/warped/NetworkMessage.cpp \
   $(WARPED_PATH)/warped/ObjectStub.cpp \
   $(WARPED_PATH)/warped/OptFossilCollManager.cpp \
   $(WARPED_PATH)/warped/OptFossilCollManagerFactory.cpp \
   $(WARPED_PATH)/warped/OutputEvents.cpp \
   $(WARPED_PATH)/warped/OutputManagerFactory.cpp \
   $(WARPED_PATH)/warped/OutputManagerImplementationBase.cpp \
   $(WARPED_PATH)/warped/Partitioner.cpp \
   $(WARPED_PATH)/warped/PartitionInfo.cpp \
   $(WARPED_PATH)/warped/PeriodicStateManager.cpp \
   $(WARPED_PATH)/warped/RestoreCkptMessage.cpp \
   $(WARPED_PATH)/warped/RoundRobinPartitioner.cpp \
   $(WARPED_PATH)/warped/SchedulingManagerFactory.cpp \
   $(WARPED_PATH)/warped/SequentialConfigurationManager.cpp \
   $(WARPED_PATH)/warped/SequentialFileManager.cpp \
   $(WARPED_PATH)/warped/SequentialSimulationManager.cpp \
   $(WARPED_PATH)/warped/SequentialSimulationStream.cpp \
   $(WARPED_PATH)/warped/Serializable.cpp \
   $(WARPED_PATH)/warped/SerializedInstance.cpp \
   $(WARPED_PATH)/warped/SharedDVFSManager.cpp \
   $(WARPED_PATH)/warped/Simulation.cpp \
   $(WARPED_PATH)/warped/SimulationConfiguration.cpp \
   $(WARPED_PATH)/warped/SimulationManager.cpp \
   $(WARPED_PATH)/warped/SimulationManagerImplementationBase.cpp \
   $(WARPED_PATH)/warped/SimulationObject.cpp \
   $(WARPED_PATH)/warped/SimulationObjectProxy.cpp \
   $(WARPED_PATH)/warped/SimulationStream.cpp \
   $(WARPED_PATH)/warped/SingleLinkedList.cpp \
   $(WARPED_PATH)/warped/SinkObject.cpp \
   $(WARPED_PATH)/warped/SourceObject.cpp \
   $(WARPED_PATH)/warped/Spinner.cpp \
   $(WARPED_PATH)/warped/SplayTree.cpp \
   $(WARPED_PATH)/warped/StartMessage.cpp \
   $(WARPED_PATH)/warped/State.cpp \
   $(WARPED_PATH)/warped/StateManagerFactory.cpp \
   $(WARPED_PATH)/warped/StateManagerImplementationBase.cpp \
   $(WARPED_PATH)/warped/StopWatch.cpp \
   $(WARPED_PATH)/warped/StragglerEvent.cpp \
   $(WARPED_PATH)/warped/TerminateToken.cpp \
   $(WARPED_PATH)/warped/TimeWarpCentralizedEventSetFactory.cpp \
   $(WARPED_PATH)/warped/TimeWarpConfigurationManager.cpp \
   $(WARPED_PATH)/warped/TimeWarpDecentralizedEventSetFactory.cpp \
   $(WARPED_PATH)/warped/TimeWarpEventSet.cpp \
   $(WARPED_PATH)/warped/TimeWarpEventSetFactory.cpp \
   $(WARPED_PATH)/warped/TimeWarpMultiSet.cpp \
   $(WARPED_PATH)/warped/TimeWarpMultiSetOneAntiMsg.cpp \
   $(WARPED_PATH)/warped/TimeWarpMultiSetSchedulingManager.cpp \
   $(WARPED_PATH)/warped/TimeWarpSenderQueue.cpp \
   $(WARPED_PATH)/warped/TimeWarpSimulationManager.cpp \
   $(WARPED_PATH)/warped/TimeWarpSimulationManagerFactory.cpp \
   $(WARPED_PATH)/warped/TimeWarpSimulationObjectQueue.cpp \
   $(WARPED_PATH)/warped/TimeWarpSimulationObjectQueueFactory.cpp \
   $(WARPED_PATH)/warped/TimeWarpSimulationStream.cpp \
   $(WARPED_PATH)/warped/TokenPassingTerminationManager.cpp \
   $(WARPED_PATH)/warped/Transceiver.cpp \
   $(WARPED_PATH)/warped/UsefulWorkMessage.cpp \
   $(WARPED_PATH)/warped/VTime.cpp \
   $(WARPED_PATH)/warped/warped.cpp \
   $(WARPED_PATH)/warped/WarpedMain.cpp \
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

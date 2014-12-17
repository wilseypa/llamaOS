#
# Copyright (c) 2014, William Magato
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

# WARPED_VERSION should be defined in custom-vars.mk
# WARPED_DIR should be defined in custom-vars.mk

OBJDIR = obj/apps/warped-$(WARPED_VERSION)

MAKEFILE_SOURCES += apps/warped-$(WARPED_VERSION)/warped.mk

CFLAGS += \
  -I apps/warped-$(WARPED_VERSION) \
  -I $(INCDIR) \
  -I $(WARPED_DIR)/src \
  -I $(WARPED_DIR)/thirdparty \
  -I $(WARPED_DIR)/thirdparty/metis/GKlib \
  -I $(WARPED_DIR)/thirdparty/metis/include \
  -I $(WARPED_DIR)/thirdparty/metis/libmetis \
  -fexceptions \
  -DJSON_USE_EXCEPTION=0 \
  -include $(SRCDIR)/llamaos/__thread.h

CPPFLAGS += \
  -I apps/warped-$(WARPED_VERSION) \
  -I $(INCDIR) \
  -I $(WARPED_DIR)/src \
  -I $(WARPED_DIR)/thirdparty \
  -I $(WARPED_DIR)/thirdparty/metis/include \
  -fexceptions \
  -DJSON_USE_EXCEPTION=0 \
  -include $(SRCDIR)/llamaos/__thread.h

VPATH = $(WARPED_DIR)/src:$(WARPED_DIR)/thirdparty

C_SOURCES = \
  metis/GKlib/graph.c \
  metis/GKlib/util.c \
  metis/GKlib/b64.c \
  metis/GKlib/blas.c \
  metis/GKlib/csr.c \
  metis/GKlib/error.c \
  metis/GKlib/evaluate.c \
  metis/GKlib/fkvkselect.c \
  metis/GKlib/fs.c \
  metis/GKlib/getopt.c \
  metis/GKlib/gkregex.c \
  metis/GKlib/htable.c \
  metis/GKlib/io.c \
  metis/GKlib/itemsets.c \
  metis/GKlib/mcore.c \
  metis/GKlib/memory.c \
  metis/GKlib/omp.c \
  metis/GKlib/pdb.c \
  metis/GKlib/pqueue.c \
  metis/GKlib/random.c \
  metis/GKlib/rw.c \
  metis/GKlib/seq.c \
  metis/GKlib/sort.c \
  metis/GKlib/string.c \
  metis/GKlib/timers.c \
  metis/GKlib/tokenizer.c \
  metis/libmetis/auxapi.c \
  metis/libmetis/balance.c \
  metis/libmetis/bucketsort.c \
  metis/libmetis/checkgraph.c \
  metis/libmetis/coarsen.c \
  metis/libmetis/compress.c \
  metis/libmetis/contig.c \
  metis/libmetis/debug.c \
  metis/libmetis/fm.c \
  metis/libmetis/fortran.c \
  metis/libmetis/frename.c \
  metis/libmetis/gklib.c \
  metis/libmetis/graph.c \
  metis/libmetis/initpart.c \
  metis/libmetis/kmetis.c \
  metis/libmetis/kwayfm.c \
  metis/libmetis/kwayrefine.c \
  metis/libmetis/mcutil.c \
  metis/libmetis/mesh.c \
  metis/libmetis/meshpart.c \
  metis/libmetis/minconn.c \
  metis/libmetis/mincover.c \
  metis/libmetis/mmd.c \
  metis/libmetis/ometis.c \
  metis/libmetis/options.c \
  metis/libmetis/parmetis.c \
  metis/libmetis/pmetis.c \
  metis/libmetis/refine.c \
  metis/libmetis/separator.c \
  metis/libmetis/sfm.c \
  metis/libmetis/srefine.c \
  metis/libmetis/stat.c \
  metis/libmetis/timing.c \
  metis/libmetis/util.c \
  metis/libmetis/wspace.c 

CPP_SOURCES = \
  json/jsoncpp.cpp \
  eclmpl/MPIPhysicalCommunicationLayer.cpp \
  eclmpl/eclmplConfigFileTable.cpp \
  eclmpl/eclmplConnectionInterface.cpp \
  eclmpl/eclmplConnectionInterfaceImplementationBase.cpp \
  eclmpl/eclmplPhysicalCommunicationLayer.cpp \
  eclmpl/eclmplReliablePhysicalCommunicationLayer.cpp \
  eclmpl/eclmplSocket.cpp \
  eclmpl/eclmplTimer.cpp \
  eclmpl/eclmplUnreliableNetworkMessage.cpp \
  eclmpl/MPIMessage.cpp \
  eclmpl/NetworkMessage.cpp \
  eclmpl/SocketBasedConnectionInterface.cpp \
  eclmpl/TCPConnectionInterface.cpp \
  eclmpl/TCPSelectPhysicalCommunicationLayer.cpp \
  eclmpl/UDPConnectionInterface.cpp \
  eclmpl/UDPSelectPhysicalCommunicationLayer.cpp \
  AdaptiveOutputManager.cpp \
  AdaptiveStateManagerBase.cpp \
  AggressiveOutputManager.cpp \
  Application.cpp \
  ChebyFossilCollManager.cpp \
  CirculateInitializationMessage.cpp \
  CommunicationManager.cpp \
  CommunicationManagerFactory.cpp \
  CommunicationManagerImplementationBase.cpp \
  Configurable.cpp \
  Configurer.cpp \
  ControlManager.cpp \
  CostAdaptiveStateManager.cpp \
  DefaultCommunicationManager.cpp \
  DefaultEvent.cpp \
  DefaultPhysicalCommunicationLayer.cpp \
  DefaultTimeWarpEventContainer.cpp \
  DefaultTimeWarpEventContOneAntiMsg.cpp \
  DefaultTimeWarpEventSet.cpp \
  DeserializerManager.cpp \
  DistributedDVFSManager.cpp \
  DVFSManagerFactory.cpp \
  DVFSManagerImplementationBase.cpp \
  Event.cpp \
  EventMessage.cpp \
  EventMessageBase.cpp \
  EventSetFactory.cpp \
  FactoryImplementationBase.cpp \
  FactoryManager.cpp \
  FactorySymbolTable.cpp \
  FileQueue.cpp \
  FlatState.cpp \
  GraphStatistics.cpp \
  GreedyPartitioner.cpp \
  GVTManagerFactory.cpp \
  GVTManagerImplementationBase.cpp \
  GVTUpdateMessage.cpp \
  InFileQueue.cpp \
  InitializationMessage.cpp \
  IntVTime.cpp \
  KernelMessage.cpp \
  LazyOutputManager.cpp \
  MatternGVTManager.cpp \
  MatternGVTMessage.cpp \
  MessageManager.cpp \
  MsgAggregatingCommunicationManager.cpp \
  NegativeEvent.cpp \
  NegativeEventMessage.cpp \
  ObjectStub.cpp \
  OptFossilCollManager.cpp \
  OptFossilCollManagerFactory.cpp \
  OutputEvents.cpp \
  OutputManagerFactory.cpp \
  OutputManagerImplementationBase.cpp \
  Partitioner.cpp \
  PartitionInfo.cpp \
  PartitionManager.cpp \
  PeriodicStateManager.cpp \
  ProfileGuidedPartitioner.cpp \
  RestoreCkptMessage.cpp \
  RoundRobinPartitioner.cpp \
  SchedulingManagerFactory.cpp \
  SequentialConfigurationManager.cpp \
  SequentialSimulationManager.cpp \
  SequentialSimulationStream.cpp \
  Serializable.cpp \
  SerializedInstance.cpp \
  SharedDVFSManager.cpp \
  Simulation.cpp \
  SimulationConfiguration.cpp \
  SimulationManager.cpp \
  SimulationManagerImplementationBase.cpp \
  SimulationObject.cpp \
  SimulationObjectProxy.cpp \
  SimulationStream.cpp \
  SingleLinkedList.cpp \
  Socket.cpp \
  Spinner.cpp \
  SplayTree.cpp \
  StartMessage.cpp \
  State.cpp \
  StateManagerFactory.cpp \
  StateManagerImplementationBase.cpp \
  StopWatch.cpp \
  StragglerEvent.cpp \
  TerminateToken.cpp \
  ThreadedAggressiveOutputManager.cpp \
  ThreadedChebyFossilCollManager.cpp \
  ThreadedCostAdaptiveStateManager.cpp \
  ThreadedDynamicOutputManager.cpp \
  ThreadedLazyOutputManager.cpp \
  ThreadedMatternGVTManager.cpp \
  ThreadedOptFossilCollManager.cpp \
  ThreadedOutputEvents.cpp \
  ThreadedOutputManagerImplementationBase.cpp \
  ThreadedPeriodicStateManager.cpp \
  ThreadedStateManagerImplementationBase.cpp \
  ThreadedTimeWarpEventSet.cpp \
  ThreadedTimeWarpLoadBalancer.cpp \
  ThreadedTimeWarpMultiSet.cpp \
  ThreadedTimeWarpMultiSetLTSF.cpp \
  ThreadedTimeWarpMultiSetSchedulingManager.cpp \
  ThreadedTimeWarpSimulationManager.cpp \
  TimeWarpConfigurationManager.cpp \
  TimeWarpEventSet.cpp \
  TimeWarpEventSetFactory.cpp \
  TimeWarpMultiSet.cpp \
  TimeWarpMultiSetOneAntiMsg.cpp \
  TimeWarpMultiSetSchedulingManager.cpp \
  TimeWarpSimulationManager.cpp \
  TimeWarpSimulationManagerFactory.cpp \
  TimeWarpSimulationStream.cpp \
  TokenPassingTerminationManager.cpp \
  Transceiver.cpp \
  UsefulWorkMessage.cpp \
  VTime.cpp \
  warped.cpp \
  WarpedDebug.cpp \
  WarpedMain.cpp

HEADERS = \
  $(INCDIR)/warped/controlkit/Actuator.h \
  $(INCDIR)/warped/controlkit/ActuatorImplementationBase.h \
  $(INCDIR)/warped/controlkit/AggregateAsyncFilteredSensor.h \
  $(INCDIR)/warped/controlkit/AggregateSyncSensor.h \
  $(INCDIR)/warped/controlkit/AsyncFilteredSensor.h \
  $(INCDIR)/warped/controlkit/AsyncSensor.h \
  $(INCDIR)/warped/controlkit/AverageFilter.h \
  $(INCDIR)/warped/controlkit/FIRFilter.h \
  $(INCDIR)/warped/controlkit/Filter.h \
  $(INCDIR)/warped/controlkit/IIRFilter.h \
  $(INCDIR)/warped/controlkit/MedianFilter.h \
  $(INCDIR)/warped/controlkit/Sensor.h \
  $(INCDIR)/warped/controlkit/SensorImplementationBase.h \
  $(INCDIR)/warped/controlkit/SyncSensor.h \
  $(INCDIR)/warped/eclmpl/eclmpl.h \
  $(INCDIR)/warped/eclmpl/eclmplCommonInclude.h \
  $(INCDIR)/warped/eclmpl/eclmplConfigFileTable.h \
  $(INCDIR)/warped/eclmpl/eclmplConnectionInterface.h \
  $(INCDIR)/warped/eclmpl/eclmplConnectionInterfaceImplementationBase.h \
  $(INCDIR)/warped/eclmpl/eclmplContactInfo.h \
  $(INCDIR)/warped/eclmpl/eclmplPhysicalCommunicationLayer.h \
  $(INCDIR)/warped/eclmpl/eclmplReliablePhysicalCommunicationLayer.h \
  $(INCDIR)/warped/eclmpl/eclmplSocket.h \
  $(INCDIR)/warped/eclmpl/eclmplTimer.h \
  $(INCDIR)/warped/eclmpl/eclmplUnreliableNetworkMessage.h \
  $(INCDIR)/warped/eclmpl/MPIMessage.h \
  $(INCDIR)/warped/eclmpl/MPIPhysicalCommunicationLayer.h \
  $(INCDIR)/warped/eclmpl/NetworkMessage.h \
  $(INCDIR)/warped/eclmpl/PhysicalCommunicationLayer.h \
  $(INCDIR)/warped/eclmpl/SocketBasedConnectionInterface.h \
  $(INCDIR)/warped/eclmpl/TCPConnectionInterface.h \
  $(INCDIR)/warped/eclmpl/TCPSelectPhysicalCommunicationLayer.h \
  $(INCDIR)/warped/eclmpl/UDPConnectionInterface.h \
  $(INCDIR)/warped/eclmpl/UDPSelectPhysicalCommunicationLayer.h \
  $(INCDIR)/warped/AdaptiveOutputManager.h \
  $(INCDIR)/warped/AdaptiveStateManagerBase.h \
  $(INCDIR)/warped/AggressiveOutputManager.h \
  $(INCDIR)/warped/Application.h \
  $(INCDIR)/warped/AtomicState.h \
  $(INCDIR)/warped/ChebyFossilCollManager.h \
  $(INCDIR)/warped/CirculateInitializationMessage.h \
  $(INCDIR)/warped/CommunicatingEntity.h \
  $(INCDIR)/warped/CommunicationManager.h \
  $(INCDIR)/warped/CommunicationManagerFactory.h \
  $(INCDIR)/warped/CommunicationManagerImplementationBase.h \
  $(INCDIR)/warped/Configurable.h \
  $(INCDIR)/warped/ConfigurationManager.h \
  $(INCDIR)/warped/Configurer.h \
  $(INCDIR)/warped/ControlManager.h \
  $(INCDIR)/warped/CostAdaptiveStateManager.h \
  $(INCDIR)/warped/DVFSManager.h \
  $(INCDIR)/warped/DVFSManagerFactory.h \
  $(INCDIR)/warped/DVFSManagerImplementationBase.h \
  $(INCDIR)/warped/DefaultCommunicationManager.h \
  $(INCDIR)/warped/DefaultEvent.h \
  $(INCDIR)/warped/DefaultObjectID.h \
  $(INCDIR)/warped/DefaultPhysicalCommunicationLayer.h \
  $(INCDIR)/warped/DefaultTimeWarpEventContOneAntiMsg.h \
  $(INCDIR)/warped/DefaultTimeWarpEventContainer.h \
  $(INCDIR)/warped/DefaultTimeWarpEventSet.h \
  $(INCDIR)/warped/DeserializerManager.h \
  $(INCDIR)/warped/DistributedDVFSManager.h \
  $(INCDIR)/warped/Event.h \
  $(INCDIR)/warped/EventFunctors.h \
  $(INCDIR)/warped/EventId.h \
  $(INCDIR)/warped/EventMessage.h \
  $(INCDIR)/warped/EventMessageBase.h \
  $(INCDIR)/warped/EventSet.h \
  $(INCDIR)/warped/EventSetFactory.h \
  $(INCDIR)/warped/Factory.h \
  $(INCDIR)/warped/FactoryImplementationBase.h \
  $(INCDIR)/warped/FactoryManager.h \
  $(INCDIR)/warped/FactorySymbolTable.h \
  $(INCDIR)/warped/FileData.h \
  $(INCDIR)/warped/FileQueue.h \
  $(INCDIR)/warped/FlatState.h \
  $(INCDIR)/warped/GVTManager.h \
  $(INCDIR)/warped/GVTManagerFactory.h \
  $(INCDIR)/warped/GVTManagerImplementationBase.h \
  $(INCDIR)/warped/GVTUpdateMessage.h \
  $(INCDIR)/warped/GraphStatistics.h \
  $(INCDIR)/warped/GreedyPartitioner.h \
  $(INCDIR)/warped/InFileData.h \
  $(INCDIR)/warped/InFileQueue.h \
  $(INCDIR)/warped/InitializationMessage.h \
  $(INCDIR)/warped/InputSetObject.h \
  $(INCDIR)/warped/IntVTime.h \
  $(INCDIR)/warped/KernelMessage.h \
  $(INCDIR)/warped/LadderQRelaxed.h \
  $(INCDIR)/warped/LadderQStrict.h \
  $(INCDIR)/warped/LazyOutputManager.h \
  $(INCDIR)/warped/ListNode.h \
  $(INCDIR)/warped/LockFreeList.h \
  $(INCDIR)/warped/LockState.h \
  $(INCDIR)/warped/LockedQueue.h \
  $(INCDIR)/warped/MatternGVTManager.h \
  $(INCDIR)/warped/MatternGVTMessage.h \
  $(INCDIR)/warped/MatternObjectRecord.h \
  $(INCDIR)/warped/MessageManager.h \
  $(INCDIR)/warped/MsgAggregatingCommunicationManager.h \
  $(INCDIR)/warped/NegativeEvent.h \
  $(INCDIR)/warped/NegativeEventMessage.h \
  $(INCDIR)/warped/ObjectID.h \
  $(INCDIR)/warped/ObjectStub.h \
  $(INCDIR)/warped/OptFossilCollManager.h \
  $(INCDIR)/warped/OptFossilCollManagerFactory.h \
  $(INCDIR)/warped/OutputEvents.h \
  $(INCDIR)/warped/OutputManager.h \
  $(INCDIR)/warped/OutputManagerFactory.h \
  $(INCDIR)/warped/OutputManagerImplementationBase.h \
  $(INCDIR)/warped/PartitionInfo.h \
  $(INCDIR)/warped/PartitionManager.h \
  $(INCDIR)/warped/Partitioner.h \
  $(INCDIR)/warped/PeriodicStateManager.h \
  $(INCDIR)/warped/ProfileGuidedPartitioner.h \
  $(INCDIR)/warped/ReceiverQueueContainer.h \
  $(INCDIR)/warped/RestoreCkptMessage.h \
  $(INCDIR)/warped/RoundRobinPartitioner.h \
  $(INCDIR)/warped/SchedulingData.h \
  $(INCDIR)/warped/SchedulingManager.h \
  $(INCDIR)/warped/SchedulingManagerFactory.h \
  $(INCDIR)/warped/SenderQueueContainer.h \
  $(INCDIR)/warped/SequentialConfigurationManager.h \
  $(INCDIR)/warped/SequentialSimulationManager.h \
  $(INCDIR)/warped/SequentialSimulationStream.h \
  $(INCDIR)/warped/Serializable.h \
  $(INCDIR)/warped/SerializedInstance.h \
  $(INCDIR)/warped/SetObject.h \
  $(INCDIR)/warped/SharedDVFSManager.h \
  $(INCDIR)/warped/Simulation.h \
  $(INCDIR)/warped/SimulationConfiguration.h \
  $(INCDIR)/warped/SimulationManager.h \
  $(INCDIR)/warped/SimulationManagerImplementationBase.h \
  $(INCDIR)/warped/SimulationObject.h \
  $(INCDIR)/warped/SimulationObjectProxy.h \
  $(INCDIR)/warped/SimulationStream.h \
  $(INCDIR)/warped/SingleLinkedList.h \
  $(INCDIR)/warped/SingleTerminationManager.h \
  $(INCDIR)/warped/Socket.h \
  $(INCDIR)/warped/Spinner.h \
  $(INCDIR)/warped/SplayTree.h \
  $(INCDIR)/warped/StackOfPtr.h \
  $(INCDIR)/warped/StartMessage.h \
  $(INCDIR)/warped/State.h \
  $(INCDIR)/warped/StateManager.h \
  $(INCDIR)/warped/StateManagerFactory.h \
  $(INCDIR)/warped/StateManagerImplementationBase.h \
  $(INCDIR)/warped/StateSetObject.h \
  $(INCDIR)/warped/StopWatch.h \
  $(INCDIR)/warped/StragglerEvent.h \
  $(INCDIR)/warped/TerminateToken.h \
  $(INCDIR)/warped/TerminationManager.h \
  $(INCDIR)/warped/ThreadedAggressiveOutputManager.h \
  $(INCDIR)/warped/ThreadedChebyFossilCollManager.h \
  $(INCDIR)/warped/ThreadedCostAdaptiveStateManager.h \
  $(INCDIR)/warped/ThreadedDynamicOutputManager.h \
  $(INCDIR)/warped/ThreadedLazyOutputManager.h \
  $(INCDIR)/warped/ThreadedMatternGVTManager.h \
  $(INCDIR)/warped/ThreadedOptFossilCollManager.h \
  $(INCDIR)/warped/ThreadedOutputEvents.h \
  $(INCDIR)/warped/ThreadedOutputManager.h \
  $(INCDIR)/warped/ThreadedOutputManagerImplementationBase.h \
  $(INCDIR)/warped/ThreadedPeriodicStateManager.h \
  $(INCDIR)/warped/ThreadedStateManager.h \
  $(INCDIR)/warped/ThreadedStateManagerImplementationBase.h \
  $(INCDIR)/warped/ThreadedTimeWarpEventSet.h \
  $(INCDIR)/warped/ThreadedTimeWarpLoadBalancer.h \
  $(INCDIR)/warped/ThreadedTimeWarpMultiSet.h \
  $(INCDIR)/warped/ThreadedTimeWarpMultiSetLTSF.h \
  $(INCDIR)/warped/ThreadedTimeWarpMultiSetSchedulingManager.h \
  $(INCDIR)/warped/ThreadedTimeWarpSimulationManager.h \
  $(INCDIR)/warped/TimeWarpCentralizedEventSet.h \
  $(INCDIR)/warped/TimeWarpConfigurationManager.h \
  $(INCDIR)/warped/TimeWarpEventSet.h \
  $(INCDIR)/warped/TimeWarpEventSetFactory.h \
  $(INCDIR)/warped/TimeWarpMultiSet.h \
  $(INCDIR)/warped/TimeWarpMultiSetOneAntiMsg.h \
  $(INCDIR)/warped/TimeWarpMultiSetSchedulingManager.h \
  $(INCDIR)/warped/TimeWarpSimulationManager.h \
  $(INCDIR)/warped/TimeWarpSimulationManagerFactory.h \
  $(INCDIR)/warped/TimeWarpSimulationStream.h \
  $(INCDIR)/warped/TokenPassingTerminationManager.h \
  $(INCDIR)/warped/Transceiver.h \
  $(INCDIR)/warped/TreeElement.h \
  $(INCDIR)/warped/Types.h \
  $(INCDIR)/warped/UsefulWorkMessage.h \
  $(INCDIR)/warped/VTime.h \
  $(INCDIR)/warped/warped.h \
  $(INCDIR)/warped/WarpedConfig.h \
  $(INCDIR)/warped/WarpedDebug.h \
  $(INCDIR)/warped/WarpedMain.h \
  $(INCDIR)/warped/WorkerInformation.h

OBJECTS = $(C_SOURCES:%.c=$(OBJDIR)/%.o)
OBJECTS += $(CPP_SOURCES:%.cpp=$(OBJDIR)/%.o)
DEPENDS = $(OBJECTS:%.o=%.d)

.PHONY: all
all : $(LIBDIR)/apps/warped/warped.a $(HEADERS)

$(LIBDIR)/apps/warped/warped.a: $(OBJECTS)
	@[ -d $(@D) ] || (mkdir -p $(@D))
	@echo linking: $@
	@$(AR) r $@ $(OBJECTS)
	@echo successfully built: $@
	@echo

$(INCDIR)/warped/WarpedConfig.h : apps/warped-$(WARPED_VERSION)/WarpedConfig.h
	@[ -d $(@D) ] || (mkdir -p $(@D))
	@echo copying: $@ from $<
	cp $< $@

$(INCDIR)/warped/% : $(WARPED_DIR)/src/%
	@[ -d $(@D) ] || (mkdir -p $(@D))
	@echo copying: $@ from $<
	cp $< $@

include rules.mk

# include auto-generated dependencies
-include $(DEPENDS)

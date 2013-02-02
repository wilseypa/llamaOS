/*
Copyright (c) 2013, John Gideon
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

   1. Redistributions of source code must retain the above copyright notice,
      this list of conditions and the following disclaimer.

   2. Redistributions in binary form must reproduce the above copyright notice,
      this list of conditions and the following disclaimer in the documentation
      and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDER(S) AND CONTRIBUTORS ''AS IS''
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER(S) OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

The views and conclusions contained in the software and documentation are those
of the authors and should not be interpreted as representing official policies,
either expressed or implied, of the copyright holder(s) or contributors.
*/

#include <iComm.h>

// Create Comm based on new id and associated group
iComm::iComm(MPI_Comm nId, iGroup *nGroup) {
   id = nId;
   group = nGroup;
   localRank = group->getLocalRank();
   localWorldRank = group->getLocalWorldRank();
   size = group->getSize();
   mpiData.comm[id] = this;
   pt2ptRxBuffer = new iRxBuffer();
   collectiveRxBuffer = new iRxBuffer();
}

// Copy comm from a previous one - also copy group - still gets a unique ID
iComm::iComm(iComm *comm) {
   id = getNewId(comm->getId(), true);
   group = new iGroup(comm->group);
   size = comm->size;
   localRank = comm->localRank;	
   localWorldRank = comm->localWorldRank;
   mpiData.comm[id] = this;
   pt2ptRxBuffer = new iRxBuffer();
   collectiveRxBuffer = new iRxBuffer();
}

// Create a new comm from a group that is a subset of the old comm
iComm::iComm(iComm *comm, iGroup *pgroup) {
   size = pgroup->getSize();
   localRank = pgroup->getLocalRank();
   localWorldRank = pgroup->getLocalWorldRank();
   bool join = !(localRank == MPI_UNDEFINED);
   id = getNewId(comm->getId(), join);
   if (join) {
      pt2ptRxBuffer = new iRxBuffer();
      collectiveRxBuffer = new iRxBuffer();
      group = new iGroup(pgroup);
      mpiData.comm[id] = this;
   }
}

// Destroy the reference to the id in the global hash map
iComm::~iComm() {
   if (id == MPI_COMM_NULL) {
      mpiData.comm.erase(id);
      delete group;
      delete pt2ptRxBuffer;
      delete collectiveRxBuffer;
   }
}

// Get a unique identifier for a new comm from a current comm
MPI_Comm iComm::getNewId(MPI_Comm comm, bool join) {
   static MPI_Comm nextId = 1;
   MPI_Comm newId;
   if (join) {
      newId = nextId;
   } else {
      newId = 0;
   }
   MPI_Allreduce (&newId, &newId, 1, MPI_INT, MPI_MAX, comm);
   if (join) {
      nextId = newId+1;
      return newId;
   } else {
      return MPI_COMM_NULL;
   }
}

// Translate the comm rank to the world rank
int iComm::getWorldRankFromRank(int rank) {
   return group->getWorldRankFromRank(rank);
}

// Translate the world rank to the comm rank
int iComm::getRankFromWorldRank(int worldRank) {
   return group->getRankFromWorldRank(worldRank);
}

// Get the group in comm
iGroup* iComm::getGroup() {
   return group;
}

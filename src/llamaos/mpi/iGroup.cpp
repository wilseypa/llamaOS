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

#include <iGroup.h>
#include <string.h>

// Return the next unique identifier
MPI_Group iGroup::getNextId() {
   static MPI_Group nextId = 1;
   return nextId++;
}

// Creating completely new group from scratch (only used internally)
iGroup::iGroup(IGROUP_CREATE_TYPE type) {
   switch (type) {
      case IGROUP_CREATE_WORLD: {
         id = getNextId();
         size = mpiData.totNodes;
         localRank = mpiData.rank;
         localWorldRank = mpiData.rank;
         rankToWorldRank.resize(size);
         for (int i = 0; i < size; i++) {
            linkRankToWorldRank(i,i);
         }
         break;
      }
      case IGROUP_CREATE_EMPTY: {
         id = MPI_GROUP_EMPTY;
         size = 0;
         localRank = MPI_UNDEFINED;
         localWorldRank = MPI_UNDEFINED;
         rankToWorldRank.resize(0);
         break;
      }
      case IGROUP_CREATE_SELF: {
         id = getNextId();
         size = 1;
         localRank = mpiData.rank;
         localWorldRank = mpiData.rank;
         rankToWorldRank.resize(size);
         linkRankToWorldRank(0,localRank);
         break;
      }
   }
   mpiData.group[id] = this;
}

// Create new group based off of an old one and a list of ranks
iGroup::iGroup(IGROUP_CREATE_TYPE type, iGroup *group, int n, int *ranks) {
   switch (type) {
      case IGROUP_CREATE_INCL: {
         id = getNextId();
         size = n;
         rankToWorldRank.resize(size);
         for (int i = 0; i < n; i++) {
            linkRankToWorldRank(i, group->getWorldRankFromRank(ranks[i]));
         }
         localRank = getRankFromWorldRank(mpiData.rank);
         if (localRank == MPI_UNDEFINED) {
            localWorldRank = MPI_UNDEFINED;
         } else {
            localWorldRank = mpiData.rank;
         }
         break;
      }
      case IGROUP_CREATE_EXCL: {
         id = getNextId();
         int oldSize = group->getSize();
         size = oldSize-n;
         rankToWorldRank.resize(size);
         std::vector<bool> inNewGroup(oldSize,true);
         for (int i = 0; i < n; i++) {
            inNewGroup[ranks[i]] = false;
         }
         int oldRank = 0;
         for (int newRank = 0; newRank < size; newRank++) {
            while (!inNewGroup[oldRank]) {oldRank++;}          
            linkRankToWorldRank(newRank, group->getWorldRankFromRank(oldRank++));
         }
         localRank = getRankFromWorldRank(mpiData.rank);
         if (localRank == MPI_UNDEFINED) {
            localWorldRank = MPI_UNDEFINED;
         } else {
            localWorldRank = mpiData.rank;
         }
         break;
      }
   }
   mpiData.group[id] = this;
}

// Create new group based on two old groups
iGroup::iGroup(IGROUP_CREATE_TYPE type, iGroup *group1, iGroup *group2) {
   // Set up merge data
   MAP_TYPE<int,int> worldRankToNum;
   for (int i = 0; i < group1->getSize(); i++) {
      int iWorldRank = group1->getWorldRankFromRank(i);
      worldRankToNum[iWorldRank] = 1;
   }
   for (int i = 0; i < group2->getSize(); i++) {
      int iWorldRank = group2->getWorldRankFromRank(i);
      MAP_TYPE<int,int>::iterator it = worldRankToNum.find(iWorldRank);
      if (it == worldRankToNum.end()) { // Not in other group
         worldRankToNum[iWorldRank] = 1;
      } else { // In other group
         worldRankToNum[iWorldRank] = 2;
      }
   }

   // Merge dependant on type
   switch (type) {
      case IGROUP_CREATE_UNION: {
         for (int i = 0; i < group1->getSize(); i++) {
            int iWorldRank = group1->getWorldRankFromRank(i);
            pushWorldRank(iWorldRank); 
         }
         for (int i = 0; i < group2->getSize(); i++) {
            int iWorldRank = group2->getWorldRankFromRank(i);
            if (worldRankToNum[iWorldRank] == 1) { // if not in other
               pushWorldRank(iWorldRank); 
            }
         }
         break;
      }
      case IGROUP_CREATE_INTER: {
         for (int i = 0; i < group1->getSize(); i++) {
            int iWorldRank = group1->getWorldRankFromRank(i);
            if (worldRankToNum[iWorldRank] == 2) { // if in other
               pushWorldRank(iWorldRank); 
            }
         }
         break;
      }
      case IGROUP_CREATE_DIFF: {
         for (int i = 0; i < group1->getSize(); i++) {
            int iWorldRank = group1->getWorldRankFromRank(i);
            if (worldRankToNum[iWorldRank] == 1) { // if not in other
               pushWorldRank(iWorldRank); 
            }
         }
         for (int i = 0; i < group2->getSize(); i++) {
            int iWorldRank = group2->getWorldRankFromRank(i);
            if (worldRankToNum[iWorldRank] == 1) { // if not in other
               pushWorldRank(iWorldRank); 
            }
         }
         break;
      }
   }

   // Set ID and size
   size = rankToWorldRank.size();
   if (size == 0) {
      id = MPI_GROUP_EMPTY;
   } else {
      id = getNextId();
   }

   // Set local values      
   localRank = getRankFromWorldRank(mpiData.rank);
   if (localRank == MPI_UNDEFINED) {
      localWorldRank = MPI_UNDEFINED;
   } else {
      localWorldRank = mpiData.rank;
   }

   // Add to global map
   mpiData.group[id] = this;
}

// Compares two groups to determine similarity
int iGroup::compare(iGroup *oGroup) {
   // First test for unequal lengths
   if (size != oGroup->getSize()) {
      return MPI_UNEQUAL;
   }

   // Next test for MPI_IDENT
   bool isDiff = false;
   for (int i = 0; i < size; i++) {
      if (getWorldRankFromRank(i) != oGroup->getWorldRankFromRank(i)) {
         isDiff = true;
         break;
      }
   }
   if (!isDiff) {
      return MPI_IDENT;
   }

   // Last test for MPI_SIMILAR
   for (int i = 0; i < size; i++) {
      if (getRankFromWorldRank(oGroup->getWorldRankFromRank(i)) == MPI_UNDEFINED) {
         return MPI_UNEQUAL;
      }
   }
   return MPI_SIMILAR;
}

// Links a rank and world rank together
void iGroup::linkRankToWorldRank(int rank, int worldRank) {
   rankToWorldRank[rank] = worldRank;
   worldRankToRank[worldRank] = rank;
}

// Adds a new rank and assigns world rank to it
void iGroup::pushWorldRank(int worldRank) {
   rankToWorldRank.push_back(worldRank);
   worldRankToRank[worldRank] = rankToWorldRank.size()-1;
}

// Destroy the reference to the id in the global hash map
iGroup::~iGroup() {
   if (id != IGROUP_CREATE_EMPTY) {
      mpiData.group.erase(id);
   }
}

// Translate the comm rank to the world rank
int iGroup::getWorldRankFromRank(int rank) {
   if (rank >= 0 && rank < size) {
      return rankToWorldRank[rank];
   } else {
      return MPI_UNDEFINED;
   }
}

// Translate the world rank to the comm rank
int iGroup::getRankFromWorldRank(int worldRank) {
   MAP_TYPE<int,int>::iterator it = worldRankToRank.find(worldRank);
   if (it != worldRankToRank.end()) {
      return it->second;
   } else {
      return MPI_UNDEFINED;
   }
}

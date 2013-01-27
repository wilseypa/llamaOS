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

#include "iGroup.h"
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
         rankToWorldRank.resize(size);
         for (int i = 0; i < size; i++) {
            rankToWorldRank[i] = i;
         }
         break;
      }
      case IGROUP_CREATE_EMPTY: {
         id = MPI_GROUP_EMPTY;
         size = 0;
         localRank = MPI_UNDEFINED;
         rankToWorldRank.resize(size);
         break;
      }
      case IGROUP_CREATE_SELF: {
         id = getNextId();
         size = 1;
         localRank = mpiData.rank;
         rankToWorldRank.resize(size);
         rankToWorldRank[0] = localRank;
         break;
      }
   }
   mpiData.group[id] = this;
}

// Destroy the reference to the id in the global hash map
iGroup::~iGroup() {
   mpiData.group.erase(id);
}

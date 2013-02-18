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

#ifndef I_GROUP_H_
#define I_GROUP_H_

#include <iGlobals.h>
#include <vector>

typedef int IGROUP_CREATE_TYPE;
#define IGROUP_CREATE_WORLD ((IGROUP_CREATE_TYPE)1)
#define IGROUP_CREATE_EMPTY ((IGROUP_CREATE_TYPE)2)
#define IGROUP_CREATE_SELF ((IGROUP_CREATE_TYPE)3)
#define IGROUP_CREATE_INCL ((IGROUP_CREATE_TYPE)4)
#define IGROUP_CREATE_EXCL ((IGROUP_CREATE_TYPE)5)
#define IGROUP_CREATE_UNION ((IGROUP_CREATE_TYPE)6)
#define IGROUP_CREATE_INTER ((IGROUP_CREATE_TYPE)7)
#define IGROUP_CREATE_DIFF ((IGROUP_CREATE_TYPE)8)
#define IGROUP_CREATE_NEW ((IGROUP_CREATE_TYPE)9)

class iGroup {
   public:
      iGroup(IGROUP_CREATE_TYPE type);
      iGroup(IGROUP_CREATE_TYPE type, int psize);
      iGroup(IGROUP_CREATE_TYPE type, iGroup *group, int n, int *ranks);
      iGroup(IGROUP_CREATE_TYPE type, iGroup *group1, iGroup *group2);
      iGroup(iGroup *group);
      ~iGroup();
      MPI_Group getId() {return id;}
      int getSize() {return size;}
      int getLocalRank() {return localRank;}
      int getLocalWorldRank() {return localWorldRank;}
      int getWorldRankFromRank(int rank);
      int getRankFromWorldRank(int worldRank);
      int compare(iGroup *oGroup);
      void pushWorldRank(int worldRank);
      void calculateLocalRanks();
   private:
      MPI_Group id;
      int size;
      int localRank;      // Rank of local process node in comm
      int localWorldRank; // Rank of local process node in world
      std::vector<int> rankToWorldRank;	// Conversion of rank in comm to world rank
      MAP_TYPE<int,int> worldRankToRank; // Conversion of world rank to rank in comm

      MPI_Group getNextId();
      void linkRankToWorldRank(int rank, int worldRank);
};

#endif

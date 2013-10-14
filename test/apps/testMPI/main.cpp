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

#include <mpi.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <llamaos/api/sleep.h>

using namespace std;

void duoTest();
void groupTest();
void commTest();
void nonBlockTest();
void largeTest();

int main(int argc, char *argv []) {
   MPI_Init (&argc, &argv);
   cout << "Starting program" << endl;
   double startTime = MPI_Wtime();

   //largeTest();	// for 2
   //duoTest();   // for 2
   //groupTest(); // for 3 or more
   //commTest();    // for 3 or more
   nonBlockTest(); // for 2 or more

   double stopTime = MPI_Wtime();
   cout << "Tests completed in " << (int)(stopTime-startTime) << " seconds" << endl;
   cout << "Ending program" << endl;
   MPI_Finalize();

   return 0;
}

void largeTest() {
   int rank, totNodes;
   MPI_Comm_rank(MPI_COMM_WORLD, &rank);
   MPI_Comm_size(MPI_COMM_WORLD, &totNodes);

   cout << "Starting large test" << endl;

   cout << "Direct Test" << endl;
	for (int mSize = 1; mSize <= 10000; mSize *= 10) {
      cout << "Message Size: " << mSize << "...  ";
		int *buf = new int[mSize];
      if (rank == 0) {
         for (int source = 1; source < totNodes; source++) {
            MPI_Status status;
            MPI_Recv(buf, mSize, MPI_INT, source, 0, MPI_COMM_WORLD, &status);
			   bool isValid = true;
            for (int i=0; i < mSize; i++) {
				   if (buf[i] != i) {
                  isValid = false;
                  break;
               }
			   }
            if (isValid) {
               cout << "VALID     ";
            } else {
               cout << "NOT VALID     ";
            }
         }
         cout << endl;
      } else {
			for (int i=0; i < mSize; i++) {
				buf[i] = i;
			}
         MPI_Send(buf, mSize, MPI_INT, 0, 0, MPI_COMM_WORLD);
         cout << "Sent message to root" << endl;
      }  
		delete[] buf;
      cout << "Barrier" << endl;
      MPI_Barrier(MPI_COMM_WORLD);
      llamaos::api::sleep(3);
   }

   cout << "Buffered Test" << endl;
	for (int mSize = 1; mSize <= 10000; mSize *= 10) {
      cout << "Message Size: " << mSize << "...  ";
		int *buf0 = new int[mSize];
      int *buf1 = new int[mSize];
      if (rank == 0) {
         for (int source = 1; source < totNodes; source++) {
            MPI_Status status;
            MPI_Recv(buf1, mSize, MPI_INT, source, 1, MPI_COMM_WORLD, &status);
            MPI_Recv(buf0, mSize, MPI_INT, source, 0, MPI_COMM_WORLD, &status);
			   bool isValid = true;
            for (int i=0; i < mSize; i++) {
				   if (buf0[i] != i) {
                  isValid = false;
                  break;
               }
				   if (buf1[i] != mSize+i) {
                  isValid = false;
                  break;
               }
			   }
            if (isValid) {
               cout << "VALID     ";
            } else {
               cout << "NOT VALID     ";
            }
         }
         cout << endl;
      } else {
			for (int i=0; i < mSize; i++) {
				buf0[i] = i;
            buf1[i] = mSize+i;
			}
         MPI_Send(buf0, mSize, MPI_INT, 0, 0, MPI_COMM_WORLD);
         MPI_Send(buf1, mSize, MPI_INT, 0, 1, MPI_COMM_WORLD);
         cout << "Sent messages to root" << endl;
      }  
		delete[] buf0;
      delete[] buf1;
      cout << "Barrier" << endl;
      MPI_Barrier(MPI_COMM_WORLD);
      llamaos::api::sleep(3);
   }
}

void nonBlockTest() {
   cout << "Starting non-blocking duo test" << endl;
   int rank, totNodes;
   MPI_Comm_rank(MPI_COMM_WORLD, &rank);
   MPI_Comm_size(MPI_COMM_WORLD, &totNodes);
   
   cout << "MPI_Probe test" << endl;
   if (rank == 0) {
      for (int source = 1; source < totNodes; source++) {
         char buf[100];
         MPI_Status status;
         MPI_Probe(source, 0, MPI_COMM_WORLD, &status);
         int charCount;
         MPI_Get_count(&status, MPI_UNSIGNED_CHAR, &charCount);
         cout << "Ready to receive message of size " << charCount << " unsigned chars" << endl;
         MPI_Recv(&buf, 100, MPI_UNSIGNED_CHAR, source, 0, MPI_COMM_WORLD, &status);
         cout << buf << endl;
      }
   } else {
      char buf[100];
      sprintf(buf, "Received message from node %d", rank);
      MPI_Send(&buf, 100, MPI_UNSIGNED_CHAR, 0, 0, MPI_COMM_WORLD);
      cout << "Sent message to root" << endl;
   }
   
   cout << "Barrier" << endl;
   MPI_Barrier(MPI_COMM_WORLD);

   cout << "MPI_Iprobe test" << endl;
   if (rank == 0) {
      for (int source = 1; source < totNodes; source++) {
         char buf[100];
         MPI_Status status;
         int flag;
         do {
            MPI_Iprobe(source, 0, MPI_COMM_WORLD, &flag, &status);
         } while(!flag);
         int charCount;
         MPI_Get_count(&status, MPI_UNSIGNED_CHAR, &charCount);
         cout << "Ready to receive message of size " << charCount << " unsigned chars" << endl;
         MPI_Recv(&buf, charCount, MPI_UNSIGNED_CHAR, source, 0, MPI_COMM_WORLD, &status);
         cout << buf << endl;
      }
   } else {
      llamaos::api::sleep(4);
      char buf[100];
      sprintf(buf, "Received iprobe message from node %d", rank);
      MPI_Send(&buf, 100, MPI_UNSIGNED_CHAR, 0, 0, MPI_COMM_WORLD);
      cout << "Sent message to root" << endl;
   }

   cout << "Barrier" << endl;
   MPI_Barrier(MPI_COMM_WORLD);

   cout << "MPI_Wait test" << endl;
   if (rank == 0) {
      for (int source = 1; source < totNodes; source++) {
         char buf[100];
         MPI_Status status;
         MPI_Request request;
         MPI_Irecv(&buf, 100, MPI_UNSIGNED_CHAR, source, 0, MPI_COMM_WORLD, &request);
         cout << "Request ID: " << request << endl;
         MPI_Wait(&request, &status);
         cout << buf << endl;
      }
   } else {
      char buf[100];
      sprintf(buf, "Received wait message from node %d", rank);
      MPI_Request request;
      MPI_Isend(&buf, 100, MPI_UNSIGNED_CHAR, 0, 0, MPI_COMM_WORLD, &request);
      cout << "Request ID: " << request << endl;
      MPI_Request_free(&request);
      cout << "Sent message to root" << endl;
   }

   cout << "Barrier" << endl;
   MPI_Barrier(MPI_COMM_WORLD);
   
   cout << "MPI_Waitall test" << endl;
   if (rank == 0) {
      for (int source = 1; source < totNodes; source++) {
         char buf[2][100];
         MPI_Status status[2];
         MPI_Request request[2];
         MPI_Irecv(&buf[0], 100, MPI_UNSIGNED_CHAR, source, 1, MPI_COMM_WORLD, &request[0]);
         MPI_Irecv(&buf[1], 100, MPI_UNSIGNED_CHAR, source, 0, MPI_COMM_WORLD, &request[1]);
         cout << "Request0 ID: " << request[0] << endl;
         cout << "Request1 ID: " << request[1] << endl;
         MPI_Waitall(2, request, status);
         cout << buf[0] << endl;
         cout << buf[1] << endl;
      }
   } else {
      char buf[100];
      sprintf(buf, "Received waitall message 0 from node %d", rank);
      MPI_Send(&buf, 100, MPI_UNSIGNED_CHAR, 0, 0, MPI_COMM_WORLD);
      llamaos::api::sleep(4);
      sprintf(buf, "Received waitall message 1 from node %d", rank);
      MPI_Send(&buf, 100, MPI_UNSIGNED_CHAR, 0, 1, MPI_COMM_WORLD);
      cout << "Sent messages to root" << endl;
   }

   cout << "Barrier" << endl;
   MPI_Barrier(MPI_COMM_WORLD);

   cout << "MPI_Waitany test" << endl;
   if (rank == 0) {
      for (int source = 1; source < totNodes; source++) {
         char buf[2][100];
         MPI_Status status;
         MPI_Request request[2];
         MPI_Irecv(&buf[0], 100, MPI_UNSIGNED_CHAR, source, 1, MPI_COMM_WORLD, &request[0]);
         MPI_Irecv(&buf[1], 100, MPI_UNSIGNED_CHAR, source, 0, MPI_COMM_WORLD, &request[1]);
         int index;
         for (int i = 0; i < 2; i++) {
            cout << "Request0 ID: " << request[0] << endl;
            cout << "Request1 ID: " << request[1] << endl;
            MPI_Waitany(2, request, &index, &status);
            cout << "Index: " << index << "  -  " << buf[index] << endl;
         }
      }
   } else {
      char buf[100];
      sprintf(buf, "Received waitany message 0 from node %d", rank);
      MPI_Send(&buf, 100, MPI_UNSIGNED_CHAR, 0, 0, MPI_COMM_WORLD);
      llamaos::api::sleep(4);
      sprintf(buf, "Received waitany message 1 from node %d", rank);
      MPI_Send(&buf, 100, MPI_UNSIGNED_CHAR, 0, 1, MPI_COMM_WORLD);
      cout << "Sent messages to root" << endl;
   }

   cout << "Barrier" << endl;
   MPI_Barrier(MPI_COMM_WORLD);

   cout << "MPI_Waitsome test" << endl;
   if (rank == 0) {
      for (int source = 1; source < totNodes; source++) {
         
         char buf[3][100];
         MPI_Status status[3];
         MPI_Request request[3];
         int indices[3];
         int outcount;
         int receivedCount = 0;
         MPI_Irecv(&buf[0], 100, MPI_UNSIGNED_CHAR, source, 0, MPI_COMM_WORLD, &request[0]);
         MPI_Irecv(&buf[1], 100, MPI_UNSIGNED_CHAR, source, 1, MPI_COMM_WORLD, &request[1]);
         MPI_Irecv(&buf[2], 100, MPI_UNSIGNED_CHAR, source, 2, MPI_COMM_WORLD, &request[2]);
         do {
            MPI_Waitsome(3, request, &outcount, indices, status);
            for (int j = 0; j < outcount; j++) {
               cout << "Index: " << indices[j] << "  -  " << buf[indices[j]] << endl;
            }
            cout << "Break in receive" << endl;
            receivedCount += outcount;
            llamaos::api::sleep(4);
         } while (receivedCount < 3);
      }
   } else {
      char buf[100];
      sprintf(buf, "Received waitsome message 0 from node %d", rank);
      MPI_Send(&buf, 100, MPI_UNSIGNED_CHAR, 0, 0, MPI_COMM_WORLD);
      llamaos::api::sleep(1);
      sprintf(buf, "Received waitsome message 1 from node %d", rank);
      MPI_Send(&buf, 100, MPI_UNSIGNED_CHAR, 0, 1, MPI_COMM_WORLD);
      sprintf(buf, "Received waitsome message 2 from node %d", rank);
      MPI_Send(&buf, 100, MPI_UNSIGNED_CHAR, 0, 2, MPI_COMM_WORLD);
      cout << "Sent messages to root" << endl;
   }
   
   cout << "Barrier" << endl;
   MPI_Barrier(MPI_COMM_WORLD);
   
   cout << "MPI_Test test" << endl;
   if (rank == 0) {
      for (int source = 1; source < totNodes; source++) {
         char buf[100];
         MPI_Status status;
         MPI_Request request;
         int flag;
         MPI_Irecv(&buf, 100, MPI_UNSIGNED_CHAR, source, 0, MPI_COMM_WORLD, &request);
         cout << "Request ID: " << request << endl;
         do {
            MPI_Test(&request, &flag, &status);
         } while(!flag);
         cout << buf << endl;
      }
   } else {
      llamaos::api::sleep(4);
      char buf[100];
      sprintf(buf, "Received test message from node %d", rank);
      MPI_Request request;
      MPI_Isend(&buf, 100, MPI_UNSIGNED_CHAR, 0, 0, MPI_COMM_WORLD, &request);
      MPI_Request_free(&request);
      cout << "Sent message to root" << endl;
   }

   cout << "Barrier" << endl;
   MPI_Barrier(MPI_COMM_WORLD);
   
   cout << "MPI_Testall test" << endl;
   if (rank == 0) {
      for (int source = 1; source < totNodes; source++) {
         char buf[2][100];
         MPI_Status status[2];
         MPI_Request request[2];
         MPI_Irecv(&buf[0], 100, MPI_UNSIGNED_CHAR, source, 1, MPI_COMM_WORLD, &request[0]);
         MPI_Irecv(&buf[1], 100, MPI_UNSIGNED_CHAR, source, 0, MPI_COMM_WORLD, &request[1]);
         cout << "Request0 ID: " << request[0] << endl;
         cout << "Request1 ID: " << request[1] << endl;
         int flag;
         do {
            MPI_Testall(2, request, &flag, status);
         } while(!flag);
         cout << buf[0] << endl;
         cout << buf[1] << endl;
      }
   } else {
      char buf[100];
      sprintf(buf, "Received testall message 0 from node %d", rank);
      MPI_Send(&buf, 100, MPI_UNSIGNED_CHAR, 0, 0, MPI_COMM_WORLD);
      llamaos::api::sleep(4);
      sprintf(buf, "Received testall message 1 from node %d", rank);
      MPI_Send(&buf, 100, MPI_UNSIGNED_CHAR, 0, 1, MPI_COMM_WORLD);
      cout << "Sent messages to root" << endl;
   }
   
   cout << "Barrier" << endl;
   MPI_Barrier(MPI_COMM_WORLD);

   cout << "MPI_Waitany test" << endl;
   if (rank == 0) {
      for (int source = 1; source < totNodes; source++) {
         char buf[2][100];
         MPI_Status status;
         MPI_Request request[2];
         MPI_Irecv(&buf[0], 100, MPI_UNSIGNED_CHAR, source, 1, MPI_COMM_WORLD, &request[0]);
         MPI_Irecv(&buf[1], 100, MPI_UNSIGNED_CHAR, source, 0, MPI_COMM_WORLD, &request[1]);
         int index;
         for (int i = 0; i < 2; i++) {
            int flag;
            cout << "Request0 ID: " << request[0] << endl;
            cout << "Request1 ID: " << request[1] << endl;
            do {
               MPI_Testany(2, request, &index, &flag, &status);
            } while(!flag);
            cout << "Index: " << index << "  -  " << buf[index] << endl;
         }
      }
   } else {
      char buf[100];
      sprintf(buf, "Received testany message 0 from node %d", rank);
      MPI_Send(&buf, 100, MPI_UNSIGNED_CHAR, 0, 0, MPI_COMM_WORLD);
      llamaos::api::sleep(4);
      sprintf(buf, "Received testany message 1 from node %d", rank);
      MPI_Send(&buf, 100, MPI_UNSIGNED_CHAR, 0, 1, MPI_COMM_WORLD);
      cout << "Sent messages to root" << endl;
   }
   
   cout << "Barrier" << endl;
   MPI_Barrier(MPI_COMM_WORLD);

   cout << "MPI_Testsome test" << endl;
   if (rank == 0) {
      for (int source = 1; source < totNodes; source++) {
         char buf[3][100];
         MPI_Status status[3];
         MPI_Request request[3];
         int indices[3];
         int outcount;
         int receivedCount = 0;
         MPI_Irecv(&buf[0], 100, MPI_UNSIGNED_CHAR, source, 0, MPI_COMM_WORLD, &request[0]);
         MPI_Irecv(&buf[1], 100, MPI_UNSIGNED_CHAR, source, 1, MPI_COMM_WORLD, &request[1]);
         MPI_Irecv(&buf[2], 100, MPI_UNSIGNED_CHAR, source, 2, MPI_COMM_WORLD, &request[2]);
         do {
            MPI_Testsome(3, request, &outcount, indices, status);
            for (int j = 0; j < outcount; j++) {
               cout << "Index: " << indices[j] << "  -  " << buf[indices[j]] << endl;
            }
            if (outcount > 0) {
               cout << "Break in receive" << endl;
               receivedCount += outcount;
               llamaos::api::sleep(4);
            }
         } while (receivedCount < 3);
      }
   } else {
      char buf[100];
      sprintf(buf, "Received testsome message 0 from node %d", rank);
      MPI_Send(&buf, 100, MPI_UNSIGNED_CHAR, 0, 0, MPI_COMM_WORLD);
      llamaos::api::sleep(1);
      sprintf(buf, "Received testsome message 1 from node %d", rank);
      MPI_Send(&buf, 100, MPI_UNSIGNED_CHAR, 0, 1, MPI_COMM_WORLD);
      sprintf(buf, "Received testsome message 2 from node %d", rank);
      MPI_Send(&buf, 100, MPI_UNSIGNED_CHAR, 0, 2, MPI_COMM_WORLD);
      cout << "Sent messages to root" << endl;
   }
}

void commTest() { // for 3 or more
   cout << "Starting comm test" << endl;
   cout << "Duplicating world comm" << endl;
   int rank, totNodes;
   MPI_Comm MPI_COMM_COPY_WORLD;
   MPI_Comm_dup(MPI_COMM_WORLD, &MPI_COMM_COPY_WORLD);
   MPI_Comm_rank(MPI_COMM_COPY_WORLD, &rank);
   MPI_Comm_size(MPI_COMM_COPY_WORLD, &totNodes);
   cout << "New duplicate comm with ID " << MPI_COMM_COPY_WORLD << " size " << totNodes;
   cout << " and rank " << rank << endl;
   cout << "Dual send test" << endl;
   if (rank == 0) {
      char buf;
      MPI_Recv(&buf, 1, MPI_CHAR, 1, 0, MPI_COMM_COPY_WORLD, 0);
      cout << "Received char: " << buf << endl;
      MPI_Recv(&buf, 1, MPI_CHAR, 1, 0, MPI_COMM_WORLD, 0);
      cout << "Received char: " << buf << endl;
   } else if (rank == 1) {
      char buf = 'A';
      MPI_Send(&buf, 1, MPI_CHAR, 0, 0, MPI_COMM_WORLD);
      buf = 'B';
      MPI_Send(&buf, 1, MPI_CHAR, 0, 0, MPI_COMM_COPY_WORLD);
   }

   cout << "Testing comm create" << endl;
   MPI_Group MPI_GROUP_WORLD, MPI_GROUP01, MPI_GROUP12, MPI_GROUP0, MPI_GROUP21;
   MPI_Comm MPI_COMM01, MPI_COMM12, MPI_COMM0, MPI_COMM21, MPI_COMM12b;
   MPI_Comm_group(MPI_COMM_WORLD, &MPI_GROUP_WORLD);
   int groupIncl01[2] = {0,1};
   MPI_Group_incl(MPI_GROUP_WORLD, 2, groupIncl01, &MPI_GROUP01);
   MPI_Comm_create(MPI_COMM_WORLD, MPI_GROUP01, &MPI_COMM01);
   cout << "Comm01 = " << MPI_COMM01 << endl;
   int groupIncl12[2] = {1,2};
   MPI_Group_incl(MPI_GROUP_WORLD, 2, groupIncl12, &MPI_GROUP12);
   MPI_Comm_create(MPI_COMM_WORLD, MPI_GROUP12, &MPI_COMM12);
   cout << "Comm12 = " << MPI_COMM12 << endl;
   int groupIncl0[1] = {0};
   MPI_Group_incl(MPI_GROUP_WORLD, 1, groupIncl0, &MPI_GROUP0);
   MPI_Comm_create(MPI_COMM_WORLD, MPI_GROUP0, &MPI_COMM0);
   cout << "Comm0 = " << MPI_COMM0 << endl;
   if (MPI_COMM01 != MPI_COMM_NULL) {
      int myVal = (rank+3);
      cout << "Comm01 - My value: " << myVal;
      MPI_Allreduce(&myVal, &myVal, 1, MPI_INT, MPI_SUM, MPI_COMM01);
      cout << "     My sum: " << myVal << endl;
   }
   if (MPI_COMM12 != MPI_COMM_NULL) {
      int myVal = (rank+3);
      cout << "Comm12 - My value: " << myVal;
      MPI_Allreduce(&myVal, &myVal, 1, MPI_INT, MPI_SUM, MPI_COMM12);
      cout << "     My sum: " << myVal << endl;
   }
   if (MPI_COMM0 != MPI_COMM_NULL) {
      int myVal = (rank+3);
      cout << "Comm0 - My value: " << myVal;
      MPI_Allreduce(&myVal, &myVal, 1, MPI_INT, MPI_SUM, MPI_COMM0);
      cout << "     My sum: " << myVal << endl;
   }

   cout << "Comparing comms" << endl;
   MPI_Comm_create(MPI_COMM_WORLD, MPI_GROUP12, &MPI_COMM12b);
   cout << "Comm12b = " << MPI_COMM12b << endl;
   int groupIncl21[2] = {2,1};
   MPI_Group_incl(MPI_GROUP_WORLD, 2, groupIncl21, &MPI_GROUP21);
   MPI_Comm_create(MPI_COMM_WORLD, MPI_GROUP21, &MPI_COMM21);
   cout << "Comm21 = " << MPI_COMM21 << endl;
   if (rank == 1) {
      int res;
      MPI_Comm_compare(MPI_COMM12, MPI_COMM12, &res);
      cout << "Identical result: " << res << endl;
      MPI_Comm_compare(MPI_COMM12, MPI_COMM12b, &res);
      cout << "Congruent result: " << res << endl;
      MPI_Comm_compare(MPI_COMM12, MPI_COMM21, &res);
      cout << "Similar result: " << res << endl;
      MPI_Comm_compare(MPI_COMM12, MPI_COMM01, &res);
      cout << "Different result: " << res << endl;
   }

   cout << "Testing comm split" << endl;
   MPI_Comm MPI_COMM_S;
   MPI_Comm_split(MPI_COMM_WORLD, rank%2, -rank, &MPI_COMM_S);
   int rank2, totNodes2;
   MPI_Comm_rank(MPI_COMM_S, &rank2);
   MPI_Comm_size(MPI_COMM_S, &totNodes2);
   cout << "New split comm with ID " << MPI_COMM_S << " size " << totNodes2;
   cout << " and rank " << rank2 << endl;
   int myVal = ((rank+1)*3);
   cout << "CommS - My value: " << myVal;
   MPI_Allreduce(&myVal, &myVal, 1, MPI_INT, MPI_PROD, MPI_COMM_S);
   cout << "     My product: " << myVal << endl;

   cout << "Running comm destructors...";
   MPI_Comm_free(&MPI_COMM_COPY_WORLD);
   MPI_Comm_free(&MPI_COMM01);
   MPI_Comm_free(&MPI_COMM12);
   MPI_Comm_free(&MPI_COMM0);
   MPI_Comm_free(&MPI_COMM21);
   MPI_Comm_free(&MPI_COMM12b);
   cout << "DONE" << endl;
}

void groupTest() { // for 3 or more
   cout << "Starting group test" << endl;
   cout << "Running group constructor tests" << endl;
   MPI_Group MPI_GROUP_WORLD;
   int gRank, gSize;
   MPI_Comm_group(MPI_COMM_WORLD, &MPI_GROUP_WORLD);
   MPI_Group_rank(MPI_GROUP_WORLD, &gRank);
   MPI_Group_size(MPI_GROUP_WORLD, &gSize);
   cout << "In world group " << MPI_GROUP_WORLD << " of size " << gSize << " with rank " << gRank << endl;
   
   MPI_Group MPI_NEW_GROUP1;
   int groupInclList[2] = {2,1};
   MPI_Group_incl(MPI_GROUP_WORLD, 2, groupInclList, &MPI_NEW_GROUP1);
   MPI_Group_rank(MPI_NEW_GROUP1, &gRank);
   MPI_Group_size(MPI_NEW_GROUP1, &gSize);
   cout << "In incl group " << MPI_NEW_GROUP1 << " of size " << gSize << " with rank " << gRank << endl;

   MPI_Group MPI_NEW_GROUP2;
   int groupExclList[1] = {1};
   MPI_Group_excl(MPI_GROUP_WORLD, 1, groupExclList, &MPI_NEW_GROUP2);
   MPI_Group_rank(MPI_NEW_GROUP2, &gRank);
   MPI_Group_size(MPI_NEW_GROUP2, &gSize);
   cout << "In excl group " << MPI_NEW_GROUP2 << " of size " << gSize << " with rank " << gRank << endl;

   MPI_Group MPI_NEW_GROUP3;
   MPI_Group_union(MPI_NEW_GROUP1, MPI_NEW_GROUP2, &MPI_NEW_GROUP3);
   MPI_Group_rank(MPI_NEW_GROUP3, &gRank);
   MPI_Group_size(MPI_NEW_GROUP3, &gSize);
   cout << "In union group " << MPI_NEW_GROUP3 << " of size " << gSize << " with rank " << gRank << endl;

   MPI_Group MPI_NEW_GROUP4;
   MPI_Group_intersection(MPI_NEW_GROUP1, MPI_NEW_GROUP2, &MPI_NEW_GROUP4);
   MPI_Group_rank(MPI_NEW_GROUP4, &gRank);
   MPI_Group_size(MPI_NEW_GROUP4, &gSize);
   cout << "In intersection group " << MPI_NEW_GROUP4 << " of size " << gSize << " with rank " << gRank << endl;

   MPI_Group MPI_NEW_GROUP5;
   MPI_Group_difference(MPI_NEW_GROUP1, MPI_NEW_GROUP2, &MPI_NEW_GROUP5);
   MPI_Group_rank(MPI_NEW_GROUP5, &gRank);
   MPI_Group_size(MPI_NEW_GROUP5, &gSize);
   cout << "In difference group " << MPI_NEW_GROUP5 << " of size " << gSize << " with rank " << gRank << endl;

   cout << "Running group accessor tests" << endl;
   int groupRanks1[3] = {2,0,1};
   int groupRanks2[3];
   MPI_Group_translate_ranks(MPI_NEW_GROUP3, 3, groupRanks1, MPI_NEW_GROUP5, groupRanks2);
   cout << "Translation: ";
   for (int i = 0; i < 3; i++) {
      cout << "(" << groupRanks1[i] << "-->" << groupRanks2[i] << ")";
   }
   cout << endl;

   MPI_Group MPI_NEW_GROUP6;
   int groupInclList2[2] = {2,1};
   MPI_Group_incl(MPI_GROUP_WORLD, 2, groupInclList2, &MPI_NEW_GROUP6);
   MPI_Group MPI_NEW_GROUP7;
   int groupInclList3[2] = {1,2};
   MPI_Group_incl(MPI_GROUP_WORLD, 2, groupInclList3, &MPI_NEW_GROUP7);
   int resSame, resSim, resDif;
   MPI_Group_compare(MPI_NEW_GROUP1, MPI_NEW_GROUP6, &resSame);
   cout << "Same result: " << resSame << endl;
   MPI_Group_compare(MPI_NEW_GROUP1, MPI_NEW_GROUP7, &resSim);
   cout << "Similar result: " << resSim << endl;
   MPI_Group_compare(MPI_NEW_GROUP1, MPI_NEW_GROUP5, &resDif);
   cout << "Different result: " << resDif << endl;

   cout << "Running group destructors...";
   MPI_Group_free(&MPI_NEW_GROUP1);
   MPI_Group_free(&MPI_NEW_GROUP2);
   MPI_Group_free(&MPI_NEW_GROUP3);
   MPI_Group_free(&MPI_NEW_GROUP4);
   MPI_Group_free(&MPI_NEW_GROUP5);
   MPI_Group_free(&MPI_NEW_GROUP6);
   MPI_Group_free(&MPI_NEW_GROUP7);
   MPI_Group_free(&MPI_GROUP_WORLD);
   cout << "DONE" << endl;
}

void duoTest() { // for 2
   int rank, totNodes;
   MPI_Comm_rank(MPI_COMM_WORLD, &rank);
   MPI_Comm_size(MPI_COMM_WORLD, &totNodes);

   if (rank >= 2) {return;}
   cout << "Starting duo test" << endl;

   cout << "Pt2pt test..." << endl;
   if (rank == 0) {
      llamaos::api::sleep(5);
      for (int source = 1; source < totNodes; source++) {
         char buf[100];
         MPI_Status status;
         MPI_Recv(&buf, 100, MPI_UNSIGNED_CHAR, source, 0, MPI_COMM_WORLD, &status);
         cout << buf << endl;
      }
   } else {
      char buf[100];
      sprintf(buf, "Received message from node %d", rank);
      MPI_Send(&buf, 100, MPI_UNSIGNED_CHAR, 0, 0, MPI_COMM_WORLD);
      cout << "Sent message to root" << endl;
   }

   cout << "Broadcast test" << endl;
   int rootRank = rank;
   MPI_Bcast(&rootRank, 4, MPI_UNSIGNED_CHAR, 1, MPI_COMM_WORLD);
   cout << "Root Rank: " << rootRank << endl;

   cout << "Barrier test" << endl;
   MPI_Barrier(MPI_COMM_WORLD);

   cout << "Scatter/Gather test" << endl;
   int intBuf[8] = {0,0,0,0,0,0,0,0};
   if (rank == 0) {
      for (int i = 0; i < 8; i++) {
         intBuf[i] = i;
      }
   }
   int subIntBuf[4];
   MPI_Scatter(intBuf, 4, MPI_INT, subIntBuf, 4, MPI_INT, 0, MPI_COMM_WORLD);
   for (int i = 0; i < 4; i++) {
      subIntBuf[i] += 1000;
   }
   MPI_Gather(subIntBuf, 4, MPI_INT, intBuf, 4, MPI_INT, 0, MPI_COMM_WORLD);
   cout << "Result is:" << endl;
   for (int i = 0; i < 8; i++) {
      cout << intBuf[i] << " ";
   } 
   cout << endl;

   cout << "Allgather test" << endl;
   MPI_Allgather(subIntBuf, 4, MPI_INT, intBuf, 4, MPI_INT, MPI_COMM_WORLD);
   cout << "Result is:" << endl;
   for (int i = 0; i < 8; i++) {
      cout << intBuf[i] << " ";
   } 
   cout << endl;

   cout << "Alltoall test" << endl;
   int ataBuf[8];
   for (int i = 0; i < 8; i++) {
      intBuf[i] = i + (10*rank);
      ataBuf[i] = -1;
   }
   MPI_Alltoall(intBuf, 4, MPI_INT, ataBuf, 4, MPI_INT, MPI_COMM_WORLD);
   cout << "Result is:" << endl;
   for (int i = 0; i < 8; i++) {
      cout << ataBuf[i] << " ";
   } 
   cout << endl;

   cout << "Reduce tests" << endl;
   cout << "Using integer values: ";
   short rValue[8];
   short subR[4];
   short resR[4];
   for (int i = 0; i < 8; i++) {
      rValue[i] = ((short)((i+1)*0xc8527a969e6d7b9e))%256;
      cout << rValue[i] << " ";
   }
   cout << endl;
   MPI_Scatter(rValue, 4, MPI_SHORT, subR, 4, MPI_SHORT, 0, MPI_COMM_WORLD);
   MPI_Reduce(subR, resR, 4, MPI_SHORT, MPI_MAX, 0, MPI_COMM_WORLD);
   cout << "MAX Results: ";
   for (int i = 0; i < 4; i++) {cout << resR[i] << " ";}
   cout << endl;
   MPI_Reduce(subR, resR, 4, MPI_SHORT, MPI_MIN, 0, MPI_COMM_WORLD);
   cout << "MIN Results: ";
   for (int i = 0; i < 4; i++) {cout << resR[i] << " ";}
   cout << endl;
   MPI_Reduce(subR, resR, 4, MPI_SHORT, MPI_SUM, 0, MPI_COMM_WORLD);
   cout << "SUM Results: ";
   for (int i = 0; i < 4; i++) {cout << resR[i] << " ";}
   cout << endl;
   MPI_Reduce(subR, resR, 4, MPI_SHORT, MPI_PROD, 0, MPI_COMM_WORLD);
   cout << "PROD Results: ";
   for (int i = 0; i < 4; i++) {cout << resR[i] << " ";}
   cout << endl;

   cout << "Using unsigned integer values: ";
   unsigned char ruValue[8];
   unsigned char subRu[4];
   unsigned char resRu[4];
   for (int i = 0; i < 8; i++) {
      ruValue[i] = ((unsigned char)((i+1+8)*0xc8527a969e6d7b9e))%256;
      cout << (unsigned int)ruValue[i] << " ";
   }
   cout << endl;
   MPI_Scatter(ruValue, 4, MPI_BYTE, subRu, 4, MPI_SHORT, 0, MPI_COMM_WORLD);
   MPI_Reduce(subRu, resRu, 4, MPI_BYTE, MPI_BAND, 0, MPI_COMM_WORLD);
   cout << "BAND Results: ";
   for (int i = 0; i < 4; i++) {cout << (unsigned int)resRu[i] << " ";}
   cout << endl;
   MPI_Reduce(subRu, resRu, 4, MPI_BYTE, MPI_BOR, 0, MPI_COMM_WORLD);
   cout << "BOR Results: ";
   for (int i = 0; i < 4; i++) {cout << (unsigned int)resRu[i] << " ";}
   cout << endl;
   MPI_Reduce(subRu, resRu, 4, MPI_BYTE, MPI_BXOR, 0, MPI_COMM_WORLD);
   cout << "BXOR Results: ";
   for (int i = 0; i < 4; i++) {cout << (unsigned int)resRu[i] << " ";}
   cout << endl;

   cout << "Using logical values: ";
   int rlValue[8] = {0, 0, 1, 16, 0, -122, 0, 1777777};
   int subRl[4];
   int resRl[4];
   for (int i = 0; i < 8; i++) {
      cout << rlValue[i] << " ";
   }
   cout << endl;
   MPI_Scatter(rlValue, 4, MPI_INT, subRl, 4, MPI_INT, 0, MPI_COMM_WORLD);
   MPI_Reduce(subRl, resRl, 4, MPI_INT, MPI_LAND, 0, MPI_COMM_WORLD);
   cout << "LAND Results: ";
   for (int i = 0; i < 4; i++) {cout << resRl[i] << " ";}
   cout << endl;
   MPI_Reduce(subRl, resRl, 4, MPI_INT, MPI_LOR, 0, MPI_COMM_WORLD);
   cout << "LOR Results: ";
   for (int i = 0; i < 4; i++) {cout << resRl[i] << " ";}
   cout << endl;
   MPI_Reduce(subRl, resRl, 4, MPI_INT, MPI_LXOR, 0, MPI_COMM_WORLD);
   cout << "LXOR Results: ";
   for (int i = 0; i < 4; i++) {cout << resRl[i] << " ";}
   cout << endl;

   struct resPair_T {
      short value;
      int index;
   };
   cout << "Using integer values: ";
   resPair_T rpValue[8];
   resPair_T subRp[4];
   resPair_T resRp[4];
   for (int i = 0; i < 8; i++) {
      rpValue[i].value = ((short)((i+1+(8*3))*0xc8527a969e6d7b9e))%256;
      rpValue[i].index = (((int)((i+1+(8*4))*0xc8527a969e6d7b9e))%128)+127;
      cout << "(" << rpValue[i].value << "," << rpValue[i].index << ") ";
   }
   cout << endl;
   MPI_Scatter(rpValue, 4, MPI_SHORT_INT, subRp, 4, MPI_SHORT_INT, 0, MPI_COMM_WORLD);
   MPI_Reduce(subRp, resRp, 4, MPI_SHORT_INT, MPI_MAXLOC, 0, MPI_COMM_WORLD);
   cout << "MAXLOC Results: ";
   for (int i = 0; i < 4; i++) {cout << "(" << resRp[i].value << "," << resRp[i].index << ") ";}
   cout << endl;
   MPI_Reduce(subRp, resRp, 4, MPI_SHORT_INT, MPI_MINLOC, 0, MPI_COMM_WORLD);
   cout << "MINLOC Results: ";
   for (int i = 0; i < 4; i++) {cout << "(" << resRp[i].value << "," << resRp[i].index << ") ";}
   cout << endl;

   cout << "Allreduce tests" << endl;
   cout << "Using integer values: ";
   for (int i = 0; i < 8; i++) {
      rValue[i] = ((short)((i+1+(8*5))*0xc8527a969e6d7b9e))%256;
      cout << rValue[i] << " ";
   }
   cout << endl;
   MPI_Scatter(rValue, 4, MPI_SHORT, subR, 4, MPI_SHORT, 0, MPI_COMM_WORLD);
   MPI_Allreduce(subR, resR, 4, MPI_SHORT, MPI_MAX, MPI_COMM_WORLD);
   cout << "MAX Results: ";
   for (int i = 0; i < 4; i++) {cout << resR[i] << " ";}
   cout << endl;
   MPI_Allreduce(subR, resR, 4, MPI_SHORT, MPI_MIN, MPI_COMM_WORLD);
   cout << "MIN Results: ";
   for (int i = 0; i < 4; i++) {cout << resR[i] << " ";}
   cout << endl;
}

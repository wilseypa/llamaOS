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

#include <iRxBuffer.h>
#include <string.h>
#include <cstdlib>

using namespace std;

std::list<MpiRxMessage_T>::iterator iRxBuffer::getMessage(int source, int tag) {
   for (std::list<MpiRxMessage_T>::iterator it = buffer.begin(); it != buffer.end(); it++) {
      if (((it->source == source) || (source == MPI_ANY_SOURCE)) &&
               ((it->tag == tag) || (tag == MPI_ANY_TAG))) {
         return it;
      }
   }
   return buffer.end();
}

std::list<MpiRxMessage_T>::iterator iRxBuffer::getInProgressMessage(int source, int tag) {
   for (std::list<MpiRxMessage_T>::iterator it = buffer.begin(); it != buffer.end(); it++) {
      if (((it->source == source) || (source == MPI_ANY_SOURCE)) &&
               ((it->tag == tag) || (tag == MPI_ANY_TAG)) && (it->curSize < it->size)) {
         return it;
      }
   }
   return buffer.end();
}

void iRxBuffer::pushMessage(unsigned char *buf, int size, int source, int tag, int totSize, int part) {
   std::list<MpiRxMessage_T>::iterator it = getInProgressMessage(source, tag);
   unsigned char *dataPt;
   if (it == buffer.end()) { //New message
      dataPt = new unsigned char[totSize];
      MpiRxMessage_T newRxMessage;
      newRxMessage.buf = dataPt;
      newRxMessage.size = totSize;
      newRxMessage.source = source;
      newRxMessage.tag = tag;
      newRxMessage.curSize = size;
      buffer.push_back(newRxMessage);
   } else { //In progress message
      it->curSize += size;
      dataPt = it->buf;
   }
   // Copy over data
   dataPt += part*MAX_MESS_SIZE;
   memcpy(dataPt, buf, size);
}

int iRxBuffer::popMessage(int source, int tag, void *buf, int size, MPI_Status *status) {
   std::list<MpiRxMessage_T>::iterator it = getMessage(source, tag);
   if (it == buffer.end()) {return 0;}

   // Verify length
   if (size < it->size) { // Will not fit in buffer - discard
      free(it->buf);
      buffer.erase(it);
      return 0;
   }

   // Copy data into buffer
   memcpy(buf, it->buf, it->size);

   // Copy data into status
   if (status != MPI_STATUS_IGNORE) {
      status->MPI_SOURCE = it->source;
      status->MPI_TAG = it->tag;
      status->MPI_ERROR = MPI_SUCCESS;
      status->size = it->size;
   }

   // Clean up list
   delete[] it->buf;
   buffer.erase(it);
   return it->curSize;
}

bool iRxBuffer::probeMessage(int source, int tag, MPI_Status *status) {
   std::list<MpiRxMessage_T>::iterator it = getMessage(source, tag);
   if (it == buffer.end()) {return false;}

   // Copy data into status
   if (status != MPI_STATUS_IGNORE) {
      status->MPI_SOURCE = it->source;
      status->MPI_TAG = it->tag;
      status->MPI_ERROR = MPI_SUCCESS;
      status->size = it->size;
   }
   return true;
}

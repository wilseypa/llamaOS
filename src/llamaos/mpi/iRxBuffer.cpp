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

void iRxBuffer::pushMessage(unsigned char *buf, int size, int source, int tag) {
   unsigned char *newData = (unsigned char*)malloc(size);
   memcpy(newData, buf, size);
   MpiRxMessage_T newRxMessage;
   newRxMessage.buf = newData;
   newRxMessage.size = size;
   newRxMessage.source = source;
   newRxMessage.tag = tag;
   buffer.push_back(newRxMessage);
}

bool iRxBuffer::popMessage(int source, int tag, void *buf, int size, MPI_Status *status) {
   for (std::list<MpiRxMessage_T>::iterator it = buffer.begin(); it != buffer.end(); it++) {
      if ((it->source == source || static_cast<uint32_t>(source) == MPI_ANY_SOURCE) &&
               (it->tag == tag || static_cast<uint32_t>(tag) == MPI_ANY_TAG)) {
         // Verify length
         if (size < it->size) { // Will not fit in buffer - discard
            free(it->buf);
            buffer.erase(it);
            return false;
         }

         // Copy data into buffer
         memcpy(buf, it->buf, it->size);

         // Copy data into status
         if (status != 0) {
            status->MPI_SOURCE = it->source;
            status->MPI_TAG = it->tag;
            status->MPI_ERROR = MPI_SUCCESS;
         }

         // Clean up list
         free(it->buf);
         buffer.erase(it);
         return true;
      }
   }
   return false;
}

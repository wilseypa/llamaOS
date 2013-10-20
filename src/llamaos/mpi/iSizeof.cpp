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

#include <iGlobals.h>

int iSizeof(MPI_Datatype type) {
   switch (type) {
      case MPI_CHAR:		return sizeof(MPI_CHAR_T);
      case MPI_BYTE:		return sizeof(MPI_BYTE_T);
      case MPI_SHORT:	 	return sizeof(MPI_SHORT_T);
      case MPI_INT:		return sizeof(MPI_INT_T);
      case MPI_LONG:		return sizeof(MPI_LONG_T);
      case MPI_FLOAT:		return sizeof(MPI_FLOAT_T);
      case MPI_DOUBLE:		return sizeof(MPI_DOUBLE_T);
      case MPI_UNSIGNED_CHAR:	return sizeof(MPI_UNSIGNED_CHAR_T);
      case MPI_UNSIGNED_SHORT:	return sizeof(MPI_UNSIGNED_SHORT_T);
      case MPI_UNSIGNED:	return sizeof(MPI_UNSIGNED_T);
      case MPI_UNSIGNED_LONG:	return sizeof(MPI_UNSIGNED_LONG_T);
      case MPI_LONG_DOUBLE:	return sizeof(MPI_LONG_DOUBLE_T);
      case MPI_LONG_LONG_INT:	return sizeof(MPI_LONG_LONG_INT_T);

      case MPI_FLOAT_INT:	return sizeof(MPI_FLOAT_INT_T);
      case MPI_LONG_INT:	return sizeof(MPI_LONG_INT_T);
      case MPI_DOUBLE_INT:	return sizeof(MPI_DOUBLE_INT_T);
      case MPI_SHORT_INT:	return sizeof(MPI_SHORT_INT_T);
      case MPI_2INT:		return sizeof(MPI_2INT_T);
      case MPI_LONG_DOUBLE_INT:	return sizeof(MPI_LONG_DOUBLE_INT_T);
      
      case MPI_CHARACTER:	return sizeof(MPI_CHARACTER_T);
      case MPI_INTEGER:	return sizeof(MPI_INTEGER_T);
      case MPI_INTEGER1:	return sizeof(MPI_INTEGER1_T);
      case MPI_INTEGER2:	return sizeof(MPI_INTEGER2_T);
      case MPI_INTEGER4:	return sizeof(MPI_INTEGER4_T);
      case MPI_REAL:	return sizeof(MPI_REAL_T);
      case MPI_DOUBLE_PRECISION:	return sizeof(MPI_DOUBLE_PRECISION_T);
      case MPI_COMPLEX:	return sizeof(MPI_COMPLEX_T);
      case MPI_DOUBLE_COMPLEX:	return sizeof(MPI_DOUBLE_COMPLEX_T);
      case MPI_LOGICAL:	return sizeof(MPI_LOGICAL_T);

      case MPI_DATATYPE_CUSTOM1: return 2*sizeof(MPI_DOUBLE_T);
	
      default:			return 0;
   }
}

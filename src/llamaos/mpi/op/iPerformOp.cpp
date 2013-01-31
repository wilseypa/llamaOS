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
#include <op/iPerformOpMax.h>
#include <op/iPerformOpMin.h>
#include <op/iPerformOpSum.h>
#include <op/iPerformOpProd.h>
#include <op/iPerformOpLand.h>
#include <op/iPerformOpBand.h>
#include <op/iPerformOpLor.h>
#include <op/iPerformOpBor.h>
#include <op/iPerformOpLxor.h>
#include <op/iPerformOpBxor.h>
#include <op/iPerformOpMaxloc.h>
#include <op/iPerformOpMinloc.h>

int iPerformOp(void *runningTotal, void *newValue, int count, MPI_Datatype type, MPI_Op op) {
   switch (type) {
      case MPI_CHAR:
         switch (op) {
            case MPI_MAX:	return    iPerformOpMax<MPI_CHAR_T>(runningTotal, newValue, count);
            case MPI_MIN:	return    iPerformOpMin<MPI_CHAR_T>(runningTotal, newValue, count);
            case MPI_SUM:	return    iPerformOpSum<MPI_CHAR_T>(runningTotal, newValue, count);
            case MPI_PROD:	return   iPerformOpProd<MPI_CHAR_T>(runningTotal, newValue, count);
            case MPI_LAND:	return   iPerformOpLand<MPI_CHAR_T>(runningTotal, newValue, count);
            case MPI_BAND:	return   iPerformOpBand<MPI_CHAR_T>(runningTotal, newValue, count);
            case MPI_LOR:	return    iPerformOpLor<MPI_CHAR_T>(runningTotal, newValue, count);
            case MPI_BOR:	return    iPerformOpBor<MPI_CHAR_T>(runningTotal, newValue, count);
            case MPI_LXOR:	return   iPerformOpLxor<MPI_CHAR_T>(runningTotal, newValue, count);
            case MPI_BXOR:	return   iPerformOpBxor<MPI_CHAR_T>(runningTotal, newValue, count);
            default: return -1;
         }
      case MPI_BYTE:
         switch (op) {
            case MPI_MAX:	return    iPerformOpMax<MPI_BYTE_T>(runningTotal, newValue, count);
            case MPI_MIN:	return    iPerformOpMin<MPI_BYTE_T>(runningTotal, newValue, count);
            case MPI_SUM:	return    iPerformOpSum<MPI_BYTE_T>(runningTotal, newValue, count);
            case MPI_PROD:	return   iPerformOpProd<MPI_BYTE_T>(runningTotal, newValue, count);
            case MPI_LAND:	return   iPerformOpLand<MPI_BYTE_T>(runningTotal, newValue, count);
            case MPI_BAND:	return   iPerformOpBand<MPI_BYTE_T>(runningTotal, newValue, count);
            case MPI_LOR:	return    iPerformOpLor<MPI_BYTE_T>(runningTotal, newValue, count);
            case MPI_BOR:	return    iPerformOpBor<MPI_BYTE_T>(runningTotal, newValue, count);
            case MPI_LXOR:	return   iPerformOpLxor<MPI_BYTE_T>(runningTotal, newValue, count);
            case MPI_BXOR:	return   iPerformOpBxor<MPI_BYTE_T>(runningTotal, newValue, count);
            default: return -1;
         }
      case MPI_SHORT:
         switch (op) {
            case MPI_MAX:	return    iPerformOpMax<MPI_SHORT_T>(runningTotal, newValue, count);
            case MPI_MIN:	return    iPerformOpMin<MPI_SHORT_T>(runningTotal, newValue, count);
            case MPI_SUM:	return    iPerformOpSum<MPI_SHORT_T>(runningTotal, newValue, count);
            case MPI_PROD:	return   iPerformOpProd<MPI_SHORT_T>(runningTotal, newValue, count);
            case MPI_LAND:	return   iPerformOpLand<MPI_SHORT_T>(runningTotal, newValue, count);
            case MPI_BAND:	return   iPerformOpBand<MPI_SHORT_T>(runningTotal, newValue, count);
            case MPI_LOR:	return    iPerformOpLor<MPI_SHORT_T>(runningTotal, newValue, count);
            case MPI_BOR:	return    iPerformOpBor<MPI_SHORT_T>(runningTotal, newValue, count);
            case MPI_LXOR:	return   iPerformOpLxor<MPI_SHORT_T>(runningTotal, newValue, count);
            case MPI_BXOR:	return   iPerformOpBxor<MPI_SHORT_T>(runningTotal, newValue, count);
            default: return -1;
         }
      case MPI_INT:
         switch (op) {
            case MPI_MAX:	return    iPerformOpMax<MPI_INT_T>(runningTotal, newValue, count);
            case MPI_MIN:	return    iPerformOpMin<MPI_INT_T>(runningTotal, newValue, count);
            case MPI_SUM:	return    iPerformOpSum<MPI_INT_T>(runningTotal, newValue, count);
            case MPI_PROD:	return   iPerformOpProd<MPI_INT_T>(runningTotal, newValue, count);
            case MPI_LAND:	return   iPerformOpLand<MPI_INT_T>(runningTotal, newValue, count);
            case MPI_BAND:	return   iPerformOpBand<MPI_INT_T>(runningTotal, newValue, count);
            case MPI_LOR:	return    iPerformOpLor<MPI_INT_T>(runningTotal, newValue, count);
            case MPI_BOR:	return    iPerformOpBor<MPI_INT_T>(runningTotal, newValue, count);
            case MPI_LXOR:	return   iPerformOpLxor<MPI_INT_T>(runningTotal, newValue, count);
            case MPI_BXOR:	return   iPerformOpBxor<MPI_INT_T>(runningTotal, newValue, count);
            default: return -1;
         }
      case MPI_LONG:
         switch (op) {
            case MPI_MAX:	return    iPerformOpMax<MPI_LONG_T>(runningTotal, newValue, count);
            case MPI_MIN:	return    iPerformOpMin<MPI_LONG_T>(runningTotal, newValue, count);
            case MPI_SUM:	return    iPerformOpSum<MPI_LONG_T>(runningTotal, newValue, count);
            case MPI_PROD:	return   iPerformOpProd<MPI_LONG_T>(runningTotal, newValue, count);
            case MPI_LAND:	return   iPerformOpLand<MPI_LONG_T>(runningTotal, newValue, count);
            case MPI_BAND:	return   iPerformOpBand<MPI_LONG_T>(runningTotal, newValue, count);
            case MPI_LOR:	return    iPerformOpLor<MPI_LONG_T>(runningTotal, newValue, count);
            case MPI_BOR:	return    iPerformOpBor<MPI_LONG_T>(runningTotal, newValue, count);
            case MPI_LXOR:	return   iPerformOpLxor<MPI_LONG_T>(runningTotal, newValue, count);
            case MPI_BXOR:	return   iPerformOpBxor<MPI_LONG_T>(runningTotal, newValue, count);
            default: return -1;
         }
      case MPI_FLOAT:
         switch (op) {
            case MPI_MAX:	return    iPerformOpMax<MPI_FLOAT_T>(runningTotal, newValue, count);
            case MPI_MIN:	return    iPerformOpMin<MPI_FLOAT_T>(runningTotal, newValue, count);
            case MPI_SUM:	return    iPerformOpSum<MPI_FLOAT_T>(runningTotal, newValue, count);
            case MPI_PROD:	return   iPerformOpProd<MPI_FLOAT_T>(runningTotal, newValue, count);
            default: return -1;
         }
      case MPI_DOUBLE:
         switch (op) {
            case MPI_MAX:	return    iPerformOpMax<MPI_DOUBLE_T>(runningTotal, newValue, count);
            case MPI_MIN:	return    iPerformOpMin<MPI_DOUBLE_T>(runningTotal, newValue, count);
            case MPI_SUM:	return    iPerformOpSum<MPI_DOUBLE_T>(runningTotal, newValue, count);
            case MPI_PROD:	return   iPerformOpProd<MPI_DOUBLE_T>(runningTotal, newValue, count);
            default: return -1;
         }
      case MPI_UNSIGNED_CHAR:
         switch (op) {
            case MPI_MAX:	return    iPerformOpMax<MPI_UNSIGNED_CHAR_T>(runningTotal, newValue, count);
            case MPI_MIN:	return    iPerformOpMin<MPI_UNSIGNED_CHAR_T>(runningTotal, newValue, count);
            case MPI_SUM:	return    iPerformOpSum<MPI_UNSIGNED_CHAR_T>(runningTotal, newValue, count);
            case MPI_PROD:	return   iPerformOpProd<MPI_UNSIGNED_CHAR_T>(runningTotal, newValue, count);
            case MPI_LAND:	return   iPerformOpLand<MPI_UNSIGNED_CHAR_T>(runningTotal, newValue, count);
            case MPI_BAND:	return   iPerformOpBand<MPI_UNSIGNED_CHAR_T>(runningTotal, newValue, count);
            case MPI_LOR:	return    iPerformOpLor<MPI_UNSIGNED_CHAR_T>(runningTotal, newValue, count);
            case MPI_BOR:	return    iPerformOpBor<MPI_UNSIGNED_CHAR_T>(runningTotal, newValue, count);
            case MPI_LXOR:	return   iPerformOpLxor<MPI_UNSIGNED_CHAR_T>(runningTotal, newValue, count);
            case MPI_BXOR:	return   iPerformOpBxor<MPI_UNSIGNED_CHAR_T>(runningTotal, newValue, count);
            default: return -1;
         }
      case MPI_UNSIGNED_SHORT:
         switch (op) {
            case MPI_MAX:	return    iPerformOpMax<MPI_UNSIGNED_SHORT_T>(runningTotal, newValue, count);
            case MPI_MIN:	return    iPerformOpMin<MPI_UNSIGNED_SHORT_T>(runningTotal, newValue, count);
            case MPI_SUM:	return    iPerformOpSum<MPI_UNSIGNED_SHORT_T>(runningTotal, newValue, count);
            case MPI_PROD:	return   iPerformOpProd<MPI_UNSIGNED_SHORT_T>(runningTotal, newValue, count);
            case MPI_LAND:	return   iPerformOpLand<MPI_UNSIGNED_SHORT_T>(runningTotal, newValue, count);
            case MPI_BAND:	return   iPerformOpBand<MPI_UNSIGNED_SHORT_T>(runningTotal, newValue, count);
            case MPI_LOR:	return    iPerformOpLor<MPI_UNSIGNED_SHORT_T>(runningTotal, newValue, count);
            case MPI_BOR:	return    iPerformOpBor<MPI_UNSIGNED_SHORT_T>(runningTotal, newValue, count);
            case MPI_LXOR:	return   iPerformOpLxor<MPI_UNSIGNED_SHORT_T>(runningTotal, newValue, count);
            case MPI_BXOR:	return   iPerformOpBxor<MPI_UNSIGNED_SHORT_T>(runningTotal, newValue, count);
            default: return -1;
         }
      case MPI_UNSIGNED:
         switch (op) {
            case MPI_MAX:	return    iPerformOpMax<MPI_UNSIGNED_T>(runningTotal, newValue, count);
            case MPI_MIN:	return    iPerformOpMin<MPI_UNSIGNED_T>(runningTotal, newValue, count);
            case MPI_SUM:	return    iPerformOpSum<MPI_UNSIGNED_T>(runningTotal, newValue, count);
            case MPI_PROD:	return   iPerformOpProd<MPI_UNSIGNED_T>(runningTotal, newValue, count);
            case MPI_LAND:	return   iPerformOpLand<MPI_UNSIGNED_T>(runningTotal, newValue, count);
            case MPI_BAND:	return   iPerformOpBand<MPI_UNSIGNED_T>(runningTotal, newValue, count);
            case MPI_LOR:	return    iPerformOpLor<MPI_UNSIGNED_T>(runningTotal, newValue, count);
            case MPI_BOR:	return    iPerformOpBor<MPI_UNSIGNED_T>(runningTotal, newValue, count);
            case MPI_LXOR:	return   iPerformOpLxor<MPI_UNSIGNED_T>(runningTotal, newValue, count);
            case MPI_BXOR:	return   iPerformOpBxor<MPI_UNSIGNED_T>(runningTotal, newValue, count);
            default: return -1;
         }
      case MPI_UNSIGNED_LONG:
         switch (op) {
            case MPI_MAX:	return    iPerformOpMax<MPI_UNSIGNED_LONG_T>(runningTotal, newValue, count);
            case MPI_MIN:	return    iPerformOpMin<MPI_UNSIGNED_LONG_T>(runningTotal, newValue, count);
            case MPI_SUM:	return    iPerformOpSum<MPI_UNSIGNED_LONG_T>(runningTotal, newValue, count);
            case MPI_PROD:	return   iPerformOpProd<MPI_UNSIGNED_LONG_T>(runningTotal, newValue, count);
            case MPI_LAND:	return   iPerformOpLand<MPI_UNSIGNED_LONG_T>(runningTotal, newValue, count);
            case MPI_BAND:	return   iPerformOpBand<MPI_UNSIGNED_LONG_T>(runningTotal, newValue, count);
            case MPI_LOR:	return    iPerformOpLor<MPI_UNSIGNED_LONG_T>(runningTotal, newValue, count);
            case MPI_BOR:	return    iPerformOpBor<MPI_UNSIGNED_LONG_T>(runningTotal, newValue, count);
            case MPI_LXOR:	return   iPerformOpLxor<MPI_UNSIGNED_LONG_T>(runningTotal, newValue, count);
            case MPI_BXOR:	return   iPerformOpBxor<MPI_UNSIGNED_LONG_T>(runningTotal, newValue, count);
            default: return -1;
         }
      case MPI_LONG_DOUBLE:
         switch (op) {
            case MPI_MAX:	return    iPerformOpMax<MPI_LONG_DOUBLE_T>(runningTotal, newValue, count);
            case MPI_MIN:	return    iPerformOpMin<MPI_LONG_DOUBLE_T>(runningTotal, newValue, count);
            case MPI_SUM:	return    iPerformOpSum<MPI_LONG_DOUBLE_T>(runningTotal, newValue, count);
            case MPI_PROD:	return   iPerformOpProd<MPI_LONG_DOUBLE_T>(runningTotal, newValue, count);
            default: return -1;
         }
      case MPI_LONG_LONG_INT:
         switch (op) {
            case MPI_MAX:	return    iPerformOpMax<MPI_LONG_LONG_INT_T>(runningTotal, newValue, count);
            case MPI_MIN:	return    iPerformOpMin<MPI_LONG_LONG_INT_T>(runningTotal, newValue, count);
            case MPI_SUM:	return    iPerformOpSum<MPI_LONG_LONG_INT_T>(runningTotal, newValue, count);
            case MPI_PROD:	return   iPerformOpProd<MPI_LONG_LONG_INT_T>(runningTotal, newValue, count);
            case MPI_LAND:	return   iPerformOpLand<MPI_LONG_LONG_INT_T>(runningTotal, newValue, count);
            case MPI_BAND:	return   iPerformOpBand<MPI_LONG_LONG_INT_T>(runningTotal, newValue, count);
            case MPI_LOR:	return    iPerformOpLor<MPI_LONG_LONG_INT_T>(runningTotal, newValue, count);
            case MPI_BOR:	return    iPerformOpBor<MPI_LONG_LONG_INT_T>(runningTotal, newValue, count);
            case MPI_LXOR:	return   iPerformOpLxor<MPI_LONG_LONG_INT_T>(runningTotal, newValue, count);
            case MPI_BXOR:	return   iPerformOpBxor<MPI_LONG_LONG_INT_T>(runningTotal, newValue, count);
            default: return -1;
         }

      case MPI_FLOAT_INT:
         switch (op) {
            case MPI_MAXLOC:	return iPerformOpMaxloc<MPI_FLOAT_INT_T>(runningTotal, newValue, count);
            case MPI_MINLOC:	return iPerformOpMinloc<MPI_FLOAT_INT_T>(runningTotal, newValue, count);
            default: return -1;
         }
      case MPI_LONG_INT:
         switch (op) {
            case MPI_MAXLOC:	return iPerformOpMaxloc<MPI_LONG_INT_T>(runningTotal, newValue, count);
            case MPI_MINLOC:	return iPerformOpMinloc<MPI_LONG_INT_T>(runningTotal, newValue, count);
            default: return -1;
         }
      case MPI_DOUBLE_INT:
         switch (op) {
            case MPI_MAXLOC:	return iPerformOpMaxloc<MPI_DOUBLE_INT_T>(runningTotal, newValue, count);
            case MPI_MINLOC:	return iPerformOpMinloc<MPI_DOUBLE_INT_T>(runningTotal, newValue, count);
            default: return -1;
         }
      case MPI_SHORT_INT:
         switch (op) {
            case MPI_MAXLOC:	return iPerformOpMaxloc<MPI_SHORT_INT_T>(runningTotal, newValue, count);
            case MPI_MINLOC:	return iPerformOpMinloc<MPI_SHORT_INT_T>(runningTotal, newValue, count);
            default: return -1;
         }
      case MPI_2INT:
         switch (op) {
            case MPI_MAXLOC:	return iPerformOpMaxloc<MPI_2INT_T>(runningTotal, newValue, count);
            case MPI_MINLOC:	return iPerformOpMinloc<MPI_2INT_T>(runningTotal, newValue, count);
            default: return -1;
         }
      case MPI_LONG_DOUBLE_INT:
         switch (op) {
            case MPI_MAXLOC:	return iPerformOpMaxloc<MPI_LONG_DOUBLE_INT_T>(runningTotal, newValue, count);
            case MPI_MINLOC:	return iPerformOpMinloc<MPI_LONG_DOUBLE_INT_T>(runningTotal, newValue, count);
            default: return -1;
         }

      default: return -1;
   }
}

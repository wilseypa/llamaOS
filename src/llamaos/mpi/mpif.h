! Copyright (c) 2013, John Gideon
! All rights reserved.
!
! Redistribution and use in source and binary forms, with or without
! modification, are permitted provided that the following conditions are met:
! 
!    1. Redistributions of source code must retain the above copyright notice,
!       this list of conditions and the following disclaimer.
! 
!    2. Redistributions in binary form must reproduce the above copyright notice,
!       this list of conditions and the following disclaimer in the documentation
!       and/or other materials provided with the distribution.
! 
! THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDER(S) AND CONTRIBUTORS ''AS IS''
! AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
! IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
! DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER(S) OR CONTRIBUTORS BE LIABLE
! FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
! DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
! SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
! CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
! OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
! OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
!
! The views and conclusions contained in the software and documentation are those
! of the authors and should not be interpreted as representing official policies,
! either expressed or implied, of the copyright holder(s) or contributors.

integer, parameter :: MPI_SUCCESS = 0

integer, parameter :: MPI_CHAR = 1
integer, parameter :: MPI_BYTE = 2
integer, parameter :: MPI_SHORT = 3
integer, parameter :: MPI_INT = 4
integer, parameter :: MPI_LONG = 5
integer, parameter :: MPI_FLOAT = 6
integer, parameter :: MPI_DOUBLE = 7
integer, parameter :: MPI_UNSIGNED_CHAR = 8
integer, parameter :: MPI_UNSIGNED_SHORT = 9
integer, parameter :: MPI_UNSIGNED = 10
integer, parameter :: MPI_UNSIGNED_LONG = 11
integer, parameter :: MPI_LONG_DOUBLE = 12
integer, parameter :: MPI_LONG_LONG_INT = 13

integer, parameter :: MPI_FLOAT_INT = 14
integer, parameter :: MPI_LONG_INT = 15
integer, parameter :: MPI_DOUBLE_INT = 16
integer, parameter :: MPI_SHORT_INT = 17
integer, parameter :: MPI_2INT = 18
integer, parameter :: MPI_LONG_DOUBLE_INT = 19

integer, parameter :: MPI_DATATYPE_NULL = 20
integer, parameter :: MPI_OP_NULL = 21
integer, parameter :: MPI_ERRHANDLER_NULL = 22

integer, parameter :: MPI_CHARACTER = 23
integer, parameter :: MPI_INTEGER = 24
integer, parameter :: MPI_INTEGER1 = 25
integer, parameter :: MPI_INTEGER2 = 26
integer, parameter :: MPI_INTEGER4 = 27
integer, parameter :: MPI_REAL = 28
integer, parameter :: MPI_DOUBLE_PRECISION = 29
integer, parameter :: MPI_COMPLEX = 30
integer, parameter :: MPI_DOUBLE_COMPLEX = 31
integer, parameter :: MPI_LOGICAL = 32

integer, parameter :: MPI_MAX       = 1      !maximum
integer, parameter :: MPI_MIN       = 2      !minimum
integer, parameter :: MPI_SUM       = 3      !sum
integer, parameter :: MPI_PROD      = 4      !product
integer, parameter :: MPI_LAND      = 5      !logical and
integer, parameter :: MPI_BAND      = 6      !bit-wise and
integer, parameter :: MPI_LOR       = 7      !logical or
integer, parameter :: MPI_BOR       = 8      !bit-wise or
integer, parameter :: MPI_LXOR      = 9      !logical xor
integer, parameter :: MPI_BXOR      = 10     !bit-wise xor
integer, parameter :: MPI_MAXLOC    = 11     !max value and location
integer, parameter :: MPI_MINLOC    = 12     !min value and location

integer, parameter :: MPI_COMM_NULL  = 0
integer, parameter :: MPI_COMM_WORLD = 2147483647
integer, parameter :: MPI_COMM_SELF  = 2147483646

integer, parameter :: MPI_GROUP_NULL  = 0
integer, parameter :: MPI_GROUP_EMPTY = -1

integer, parameter :: MPI_REQUEST_NULL = 0

integer, parameter :: MPI_IDENT = 1     !Identical
integer, parameter :: MPI_CONGRUENT = 2 !(only for MPI_COMM_COMPARE ) The groups are identical
integer, parameter :: MPI_SIMILAR = 3   !Same members, but in a different order
integer, parameter :: MPI_UNEQUAL = 4   !Different

integer, parameter :: MPI_STATUS_IGNORE = 0
integer, parameter :: MPI_TAG_UB = 2147483647
integer, parameter :: MPI_UNDEFINED = -1
integer, parameter :: MPI_ANY_SOURCE = -1
integer, parameter :: MPI_ANY_TAG = -1

integer, parameter :: MPI_STATUS_SIZE = 4

integer, parameter :: MPI_ERR_INTERN = 0
integer, parameter :: MPI_MAX_ERROR_STRING = 0

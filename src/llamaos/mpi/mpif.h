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

      integer MPI_SUCCESS
      parameter (MPI_SUCCESS = 0)

      integer MPI_CHAR, MPI_BYTE, MPI_SHORT, MPI_INT, MPI_LONG 
      integer MPI_FLOAT, MPI_DOUBLE, MPI_UNSIGNED_CHAR
      integer MPI_UNSIGNED_SHORT, MPI_UNSIGNED, MPI_UNSIGNED_LONG
      integer MPI_LONG_DOUBLE, MPI_LONG_LONG_INT
      parameter (MPI_CHAR = 1)
      parameter (MPI_BYTE = 2)
      parameter (MPI_SHORT = 3)
      parameter (MPI_INT = 4)
      parameter (MPI_LONG = 5)
      parameter (MPI_FLOAT = 6)
      parameter (MPI_DOUBLE = 7)
      parameter (MPI_UNSIGNED_CHAR = 8)
      parameter (MPI_UNSIGNED_SHORT = 9)
      parameter (MPI_UNSIGNED = 10)
      parameter (MPI_UNSIGNED_LONG = 11)
      parameter (MPI_LONG_DOUBLE = 12)
      parameter (MPI_LONG_LONG_INT = 13)

      integer MPI_FLOAT_INT, MPI_LONG_INT, MPI_DOUBLE_INT
      integer MPI_SHORT_INT, MPI_2INT, MPI_LONG_DOUBLE_INT
      parameter (MPI_FLOAT_INT = 14)
      parameter (MPI_LONG_INT = 15)
      parameter (MPI_DOUBLE_INT = 16)
      parameter (MPI_SHORT_INT = 17)
      parameter (MPI_2INT = 18)
      parameter (MPI_LONG_DOUBLE_INT = 19)

      integer MPI_DATATYPE_NULL, MPI_OP_NULL, MPI_ERRHANDLER_NULL
      parameter (MPI_DATATYPE_NULL = 20)
      parameter (MPI_OP_NULL = 21)
      parameter (MPI_ERRHANDLER_NULL = 22)

      integer MPI_CHARACTER, MPI_INTEGER, MPI_INTEGER1, MPI_INTEGER2
      integer MPI_INTEGER4, MPI_REAL, MPI_DOUBLE_PRECISION, MPI_COMPLEX
      integer MPI_DOUBLE_COMPLEX, MPI_LOGICAL
      parameter (MPI_CHARACTER = 23)
      parameter (MPI_INTEGER = 24)
      parameter (MPI_INTEGER1 = 25)
      parameter (MPI_INTEGER2 = 26)
      parameter (MPI_INTEGER4 = 27)
      parameter (MPI_REAL = 28)
      parameter (MPI_DOUBLE_PRECISION = 29)
      parameter (MPI_COMPLEX = 30)
      parameter (MPI_DOUBLE_COMPLEX = 31)
      parameter (MPI_LOGICAL = 32)

      integer MPI_MAX, MPI_MIN, MPI_SUM, MPI_PROD, MPI_LAND, MPI_BAND
      integer MPI_LOR, MPI_BOR, MPI_LXOR, MPI_BXOR
      integer MPI_MAXLOC, MPI_MINLOC
      parameter (MPI_MAX       = 1)      !maximum
      parameter (MPI_MIN       = 2)      !minimum
      parameter (MPI_SUM       = 3)      !sum
      parameter (MPI_PROD      = 4)      !product
      parameter (MPI_LAND      = 5)      !logical and
      parameter (MPI_BAND      = 6)      !bit-wise and
      parameter (MPI_LOR       = 7)      !logical or
      parameter (MPI_BOR       = 8)      !bit-wise or
      parameter (MPI_LXOR      = 9)      !logical xor
      parameter (MPI_BXOR      = 10)     !bit-wise xor
      parameter (MPI_MAXLOC    = 11)     !max value and location
      parameter (MPI_MINLOC    = 12)     !min value and location

      integer MPI_COMM_NULL, MPI_COMM_WORLD, MPI_COMM_SELF
      parameter (MPI_COMM_NULL  = 0)
      parameter (MPI_COMM_WORLD = 2147483647)
      parameter (MPI_COMM_SELF  = 2147483646)

      integer MPI_GROUP_NULL, MPI_GROUP_EMPTY
      parameter (MPI_GROUP_NULL  = 0)
      parameter (MPI_GROUP_EMPTY = -1)

      integer MPI_REQUEST_NULL
      parameter (MPI_REQUEST_NULL = 0)

      integer MPI_IDENT, MPI_CONGRUENT, MPI_SIMILAR, MPI_UNEQUAL
      parameter (MPI_IDENT = 1)     !Identical
      parameter (MPI_CONGRUENT = 2) !(only for MPI_COMM_COMPARE ) The groups are identical
      parameter (MPI_SIMILAR = 3)   !Same members, but in a different order
      parameter (MPI_UNEQUAL = 4)   !Different

      integer MPI_STATUS_IGNORE, MPI_TAG_UB, MPI_UNDEFINED
      integer MPI_ANY_SOURCE, MPI_ANY_TAG
      parameter (MPI_STATUS_IGNORE = 0)
      parameter (MPI_TAG_UB = 2147483647)
      parameter (MPI_UNDEFINED = -1)
      parameter (MPI_ANY_SOURCE = -1)
      parameter (MPI_ANY_TAG = -1)

      integer MPI_STATUS_SIZE
      parameter (MPI_STATUS_SIZE = 4)

      integer MPI_ERR_INTERN, MPI_MAX_ERROR_STRING
      parameter (MPI_ERR_INTERN = 0)
      parameter (MPI_MAX_ERROR_STRING = 0)
      
      double precision mpi_wtime, mpi_wtick
      external mpi_wtime, mpi_wtick

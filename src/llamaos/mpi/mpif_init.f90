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

! Taken from http://stackoverflow.com/questions/13843772/fortran-read-command-line-arguments-how-to-use-command-line-argument
SUBROUTINE mpi_init ( ierr )
   integer ierr
   integer :: num_args, ix
   character(len=20), dimension(:), allocatable :: args
   
   num_args = iargc()
   allocate(args(num_args))
   
   do ix = 1, num_args
      call getarg(ix,args(ix))
   end do
   
   call mpi_init_full(num_args, args, ierr)
   
   RETURN  
END
     

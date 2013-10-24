C     -*- Mode: Fortran; -*-
C
C     (C) 2001 by Argonne National Laboratory.
C     See COPYRIGHT in top-level directory.
C
       subroutine mpirinitf( )
       integer mpi_status_size
       parameter (mpi_status_size=10)
C      STATUS_IGNORE, STATUSES_IGNORE
       integer si(mpi_status_size), ssi(mpi_status_size,1)
C      BOTTOM, IN_PLACE, UNWEIGHTED, ERRCODES_IGNORE
       integer bt, ip, uw, ecsi(1)
C      ARGVS_NULL, ARGV_NULL
       character*1 asn(1,1), an(1)
       character*1 pads_a(3), pads_b(3)
       common /MPIFCMB1/ si
       common /MPIFCMB2/ ssi
       common /MPIFCMB3/ bt
       common /MPIFCMB4/ ip
       common /MPIFCMB5/ uw
       common /MPIFCMB6/ ecsi
       common /MPIFCMB7/ asn, pads_a
       common /MPIFCMB8/ an, pads_b
       common /MPIFCMB9/ we
       save /MPIFCMB1/,/MPIFCMB2/
       save /MPIFCMB3/,/MPIFCMB4/,/MPIFCMB5/,/MPIFCMB6/
       save /MPIFCMB7/,/MPIFCMB8/,/MPIFCMB9/
C      MPI_ARGVS_NULL 
C      (Fortran requires character data in a separate common block)
       call mpirinitc(si, ssi, bt, ip, uw, ecsi, asn, we)
       call mpirinitc2(an)
       return
       end

program main
   implicit none
   include 'mpif.h'
   integer ierr, numNodes, rank, source
   integer buf(3)

   call mpi_sleep(3)
   call mpi_init(ierr)
   call mpi_comm_size(MPI_COMM_WORLD, numNodes, ierr)
   call mpi_comm_rank(MPI_COMM_WORLD, rank, ierr)

   print *, 'Pt2pt test...'
   if (rank.eq.0) then
      call mpi_sleep(3)
      do source = 1, numNodes-1, 1
         call mpi_recv(buf, 3, MPI_INTEGER, source, 0, MPI_COMM_WORLD, 0)
         if ((buf(1).eq.3).and.(buf(2).eq.80).and.(buf(3).eq.19)) then
            print *, 'Successful receive'
         else
            print *, 'Failed received'
         endif
      end do
   else
      buf(1) = 3
      buf(2) = 80
      buf(3) = 19
      call mpi_send(buf, 3, MPI_INTEGER, 0, 0, MPI_COMM_WORLD);
      print *, 'Sent message to root'
   endif
end

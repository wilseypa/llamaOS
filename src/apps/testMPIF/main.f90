program main
include 'mpif.h'
call mpi_sleep(3)
call mpi_init(ierr)
call mpi_comm_size(MPI_COMM_WORLD, numNodes, ierr)
end

#!/bin/bash
cd ../../../../net
sudo xl create shmem.config name=\"pi3f90-r.4\"
sleep 5
cd ../mpich/examples/local/f90
sudo xl create pi3f90.config name=\"pi3f90-0.4\"
sleep 1
sudo xl create pi3f90.config name=\"pi3f90-1.4\"
sudo xl create pi3f90.config name=\"pi3f90-2.4\"
sudo xl create pi3f90.config name=\"pi3f90-3.4\"
sudo xl console pi3f90-0.4
sleep 5
sudo xl destroy pi3f90-r.4

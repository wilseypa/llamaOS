#!/bin/bash
cd ../../../../net
sudo xl create shmem.config name=\"fpi-r.4\"
sleep 5
cd ../mpich/examples/local/f77
sudo xl create fpi.config name=\"fpi-0.4\"
sleep 1
sudo xl create fpi.config name=\"fpi-1.4\"
sudo xl create fpi.config name=\"fpi-2.4\"
sudo xl create fpi.config name=\"fpi-3.4\"
sudo xl console fpi-0.4
sleep 5
sudo xl destroy fpi-r.4

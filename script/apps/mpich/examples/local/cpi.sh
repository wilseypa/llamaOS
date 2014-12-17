#!/bin/bash
cd ../../../net
sudo xl create shmem.config name=\"cpi-r.4\"
sleep 5
cd ../mpich/examples/local
sudo xl create cpi.config name=\"cpi-0.4\"
sleep 1
sudo xl create cpi.config name=\"cpi-1.4\"
sudo xl create cpi.config name=\"cpi-2.4\"
sudo xl create cpi.config name=\"cpi-3.4\"
sudo xl console cpi-0.4
sleep 5
sudo xl destroy cpi-r.4

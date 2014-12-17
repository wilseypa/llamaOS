#!/bin/bash
cd ../../net
sudo xl create shmem.config name=\"epidemic-r.2\"
sleep 5
cd ../warped-4.0.0/local
sudo xl create epidemic_w.config name=\"epidemic-0.2\"
sudo xl create epidemic.config name=\"epidemic-1.2\"
sudo xl console epidemic-0.2
sleep 10
sudo xl destroy epidemic-r.2


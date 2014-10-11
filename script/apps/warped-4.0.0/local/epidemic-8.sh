#!/bin/bash
cd ../../net
sudo xl create shmem.config name=\"epidemic-r.8\"
sleep 5
cd ../warped-4.0.0/local
sudo xl create epidemic_w.config name=\"epidemic-0.8\"
sudo xl create epidemic.config name=\"epidemic-1.8\"
sudo xl create epidemic.config name=\"epidemic-2.8\"
sudo xl create epidemic.config name=\"epidemic-3.8\"
sudo xl create epidemic.config name=\"epidemic-4.8\"
sudo xl create epidemic.config name=\"epidemic-5.8\"
sudo xl create epidemic.config name=\"epidemic-6.8\"
sudo xl create epidemic.config name=\"epidemic-7.8\"
sudo xl console epidemic-0.8
sleep 10
sudo xl destroy epidemic-r.8


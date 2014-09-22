#!/bin/bash
cd ../../net
sudo xl create shmem.config name=\"epidemic-r.4\"
sleep 10
cd ../warped-4.0.0/local
sudo xl create epidemic_w.config name=\"epidemic-0.4\"
sudo xl create epidemic.config name=\"epidemic-1.4\"
sudo xl create epidemic.config name=\"epidemic-2.4\"
sudo xl create epidemic.config name=\"epidemic-3.4\"
sudo xl console epidemic-0.4
sleep 10
sudo xl destroy epidemic-r.4

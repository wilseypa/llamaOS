#!/bin/bash
cd ../../net
sudo xl create shmem.config name=\"imb-r.4\"
sleep 5
cd ../imb/local
sudo xl create imb.config name=\"imb-0.4\"
sleep 1
sudo xl create imb.config name=\"imb-1.4\"
sudo xl create imb.config name=\"imb-2.4\"
sudo xl create imb.config name=\"imb-3.4\"
sudo xl console imb-0.4
sleep 5
sudo xl destroy imb-r.4

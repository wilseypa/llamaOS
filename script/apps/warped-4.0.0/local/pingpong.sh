#!/bin/bash
cd ../../net
sudo xl create -c shmem.config name=\"pingpong-r.2\"
sleep 5
cd ../warped-4.0.0/local
sudo xl create pingpong.config name=\"pingpong-0.2\"
sudo xl create pingpong.config name=\"pingpong-1.2\"
sudo xl console pingpong-0.2
sleep 5
sudo xl destroy pingpong-r.2

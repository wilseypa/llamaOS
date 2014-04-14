#!/bin/bash
cd ../../../net
sudo xl create shmem.config name=\"srtest-r.4\"
sleep 5
cd ../mpich/examples/local
sudo xl create srtest.config name=\"srtest-0.4\"
sleep 1
sudo xl create srtest.config name=\"srtest-1.4\"
sudo xl create srtest.config name=\"srtest-2.4\"
sudo xl create srtest.config name=\"srtest-3.4\"
sudo xl console srtest-0.4
sleep 5
sudo xl destroy srtest-r.4

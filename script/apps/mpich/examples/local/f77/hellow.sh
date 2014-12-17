#!/bin/bash
cd ../../../../net
sudo xl create shmem.config name=\"hellow-r.4\"
sleep 5
cd ../mpich/examples/local/f77
sudo xl create hellow.config name=\"hellow-0.4\"
sleep 1
sudo xl create hellow.config name=\"hellow-1.4\"
sudo xl create hellow.config name=\"hellow-2.4\"
sudo xl create hellow.config name=\"hellow-3.4\"
sudo xl console hellow-0.4
sleep 5
sudo xl destroy hellow-r.4

#!/bin/bash
cd ../../net
sudo xl create shmem.config name=\"netpipe-r.2\"
sleep 5
cd ../netpipe/local
sudo xl create netpipe.config name=\"netpipe-0.2\"
sudo xl create netpipe.config name=\"netpipe-1.2\"
sudo xl console netpipe-0.2
sleep 10
sudo xl destroy netpipe-r.2


#!/bin/bash
cd ../../net
konsole --hold -e sudo xl create -c shmem.config name=\"epidemic-r.4\"
sleep 5
cd ../warped-4.0.0/local
konsole --hold -e sudo xl create -c epidemic_w.config name=\"epidemic-0.4\"
sleep 3
konsole --hold -e sudo xl create -c epidemic.config name=\"epidemic-1.4\"
sleep 3
konsole --hold -e sudo xl create -c epidemic.config name=\"epidemic-2.4\"
sleep 3
konsole --hold -e sudo xl create -c epidemic.config name=\"epidemic-3.4\"
# sudo xl console epidemic-0.4
sleep 10
# sudo xl destroy epidemic-r.4


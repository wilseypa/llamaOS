#!/bin/bash
cd ../../net
konsole --hold -e sudo xl create -c shmem.config name=\"imb-r.4\"
sleep 5
cd ../imb/local
konsole --hold -e sudo xl create -c imb.config name=\"imb-0.4\"
sleep 3
konsole --hold -e sudo xl create -c imb.config name=\"imb-1.4\"
sleep 3
konsole --hold -e sudo xl create -c imb.config name=\"imb-2.4\"
sleep 3
konsole --hold -e sudo xl create -c imb.config name=\"imb-3.4\"
# sleep 60
# sudo xl destroy imb-r.4

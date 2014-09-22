#!/bin/bash
dd if=/dev/zero of=disk.img bs=512 count=65536
sudo mkfs.ext2 -r 0 disk.img
sudo mount disk.img /mnt/llamaOS
sudo cp epidemic.xml /mnt/llamaOS
sudo cp parallel.json /mnt/llamaOS
sudo cp sequential.json /mnt/llamaOS
sudo umount /mnt/llamaOS


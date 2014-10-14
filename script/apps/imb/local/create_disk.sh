#!/bin/bash
dd if=/dev/zero of=disk.img bs=512 count=81920
sudo mkfs.ext2 -r 0 disk.img
sudo mount disk.img /mnt/llamaOS
# sudo cp epidemic.xml /mnt/llamaOS
sudo umount /mnt/llamaOS


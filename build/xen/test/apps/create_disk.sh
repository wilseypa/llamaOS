#!/bin/bash
dd if=/dev/zero of=disk.img bs=512 count=128
sudo mkfs.ext2 -r 0 disk.img
sudo mount disk.img /mnt/llamaOS
sudo cp test.xml /mnt/llamaOS
sudo umount /mnt/llamaOS


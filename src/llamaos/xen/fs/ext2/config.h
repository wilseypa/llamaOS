/* config.h
 * 
 * Copyright (C) 2009 Guillaume Duranceau
 * This file is part of CROCOS.
 *
 * This file is distributed under the terms of the GNU General Public License.
 * This license is available in the COPYING file, in the main repository.
 */

/* macros holding the system configuration. they can be modified to adapt
 * CROCOS to a particular system. */

#ifndef _CROCOS_CONFIG_CONFIG_H
#define _CROCOS_CONFIG_CONFIG_H

/* maximum number of processes */
#define CONFIG_TASKS_N 32

/* kernel/user stack size per process (number of words in stack).
 * on 32/64 bits systems, the stack size in bytes is 4/8 times this value. */
#define CONFIG_KSTACK_SIZE 512
#define CONFIG_USTACK_SIZE 4096

/* maximum number of characters printed in /proc/pid/cmd files (process
 * command line) */
#define CONFIG_MAX_CMDLINE_SIZE 64

/* disk image name */
#define CONFIG_DISK_IMAGE "disk.img"
// #define CONFIG_DISK_SIZE (10 << 20)
#define CONFIG_DISK_SIZE (64*1024)

/* for ext2 file system, maximum number of block groups.
 * the size of the block groups table is 32 times this value (in bytes).
 * max partition size (bytes) =  8 * CONFIG_EXT2_MAX_BLKGRP * block_size^2 */
#define CONFIG_EXT2_MAX_BLKGRP 256

/* maximum number of files which can be opened simultaneously */
#define CONFIG_FS_OPENED_INODE_N 128

/* maximum number of file descriptors (opened file) per process */
#define CONFIG_FS_MAX_FD 16

#endif /* _CROCOS_CONFIG_CONFIG_H */


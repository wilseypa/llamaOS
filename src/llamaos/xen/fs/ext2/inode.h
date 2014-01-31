/* inode.h
 * 
 * Copyright (C) 2009 Guillaume Duranceau
 * This file is part of CROCOS.
 *
 * This file is distributed under the terms of the GNU General Public License.
 * This license is available in the COPYING file, in the main repository.
 */

/* Generic inode (contains information to locate a file on a disk).
 * For a given valid path, there is only one inode. The inode structure is
 * shared between processes working on the same file. */

#ifndef _CROCOS_FS_INODE_H
#define _CROCOS_FS_INODE_H

#include "stat.h"


/* do not include fs/fsdesc.h to avoid circular header dependencies */
struct fsdesc_t;

/* a file is identified by the couple (device, inode number) in the stat
 * structure */
struct inode {
    struct stat st; /* device ID, inode number, mode access... */
    struct fsdesc_t *fs; /* file system descriptor for this inode */
    int ref; /* number of file descriptors opened for this inode */

    struct inode *used_prev, *used_next; /* used inodes list */
    struct inode *free_prev, *free_next; /* free inodes list */
};

#endif /* _CROCOS_FS_INODE_H */


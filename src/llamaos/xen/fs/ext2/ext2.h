/* ext2.h
 * 
 * Copyright (C) 2009 Guillaume Duranceau
 * This file is part of CROCOS.
 *
 * This file is distributed under the terms of the GNU General Public License.
 * This license is available in the COPYING file, in the main repository.
 */

/* driver for ext2 file system. */

#ifndef _CROCOS_FS_EXT2_H
#define _CROCOS_FS_EXT2_H

#include "direntry.h"
#include "fsdesc.h"
#include "inode.h"
#include "stat.h"

#include <stddef.h>
#include <unistd.h>

#define EXT2_ROOT_INO 2

/* mount the disk device, considering that it contains a single partition
 * formated as an ext2 file system. */
bool ext2_mount ();
bool ext2_unmount ();

/* find the inode number (ino) of the file/directory 'name' in the 'parent'
 * directory.
 * return 0 if the file/directory is found.
 * return -EIO in case of low-level I/O error.
 * return -ENAMETOOLONG if 'name' is too long.
 * return -ENOENT if the file/directory doesn't exist.
 * return -ENOTDIR if 'parent' is not a directory. */
int ext2_lookup (ino_t parent, const char *name, int name_len, ino_t *ino);

/* fill a stat structure.
 * return -EIO in case of low-level I/O error, 0 otherwise */
int ext2_fill_stat (ino_t ino, struct stat *buf);

/* read count bytes from offset from a file.
 * return number of bytes read (can be lower than count if EOF).
 * return -EFBIG if the file is too big for this implementation.
 * return -EIO in case of low-level I/O error. */
ssize_t ext2_read (struct inode *node, void *buf, off_t offset, size_t count);

/* write bytes to offset from a file.
 * return number of bytes written.
 * return -EFBIG if the file size limit is reached.
 * return -EIO in case of low-level I/O error. */
ssize_t ext2_write (struct inode *node, const void *data_buf, off_t offset, size_t len);

/* read the directory entry at position 'offset' in the directory file.
 * return number of bytes read in the directory file (0 if EOF) */
ssize_t ext2_readdir (struct inode *dirnode, struct direntry *dir,
    off_t offset);

#endif /* _CROCOS_FS_EXT2_H */


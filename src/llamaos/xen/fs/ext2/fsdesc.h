/* fsdesc.h
 * 
 * Copyright (C) 2009 Guillaume Duranceau
 * This file is part of CROCOS.
 *
 * This file is distributed under the terms of the GNU General Public License.
 * This license is available in the COPYING file, in the main repository.
 */

/* File system instance descriptor */

#ifndef _CROCOS_FS_FSDESC_H
#define _CROCOS_FS_FSDESC_H

#include "direntry.h"
#include "inode.h"
#include "stat.h"
#include <stdbool.h>
#include <stddef.h>
#include <unistd.h>

struct fsdesc_t;

/* file system dependent functions */

/* mount the file system instance */
typedef bool (*fsdesc_mount) (struct fsdesc_t *fsdesc, dev_t dev);

/* find the inode number of a file in a directory. */
typedef int (*fsdesc_lookup) (ino_t parent, const char *name,
    int name_len, ino_t *ino);

/* fill an inode structure. */
typedef int (*fsdesc_fill_stat) (ino_t ino, struct stat *buf);

/* read count bytes from offset from a file. */
typedef ssize_t (*fsdesc_read) (struct inode *node, void *buf,
    off_t offset, size_t count);

/* write len bytes to offset from a file. */
typedef ssize_t (*fsdesc_write) (struct inode *node, const void *data_buf,
				off_t offset, size_t len);

/* read one directory entry at position 'offset' in a directory file */
typedef ssize_t (*fsdesc_readdir) (struct inode *dirnode,
    struct direntry *dir, off_t offset);

/* file system descriptor */
struct fsdesc_t {
    ino_t            root_ino;  /* root inode */
    fsdesc_mount     mount;     /* mount function */
    fsdesc_lookup    lookup;    /* lookup function */
    fsdesc_fill_stat fill_stat; /* fill_inode function */
    fsdesc_read      read;      /* read function */
    fsdesc_write     write;     /* write function */ 
    fsdesc_readdir   readdir;   /* readdir function */
};

#endif /* _CROCOS_FS_FSDESC_H */


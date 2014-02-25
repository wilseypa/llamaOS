/* fd.h
 * 
 * Copyright (C) 2009 Guillaume Duranceau
 * This file is part of CROCOS.
 *
 * This file is distributed under the terms of the GNU General Public License.
 * This license is available in the COPYING file, in the main repository.
 */

/* File descriptors management */

#ifndef _CROCOS_FS_FD_H
#define _CROCOS_FS_FD_H

#include "inode.h"
#include "stat.h"
#include <stdbool.h>
#include <unistd.h>

struct fd {
    bool used; /* fd used in the process */
    struct inode *inode; /* inode for the opened file */
    int flags; /* open flags */
    off_t offset; /* offset for read/write accesses */
};

/* must be called when a processes is initialized and killed */
void fd_init_process ();
void fd_kill_process ();

/* allocate a free fd for a process, and use it for the given inode, with the
 * given opening flags.
 * return -EMFILE if the process reached the maximum number of files opened.
 * return a free fd otherwise */
int fd_allocate (struct inode *inode, int flags);

/* free a fd for a process (validity of fd must have been checked with fd_get
 * before) */
void fd_free (int fd);

/* get the fd structure. return NULL if fd isn't a valid file descriptor */
struct fd *fd_get (int fd);

#endif /* _CROCOS_FS_FD_H */


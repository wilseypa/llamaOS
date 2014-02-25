/* fd.c
 * 
 * Copyright (C) 2009 Guillaume Duranceau
 * This file is part of CROCOS.
 *
 * This file is distributed under the terms of the GNU General Public License.
 * This license is available in the COPYING file, in the main repository.
 */

#include "config.h"
#include "fd.h"
#include "inode.h"
#include "vfs.h"
#include "list.h"
#include <errno.h>
#include <stdbool.h>
#include <stddef.h>

struct fd fd_tbl [CONFIG_FS_MAX_FD];

void fd_init_process () {
    int fd; for (fd = 0; fd < CONFIG_FS_MAX_FD; fd++)
        fd_tbl[fd].used = false;
}

void fd_kill_process () {
    /* close opened file descriptors */
    int fd; for (fd = 0; fd < CONFIG_FS_MAX_FD; fd++)
        if (fd_tbl[fd].used) fs_close (fd);
}


int fd_allocate (struct inode *inode, int flags) {
    struct fd *freefd;
    int fd; for (fd = 0; fd < CONFIG_FS_MAX_FD; fd++)
        if (!fd_tbl[fd].used) break;
    if (fd == CONFIG_FS_MAX_FD) return -EMFILE;
    freefd = fd_tbl + fd;
    freefd->used = true;
    freefd->inode = inode;
    freefd->flags = flags;
    freefd->offset = 0;
    return fd;
}

void fd_free (int fd) {
    fd_tbl[fd].used = false;
}

struct fd *fd_get (int fd) {
    if ((fd < 0) || (fd >= CONFIG_FS_MAX_FD) || (!(fd_tbl[fd].used)))
        return NULL;
    return fd_tbl + fd;
}


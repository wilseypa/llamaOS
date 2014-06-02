/* vfs.c
 * 
 * Copyright (C) 2009 Guillaume Duranceau
 * This file is part of CROCOS.
 *
 * This file is distributed under the terms of the GNU General Public License.
 * This license is available in the COPYING file, in the main repository.
 */

/* A file location is normally identify by a couple (device, inode number).
 * Only one disk storage mount point is supported. Thus, the device ID is not
 * used in the file sytem related functions. */

#include "config.h"
#include "panic.h"
#include "direntry.h"
#include "fd.h"
#include "ext2.h"
#include "inode.h"
#include "stat.h"
#include "vfs.h"
#include "list.h"
#include <errno.h>
#include <stdbool.h>
#include <stddef.h>

/* inodes table (used to keep inodes of opened files)
 * multiple processes opening the same file will share the inode by
 * referencing the same entry in this table in their file descriptor. */
struct inode ino_tbl [CONFIG_FS_OPENED_INODE_N];

/* lists of used and free inodes */
struct inode *free_inodes, *used_inodes;

/* opening flags */
#define O_RDONLY 00
#define O_WRONLY 01
#define O_RDWR   02

#define RDWR_MASK 03
#define is_rd(flags)    \
    ((((flags) & RDWR_MASK) == O_RDONLY) || (((flags) & RDWR_MASK) == O_RDWR))
#define is_wr(flags)    \
    ((((flags) & RDWR_MASK) == O_WRONLY) || (((flags) & RDWR_MASK) == O_RDWR))

/* whence */
#define SEEK_SET 0
#define SEEK_CUR 1
#define SEEK_END 2

static ino_t ext2_root_ino = EXT2_ROOT_INO;

/* find the inode number (ino) of the file/directory identified by 'path' in
 * the 'parent' directory.
 * return 0 if the file/directory is found
 * return -EACCES if search permission is denied for one of the directories
 * return -ENAMETOOLONG if the file name is too long
 * return -ENOENT if the file does not exist
 * return -ENOTDIR if a component of the path is not a directory
 * return -EIO if a low-level I/O error occured */
static int lookup (ino_t parent, const char *path, ino_t *ino) {
    struct stat pdir; /* parent directory stat info */
    const char *entry; /* directory or file name (without any "/") */
    int entry_len, retval;
    ino_t entry_ino;

    /* check that parent is a directory with search permission */
    if ((retval = ext2_fill_stat (parent, &pdir)) < 0) return retval;
    if (!S_ISDIR (pdir.st_mode)) return -ENOTDIR;
    if (!(pdir.st_mode & S_IXUSR)) return -EACCES;

    while (*path == '/') path++; /* eat slashes */
    entry = path;
    /* find the end of the entry */
    while ((*path != '/')  && (*path != 0)) path++;
    entry_len = (int)(path - entry);

    /* end of search ? last path character is a '/' => return parent inode */
    if (entry_len == 0) { *ino = parent; return 0; }
    /* look for the entry inode number */
    if ((retval = ext2_lookup (parent, entry, entry_len, &entry_ino)) < 0)
        return retval;
    /* end of search ? return the entry inode just found */
    if (*path == 0) { *ino = entry_ino; return 0; }
    /* continue the search with the next entry */
    return lookup (entry_ino, path, ino);
}

void fs_initialize () {
    int ino;
    if (!ext2_mount ()) kpanic ("can't mount root FS");
    list_init (free_inodes, free_prev, free_next);
    list_init (used_inodes, used_prev, used_next);
    for (ino = 0; ino < CONFIG_FS_OPENED_INODE_N; ino++) {
        list_add_tail (free_inodes, ino_tbl + ino, free_prev, free_next);
        ino_tbl[ino].ref = 0;
    }
}

int fs_stat (const char *path, struct stat *buf) {
    ino_t path_ino;
    int retval;
    if (*path == 0) return -ENOENT; /* empty path */
    if ((retval = lookup (ext2_root_ino, path, &path_ino)) < 0) return retval;
    if ((retval = ext2_fill_stat (path_ino, buf)) < 0) return retval;
    return 0;
}

int fs_open (const char *path, int flags) {
    struct inode *node;
    ino_t path_ino;
    int retval, nb_ino;
    bool already_opened = false;

    if (*path == 0) return -ENOENT; /* empty path */

    /* retrieve the inode number and check if it is an already opened file */
    if ((retval = lookup (ext2_root_ino, path, &path_ino)) < 0) return retval;
    list_foreach_forward (used_inodes, node, nb_ino, used_prev, used_next) {
        if (node->st.st_ino == path_ino) break;
    }
    if (!list_foreach_f_early_break (used_inodes, node, nb_ino, used_prev,
        used_next)) { /* file not already opened */
        if (list_is_empty (free_inodes, free_prev, free_next)) return -ENFILE;
        node = list_get_head (free_inodes, free_prev, free_next);
        if ((retval = ext2_fill_stat (path_ino, &(node->st))) < 0)
            return retval;
    }
    else already_opened = true;

    /* check open flags */
    mode_t mode = node->st.st_mode;
    if (S_ISDIR (mode) && is_wr (flags)) return -EISDIR;
    if ((!(mode & S_IRUSR)) && is_rd (flags)) return -EACCES;
    if ((!(mode & S_IWUSR)) && is_wr (flags)) return -EACCES;

    /* allocate a file descriptor for the running process */
    if ((retval = fd_allocate (node, flags)) < 0)
        return retval;

    /* one more file descriptor is referencing the inode */
    (node->ref)++;
    /* if the file was not yet opened, move the inode from the free to the
     * used list */
    if (!already_opened) {
        list_pop_head (free_inodes, free_prev, free_next);
        list_add_tail (used_inodes, node, used_prev, used_next);
    }

    return retval;
}

int fs_close (int fd) {
    struct fd *fdesc = fd_get (fd);
    if (fdesc == NULL) return -EBADF;

    if ((--(fdesc->inode->ref)) == 0) { /* no more references on this inode */
        /* move the inode from the used to the free list */
        list_delete (used_inodes, fdesc->inode, used_prev, used_next);
        list_add_tail (free_inodes, fdesc->inode, free_prev, free_next);
    }

    /* free the file descriptor for the running process */
    fd_free (fd);
    return 0;
}

int fs_fstat (int fd, struct stat *buf) {
    struct fd *fdesc = fd_get (fd);
    if (fdesc == NULL) return -EBADF;
    *buf = fdesc->inode->st;
    return 0;
}

off_t fs_lseek (int fd, off_t offset, int whence) {
    off_t old_offset;
    mode_t mode;
    struct fd *fdesc = fd_get (fd);
    if (fdesc == NULL) return -EBADF;
    mode = fdesc->inode->st.st_mode;
    if (S_ISFIFO (mode) || S_ISSOCK (mode)) return -EPIPE;
    old_offset = fdesc->offset;
    switch (whence) {
        case SEEK_SET: fdesc->offset = offset; break;
        case SEEK_CUR: fdesc->offset += offset; break;
        case SEEK_END: fdesc->offset = fdesc->inode->st.st_size + offset;
                       break;
        default: return -EINVAL;
    }
    if (fdesc->offset < 0) { fdesc->offset = old_offset; return -EINVAL; }
    else return fdesc->offset;
}

ssize_t fs_read (int fd, void *buf, size_t count) {
    ssize_t retval;
    mode_t mode;
    struct fd *fdesc = fd_get (fd);
    if (fdesc == NULL) return -EBADF;
    if (!is_rd (fdesc->flags)) return -EINVAL;
    mode = fdesc->inode->st.st_mode;
    if (S_ISDIR (mode)) return -EISDIR;
    if (S_ISCHR (mode) || S_ISBLK (mode) || S_ISFIFO (mode) ||
        S_ISSOCK (mode)) /* don't support read on those file types */
        return -EINVAL;
    if (count == 0) return 0;
    retval = ext2_read (fdesc->inode, buf, fdesc->offset, count);
    if (retval > 0) fdesc->offset += retval;
    return retval;
}

ssize_t fs_write (int fd, const void *buf, size_t count) {
  ssize_t retval;
  mode_t mode;
  struct fd *fdesc = fd_get (fd);
  if (fdesc == NULL) return -EBADF;
  if (!is_wr (fdesc->flags)) return -EINVAL;
  mode = fdesc->inode->st.st_mode;
  if (S_ISDIR (mode)) return -EISDIR;
  if (S_ISCHR (mode) || S_ISBLK (mode) || S_ISFIFO (mode) || S_ISSOCK (mode)) return -EINVAL;
  if (count == 0) return 0;
  retval = ext2_write (fdesc->inode, buf, fdesc->offset, count);
  if (retval > 0) fdesc->offset += retval;
  return retval;
}

int fs_readdir (int fd, struct direntry *dir) {
    ssize_t retval;
    mode_t mode;
    struct fd *fdesc = fd_get (fd);
    if (fdesc == NULL) return -EBADF;
    mode = fdesc->inode->st.st_mode;
    if (!S_ISDIR (mode)) return -ENOTDIR;
    retval = ext2_readdir (fdesc->inode, dir, fdesc->offset);
    if (retval > 0) fdesc->offset += retval;
    return (retval > 0) ? 1 : 0;
}


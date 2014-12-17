/* stat.h
 * 
 * Copyright (C) 2009 Guillaume Duranceau
 * This file is part of CROCOS.
 *
 * This file is distributed under the terms of the GNU General Public License.
 * This license is available in the COPYING file, in the main repository.
 */

/* types, structure and macros definitions for the stat/fstat system calls */

#ifndef _CROCOS_FS_STAT_H
#define _CROCOS_FS_STAT_H

#include <stdint.h>

/* these typedefs seem more or less standard... */
typedef uint64_t dev_t;
typedef unsigned long int ino_t;
typedef uint32_t mode_t;
typedef unsigned int nlink_t;
typedef uint32_t uid_t;
typedef uint32_t gid_t;
typedef long int off_t;
typedef long int blksize_t;
typedef long int blkcnt_t;
typedef long int time_t;

struct stat {
    dev_t     st_dev;     /* ID of device containing file */
    ino_t     st_ino;     /* inode number */
    mode_t    st_mode;    /* protection */
    nlink_t   st_nlink;   /* number of hard links */
    uid_t     st_uid;     /* user ID of owner */
    gid_t     st_gid;     /* group ID of owner */
    dev_t     st_rdev;    /* device ID (if special file) */
    off_t     st_size;    /* total size, in bytes */
    blksize_t st_blksize; /* blocksize for file system I/O */
    blkcnt_t  st_blocks;  /* number of 512B blocks allocated */
    time_t    st_atime;   /* time of last access */
    time_t    st_mtime;   /* time of last modification */
    time_t    st_ctime;   /* time of last status change */
};

/* standard flags for the st_mode field:
 *
 * S_IFMT     bit mask for the file type bit fields
 * S_IFSOCK   socket
 * S_IFLNK    symbolic link
 * S_IFREG    regular file
 * S_IFBLK    block device
 * S_IFDIR    directory
 * S_IFCHR    character device
 * S_IFIFO    FIFO
 * S_ISUID    set UID bit
 * S_ISGID    set-group-ID bit
 * S_ISVTX    sticky bit
 * S_IRWXU    mask for file owner permissions
 * S_IRUSR    owner has read permission
 * S_IWUSR    owner has write permission
 * S_IXUSR    owner has execute permission
 * S_IRWXG    mask for group permissions
 * S_IRGRP    group has read permission
 * S_IWGRP    group has write permission
 * S_IXGRP    group has execute permission
 * S_IRWXO    mask for permissions for others (not in group)
 * S_IROTH    others have read permission
 * S_IWOTH    others have write permission
 * S_IXOTH    others have execute permission
 */
#define S_IFMT     0170000
#define S_IFSOCK   0140000
#define S_IFLNK    0120000
#define S_IFREG    0100000
#define S_IFBLK    0060000
#define S_IFDIR    0040000
#define S_IFCHR    0020000
#define S_IFIFO    0010000
#define S_ISUID    0004000
#define S_ISGID    0002000
#define S_ISVTX    0001000
#define S_IRWXU    00700
#define S_IRUSR    00400
#define S_IWUSR    00200
#define S_IXUSR    00100
#define S_IRWXG    00070
#define S_IRGRP    00040
#define S_IWGRP    00020
#define S_IXGRP    00010
#define S_IRWXO    00007
#define S_IROTH    00004
#define S_IWOTH    00002
#define S_IXOTH    00001

/* macros to check the file type from the mode:
 *
 * S_ISREG    regular file
 * S_ISDIR    directory
 * S_ISCHR    character device
 * S_ISBLK    block device
 * S_ISFIFO   named pipe
 * S_ISLNK    symbolic links
 * S_ISSOCK   socket
 */
#define S_ISREG(m)  (((m) & S_IFMT) == S_IFREG)
#define S_ISDIR(m)  (((m) & S_IFMT) == S_IFDIR)
#define S_ISCHR(m)  (((m) & S_IFMT) == S_IFCHR)
#define S_ISBLK(m)  (((m) & S_IFMT) == S_IFBLK)
#define S_ISFIFO(m) (((m) & S_IFMT) == S_IFIFO)
#define S_ISLNK(m)  (((m) & S_IFMT) == S_IFLNK)
#define S_ISSOCK(m) (((m) & S_IFMT) == S_IFSOCK)

#endif /* _CROCOS_FS_STAT_H */


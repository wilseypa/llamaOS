/* vfs.h
 * 
 * Copyright (C) 2009 Guillaume Duranceau
 * This file is part of CROCOS.
 *
 * This file is distributed under the terms of the GNU General Public License.
 * This license is available in the COPYING file, in the main repository.
 */

/* Virtual File System (VFS):
 * The functions declared here can be used on all files, whether the file is
 * stored on disk or is a special file. File systems supported by CROCOS are:
 * - ext2              : mounted on /
 * - proc file system  : mounted on /proc (in later phases)
 * - device file system: mounted on /dev (in later phases)
 */

#ifndef _CROCOS_FS_VFS_H
#define _CROCOS_FS_VFS_H

#ifdef __cplusplus
extern "C" {
#endif  // __cplusplus

/* initialize the file system: try to mount the disk partition on / */
void fs_initialize ();

/* finalize the file system: try to unmount the disk partition on / */
void fs_finalize ();

/* open a file.
 * flags: bitwise-or'd flags (O_RDONLY, O_WRONLY or O_RDWR)
 * return -EACCES if the requested access is not allowed or if search
 *        permission is denied for one of the directories.
 * return -EISDIR if write access is requested on a directory.
 * return -EIO if a low-level I/O error occured.
 * return -EMFILE if the process reached the maximum number of files opened.
 * return -ENAMETOOLONG if the path is too long.
 * return -ENFILE if the system reached the maximum number of files opened.
 * return -ENOENT if a component in the path is not found.
 * return -ENOTDIR if a component in the path is not a directory.
 * return a file descriptor otherwise (no error) */
int fs_open (const char *path, int flags);

/* close a file descriptor.
 * return -EBADF if fd isn't a valid file descriptor.
 * return 0 otherwise (no error). */
int fs_close (int fd);

/* reposition the offset of an opened file.
 * return -EBADF if fd isn't a valid file descriptor.
 * return -EINVAL if whence is not SEEK_SET, SEEK_CUR or SEEK_END.
 * return -EPIPE if fd is associated with a pipe, socket or FIFO.
 * return the resulting offset otherwise. */
off_t fs_lseek (int fd, off_t offset, int whence);

/* read bytes from an opened file into a buffer.
 * return -EBADF if fd isn't a valid file descriptor.
 * return -EFBIG if the file is too large for the implementation.
 * return -EINVAL if fd is an object which can't be read.
 * return -EISDIR if fd refers to a directory.
 * return -EIO if a low-level I/O error occured.
 * return the number of bytes read otherwise (no error). */
ssize_t fs_read (int fd, void *buf, size_t count);

/* write bytes to an opened file from a buffer.
 * return -EBADF if fd isn't a valid file descriptor.
 * return -EFBIG if the the file size limit is reached.
 * return -EINVAL if fd is an object which can't be written.
 * return -EISDIR if fd refers to a directory.
 * return -EIO if a low-level I/O error occured.
 * return the number of bytes written otherwise (no error). */
ssize_t fs_write (int fd, const void *buf, size_t count);

int fs_get_flags (int fd);

int fs_unlink (const char *path);

#ifdef __cplusplus
}
#endif  // __cplusplus

#if 0
#include "direntry.h"
#include "stat.h"
#include <stddef.h>
#include <stdbool.h>
#include <unistd.h>

/* initialize the file system: try to mount the disk partition on / */
void fs_initialize ();

/* fill the stat buffer with information about a file.
 * return -EACCES if search permission is denied for one of the directories.
 * return -EIO if a low-level I/O error occured.
 * return -ENAMETOOLONG if the path is too long.
 * return -ENOENT if a component in the path is not found.
 * return -ENOTDIR if a component in the path is not a directory.
 * return 0 otherwise (no error). */
int fs_stat (const char *path, struct stat *buf);

/* open a file.
 * flags: bitwise-or'd flags (O_RDONLY, O_WRONLY or O_RDWR)
 * return -EACCES if the requested access is not allowed or if search
 *        permission is denied for one of the directories.
 * return -EISDIR if write access is requested on a directory.
 * return -EIO if a low-level I/O error occured.
 * return -EMFILE if the process reached the maximum number of files opened.
 * return -ENAMETOOLONG if the path is too long.
 * return -ENFILE if the system reached the maximum number of files opened.
 * return -ENOENT if a component in the path is not found.
 * return -ENOTDIR if a component in the path is not a directory.
 * return a file descriptor otherwise (no error) */
int fs_open (const char *path, int flags);

/* close a file descriptor.
 * return -EBADF if fd isn't a valid file descriptor.
 * return 0 otherwise (no error). */
int fs_close (int fd);

/* fill the stat buffer with information about an opened file.
 * return -EBADF if fd isn't a valid file descriptor.
 * return 0 otherwise (no error). */
int fs_fstat (int fd, struct stat *buf);

/* reposition the offset of an opened file.
 * return -EBADF if fd isn't a valid file descriptor.
 * return -EINVAL if whence is not SEEK_SET, SEEK_CUR or SEEK_END.
 * return -EPIPE if fd is associated with a pipe, socket or FIFO.
 * return the resulting offset otherwise. */
off_t fs_lseek (int fd, off_t offset, int whence);

/* read bytes from an opened file into a buffer.
 * return -EBADF if fd isn't a valid file descriptor.
 * return -EFBIG if the file is too large for the implementation.
 * return -EINVAL if fd is an object which can't be read.
 * return -EISDIR if fd refers to a directory.
 * return -EIO if a low-level I/O error occured.
 * return the number of bytes read otherwise (no error). */
ssize_t fs_read (int fd, void *buf, size_t count);

/* write bytes to an opened file from a buffer.
 * return -EBADF if fd isn't a valid file descriptor.
 * return -EFBIG if the the file size limit is reached.
 * return -EINVAL if fd is an object which can't be written.
 * return -EISDIR if fd refers to a directory.
 * return -EIO if a low-level I/O error occured.
 * return the number of bytes written otherwise (no error). */
ssize_t fs_write (int fd, const void *buf, size_t count);

/* read one directory entry from an opened directory.
 * return 1 on success.
 * return 0 on end of directory.
 * return -EBADF if fd isn't a valid file descriptor.
 * return -ENOTDIR if fd doesn't refer to a directory. */
int fs_readdir (int fd, struct direntry *dir);

#endif

#endif /* _CROCOS_FS_VFS_H */


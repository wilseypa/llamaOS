/* direntry.h
 * 
 * Copyright (C) 2009 Guillaume Duranceau
 * This file is part of CROCOS.
 *
 * This file is distributed under the terms of the GNU General Public License.
 * This license is available in the COPYING file, in the main repository.
 */

#ifndef _CROCOS_FS_DIRENTRY_H
#define _CROCOS_FS_DIRENTRY_H

#include <stdint.h>

#define MAX_FILE_NAME_SIZE 255

/* directory entry for readdir syscall */
struct direntry {
    uint32_t inode;                   /* inode number */
    uint32_t name_len;                /* name length */
    char name [MAX_FILE_NAME_SIZE+1]; /* name */
};

#endif /* _CROCOS_FS_DIRENTRY_H */


/* disk.c
 * 
 * Copyright (C) 2009 Guillaume Duranceau
 * This file is part of CROCOS.
 *
 * This file is distributed under the terms of the GNU General Public License.
 * This license is available in the COPYING file, in the main repository.
 */

#include "config.h"
#include "disk.h"
#include "devices/linux.h"
#include "panic.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

unsigned char img [CONFIG_DISK_SIZE]; /* disk image (copied in memory) */

#define init_error(format, ...) \
({  kwarning (format, ##__VA_ARGS__); return false; })
bool disk_initialize () {
    int img_fd; /* disk image file descriptor */
    if ((img_fd = syscall (SYS_open, CONFIG_DISK_IMAGE, linux_O_RDWR)) < 0)
        init_error ("can't open disk image file: " CONFIG_DISK_IMAGE);
    /* copy the file into memory */
    if (syscall (SYS_read, img_fd, img, CONFIG_DISK_SIZE) != CONFIG_DISK_SIZE)
        init_error ("can't copy disk image file (" CONFIG_DISK_IMAGE
            ", %d bytes) in memory ", CONFIG_DISK_SIZE);
    syscall (SYS_close, img_fd);
    return true;
}

bool disk_read (uint64_t off, void *buf, size_t size) {
    memcpy (buf, img + off, size); return true;
}

bool disk_write (uint64_t off, const void *buf, size_t size) {
    memcpy (img + off, buf, size); return true;
}


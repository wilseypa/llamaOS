/* disk.h
 * 
 * Copyright (C) 2009 Guillaume Duranceau
 * This file is part of CROCOS.
 *
 * This file is distributed under the terms of the GNU General Public License.
 * This license is available in the COPYING file, in the main repository.
 */

/* emulate read/write access on a disk. the disk is actually an image file
 * (see CONFIG_DISK_IMAGE macro in config/config.h) copied in memory at
 * startup time: changes are not visible into the image file. */

#ifndef _CROCOS_DEVICES_DISK_H
#define _CROCOS_DEVICES_DISK_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

/* open and copy the disk image file into memory */
bool disk_initialize ();

/* read/write 'size' bytes from/to the disk image (offset 'off).
 * return false in case of IO error. */
bool disk_read (uint64_t off, void *buf, size_t size);
bool disk_write (uint64_t off, const void *buf, size_t size);

#endif /* _CROCOS_DEVICES_DISK_H */


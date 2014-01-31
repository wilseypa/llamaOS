/* panic.h
 * 
 * Copyright (C) 2006-2009 Guillaume Duranceau
 * This file is part of CROCOS.
 *
 * This file is distributed under the terms of the GNU General Public License.
 * This license is available in the COPYING file, in the main repository.
 */

#ifndef _CROCOS_DEVICES_PANIC_H
#define _CROCOS_DEVICES_PANIC_H

#define kpanic(format, ...) \
    do_kpanic (format, __FILE__, __LINE__, __func__, ##__VA_ARGS__)

void do_kpanic (const char *format, const char *file, unsigned int line,
    const char *func, ...);

void kwarning (const char *format, ...);

#endif /* _CROCOS_DEVICES_PANIC_H */


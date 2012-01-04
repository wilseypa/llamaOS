/* Copyright (C) 1991, 1995, 1996, 1997, 2002 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, write to the Free
   Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA
   02111-1307 USA.  */

#include <errno.h>

// define function pointer
typedef void *(*llamaos_brk_t) (void *);

// function pointer variable
static llamaos_brk_t llamaos_brk = 0;

// function called by llamaos to register pointer
int register_llamaos_brk (llamaos_brk_t brk)
{
   llamaos_brk = brk;
}

/* sbrk.c expects this.  */
void *__curbrk = 0;

int __brk (void *addr)
{
   if (0 == llamaos_brk)
   {
      __set_errno (ENOSYS);
      return -1;
   }

   __curbrk = llamaos_brk (addr);

   if (__curbrk < addr)
   {
      __set_errno (ENOMEM);
      return -1;
   }

   return 0;
}
weak_alias (__brk, brk)

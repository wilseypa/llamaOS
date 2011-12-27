/* Copyright (C) 1991,1994-1996,1998,2001,2002,2005,2009,2011
   Free Software Foundation, Inc.
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

/* This function, when passed a string containing an asserted
   expression, a filename, and a line number, prints a message
   on the standard error stream of the form:
	a.c:10: foobar: Assertion `a == b' failed.
   It then aborts program execution via a call to `abort'.  */

#include <assert.h>
#include <libintl.h>

void
__assert_fail_base (const char *fmt, const char *assertion, const char *file,
		    unsigned int line, const char *function)
{
   // !BAM this should stop the os
   for (;;);
}

#undef __assert_fail
void
__assert_fail (const char *assertion, const char *file, unsigned int line,
	       const char *function)
{
  __assert_fail_base (_("%s%s%s:%u: %s%sAssertion `%s' failed.\n%n"),
		      assertion, file, line, function);
}

hidden_def(__assert_fail)

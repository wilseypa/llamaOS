/*
Copyright (c) 2013, William Magato
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

   1. Redistributions of source code must retain the above copyright notice,
      this list of conditions and the following disclaimer.

   2. Redistributions in binary form must reproduce the above copyright notice,
      this list of conditions and the following disclaimer in the documentation
      and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDER(S) AND CONTRIBUTORS ''AS IS''
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER(S) OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

The views and conclusions contained in the software and documentation are those
of the authors and should not be interpreted as representing official policies,
either expressed or implied, of the copyright holder(s) or contributors.
*/

#ifndef glibc_sysdeps_llamaos_bits_ioctl_types_h
#define glibc_sysdeps_llamaos_bits_ioctl_types_h

// #include_next <bits/ioctl-types.h>
/* Structure types for pre-termios terminal ioctls.  Generic Unix version.
   Copyright (C) 1996,1997,2011 Free Software Foundation, Inc.
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
   License along with the GNU C Library; if not, see
   <http://www.gnu.org/licenses/>.  */

#ifndef _SYS_IOCTL_H
# error "Never use <bits/ioctl-types.h> directly; include <sys/ioctl.h> instead."
#endif

#if defined TIOCGETC || defined TIOCSETC
/* Type of ARG for TIOCGETC and TIOCSETC requests.  */
struct tchars
{
  char t_intrc;			/* Interrupt character.  */
  char t_quitc;			/* Quit character.  */
  char t_startc;		/* Start-output character.  */
  char t_stopc;			/* Stop-output character.  */
  char t_eofc;			/* End-of-file character.  */
  char t_brkc;			/* Input delimiter character.  */
};

#define	_IOT_tchars	/* Hurd ioctl type field.  */ \
  _IOT (_IOTS (char), 6, 0, 0, 0, 0)
#endif

#if defined TIOCGLTC || defined TIOCSLTC
/* Type of ARG for TIOCGLTC and TIOCSLTC requests.  */
struct ltchars
{
  char t_suspc;			/* Suspend character.  */
  char t_dsuspc;		/* Delayed suspend character.  */
  char t_rprntc;		/* Reprint-line character.  */
  char t_flushc;		/* Flush-output character.  */
  char t_werasc;		/* Word-erase character.  */
  char t_lnextc;		/* Literal-next character.  */
};

#define	_IOT_ltchars	/* Hurd ioctl type field.  */ \
  _IOT (_IOTS (char), 6, 0, 0, 0, 0)
#endif

/* Type of ARG for TIOCGETP and TIOCSETP requests (and gtty and stty).  */
struct sgttyb
{
  char sg_ispeed;		/* Input speed.  */
  char sg_ospeed;		/* Output speed.  */
  char sg_erase;		/* Erase character.  */
  char sg_kill;			/* Kill character.  */
  short int sg_flags;		/* Mode flags.  */
};

#define	_IOT_sgttyb	/* Hurd ioctl type field.  */ \
  _IOT (_IOTS (char), 4, _IOTS (short int), 1, 0, 0)

#if defined TIOCGWINSZ || defined TIOCSWINSZ
/* Type of ARG for TIOCGWINSZ and TIOCSWINSZ requests.  */
struct winsize
{
  unsigned short int ws_row;	/* Rows, in characters.  */
  unsigned short int ws_col;	/* Columns, in characters.  */

  /* These are not actually used.  */
  unsigned short int ws_xpixel;	/* Horizontal pixels.  */
  unsigned short int ws_ypixel;	/* Vertical pixels.  */
};

#define	_IOT_winsize	/* Hurd ioctl type field.  */ \
  _IOT (_IOTS (unsigned short int), 4, 0, 0, 0, 0)
#endif

#if defined TIOCGSIZE || defined TIOCSSIZE
/* The BSD-style ioctl constructor macros use `sizeof', which can't be used
   in a preprocessor conditional.  Since the commands are always unique
   regardless of the size bits, we can safely define away `sizeof' for the
   purpose of the conditional.  */
#  define sizeof(type) 0
#  if defined TIOCGWINSZ && TIOCGSIZE == TIOCGWINSZ
/* Many systems that have TIOCGWINSZ define TIOCGSIZE for source
   compatibility with Sun; they define `struct ttysize' to have identical
   layout as `struct winsize' and #define TIOCGSIZE to be TIOCGWINSZ
   (likewise TIOCSSIZE and TIOCSWINSZ).  */
struct ttysize
{
  unsigned short int ts_lines;
  unsigned short int ts_cols;
  unsigned short int ts_xxx;
  unsigned short int ts_yyy;
};
#define	_IOT_ttysize	_IOT_winsize
#  else
/* Suns use a different layout for `struct ttysize', and TIOCGSIZE and
   TIOCGWINSZ are separate commands that do the same thing with different
   structures (likewise TIOCSSIZE and TIOCSWINSZ).  */
struct ttysize
{
  int ts_lines, ts_cols;	/* Lines and columns, in characters.  */
};
#  endif
#  undef sizeof			/* See above.  */
#endif

#endif	// glibc_sysdeps_llamaos_bits_ioctl_types_h


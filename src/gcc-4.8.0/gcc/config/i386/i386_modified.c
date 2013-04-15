/* Subroutines used for code generation on IA-32.
   Copyright (C) 1988-2013 Free Software Foundation, Inc.

This file is part of GCC.

GCC is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 3, or (at your option)
any later version.

GCC is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with GCC; see the file COPYING3.  If not see
<http://www.gnu.org/licenses/>.  */

  /* ADCX */
  def_builtin (0, "__builtin_ia32_addcarryx_u32",
	       UCHAR_FTYPE_UCHAR_UINT_UINT_PUNSIGNED, IX86_BUILTIN_ADDCARRYX32);
  def_builtin (OPTION_MASK_ISA_64BIT,
	       "__builtin_ia32_addcarryx_u64",
	       UCHAR_FTYPE_UCHAR_ULONGLONG_ULONGLONG_PULONGLONG,
	       IX86_BUILTIN_ADDCARRYX64);


#
# Copyright (c) 2013, William Magato
# All rights reserved.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions are met:
#
#    1. Redistributions of source code must retain the above copyright notice,
#       this list of conditions and the following disclaimer.
#
#    2. Redistributions in binary form must reproduce the above copyright
#       notice, this list of conditions and the following disclaimer in the
#       documentation and/or other materials provided with the distribution.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDER(S) AND CONTRIBUTORS
# ''AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
# TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
# PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER(S) OR
# CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
# EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
# PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
# OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
# WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
# OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
# ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
# 
# The views and conclusions contained in the software and documentation are
# those of the authors and should not be interpreted as representing official
# policies, either expressed or implied, of the copyright holder(s) or
# contributors.
#

# include common variables
include common-vars.mk
include common-flags.mk

MAKEFILE_SOURCES += sys/gfortran-$(GCC_VERSION).mk

# -iquote/usr/src/gcc-4.8.0/libgfortran/io
CFLAGS += \
  -DHAVE_CONFIG_H \
  -Wall \
  -Wstrict-prototypes \
  -Wmissing-prototypes \
  -Wold-style-definition \
  -Wextra \
  -Wwrite-strings \
  -fcx-fortran-rules \
  -I $(SRCDIR)/sys/gcc-$(GCC_VERSION)/libgfortran \
  -I $(SRCDIR)/sys/gcc-$(GCC_VERSION)/gcc \
  -I $(SRCDIR)/sys/gcc-$(GCC_VERSION)/gcc/config \
  -I $(SRCDIR)/sys/gcc-$(GCC_VERSION)/libquadmath \
  -I $(SRCDIR)/sys/gcc-$(GCC_VERSION)/libgcc \
  -I $(INCDIR)

VPATH = $(SRCDIR)

# needs __S_ISVTX defined
#  sys/gcc-$(GCC_VERSION)/libgfortran/intrinsics/chmod.c

# this is all jacked up
#  sys/gcc-$(GCC_VERSION)/libgfortran/intrinsics/stat.c \

SOURCES = \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/all_l1.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/all_l16.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/all_l2.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/all_l4.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/all_l8.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/any_l1.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/any_l16.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/any_l2.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/any_l4.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/any_l8.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/bessel_r10.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/bessel_r16.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/bessel_r4.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/bessel_r8.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/count_16_l.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/count_1_l.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/count_2_l.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/count_4_l.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/count_8_l.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/cshift0_c10.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/cshift0_c16.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/cshift0_c4.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/cshift0_c8.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/cshift0_i1.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/cshift0_i16.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/cshift0_i2.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/cshift0_i4.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/cshift0_i8.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/cshift0_r10.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/cshift0_r16.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/cshift0_r4.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/cshift0_r8.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/cshift1_16.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/cshift1_4.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/cshift1_8.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/eoshift1_16.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/eoshift1_4.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/eoshift1_8.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/eoshift3_16.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/eoshift3_4.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/eoshift3_8.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/exponent_r10.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/exponent_r16.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/exponent_r4.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/exponent_r8.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/fraction_r10.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/fraction_r16.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/fraction_r4.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/fraction_r8.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/iall_i1.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/iall_i16.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/iall_i2.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/iall_i4.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/iall_i8.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/iany_i1.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/iany_i16.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/iany_i2.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/iany_i4.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/iany_i8.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/in_pack_c10.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/in_pack_c16.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/in_pack_c4.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/in_pack_c8.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/in_pack_i1.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/in_pack_i16.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/in_pack_i2.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/in_pack_i4.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/in_pack_i8.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/in_pack_r10.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/in_pack_r16.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/in_pack_r4.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/in_pack_r8.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/in_unpack_c10.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/in_unpack_c16.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/in_unpack_c4.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/in_unpack_c8.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/in_unpack_i1.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/in_unpack_i16.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/in_unpack_i2.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/in_unpack_i4.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/in_unpack_i8.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/in_unpack_r10.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/in_unpack_r16.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/in_unpack_r4.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/in_unpack_r8.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/iparity_i1.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/iparity_i16.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/iparity_i2.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/iparity_i4.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/iparity_i8.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/matmul_c10.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/matmul_c16.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/matmul_c4.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/matmul_c8.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/matmul_i1.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/matmul_i16.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/matmul_i2.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/matmul_i4.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/matmul_i8.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/matmul_l16.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/matmul_l4.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/matmul_l8.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/matmul_r10.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/matmul_r16.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/matmul_r4.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/matmul_r8.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/maxloc0_16_i1.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/maxloc0_16_i16.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/maxloc0_16_i2.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/maxloc0_16_i4.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/maxloc0_16_i8.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/maxloc0_16_r10.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/maxloc0_16_r16.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/maxloc0_16_r4.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/maxloc0_16_r8.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/maxloc0_4_i1.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/maxloc0_4_i16.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/maxloc0_4_i2.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/maxloc0_4_i4.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/maxloc0_4_i8.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/maxloc0_4_r10.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/maxloc0_4_r16.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/maxloc0_4_r4.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/maxloc0_4_r8.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/maxloc0_8_i1.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/maxloc0_8_i16.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/maxloc0_8_i2.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/maxloc0_8_i4.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/maxloc0_8_i8.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/maxloc0_8_r10.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/maxloc0_8_r16.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/maxloc0_8_r4.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/maxloc0_8_r8.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/maxloc1_16_i1.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/maxloc1_16_i16.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/maxloc1_16_i2.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/maxloc1_16_i4.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/maxloc1_16_i8.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/maxloc1_16_r10.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/maxloc1_16_r16.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/maxloc1_16_r4.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/maxloc1_16_r8.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/maxloc1_4_i1.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/maxloc1_4_i16.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/maxloc1_4_i2.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/maxloc1_4_i4.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/maxloc1_4_i8.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/maxloc1_4_r10.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/maxloc1_4_r16.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/maxloc1_4_r4.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/maxloc1_4_r8.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/maxloc1_8_i1.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/maxloc1_8_i16.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/maxloc1_8_i2.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/maxloc1_8_i4.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/maxloc1_8_i8.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/maxloc1_8_r10.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/maxloc1_8_r16.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/maxloc1_8_r4.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/maxloc1_8_r8.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/maxval_i1.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/maxval_i16.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/maxval_i2.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/maxval_i4.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/maxval_i8.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/maxval_r10.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/maxval_r16.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/maxval_r4.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/maxval_r8.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/minloc0_16_i1.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/minloc0_16_i16.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/minloc0_16_i2.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/minloc0_16_i4.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/minloc0_16_i8.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/minloc0_16_r10.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/minloc0_16_r16.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/minloc0_16_r4.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/minloc0_16_r8.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/minloc0_4_i1.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/minloc0_4_i16.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/minloc0_4_i2.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/minloc0_4_i4.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/minloc0_4_i8.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/minloc0_4_r10.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/minloc0_4_r16.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/minloc0_4_r4.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/minloc0_4_r8.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/minloc0_8_i1.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/minloc0_8_i16.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/minloc0_8_i2.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/minloc0_8_i4.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/minloc0_8_i8.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/minloc0_8_r10.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/minloc0_8_r16.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/minloc0_8_r4.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/minloc0_8_r8.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/minloc1_16_i1.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/minloc1_16_i16.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/minloc1_16_i2.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/minloc1_16_i4.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/minloc1_16_i8.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/minloc1_16_r10.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/minloc1_16_r16.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/minloc1_16_r4.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/minloc1_16_r8.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/minloc1_4_i1.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/minloc1_4_i16.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/minloc1_4_i2.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/minloc1_4_i4.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/minloc1_4_i8.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/minloc1_4_r10.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/minloc1_4_r16.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/minloc1_4_r4.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/minloc1_4_r8.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/minloc1_8_i1.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/minloc1_8_i16.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/minloc1_8_i2.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/minloc1_8_i4.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/minloc1_8_i8.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/minloc1_8_r10.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/minloc1_8_r16.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/minloc1_8_r4.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/minloc1_8_r8.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/minval_i1.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/minval_i16.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/minval_i2.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/minval_i4.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/minval_i8.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/minval_r10.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/minval_r16.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/minval_r4.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/minval_r8.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/nearest_r10.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/nearest_r16.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/nearest_r4.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/nearest_r8.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/norm2_r10.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/norm2_r16.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/norm2_r4.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/norm2_r8.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/pack_c10.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/pack_c16.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/pack_c4.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/pack_c8.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/pack_i1.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/pack_i16.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/pack_i2.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/pack_i4.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/pack_i8.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/pack_r10.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/pack_r16.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/pack_r4.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/pack_r8.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/parity_l1.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/parity_l16.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/parity_l2.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/parity_l4.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/parity_l8.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/pow_c10_i16.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/pow_c10_i4.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/pow_c10_i8.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/pow_c16_i16.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/pow_c16_i4.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/pow_c16_i8.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/pow_c4_i16.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/pow_c4_i4.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/pow_c4_i8.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/pow_c8_i16.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/pow_c8_i4.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/pow_c8_i8.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/pow_i16_i16.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/pow_i16_i4.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/pow_i16_i8.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/pow_i4_i16.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/pow_i4_i4.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/pow_i4_i8.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/pow_i8_i16.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/pow_i8_i4.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/pow_i8_i8.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/pow_r10_i16.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/pow_r10_i8.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/pow_r16_i16.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/pow_r16_i4.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/pow_r16_i8.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/pow_r4_i16.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/pow_r4_i8.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/pow_r8_i16.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/pow_r8_i8.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/product_c10.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/product_c16.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/product_c4.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/product_c8.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/product_i1.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/product_i16.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/product_i2.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/product_i4.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/product_i8.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/product_r10.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/product_r16.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/product_r4.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/product_r8.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/reshape_c10.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/reshape_c16.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/reshape_c4.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/reshape_c8.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/reshape_i16.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/reshape_i4.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/reshape_i8.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/reshape_r10.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/reshape_r16.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/reshape_r4.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/reshape_r8.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/rrspacing_r10.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/rrspacing_r16.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/rrspacing_r4.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/rrspacing_r8.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/set_exponent_r10.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/set_exponent_r16.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/set_exponent_r4.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/set_exponent_r8.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/shape_i16.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/shape_i4.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/shape_i8.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/spacing_r10.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/spacing_r16.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/spacing_r4.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/spacing_r8.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/spread_c10.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/spread_c16.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/spread_c4.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/spread_c8.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/spread_i1.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/spread_i16.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/spread_i2.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/spread_i4.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/spread_i8.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/spread_r10.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/spread_r16.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/spread_r4.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/spread_r8.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/sum_c10.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/sum_c16.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/sum_c4.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/sum_c8.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/sum_i1.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/sum_i16.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/sum_i2.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/sum_i4.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/sum_i8.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/sum_r10.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/sum_r16.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/sum_r4.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/sum_r8.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/transpose_c10.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/transpose_c16.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/transpose_c4.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/transpose_c8.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/transpose_i16.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/transpose_i4.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/transpose_i8.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/transpose_r10.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/transpose_r16.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/transpose_r4.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/transpose_r8.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/unpack_c10.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/unpack_c16.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/unpack_c4.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/unpack_c8.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/unpack_i1.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/unpack_i16.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/unpack_i2.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/unpack_i4.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/unpack_i8.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/unpack_r10.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/unpack_r16.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/unpack_r4.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/generated/unpack_r8.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/intrinsics/abort.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/intrinsics/access.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/intrinsics/args.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/intrinsics/associated.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/intrinsics/bit_intrinsics.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/intrinsics/c99_functions.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/intrinsics/chdir.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/intrinsics/clock.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/intrinsics/cpu_time.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/intrinsics/cshift0.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/intrinsics/ctime.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/intrinsics/date_and_time.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/intrinsics/dtime.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/intrinsics/env.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/intrinsics/eoshift0.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/intrinsics/eoshift2.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/intrinsics/erfc_scaled.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/intrinsics/etime.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/intrinsics/execute_command_line.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/intrinsics/exit.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/intrinsics/extends_type_of.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/intrinsics/fnum.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/intrinsics/gerror.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/intrinsics/getXid.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/intrinsics/getcwd.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/intrinsics/getlog.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/intrinsics/hostnm.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/intrinsics/ierrno.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/intrinsics/ishftc.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/intrinsics/iso_c_binding.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/intrinsics/iso_c_generated_procs.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/intrinsics/kill.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/intrinsics/link.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/intrinsics/malloc.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/intrinsics/move_alloc.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/intrinsics/mvbits.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/intrinsics/pack_generic.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/intrinsics/perror.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/intrinsics/rand.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/intrinsics/random.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/intrinsics/rename.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/intrinsics/reshape_generic.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/intrinsics/reshape_packed.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/intrinsics/selected_char_kind.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/intrinsics/signal.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/intrinsics/size.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/intrinsics/sleep.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/intrinsics/spread_generic.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/intrinsics/string_intrinsics.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/intrinsics/symlnk.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/intrinsics/system.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/intrinsics/system_clock.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/intrinsics/time.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/intrinsics/transpose_generic.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/intrinsics/umask.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/intrinsics/unlink.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/intrinsics/unpack_generic.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/io/close.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/io/fbuf.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/io/file_pos.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/io/format.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/io/inquire.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/io/intrinsics.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/io/list_read.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/io/lock.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/io/open.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/io/read.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/io/size_from_kind.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/io/transfer.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/io/transfer128.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/io/unit.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/io/unix.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/io/write.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/runtime/backtrace.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/runtime/bounds.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/runtime/compile_options.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/runtime/convert_char.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/runtime/environ.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/runtime/error.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/runtime/fpu.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/runtime/in_pack_generic.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/runtime/in_unpack_generic.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/runtime/main.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/runtime/memory.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/runtime/pause.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/runtime/select.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/runtime/stop.c \
  sys/gcc-$(GCC_VERSION)/libgfortran/runtime/string.c

OBJECTS  = $(SOURCES:%.c=$(OBJDIR)/%.o)
DEPENDS += $(OBJECTS:%.o=%.d)

.PHONY: all
all : $(LIBDIR)/sys/gfortran.a

$(LIBDIR)/sys/gfortran.a: $(OBJECTS)
	@[ -d $(@D) ] || (mkdir -p $(@D))
	@echo linking: $@
	@$(AR) r $@ $(OBJECTS)
	@echo successfully built: $@
	@echo

include rules.mk

# include auto-generated dependencies
-include $(DEPENDS)





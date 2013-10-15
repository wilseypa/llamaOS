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

MAKEFILE_SOURCES += tools/blas.mk

F77FLAGS += 

VPATH = $(SRCDIR)

SOURCES = \
  tools/blas/caxpy.f \
  tools/blas/ccopy.f \
  tools/blas/cdotc.f \
  tools/blas/cdotu.f \
  tools/blas/cgbmv.f \
  tools/blas/cgemm.f \
  tools/blas/cgemv.f \
  tools/blas/cgerc.f \
  tools/blas/cgeru.f \
  tools/blas/chbmv.f \
  tools/blas/chemm.f \
  tools/blas/chemv.f \
  tools/blas/cher.f \
  tools/blas/cher2.f \
  tools/blas/cher2k.f \
  tools/blas/cherk.f \
  tools/blas/chpmv.f \
  tools/blas/chpr.f \
  tools/blas/chpr2.f \
  tools/blas/crotg.f \
  tools/blas/cscal.f \
  tools/blas/csrot.f \
  tools/blas/csscal.f \
  tools/blas/cswap.f \
  tools/blas/csymm.f \
  tools/blas/csyr2k.f \
  tools/blas/csyrk.f \
  tools/blas/ctbmv.f \
  tools/blas/ctbsv.f \
  tools/blas/ctpmv.f \
  tools/blas/ctpsv.f \
  tools/blas/ctrmm.f \
  tools/blas/ctrmv.f \
  tools/blas/ctrsm.f \
  tools/blas/ctrsv.f \
  tools/blas/dasum.f \
  tools/blas/daxpy.f \
  tools/blas/dcabs1.f \
  tools/blas/dcopy.f \
  tools/blas/ddot.f \
  tools/blas/dgbmv.f \
  tools/blas/dgemm.f \
  tools/blas/dgemv.f \
  tools/blas/dger.f \
  tools/blas/dnrm2.f \
  tools/blas/drot.f \
  tools/blas/drotg.f \
  tools/blas/drotm.f \
  tools/blas/drotmg.f \
  tools/blas/dsbmv.f \
  tools/blas/dscal.f \
  tools/blas/dsdot.f \
  tools/blas/dspmv.f \
  tools/blas/dspr.f \
  tools/blas/dspr2.f \
  tools/blas/dswap.f \
  tools/blas/dsymm.f \
  tools/blas/dsymv.f \
  tools/blas/dsyr.f \
  tools/blas/dsyr2.f \
  tools/blas/dsyr2k.f \
  tools/blas/dsyrk.f \
  tools/blas/dtbmv.f \
  tools/blas/dtbsv.f \
  tools/blas/dtpmv.f \
  tools/blas/dtpsv.f \
  tools/blas/dtrmm.f \
  tools/blas/dtrmv.f \
  tools/blas/dtrsm.f \
  tools/blas/dtrsv.f \
  tools/blas/dzasum.f \
  tools/blas/dznrm2.f \
  tools/blas/icamax.f \
  tools/blas/idamax.f \
  tools/blas/isamax.f \
  tools/blas/izamax.f \
  tools/blas/lsame.f \
  tools/blas/sasum.f \
  tools/blas/saxpy.f \
  tools/blas/scabs1.f \
  tools/blas/scasum.f \
  tools/blas/scnrm2.f \
  tools/blas/scopy.f \
  tools/blas/sdot.f \
  tools/blas/sdsdot.f \
  tools/blas/sgbmv.f \
  tools/blas/sgemm.f \
  tools/blas/sgemv.f \
  tools/blas/sger.f \
  tools/blas/snrm2.f \
  tools/blas/srot.f \
  tools/blas/srotg.f \
  tools/blas/srotm.f \
  tools/blas/srotmg.f \
  tools/blas/ssbmv.f \
  tools/blas/sscal.f \
  tools/blas/sspmv.f \
  tools/blas/sspr.f \
  tools/blas/sspr2.f \
  tools/blas/sswap.f \
  tools/blas/ssymm.f \
  tools/blas/ssymv.f \
  tools/blas/ssyr.f \
  tools/blas/ssyr2.f \
  tools/blas/ssyr2k.f \
  tools/blas/ssyrk.f \
  tools/blas/stbmv.f \
  tools/blas/stbsv.f \
  tools/blas/stpmv.f \
  tools/blas/stpsv.f \
  tools/blas/strmm.f \
  tools/blas/strmv.f \
  tools/blas/strsm.f \
  tools/blas/strsv.f \
  tools/blas/xerbla.f \
  tools/blas/zaxpy.f \
  tools/blas/zcopy.f \
  tools/blas/zdotc.f \
  tools/blas/zdotu.f \
  tools/blas/zdrot.f \
  tools/blas/zdscal.f \
  tools/blas/zgbmv.f \
  tools/blas/zgemm.f \
  tools/blas/zgemv.f \
  tools/blas/zgerc.f \
  tools/blas/zgeru.f \
  tools/blas/zhbmv.f \
  tools/blas/zhemm.f \
  tools/blas/zhemv.f \
  tools/blas/zher.f \
  tools/blas/zher2.f \
  tools/blas/zher2k.f \
  tools/blas/zherk.f \
  tools/blas/zhpmv.f \
  tools/blas/zhpr.f \
  tools/blas/zhpr2.f \
  tools/blas/zrotg.f \
  tools/blas/zscal.f \
  tools/blas/zswap.f \
  tools/blas/zsymm.f \
  tools/blas/zsyr2k.f \
  tools/blas/zsyrk.f \
  tools/blas/ztbmv.f \
  tools/blas/ztbsv.f \
  tools/blas/ztpmv.f \
  tools/blas/ztpsv.f \
  tools/blas/ztrmm.f \
  tools/blas/ztrmv.f \
  tools/blas/ztrsm.f \
  tools/blas/ztrsv.f

OBJECTS = $(SOURCES:%.f=$(OBJDIR)/%.o)
DEPENDS += $(OBJECTS:%.o=%.d)

.PHONY: all
all : $(LIBDIR)/tools/blas.a

$(LIBDIR)/tools/blas.a: $(OBJECTS)
	@[ -d $(@D) ] || (mkdir -p $(@D))
	@echo linking: $@
	@$(AR) r $@ $^
	@echo successfully built: $@
	@echo

include rules.mk

# include auto-generated dependencies
-include $(DEPENDS)

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

MAKEFILE_SOURCES += tools/cblas.mk

CFLAGS += \
  -I $(SRCDIR)/tools/cblas/include

VPATH = $(SRCDIR)

SOURCES = \
  tools/cblas/src/cblas_caxpy.c \
  tools/cblas/src/cblas_ccopy.c \
  tools/cblas/src/cblas_cdotc_sub.c \
  tools/cblas/src/cblas_cdotu_sub.c \
  tools/cblas/src/cblas_cgbmv.c \
  tools/cblas/src/cblas_cgemm.c \
  tools/cblas/src/cblas_cgemv.c \
  tools/cblas/src/cblas_cgerc.c \
  tools/cblas/src/cblas_cgeru.c \
  tools/cblas/src/cblas_chbmv.c \
  tools/cblas/src/cblas_chemm.c \
  tools/cblas/src/cblas_chemv.c \
  tools/cblas/src/cblas_cher.c \
  tools/cblas/src/cblas_cher2.c \
  tools/cblas/src/cblas_cher2k.c \
  tools/cblas/src/cblas_cherk.c \
  tools/cblas/src/cblas_chpmv.c \
  tools/cblas/src/cblas_chpr.c \
  tools/cblas/src/cblas_chpr2.c \
  tools/cblas/src/cblas_cscal.c \
  tools/cblas/src/cblas_csscal.c \
  tools/cblas/src/cblas_cswap.c \
  tools/cblas/src/cblas_csymm.c \
  tools/cblas/src/cblas_csyr2k.c \
  tools/cblas/src/cblas_csyrk.c \
  tools/cblas/src/cblas_ctbmv.c \
  tools/cblas/src/cblas_ctbsv.c \
  tools/cblas/src/cblas_ctpmv.c \
  tools/cblas/src/cblas_ctpsv.c \
  tools/cblas/src/cblas_ctrmm.c \
  tools/cblas/src/cblas_ctrmv.c \
  tools/cblas/src/cblas_ctrsm.c \
  tools/cblas/src/cblas_ctrsv.c \
  tools/cblas/src/cblas_dasum.c \
  tools/cblas/src/cblas_daxpy.c \
  tools/cblas/src/cblas_dcopy.c \
  tools/cblas/src/cblas_ddot.c \
  tools/cblas/src/cblas_dgbmv.c \
  tools/cblas/src/cblas_dgemm.c \
  tools/cblas/src/cblas_dgemv.c \
  tools/cblas/src/cblas_dger.c \
  tools/cblas/src/cblas_dnrm2.c \
  tools/cblas/src/cblas_drot.c \
  tools/cblas/src/cblas_drotg.c \
  tools/cblas/src/cblas_drotm.c \
  tools/cblas/src/cblas_drotmg.c \
  tools/cblas/src/cblas_dsbmv.c \
  tools/cblas/src/cblas_dscal.c \
  tools/cblas/src/cblas_dsdot.c \
  tools/cblas/src/cblas_dspmv.c \
  tools/cblas/src/cblas_dspr.c \
  tools/cblas/src/cblas_dspr2.c \
  tools/cblas/src/cblas_dswap.c \
  tools/cblas/src/cblas_dsymm.c \
  tools/cblas/src/cblas_dsymv.c \
  tools/cblas/src/cblas_dsyr.c \
  tools/cblas/src/cblas_dsyr2.c \
  tools/cblas/src/cblas_dsyr2k.c \
  tools/cblas/src/cblas_dsyrk.c \
  tools/cblas/src/cblas_dtbmv.c \
  tools/cblas/src/cblas_dtbsv.c \
  tools/cblas/src/cblas_dtpmv.c \
  tools/cblas/src/cblas_dtpsv.c \
  tools/cblas/src/cblas_dtrmm.c \
  tools/cblas/src/cblas_dtrmv.c \
  tools/cblas/src/cblas_dtrsm.c \
  tools/cblas/src/cblas_dtrsv.c \
  tools/cblas/src/cblas_dzasum.c \
  tools/cblas/src/cblas_dznrm2.c \
  tools/cblas/src/cblas_globals.c \
  tools/cblas/src/cblas_icamax.c \
  tools/cblas/src/cblas_idamax.c \
  tools/cblas/src/cblas_isamax.c \
  tools/cblas/src/cblas_izamax.c \
  tools/cblas/src/cblas_sasum.c \
  tools/cblas/src/cblas_saxpy.c \
  tools/cblas/src/cblas_scasum.c \
  tools/cblas/src/cblas_scnrm2.c \
  tools/cblas/src/cblas_scopy.c \
  tools/cblas/src/cblas_sdot.c \
  tools/cblas/src/cblas_sdsdot.c \
  tools/cblas/src/cblas_sgbmv.c \
  tools/cblas/src/cblas_sgemm.c \
  tools/cblas/src/cblas_sgemv.c \
  tools/cblas/src/cblas_sger.c \
  tools/cblas/src/cblas_snrm2.c \
  tools/cblas/src/cblas_srot.c \
  tools/cblas/src/cblas_srotg.c \
  tools/cblas/src/cblas_srotm.c \
  tools/cblas/src/cblas_srotmg.c \
  tools/cblas/src/cblas_ssbmv.c \
  tools/cblas/src/cblas_sscal.c \
  tools/cblas/src/cblas_sspmv.c \
  tools/cblas/src/cblas_sspr.c \
  tools/cblas/src/cblas_sspr2.c \
  tools/cblas/src/cblas_sswap.c \
  tools/cblas/src/cblas_ssymm.c \
  tools/cblas/src/cblas_ssymv.c \
  tools/cblas/src/cblas_ssyr.c \
  tools/cblas/src/cblas_ssyr2.c \
  tools/cblas/src/cblas_ssyr2k.c \
  tools/cblas/src/cblas_ssyrk.c \
  tools/cblas/src/cblas_stbmv.c \
  tools/cblas/src/cblas_stbsv.c \
  tools/cblas/src/cblas_stpmv.c \
  tools/cblas/src/cblas_stpsv.c \
  tools/cblas/src/cblas_strmm.c \
  tools/cblas/src/cblas_strmv.c \
  tools/cblas/src/cblas_strsm.c \
  tools/cblas/src/cblas_strsv.c \
  tools/cblas/src/cblas_xerbla.c \
  tools/cblas/src/cblas_zaxpy.c \
  tools/cblas/src/cblas_zcopy.c \
  tools/cblas/src/cblas_zdotc_sub.c \
  tools/cblas/src/cblas_zdotu_sub.c \
  tools/cblas/src/cblas_zdscal.c \
  tools/cblas/src/cblas_zgbmv.c \
  tools/cblas/src/cblas_zgemm.c \
  tools/cblas/src/cblas_zgemv.c \
  tools/cblas/src/cblas_zgerc.c \
  tools/cblas/src/cblas_zgeru.c \
  tools/cblas/src/cblas_zhbmv.c \
  tools/cblas/src/cblas_zhemm.c \
  tools/cblas/src/cblas_zhemv.c \
  tools/cblas/src/cblas_zher.c \
  tools/cblas/src/cblas_zher2.c \
  tools/cblas/src/cblas_zher2k.c \
  tools/cblas/src/cblas_zherk.c \
  tools/cblas/src/cblas_zhpmv.c \
  tools/cblas/src/cblas_zhpr.c \
  tools/cblas/src/cblas_zhpr2.c \
  tools/cblas/src/cblas_zscal.c \
  tools/cblas/src/cblas_zswap.c \
  tools/cblas/src/cblas_zsymm.c \
  tools/cblas/src/cblas_zsyr2k.c \
  tools/cblas/src/cblas_zsyrk.c \
  tools/cblas/src/cblas_ztbmv.c \
  tools/cblas/src/cblas_ztbsv.c \
  tools/cblas/src/cblas_ztpmv.c \
  tools/cblas/src/cblas_ztpsv.c \
  tools/cblas/src/cblas_ztrmm.c \
  tools/cblas/src/cblas_ztrmv.c \
  tools/cblas/src/cblas_ztrsm.c \
  tools/cblas/src/cblas_ztrsv.c \
  tools/cblas/src/xerbla.c

HEADERS = \
  tools/cblas/include/cblas.h \
  tools/cblas/include/cblas_f77.h

OBJECTS = $(SOURCES:%.c=$(OBJDIR)/%.o)
DEPENDS = $(OBJECTS:%.o=%.d)

.PHONY: all
all : $(LIBDIR)/tools/cblas.a headers

.PHONY: headers
headers : $(HEADERS)

$(LIBDIR)/tools/cblas.a: $(OBJECTS)
	@[ -d $(@D) ] || (mkdir -p $(@D))
	@echo linking: $@
	@$(AR) r $@ $^
	@echo successfully built: $@
	@echo

$(INCDIR)/% : $(SRCDIR)/tools/cblas/include/%
	@[ -d $(@D) ] || (mkdir -p $(@D))
	@echo copying: $@ from $<
	cp $< $@

include rules.mk

# include auto-generated dependencies
-include $(DEPENDS)


MAKE_SOURCES = glibc.mk common.mk rules.mk

include common.mk

CFLAGS += -include glibc/include/libc-symbols.h -include stdbool.h \
          -DHAVE_MREMAP=0 -D'LOCALEDIR=""' -D'GCONV_PATH=""' -D'GCONV_DIR=""' -D'LOCALE_ALIAS_PATH=""'

INCLUDES = \
  glibc/include \
  glibc/sysdeps/llamaos \
  glibc/sysdeps/llamaos/elf \
  glibc/sysdeps/x86_64 \
  glibc/sysdeps/x86_64/fpu \
  glibc/sysdeps/ieee754/ldbl-128 \
  glibc/sysdeps/ieee754 \
  glibc/sysdeps/generic \
  glibc/elf \
  glibc/iconv \
  glibc/libio \
  glibc/stdlib \
  glibc/string \
  glibc/wcsmbs \
  glibc \
  gcc/include

CFLAGS += $(INCLUDES:%=-I %)

VPATH = glibc

SOURCES = \
  ctype/ctype-info.c \
  ctype/ctype.c \
  ctype/ctype_l.c \
  csu/dso_handle.c \
  debug/fortify_fail.c \
  debug/readonly-area.c \
  iconv/gconv.c \
  iconv/gconv_builtin.c \
  iconv/gconv_cache.c \
  iconv/gconv_close.c \
  iconv/gconv_conf.c \
  iconv/gconv_db.c \
  iconv/gconv_dl.c \
  iconv/gconv_open.c \
  iconv/gconv_simple.c \
  iconv/gconv_trans.c \
  intl/dcgettext.c \
  intl/dcigettext.c \
  intl/explodename.c \
  intl/finddomain.c \
  intl/hash-string.c \
  intl/l10nflist.c \
  intl/loadmsgcat.c \
  intl/localealias.c \
  intl/plural.c \
  intl/plural-exp.c \
  io/access.c \
  io/close.c \
  io/fxstat.c \
  io/fxstat64.c \
  io/getcwd.c \
  io/isatty.c \
  io/open.c \
  io/read.c \
  io/write.c \
  io/xstat.c \
  io/xstat64.c \
  libio/filedoalloc.c \
  libio/fileno.c \
  libio/fileops.c \
  libio/fputc.c \
  libio/fseek.c \
  libio/ftello.c \
  libio/genops.c \
  libio/iofclose.c \
  libio/iofgets.c \
  libio/iofflush.c \
  libio/iofopen.c \
  libio/iofputs.c \
  libio/iofread.c \
  libio/iofwide.c \
  libio/iofwrite.c \
  libio/iogetdelim.c \
  libio/iogetline.c \
  libio/iopadn.c \
  libio/ioseekoff.c \
  libio/iovsprintf.c \
  libio/iovsscanf.c \
  libio/iowpadn.c \
  libio/stdfiles.c \
  libio/stdio.c \
  libio/strops.c \
  libio/vscanf.c \
  libio/vsnprintf.c \
  libio/wfiledoalloc.c \
  libio/wfileops.c \
  libio/wgenops.c \
  locale/C-address.c \
  locale/C-collate.c \
  locale/C-ctype.c \
  locale/C-identification.c \
  locale/C-measurement.c \
  locale/C-messages.c \
  locale/C-monetary.c \
  locale/C-name.c \
  locale/C-numeric.c \
  locale/C-paper.c \
  locale/C-telephone.c \
  locale/C-time.c \
  locale/C_name.c \
  locale/coll-lookup.c \
  locale/findlocale.c \
  locale/fpathconf.c \
  locale/global-locale.c \
  locale/lc-ctype.c \
  locale/loadarchive.c \
  locale/loadlocale.c \
  locale/localename.c \
  locale/mb_cur_max.c \
  locale/setlocale.c \
  locale/SYS_libc.c \
  locale/xlocale.c \
  malloc/malloc.c \
  malloc/morecore.c \
  misc/init-misc.c \
  misc/lseek.c \
  misc/madvise.c \
  misc/mmap.c \
  misc/mmap64.c \
  misc/mprotect.c \
  misc/munmap.c \
  misc/sbrk.c \
  misc/tsearch.c \
  posix/confstr.c \
  posix/environ.c \
  posix/getegid.c \
  posix/geteuid.c \
  posix/getgid.c \
  posix/getuid.c \
  posix/pathconf.c \
  stdio-common/_itoa.c \
  stdio-common/fprintf.c \
  stdio-common/fxprintf.c \
  stdio-common/itoa-digits.c \
  stdio-common/itoa-udigits.c \
  stdio-common/itowa-digits.c \
  stdio-common/printf_fp.c \
  stdio-common/printf_fphex.c \
  stdio-common/printf-parsemb.c \
  stdio-common/printf-parsewc.c \
  stdio-common/reg-modifier.c \
  stdio-common/reg-printf.c \
  stdio-common/reg-type.c \
  stdio-common/snprintf.c \
  stdio-common/sprintf.c \
  stdio-common/sscanf.c \
  stdio-common/vfprintf.c \
  stdio-common/vfscanf.c \
  stdio-common/vfwprintf.c \
  stdlib/add_n.c \
  stdlib/addmul_1.c \
  stdlib/bsearch.c \
  stdlib/cmp.c \
  stdlib/cxa_atexit.c \
  stdlib/divrem.c \
  stdlib/fpioconst.c \
  stdlib/getenv.c \
  stdlib/grouping.c \
  stdlib/lshift.c \
  stdlib/msort.c \
  stdlib/mul.c \
  stdlib/mul_1.c \
  stdlib/mul_n.c \
  stdlib/qsort.c \
  stdlib/rshift.c \
  stdlib/setenv.c \
  stdlib/strtod.c \
  stdlib/strtod_l.c \
  stdlib/strtof.c \
  stdlib/strtof_l.c \
  stdlib/strtold.c \
  stdlib/sub_n.c \
  stdlib/submul_1.c \
  stdlib/tens_in_limb.c \
  string/_strerror.c \
  string/argz-addsep.c \
  string/argz-append.c \
  string/argz-count.c \
  string/argz-create.c \
  string/argz-ctsep.c \
  string/argz-delete.c \
  string/argz-extract.c \
  string/argz-insert.c \
  string/argz-next.c \
  string/argz-replace.c \
  string/argz-stringify.c \
  string/bcopy.c \
  string/bzero.c \
  string/memccpy.c \
  string/memchr.c \
  string/memcmp.c \
  string/memcpy.c \
  string/memfrob.c \
  string/memmem.c \
  string/memmove.c \
  string/mempcpy.c \
  string/memrchr.c \
  string/memset.c \
  string/rawmemchr.c \
  string/stpcpy.c \
  string/stpncpy.c \
  string/strcasecmp.c \
  string/strcasecmp_l.c \
  string/strcasestr.c \
  string/strcat.c \
  string/strchr.c \
  string/strchrnul.c \
  string/strcmp.c \
  string/strcoll.c \
  string/strcoll_l.c \
  string/strcpy.c \
  string/strdup.c \
  string/strerror.c \
  string/strerror_l.c \
  string/strlen.c \
  string/strncase.c \
  string/strncase_l.c \
  string/strncat.c \
  string/strncmp.c \
  string/strncpy.c \
  string/strndup.c \
  string/strnlen.c \
  string/strrchr.c \
  string/strsep.c \
  string/strstr.c \
  string/strtok.c \
  string/strtok_r.c \
  string/strxfrm.c \
  string/strxfrm_l.c \
  string/swab.c \
  string/wordcopy.c \
  sysdeps/ieee754/dbl-64/word-64/s_isinf.c \
  sysdeps/ieee754/dbl-64/word-64/s_isnan.c \
  sysdeps/ieee754/dbl-64/dbl2mpn.c \
  sysdeps/ieee754/dbl-64/mpn2dbl.c \
  sysdeps/ieee754/flt-32/mpn2flt.c \
  sysdeps/ieee754/ldbl-64-128/strtold_l.c \
  sysdeps/ieee754/ldbl-128/ldbl2mpn.c \
  sysdeps/ieee754/ldbl-128/mpn2ldbl.c \
  sysdeps/ieee754/ldbl-128/s_isinfl.c \
  sysdeps/ieee754/ldbl-128/s_isnanl.c \
  sysdeps/llamaos/elf/enbl-secure.c \
  sysdeps/llamaos/elf/dl-libc.c \
  sysdeps/llamaos/elf/dl-profstub.c \
  sysdeps/llamaos/posix/sysconf.c \
  sysdeps/llamaos/abort.c \
  sysdeps/llamaos/assert.c \
  sysdeps/llamaos/brk.c \
  sysdeps/llamaos/errlist.c \
  sysdeps/llamaos/errno.c \
  sysdeps/llamaos/getpagesize.c \
  sysdeps/llamaos/init-first.c \
  sysdeps/llamaos/libc_fatal.c \
  sysdeps/wordsize-64/strtol.c \
  sysdeps/wordsize-64/strtol_l.c \
  sysdeps/wordsize-64/strtoul.c \
  sysdeps/wordsize-64/strtoul_l.c \
  time/alt_digit.c \
  time/era.c \
  time/lc-time-cleanup.c \
  time/localtime.c \
  time/mktime.c \
  time/offtime.c \
  time/strftime.c \
  time/strftime_l.c \
  time/tzfile.c \
  time/tzset.c \
  time/wcsftime.c \
  time/wcsftime_l.c \
  wcsmbs/btowc.c \
  wcsmbs/mbrlen.c \
  wcsmbs/mbrtowc.c \
  wcsmbs/mbsnrtowcs.c \
  wcsmbs/mbsrtowcs.c \
  wcsmbs/mbsrtowcs_l.c \
  wcsmbs/wcpcpy.c \
  wcsmbs/wcpncpy.c \
  wcsmbs/wcrtomb.c \
  wcsmbs/wcschr.c \
  wcsmbs/wcschrnul.c \
  wcsmbs/wcscmp.c \
  wcsmbs/wcscoll.c \
  wcsmbs/wcscoll_l.c \
  wcsmbs/wcslen.c \
  wcsmbs/wcsnlen.c \
  wcsmbs/wcsmbsload.c \
  wcsmbs/wcsrtombs.c \
  wcsmbs/wcsxfrm.c \
  wcsmbs/wcsxfrm_l.c \
  wcsmbs/wctob.c \
  wcsmbs/wmemchr.c \
  wcsmbs/wmemcmp.c \
  wcsmbs/wmemcpy.c \
  wcsmbs/wmemmove.c \
  wcsmbs/wmempcpy.c \
  wcsmbs/wmemset.c \
  wctype/iswctype.c \
  wctype/towctrans.c \
  wctype/wcfuncs.c \
  wctype/wcfuncs_l.c \
  wctype/wctype.c \
  wctype/wctrans.c

BINARY  = glibc.a
OBJECTS = $(SOURCES:%.c=$(OBJDIR)/%.o)
DEPENDS = $(OBJECTS:%.o=%.d)

$(LIBDIR)/$(BINARY) : $(OBJECTS)
	@[ -d $(@D) ] || (mkdir -p $(@D))
	@echo linking: $@
	@$(AR) r $@ $(OBJECTS)
	@echo successfully built: $@
	@echo

include rules.mk

# include auto-generated dependencies
ifneq ($(MAKECMDGOALS),clean)
-include $(DEPENDS)
endif

/* config.h.  Generated from config.h.in by configure.  */
#if !defined __ASSEMBLER__ && !defined _ISOMAC && !defined __OPTIMIZE__
# error "glibc cannot be compiled without optimization"
#endif

/* Another evil option when it comes to compiling the C library is
   --ffast-math since it alters the ABI.  */
#if defined __FAST_MATH__ && !defined TEST_FAST_MATH
# error "glibc must not be compiled with -ffast-math"
#endif

/* Define if using ELF, which supports weak symbols.
   This implies HAVE_ASM_WEAK_DIRECTIVE and NO_UNDERSCORES; set by
   --with-elf.  */
#define HAVE_ELF 1

/* Define if C symbols are asm symbols.  Don't define if C symbols
   have a `_' prepended to make the asm symbol.  */
#define NO_UNDERSCORES 1

/* Define if weak symbols are available via the `.weak' directive.  */
#define HAVE_ASM_WEAK_DIRECTIVE 1


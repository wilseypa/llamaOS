
#include <errno.h>
#include <libintl.h>

#ifndef ERR_REMAP
# define ERR_REMAP(n) n
#endif

#ifdef ERR_MAX
# define ERRLIST_SIZE ERR_MAX + 1
#else
# define ERRLIST_SIZE
#endif
const char *const _sys_errlist_internal[ERRLIST_SIZE] =
  {
    [0] = N_("Success"),
  };

#define NERR \
  (sizeof _sys_errlist_internal / sizeof _sys_errlist_internal [0])
const int _sys_nerr_internal = NERR;

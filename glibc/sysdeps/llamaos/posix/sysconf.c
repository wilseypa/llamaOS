
#include <errno.h>

long int
__sysconf (name)
     int name;
{
  __set_errno (ENOSYS);
  return -1;
}

stub_warning (sysconf)
#include <stub-tag.h>
weak_alias (__sysconf, sysconf)

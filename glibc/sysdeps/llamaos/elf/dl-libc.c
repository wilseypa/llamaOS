
#include <errno.h>

void *
__libc_dlopen_mode (const char *name, int mode)
{
  __set_errno (ENOSYS);
}
// libc_hidden_def (__libc_dlopen_mode)
stub_warning (libc_dlopen_mode)
#include <stub-tag.h>
weak_alias (__libc_dlopen_mode, libc_dlopen_mode)

void *
__libc_dlsym (void *map, const char *name)
{
  __set_errno (ENOSYS);
}
// libc_hidden_def (__libc_dlsym)
stub_warning (libc_dlsym)
#include <stub-tag.h>
weak_alias (__libc_dlsym, libc_dlsym)

int
__libc_dlclose (void *map)
{
  __set_errno (ENOSYS);
}
// libc_hidden_def (__libc_dlclose)
stub_warning (libc_dlclose)
#include <stub-tag.h>
weak_alias (__libc_dlclose, libc_dlclose)

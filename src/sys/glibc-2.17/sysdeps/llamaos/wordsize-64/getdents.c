#define __getdents64 __no___getdents64_decl
// !BAM
// #include <sysdeps/unix/sysv/linux/getdents.c>
#include "../getdents.c"
#undef __getdents64
weak_alias (__getdents, __getdents64);

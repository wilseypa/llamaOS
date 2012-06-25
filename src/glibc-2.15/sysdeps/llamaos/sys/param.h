

#ifndef llamaos_sys_param_h
#define llamaos_sys_param_h

#include_next<sys/param.h>

#define powerof2(x)      ((((x) - 1) & (x)) == 0)

#endif  // llamaos_sys_param_h

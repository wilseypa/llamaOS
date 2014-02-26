
#include <stdint.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>

#include <llamaos/xen/fs/ext2/panic.h>

static char buffer [512] = { '\0' };

void do_kpanic (const char *format, const char *file, unsigned int line,
    const char *func, ...)
{
   // prep variable arguments
   va_list arg;
   va_start (arg, func);

   // copy formatted output to buffer
   int count = vsnprintf (buffer, sizeof(buffer)-1, format, arg);

   // term variable arguments
   va_end (arg);

   if ((count > 0) && (count < sizeof(buffer)))
   {
      printf("%s:%d (%s): ", file, line, func);
      printf(buffer);
      printf("\n");
   }
}

void kwarning (const char *format, ...)
{
   // prep variable arguments
   va_list arg;
   va_start (arg, format);

   // copy formatted output to buffer
   int count = vsnprintf (buffer, sizeof(buffer)-1, format, arg);

   // term variable arguments
   va_end (arg);

   if ((count > 0) && (count < sizeof(buffer)))
   {
      printf(buffer);
      printf("\n");
   }
}

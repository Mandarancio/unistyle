#include "unistring.h"

#include <stdlib.h>

#include <stdarg.h>
#include <stdio.h>

UniStr*
unistr_new (void)
{
  UniStr * str = malloc(sizeof(UniStr));
  str->size = 0;
  str->data = malloc(sizeof(char));
  str->data[0] = 0;
  return str;
}

void
unistr_puts (UniStr *str,
      char   *data)
{
  size_t n = strlen(data);
  if (n)
  {
    size_t s = n + str->size + 1;
    str->data = realloc(str->data, s*sizeof(char));
    memcpy(str->data + str->size, data, n);
    str->data[s-1] = 0;
    str->size = s - 1;
  }
}

void
unistr_printf (UniStr *str,
               const char *fmt,
               ...)
{
  va_list ap;
  int n;
  char buff[1024];
  va_start(ap, fmt);

  n = vsnprintf(buff, 1024, fmt, ap);

  va_end(ap);

  if (n < 0) {
     	return;
  }
  unistr_puts(str, buff);
}

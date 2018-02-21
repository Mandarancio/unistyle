#ifndef __UNI_STRING_H__
#define __UNI_STRING_H__

#include <string.h>

struct UniStr
{
  char * data;
  size_t size;
} typedef UniStr;

UniStr    *unistr_new    (void);
void       unistr_puts   (UniStr *str,
                          char   *data);
void       unistr_printf (UniStr *str,
                          const char *fmt,
                          ...);

#endif

#include <asm/uaccess.h>
#include <string.h>
unsigned long copy_to_user(void *to, const void *from, unsigned long n)
{
   char *dst = (char *)to;
   const char *src = (const char *)from;
   memcpy(dst, src, n);
   return 0;
}
unsigned long copy_from_user(void *to, const void *from, unsigned long n)
{
    char *dst = (char *)to;
    const char *src = (const char *)from;
    memcpy(dst, src, n);
    return 0;
}


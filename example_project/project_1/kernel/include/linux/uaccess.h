#define __uaccess_h
#ifdef __uaccess_h
#include <asm/uaccess.h>

unsigned long copy_to_user(void *to, const void *from, unsigned long n);
unsigned long copy_from_user(void *to, const void *from, unsigned long n);

#endif
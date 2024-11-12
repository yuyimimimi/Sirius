#include <stdbool.h>
#include <stdlib.h>
#include <stdarg.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <reent.h>
#include <sys/fcntl.h>
#include "sdkconfig.h"
#include "esp_rom_uart.h"
#include "esp_console.h"
#include "linux/errno.h"


int __attribute__((weak)) system(const char* str)
{
    int a = 0;
    int *i =&a;
    int err = esp_console_run(str,i);
    if(err == 0 )
    return 0;
    else
    return -1;
}


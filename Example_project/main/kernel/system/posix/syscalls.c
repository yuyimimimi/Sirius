

/*
 * SPDX-FileCopyrightText: 2015-2022 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

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

int system(const char* str) {
    int a = 0;
    int *i = &a;
    esp_console_run(str, i);  
    return 0;  
}

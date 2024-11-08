#ifndef __APP_INSTALL_H__
#define __APP_INSTALL_H__

#include <linux/module.h>
#include "esp_console.h"

void add_console_app(char* name , esp_console_cmd_func_t func, char* help,...);


#endif /* __APP_INSTALL_H__ */
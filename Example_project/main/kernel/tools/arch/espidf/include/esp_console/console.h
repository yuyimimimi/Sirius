#define __CONSOLE_H__
#ifdef __CONSOLE_H__
#include "esp_console.h"

void init_normal_console(void);
void init_console_recovery_mode(void);
void add_console_app(char* name , esp_console_cmd_func_t func, char* help,...);

#endif
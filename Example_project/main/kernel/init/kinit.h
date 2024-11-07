#ifndef __INIT_H__
#define __INIT_H__
#include <stdio.h>
#include <linux/init.h>
#include <linux/module.h>
void start_console(void);
void __init __init__(void);
void app_main(){printf("\n\n\n\n\n\n\n\n\n\n\n");  start_console();}
module_init(__init__);
#endif

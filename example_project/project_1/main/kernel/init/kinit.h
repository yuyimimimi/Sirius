#ifndef __INIT_H__
#define __INIT_H__
#include <linux/init.h>
#include <linux/module.h>
void start_console(void);


void __init __init__(void);
module_init(__init__);
void app_main(){start_console();}

#endif

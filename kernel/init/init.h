#ifndef __INIT_H__
#define __INIT_H__
#include <linux/init.h>
#include <linux/module.h>
void start_console(void);


void __init __init__(void);
void __init __attribute__((constructor)) init(void)
{
    __init__();
}

void app_main(){ start_console();}// 发送系统界面启动信号



#endif

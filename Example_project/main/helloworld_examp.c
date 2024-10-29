#include "stdio.h"

int helloworld(int argc, char **argv){   
    if(argc > 1)
    {
        printf("Hello World%s!\n", argv[1]);
        return 0;
    }
    else
    printf("Hello World!\n");

    return 0;
}


#include "app_install.h"
void add_i2cdetect_console_app(void)
{
    add_console_app("helloworld",helloworld,"print 'hello world'");    //程序名称，函数指针，帮助信息,可变参数
}


//add two lines into main.c,This module can install into system console app list.

//将下方注释的两行放入main.c中就可以将helloworld程序安装到系统控制台程序列表中。可以使用helloworld + 参数 进行调用。

// void add_i2cdetect_console_app(void)
// AppInit_init(add_i2cdetect_console_app);
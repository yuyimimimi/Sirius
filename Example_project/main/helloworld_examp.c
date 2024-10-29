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
    add_console_app("helloworld",helloworld,"print 'hello world'");
}


//add two lines into main.c,This module can install into system console app list.
// void add_i2cdetect_console_app(void)
// AppInit_init(add_i2cdetect_console_app);
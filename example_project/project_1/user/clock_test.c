#include "stdio.h"
static int start_main(int argc, char *argv[])
{
    int i = 1;
    while(i< 10000){ 
        i++;
    }
    printf("i:%d\n", i);
    return 0;
}



#include "app_install.h"
void add_clock_tets_console_app(void)
{
    add_console_app("loop_test", start_main, "test");
}


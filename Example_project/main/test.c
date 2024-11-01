#include <stdio.h>



int test_main(int argc, char const *argv[])
{
    printf("just for test!\n");
    return 0;
}


#include <app_install.h>
void install_test()
{
    add_console_app("test", test_main, "test_main");
}

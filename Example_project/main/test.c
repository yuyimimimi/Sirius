#include <stdio.h>


int test_main(int argc, char const *argv[])
{
    system("echo Hello World!");
    system("echo 8 > /dev/gpioexport");
    system("echo out > /dev/gpio-8/d");
    system("echo 1 > /dev/gpio-8/v");
    return 0;
}


#include <app_install.h>
void install_test()
{
    add_console_app("test", test_main, "test_main");
}

#include <stdio.h>


int test_main(int argc, char const *argv[])
{
    if(argc < 2)
    {
        return 0;
    }
    system(argv[1]);
    printf("test_main\n");

    return 0;
}


#include <app_install.h>
void install_test()
{
    add_console_app("test", test_main, "test_main");
}

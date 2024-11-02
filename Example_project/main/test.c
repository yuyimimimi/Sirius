#include <stdio.h>


int test_main(int argc, char const *argv[])
{
    system("echo Hello World!");
    system("echo 8 > /dev/gpioexport");
    system("echo out > /dev/gpio-8/d");
    system("echo 1 > /dev/gpio-8/v");
    return 0;
}

int test_2_main(int argc, char const *argv[])   //示例2和1实现相同功能
{
    printf("Hello World!\n");
    FILE *fp;
    fp = fopen("/dev/gpioexport", "w");
    if (fp == NULL) {
        printf("open /dev/gpioexport failed\n");
        return -1;
    }
    fprintf(fp, "8");
    fclose(fp);
    fp = fopen("/dev/gpio-8/d", "w");
    if (fp == NULL) {
        printf("open /dev/gpio-8/d failed\n");
        return -1;
    }
    fprintf(fp, "out");
    fclose(fp);
    fp = fopen("/dev/gpio-8/v", "w");
    if (fp == NULL) {
        printf("open /dev/gpio-8/v failed\n");
        return -1;
    }
    fprintf(fp, "1");
    fclose(fp);
    return 0;
}

#include <app_install.h>
void install_test()
{
    add_console_app("test", test_main, "test_main");
    add_console_app("test_2", test_2_main, "test_2_main");
}

AppInit_init(install_test);

#include <stdio.h>
#include <time.h>

int date_command(int argc, char *argv[]) {
    time_t t;
    struct tm *tm_info;

    time(&t);
    tm_info = localtime(&t);

    printf("Current date and time: %s", asctime(tm_info));
    return 0;
}


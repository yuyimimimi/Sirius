#include <stdio.h>
#include <unistd.h>

int sleep_command(int argc, char **argv) {
    if(argc!= 2) {
    printf("Usage: sleep <seconds>\n");
    return 1;
    }
    int seconds = atoi(argv[1]);
    sleep(seconds);
return 0;
};
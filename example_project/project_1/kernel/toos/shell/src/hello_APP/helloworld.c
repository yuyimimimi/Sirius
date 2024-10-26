#include "stdio.h"

int helloworld(int argc, char **argv){   
    if(argc > 1)
    {
        printf("Hello %s!\n", argv[1]);
        return 0;
    }
    else
    printf("Hello World!\n");
    return 0;
}



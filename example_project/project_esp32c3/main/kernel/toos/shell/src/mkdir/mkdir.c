#include <console_cop.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

int mkdir_cmd(int argc,char **argv)
{
    int needfree = 0;
    if (argc < 2) {
        return 0;
    }
    char * path = argv[1]; 
    if(path[0]!='/')
    {
        char *this_path = get_console_path();
        char *new_path = malloc(strlen(this_path) + strlen(path) + 2);
        needfree = 1;
        strcpy(new_path, this_path);
        strcat(new_path, "/");
        strcat(new_path, argv[1]);
        path = new_path;
    }
    if(mkdir(path, 0777)!=0)
    {
        printf("mkdir %s failed\n", path);
    }
    if(needfree)
    {
        free(path);
    }

    return 0;
}
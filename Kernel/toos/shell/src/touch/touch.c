#include <stdio.h>
#include <console_cop.h>
#include <string.h>


int touch_cmd(int argc, char *argv[])
{
    if(argc < 2)
    {
        return 0;
    }
    char *console_path = get_console_path();

    int need_free_path = 0;
    char *path_1 = argv[1];
    if(path_1 == NULL){
        return 0;
    }
    else if(path_1[0] != '/')
    {
        char *new_path = malloc(strlen(path_1) + strlen(console_path) + 2);
        strcpy(new_path, console_path);
        new_path[strlen(console_path)] = '/';
        strcpy(new_path + strlen(console_path) + 1, path_1);
        new_path[strlen(console_path) + strlen(path_1) + 1] = '\0';
        need_free_path = 1;
        path_1 = new_path;
    }

    FILE *fp = fopen(path_1, "w");
    if(fp == NULL)
    {
        printf("touch: cannot open file %s\n", path_1);
        return 1;
    }
    fclose(fp);

    if(need_free_path)
    {
        free(path_1);
    }
    return 0;
}
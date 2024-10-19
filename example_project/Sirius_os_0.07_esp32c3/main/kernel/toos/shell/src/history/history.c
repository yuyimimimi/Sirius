#include <stdio.h>
#include "env.h"
int history_cmd(int argc, char **argv)
{

    char *path = getenv_("shell_home");
    if(path == NULL)
    {
        printf("Shell home not set\n");
        printf("Please set the 'shell home' in /etc/profile or ~/.bashrc\n");
        return 1;
    }  
    char *data;
    size_t size;
    FILE *fp = fopen(path, "r");
    if(fp == NULL)
    {
        perror("Failed to open file");
        printf("Shell home: %s\n", path);
        return 0;
    }
    else
    {
        fseek(fp, 0, SEEK_END);
        size = ftell(fp);
        fseek(fp, 0, SEEK_SET);

        data = (char*)malloc(1+size);
        if (data == NULL) {
            perror("Failed to allocate memory");
            fclose(fp);
            return 1;
        }
        fread(data, 1, size, fp);
        fclose(fp);
        data[size] = '\0'; 
        printf("%s", data);
        free(data);
        return 0;
    }
    free(path);
}

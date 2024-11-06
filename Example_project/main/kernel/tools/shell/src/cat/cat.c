#include <stdio.h>
#include <lwip/sockets.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <unistd.h>
#include <console_cop.h>

int cat_main(int arg,char **argv)
{
    int needfree = 0;
    if (arg < 2) {
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
    
    char *data;
    size_t size;
    FILE *fp = fopen(path, "r");
    if(fp == NULL)
    {   
        perror("Failed to open file");
        printf("File name is %s\n",path);
        return -1;
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
    }

    printf("\n%s\n>>%s\n",data,path);
    free(data);
    
    if(needfree)
        free(path);
    return 0;
}



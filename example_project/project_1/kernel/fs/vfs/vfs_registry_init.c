#include <registry.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cJSON.h>
#include <linux/vfs/vfs.h>
#include <dirent.h>


static char *path = vfs_swap_path;
static char *path_str = NULL;

void init_vfs_registry(void)
{
    char *register_path = get_registry_path();
    printf("register_path = %s\n", register_path);

    path_str = malloc(strlen(register_path) + strlen(path) + 2);
    strcpy(path_str, register_path);  
    strcat(path_str + strlen(register_path), path);
    path_str[strlen(register_path) + strlen(path)+1] = '\0';

    cJSON *root = cJSON_CreateObject();
    cJSON_AddStringToObject(root, "type"        , "dir");   
    cJSON_AddStringToObject(root, "name"        , "/"  );
    cJSON_AddNumberToObject(root, "number", 0  );
    char *json_str = cJSON_Print(root);

    FILE *fp = fopen(path_str, "w");
    if(fp == NULL)
    {
        printf("Failed to create file %s\n", path_str);
        printf("please check at /kernel/fs/vfs/add_file.c\n");
        while (1){}
    }
    fwrite(json_str, 1, strlen(json_str), fp);
    fclose(fp);
    free(json_str);
    cJSON_Delete(root);
    printf("vfs registry init success\n");
}

char *get_vfs_registry_path(void)
{
    return path_str;
}






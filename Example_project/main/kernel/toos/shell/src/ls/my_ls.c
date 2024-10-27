#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <esp_fs/espfs.h>
#include <fnmatch.h>
#include <dirent.h>
#include <console_cop.h>
#include <sys/stat.h>
#include "cJSON.h"
#include <linux/vfs/vfs.h>

#define setTextColor printf

static char * console_path;            //控制台当前路径
int ls_main(int arg,char **argv)
{ 

    console_path = get_console_path();

    uint8_t cmd_of_l = 0;
    uint8_t cmd_of_a = 0;
    uint8_t need_free_path = 0;
    char *path_1 = NULL;
    char *args;
    //解析命令行参数
    for(int i = 1; i < arg; i++)                     //遍历命令行参数
    {
        args = argv[i];
        if( args[0] == '-'){         //如果有命令  
            for(int j = 1; args[j]!= '\0'; j++){
                if(args[j] == 'l'){
                    cmd_of_l = 1;
                }
                else if(args[j] == 'a'){
                    cmd_of_a = 1;
                }
            }
        }
        else
        {
            if(path_1 == NULL){
                path_1 = argv[i];
            }
        }
    }
    
    if(path_1 == NULL)
    {
        path_1 = console_path;
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
    



uint8_t fs_slect = 0;  
uint8_t registry = 0;
    //查询文件系统
struct dirent *entry;
DIR *dir = opendir(path_1);
    if(dir != NULL)
    {  
        fs_slect = 1;
        while ((entry = readdir(dir)) != NULL) {
            if(cmd_of_l==1)
             printf("%-5d", entry->d_ino);

                if(entry->d_type == DT_DIR)
                {
                    setTextColor("\033[36m");
                    printf(" %-20s", entry->d_name);   
                    setTextColor("\033[37m"); 
                }
                else if (entry->d_type == DT_REG)
                {
                    printf(" %-20s", entry->d_name);
                }
                // else if (entry->d_type == DT_LNK)   //使用esp32c3时，此处会报错，可以直接标注为注释，只会影响颜色显示
                // {
                //     setTextColor("\033[36m");  // 青色
                //     printf(" %-20s", entry->d_name);
                //     setTextColor("\033[37m"); 
                // }
                else{
                    setTextColor("\033[31m");  // 红色
                    printf(" %-15s", entry->d_name);
                    setTextColor("\033[37m"); 
                }                   
                if(cmd_of_l == 1){
                    printf("%-10d\n", entry->d_ino);
                }
        }
         if(cmd_of_l!=1)
         printf("\n");
        closedir(dir);
    }

    //查询注册表     ls /dev

    cJSON *rootnode =  get_vfs_registry_root();
    cJSON *json = get_vfs_node_file(path_1,rootnode);    
    if(json == NULL)
    {
        if((fs_slect == 0)&&(registry == 0))
        {
            printf("No such file or directory\n");
        }
    }
    else
    {
        cJSON *current_node = cJSON_GetObjectItem(json , "type");
        if(strcmp(current_node->valuestring, "dir") == 0)
        {
            json = cJSON_GetObjectItem(json , "child");
            while (json != NULL)
            {
                current_node = cJSON_GetObjectItem(json , "type");
                if(strcmp(current_node->valuestring, "dir") == 0)
                {
                    current_node = cJSON_GetObjectItem(json , "name");
                   setTextColor("\033[36m");
                    printf("%-20s", current_node->valuestring);
                    setTextColor("\033[37m");
                }
                else if(strcmp(current_node->valuestring, "device") == 0)
                {
                    current_node = cJSON_GetObjectItem(json , "name");
                    setTextColor("\033[33m"); 
                    printf("%-20s", current_node->valuestring);
                    setTextColor("\033[37m"); 
                }
                else if(strcmp(current_node->valuestring, "mount_point") == 0)
                {
                    current_node = cJSON_GetObjectItem(json , "name");
                   setTextColor("\033[36m");
                    printf("%-20s", current_node->valuestring);
                    setTextColor("\033[37m"); 
                }
                else
                {
                    current_node = cJSON_GetObjectItem(json , "name");
                    setTextColor("\033[32m");  
                    printf("%-20s", current_node->valuestring);
                    setTextColor("\033[37m"); 
                }
                if(cmd_of_l == 1)
                {
                     current_node = cJSON_GetObjectItem(json , "number");
                     if(current_node != NULL)
                     printf("%10d\n", current_node->valueint);
                }
                json = cJSON_GetObjectItem(json , "next");
            }
            if(cmd_of_l != 1)
                printf("\n");
        }
        else
        {
            if((fs_slect == 0)&&(registry == 0))
            {
                printf("No such file or directory\n");
            }
        }
    }
    cJSON_Delete(rootnode);
    if(need_free_path == 1){
        free(path_1);
    }
    return 0;
}



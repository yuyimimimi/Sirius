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
#include "env.h"

#define setTextColor printf
void print_file_permissions(mode_t mode) {
    // 打印文件权限
    printf("%c", (S_ISDIR(mode)) ? 'd' : '-');
    printf("%c", (mode & S_IRUSR) ? 'r' : '-');
    printf("%c", (mode & S_IWUSR) ? 'w' : '-');
    printf("%c", (mode & S_IXUSR) ? 'x' : '-');
    printf("%c", (mode & S_IRGRP) ? 'r' : '-');
    printf("%c", (mode & S_IWGRP) ? 'w' : '-');
    printf("%c", (mode & S_IXGRP) ? 'x' : '-');
    printf("%c", (mode & S_IROTH) ? 'r' : '-');
    printf("%c", (mode & S_IWOTH) ? 'w' : '-');
    printf("%c", (mode & S_IXOTH) ? 'x' : '-');
}




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
        struct stat file_stat;
        fs_slect = 1;

        while ((entry = readdir(dir)) != NULL) {
            char full_path[1024];
            snprintf(full_path, sizeof(full_path), "%s/%s", path_1, entry->d_name);

            // 如果是 -l 参数，获取并打印文件的详细信息
            if (cmd_of_l == 1) {
                if (stat(full_path, &file_stat) == 0) {
                
                    // 打印文件权限
                    print_file_permissions(file_stat.st_mode);
                    printf("  ");
                    printf("%-3d", entry->d_ino);
                    printf("null   null ");
                    printf("%8ld   ", file_stat.st_size);
                    // 打印最后修改时间戳
                    char time_str[100];
                    struct tm *tm_info = localtime(&file_stat.st_mtime);
                    strftime(time_str, sizeof(time_str), "%b   %d   %H:%M", tm_info);
                    printf("%-16s", time_str);
                }
                else 
                {
                    perror("stat error");
                    continue;
                }
            }

            if (entry->d_type == DT_DIR) {
                setTextColor("\033[36m");  // 目录名用青色
                if (cmd_of_l == 1)
                {
                printf("  %s/", entry->d_name);                   
                }
                else
                printf(" %10s", entry->d_name);
                setTextColor("\033[37m");  // 恢复默认颜色
            } else if (entry->d_type == DT_REG) {
                if (cmd_of_l == 1)
                {
                printf("  %s", entry->d_name);  // 普通文件
                }
                 else
                printf(" %10s", entry->d_name);  // 普通文件
            } else {
                setTextColor("\033[31m");  // 红色
                if (cmd_of_l == 1)
                {
                printf("  %s", entry->d_name);  // 普通文件
                }
                else
                printf(" %10s", entry->d_name);  // 其他类型的文件
                setTextColor("\033[37m");  // 恢复默认颜色
            }
            if (cmd_of_l == 1) {
                printf("\n");
            }
        }
        if (cmd_of_l != 1) {
            printf("\n");
        }

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



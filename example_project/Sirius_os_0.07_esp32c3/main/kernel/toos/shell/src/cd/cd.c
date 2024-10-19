#include <stdio.h>
#include <console_cop.h>
#include <sys/stat.h>
#include <string.h>
#include <cJSON.h>
#include <linux/vfs/vfs.h>
#include <dirent.h>
#include "env.h"

int  cd_cmd(int argc, char **argv) 
{
    if(argc == 1)
    {
        return 0;
    }
    if(argc == 2)
    {
    char *pwd = get_console_path();
       
        char *path = argv[1];        
        if(path[0] == '.' && path[1] == '.'){ 
        
            int len = strlen(pwd)-1;
            while (pwd[len] != '/'){
                pwd[len] = '\0';
                len--;
            }
            pwd[len] = '\0'; 
            if(pwd[0] == '\0'){                // 根目录不能回退
                set_console_path("/");
                return 0;
            }
            set_console_path(pwd);
            return 0;
        }
        else if(path[0] == '.') {
            char *home_path = getenv_("HOME");
            set_console_path(home_path);
            free(home_path);
            return 0;
        }
        else if(path[0] == '~') {
            char *home_path = getenv_("HOME");
            set_console_path(home_path);
            free(home_path);
            return 0;
        }


        int need_free = 0;
        if(path[0] != '/')                // 转化为绝对路径
        {
            char *new_path = malloc(strlen(pwd)+strlen(path) + 2);
            strcpy(new_path, pwd);
            if(new_path[strlen(new_path)-1] == '/')
            {
                strcpy(new_path + strlen(pwd), path);
                new_path[strlen(pwd) + strlen(path)] = '\0';
            }
            else
            {
                new_path[strlen(pwd)] = '/';
                strcpy(new_path + strlen(pwd) + 1, path);
                new_path[strlen(pwd) + strlen(path) + 1] = '\0';
            }
            need_free = 1;
            path = new_path;   
        }
        else 
        {
          path = argv[1];
        }

        struct stat statbuf;
        if (stat(path, &statbuf) == 0)      // 判断路径是否存在
        {
            DIR *dir = opendir(path);
            if(dir != NULL)
            {
                closedir(dir);
                set_console_path(path);
                if(need_free == 1)
                free(path);
                return 0;
            }
        }

        cJSON *rootnode =  get_vfs_registry_root();
        cJSON *json = get_vfs_node_file(path,rootnode); 
        if(json == NULL)
        {
            printf("No such file or directory\n");     
        }
        else
        {
            cJSON *current_node = cJSON_GetObjectItem(json , "type");
            if(strcmp(current_node->valuestring, "dir") == 0){
                set_console_path(path);
            }
            else{
                printf("No such file or directory\n");
            }      
        }
        cJSON_Delete(rootnode);
        if(need_free == 1)
        {
            free(path);
        }
    }
    return 0;
}




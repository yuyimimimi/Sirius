#include <linux/vfs/vfs.h>
#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <cJSON.h>
#include <unistd.h>
#include <stdarg.h> 

static int get_dir_name(char *path, char *dir_name,int nunber) //获取指定目录中指定位置的目录名
{
    int i = 0;
    int j = 0;
    while (path[i]!= '\0'){
        if(path[i] == '/')
        j++;
        if(j == nunber)
        goto a;
        i++;
    }
    return -1;
    a:
    i++;
    j = 0;
    while (path[i+j]!= '\0'){
       dir_name[j] = path[i+j];
       if(path[i+j] == '/')
       break;
       j++;
    }
    dir_name[j] = '\0';
    return 0;
}


static int get_dir_number(char *path)                       //获取指定目录的层级数
{
    int j = 0;
    int i = 0;
    while (path[j]!= '\0'){
        if(path[j] == '/')
        i++;
        j++;
    }
    return i;
}



static cJSON *select_dir(char *path_name, cJSON *dir_node) // 按照命名查找目录节点 
{
    cJSON *node = cJSON_GetObjectItem(dir_node, "child");
    cJSON *get_node = NULL;
    while (node != NULL) {
        get_node = cJSON_GetObjectItem(node, "name");
        if(get_node == NULL){
            return NULL;
        }
        if (strcmp(path_name, get_node->valuestring) == 0){
            return node; // 找到匹配的节点
        }
        node =cJSON_GetObjectItem(node, "next");// 移动到下一个节点
    }
    return NULL; // 没有找到匹配的节点
}



int create_vfs_node_file(char *path, char *type ,unsigned int dev_id,...) //创建文件节点
{

        char new_path[100];
        va_list args;
        va_start(args, dev_id);
        vsnprintf(new_path, 100, path, args);
        va_end(args);
        path = new_path;
        
        char *path_of_dat = get_vfs_registry_path();
        int times = 0;
    oprnfile:
        FILE *fp = fopen(path_of_dat, "r");               
        if(fp == NULL){
            times++;
            if(times > 20){
                printf("device is busy\n");
                return -1;
            }
            usleep(1000);
            goto oprnfile;
        }
        fseek(fp, 0, SEEK_END);
        size_t size = ftell(fp);
        fseek(fp, 0, SEEK_SET);
        char  *buf = (char *)malloc(size+1);
        if(buf == NULL){
            printf("malloc buf failed\n");
            return -1;
        }
        fread(buf, 1, size, fp);
        buf[size] ='\0';
        cJSON *root = cJSON_Parse(buf);
        free(buf);
        int dir_number = get_dir_number(path); //获取指定目录的层级数    
        char dir_name[100];                    //获取指定目录中指定位置的目录名
        cJSON *dir_node = root;                
        cJSON *get_node ;
        cJSON *new_node ;
        for(int i = 1; i <= dir_number; i++){
            get_dir_name(path, dir_name, i);
            get_node = select_dir(dir_name, dir_node);
            if(get_node == NULL)
            {
                new_node = cJSON_CreateObject();
                if(dir_number == i){
                    cJSON_AddStringToObject(new_node,"type",type); 
                    cJSON_AddNumberToObject(new_node,"number",dev_id ); 
                }
                else{
                    cJSON_AddStringToObject(new_node, "type" ,"dir"); 
                    cJSON_AddNumberToObject(new_node, "number", 0  ); 
                }
                cJSON_AddStringToObject(new_node, "name"         ,  dir_name); 

                get_node =cJSON_GetObjectItem(dir_node, "child");
                if(cJSON_IsObject(get_node))
                { 
                    while (cJSON_IsObject(cJSON_GetObjectItem(get_node, "next")))
                    {
                         get_node = cJSON_GetObjectItem(get_node, "next");
                    }
                    cJSON_AddItemToObject(get_node, "next", new_node);              
                }
                else
                {
                    cJSON_AddItemToObject(dir_node, "child", new_node);
                }
                dir_node = new_node;
            }
            else
            {
                dir_node = get_node;
            }
        }
        char *new_buf = cJSON_Print(root);
        fclose(fp);
        fp = fopen(path_of_dat, "w");
        if(fp == NULL)
        {
            printf("open file failed\n");
            return -1;
        }
        fprintf(fp, "%s", new_buf);
        fclose(fp);
        free(new_buf);
        cJSON_Delete(root);
        return 0;
}




 //cat /etc/system/registry/fs.dat
//ls /dev

cJSON *get_vfs_registry_root()
{
    //get_data_from_file
    char *path_of_dat = get_vfs_registry_path();
    int times = 0;
    oprnfile:
    FILE *fp = fopen(path_of_dat, "r");               
    if(fp == NULL)
    {
        times++;
        if(times > 20)
        {
            printf("device is busy\n");
            return NULL;
        }
        usleep(10000);
        goto oprnfile;
    }
    fseek(fp, 0, SEEK_END);
    size_t size = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    char  *buf = (char *)malloc(size+1);
    if(buf == NULL)
    {
        printf("malloc buf failed\n");
        return NULL;
    }
    fread(buf, 1, size, fp);
    fclose(fp);
    buf[size] ='\0';
    cJSON *root = cJSON_Parse(buf);
    free(buf);
    return root;
}

cJSON *get_vfs_node_file(char *path,cJSON *rootnode) 
{   
    if(path == NULL || rootnode == NULL){
        return NULL;
    }
    if(strcmp(path, "/") == 0)
    {
        return rootnode;
    }
    int dir_number = get_dir_number(path); //获取指定目录的层级数    
    char dir_name[100];                    //获取指定目录中指定位置的目录名
    cJSON *dir_node = rootnode;               
    cJSON *get_node;
    for(int i = 1; i <= dir_number; i++)
    {
        get_dir_name(path, dir_name, i);
        get_node = select_dir(dir_name, dir_node);
        if(get_node == NULL)
        {
            return NULL;
        }
        dir_node = get_node;
    }
    return dir_node;
}
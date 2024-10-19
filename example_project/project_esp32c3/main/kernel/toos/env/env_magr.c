#include <stdio.h>
#include <string.h>
#include <stdlib.h>




void init_env() 
{
    char *path = "/etc/profile";
    FILE *fp = fopen(path, "r");
    if (fp == NULL) {
        printf("cannot read profile file\n");
        goto build_file;
    }
    fseek(fp, 0, SEEK_END);
    int size = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    fclose(fp);
    if(size == 0)  
    {
        goto  build_file;    
        printf("profile file is empty\n");  
    }
    return;
    
build_file:

    fp = fopen(path, "w");
    if (fp == NULL) {
        printf("cannot build profile file\n");
        return;
    }
    fprintf(fp, "[PATH]\n"); 
    fclose(fp);    
}



static int find_path(const char *env_path, const char *path, int file_size) {
    int path_len = strlen(path);
    for (int i = 0; i <= file_size - path_len; i++) 
    {



        if(env_path[i] == '[')
        while (env_path[i] != ']')
        {
            i++;
        }
        if (env_path[i] == '{')
        while (env_path[i] != '}')
        {
            i++;
        }
        if (env_path[i] == '\"')
        {
            i++;
            while (env_path[i] != '\"')
            {
                i++;
            }            
        }

        if (env_path[i] == '\'')
        {
            i++; 
            while (env_path[i] != '\'')
            {
                i++;
            }
        }

        
        if (env_path[i] == '%')
        {
            i++; 
            while (env_path[i] != '%')
            {
                i++;
            }
        }





        if(env_path[i] == '#')
        while ( env_path[i] != '\n' && env_path[i] != '\0')
        {
           i++;
        }
 



        if (strncmp(&env_path[i], path, path_len) == 0) {
            return i; // 返回匹配的起始索引
        }
    }
    return -1; // 未找到
}


char *get_resolve_path(const char *env_path)//获取有%的路径名
{
    char *get_path = malloc(512);    // max length of path is 255
    int i = 0;
    while (env_path[i] != '\0')
    {
        if (env_path[i] == '%')
        {
            i++;
            int j = 0;
            while (env_path[i] != '%')
            {
                get_path[j] = env_path[i];
                i++;
                j++;
            }
            get_path[j] = '\0';
            return get_path;
        }
        i++;
    }   
    free(get_path);    
    return NULL;
}

char *replace_path(const char *path ,const char *env_path) //替换%的路径名
{
    char *new_path = malloc(strlen(path) + strlen(env_path) + 1);    // max length of path is 255

    int i = 0;
    int k = 0;
    int j = 0;
    while (path[k] != '%' && path[i] != '\0')    // 拷贝并找到第一个%
    {
        new_path[i] = path[k];
        i++;
        k++;
    }

    while (env_path[i] != '\0')
    {
        new_path[i] = env_path[j];
        i++;
        j++;
    }

    k++;
    while (path[k] != '%')
    {
        k++;
    }
    k++;
    
    while (path[k] != '\0')
    {
        new_path[i] = path[k];
        i++;
        k++;
    }
    new_path[i] = '\0';
    return new_path;
}


const char* get_path(const char *__string) 
{
    // get the path of the file
    char *path_file = "/etc/profile";
    FILE *fp = fopen(path_file, "r");
    if (fp == NULL) {
        printf("open file error\n");
        return NULL;
    }
    fseek(fp, 0, SEEK_END);
    int file_size = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    char *env_path = malloc(file_size + 1);
    fread(env_path, 1, file_size, fp);
    fclose(fp);
    env_path[file_size] = '\0';

    // find the path in the file
    int i = find_path(env_path, __string, file_size);
    if (i == -1) {
        return NULL;
    }
    char *getpath = malloc(512);    // max length of path is 255
    while (env_path[i]!='=')
    {
        i++;
    }
    i++;
    while (env_path[i] == ' ')
    {
        i++;
    }
    int j = 0;
    while (env_path[i] != ' ' && env_path[i] != '\n' && env_path[i] != '\0')
    {
        getpath[j] = env_path[i];
        i++;
        j++;
    }
    getpath[j] = '\0';
    free(env_path);
    return getpath;
}

int get_boot_mode();
char *getenv_(const char *path) 
{
    if(get_boot_mode() == 0) return NULL; //恢复引导模式不提供环境变量
    char *swap_get_path;
    char *resolve_path;
    char *getpath = get_path(path);
    if(getpath == NULL)
    {
        return NULL;
    }
    resolve_path = get_resolve_path(getpath); // 获取第一个有%的路径名
    if(resolve_path == NULL)
    {
        return getpath;
    }
    swap_get_path = get_path(resolve_path);
    char *path_ = replace_path(getpath, swap_get_path);
    free(swap_get_path);
    free(getpath);
    free(resolve_path);
    return path_;
}








int setenv_(const char *name, const char *value, int overwrite) 
{
    char *existing_value = get_path(name);
    if (existing_value != NULL) 
    {
        free(existing_value);
        if (overwrite == 0) 
        {
            return 0;
        }
    }

    // 读取文件
    char *path_file = "/etc/profile";
    FILE *fp = fopen(path_file, "r");
    if (fp == NULL) 
    {
        printf("open file error\n");
        return -1;
    }
    // 读取整个文件内容
    fseek(fp, 0, SEEK_END);
    long file_size = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    char *file_content = malloc(file_size + 1);
    if (file_content == NULL) 
    {
        fclose(fp);
        return -1;
    }
    fread(file_content, 1, file_size, fp);
    fclose(fp);
    file_content[file_size] = '\0';

    // 查找环境变量
    int i = find_path(file_content, name, file_size);
    if (i != -1) {
        // 替换现有值
        while (file_content[i] != '=') 
        {
            i++;
        }
        i++; // 跳过 '='
        while (file_content[i] == ' ') 
        {
            i++;
        }
        // 替换值
        int len = strlen(value);
        strncpy(&file_content[i], value, len);
        i += len;

        // 清除剩余的内容
        while (file_content[i] != ' ' && file_content[i] != '\n' && file_content[i] != '\0') 
        {
            file_content[i] = ' ';
            i++;
        }
    }
    else
    {

        // 添加新环境变量
        char *new_entry = malloc(strlen(name) + strlen(value) + 3);
        if (new_entry == NULL) 
        {
            free(file_content);
            return -1;
        }
        sprintf(new_entry, "\n%s=%s", name, value);
        file_content = realloc(file_content, file_size + strlen(new_entry) + 1);
        if (file_content == NULL) 
        {
            free(new_entry);
            return -1;
        }
        strcat(file_content, new_entry);
        free(new_entry);
    }

    // 写回文件
    fp = fopen(path_file, "w");
    if (fp == NULL) {
        printf("open file error\n");
        free(file_content);
        return -1;
    }
    fprintf(fp, "%s", file_content);
    fclose(fp);
    free(file_content);
    return 0;
}

int unsetenv_(const char *name) 
{
    char *existing_value = get_path(name);
    if (existing_value == NULL) 
    {
        return 0;
    }
    free(existing_value);

    // get the path of the file
    char *path_file = "/etc/profile";
    FILE *fp = fopen(path_file, "r");
    if (fp == NULL) {
        printf("open file error\n");
        return -1;
    }
    fseek(fp, 0, SEEK_END);
    int file_size = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    char *env_path = malloc(file_size + 1);
    fread(env_path, 1, file_size, fp);
    fclose(fp);
    env_path[file_size] = '\0';


    int i = find_path(env_path, name, file_size);
            // 清除剩余的内容
    while ( env_path[i] != '\n' && env_path[i] != '\0') 
    {
        env_path[i] = ' ';
        i++;
    }
    // 写回文件
    fp = fopen(path_file, "w");
    if (fp == NULL) {
        printf("open file error\n");
        free(env_path);
        return -1;
    }
    fprintf(fp, "%s", env_path);
    fclose(fp);
    free(env_path);
    return 0;
}
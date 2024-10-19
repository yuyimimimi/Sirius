#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

static int parser_max_menory_use = 2 * 1024; //最大内存使用量,动态占用,用完会自动释放

//path_like = "/etc/sys_data.dat";
static int retry_times = 5;
void init_data_storage(char *path)                 //初始化文件
{
    int times = 0;
openfile:
    FILE *fp = fopen(path, "r");
    if (fp == NULL) {
        times++;
        if(times > retry_times)
        {
            printf("cannot read profile file\n");
            goto build_file;            
        }
        usleep(1000);
        goto openfile;
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
static int find_item(const char *env_path, const char *path, int file_size) //文件所有内容、查找的项目名称、 文件大小 
{
    int path_len = strlen(path);

    for (int i = 0; i <= file_size - path_len; i++) 
    {


        if(env_path[i] == '[')
        while (env_path[i] != ']')         //带有[]设为注释，内部不参与查找
        {
            i++;
        }

        if(env_path[i] == '{')             //带有{}视为单个值，内部不参与查找
        {
            int num = 1;
            while (num !=  0 &&  env_path[i] != '\0')
            {
                i++;
                if(env_path[i] == '{')
                {
                    num++;
                }
                else if(env_path[i] == '}')
                {
                    num--;
                }
            }
        }
        if(env_path[i] == '/' && env_path[i+1] == '/') //注释行，内部不参与查找
        {
            while (env_path[i] != '\n' && env_path[i] != '\0')
            {
                i++;
            }
        }
       
        if (env_path[i] == '&')             //&视为标记，解析时忽视
           i++; 

        if(env_path[i] == ';')             //;视为分隔符，内部不参与查找
        {
            i++;
        }
        
        if (env_path[i] == '%')            //%视为宏定义，解析时替换,不参与查找
        {
            i++; 
            while (env_path[i] != '%')
            {
                i++;
            }
        }

        if(env_path[i] == '#')            //#视为单行注释，内部不参与查找
        {
            while ( env_path[i] != '\n' && env_path[i] != '\0')
            {
            i++;
            }            
        }

       

        if (strncmp(&env_path[i], path, path_len) == 0) {
            return i; 
        }
    }
    return -1; 
}


const char *get_resolve_item(const char *env_path)           //提取第一个带有%的标记，作用相当于宏定义          //本身安全，返回需释放
{
    char *get_path = malloc(1024);                                
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
const char *replace_item(const char *path ,const char *env_path) //原始项目 、 宏定义                         //本身安全，返回需释放
{
    char *new_path = malloc(strlen(path) + strlen(env_path) + 1);    

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

static char* get_item_from_file(const char *__string,char *path)        //项目名称、文件路径                    //本身安全，返回值需要释放
{
    int retry_time = 0;
openfile:
    FILE *fp = fopen(path, "r");
    if (fp == NULL) {
        retry_time++;
        if(retry_time > retry_times)
        {
            printf("cannot read profile file\n");
            return NULL;
        }
        usleep(1000);
        goto openfile;
    }
    fseek(fp, 0, SEEK_END);
    int file_size = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    char *env_path = malloc(file_size + 1);
    fread(env_path, 1, file_size, fp);
    fclose(fp);
    env_path[file_size] = '\0';

    int i = find_item(env_path, __string, file_size);
    if (i == -1) {
        free(env_path);
        return NULL;
    }
    char *getpath = malloc(parser_max_menory_use);    
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
    if(env_path[i]!= '{')
    {
        while (env_path[i] != ' ' && env_path[i] != '\n' && env_path[i] != '\0')
        {
            getpath[j] = env_path[i];
            i++;
            j++;
        }
        getpath[j] = '\0';        
    }
    else
    {
        int num = 1;
        while ( num !=  0 &&  env_path[i] != '\0')
        {

            getpath[j] = env_path[i];
            i++;
            j++;  
            if(env_path[i] == '#')
            {
                while (env_path[i] != '\n' && env_path[i] != '\0')
                {
                    i++;
                }
            }
            if(env_path[i] == '{')
            {
                num++;
            }
            if(env_path[i] == '}')
            {
                num--;
            }
        }
        getpath[j] = '}' ;
        getpath[j+1] = '\0';     
    }
    free(env_path);
    return getpath;
}

char* get_item_from_data(const char *__string,char *data)        //项目名称、文件内容                        // 本身安全，返回值需要释放 
{ 
    char *env_path = data;
    int file_size = strlen(env_path);

    int i = find_item(env_path, __string, file_size);
    if (i == -1) {
        return NULL;
    }
    char *getpath = malloc(parser_max_menory_use);    
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
    if(env_path[i]!= '{')
    {
        while (env_path[i] != ' ' && env_path[i] != '\n' && env_path[i] != '\0')
        {
            getpath[j] = env_path[i];
            i++;
            j++;
        }
        getpath[j] = '\0';        
    }
    else
    {
        while ( env_path[i] != '}' && env_path[i] != '\0')
        {
            getpath[j] = env_path[i];
            i++;
            j++;
        }
        getpath[j] = '}' ;
        getpath[j+1] = '\0';     
    }

    return getpath;
}


char* trim_braces(char* str) {
    if(str[0] == '{')
    {
         int i = strlen(str) - 1;
         for(int j = 0;j < i;j++)
         {
            str[j] = str[j+1];
         }
         str[i - 2] = '\0';
    }
    return str; 
}


char *getitem(const char *path,char *name)                   // 本身安全，返回值需要释放 
{
    //check if file exists
    FILE *fp = fopen(path, "r");
    if (fp == NULL) {
        printf("open file error\n");
        return NULL;
    }
    size_t file_size = 0;
    fseek(fp, 0, SEEK_END);
    file_size = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    fclose(fp);

    if(file_size > parser_max_menory_use)
    {
        printf("file %s is too large Please reduce the size\n",path);
        return NULL;
    }

    char *swap_get_path;
    char *resolve_path;
    char *getpath = get_item_from_file(name,path);
    if(getpath == NULL){
        return NULL;
    }
    resolve_path = get_resolve_item(getpath); // 获取第一个有%的路径名
    if(resolve_path == NULL){
        return getpath;
    }
    swap_get_path = get_item_from_file(name,resolve_path);
    char *path_ = replace_item(getpath, swap_get_path);
    free(swap_get_path);
    free(getpath);
    free(resolve_path);

    for (int i = strlen(path_) - 1; i >= 0; i--) {
        if (path_[i] == ' ' || path_[i] == '\n') {
            path_[i] = '\0';
        } else {
            break; // 停止
        }
    }

    return path_;
}


int setitem(const char *name, const char *value, int overwrite,char *path) //overwrite 0:不覆盖，1：覆盖
{
    char *existing_value = get_item_from_file(name,path);
    if (existing_value != NULL) {
        free(existing_value);
        if (overwrite == 0) {
            return 0;
        }
    }
int retry_time = 0;
openfile:
    FILE *fp = fopen(path, "r");
    if (fp == NULL) 
    {  
        retry_time++;
        if(retry_time > retry_times)
        {
            printf("open file error\n");
            return -1;            
        }
        usleep(1000);
        goto openfile;        
    }

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

    int i = find_item(file_content, name, file_size);
    if (i != -1) {
        while (file_content[i] != '=') 
        {
            i++;
        }
        i++; 
        while (file_content[i] == ' ') 
        {
            i++;
        }
        int len = strlen(value);
        strncpy(&file_content[i], value, len);
        i += len;

        while (file_content[i] != ' ' && file_content[i] != '\n' && file_content[i] != '\0') 
        {
            file_content[i] = ' ';
            i++;
        }
    }
    else
    {

        char *new_entry = malloc(strlen(name) + strlen(value) + 3);
        if (new_entry == NULL) {
            free(file_content);
            return -1;
        }
        sprintf(new_entry, "\n%s=%s", name, value);
        file_content = realloc(file_content, file_size + strlen(new_entry) + 1);
        if (file_content == NULL) {
            free(new_entry);
            return -1;
        }
        strcat(file_content, new_entry);
        free(new_entry);
    }

    fp = fopen(path, "w");
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







int unsetitem(const char *name , char *path) 
{
    char *existing_value = get_item_from_file(name,path);
    if (existing_value == NULL) {
        return 0;
    }
    free(existing_value);

    FILE *fp = fopen(path, "r");
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


    int i = find_item(env_path, name, file_size);
    
    while ( env_path[i] != '\n' && env_path[i] != '\0') 
    {
        env_path[i] = ' ';
        i++;
    }

    fp = fopen(path, "w");
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
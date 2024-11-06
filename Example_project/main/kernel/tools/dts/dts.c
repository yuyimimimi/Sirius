#include "stdio.h"
#include "item_script.h"
#include "env.h"
#include <linux/of_device.h>
#include <linux/of.h>

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

static int get_dir_number(char *path)                         //获取指定目录的层级数
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

int get_boot_mode();
char* try_to_parse_dts(char *devic_node)           //返回值需要释放
{
    if(get_boot_mode() == 0){return NULL;} //恢复启动模式不提供dts解析功能
    char *path  = getenv_("DTS_PATH");      //获取DTS路径环境变量
    if(path == NULL){
        return NULL;
    }
    char *node = devic_node;
    
    int node_numbers = get_dir_number(node);
    if(node_numbers < 1){                     //节点路径不合法，至少需要1层
        printf("Error: node path is invalid\n");
        free(path);
        return NULL;
    }
    char dir_name[256];
    char *new_data;
    get_dir_name(node, &dir_name, 1);       //获取第1层根结点名
    char *data = getitem(path, &dir_name);  //获取根结点的数据
    if(data == NULL){
        printf("Error: can not find root node data\n");
        free(path);
        return NULL;
    }
    if(node_numbers == 1){
        free(path);
        return data;
    }

    data = trim_braces(data);               //去掉首尾的花括号
    for(int i = 2; i <= node_numbers; i++)
    {
        get_dir_name(node, &dir_name, i);                   //获取第i层目录名
        new_data = get_item_from_data(&dir_name, data);     //获取第i层目录的数据
        free(data);
        if(new_data == NULL){
            
            free(path);
            return NULL;
        }
        if(new_data[0] == '{'){
            new_data = trim_braces(new_data);  
        }
        data = new_data;
    }
    free(path);
    return data;
}


struct device_node* of_find_node_by_path(char *path)
{  
    char *test = try_to_parse_dts(path);
    if(test == NULL){
        return NULL;
    }
    free(test);
    
    struct device_node *dev_node = malloc(sizeof(struct device_node));
    if (!dev_node) return NULL;

    dev_node->node_path = malloc(strlen(path) + 1);
    if (!dev_node->node_path) {
        free(dev_node);
        return NULL;
    }
    strcpy(dev_node->node_path, path);
    
    return dev_node;
}


void* of_get_property(struct device_node *dev_node, char *property_name, int *len)
{
    char *path = (char *)malloc(1024);
    if(path == NULL){
        return NULL;
    }
    strcpy(path, dev_node->node_path);
    strcat(path+ strlen(path), "/");
    strcat(path+ strlen(path), property_name);
    char *data = try_to_parse_dts(path);
    free(path);
    if(data == NULL){
        return NULL;
    }


    if(data[0] == '<')
    {
        int num = 0;
        for(int i = 0; i < strlen(data); i++)
        {
            if(data[i] == ','){
                num++;
            }
        }
        if(num == 0)
        {
            int i = 0;
            while (data[i]!= '>' && data[i] != '\0')
            {
                data[i] = data[i+1];
                i++;
            }  
            data[i] = '\0';

            int *number = (int*)malloc(sizeof(int));
            if(number == NULL){
                free(data);
                return NULL;
            }
            *number = atoi(data);
            free(data);
            return (void*)number;            
        }
        else
        {   
            if(len == NULL){
                free(data);
                return NULL;
            }

            *len  = num+1; // 返回数组长度
            int *array = (int*)malloc(sizeof(int) * (*len));
            if(array == NULL){
                free(data);
                return NULL;
            }
            char *temp = (char*)malloc(32);
            if(temp == NULL){
                free(array);
                free(data);
                return NULL;
            }
            int j = 1;                   //字符串遍历指针起始为1是为了跳过第一个<
            int k = 0;                   //temp缓存指针
            for(int i = 0; i < num; i++) //数组遍历
            {   
                while (data[j] != ',' && data[j] != '>' && data[j] != '\0' && data[j] != ';'){
                    temp[k] = data[j];
                    k++;
                    j++;
                }
                temp[k] = '\0';
                array[i] = atoi(temp);
                k = 0;
                j++;                                                       //跳过逗号
            }
            free(temp);
            free(data);
            return (void*)array;
        }
    }

    if(data[0] == '"'){
        data[0] = data[1];
        int i = 1;
        while (data[i] != '"' && data[i] != '\0'){
            data[i] = data[i+1];
            i++;
        }  
        data[i-1] = '\0';
        return (void*)data;
    }

    free(data);
    return NULL;
}

void of_node_put(struct device_node *dev_node) {
    if (dev_node) {
        if(dev_node->node_path){
            free(dev_node->node_path);
        }
        free(dev_node);               // 释放 device_node 结构体
    }
}


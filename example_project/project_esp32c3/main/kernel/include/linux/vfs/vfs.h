#ifndef _LINUX_VFS_VFS_H
#define _LINUX_VFS_VFS_H

#include <cJSON.h>


#define vfs_swap_path "fs.dat"                                          //交换分区文件名
void init_vfs_registry(void);                                           //初始化vfs注册表
char *get_vfs_registry_path(void);                                      //获取vfs注册表路径
int create_vfs_node_file(char *path, char* type ,unsigned int dev_id);  //创建文件
cJSON *get_vfs_registry_root();                                         //获取vfs注册表根节点
cJSON *get_vfs_node_file(char *path,cJSON *rootnode);                   //按照路径获取文件信息


#endif /* _LINUX_VFS_VFS_H */
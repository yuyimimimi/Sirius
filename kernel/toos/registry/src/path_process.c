#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include "registry.h"
#include "string.h"



static int get_addr(char *path, int i) {
    int j = 0;
    for (int num = 0; path[num] != '\0'; num++) {
        if (path[num] == '/') {
            j++;
            if (j == i) return num; 
        }
    }
    return -1; 
}


static void copy_path(char *path, char *p, int i) {
    strncpy(p, path, i);
    p[i] = '\0'; 
}

static int get_path(char *path,char *p,int i)    //获取第i个路径
{
    int addr = get_addr(path,i);
    if(addr == -1){
        return -1;
    }
    copy_path(path,p,addr);
    return 0;
}






int check_path(char *path)
{
    if (path == NULL) 
    {
        printf("Error: Path is NULL\n");
        printf("please set the path at ./source/kernel/toos/include/registry.h !\n");
        while (1) {}     // halt the system
    }

    char *p = (char *)malloc(512);
    struct stat statbuf; 
    int i = 2;
    while (get_path(path,p,i) == 0)
    {
        if (stat(p, &statbuf) == -1)
        {
            if(mkdir(p, 0755))
            {
                printf("try to mkdir %s failed\n", p);
                printf("please check the path!\n");
                printf("please set the path at ./source/kernel/toos/include/registry.h !\n");
                printf("source at :./source/kernel/toos/registry/src/path_process.c\n");
                while (1) {}     // halt the system
            }
        }
        i++;
    }
    free(p);
    return 0;
}


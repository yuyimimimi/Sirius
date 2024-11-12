#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "env.h"

int getenv_command(int argc, char* argv[]) {
    if (argc != 2) {
        printf("Usage: getenv <variable_name>\n");
        return 0;
    }
    char* value = getenv_(argv[1]);
    if (value != NULL) {
        printf("%s=%s\n", argv[1], value);
    } else {
        printf("%s is not set\n", argv[1]);
    }
    return 0;
}

int setenv_command(int argc, char* argv[]) {
    if (argc != 3) {
        printf("Usage: setenv <variable_name> <value>\n");
        return 0;
    }
    int result = setenv_(argv[1], argv[2], 1);
    return 0;
}

int unsetenv_command(int argc, char* argv[]) {
    if (argc != 2) {
        printf("Usage: unsetenv <variable_name>\n");
        return 0;
    }
    int result = unsetenv_(argv[1]);
    return 0;
}


int env_command(int argc, char* argv[]) {
    char *path = "/etc/profile";
    FILE *fp = fopen(path, "r");
    if (fp == NULL) {
        printf("Error: cannot open %s\n", path);
        return -1;  // 返回 -1 表示文件打开失败
    }
    
    char line[1024];  // 用一个足够大的缓冲区来存储每行数据
    while (fgets(line, sizeof(line), fp)) {
        printf("%s", line);
    }

    fclose(fp);
    return 0;
}
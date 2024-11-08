#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <time.h>
#include <console_cop.h>

int stat_command(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: stat <file>\n");
        return 1;
    }

    argv[1] = get_file_path(argv[1]);
    if(argv[1]  == NULL)
        return 1;

    // 获取文件信息
    struct stat file_stat;
    if (stat(argv[1], &file_stat) == -1) {
        perror("stat");
        return 1;
    }

    // 打印文件信息
    printf("File: %s\n", argv[1]);
    free(argv[1]);

    printf("Size: %ld bytes\n", file_stat.st_size);
    
    // 打印文件权限
    printf("Permissions: ");
    printf((file_stat.st_mode & S_IRUSR) ? "r" : "-");
    printf((file_stat.st_mode & S_IWUSR) ? "w" : "-");
    printf((file_stat.st_mode & S_IXUSR) ? "x" : "-");
    printf((file_stat.st_mode & S_IRGRP) ? "r" : "-");
    printf((file_stat.st_mode & S_IWGRP) ? "w" : "-");
    printf((file_stat.st_mode & S_IXGRP) ? "x" : "-");
    printf((file_stat.st_mode & S_IROTH) ? "r" : "-");
    printf((file_stat.st_mode & S_IWOTH) ? "w" : "-");
    printf((file_stat.st_mode & S_IXOTH) ? "x" : "-");
    printf("\n");

    // 打印最后修改时间
    char time_str[100];
    struct tm *tm_info = localtime(&file_stat.st_mtime);
    strftime(time_str, sizeof(time_str), "%Y-%m-%d %H:%M:%S", tm_info);
    printf("Last modified: %s\n", time_str);

    return 0;
}

int main(int argc, char *argv[]) {
    return stat_command(argc, argv);
}

#include <stdio.h>
#include <console_cop.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <string.h>


int copy_file(const char *source, const char *destination) {
    int src_fd, dest_fd;
    char buffer[1024];
    ssize_t bytes_read, bytes_written;

    // 打开源文件
    src_fd = open(source, O_RDONLY);
    if (src_fd == -1) {
        perror("Error opening source file");
        return 1;
    }

    // 创建目标文件
    dest_fd = open(destination, O_WRONLY | O_CREAT | O_TRUNC, 0666);
    if (dest_fd == -1) {
        perror("Error creating destination file");
        close(src_fd);
        return 1;
    }

    // 从源文件读取并写入目标文件
    while ((bytes_read = read(src_fd, buffer, sizeof(buffer))) > 0) {
        bytes_written = write(dest_fd, buffer, bytes_read);
        if (bytes_written != bytes_read) {
            perror("Error writing to destination file");
            close(src_fd);
            close(dest_fd);
            return 1;
        }
    }

    if (bytes_read == -1) {
        perror("Error reading source file");
    }

    close(src_fd);
    close(dest_fd);
    return 0;
}


int cp_command(int argc, char *argv[])
{
    if(argc < 3)
    {
        printf("Usage: mv <source> <destination>\n");
        return 1;
    }
    char *path1 = get_file_path(argv[1]); //获取绝对路径
    char *path2 = get_file_path(argv[2]); //获取绝对路径
    if(path1 == NULL || path2 == NULL)
    {
        printf("Invalid path\n");
        return 1;
    }
    if(copy_file(path1, path2)!= 0)
    {
        printf("Failed to copy file\n");
        return 1;
    }

    free(path1);
    free(path2);
    
    return 0;
}



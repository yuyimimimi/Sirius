#include <stdio.h>
#include <console_cop.h>

int mv_command(int argc, char *argv[])
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
    if(rename(path1, path2)!= 0) //重命名文件
    {
        printf("Failed to rename file\n");
        return 1;
    }
    free(path1);
    free(path2);
    
    return 0;
}

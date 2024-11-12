#include <stdio.h>
#include <stdlib.h>
#include <console_cop.h>


int tail_command(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: tail <file>  [lines]\n");
        return 1;
    }

    char *path = get_file_path(argv[1]); 
    
    FILE *file = fopen(path, "r");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    // 使用 fseek 定位到文件末尾
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);

    if (file_size < 0) {
        perror("Error getting file size");
        fclose(file);
        return 1;
    }

    long offset = 0;
    int count = 0;
    char ch;
    int lines = 10;
    
    if(argc == 2)
    {
        lines = atoi(argv[2]);
        if (lines <= 0) {
            fprintf(stderr, "Invalid line count\n");
            fclose(file);
            return 1;
        }
    }

    // 从文件末尾向回读取，直到找到所需的行数
    while (file_size - offset > 0 && count < lines) {
        fseek(file, --file_size, SEEK_SET);
        ch = fgetc(file);

        if (ch == '\n') {
            count++;
        }
        offset++;
    }

    // 读取并显示最后的部分
    char line[256];
    while (fgets(&line, sizeof(line), file)) {
        printf("%s", line);
    }

    fclose(file);
    free(path);
    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <console_cop.h>



int head_command(int argc, char *argv[]) {
    if (argc != 2) {
        printf(stderr, "Usage: head <file> [lines]\n");
        return 1;
    }
    char *path = get_file_path(argv[1]); 

    FILE *file = fopen(path, "r");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    char line[1024];
    int count = 0;

    int lines = 10;
    if (argc == 3) {
        lines = atoi(argv[2]);
        if (lines <= 0) {
            fprintf(stderr, "Invalid line count\n");
            fclose(file);
            return 1;
        }
    }

    // 显示前10行
    while (fgets(line, sizeof(line), file) && count < lines) {
        printf("%s", line);
        count++;
    }

    fclose(file);
    free(path);
    return 0;
}

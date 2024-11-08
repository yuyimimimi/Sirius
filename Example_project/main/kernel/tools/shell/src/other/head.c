#include <stdio.h>
#include <stdlib.h>

#define DEFAULT_LINES 10

int head_command(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: head <file>\n");
        return 1;
    }

    FILE *file = fopen(argv[1], "r");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    char line[1024];
    int count = 0;

    // 显示前10行
    while (fgets(line, sizeof(line), file) && count < DEFAULT_LINES) {
        printf("%s", line);
        count++;
    }

    fclose(file);
    return 0;
}

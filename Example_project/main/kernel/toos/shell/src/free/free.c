#include <stdio.h>
#include "esp_system.h"

int _get_memory_size();

int free_cmd(int argv,char **argc) 
{
    int free_memory_size = esp_get_minimum_free_heap_size() / 1024;
    int all_memory_size = _get_memory_size() / 1024;
    printf("               total        used        free   ");
    printf("\nmem:            %d          %d         %d  \n" , all_memory_size,(all_memory_size - free_memory_size),free_memory_size);
    return 0;
}


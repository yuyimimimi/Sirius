#include <stdio.h>

int full_memorysize;

void _set_memory_size(int size)
{
    full_memorysize = size;
}

int _get_memory_size()
{
    return full_memorysize;
}


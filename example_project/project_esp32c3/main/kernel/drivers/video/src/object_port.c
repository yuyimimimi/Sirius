#include "display_private_def.h"
#include <stdio.h>
#include <lwip/sockets.h>
#include <stdlib.h>


int insert_new_display_object(display_object_t *new_object)
{
    int dev = open(new_object->object_path, O_RDWR);
    if (dev < 0) {
        printf("Failed to open %s\n", new_object->object_path);
        return -1;
    }
    close(dev);
    insert_node_into_list(new_object);


    return 0;
}

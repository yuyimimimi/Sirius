#ifndef __DISPLAY_PRIVATE_DATA_H__
#define __DISPLAY_PRIVATE_DATA_H__
#include "display_farmerwork.h"
#include <stdlib.h>
#include <stdint.h>




typedef struct display_list{ 
    int object_id;
    display_device_t *device;
    struct display_list *next;
}display_list_t;


display_list_t *get_root_node(void);
size_t color_to_color(uint32_t *color ,uint32_t length ,int pixel_format,void *dest_buffer,int dest_pixel_format);
void draw_display(int Offset_X, int Offset_Y, int width, int height,uint32_t *buffer);

#endif /* __DISPLAY_PRIVATE_DATA_H__ */
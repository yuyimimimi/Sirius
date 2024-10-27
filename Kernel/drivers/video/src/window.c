#include "display_farmerwork.h"
#include <sirapi/video/sirgui.h>
#include <linux/errno.h>
#include <string.h>
#include <linux/printk.h>

typedef struct Windows_list {
    __u8 id;
    __u8 enable;   
    Window window_node;
    struct Windows_list *next;
}Windows_list;


Windows_list *head_list = NULL;


Window* CreateWindow(int x, int y, int width, int height, int color_format, __u32 backgroundColor,  __u8 priority, const char* title)
{
    Window *window = (Window*)malloc(sizeof(Window));
    window->appearance.BackgroundColor = backgroundColor;
    window->appearance.color_format = color_format;
    window->appearance.Margin = 1;
    window->appearance.MarginColor = 0x00000000;

    window->attributes.height = height;
    window->attributes.width = width;
    window->attributes.x_offset = x;
    window->attributes.y_offset = y;
    window->attributes.Title = (char*)malloc(strlen(title)+1);
    if(window->attributes.Title == NULL)
    {
        free(window);
        printk( KERN_ERR "Failed to allocate memory for window title\n");
        return NULL;
    }
    strcpy(window->attributes.Title, title);

    Windows_list *window_node;
    window_node = head_list;        //head of list

    int id = 0;
    while(window_node!= NULL){      //find the last node
        id++;
        window_node = window_node->next;
    }
    window_node = (Windows_list*)malloc(sizeof(Windows_list));
    if(window_node == NULL)
    {
        free(window->attributes.Title);
        free(window);
        printk( KERN_ERR "Failed to allocate memory for window node\n");
        return NULL;
    }

    window_node->id = id;
    window_node->enable = 1;
    window_node->window_node = *window;
    window_node->next = NULL;
    return window;        
}




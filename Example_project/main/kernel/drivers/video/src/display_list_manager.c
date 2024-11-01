#include "display_private_def.h"
#include <linux/of.h>
#include <stdlib.h>
#include <linux/printk.h>
#include <linux/vfs/vfs.h>

display_list_t *displat_object_list = {0,NULL,NULL};

int display_object_add(struct display_device *obj)
{
    printk(KERN_INFO "display_object_add: add display device %s\n", obj->name);
    struct device_node *np = NULL;
    char *node_path = obj->node;
    np = of_find_node_by_path(node_path);
    if (np == NULL) {
        printk(KERN_ERR "display_object_add: can't add display device %s\n", obj->name);
        printk(KERN_ERR "display_object_add: please check the node path %s\n", node_path);
        return -1;
    }
    printk(KERN_INFO "display_object_add: display device %s is found\n", obj->name);
    char *status = of_get_property(np, "status", NULL);
    if (status == NULL) {
        printk(KERN_ERR "display_object_add: can't get status for display device %s\n", obj->name);
        return -1;
    }
    if (strcmp(status, "okay") != 0) {
        printk(KERN_ERR "display_object_add: display device %s is not disabled\n", obj->name);
        return -1;
    }
    printk(KERN_INFO "display_object_add: display device %s is added\n", obj->name);

    obj->data.buffer_size = of_get_property(np, "buffer_size", NULL);
    if (obj->data.buffer_size == NULL) {
        printk(KERN_ERR "display_object_add: can't get buffer-size for display device %s\n", obj->name);
        return -1;
    }
    printk(KERN_INFO "display_object_add: buffer-size for display device %s is %d\n", obj->name, *(int *)obj->data.buffer_size);
    obj->data.width = of_get_property(np, "width", NULL);
    if (obj->data.width == NULL) {
        printk(KERN_ERR "display_object_add: can't get width for display device %s\n", obj->name);
        return -1;
    }
    printk(KERN_INFO "display_object_add: width for display device %s is %d\n", obj->name, *(int *)obj->data.width);
    obj->data.height = of_get_property(np, "height", NULL);
    if (obj->data.height == NULL) {
        printk(KERN_ERR "display_object_add: can't get height for display device %s\n", obj->name);
        return -1;
    }
    printk(KERN_INFO "display_object_add: height for display device %s is %d\n", obj->name, *(int *)obj->data.height);
    obj->data.offset_x = of_get_property(np, "offset-x", NULL);
    if (obj->data.offset_x == NULL) {
        printk(KERN_ERR "display_object_add: can't get offset-x for display device %s\n", obj->name);
        return -1;
    }
    printk(KERN_INFO "display_object_add: offset-x for display device %s is %d\n", obj->name, *(int *)obj->data.offset_x);
    obj->data.offset_y = of_get_property(np, "offset-y", NULL);
    if (obj->data.offset_y == NULL) {
        printk(KERN_ERR "display_object_add: can't get offset-y for display device %s\n", obj->name);
        return -1;
    }
    printk(KERN_INFO "display_object_add: offset-y for display device %s is %d\n", obj->name, *(int *)obj->data.offset_y);
    obj->data.pixel_format = of_get_property(np, "pixel-format", NULL);
    if (obj->data.pixel_format == NULL) {
        printk(KERN_ERR "display_object_add: can't get pixel-format for display device %s\n", obj->name);
        return -1;
    }
    printk(KERN_INFO "display_object_add: pixel-format for display device %s is %d\n", obj->name, *(int *)obj->data.pixel_format);
    
    int ret = obj->init();
    if(ret != 0) {
        printk(KERN_ERR "display_object_add: init display device %s failed\n", obj->name);
        return -1;
    }

    if(displat_object_list == NULL)
    {
        displat_object_list = (display_list_t *)malloc(sizeof(display_list_t));
        displat_object_list->device = obj;
        displat_object_list->next = NULL;
    }
    else
    {
        display_list_t *temp = displat_object_list;
        while (temp->next != NULL)
        {
            temp = temp->next;
        }
        temp->next = (display_list_t *)malloc(sizeof(display_list_t));
        temp->next->device = obj;
        temp->next->next = NULL;
    }
    printk(KERN_INFO "display_object_add: display device %s is added successfully\n", obj->name);
    create_vfs_node_file("/dev/video/%s","device",0x00ff00ff,obj->name);

    return 0;
}

display_list_t *get_root_node(void)
{
    return displat_object_list;
}
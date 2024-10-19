#ifndef __DISPLAY_PRIVATE_DATA_H__
#define __DISPLAY_PRIVATE_DATA_H__
#include "display_farmerwork.h"
#include <stdlib.h>
#include <stdint.h>

typedef struct display_object_t_list{
    int object_id;
    display_object_t *display_object_node;
    struct display_object_t_list *next;
}display_object_t_list_t;

display_object_t_list_t *display_object_list_head;


#define No_memory_error 1
#define not_usefull_error 2


int insert_node_into_list(display_object_t *node);   //插入节点到链表中   
int display_object_list_release_nide_by_num(int num); //根据id删除节点   
display_object_t *get_object_by_id(int id);          //根据id获取节点   
display_object_t *display_Iterators(void);           //节点迭代器   
void reset_Iterators(void);                        //重置迭代器   


int color_to_color(void *src, void *dst, uint32_t len, color_mode_t src_color, color_mode_t dst_color); //颜色转换


void rebuid_display_buffer();                                                                    //重建显示缓存
void init_display_buffer();                                                                      //初始化显示缓存         
void draw_display_buffer(int Offset_X, int Offset_Y, int width, int height,void *buffer,color_mode_t color_mode);   //绘制显示缓存   



#endif /* __DISPLAY_PRIVATE_DATA_H__ */
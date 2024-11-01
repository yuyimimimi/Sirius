#include "display_private_def.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <linux/mutex.h> 
#include <linux/module.h>
#include <linux/init.h>
#include <linux/delay.h>
#include <linux/slab.h>
   

#define min(a,b) ((a)<(b)?(a):(b))
#define max(a,b) ((a)>(b)?(a):(b))

struct mutex dsp_lock;

int __init int_display_system()
{
    printk(KERN_INFO "video system: initializing\n");
    mutex_init(dsp_lock);
    return 0;
}

void draw_display(int Offset_X, int Offset_Y, int width, int height,uint32_t *buffer) //只支持RGBA8888格式绘图
{   
    display_list_t *list = get_root_node();
    int display_Offset_X;
    int display_Offset_Y;
    int display_width;
    int display_height;
    int display_pixel_size;

    int x_coordanate = 0;
    int y_coordinate = 0;
    int x_coordinate_of_draw = 0;
    int y_coordinate_of_draw = 0;
    int draw_width;
    int draw_height;

    while (list!= NULL)
    {
        display_Offset_X = list->device->data.offset_x[0];
        display_Offset_Y = list->device->data.offset_y[0];
        display_width = list->device->data.width[0];
        display_height = list->device->data.height[0];
        display_pixel_size = list->device->data.pixel_format[0];
              
        /**
         * 碰撞检测
        */

        int x_overlap = max(0, min(display_Offset_X + display_width, Offset_X + width) - max(display_Offset_X, Offset_X));
        int y_overlap = max(0, min(display_Offset_Y + display_height, Offset_Y + height) - max(display_Offset_Y, Offset_Y));
        if (x_overlap == 0 || y_overlap == 0) {
            goto next;
        };

        /**
         * 
         * 显示器局部刷新坐标
         * 
        */
        x_coordanate = max(Offset_X - display_Offset_X,0);
        y_coordinate = max(Offset_Y - display_Offset_Y,0);


        /**
         * 
         * 绘制区域偏移量
         * 
        */

       x_coordinate_of_draw = max(0,display_Offset_X - Offset_X);
       y_coordinate_of_draw = max(0,display_Offset_Y - Offset_Y);   

        /**
         * 
         * 绘制区域长宽
         * 
        */

        draw_width = min(width - x_coordinate_of_draw,display_width - x_coordanate);
        draw_height = min(height - x_coordinate_of_draw,display_height -y_coordinate);  

        mutex_lock(dsp_lock);  
        if(display_pixel_size == 888)
        {
            if(draw_width == width)
            {
                list->device->display(x_coordanate,y_coordinate,draw_width,draw_height,buffer+y_coordinate*width);
            }
            else
            {
                int j = 0;
                for(int i = y_coordinate;i<height;i++)
                {
                    list->device->display(x_coordanate,y_coordinate+j,draw_width,1,           buffer+i*width+x_coordinate_of_draw);
                    j++;
                }
            }
        } 
        else 
        {
            uint16_t *buffer_16bit =(uint16_t *)vmalloc(draw_width*draw_height*2);
            if(buffer_16bit == NULL){
                pr_err("video system: no enough memory\n");
            }

            if(draw_width == width)
            {
                color_to_color(buffer + y_coordinate_of_draw*width ,width*draw_height,display_pixel_size,buffer_16bit,888);
            }
            else
            {
                int j = 0;
                for(int i = y_coordinate; i<height;i++)
                {
                    color_to_color(buffer+i*y_coordinate_of_draw+x_coordinate_of_draw, draw_width, display_pixel_size,buffer_16bit + j*draw_width,888);
                    j++;
                }          
            }
            list->device->display(x_coordanate,y_coordinate,draw_width,draw_height,buffer_16bit);
            vfree(buffer_16bit);
        }
    
        mutex_unlock(dsp_lock);

        next:
        list = list->next;
    }
}




void draw_display_565(int Offset_X, int Offset_Y, int width, int height,uint16_t *buffer) 
{   
    display_list_t *list = get_root_node();
    int display_Offset_X;
    int display_Offset_Y;
    int display_width;
    int display_height;
    int display_pixel_size;

    int x_coordanate = 0;
    int y_coordinate = 0;
    int x_coordinate_of_draw = 0;
    int y_coordinate_of_draw = 0;
    int draw_width;
    int draw_height;

    while (list!= NULL)
    {
        display_Offset_X = list->device->data.offset_x[0];
        display_Offset_Y = list->device->data.offset_y[0];
        display_width = list->device->data.width[0];
        display_height = list->device->data.height[0];
        display_pixel_size = list->device->data.pixel_format[0];
              
        /**
         * 碰撞检测
        */

        int x_overlap = max(0, min(display_Offset_X + display_width, Offset_X + width) - max(display_Offset_X, Offset_X));
        int y_overlap = max(0, min(display_Offset_Y + display_height, Offset_Y + height) - max(display_Offset_Y, Offset_Y));
        if (x_overlap == 0 || y_overlap == 0) {
            goto next;
        };

        /**
         * 
         * 显示器局部刷新坐标
         * 
        */
        x_coordanate = max(Offset_X - display_Offset_X,0);
        y_coordinate = max(Offset_Y - display_Offset_Y,0);


        /**
         * 
         * 绘制区域偏移量
         * 
        */

       x_coordinate_of_draw = max(0,display_Offset_X - Offset_X);
       y_coordinate_of_draw = max(0,display_Offset_Y - Offset_Y);   

        /**
         * 
         * 绘制区域长宽
         * 
        */

        draw_width = min(width - x_coordinate_of_draw,display_width - x_coordanate);
        draw_height = min(height - x_coordinate_of_draw,display_height -y_coordinate);  

        mutex_lock(dsp_lock);  
        if(display_pixel_size == 565)
        {
            if(draw_width == width)
            {  
                list->device->display(x_coordanate,y_coordinate,width,draw_height,buffer+y_coordinate_of_draw*width);
            }
            else
            {
                int j = 0;
                for(int i = y_coordinate_of_draw;i<height;i++)
                {
                    list->device->display(x_coordanate,y_coordinate+j,draw_width,1,   buffer+i*width+x_coordinate_of_draw);
                    j++;
                }
            }
        } 
        else 
        {
            // uint16_t *buffer_16bit =(uint16_t *)vmalloc(draw_width*draw_height*2);
            // if(buffer_16bit == NULL){
            //     pr_err("video system: no enough memory\n");
            // }
            // else
            // {
            //     if(draw_width == width)
            //     {
            //         color_to_color(buffer + y_coordinate_of_draw*width ,width*draw_height,display_pixel_size,buffer_16bit,565);
            //     }
            //     else
            //     {
            //         int j = 0;
            //         for(int i = y_coordinate; i<height;i++)
            //         {
            //             color_to_color(buffer+i*y_coordinate_of_draw+x_coordinate_of_draw, draw_width, display_pixel_size,buffer_16bit + j*draw_width,565);
            //             j++;
            //         }          
            //     }
            //     list->device->display(x_coordanate,y_coordinate,draw_width,draw_height,buffer_16bit);
            //     vfree(buffer_16bit);                
            // }
        }

        mutex_unlock(dsp_lock);
        
        next:
        list = list->next;
    }
}




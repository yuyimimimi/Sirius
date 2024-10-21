#ifndef __DISPLAY_FARMERWORK_H__
#define __DISPLAY_FARMERWORK_H__
#include <stdio.h>

#define display_buffer  1024//pixel 
#define sys_color_mode      RGB_565




/**
 * @brief display_color_mode_t
 * @note   显示器的颜色模式
 * @param  RGB_888: 888模式
 * @param  RGB_565: 565模式
 * @param  GRAYSCALE: 灰度模式
 * @param  darkandlight: 深浅灰模式
*/

typedef enum color_mode {
    RGB_888,
    RGB_565,
    GRAYSCALE,
    darkandlight,
}color_mode_t;


/**
 * 
 * @brief display_object_t
 * @note   显示器对象结构体
 * @param  object_width: 显示器对象宽度
 * @param  object_height: 显示器对象高度
 * @param  object_buffer_size: 显示器对象缓存大小
 * @param  color_mode: 显示器对象颜色模式
 * @param  object_path: 显示器对象路径
 * @param  virtual_display_object: 显示器对象是否为虚拟对象
 * @param  object_type: 显示器对象类型
 * @param  displaye_Priority: 显示器对象优先级
 * @param  Offset_X: 显示器对象映射像素左上角位置X坐标
 * @param  Offset_Y: 显示器对象映射像素左上角位置Y坐标
 * @param  set_coordinate: 显示器对象设置坐标函数指针
 * @param  draw_object: 显示器对象绘制函数指针
 * @param  object_display_buffer: 显示器对象显示缓存,只有摄像机设备才有效
 * 
*/


typedef struct display_object {
 char *object_path;
    struct object_data
    {
        int object_width;
        int object_height;
        int object_buffer_size;
        color_mode_t color_mode;   
    }object_data_t;
 uint8_t virtual_display_object;   //0:real display object 1:virtual display object
 uint8_t object_type;              //0:displaye_object 1:carema_object  
 int displaye_Priority;            //if this object = 0 system will not use it to display desktops
 int Offset_X;                     //显存上映射像素左上角位置
 int Offset_Y;                     //与Offset_X对应，表示映射像素左上角位置坐标
 int (*set_coordinate)(int x_coordinate, int y_coordinate, int width, int height);
 int (*draw_object)(void *picture,int pixel_num);
 uint32_t *object_display_buffer;  //摄像机设备的显示缓存
}display_object_t;


int insert_new_display_object(display_object_t *new_object); 


#endif

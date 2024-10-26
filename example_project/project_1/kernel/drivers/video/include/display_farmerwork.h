#ifndef __DISPLAY_FARMERWORK_H__
#define __DISPLAY_FARMERWORK_H__
#include <stdio.h>
#include <linux/of.h>
#include <linux/types.h>

#define display_buffer  1024//pixel 
#define sys_color_mode      RGB_565

/**
 * 
 * @brief display_device_t
 * @note  设备树节点
 * @param name: 设备名称
 * @param node: 设备树节点名称,不需要用户填写
 * @param data: 设备数据结构体,包含设备的状态,宽度,高度,缓冲区大小,像素格式,偏移量等信息
 * @param init: 初始化函数指针,用于初始化显示设备
 * @param display: 显示函数指针,用于显示图像
 * 
 * 
*/

typedef struct {
    uint8_t r; // 红色通道
    uint8_t g; // 绿色通道
    uint8_t b; // 蓝色通道
    uint8_t a; // Alpha 通道
} RGBA8888;

typedef struct {
    uint8_t c; // 青色通道
    uint8_t m; // 品红通道
    uint8_t y; // 黄色通道
    uint8_t k; // 黑色通道
} CMYK;

typedef struct {
    uint8_t r;  // 红色通道
    uint8_t g;  // 绿色通道
    uint8_t b;  // 蓝色通道
} RGB888;

typedef struct {
    uint16_t r;  // 红色通道
    uint16_t g;  // 绿色通道
    uint16_t b;  // 蓝色通道
} RGB565;



struct object_data {
    int status;           // 设备状态
    int *width;            // 显示设备宽度
    int *height;           // 显示设备高度
    int *buffer_size;      // 显示设备缓冲区大小
    int  *pixel_format;     // 像素格式
    int *offset_x;         // 显存上的 x 偏移量
    int *offset_y;         // 显存上的 y 偏移量
};

typedef struct display_device {
    const char *name;                // 设备名称
    const char *node;                // 设备树节点
    struct object_data data;          // 设备数据
    int (*init)(void); // 初始化函数
    size_t (*display)(int x, int y, int width, int height, void *picture); // 显示函数
} display_device_t;

int display_object_add(struct display_device *obj);

#endif

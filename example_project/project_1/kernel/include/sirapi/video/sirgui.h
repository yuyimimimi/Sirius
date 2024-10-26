#ifndef _SIRGUI_H_
#define _SIRGUI_H_

#include <linux/types.h>

#define RGB(r, g, b) ((r << 16) | (g << 8) | b)


typedef struct {
    int x_offset;         // 窗口的 x 偏移
    int y_offset;         // 窗口的 y 偏移
    int width;            // 窗口的宽度
    int height;           // 窗口的高度
    __u8 IsVisible;       // 窗口是否可见
    char *Title;          // 窗口标题

} WindowAttributes;

typedef struct {
    int color_format;      // 窗口的颜色格式
    __u32 BackgroundColor; // 窗口的背景颜色
    __u8 Margin;           // 窗口的边距
    __u32 MarginColor;     // 窗口的边框颜色
} WindowStyle;



typedef struct {
    WindowAttributes attributes;  // 窗口基本属性
    WindowStyle appearance;       // 窗口外观
} Window;







#endif // _SIRGUI_H_
#ifndef _WINDOWS_H_
#define _WINDOWS_H_

#include <stdint.h>

// 定义窗口句柄类型
typedef struct {
    int width;
    int height;
    void* private_data; // 用于保存窗口相关的私有数据
} HWND;

// 窗口管理 API
HWND* CreateWindow(const char* title, int width, int height);
void DestroyWindow(HWND* window);
void ShowWindow(HWND* window);
void HideWindow(HWND* window);

// 绘图操作 API
void FillRect(HWND* window, int x, int y, int width, int height, uint32_t color);
void DrawText(HWND* window, int x, int y, const char* text, uint32_t color);

// 刷新窗口内容
void UpdateWindow(HWND* window, int offset_x, int offset_y, int width, int height, uint32_t* buffer);



#endif /* _WINDOWS_H_ */
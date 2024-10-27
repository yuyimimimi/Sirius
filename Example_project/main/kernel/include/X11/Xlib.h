#ifndef _XLIB_H_
#define _XLIB_H_
typedef struct Display {
    int dummy;
} Display;
    
typedef unsigned Window {
    int dummy;
};


typedef struct {
    Display *display;  // X11显示
    Window window;     // 窗口
    int width;         // 窗口宽度
    int height;        // 窗口高度
    char *title;   // 窗口标题
} WindowManager;




#endif /* _XLIB_H_ */
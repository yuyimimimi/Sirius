#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "lvgl/lvgl.h"
#include "lv_port_disp.h"
#include "lv_demos.h"

#include "lv_port_indev_template.h"
#include <pthread.h>
#include <unistd.h>  // For usleep


static int run = 0;

static IRAM_ATTR void lvgl_0(void *arg){
    lv_demo_benchmark();
    while (run){
        vTaskDelay(4);
        lv_task_handler();
    }
    lv_task_handler();           // 处理剩余事件
    lv_obj_clean(lv_scr_act());  // 清空活动屏幕上的所有对象
    lv_deinit();                 // 关闭 LVGL 子系统
    printf("lvgl_0 task exiting\n");  // 确认退出
    vTaskDelete(NULL); 
}

static IRAM_ATTR void lvgl_1(void *arg){
    lv_demo_music();
    while (run){
        vTaskDelay(4);
        lv_task_handler();
    }
    lv_task_handler();           // 处理剩余事件
    lv_obj_clean(lv_scr_act());  // 清空活动屏幕上的所有对象
    lv_deinit();                 // 关闭 LVGL 子系统
    printf("lvgl_0 task exiting\n");  // 确认退出
    vTaskDelete(NULL); 
}


static int lv_demo_0(int argc, char *argv[]){
    if(run == 1){
        run = 0;
        vTaskDelay(4);
    }
    if(argc < 2){
        printf("lv_demo 0 : lv_demo_benchmark\n");
        printf("lv_demo 1 : lv_demo_music \n");
        return 0;
    }
    if(argv[1][0] == '0'){
        run = 1;
        lv_init();           // lvgl内核初始化   
        lv_port_disp_init(); // lvgl显示接口初始化
        lv_port_indev_init();
        printf("lv_demo_benchmark\n");
        xTaskCreate(lvgl_0, "lvgl_task", 1024*16, NULL, 7 , NULL);    
    }
    else if(argv[1][0] == '1' ){
        run = 1;
        lv_init();           // lvgl内核初始化   
        lv_port_disp_init(); // lvgl显示接口初始化
        lv_port_indev_init();
        printf("lv_demo_music\n");
        xTaskCreate(lvgl_1, "lvgl_task", 1024*16, NULL, 7 , NULL);    
    }
    return 0;
}

#include "app_install.h"
void lv_demo_install(void)
{
    char * help_msg = "run lv_demo to start lvgl demo ";
    add_console_app("lv_demo", lv_demo_0, help_msg );
}

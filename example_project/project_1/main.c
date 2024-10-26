
#include "kinit.h"
#include <linux/init.h>
#include <linux/module.h>


// void stop_watch_dog(void);
// AppInit_init(stop_watch_dog);



int __init int_display_system(); //显示设备子系统模块初始化
module_init(int_display_system);

int __init button0_driver_init(void);
module_init(button0_driver_init);

int __init i2c_2_dev_init(void);
module_init(i2c_2_dev_init);

int __init i2c_1_dev_init(void);
module_init(i2c_1_dev_init);

int __init spi_init(void);
module_init(spi_init);


int __init st7789_driver_init(void);
module_init(st7789_driver_init);

void add_i2cdetect_console_app(void);
AppInit_init(add_i2cdetect_console_app);

void add_pikapython_console_app(void);
AppInit_init(add_pikapython_console_app);

void add_clock_tets_console_app(void);
AppInit_init(add_clock_tets_console_app);





//espidf中只有rsicv gcc支持module_init初始化宏，如果模块没有被正确链接请注释上方所有部分并使用下面代码

// int __init int_display_system(); //显示设备子系统模块初始化
// int __init button0_driver_init(void);
// int __init i2c_2_dev_init(void);
// int __init i2c_1_dev_init(void);
// int __init spi_init(void);
// int __init st7789_driver_init(void);
// void add_i2cdetect_console_app(void);
// void add_pikapython_console_app(void);
// void add_clock_tets_console_app(void);
// void start_console(void);
// void __init __init__(void);
// void app_main(){
// __init__();
// button0_driver_init();
// i2c_2_dev_init();
// i2c_1_dev_init();
// spi_init();
// add_i2cdetect_console_app();
// add_pikapython_console_app();
// add_clock_tets_console_app();
// start_console();
//}


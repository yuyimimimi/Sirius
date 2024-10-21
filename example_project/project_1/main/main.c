#include "kinit.h"
#include <linux/init.h>
#include <linux/module.h>


int __init button0_driver_init(void);
int __init i2c_2_dev_init(void);
int __init i2c_1_dev_init(void);
int __init spi_init(void);
void add_i2cdetect_console_app(void);
void add_pikapython_console_app(void);
void add_clock_tets_console_app(void);


module_init(__init__);
module_init(button0_driver_init);
module_init(i2c_2_dev_init);
module_init(i2c_1_dev_init);
module_init(spi_init);
AppInit_init(add_i2cdetect_console_app);
AppInit_init(add_pikapython_console_app);
AppInit_init(add_clock_tets_console_app);




//espidf中只有rsicv gcc支持module_init初始化宏，如果模块没有被正确链接请注释"kinit.h"以及所有始化宏
//初始化宏只会在mian.c中生效

// void start_console(void);
// void __init __init__(void);
// void app_main(){
// __init__();
// button0_driver_init();
// i2c_2_dev_init();
// i2c_1_dev_init();
// spi_init();
// add_i2cdetect_console_app();
// add_pikapython_console_app();ls

// add_clock_tets_console_app();
// start_console();
//}




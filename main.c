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





module_init(button0_driver_init);                  //Xtensa GCC is not support module_init ,you can use app_main() instead
module_init(i2c_2_dev_init);                       //if you use rsicv toolchain,you can use module_init
module_init(i2c_1_dev_init);
module_init(spi_init);
AppInit_init(add_i2cdetect_console_app);
AppInit_init(add_pikapython_console_app);
AppInit_init(add_clock_tets_console_app);


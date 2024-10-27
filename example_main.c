#include "kinit.h"
#include <linux/init.h>
#include <linux/module.h>

int __init button0_driver_init(void);
module_init(button0_driver_init);

int __init i2c_2_dev_init(void);
module_init(i2c_2_dev_init);

int __init spi_init(void);
module_init(spi_init);

int __init i2c_1_dev_init(void);
module_init(i2c_1_dev_init);

int __init st7789_driver_init(void);
module_init(st7789_driver_init);
void add_i2cdetect_console_app(void);
AppInit_init(add_i2cdetect_console_app);

void add_pikapython_console_app(void);
AppInit_init(add_pikapython_console_app);

void add_clock_tets_console_app(void);
AppInit_init(add_clock_tets_console_app);


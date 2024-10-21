#ifndef __GPIO_SET_H__
#define __GPIO_SET_H__
#include <linux/module.h>
#include <linux/gpio/consumer.h>

#define GPIO_chip_ENABEL    1
void set_gpio_config(struct gpio_dev_info *gpio_dev_info);
void gpio_d_set_level(int gpio_num,int level);
int  gpio_d_get_level(int gpio_num);
void release_gpio_config(struct gpio_dev_info *gpio_dev_info);


#endif
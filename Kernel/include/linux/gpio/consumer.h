#ifndef __LINUX_GPIO_CONSUMER_H
#define __LINUX_GPIO_CONSUMER_H

#include <stdio.h>

struct gpio_dev_info {
    int gpio_num;        //gpio number
    struct gpio_cofg
    {
        int direction;   //0:output, 1:input
        int pull;        //0:none,   1:up,    2:down        
    }gpio_cofg_t;
    char *dev_label;               //device label
    int used;                       //1:unused, 0:used (资源信号量)
    uint32_t user_device_number;   //user device number 可以是传递到用户空间的gpio设备号 也可以是占用该gpio驱动的设备号
};


#endif //__LINUX_GPIO_CONSUMER_H

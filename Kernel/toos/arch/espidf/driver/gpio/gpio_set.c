#include "driver/gpio.h"
#include <linux/gpio/consumer.h>
#include <linux/errno.h>

char *dev_name = "GPIO";
void set_gpio_config(struct gpio_dev_info *gpio_dev_info)
{
    gpio_config_t GPIO_Init_struct = {};
    GPIO_Init_struct.intr_type = GPIO_INTR_DISABLE;

    GPIO_Init_struct.pin_bit_mask = 1ULL <<  gpio_dev_info->gpio_num;
    
    if(gpio_dev_info->gpio_cofg_t.direction == 0) GPIO_Init_struct.mode = GPIO_MODE_INPUT;
    else                                          GPIO_Init_struct.mode = GPIO_MODE_OUTPUT;
    
    if(gpio_dev_info->gpio_cofg_t.pull == 1){
        GPIO_Init_struct.pull_up_en = 1;
        GPIO_Init_struct.pull_down_en = 0;
    }
    else if(gpio_dev_info->gpio_cofg_t.pull == 2){
        GPIO_Init_struct.pull_up_en = 0;
        GPIO_Init_struct.pull_down_en = 1;
    }
    else{
        GPIO_Init_struct.pull_up_en = 0;
        GPIO_Init_struct.pull_down_en = 0;
    }
    
    int ret = gpio_config(&GPIO_Init_struct);
    if(ret != EXIT_SUCCESS) pr_err(dev_name,"GPIO config error");
    else gpio_dev_info->used = 0;
}

void gpio_d_set_level(int gpio_num,int level){
    gpio_set_level(gpio_num,level);
}

int gpio_d_get_level(int gpio_num){
    return gpio_get_level(gpio_num);
}

void release_gpio_config(struct gpio_dev_info *gpio_dev_info){
    gpio_dev_info->used = 1;
}


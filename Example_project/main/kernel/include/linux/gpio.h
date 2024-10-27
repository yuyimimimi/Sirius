#ifndef _LINUX_GPIO_H
#define _LINUX_GPIO_H

#include <linux/types.h>
#include <linux/init.h>
#include <linux/gpio/consumer.h>
#include <stdint.h>

#define GPIO_MAJOR 244

typedef enum gpio_pull_t{
    GPIO_PULLUP,
    GPIO_PULLDOWN,
    GPIO_PULLNONE,
};

/**
 * @brief Request a GPIO line gpionum ,device name and device number
 * device name can use null
 * if you use it in driver,please use your device_number from your driver 
 *  
*/
int gpio_request(unsigned gpio_num,const char *label, uint32_t device_number );

/**
 * @brief Free a GPIO line
 * you need to free a GPIO line after use it
 * 
*/
int gpio_free(int gpio_num);

/**
 * @brief Set the direction of a GPIO line to input or output
 * @param gpio_num: the number of the GPIO line
 * @param value: 1 for output, 0 for input
*/
int gpio_direction_input(int gpio_num);

/**
 * @brief Set the direction of a GPIO line to output and set the output value
 * @param gpio_num: the number of the GPIO line
 * @param value: the output value, 1 or 0   
*/

int gpio_direction_output(int gpio_num,int value);
/**
 * @brief Get the value of a GPIO line
 * @param gpio_num: the number of the GPIO line
 * @return the value of the GPIO line, 1 or 0
*/

int gpio_get_value(int gpio_num);
/**
 * @brief Set the value of a GPIO line
 * @param gpio_num: the number of the GPIO line
 * @param value: the output value, 1 or 0
*/
int gpio_set_value(int gpio_num,int value);

/**
 * @brief Set the pull-up or pull-down resistor for a GPIO line
 * @param gpio_num: the number of the GPIO line
 * @param pull: the pull-up or pull-down resistor, GPIO_PULLUP or GPIO_PULLDOWN
*/
int gpio_set_pullupdown(int gpio_num,enum gpio_pull_t pull);
/**
* @brief Get the gpio number by device number
* @param device_number: the device number
* @param gpio_list: the gpio list
* @return the gpio count
*/
int get_gpio_num_by_dev_number(const uint32_t device_number,int **gpio_list);


int check_is_gpio_in_using_io_number(int gpio_num); //检查gpio是否被使用


int get_gpio_direction(int gpio_num); //获取gpio方向

/**
 * user needn't use this function
*/
void __init gpio_subsystem_init(void);



#endif /* _LINUX_GPIO_H */
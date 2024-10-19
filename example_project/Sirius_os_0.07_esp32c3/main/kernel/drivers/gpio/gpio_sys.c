#include <linux/uaccess.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/errno.h>
#include <linux/printk.h>
#include <linux/slab.h>
#include <linux/init.h>
#include <linux/mutex.h>
#include <linux/gpio/consumer.h>
#include <linux/gpio.h>
#include <fcntl.h>
#include <linux/of.h>
#include "gpio_set.h"

/**
 * @file gpio_chip.c
 * @brief GPIO chip for any chip that has a GPIO controller.
 * @author <NAME>
 * @date 2019-07-01
 * @version 0.04.0
 * @copyright (c) 2019-2020 53224
 * 
 * @section LICENSE
 * 
 * you divice port all in /arch/structure/devicename/include/gpio_chip.h
 * 
*/


#define min(a,b) ((a)<(b)?(a):(b))

#if (                            GPIO_chip_ENABEL == 1)
#define GPIO_chip_DEV_NAME "gpio_chip"
  
struct gpio_dev_info *gpio_dev_info_array;
static const  char*    dev_name     = GPIO_chip_DEV_NAME;
static int gpio_pin_num = 12;


int  gpio_driver_init(void);

static struct device_node *gpio_node;

void __init gpio_subsystem_init(void)      //初始化gpio子系统
{
    char *gpiio_path = "/gpio_dev/gpio-controller";
    gpio_node = of_find_node_by_path(gpiio_path);
    if (gpio_node == NULL){
        pr_err(dev_name,"gpio_node is NULL");
    }
    else
    {
        int *gpio_number = of_get_property(gpio_node, "ngpios", NULL);
        if(gpio_number == NULL)
        {
            pr_err(dev_name,"ngpios is NULL");
        }
        else
        {
            gpio_pin_num = gpio_number[0];
        }
        free(gpio_number);
        of_node_put(gpio_node);    
    }


   gpio_dev_info_array =(struct gpio_dev_info*)vmalloc(sizeof(struct gpio_dev_info)*gpio_pin_num);
   if(gpio_dev_info_array == NULL)
   {
       pr_err(dev_name,"vmalloc error");
       return;
   }
   else
   {
       for(int i=0;i<gpio_pin_num;i++)
       {
           gpio_dev_info_array[i].gpio_num = i;
           gpio_dev_info_array[i].gpio_cofg_t.pull  = 0;
           gpio_dev_info_array[i].gpio_cofg_t.direction = 0;
           gpio_dev_info_array[i].user_device_number = 0;
           gpio_dev_info_array[i].dev_label = NULL;
           gpio_dev_info_array[i].used = 1;
       }
   }
   gpio_driver_init();
}


static inline bool is_valid_gpio(int gpio_num)
{
    if(gpio_num < 0 || gpio_num >= gpio_pin_num)
    {
        return false;
    }
    return true;
}



int gpio_request(unsigned gpio_num,const char *label, uint32_t device_number )//申请使用gpio
{
    if(is_valid_gpio(gpio_num) == false){
        return -EINVAL;
    }
    struct mutex i2c_1_dev_mutex; 
    mutex_init(i2c_1_dev_mutex);
    mutex_lock(i2c_1_dev_mutex);                                        //进入临界区

     if(gpio_dev_info_array[gpio_num].used == 1) //该gpio信号量为1 
     { 
       gpio_dev_info_array[gpio_num].used-- ;                            //申请成功 信号量减1
       mutex_unlock(i2c_1_dev_mutex);                                    //释放临界区
       mutex_destroy(i2c_1_dev_mutex);                                   //销毁临界区
       gpio_dev_info_array[gpio_num].user_device_number = device_number; //绑定用户设备号
       gpio_dev_info_array[gpio_num].dev_label = label;                  //绑定设备标签(可以为空)
       gpio_dev_info_array[gpio_num].gpio_cofg_t.direction = 0;          //重置方向为默认值
       gpio_dev_info_array[gpio_num].gpio_cofg_t.pull = 0;               //重置方向和上拉下拉为默认值
       return 0;
     }
     else //该gpio信号量为0 申请失败
     {
       pr_err(dev_name,"gpio %d is busy\n",gpio_num);
       if(gpio_dev_info_array[gpio_num].dev_label!= NULL)
       pr_err(dev_name,"device %s is using this gpio pleace release it first\n",gpio_dev_info_array[gpio_num].dev_label);
       return -EBUSY;
     }
}



int gpio_free(int gpio_num) //释放gpio
{
    if(is_valid_gpio(gpio_num) == false){
        return -EINVAL;
    }
    gpio_dev_info_array[gpio_num].used=1;
    return 0;
}


int gpio_direction_input(int gpio_num) //设置gpio为输入
{
    if(is_valid_gpio(gpio_num) == false){
        return -EINVAL;
    }
    gpio_dev_info_array[gpio_num].gpio_cofg_t.direction = 0;
    set_gpio_config(&gpio_dev_info_array[gpio_num]);
    return 0;
}


int gpio_direction_output(int gpio_num,int value) //设置gpio为输出
{
    if(is_valid_gpio(gpio_num) == false){
        return -EINVAL;
    }
    gpio_dev_info_array[gpio_num].gpio_cofg_t.direction = 1;
    set_gpio_config(&gpio_dev_info_array[gpio_num]);
    gpio_d_set_level(gpio_num,value);
    return 0;
}

int gpio_get_value(int gpio_num)                       //获取gpio输入值
{
    return gpio_d_get_level(gpio_num);
}

int gpio_set_value(int gpio_num,int value)             //设置gpio输出值
{
    gpio_d_set_level(gpio_num,value);
    return 0;
}

int gpio_set_pullupdown(int gpio_num,enum gpio_pull_t pull) //设置gpio上拉下拉
{
    if(is_valid_gpio(gpio_num) == false){
        return -EINVAL;
    }
    if(pull == GPIO_PULLUP){
        gpio_dev_info_array[gpio_num].gpio_cofg_t.pull = 1;
    }
    else if(pull == GPIO_PULLDOWN){
        gpio_dev_info_array[gpio_num].gpio_cofg_t.pull = 2;
    }
    else{
        gpio_dev_info_array[gpio_num].gpio_cofg_t.pull = 0;
    }
    set_gpio_config(&gpio_dev_info_array[gpio_num]);
    return 0;
}

int get_gpio_num_by_dev_number(const uint32_t device_number,int **gpio_list)           //根据设备号获取gpio列表
{
    int gpio_list_length = 0;
    for(int i=0;i<gpio_pin_num;i++){
        if(gpio_dev_info_array[i].used == 0 && gpio_dev_info_array[i].user_device_number == device_number ){
           gpio_list_length++;
        }
    }
    if(gpio_list_length == 0)    return -EINVAL;
    
    *gpio_list = (int*)vmalloc(sizeof(int)*gpio_list_length);
    int k = 0;
    for(int i=0;i<gpio_pin_num;i++)
    { 
        if(gpio_dev_info_array[i].used == 0 && gpio_dev_info_array[i].user_device_number == device_number )
        {
           *gpio_list[k] = i;
           k++;
        }
    }
    return gpio_list_length;
}

int check_is_gpio_in_using_io_number(int gpio_num) //检查gpio是否被使用
{
    if(is_valid_gpio(gpio_num) == false){
        return -EINVAL;
    }
    if(gpio_dev_info_array[gpio_num].used <= 0)
    {
        return 1;
    }
    return -1;
}


int get_gpio_direction(int gpio_num) //获取gpio方向
{
    if(is_valid_gpio(gpio_num) == false){
        return -EINVAL;
    }
    return gpio_dev_info_array[gpio_num].gpio_cofg_t.direction;
}


#elif
void __init gpio_subsystem_init(void)  {};
int gpio_request(unsigned gpio_num,const char *label, uint32_t device_number )  {return -ENOSYS;};
int gpio_free(int gpio_num)  {return -ENOSYS;};
int gpio_direction_input(int gpio_num)  {return -ENOSYS;};
int gpio_direction_output(int gpio_num,int value)  {return -ENOSYS;};
int __gpio_get_value(int gpio_num)  {return -ENOSYS;};
int __gpio_set_value(int gpio_num,int value)  {return -ENOSYS;};
int gpio_set_pullupdown(int gpio_num,enum gpio_pull_t pull)  {return -ENOSYS;};
int get_gpio_num_by_dev_number(const uint32_t device_number,int *gpio_list)  {return -ENOSYS;};
int check_is_gpio_in_using_io_number(int gpio_num)  {return -ENOSYS;};
#endif

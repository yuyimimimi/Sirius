#include <linux/gpio.h>          
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/errno.h>
#include <linux/init.h>
#include <linux/uaccess.h>
#include <linux/bits.h>
#include <linux/types.h>                                     
#include <linux/printk.h>
#include <stdio.h>
#include <string.h>
#include <linux/of.h>
#include <string.h>

/**
 * Do not change anythings in this file, allow you want use it in other platfroms.
 * you can change all tings in dts file;
 * module_init and module_exit is interface only 
*/


#define GPIO_DRIVER_NAME "gpiochip"
#define GPIO_DEV_NAME    "gpio-%d"
#define min(a,b) ((a)<(b)?(a):(b))

static char *gpio_chip_name = GPIO_DRIVER_NAME;
static char *gpio_dev_name  = GPIO_DEV_NAME;
static int   max_pin_num = 10;

static __u16 major =  GPIO_MAJOR;



static int gpio_value_open(void* ctx, const char * path, int flags, int mode)
{
    return 0;
}
static ssize_t gpio_value_read(void* ctx,int fd, void *buf, size_t count)
{
    printf("gpio_read\n");
    unsigned int *device_number =  (unsigned int*)ctx;                                                       
    int *pin_num;
    int length = get_gpio_num_by_dev_number(device_number[0], &pin_num);
    if(length < 0)
    {
        return -1;
    }
    __u8 value = gpio_get_value(pin_num[0]);
    copy_to_user(buf, &value, 1);
    free (pin_num);
    return 0;
}

static ssize_t gpio_value_write(void* ctx, int fd, const void * data, size_t size)
{
    unsigned int *device_number =  (unsigned int*)ctx;   
    char   value;
    copy_from_user(&value, data, 1);
    int *pin_num = NULL;
    if(get_gpio_num_by_dev_number(device_number[0], &pin_num) > 0)
    {
        if(value == '0')
        {
            gpio_set_value(pin_num[0], 0);        
        }

        else if(value == '1')
        {
            gpio_set_value(pin_num[0], 1);        
        }
        else
        {
            printf("invalid value\n");
        }
        free (pin_num);
    }
    return 0;
}
static int gpio_value_release(void* ctx, int fd)
{
    return 0;
}
static file_operations_t gpio_value   = {
    .open_p    = &gpio_value_open,
    .read_p    = &gpio_value_read,
    .write_p   = &gpio_value_write,
    .close_p   = &gpio_value_release,
};


static int gpio_direction_open(void* ctx, const char * path, int flags, int mode){return 0;}
static ssize_t gpio_direction_read(void* ctx,int fd, void *buf, size_t count){return 0;}
static ssize_t gpio_direction_write(void* ctx, int fd, const void * data, size_t size)
{   int *pin_num = NULL;
    unsigned int *device_number =  (unsigned int*)ctx;   
    if(get_gpio_num_by_dev_number(device_number[0], &pin_num) > 0)
    {
        char buffer[10];
        copy_from_user(buffer, data, min(size, sizeof(char)*10));
        buffer[min(size, sizeof(char)*10)] = '\0';
        if(strcmp(buffer, "in") == 0)
        {
           gpio_direction_input(pin_num[0]);
        }
        else if(strcmp(buffer, "out") == 0)
        {
           gpio_direction_output(pin_num[0],0); //set output value to 0
        }
        else{
            printf("invalid direction\n");
        }
        free (pin_num);
    }
    return 0;
}
static int gpio_direction_release(void* ctx, int fd){return 0;}

static file_operations_t gpio_direction = {
    .open_p    = &gpio_direction_open,
    .read_p    = &gpio_direction_read,
    .write_p   = &gpio_direction_write,
    .close_p   = &gpio_direction_release,
};

static struct device_node *gpio_node;

static int get_device_data_from_dts(void)
{
    char *gpiio_path = "/gpio_dev/gpio-controller";
    gpio_node = of_find_node_by_path(gpiio_path);
    int *gpio_count = of_get_property(gpio_node, "ngpios", NULL);
    if(gpio_count == NULL) max_pin_num = 10; //default value
    else
    {
        max_pin_num = *gpio_count;
        free(gpio_count);
        printk(KERN_INFO  "max_pin_num:%d\n",max_pin_num);        
    } 

    int *dev_major = of_get_property(gpio_node, "reg", NULL);
    if(dev_major == NULL) major =  GPIO_MAJOR; //default value
    else 
    {
      major = *dev_major;
      free(dev_major);     
      printk(KERN_INFO  "major:%d\n",major);
    }


    char *gpio_chip_name_tmp = of_get_property(gpio_node, "compatible", NULL);
    if(gpio_chip_name_tmp == NULL) gpio_chip_name = GPIO_DRIVER_NAME; //default value
    else 
    {
       gpio_chip_name = gpio_chip_name_tmp;
       free(gpio_chip_name_tmp);  
       printk(KERN_INFO  "gpio_chip_name:%s\n",gpio_chip_name);
    }
    of_node_put(gpio_node);

    return 0;
}


static int gpiochip_open(void* ctx,const char * path, int flags, int mode){return 0;}
static ssize_t gpiochip_write(void* ctx,int fd,const void *buf, size_t count)
{   
    char gpio_pin_num[] = {'\0','\0','\0'};
    copy_from_user (&gpio_pin_num, buf, min(count, sizeof(char)*3));
    int pin_num = 0;
    
    if(gpio_pin_num[0]=='\0'){
        return -1;
    }
    else if(gpio_pin_num[1]=='\0'){
        pin_num = gpio_pin_num[0] - '0';
    }
    else if(gpio_pin_num[2]=='\0'){
        pin_num = (gpio_pin_num[0] - '0')*10 + (gpio_pin_num[1] - '0');
    }
    else{
        pin_num = (gpio_pin_num[0] - '0')*100 + (gpio_pin_num[1] - '0')*10 + (gpio_pin_num[2] - '0');
    }

    printf("gpio_pin_num:%d\n",pin_num);

    if(check_is_gpio_in_using_io_number(pin_num) == 1)
    {
        printk("GPIO busy\n");
        return -1;
    }
    __u32 device_number = register_chrdev(major, "gpio-%d/v", &gpio_value,pin_num); //注册设备,将设备导出到用户空间
    if ((device_number & 0x0000ffff )== 0) 
    {
        return -1;
    }
    gpio_request(pin_num, gpio_dev_name,device_number);                               //请求gpio口  
    register_chrdev(device_number, "gpio-%d/d", &gpio_direction, pin_num);            //注册gpio口方向设备
    return 0;
}

static int gpiochip_release(void* ctx, int fd){return 0;}
static ssize_t gpiochip_read(void* ctx, int fd, void *buf, size_t count){return 0;}
static file_operations_t gpiochip_fops = {
    .open_p  = &gpiochip_open,
    .close_p = &gpiochip_release, 
    .read_p  = &gpiochip_read,
    .write_p = &gpiochip_write,
};
int __init gpio_driver_init(void)
{
    if(get_device_data_from_dts() < 0)return -1;
    register_chrdev(major, gpio_chip_name, &gpiochip_fops);
    return 0;
}

// void __exit gpio_driver_exit(void)
// {
//  unregister_chrdev(major, gppio_chip_name);
// }

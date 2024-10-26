#include "linux/uaccess.h"
#include "linux/fs.h"
#include "linux/errno.h"
#include "linux/printk.h"
#include "linux/slab.h"
#include <linux/module.h>
#include <linux/init.h>
#include <linux/of.h>
#include <linux/gpio.h>

#define min(a,b) ((a)<(b)?(a):(b))

static char*               button0_buffer;
static int                 button0_dev_major;
static const char*         button0_TAG = "BUTTON0_DRIVER";
static char                button0_pin = 0;
static int                 PULL_DOWN_BUTTON;
static int                 PULL_UP_BUTTON;

static int          button0_init(void);
static ssize_t      button0_read(void *p,int fd, void *buf, size_t count);
static int          button0_open(void *p,const char *path, int flags, int mode);
static int          button0_close(void *p,int fd);

static struct device_node *device_data = NULL;
static __init int button_data_from_dtb(void)
{
    char *path = "/button@0";
    device_data = of_find_node_by_path(path);
    if(device_data == NULL){printk(KERN_INFO "Button: Can not find device node %s\n", path);return -1;}

    char *data1 = (char*)of_get_property(device_data, "status", NULL);
    if(data1 == NULL){return -1; printk(KERN_INFO "Button: Button driver init failed ,please check 'status' in dts file\n");}
    if(data1[0] != 'o'){return -1; printk(KERN_INFO "Button: Button driver is Desabled\n");}
    printk(KERN_INFO "Button: Button driver status:%s\n", data1);
    free(data1);

    int *data = (int*)of_get_property(device_data, "pin", NULL);
    if(data == NULL){return -1;}
    button0_pin = *data;free(data);
    printk(KERN_INFO "BButton: utton driver pin:%d\n", button0_pin);

    data = (int*)of_get_property(device_data, "pull-up", NULL);
    if(data == NULL){printk(KERN_INFO "Button: Button driver init failed\n");return -1; }
    PULL_UP_BUTTON = *data;free(data);
    printk(KERN_INFO "Button: Button driver pull-up:%d\n", PULL_UP_BUTTON);

    data = (int*)of_get_property(device_data, "pull-down", NULL);
    if(data == NULL){printk(KERN_INFO "Button: Button driver init failed\n");return -1;}
    PULL_DOWN_BUTTON = *data;free(data);
    printk(KERN_INFO "Button: Button driver pull-down:%d\n", PULL_DOWN_BUTTON);
 
    data = (int*)of_get_property(device_data, "major", NULL);
    if(data == NULL){ button0_dev_major = 0;}
    button0_dev_major = *data;free(data); 
    printk(KERN_INFO "Button: Button driver major:%d\n", button0_dev_major);
    return 0;
}

static file_operations_t button0_fops = {
   .open_p  = &button0_open, 
   .write_p = NULL,
   .read_p  = &button0_read,
   .close_p = &button0_close,
   .ioctl_p = NULL,
};
static int  button0_init(void){
    if(gpio_request(button0_pin, "button0",0) != 0){
        if(device_data != NULL){of_node_put(device_data);}
        printk(KERN_INFO "Button: gpio busy or invalid pin\n");
        return -1;
    }
    of_node_put(device_data);
    if(PULL_UP_BUTTON == 1){gpio_direction_input(button0_pin);}
    else{gpio_direction_output(button0_pin, 1);}
    return 0;
}
int __init button0_driver_init(void){       
  if(button_data_from_dtb () != 0)return -1;                                                               
  if(button0_init() != 0)return -1;                                                                         
  button0_buffer = (char*)vmalloc(sizeof(char)*8);  
  if(button0_buffer == NULL){
      printk(KERN_INFO "Button: Button driver init failed\n");
      return -1;
  }
  button0_dev_major = register_chrdev(button0_dev_major, "button-1", &button0_fops);  
  if((button0_dev_major&0xffff)>0){                                            
     printk(button0_TAG,"Button: USE pin:%d",button0_pin);                              
  }
  return 0;                                                                    
}          

static ssize_t button0_read(void *p,int fd, void *buf, size_t count){
    if(count > 1){
        return -EINVAL;
    }
    button0_buffer[0] = gpio_get_value(button0_pin);
    if(PULL_DOWN_BUTTON == 1){
         if(button0_buffer[0] == 0)
         button0_buffer[0] = '0';
         else
         button0_buffer[0] = '1';
    }else{
         if(button0_buffer[0] == 1)
         button0_buffer[0] = '0';
         else
         button0_buffer[0] = '1';
   }
    copy_to_user(buf, button0_buffer, min(count, 1));
    return count;
}

static int button0_open(void *p,const char *path, int flags, int mode){
    return 0;
}
static int button0_close(void *p,int fd){
    return 0;
}

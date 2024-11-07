#include <linux/errno.h>
#include <linux/module.h>
#include <linux/printk.h>
#include <linux/fs.h>
#include <linux/init.h>
#include <linux/uaccess.h>
#include <linux/delay.h>
#include <linux/i2c-dev.h>
#include <linux/slab.h>
#include <sys/ioctl.h>
#include <linux/mutex.h>
#include <linux/gpio.h>
#include <string.h>
#include <linux/of.h>
#include "driver/i2c.h"


#define  min(a,b) ((a)<(b)?(a):(b))
static int i2c_mode = I2C_MODE_MASTER;
static int i2c_master_port;
static int i2c_master_freq_hz;
static int i2c_master_sda_io;
static int i2c_master_scl_io;
static int i2c_master_rx_buf_disable;
static int i2c_master_tx_buf_disable;
static int i2c_buffer_size;
static char* I2C_TAG ="I2C_2"; 
static char* I2c_dev_name;
static uint16_t i2c_dev_major = I2C_MAJOR; 
static int i2c_dev_timeout_ms;


static uint8_t *i2c_dev_buffer;
static uint8_t  lock = 0;
static struct mutex i2c_dev_mutex;
static uint8_t  i2c_dev_addr;
static uint8_t  i2c_dev_ternbit;
static uint32_t i2c_retrans_times;



static struct device_node *i2c_dev_devicetree; 
static int get_i2c_dev_data_from_dtb(void)
{ 
    char *i2c_dev_path = "/i2c_dev/i2c@2";
    i2c_dev_devicetree = of_find_node_by_path(i2c_dev_path);
    if(i2c_dev_devicetree == NULL){printk(KERN_INFO "i2c_2_dev_init: i2c_dev_devicetree not found in dtb");return -1;}

    char  *data1 = (int *)of_get_property(i2c_dev_devicetree, "status", NULL);
    if(data1 == NULL){printk(KERN_INFO "i2c_1_dev_init: status not found in dtb");goto initfaled;}
    if(data1[0] != 'o'){printk(KERN_INFO "i2c_1_dev_init: i2c_dev_status not okay in dtb");goto initfaled;}
    printk(KERN_INFO "i2c_1_dev_init: i2c_dev_status okay in dtb");
    free(data1);


    int *data  = (int *)of_get_property(i2c_dev_devicetree, "port", NULL);
    if(data == NULL){printk(KERN_INFO "i2c_2_dev_init: i2c_master_port not found in dtb");goto initfaled;}
    i2c_master_port = *data;
    free(data);
    printk(KERN_INFO "i2c_2_dev_init: i2c_master_port is %d",i2c_master_port);
    data  = (int *)of_get_property(i2c_dev_devicetree, "freq_hz", NULL);
    if(data == NULL){printk(KERN_INFO "i2c_2_dev_init: i2c_master_freq_hz not found in dtb");goto initfaled;}
    i2c_master_freq_hz = *data;
    free(data);
    printk(KERN_INFO "i2c_2_dev_init: i2c_master_freq_hz is %d",i2c_master_freq_hz);
    data  = (int *)of_get_property(i2c_dev_devicetree, "sda_io", NULL);
    if(data == NULL){printk(KERN_INFO "i2c_2_dev_init: i2c_master_sda_io not found in dtb");goto initfaled;}
    i2c_master_sda_io = *data;
    free(data);
    printk(KERN_INFO "i2c_2_dev_init: i2c_master_sda_io is %d",i2c_master_sda_io);
    data  = (int *)of_get_property(i2c_dev_devicetree, "scl_io", NULL);
    if(data == NULL){printk(KERN_INFO "i2c_2_dev_init: i2c_master_scl_io not found in dtb");goto initfaled;}
    i2c_master_scl_io = *data;
    free(data);
    printk(KERN_INFO "i2c_2_dev_init: i2c_master_scl_io is %d",i2c_master_scl_io);
    data  = (int *)of_get_property(i2c_dev_devicetree, "rx_buf_enable", NULL);
    if(data == NULL){printk(KERN_INFO "i2c_2_dev_init: i2c_master_rx_buf_disable not found in dtb");goto initfaled;}
    i2c_master_rx_buf_disable = *data;
    free(data);
    printk(KERN_INFO "i2c_2_dev_init: i2c_master_rx_buf_disable is %d",i2c_master_rx_buf_disable);
    data  = (int *)of_get_property(i2c_dev_devicetree, "tx_buf_enable", NULL);
    if(data == NULL){printk(KERN_INFO "i2c_2_dev_init: i2c_master_tx_buf_disable not found in dtb");goto initfaled;}
    i2c_master_tx_buf_disable = *data;
    free(data);
    printk(KERN_INFO "i2c_2_dev_init: i2c_master_tx_buf_disable is %d",i2c_master_tx_buf_disable);
    data  = (int *)of_get_property(i2c_dev_devicetree, "buffer_size", NULL);
    if(data == NULL){printk(KERN_INFO "i2c_2_dev_init: i2c_buffer_size not found in dtb");goto initfaled;}
    i2c_buffer_size = *data;
    free(data);
    printk(KERN_INFO "i2c_2_dev_init: i2c_buffer_size is %d",i2c_buffer_size);
    data  = (int *)of_get_property(i2c_dev_devicetree, "timeout_ms", NULL);
    if(data == NULL){printk(KERN_INFO "i2c_2_dev_init: i2c_dev_timeout_ms not found in dtb");goto initfaled;}
    i2c_dev_timeout_ms = *data;
    free(data);
    printk(KERN_INFO "i2c_2_dev_init: i2c_dev_timeout_ms is %d",i2c_dev_timeout_ms);
    data  = (int *)of_get_property(i2c_dev_devicetree, "retrans_times", NULL);
    if(data == NULL){printk(KERN_INFO "i2c_2_dev_init: i2c_retrans_times not found in dtb");goto initfaled;}
    i2c_retrans_times = *data;
    free(data);
    printk(KERN_INFO "i2c_2_dev_init: i2c_retrans_times is %ld",i2c_retrans_times);
    char *i2c_dev_name_data = (char *)of_get_property(i2c_dev_devicetree, "name", NULL);
    if(i2c_dev_name_data == NULL){printk(KERN_INFO "i2c_2_dev_init: i2c_dev_name not found in dtb");goto initfaled;}
    I2c_dev_name = i2c_dev_name_data;
    of_node_put(i2c_dev_devicetree);
    return 0;

initfaled:
    of_node_put(i2c_dev_devicetree);
    return -1;
}


static void i2c_chino_init(void)
{

    i2c_config_t conf = {
        .mode = i2c_mode,
        .sda_io_num =                i2c_master_sda_io,
        .scl_io_num =                i2c_master_scl_io,
        .sda_pullup_en = 1,
        .scl_pullup_en = 1,
        .master.clk_speed =         i2c_master_freq_hz,
    };
    i2c_param_config(i2c_master_port, &conf);
};

static int get_gpio_pin(void)
{
    if(gpio_request(i2c_master_sda_io, "i2c_sda",i2c_dev_major) != 0){printk(KERN_INFO "i2c_1_dev_init: gpio_request sda failed");return -1;}
    if(gpio_request(i2c_master_scl_io, "i2c_scl",i2c_dev_major)!= 0){printk(KERN_INFO "i2c_1_dev_init: gpio_request scl failed");gpio_free(i2c_master_sda_io);return -1;}
    return 0;
}
static void release_gpio_pin(void)
{
    gpio_free(i2c_master_sda_io);
    gpio_free(i2c_master_scl_io); 
}
static int get_i2c_dev(void)
{
    mutex_lock(i2c_dev_mutex);
    i2c_chino_init();
    i2c_driver_install(i2c_master_port, i2c_mode, i2c_master_rx_buf_disable, i2c_master_tx_buf_disable,i2c_retrans_times);
    return 0;
}

static void release_i2c_dev(void)
{
    i2c_driver_delete(i2c_master_port);
    mutex_unlock(i2c_dev_mutex);
}
static int i2c_dev_open(void * p ,const char *path, int flags, int mode) 
{
    if(lock == 1){
        pr_err(I2C_TAG,"Device busy");
        return -EBUSY;
    }
    i2c_retrans_times = 0x00;
    i2c_dev_addr    = 0x00;
    i2c_dev_ternbit = 0x00;
    mutex_init(i2c_dev_mutex);
    lock = 1;
    return 0;
}
static int i2c_dev_release(void * p ,int fd) 
{  
    if (lock == 1){
       mutex_destroy(i2c_dev_mutex);
       lock = 0;
       return 0;
    }
    else{
        return -EINVAL;
    }
}
static int  i2c_dev_ioctl(void * p ,int fd, int cmd, va_list args)
{    
    int arg1; 
    arg1 = va_arg(args, int); 
    if(cmd == I2C_TENBIT){
        i2c_dev_ternbit = arg1;
    }
    if(cmd == I2C_RETRIES){
        i2c_retrans_times = arg1;
    }
    if(cmd == I2C_SLAVE){
        i2c_dev_addr    = arg1;    
    }
    return 0;
}
static ssize_t   i2c_dev_write(void * p ,int fd, const void *buf, size_t count) 
{
    copy_from_user(i2c_dev_buffer, buf, min(count, i2c_buffer_size));
    if(get_i2c_dev() != 0){
        return -EIO;
    }
    i2c_cmd_handle_t cmd = i2c_cmd_link_create();
	i2c_master_start(cmd);
	i2c_master_write_byte(cmd, i2c_dev_addr, true);
	i2c_master_write(cmd, i2c_dev_buffer,count, true);
	i2c_master_stop(cmd);
    int ret = i2c_master_cmd_begin(i2c_master_port, cmd, i2c_dev_timeout_ms);
    release_i2c_dev();   
    i2c_cmd_link_delete(cmd);
    if(ret != EXIT_SUCCESS){
     return -EIO;
    }
    return min(count, i2c_buffer_size);
}
static ssize_t i2c_dev_read(void * p ,int fd, void *buf, size_t count) 
{
    if( get_i2c_dev() != 0){
        return -EIO;
    }
    i2c_cmd_handle_t cmd = i2c_cmd_link_create();
	i2c_master_start(cmd);
	i2c_master_write_byte(cmd, i2c_dev_addr, true);
    i2c_master_read(cmd, i2c_dev_buffer,count, I2C_MASTER_NACK);
    i2c_master_stop(cmd);
    int ret = i2c_master_cmd_begin(i2c_master_port, cmd, i2c_dev_timeout_ms);
    release_i2c_dev();
    i2c_cmd_link_delete(cmd);
    if(ret != EXIT_SUCCESS)
    {
        return -EIO;
    }
    copy_to_user(buf, i2c_dev_buffer, min(count, i2c_buffer_size));
    return min(count, i2c_buffer_size);
}

static file_operations_t i2c_fops = {
    .open_p =  i2c_dev_open,
    .close_p = i2c_dev_release,
    .write_p = i2c_dev_write,
    .read_p =  i2c_dev_read,
    .ioctl_p = i2c_dev_ioctl,
};
int __init i2c_2_dev_init(void)
{
    printk(KERN_INFO "i2c_2_dev_init: i2c_2 device driver init");
    if(get_i2c_dev_data_from_dtb() != 0) {
        return -1;
    }
    if(get_gpio_pin() != 0) {
        return -1;
    }
    i2c_dev_buffer = (uint8_t *)vmalloc(sizeof(uint8_t) * i2c_buffer_size); // allocate a buffer for i2c communication
    i2c_dev_major = register_chrdev(i2c_dev_major, I2c_dev_name, &i2c_fops); // register the device driver
    if((i2c_dev_major&0xffff)>0)
    {
        printk(I2C_TAG,"USE_IO SCL:%d,SDA:%d",i2c_master_scl_io,i2c_master_sda_io);
        printk(I2C_TAG,"Speed: %d",i2c_master_freq_hz);
    }
    return 0;
}
void __exit i2c_2_dev_exit(void)
{
    release_gpio_pin();
    vfree(i2c_dev_buffer);
    unregister_chrdev(i2c_dev_major, I2c_dev_name);
}



#include <linux/errno.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/of.h>
#include <linux/gpio.h>
#include <linux/fs.h>
#include <linux/of_device.h>
#include <linux/uaccess.h>
#include <linux/printk.h>
#include <linux/slab.h>
#include <linux/spi/spidev.h>
#include "driver/spi_master.h"

#define DRIVER_NAME "spi"
#define DRIVER_VERSION "0.01"


static int PIN_NUM_MISO = -1;
static int PIN_NUM_MOSI = -1;
static int PIN_NUM_CLK  = -1;
static int EEPROM_HOST  = -1;
static int trans_list_longer  = 10; //任务队列长度
static int spi_buffer_size = 1024;
static int spi_default_speed = 1000000;




static int spi_bus_init(void){
    spi_bus_config_t buscfg={
        .miso_io_num=PIN_NUM_MISO,
        .mosi_io_num=PIN_NUM_MOSI,
        .sclk_io_num=PIN_NUM_CLK,
        .quadwp_io_num=-1,
        .quadhd_io_num=-1,
        .max_transfer_sz=spi_buffer_size,              //非DMA:64byte，，DMA:4096Byte
    };
    int ret = spi_bus_initialize(EEPROM_HOST, &buscfg, SPI_DMA_CH_AUTO); //初始化检查SPI主机模式是否成功
    if(ret != EXIT_SUCCESS){
        return -1;
    }
    printk(KERN_INFO "spi bus init success\n");
    return 0;
}

struct device_node *np = NULL;
static int get_spi_config_from_dt(void)
{
    char *path_of_node = "/spi_dev/spi@0";
    np = of_find_node_by_path(path_of_node);
    if (np == NULL) {printk(KERN_ERR "Spi driver: Failed to find node %s\n", path_of_node);return -1;}
    printk(KERN_INFO "Spi driver: Found node %s\n", path_of_node);
    

    int *data = of_get_property(np, "enable", NULL);
    if(data == NULL) {printk(KERN_ERR "Spi driver: Failed to get enable property\n");return -1;}
    if(*data != 1) {printk(KERN_ERR "Spi driver: SPI is not enabled\n");return -1;}
    printk(KERN_INFO "Spi driver: SPI is enabled\n");
    free(data);

    data = of_get_property(np, "miso_pin", NULL);
    if(data == NULL) {printk(KERN_ERR "Spi driver: Failed to get miso-gpio property\n");return -1;}
    PIN_NUM_MISO = *data;
    printk(KERN_INFO "Spi driver: miso-gpio is %d\n", PIN_NUM_MISO);
    free(data);

    data = of_get_property(np, "mosi_pin", NULL);
    if(data == NULL) {printk(KERN_ERR "Spi driver: Failed to get mosi-gpio property\n");return -1;}
    PIN_NUM_MOSI = *data;
    printk(KERN_INFO "Spi driver: mosi-gpio is %d\n", PIN_NUM_MOSI);
    free(data);

    data = of_get_property(np, "sclk_pin", NULL);
    if(data == NULL) {printk(KERN_ERR "Spi driver: Failed to get sclk-gpio property\n");return -1;}
    PIN_NUM_CLK = *data;
    printk(KERN_INFO "Spi driver: sclk-gpio is %d\n", PIN_NUM_CLK);
    free(data);

    data = of_get_property(np, "spi_host", NULL);
    if(data == NULL) {printk(KERN_ERR "Spi driver: Failed to get host property\n");return -1;}
    EEPROM_HOST = *data;
    printk(KERN_INFO "Spi driver: spi_host is %d\n", EEPROM_HOST);
    free(data);

    data = of_get_property(np, "trans_list_longer", NULL);
    if(data == NULL) {printk(KERN_ERR "Spi driver: Failed to get trans_list_longer property\n");return -1;}
    trans_list_longer = *data;
    printk(KERN_INFO "Spi driver: trans_list_longer is %d\n", trans_list_longer);
    free(data);

    data = of_get_property(np, "spi_buffer_size", NULL);
    if(data == NULL) {printk(KERN_ERR "Spi driver: Failed to get spi_buffer_size property\n");return -1;}
    spi_buffer_size = *data;
    printk(KERN_INFO "Spi driver: spi_buffer_size is %d\n", spi_buffer_size);
    free(data);

    data = of_get_property(np, "default_speed", NULL);
    if(data == NULL) {printk(KERN_ERR "Spi driver: Failed to get spi_default_speed property\n");return -1;}
    spi_default_speed = *data;
    printk(KERN_INFO "Spi driver: spi_default_speed is %d\n", spi_default_speed);
    free(data);

    of_node_put(np);
    printk(KERN_INFO "Spi driver: SPI get data frome dt success\n");
    return 0;
}


static int get_gpio(void)
{
    if(PIN_NUM_MISO != -1){
        if(gpio_request(PIN_NUM_MISO, "SPI_miso_gpio",0) != 0){
            printk(KERN_ERR "Spi driver: Failed to request miso gpio\n");
            return -1;
        }        
    }
    printk(KERN_INFO "Spi driver: spi get miso pin success\n"); 
    if(PIN_NUM_MOSI != -1){
        if(gpio_request(PIN_NUM_MOSI, "SPI_mosi_gpio",0) != 0){
            printk(KERN_ERR "Spi driver: Failed to request mosi gpio\n");
            gpio_free(PIN_NUM_MISO);
            return -1;
        }
    }
    printk(KERN_INFO "Spi driver: spi get mosi pin success\n"); 
    if(PIN_NUM_CLK  != -1){
        if(gpio_request(PIN_NUM_CLK, "SPI_sck_gpio",0) != 0){
            printk(KERN_ERR "Spi driver: Failed to request sck gpio\n");
            gpio_free(PIN_NUM_MOSI);
            gpio_free(PIN_NUM_MISO);
            return -1;
        }
    }
    printk(KERN_INFO "Spi driver: spi get sck pin success\n"); 
    return 0;
}


static spi_device_handle_t spi;
static int spi_driver_Init(){
     esp_err_t ret;
     spi_device_interface_config_t interface_config={
        .clock_speed_hz = spi_default_speed,
		.queue_size = 10,
        .pre_cb = NULL,
        .post_cb = NULL,
     };
    ret=spi_bus_add_device(EEPROM_HOST, &interface_config, &spi);
    if(ret != EXIT_SUCCESS){
        printk(KERN_ERR "Spi driver: Failed to add device to spi bus\n");
        return -1;
    }
    return 0;
}


static spi_transaction_t *user_spi_transaction;   //异步发送事务环形队列
static int spi_device_init(void)
{
    if(get_spi_config_from_dt() != 0){   //从dt中获取SPI配置
        return -1;
    }
    if(get_gpio() != 0){                 //获取GPIO
        return -1;
    }
    if(spi_bus_init() != 0){              //初始化SPI主机
        return -1;
    }
    if(spi_driver_Init() != 0){           //初始化SPI设备
        return -1;
    }
    user_spi_transaction = (spi_transaction_t*)vmalloc(trans_list_longer * sizeof(spi_transaction_t));
    if(user_spi_transaction == NULL){
        printk(KERN_ERR "Spi driver: Failed to allocate memory for spi transaction\n");
        return -1;
    }
    return 0;
}


static struct spi_ioc_transfer spi_dev;
static uint8_t user_spi_transaction_cnt = 0;

static void spi_transment(void){
    memset(&user_spi_transaction[user_spi_transaction_cnt], 0, sizeof(spi_transaction_t));  
    user_spi_transaction[user_spi_transaction_cnt].length = spi_dev.len *sizeof(long);
    user_spi_transaction[user_spi_transaction_cnt].flags = 0;
    if(spi_dev.len * sizeof(long) / 8 < 4){
        for(int i=0;i<spi_dev.len *sizeof(long) / 8;i++){
            if(spi_dev.tx_buf != NULL){
                user_spi_transaction[user_spi_transaction_cnt].tx_data[i] = *(uint8_t*)(spi_dev.tx_buf + i);
                user_spi_transaction[user_spi_transaction_cnt].flags = user_spi_transaction[user_spi_transaction_cnt].flags | SPI_TRANS_USE_TXDATA;
            }
            if(spi_dev.rx_buf != NULL){
                user_spi_transaction[user_spi_transaction_cnt].rx_data[i] = *(uint8_t*)(spi_dev.rx_buf + i);
                user_spi_transaction[user_spi_transaction_cnt].flags = user_spi_transaction[user_spi_transaction_cnt].flags | SPI_TRANS_USE_RXDATA;
            }
        }
    }
    else{
        if(spi_dev.tx_buf != NULL){
             user_spi_transaction[user_spi_transaction_cnt].tx_buffer = spi_dev.tx_buf;
        };
        if(spi_dev.rx_buf != NULL){
             user_spi_transaction[user_spi_transaction_cnt].rx_buffer = spi_dev.rx_buf;
        }
    }
    int ret = spi_device_queue_trans(spi, &user_spi_transaction[user_spi_transaction_cnt], spi_dev.delay_usecs);
    assert(ret == EXIT_SUCCESS);
    user_spi_transaction_cnt++;
    if (user_spi_transaction_cnt == trans_list_longer){
        user_spi_transaction_cnt = 0;
    }
}

static int spi_major;
static int device_use = 1;
static int spi_dev_open(void* ctx, const char * path, int flags, int mode){
    if(device_use == 1){
        device_use = 0;
        return 0;
    }
    else{
        return -EBUSY;
    }
}
static int spi_dev_ioctl(void* ctx, int fd, int cmd, va_list args){
    if(cmd > 1){
        spi_dev = va_arg(args,struct spi_ioc_transfer);
    }
    spi_transment();
    return 0;
}
static int spi_dev_release(void* ctx, int fd){
    device_use = 1;
    return 0;
}
static size_t spi_dev_read(void* ctx, int fd, char *buf, size_t count){
    return 0;
}
static size_t spi_dev_write(void* ctx, int fd, const char *buf, size_t count){
    return 0;
}
static file_operations_t spi_fops = {
    .open_p = spi_dev_open,
    .ioctl_p = spi_dev_ioctl,
    .close_p = spi_dev_release,
    .read_p = spi_dev_read,
    .write_p = spi_dev_write,
};


int __init spi_init(void)
{
    printk(KERN_INFO "Spi driver: spi driver version %s\n", DRIVER_VERSION);
    if(spi_device_init() != 0){
        return -1;
    }
    spi_major = register_chrdev(230, "spi-1", &spi_fops);
    if(spi_major < 0){
        printk(KERN_ERR "Spi driver: Failed to register char device\n");
        return -1;
    }
    printk(KERN_INFO "Spi driver: spi driver major number %d\n", spi_major);
    return 0;
}

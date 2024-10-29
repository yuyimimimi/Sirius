#include <stdio.h>
#include <linux/of.h>
#include <linux/of_device.h>
#include <linux/printk.h>
#include <linux/err.h>

static uint8_t *Back_Pin;
static uint8_t *CS_pin;
static uint8_t *DC_pin;

static uint8_t  *spi_host;
static uint32_t *spi_speed_hz;
static uint32_t *spi_buffers_max_size;

/**
 * 
 * @brief  获取st7789的配置信息
 * @return 成功返回0，失败返回-1
 * 
 * 
*/

int ST7789_Getconfig(void)  
{
    char *device_node_path = "/st7789@0";
    char *spi_node_path = NULL;
    struct device_node *device_node = NULL;
    /**
     * 准备获取st7789的配置信息
    */
    //获取ST7789设备节点
    device_node = of_find_node_by_path(device_node_path);           
    if (device_node == NULL) {
        printf("ST7789:Failed to find device node %s\n", device_node_path);
        return -1;
    }
    //检测是否启用结点
    char *enable_node_path = of_get_property(device_node, "status", NULL);
    if (enable_node_path == NULL) {
        printf("Failed to get status property\n");
        return -1;
    }
    if (strcmp(enable_node_path, "okay") != 0) {
        printf("Device is disabled\n");
        return -1;
    }
    //获取spi节点路径
    spi_node_path = of_get_property(device_node, "compatible", NULL);
    if (spi_node_path == NULL) {
        printf("Failed to get compatible property\n");
        return -1;
    }
    printk( KERN_INFO "ST7789:use spi node %s\n", spi_node_path);
    //获取spi节点
    struct device_node *spi_node = of_find_node_by_path(spi_node_path);
    if (spi_node == NULL) {
        printf("Failed to find spi node %s\n", spi_node_path);
        return -1;
    }
    printk( KERN_INFO "ST7789:get spi node\n");
    /**
     * 获取st7789的引脚配置信息
    */
    //获取Back_Pin
    Back_Pin = of_get_property(device_node, "bl_gpios", NULL);
    if (Back_Pin == NULL) {
        printf("Failed to get back-pin property\n");
        return -1;
    }
    printk( KERN_INFO "ST7789:get back-pin : %d\n", *Back_Pin);
    //获取CS_pin
    CS_pin = of_get_property(device_node, "cs_gpios", NULL);
    if (CS_pin == NULL) {
        printf("Failed to get cs-pin property\n");
        return -1;
    }
    printk( KERN_INFO "ST7789:get cs-pin : %d\n", *CS_pin);
    //获取DC_pin
    DC_pin = of_get_property(device_node, "dc_gpios", NULL);
    if (DC_pin == NULL) {
        printf("Failed to get dc-pin property\n");
        return -1;
    }
    printk( KERN_INFO "ST7789:get dc-pin: %d\n", *DC_pin);
    /**
     * 获取使用的spi通道的配置信息
    */
    //获取spi_speed_hz
    spi_speed_hz = of_get_property(device_node, "spi_max_frequency", NULL);
    if (spi_speed_hz == NULL) {
        printf("Failed to get spi-max-frequency property\n");
        return -1;
    }
    printk( KERN_INFO "ST7789:ST7789 spi_speed_frequency_hz : %ld\n", *spi_speed_hz);
    //获取spi_host
    spi_host = of_get_property(spi_node, "spi_host", NULL);
    if (spi_host == NULL) {
        printf("Failed to get spi-host property\n");
        return -1;
    }
    printk( KERN_INFO "ST7789:get spi-host : %d\n", *spi_host);
    //获取spi_buffers_max_size
    spi_buffers_max_size = of_get_property(spi_node, "spi_buffer_size", NULL);
    if (spi_buffers_max_size == NULL) {
        printf("Failed to get spi-buffers-max-size property\n");
        return -1;
    }
    printk( KERN_INFO "ST7789:get spi-buffers-max-size : %ld\n", *spi_buffers_max_size);
    return 0;
}


int ST7789_get_spi_host(void){
    return *spi_host;
}
int ST7789_get_spi_speed_hz(void){
    return *spi_speed_hz;
}
int ST7789_get_spi_buffers_max_size(void){
    return *spi_buffers_max_size;
}
uint8_t ST7789_get_Back_Pin(void){
    return *Back_Pin;
}
uint8_t ST7789_get_CS_pin(void){
    return *CS_pin;
}
uint8_t ST7789_get_DC_pin(void){
    return *DC_pin;
}



#include <stdint.h>
#include <stdio.h>

int ST7789_Getconfig(void);
int ST7789_get_spi_host(void);
int ST7789_get_spi_speed_hz(void);
uint8_t ST7789_get_Back_Pin(void);
uint8_t ST7789_get_CS_pin(void);
uint8_t ST7789_get_DC_pin(void);

#include <linux/errno.h>
#include <linux/gpio.h>
#include <linux/printk.h>
#include <linux/delay.h>
#include "driver/ledc.h"
#include "driver/spi_master.h"


static int ST7789_Backlight_Init(void)
{
    if(gpio_request(ST7789_get_Back_Pin(), "ST7789_Backlight",0) != 0)
    {
        printk( KERN_INFO "ST7789_Backlight gpio busy,please check device tree");
        return -1;
    }

    ledc_timer_config_t ledc_timer = {
    .duty_resolution = LEDC_TIMER_13_BIT,
    .freq_hz = 5000,                     
    .speed_mode = LEDC_LOW_SPEED_MODE,          
    .timer_num = LEDC_TIMER_1,           
    .clk_cfg = LEDC_AUTO_CLK         
    };
    ledc_timer_config(&ledc_timer);
    ledc_channel_config_t ledc_timer_channel= {
        .gpio_num   = ST7789_get_Back_Pin(),
        .speed_mode = LEDC_LOW_SPEED_MODE,
        .channel    = LEDC_CHANNEL_0,
        .timer_sel  = LEDC_TIMER_1,
        .duty       = 8191,
        .hpoint     = 0
    };
    ledc_channel_config( &ledc_timer_channel );
    return 0;
}


static int ST7789_CSDC_Init(void)
{
    if(gpio_request(ST7789_get_CS_pin(), "ST7789_CS",0) != 0)
    {
        printk( KERN_INFO "ST7789_CS gpio busy,please check device tree");
        return -1;
    }
    if(gpio_request(ST7789_get_DC_pin(), "ST7789_DC",0) != 0)
    {
        printk( KERN_INFO "ST7789_DC gpio busy,please check device tree");
        return -1;
    }
    gpio_direction_output(ST7789_get_DC_pin(), 1);
    return 0;
}



#define ST7789_SPI_TRANSACTION_NUM 10
static spi_transaction_t user_spi_transaction[ST7789_SPI_TRANSACTION_NUM];
static uint8_t user_spi_transaction_cnt = 0; //循环队列头指针
static uint8_t user_spi_transaction_done = 0;//循环队列尾指针

static spi_device_handle_t ST779_spi;
static void ST7789_SetDC(spi_transaction_t *t){
    uint8_t *cmd = (uint8_t *)t->user;
    if(cmd != NULL)
     gpio_set_value(ST7789_get_DC_pin(), 1);
}

static void ST7789_ResetDC(spi_transaction_t *t){
    uint8_t *cmd = (uint8_t *)t->user;
    if(cmd != NULL)
    gpio_set_value(ST7789_get_DC_pin(), 0);

    user_spi_transaction_done++;
    if(user_spi_transaction_done == ST7789_SPI_TRANSACTION_NUM){
        user_spi_transaction_done = 0;
    }
}

static int ST7789_spi_Init(void)
{
    esp_err_t ret;
    spi_device_interface_config_t interface_config={        
        .clock_speed_hz =ST7789_get_spi_speed_hz(),         
        .mode = 0,                                          
        .spics_io_num = ST7789_get_CS_pin(),	            
		.queue_size = 10,                                   
		.cs_ena_pretrans = 1,                               
        .pre_cb =  ST7789_ResetDC,                          
        .post_cb = ST7789_SetDC,               
     };                                                     
    ret = spi_bus_add_device(ST7789_get_spi_host(), &interface_config, &ST779_spi);
    if(ret != EXIT_SUCCESS){
        return -1;
    }
    return 0;
}




int ST7789_device_init(void)
{
    if(ST7789_Getconfig() != 0){
        printk( KERN_INFO "ST7789_Getconfig failed");
        return -1;
    }
    printk( KERN_INFO "ST7789_Getconfig success");
    if(ST7789_Backlight_Init() != 0){
        printk(KERN_INFO "ST7789_Backlight_Init failed");
        return -1;
    }
    printk( KERN_INFO "ST7789_Backlight_Init success");
    if(ST7789_CSDC_Init() != 0){
        printk(KERN_INFO "ST7789_CSDC_Init failed");
        return -1;
    }
    printk( KERN_INFO "ST7789_CSDC_Init success");

    if(ST7789_spi_Init() != 0){
        printk(KERN_INFO "ST7789_spi_Init failed");
        return -1;
    }
    printk( KERN_INFO "ST7789_spi_Init success");
    return 0;
}



void ST7789_SetBackLight(uint16_t bl_britness)
{
     ledc_set_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0, (bl_britness));
     ledc_update_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0);
}




void ST7789_SendCmd(void* cmd_data,int cmd_length)
{
    while (user_spi_transaction_cnt+1%ST7789_SPI_TRANSACTION_NUM == user_spi_transaction_done)//如果队列满了，等待空出一个位置
    {
        udelay(10);
    }


    uint8_t *cmd = (uint8_t*)cmd_data;
    memset(&user_spi_transaction[user_spi_transaction_cnt], 0, sizeof(spi_transaction_t)); // Zero out the transaction
    user_spi_transaction[user_spi_transaction_cnt].length = 8 * cmd_length;                             // Command is 8 bits
    user_spi_transaction[user_spi_transaction_cnt].user = cmd;
    if(cmd_length < 4)
    {
        user_spi_transaction[user_spi_transaction_cnt].flags = SPI_TRANS_USE_TXDATA;           // Command is 8 bits
        for(int i =0 ; i< cmd_length ;i++){
        user_spi_transaction[user_spi_transaction_cnt].tx_data[i] = cmd[i];                    // Command is 8 bits
        }
    }
    else{
        user_spi_transaction[user_spi_transaction_cnt].tx_buffer = cmd;
    }
    spi_device_queue_trans(ST779_spi , &user_spi_transaction[user_spi_transaction_cnt], portMAX_DELAY);
    user_spi_transaction_cnt++;
    if (user_spi_transaction_cnt == ST7789_SPI_TRANSACTION_NUM){
        user_spi_transaction_cnt = 0;
    }
}

void ST7789_SendData(void* data_d,int cmd_length)
{
    while (user_spi_transaction_cnt+1%ST7789_SPI_TRANSACTION_NUM == user_spi_transaction_done)//如果队列满了，等待空出一个位置
    {
        udelay(10);
    }

    uint8_t *data = (uint8_t*)data_d;
    memset(&user_spi_transaction[user_spi_transaction_cnt], 0, sizeof(spi_transaction_t)); // Zero out the transaction
    user_spi_transaction[user_spi_transaction_cnt].length = 8 * cmd_length;                // Command is 8 bits
    if(cmd_length < 4){
        user_spi_transaction[user_spi_transaction_cnt].flags = SPI_TRANS_USE_TXDATA;       // Command is 8 bits
        for(int i =0 ; i< cmd_length ;i++){
        user_spi_transaction[user_spi_transaction_cnt].tx_data[i] = data[i];               // Command is 8 bits
        }
    }
    else{
        user_spi_transaction[user_spi_transaction_cnt].tx_buffer = data;
    }
    
    int ret = spi_device_queue_trans(ST779_spi , &user_spi_transaction[user_spi_transaction_cnt], portMAX_DELAY);

    user_spi_transaction_cnt++;
    if (user_spi_transaction_cnt == ST7789_SPI_TRANSACTION_NUM){
        user_spi_transaction_cnt = 0;
    }
}

int ST7789_get_spi_transaction_done(void)
{
    if(user_spi_transaction_cnt == user_spi_transaction_done)//如果队列满了，等待空出一个位置
    return 0;
    else
    return 1;
}

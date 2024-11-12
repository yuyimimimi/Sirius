#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <linux/printk.h>
#include  <unistd.h>
#include <display_farmerwork.h>
#include <linux/delay.h>

int  ST7789_device_init(void);

void ST7789_SetBackLight(uint16_t bl_britness);
void ST7789_SendCmd(void* cmd_data,int cmd_length);
void ST7789_SendData(void* data_d,int cmd_length);
int ST7789_get_spi_buffers_max_size(void);
int ST7789_get_spi_transaction_done(void); //获取队列中spi事务是否完成

typedef struct {
    uint8_t cmd;
    uint8_t data[16];
    uint8_t data_bytes; // Length of data in above data array; 0xFF = end of cmds.
} lcd_init_cmd_t;



static const lcd_init_cmd_t vendor_specific_init[] = {
    {0x36, {0x00}, 1},                       //设置旋转模式
    {0x3A, {0x55}, 1},                       //黑白  0x55 
    {0xB2, {0x0C, 0x0C, 0x00, 0x33, 0x33}, 5}, //???
    {0xB7, {0x75}, 1},                //???
    {0xBB, {0x2F}, 1},                //???
	{0xC0, {0x2C}, 1},                //???
    {0xC3, {0X16}, 1},                //???
    {0xC4, {0x20}, 1},                //???
	{0x2A, {0x00,0x00,0x00,0xEf},4},  //列地址设置
	{0x2B, {0x00,0x00,0x01,0x3f},4},  //行地址设置
    {0xC6, {0x13}, 1},                //設置為60hz
    {0xD0, {0xA4, 0xA1}, 2},          //???
	{0xD6, {0xA1}, 1},                //???
    {0xE0, {0xF0, 0x04, 0x07, 0x09, 0x07, 0x13, 0x25, 0x33, 0x3C, 0x34, 0x10, 0x10, 0x29,0X32}, 14}, //伽马校正
    {0xE1, {0xF0, 0x05, 0x08, 0x0A, 0x09, 0x05, 0x25, 0x32, 0x3B, 0x3B, 0x17, 0x18, 0x2E, 0x37}, 14},//伽马校正
    {0x21, {}, 0},                      //此命令用于从显示反转模式恢复。
	{0x29, {}, 0},                      //开启显示
	{0x55, {0x93}, 1},
	{0xFF, {}, 0},//停止位
};


void ST7789V_SPISendData2Bytes(uint16_t Color)
{
    uint8_t highByte = (Color >> 8) & 0xFF;  // 提取高字节
    uint8_t lowByte = Color & 0xFF;          // 提取低字节
    uint8_t data[2] = {highByte , lowByte};
    ST7789_SendData(&data, 2);
}

void ST7789V_SetLcdAddress(uint16_t Start_X,uint16_t Start_Y,uint16_t End_X,uint16_t End_Y)
{
    uint8_t data = 0x2A; 
    ST7789_SendCmd(&data,1);//列地址设置
    ST7789V_SPISendData2Bytes(Start_X);
    ST7789V_SPISendData2Bytes(End_X);
    data = 0x2B;
    ST7789_SendCmd(&data,1);//行地址设置
    ST7789V_SPISendData2Bytes(Start_Y);
    ST7789V_SPISendData2Bytes(End_Y);
    data = 0x2C;
    ST7789_SendCmd(&data,1);//储存器写
}


void ST7789V_LcdDrawPoint(uint16_t X,uint16_t Y,uint16_t Color)
{
    ST7789V_SetLcdAddress(X,Y,X,Y);//设置光标位置 
    ST7789V_SPISendData2Bytes(Color);
} 


void Draw(int x1, int y1, int width, int height, void *color)
{

    uint16_t *color_16 = (uint16_t*)color;
    uint32_t size = width * height;

    int max_sendpx = ST7789_get_spi_buffers_max_size() / 2;                 //size = uint16_t
    int datasendtimes = size / max_sendpx;
    int lostbytes = size % max_sendpx;

    ST7789V_SetLcdAddress(x1,y1,x1 + width - 1,y1 + height - 1);
    
    if(datasendtimes > 0)
    {
        for(int i=0;i<datasendtimes;i++)
        {
            ST7789_SendData(&color_16[i * max_sendpx ], max_sendpx*2);      
        }
    }
    if(lostbytes > 0)
    {
        ST7789_SendData(&color_16[max_sendpx * datasendtimes], lostbytes*2);   
    }

    while (ST7789_get_spi_transaction_done())
    {
        usleep(100);
    }
}



void draw_block_test(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color)
{
    ST7789V_SetLcdAddress(x1,y1,x2,y2);   
    int length = (x2 - x1 + 1) * (y2 - y1 + 1);
    for(int i=0;i<length;i++){
        ST7789V_SPISendData2Bytes(color);
    }
}




#define RGB888(r,g,b) ((r<<16)|(g<<8)|b)


int LCDST7789c_Init()
{
    printf("ST7789 init start!");
    if(ST7789_device_init() != 0){
        printk( KERN_INFO "ST7789 device init fail!");
        return -1;
    }

    ST7789_SetBackLight(10);

    uint8_t data = 0x11;
    ST7789_SendCmd(&data,1);
    usleep(120*1000);

    int num=0;
    while (vendor_specific_init[num].cmd != 0xff) {	
        ST7789_SendCmd(&vendor_specific_init[num].cmd,1);
        if(vendor_specific_init[num].data_bytes > 0)
        {
            ST7789_SendData(&vendor_specific_init[num].data[0],vendor_specific_init[num].data_bytes);   
        }
        num++;
    }
    printf("ST7789 init success!");    

    uint16_t *color = (uint16_t*)malloc(240*sizeof(uint16_t));
    for(int j=0;j<240;j++){
        color[j] = 0x0000;
    }
    for(int i=0;i<320;i++)
    {
        Draw(0,i,240,1,color);  
    }
    free(color);

    return 0;
}


display_device_t sisplayer = {
    .name = "ST7789",
    .init = LCDST7789c_Init,
    .display = Draw,
    .node = "/panel/st7789",
};


int __init st7789_driver_init(void)
{
    display_object_add(&sisplayer);
    return 0;
}
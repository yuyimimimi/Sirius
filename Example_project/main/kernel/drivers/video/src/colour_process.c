#include "display_private_def.h"
#include <stdlib.h>
#include <string.h>
#include <linux/printk.h>

static size_t rgb888_to_rgb565(uint32_t *rgb888,uint32_t size,void *dest_buffer);

size_t color_to_color(uint32_t *color ,uint32_t length ,int pixel_format,void *dest_buffer,int dest_pixel_format)
{
  if( dest_pixel_format == 888 && pixel_format == 565)
  {
      return rgb888_to_rgb565(color,length,dest_buffer);
  }
  return NULL;
}


static size_t rgb888_to_rgb565(uint32_t *rgb888,uint32_t size,void *dest_buffer)//此函数通过减少跳转语句以提高性能，请不要尝试“优化”
{
     uint16_t *rgb565_buffer =(uint16_t*)dest_buffer;
    int block_size = 0;
    if(size >= 16)
    {
      int times = size/16;
      int base = 0;
      for(int i = 0; i < times; i++)
      {
      base = i*16;
        for(int j = 0; j < 16; j++) //此处由编译器展开不涉及循环
        {
          rgb565_buffer[base] = (((rgb888[base] & 0xF80000) >> 16)/8)<<11  |   (((rgb888[base] & 0x00FC00) >> 8)/4)<<5  |  ((rgb888[base] & 0x0000F8)/8);  
          base++;           
        } 
      }
      block_size += times * 16;
      size = size%16;
    }
    if(size > 0)
    {
      for(int i = 0; i < size; i++)
      {
         rgb565_buffer[block_size+i] = (((rgb888[block_size+i] & 0xF80000) >> 16)/8)<<11  |   (((rgb888[block_size+i] & 0x00FC00) >> 8)/4)<<5  |  ((rgb888[block_size+i] & 0x0000F8)/8);  
      }
    }
  return block_size + size;
}


static size_t rgb565_to_rgb888(uint16_t *rgb565,uint32_t size,void *dest_buffer)
{
    uint32_t *rgb888_buffer =(uint32_t*)dest_buffer;
    int block_size = 16;
    int base = 0;
    for(int i = 0; i < size; i++)
    {
      base = block_size*i;
      for(int j = 0; j < block_size; j++)
      {
        rgb888_buffer[base] = ((rgb565[i] & 0xF800) << 8)  |   ((rgb565[base] & 0x07E0) << 5)  |  ((rgb565[base] & 0x001F) << 3);        
        base++;
      }
    }
    int less = size%block_size;
    for(int i = 0; i < less; i++)
    {
      
    }


    return size;
}
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


static size_t rgb888_to_rgb565(uint32_t *rgb888,uint32_t size,void *dest_buffer)
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
      rgb565_buffer[base] = ((rgb888[base] & 0xF80000) >> 8)  |   ((rgb888[base] & 0x00FC00) >> 5)  |  ((rgb888[base] & 0x0000F8) >> 3);  
      base++;       
      rgb565_buffer[base] = ((rgb888[base] & 0xF80000) >> 8)  |   ((rgb888[base] & 0x00FC00) >> 5)  |  ((rgb888[base] & 0x0000F8) >> 3);  
      base++;             
      rgb565_buffer[base] = ((rgb888[base] & 0xF80000) >> 8)  |   ((rgb888[base] & 0x00FC00) >> 5)  |  ((rgb888[base] & 0x0000F8) >> 3);  
      base++;       
      rgb565_buffer[base] = ((rgb888[base] & 0xF80000) >> 8)  |   ((rgb888[base] & 0x00FC00) >> 5)  |  ((rgb888[base] & 0x0000F8) >> 3);  
      base++;        
      rgb565_buffer[base] = ((rgb888[base] & 0xF80000) >> 8)  |   ((rgb888[base] & 0x00FC00) >> 5)  |  ((rgb888[base] & 0x0000F8) >> 3);  
      base++;       
      rgb565_buffer[base] = ((rgb888[base] & 0xF80000) >> 8)  |   ((rgb888[base] & 0x00FC00) >> 5)  |  ((rgb888[base] & 0x0000F8) >> 3);  
      base++;             
      rgb565_buffer[base] = ((rgb888[base] & 0xF80000) >> 8)  |   ((rgb888[base] & 0x00FC00) >> 5)  |  ((rgb888[base] & 0x0000F8) >> 3);  
      base++;       
      rgb565_buffer[base] = ((rgb888[base] & 0xF80000) >> 8)  |   ((rgb888[base] & 0x00FC00) >> 5)  |  ((rgb888[base] & 0x0000F8) >> 3);  
      base++;    
      rgb565_buffer[base] = ((rgb888[base] & 0xF80000) >> 8)  |   ((rgb888[base] & 0x00FC00) >> 5)  |  ((rgb888[base] & 0x0000F8) >> 3);  
      base++;       
      rgb565_buffer[base] = ((rgb888[base] & 0xF80000) >> 8)  |   ((rgb888[base] & 0x00FC00) >> 5)  |  ((rgb888[base] & 0x0000F8) >> 3);  
      base++;             
      rgb565_buffer[base] = ((rgb888[base] & 0xF80000) >> 8)  |   ((rgb888[base] & 0x00FC00) >> 5)  |  ((rgb888[base] & 0x0000F8) >> 3);  
      base++;       
      rgb565_buffer[base] = ((rgb888[base] & 0xF80000) >> 8)  |   ((rgb888[base] & 0x00FC00) >> 5)  |  ((rgb888[base] & 0x0000F8) >> 3);  
      base++;    
      rgb565_buffer[base] = ((rgb888[base] & 0xF80000) >> 8)  |   ((rgb888[base] & 0x00FC00) >> 5)  |  ((rgb888[base] & 0x0000F8) >> 3);  
      base++;       
      rgb565_buffer[base] = ((rgb888[base] & 0xF80000) >> 8)  |   ((rgb888[base] & 0x00FC00) >> 5)  |  ((rgb888[base] & 0x0000F8) >> 3);  
      base++;             
      rgb565_buffer[base] = ((rgb888[base] & 0xF80000) >> 8)  |   ((rgb888[base] & 0x00FC00) >> 5)  |  ((rgb888[base] & 0x0000F8) >> 3);  
      base++;       
      rgb565_buffer[base] = ((rgb888[base] & 0xF80000) >> 8)  |   ((rgb888[base] & 0x00FC00) >> 5)  |  ((rgb888[base] & 0x0000F8) >> 3);  
      base++;                 
      }
      block_size += times * 16;
      size = size%16;
    }
    if(size > 0)
    {
      for(int i = 0; i < size; i++)
      {
         rgb565_buffer[block_size+i] = ((rgb888[block_size+i] & 0xF80000) >> 8)  |   ((rgb888[block_size+i] & 0x00FC00) >> 5)  |  ((rgb888[block_size+i] & 0x0000F8) >> 3);  
      }
    }
  return block_size + size;
}


static size_t rgb565_to_rgb888(uint16_t *rgb565,uint32_t size,void *dest_buffer)
{
    uint32_t *rgb888_buffer =(uint32_t*)dest_buffer;
    for(int i = 0; i < size; i++)
    {
      rgb888_buffer[i] = ((rgb565[i] & 0xF800) << 8)  |   ((rgb565[i] & 0x07E0) << 5)  |  ((rgb565[i] & 0x001F) << 3);  
    }
    return size;
}
#include "display_private_def.h"
#include <string.h>


static void RGB565_TO_RGB888(void *src, void *dst, uint32_t len);
static void RGB888_TO_RGB565(void *src, void *dst, uint32_t len);
static void Grayscale_TO_RGB888(void *src, void *dst, uint32_t len);
static void RGB888_TO_Grayscale(void *src, void *dst, uint32_t len);
static void RGB565_TO_Grayscale(void *src, void *dst, uint32_t len);
static void Grayscale_TO_RGB565(void *src, void *dst, uint32_t len);
static void darkandlight_TO_RGB888(void *src, void *dst, uint32_t len);
static void darkandlight_TO_RGB565(void *src, void *dst, uint32_t len);
static void darkandlight_TO_Grayscale(void *src, void *dst, uint32_t len);


int color_to_color(void *src, void *dst, uint32_t len, color_mode_t src_color, color_mode_t dst_color)
{
   if(src_color == dst_color) 
   {
       memcpy(dst, src, len);
       return 0;
   }
   switch(src_color)
   {
      case RGB_888: 
         switch (dst_color)
         {
            case RGB_565: 
               RGB888_TO_RGB565(src, dst, len);
               break;
            case GRAYSCALE:
               RGB888_TO_Grayscale(src, dst, len);
               break;
            case darkandlight:
               RGB888_TO_Grayscale(src, dst, len);
            default:
               break;
         }
         break;
      case RGB_565:
         switch(dst_color)
         {
            case RGB_888:
               RGB565_TO_RGB888(src, dst, len);
               break;
            case GRAYSCALE:
               RGB565_TO_Grayscale(src, dst, len);
               break;
            case darkandlight:
               RGB565_TO_Grayscale(src, dst, len);
               break;
            default:
               break;
         }
         break;
      case GRAYSCALE:
         switch (dst_color)
         {
            case RGB_888:
               Grayscale_TO_RGB888(src, dst, len);
               break;
            case RGB_565:
               Grayscale_TO_RGB565(src, dst, len);
               break;
            default:
               break;
         }
         break;
      case darkandlight:
         switch (dst_color)
         {
            case RGB_888:
               darkandlight_TO_RGB888(src, dst, len);
               break;
            case RGB_565:
               darkandlight_TO_RGB565(src, dst, len);
               break;
            case GRAYSCALE:
               darkandlight_TO_Grayscale(src, dst, len);
               break;
            default:
               break;
         }
         break;
      default:
         break;
   }
   return 0;
}




static void RGB565_TO_RGB888(void *src, void *dst, uint32_t len)
{
   uint16_t *src_ptr = (uint16_t *)src;
   uint32_t *dst_ptr = (uint32_t *)dst;
   uint16_t pixel_R;
   uint16_t pixel_G;
   uint16_t pixel_B;
   for(uint32_t i = 0; i < len; i++)
   {
       pixel_R = ((src_ptr[i] & 0xF800)>>11)*8;
       pixel_G = ((src_ptr[i] & 0x07E0)>>5)*7;
       pixel_B = (src_ptr[i] & 0x001F)*8;
       dst_ptr [i] = (pixel_R << 16) | (pixel_G << 8) | pixel_B;
   }
}

static void RGB888_TO_RGB565(void *src, void *dst, uint32_t len)
{
   uint16_t *src_ptr = (uint16_t *)src;
   uint32_t *dst_ptr = (uint32_t *)dst;
   uint16_t pixel_R;
   uint16_t pixel_G;
   uint16_t pixel_B;
   for(uint32_t i = 0; i < len; i++)
   {
       pixel_R = ((src_ptr[i] & 0xFF0000) >> 16)/8;
       pixel_G = ((src_ptr[i] & 0x00FF00) >> 8)/7;
       pixel_B = (src_ptr[i] & 0x0000FF)/8;
       dst_ptr[i] = (pixel_R << 11) | (pixel_G << 5) | pixel_B;
   }
}

static void Grayscale_TO_RGB888(void *src, void *dst, uint32_t len)
{
   uint8_t *src_ptr = (uint8_t *)src;
   uint32_t *dst_ptr = (uint32_t *)dst;
    for(uint32_t i = 0; i < len; i++)
    {
       dst_ptr[i] = (src_ptr[i] << 16) | (src_ptr[i] << 8) | src_ptr[i];
    }
}

static void RGB888_TO_Grayscale(void *src, void *dst, uint32_t len)
{
   uint32_t *src_ptr = (uint32_t *)src;
   uint8_t *dst_ptr = (uint8_t *)dst;
   for(uint32_t i = 0; i < len; i++)
   {
       dst_ptr = (((src_ptr[i] & 0xFF0000) >> 16) + ((src_ptr[i] & 0x00FF00) >> 8) + (src_ptr[i] & 0x0000FF))/3;
   }
}
static void RGB565_TO_Grayscale(void *src, void *dst, uint32_t len)
{
   uint16_t *src_ptr = (uint16_t *)src;
   uint8_t *dst_ptr = (uint8_t *)dst;
   for(uint32_t i = 0; i < len; i++)
   {
       dst_ptr[i] = (((src_ptr[i] & 0xF800)>>11)*8 + ((src_ptr[i] & 0x07E0)>>5)*7 + (src_ptr[i] & 0x001F)*8 )/3;
   }
}
static void Grayscale_TO_RGB565(void *src, void *dst, uint32_t len)
{
   uint8_t *src_ptr = (uint8_t *)src;
   uint16_t *dst_ptr = (uint16_t *)dst;
   for(uint32_t i = 0; i < len; i++)
   {
       dst_ptr[i] = (src_ptr[i] << 11) | (src_ptr[i] << 5) | src_ptr[i];
   }
}

static void RGB888_TO_darkandlight(void *src, void *dst, uint32_t len)
{
   uint32_t *src_ptr = (uint32_t *)src;
   uint8_t *dst_ptr = (uint8_t *)dst;
   for(uint32_t i = 0; i < len; i++)
   {
       if(((src_ptr[i] & 0xFF0000) >> 16) + ((src_ptr[i] & 0x00FF00) >> 8) + (src_ptr[i] & 0x0000FF) > 383)
       {
           dst_ptr[i] = 0xFF;
       }
       else
       {
           dst_ptr[i] = 0x00;
       }
   }
}


static void RGB565_TO_darkandlight(void *src, void *dst, uint32_t len)
{
   uint16_t *src_ptr = (uint16_t *)src;
   uint8_t *dst_ptr = (uint8_t *)dst;
   for(uint32_t i = 0; i < len; i++)
   {
       if(((src_ptr[i] & 0xF800)>>11)*8 + ((src_ptr[i] & 0x07E0)>>5)*7 + (src_ptr[i] & 0x001F)*8 > 191)
       {
           dst_ptr[i] = 0xFF;
       }
       else
       {
           dst_ptr[i] = 0x00;
       }
   }
}

static void Grayscale_TO_darkandlight(void *src, void *dst, uint32_t len)
{
   uint8_t *src_ptr = (uint8_t *)src;
   uint32_t *dst_ptr = (uint32_t *)dst;
   for(uint32_t i = 0; i < len; i++)
   {
       if(src_ptr[i] > 127)
       {
           dst_ptr[i] = 0x00FFFFFF;
       }
       else
       {
           dst_ptr[i] = 0x00000000;
       }
   }
}
static void darkandlight_TO_RGB888(void *src, void *dst, uint32_t len)
{
   uint8_t *src_ptr = (uint8_t *)src;
   uint32_t *dst_ptr = (uint32_t *)dst;
   for(uint32_t i = 0; i < len; i++)
   {
       if(src_ptr[i] == 0xFF)
       {
           dst_ptr[i] = 0x00FFFFFF;
       }
       else
       {
           dst_ptr[i] = 0x00000000;
       }
   }
}

static void darkandlight_TO_RGB565(void *src, void *dst, uint32_t len)
{
   uint8_t *src_ptr = (uint8_t *)src;
   uint16_t *dst_ptr = (uint16_t *)dst;
   for(uint32_t i = 0; i < len; i++)
   {
       if(src_ptr[i] == 0xFF)
       {
           dst_ptr[i] = 0xFFFF;
       }
       else
       {
           dst_ptr[i] = 0x0000;
       }
   }
}

static void darkandlight_TO_Grayscale(void *src, void *dst, uint32_t len)
{
   uint8_t *src_ptr = (uint8_t *)src;
   uint8_t *dst_ptr = (uint8_t *)dst;
   for(uint32_t i = 0; i < len; i++)
   {
       if(src_ptr[i] == 0xFF)
       {
           dst_ptr[i] = 0xFF;
       }
       else
       {
           dst_ptr[i] = 0x00;
       }
   }
}
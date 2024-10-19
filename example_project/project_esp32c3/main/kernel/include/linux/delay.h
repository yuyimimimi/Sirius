#ifndef __DELAY_H__
#define __DELAY_H__

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_rom_sys.h"

#define mdelay(x) vTaskDelay(x/portTICK_PERIOD_MS)
#define udelay(x) esp_rom_delay_us(x)
#define ndelay(x) esp_rom_delay_ns(x)

#endif

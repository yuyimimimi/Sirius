#include <stdio.h>
#include "esp_chip_info.h"
#include "esp_flash.h"
#include "esp_system.h"
#include <inttypes.h>
#include "sdkconfig.h"
#include "esp_private/esp_clk.h"

int uname_cmd(int argc, char **argv)
{
    printf("Sirius kernel is open source and free to use\n");
    printf("If you like it,Please give me a star on GitHub\n");
    printf("GitHub: https://github.com/yuyimimimi/Sirius\n");
    printf("This software and any derivative works must comply with GPL v2.0\n");
    printf("using GPL-v2.0 license\n\n");       
    FILE*  fp = fopen("/etc/system/data/system_version.dat", "r");
    if(fp != NULL)
    {
        fseek(fp, 0, SEEK_END);
        long file_size = ftell(fp);
        fseek(fp, 0, SEEK_SET);
        char *system_version = (char*)malloc(file_size + 1);
        fread(system_version, 1, 1024, fp);
        system_version[file_size] = '\0';
        fclose(fp);
        printf("system version:%20s", system_version);
        free(system_version);
    }
    printf("Core%30s","FreeRTOS\n");
    
    printf("ESpidf version:%20s\n", esp_get_idf_version());
    esp_chip_info_t chip_info;  
    uint32_t flash_size;
    esp_chip_info(&chip_info);
    printf("chip message:\n                        %s \n                        %d CPU core(s)\n                        %s%s%s%s, ",CONFIG_IDF_TARGET,chip_info.cores,(chip_info.features & CHIP_FEATURE_WIFI_BGN) ? "WiFi/" : "",(chip_info.features & CHIP_FEATURE_BT) ? "BT" : "",(chip_info.features & CHIP_FEATURE_BLE) ? "BLE" : "",(chip_info.features & CHIP_FEATURE_IEEE802154) ? ", 802.15.4 (Zigbee/Thread)" : "");
    printf("802.15.4 (Zigbee/Thread)");
    printf("\ncore speed:\n                        %d MHz\n",esp_clk_cpu_freq()/1000/1000);
    unsigned major_rev = chip_info.revision / 100;
    unsigned minor_rev = chip_info.revision % 100;
    printf("silicon revision\n                        v%d.%d, ", major_rev, minor_rev);
    if(esp_flash_get_size(NULL, &flash_size) != ESP_OK) {
        printf("Get flash size failed");
        return 0;
    }
    printf("\nMinimum free heap size:\n                        %" PRIu32 " kb\n", esp_get_minimum_free_heap_size()/1024);
    return 0;
}

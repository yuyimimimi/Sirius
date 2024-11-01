#ifndef __ESPFS_H__
#define __ESPFS_H__

#include <kernelconfig>



int esp_spi_fatfs_mount_0(void);
int esp_spi_fatfs_mount_1(void);
int esp_spi_fatfs_mount_2(void);
int esp_spi_fatfs_mount_3(void);
int esp_spi_fatfs_mount_4(void);
int esp_spi_fatfs_mount_5(void);
int esp_spi_fatfs_mount_6(void);
int esp_spi_fatfs_mount_7(void);


int esp_spi_spiffs_mount_0(void);
int esp_spi_spiffs_mount_1(void);
int esp_spi_spiffs_mount_2(void);
int esp_spi_spiffs_mount_3(void);
int esp_spi_spiffs_mount_4(void);
int esp_spi_spiffs_mount_5(void);
int esp_spi_spiffs_mount_6(void);
int esp_spi_spiffs_mount_7(void);



int esp_littlefs_mount_0(void);
int esp_littlefs_mount_1(void);
int esp_littlefs_mount_2(void);
int esp_littlefs_mount_3(void);
int esp_littlefs_mount_4(void);
int esp_littlefs_mount_5(void);
int esp_littlefs_mount_6(void);
int esp_littlefs_mount_7(void);

void default_mount_esp_spi_Partition(void);
#endif
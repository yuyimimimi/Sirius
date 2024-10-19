#ifndef __ESPFS_H__
#define __ESPFS_H__

#define flash_fs 1      //FATFS  
#if flash_fs == 1
   // #define fatfs_mount_path_0       "/home"
   // #define fatfs_Partition_name_0   "p_1"
   // #define fatfs_mount_path_1       "/etc"
   // #define fatfs_Partition_name_1   "p_2"
   // #define fatfs_mount_path_2       "/usr"
   // #define fatfs_Partition_name_2   "p_3"
   // #define fatfs_mount_path_3       "/boot"
   // #define fatfs_Partition_name_3   "p_0"
   // #define fatfs_mount_path_4       "/data"
   // #define fatfs_Partition_name_4   "data"
   // #define fatfs_mount_path_5       "/tmp"
   // #define fatfs_Partition_name_5   "p_4"
   // #define fatfs_mount_path_6       "/usr"
   // #define fatfs_Partition_name_6   "p_5"
   // #define fatfs_mount_path_7       "/factory_nvs"
   // #define fatfs_Partition_name_7   "factory_nvs"
#endif

int esp_spi_fatfs_mount_0(void);
int esp_spi_fatfs_mount_1(void);
int esp_spi_fatfs_mount_2(void);
int esp_spi_fatfs_mount_3(void);
int esp_spi_fatfs_mount_4(void);
int esp_spi_fatfs_mount_5(void);
int esp_spi_fatfs_mount_6(void);
int esp_spi_fatfs_mount_7(void);


#define spiffs_fs 1     //SPIFFS  
#if spiffs_fs == 1
   // #define spiffs_mount_path_0       "/dev"
   // #define spiffs_Partition_name_0   "p_0"
   // #define spiffs_mount_path_1       "/etc"
   // #define spiffs_Partition_name_1   "p_2"
   // #define spiffs_mount_path_2      "/tmp"
   // #define spiffs_Partition_name_2  "tmp"
   // #define spiffs_mount_path_3      "/usr"
   // #define spiffs_Partition_name_3  "usr"
   // #define spiffs_mount_path_4      "/factory"
   // #define spiffs_Partition_name_4  "factory"
   // #define spiffs_mount_path_5      "/factory_nvs"
   // #define spiffs_Partition_name_5  "factory_nvs"   
   // #define spiffs_mount_path_6      "/etc"ls
   // #define spiffs_Partition_name_6  "etc"
   // #define spiffs_mount_path_7      "/var"
   // #define spiffs_Partition_name_7  "var"
#endif

int esp_spi_spiffs_mount_0(void);
int esp_spi_spiffs_mount_1(void);
int esp_spi_spiffs_mount_2(void);
int esp_spi_spiffs_mount_3(void);
int esp_spi_spiffs_mount_4(void);
int esp_spi_spiffs_mount_5(void);
int esp_spi_spiffs_mount_6(void);
int esp_spi_spiffs_mount_7(void);


#define esp_littlefs_fs 1     //LittleFS  
#if esp_littlefs_fs == 1
   // #define esp_littlefs_mount_path_0            "/etc"
   // #define esp_littlefs_Partition_name_0        "p_0"
   // #define esp_littlefs_mount_path_1            "/etc"
   // #define esp_littlefs_Partition_name_1        "p_1"
   #define esp_littlefs_mount_path_2            "/home"
   #define esp_littlefs_Partition_name_2        "p_2"
   // #define esp_littlefs_mount_path_3            "/usr"
   // #define esp_littlefs_Partition_name_3        "p_3"
   // #define esp_littlefs_mount_path_4         "/tmp"
   // #define esp_littlefs_Partition_name_4     "tmp"
   // #define esp_littlefs_mount_path_5         "/usr"
   // #define esp_littlefs_Partition_name_5     "usr"
   // #define esp_littlefs_mount_path_6         "/var"
   // #define esp_littlefs_Partition_name_6     "var"
   // #define esp_littlefs_mount_path_7         "/dev"
   // #define esp_littlefs_Partition_name_7     "p_0"
#endif

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
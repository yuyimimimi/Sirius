#include "esp_vfs.h"
#include "esp_vfs_fat.h"
#include "esp_fs/espfs.h"


#if defined(fatfs_mount_path_0)
int esp_spi_fatfs_mount_0(void)
{                
    esp_vfs_fat_mount_config_t mount_config = {
        .max_files = 8,
        .format_if_mount_failed = true,
    };
    static wl_handle_t wl_handle0 = WL_INVALID_HANDLE;
    esp_err_t err = esp_vfs_fat_spiflash_mount(fatfs_mount_path_0, fatfs_Partition_name_0, &mount_config, &wl_handle0);
    if ( err != ESP_OK )
    {
        printf("Failed to mount FATFS (%s) on %s (%s)\n", fatfs_Partition_name_0, fatfs_mount_path_0, esp_err_to_name(err));
        return -1;
    }
    return 0;
}
 #else
   int esp_spi_fatfs_mount_0(void){
        return -20;
   }
 #endif



#if defined(fatfs_mount_path_1)
int esp_spi_fatfs_mount_1(void)
{                
    esp_vfs_fat_mount_config_t mount_config = {
        .max_files = 8,
        .format_if_mount_failed = true,
    };
    static wl_handle_t wl_handle0 = WL_INVALID_HANDLE;
    esp_err_t err = esp_vfs_fat_spiflash_mount(fatfs_mount_path_1, fatfs_Partition_name_1, &mount_config, &wl_handle0);
    if ( err != ESP_OK )
    {
        printf("Failed to mount FATFS (%s) on %s (%s)\n", fatfs_Partition_name_1, fatfs_mount_path_1, esp_err_to_name(err));
        return -1;
    }
    return 0;
}
 #else
   int esp_spi_fatfs_mount_1(void){
        return -20;
   }
 #endif

 #if defined(fatfs_mount_path_2)
int esp_spi_fatfs_mount_2(void)
{                
    esp_vfs_fat_mount_config_t mount_config = {
        .max_files = 8,
        .format_if_mount_failed = true,
    };
    static wl_handle_t wl_handle0 = WL_INVALID_HANDLE;
    esp_err_t err = esp_vfs_fat_spiflash_mount(fatfs_mount_path_2, fatfs_Partition_name_2, &mount_config, &wl_handle0);
    if ( err != ESP_OK )
    {
        printf("Failed to mount FATFS (%s) on %s (%s)\n", fatfs_Partition_name_2, fatfs_mount_path_2, esp_err_to_name(err));
        return -1;
    }
    return 0;
}
 #else
   int esp_spi_fatfs_mount_2(void){
        return -20;
   }
 #endif

 #if defined(fatfs_mount_path_3)
int esp_spi_fatfs_mount_3(void)
{                
    esp_vfs_fat_mount_config_t mount_config = {
        .max_files = 4,
        .format_if_mount_failed = true,
    };
    static wl_handle_t wl_handle0 = WL_INVALID_HANDLE;
    esp_err_t err = esp_vfs_fat_spiflash_mount(fatfs_mount_path_3, fatfs_Partition_name_3, &mount_config, &wl_handle0);
    if ( err != ESP_OK )
    {
        printf("Failed to mount FATFS (%s) on %s (%s)\n", fatfs_Partition_name_3, fatfs_mount_path_3, esp_err_to_name(err));
        return -1;
    }
    return 0;
}
 #else
   int esp_spi_fatfs_mount_3(void){
        return -20;
   }
 #endif


 #if defined(fatfs_mount_path_4)
    
int esp_spi_fatfs_mount_4(void)
{                
    esp_vfs_fat_mount_config_t mount_config = {
        .max_files = 4,
        .format_if_mount_failed = true,
    };
    static wl_handle_t wl_handle0 = WL_INVALID_HANDLE;
    esp_err_t err = esp_vfs_fat_spiflash_mount(fatfs_mount_path_4, fatfs_Partition_name_4, &mount_config, &wl_handle0);
    if ( err != ESP_OK )
    {
        printf("Failed to mount FATFS (%s) on %s (%s)\n", fatfs_Partition_name_4, fatfs_mount_path_4, esp_err_to_name(err));
        return -1;
    }
    return 0;
}
 #else
   int esp_spi_fatfs_mount_4(void){
        return -20;
   }
 #endif




 #if defined(fatfs_mount_path_5)
int esp_spi_fatfs_mount_5(void)
{                
    esp_vfs_fat_mount_config_t mount_config = {
        .max_files = 4,
        .format_if_mount_failed = true,
    };
    static wl_handle_t wl_handle0 = WL_INVALID_HANDLE;
    esp_err_t err = esp_vfs_fat_spiflash_mount(fatfs_mount_path_5, fatfs_Partition_name_5, &mount_config, &wl_handle0);
    if ( err != ESP_OK )
    {
        printf("Failed to mount FATFS (%s) on %s (%s)\n", fatfs_Partition_name_5, fatfs_mount_path_5, esp_err_to_name(err));
        return -1;
    }
    return 0;
}
 #else
   int esp_spi_fatfs_mount_5(void){
        return -20;
   }
 #endif


 #if defined(fatfs_mount_path_6)
int esp_spi_fatfs_mount_6(void)
{                
    esp_vfs_fat_mount_config_t mount_config = {
        .max_files = 4,
        .format_if_mount_failed = true,
    };
    static wl_handle_t wl_handle0 = WL_INVALID_HANDLE;
    esp_err_t err = esp_vfs_fat_spiflash_mount(fatfs_mount_path_6, fatfs_Partition_name_6, &mount_config, &wl_handle0);
    if ( err != ESP_OK )
    {
        printf("Failed to mount FATFS (%s) on %s (%s)\n", fatfs_Partition_name_6, fatfs_mount_path_6, esp_err_to_name(err));
        return -1;
    }
    return 0;
}
 #else
   int esp_spi_fatfs_mount_6(void){
        return -20;
   }
 #endif


 #if defined(fatfs_mount_path_7)
int esp_spi_fatfs_mount_7(void)
{                
    esp_vfs_fat_mount_config_t mount_config = {
        .max_files = 4,
        .format_if_mount_failed = true,
    };
    static wl_handle_t wl_handle0 = WL_INVALID_HANDLE;
    esp_err_t err = esp_vfs_fat_spiflash_mount(fatfs_mount_path_7, fatfs_Partition_name_7, &mount_config, &wl_handle0);
    if ( err != ESP_OK )
    {
        printf("Failed to mount FATFS (%s) on %s (%s)\n", fatfs_Partition_name_7, fatfs_mount_path_7, esp_err_to_name(err));
        return -1;
    }
    return 0;
}
 #else
   int esp_spi_fatfs_mount_7(void){
        return -20;
   }
 #endif

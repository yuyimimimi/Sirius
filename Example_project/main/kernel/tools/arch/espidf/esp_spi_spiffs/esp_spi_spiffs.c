#include "esp_vfs.h"
#include "esp_vfs_fat.h"
#include "esp_fs/espfs.h"
#include "esp_spiffs.h"

#if defined(spiffs_mount_path_0)
int esp_spi_spiffs_mount_0(void)
{
    esp_vfs_spiffs_conf_t conf = {
       .base_path       = spiffs_mount_path_0,
       .partition_label = spiffs_Partition_name_0,
       .max_files       = 8,
       .format_if_mount_failed = true,
    };
    esp_err_t ret = esp_vfs_spiffs_register(&conf);
    if (ret != ESP_OK) {
        printf("Failed to mount or format filesystem\n");
        return -1;
    }

    ret = esp_spiffs_check(conf.partition_label);
    if(ret != ESP_OK)
    {
        printf("Failed to check filesystem\n");
        return -1;
    }
    
    size_t total = 0, used = 0;
    ret = esp_spiffs_info(conf.partition_label, &total, &used);
    if (ret != ESP_OK)
    {
        printf("Failed to get filesystem info\n");
        return -1;
    }
    return 0;
}
#else
int esp_spi_spiffs_mount_0(){
    return -20;
}
#endif


#if defined(spiffs_mount_path_1)
int esp_spi_spiffs_mount_1(void)
{
    esp_vfs_spiffs_conf_t conf = {
       .base_path       = spiffs_mount_path_1,
       .partition_label = spiffs_Partition_name_1,
       .max_files       = 8,
       .format_if_mount_failed = true,
    };
    esp_err_t ret = esp_vfs_spiffs_register(&conf);
    if (ret != ESP_OK) {
        printf("Failed to mount or format filesystem\n");
        return -1;
    }

    ret = esp_spiffs_check(conf.partition_label);
    if(ret != ESP_OK)
    {
        printf("Failed to check filesystem\n");
        return -1;
    }
    
    size_t total = 0, used = 0;
    ret = esp_spiffs_info(conf.partition_label, &total, &used);
    if (ret != ESP_OK)
    {
        printf("Failed to get filesystem info\n");
        return -1;
    }
    return 0;
}
#else
int esp_spi_spiffs_mount_1(){
    return -20;
}
#endif

#if defined(spiffs_mount_path_2)
int esp_spi_spiffs_mount_2(void)
{
    esp_vfs_spiffs_conf_t conf = {
       .base_path       = spiffs_mount_path_2,
       .partition_label = spiffs_Partition_name_2,
       .max_files       = 8,
       .format_if_mount_failed = true,
    };
    esp_err_t ret = esp_vfs_spiffs_register(&conf);
    if (ret != ESP_OK) {
        printf("Failed to mount or format filesystem\n");
        return -1;
    }

    ret = esp_spiffs_check(conf.partition_label);
    if(ret != ESP_OK)
    {
        printf("Failed to check filesystem\n");
        return -1;
    }
    
    size_t total = 0, used = 0;
    ret = esp_spiffs_info(conf.partition_label, &total, &used);
    if (ret != ESP_OK)
    {
        printf("Failed to get filesystem info\n");
        return -1;
    }
    return 0;
}
#else
int esp_spi_spiffs_mount_2(){
    return -20;
}
#endif

#if defined(spiffs_mount_path_3)
int esp_spi_spiffs_mount_3(void)
{
    esp_vfs_spiffs_conf_t conf = {
       .base_path       = spiffs_mount_path_3,
       .partition_label = spiffs_Partition_name_3,
       .max_files       = 8,
       .format_if_mount_failed = true,
    };
    esp_err_t ret = esp_vfs_spiffs_register(&conf);
    if (ret != ESP_OK) {
        printf("Failed to mount or format filesystem\n");
        return -1;
    }

    ret = esp_spiffs_check(conf.partition_label);
    if(ret != ESP_OK)
    {
        printf("Failed to check filesystem\n");
        return -1;
    }

    size_t total = 0, used = 0;
    ret = esp_spiffs_info(conf.partition_label, &total, &used);
    if (ret != ESP_OK)
    {
        printf("Failed to get filesystem info\n");
        return -1;
    }
    return 0;
}
#else
int esp_spi_spiffs_mount_3(){
    return -20;
}
#endif

#if defined(spiffs_mount_path_4)
int esp_spi_spiffs_mount_4(void)
{
    esp_vfs_spiffs_conf_t conf = {
       .base_path       = spiffs_mount_path_4,
       .partition_label = spiffs_Partition_name_4,
       .max_files       = 8,
       .format_if_mount_failed = true,
    };
    esp_err_t ret = esp_vfs_spiffs_register(&conf);
    if (ret != ESP_OK) {
        printf("Failed to mount or format filesystem\n");
        return -1;
    }

    ret = esp_spiffs_check(conf.partition_label);
    if(ret != ESP_OK)
    {
        printf("Failed to check filesystem\n");
        return -1;
    }

    size_t total = 0, used = 0;
    ret = esp_spiffs_info(conf.partition_label, &total, &used);
    if (ret != ESP_OK)
    {
        printf("Failed to get filesystem info\n");
        return -1;
    }
    return 0;
}
#else
int esp_spi_spiffs_mount_4(){
    return -20;
}
#endif

#if defined(spiffs_mount_path_5)
int esp_spi_spiffs_mount_5(void)
{
    esp_vfs_spiffs_conf_t conf = {
       .base_path       = spiffs_mount_path_5,
       .partition_label = spiffs_Partition_name_5,
       .max_files       = 8,
       .format_if_mount_failed = true,
    };
    esp_err_t ret = esp_vfs_spiffs_register(&conf);
    if (ret != ESP_OK) {
        printf("Failed to mount or format filesystem\n");
        return -1;
    }

    ret = esp_spiffs_check(conf.partition_label);
    if(ret != ESP_OK)
    {
        printf("Failed to check filesystem\n");
        return -1;
    }

    size_t total = 0, used = 0;
    ret = esp_spiffs_info(conf.partition_label, &total, &used);
    if (ret != ESP_OK)
    {
        printf("Failed to get filesystem info\n");
        return -1;
    }
    return 0;
}
#else
int esp_spi_spiffs_mount_5(){
    return -20;
}
#endif


#if defined(spiffs_mount_path_6)
int esp_spi_spiffs_mount_6(void)
{
    esp_vfs_spiffs_conf_t conf = {
       .base_path       = spiffs_mount_path_6,
       .partition_label = spiffs_Partition_name_6,
       .max_files       = 8,
       .format_if_mount_failed = true,
    };
    esp_err_t ret = esp_vfs_spiffs_register(&conf);
    if (ret != ESP_OK) {
        printf("Failed to mount or format filesystem\n");
        return -1;
    }

    ret = esp_spiffs_check(conf.partition_label);
    if(ret != ESP_OK)
    {
        printf("Failed to check filesystem\n");
        return -1;
    }

    size_t total = 0, used = 0;
    ret = esp_spiffs_info(conf.partition_label, &total, &used);
    if (ret != ESP_OK)
    {
        printf("Failed to get filesystem info\n");
        return -1;
    }
    return 0;
}
#else
int esp_spi_spiffs_mount_6(){
    return -20;
}
#endif


#if defined(spiffs_mount_path_7)
int esp_spi_spiffs_mount_7(void)
{
    esp_vfs_spiffs_conf_t conf = {
       .base_path       = spiffs_mount_path_7,
       .partition_label = spiffs_Partition_name_7,
       .max_files       = 8,
       .format_if_mount_failed = true,
    };
    esp_err_t ret = esp_vfs_spiffs_register(&conf);
    if (ret != ESP_OK) {
        printf("Failed to mount or format filesystem\n");
        return -1;
    }

    ret = esp_spiffs_check(conf.partition_label);
    if(ret != ESP_OK)
    {
        printf("Failed to check filesystem\n");
        return -1;
    }

    size_t total = 0, used = 0;
    ret = esp_spiffs_info(conf.partition_label, &total, &used);
    if (ret != ESP_OK)
    {
        printf("Failed to get filesystem info\n");
        return -1;
    }
    return 0;
}
#else
int esp_spi_spiffs_mount_7(){
    return -20;
}
#endif

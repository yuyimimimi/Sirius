#include "esp_fs/espfs.h"
#include "esp_littlefs.h"
#include <linux/errno.h>
#include <linux/module.h>
#include <linux/slab.h>
#include <linux/uaccess.h>
#include <linux/init.h>
#define esp_littlefs_tag "[esp_littlefs]"



int __init mount_start_partition(char *paartition_name)
{
    esp_err_t err;
    esp_vfs_littlefs_conf_t conf = {
       .base_path      = "/etc",
       .partition_label = paartition_name,
       .format_if_mount_failed = true,
       .grow_on_mount = true,
    };
    err = esp_vfs_littlefs_register(&conf);
    if (err != ESP_OK) {
        ESP_LOGE(esp_littlefs_tag, "Failed to mount filesystem. Error: %s", esp_err_to_name(err));
        return -1;
    }
    return 0;
}

#if defined(esp_littlefs_mount_path_0)&&defined(esp_littlefs_Partition_name_0)
int __init esp_littlefs_mount_0(void)
{
    esp_err_t err;
    esp_vfs_littlefs_conf_t conf = {
       .base_path      = esp_littlefs_mount_path_0,
       .partition_label = esp_littlefs_Partition_name_0,
       .format_if_mount_failed = true,
       .grow_on_mount = true,
    };
    err = esp_vfs_littlefs_register(&conf);
    if (err != ESP_OK) {
        ESP_LOGE(esp_littlefs_tag, "Failed to mount filesystem. Error: %s", esp_err_to_name(err));
        return -1;
    }
    return 0;
}
#else
int esp_littlefs_mount_0(void){
    return -20;
}
#endif 

#if defined(esp_littlefs_mount_path_1)&&defined(esp_littlefs_Partition_name_1)
int __init esp_littlefs_mount_1(void)
{
    esp_err_t err;
    esp_vfs_littlefs_conf_t conf = {
       .base_path = esp_littlefs_mount_path_1,
       .partition_label = esp_littlefs_Partition_name_1,
       .format_if_mount_failed = true,
       .grow_on_mount = true,
    };
    err = esp_vfs_littlefs_register(&conf);
    if (err != ESP_OK) {
        ESP_LOGE(esp_littlefs_tag, "Failed to mount filesystem. Error: %s", esp_err_to_name(err));
        return -1;
    }
        return 0;
}
#else
int esp_littlefs_mount_1(void){
    return -20;
}
#endif 


#if defined(esp_littlefs_mount_path_2)&&defined(esp_littlefs_Partition_name_2)
int __init esp_littlefs_mount_2(void)
{
    esp_err_t err;
    esp_vfs_littlefs_conf_t conf = {
       .base_path = esp_littlefs_mount_path_2,
       .partition_label = esp_littlefs_Partition_name_2,
       .format_if_mount_failed = true,
       .grow_on_mount = true,
    };
    err = esp_vfs_littlefs_register(&conf);
    if (err != ESP_OK) {
        ESP_LOGE(esp_littlefs_tag, "Failed to mount filesystem. Error: %s", esp_err_to_name(err));
        return -1;
    }
        return 0;
}
#else
int esp_littlefs_mount_2(void){
    return -20;
}
#endif 

#if defined(esp_littlefs_mount_path_3)&&defined(esp_littlefs_Partition_name_3)
int __init esp_littlefs_mount_3(void)
{
    esp_err_t err;
    esp_vfs_littlefs_conf_t conf = {
       .base_path = esp_littlefs_mount_path_3,
       .partition_label = esp_littlefs_Partition_name_3,
       .format_if_mount_failed = true,
       .grow_on_mount = true,
    };
    err = esp_vfs_littlefs_register(&conf);
    if (err != ESP_OK) {
        ESP_LOGE(esp_littlefs_tag, "Failed to mount filesystem. Error: %s", esp_err_to_name(err));
        return -1;
    }
        return 0;
}
#else
int esp_littlefs_mount_3(void){
    return -20;
}
#endif 

#if defined(esp_littlefs_mount_path_4)&&defined(esp_littlefs_Partition_name_4)
int __init esp_littlefs_mount_4(void)
{
    esp_err_t err;
    esp_vfs_littlefs_conf_t conf = {
       .base_path = esp_littlefs_mount_path_4,
       .partition_label = esp_littlefs_Partition_name_4,
       .format_if_mount_failed = true,
       .grow_on_mount = true,
    };
    err = esp_vfs_littlefs_register(&conf);
    if (err != ESP_OK) {
        ESP_LOGE(esp_littlefs_tag, "Failed to mount filesystem. Error: %s", esp_err_to_name(err));
        return -1;
    }
        return 0;
}
#else
int esp_littlefs_mount_4(void){
    return -20;
}
#endif 


#if defined(esp_littlefs_mount_path_5)&&defined(esp_littlefs_Partition_name_5)
int __init esp_littlefs_mount_5(void)
{
    esp_err_t err;
    esp_vfs_littlefs_conf_t conf = {
       .base_path = esp_littlefs_mount_path_5,
       .partition_label = esp_littlefs_Partition_name_5,
       .format_if_mount_failed = true,
       .grow_on_mount = true,
    };
    err = esp_vfs_littlefs_register(&conf);
    if (err != ESP_OK) {
        ESP_LOGE(esp_littlefs_tag, "Failed to mount filesystem. Error: %s", esp_err_to_name(err));
        return -1;
    }
        return 0;
}
#else
int esp_littlefs_mount_5(void){
    return -20;
}
#endif 


#if defined(esp_littlefs_mount_path_6)&&defined(esp_littlefs_Partition_name_6)
int __init esp_littlefs_mount_6(void)
{
    esp_err_t err;
    esp_vfs_littlefs_conf_t conf = {
       .base_path = esp_littlefs_mount_path_6,
       .partition_label = esp_littlefs_Partition_name_6,
       .format_if_mount_failed = true,
       .grow_on_mount = true,
    };
    err = esp_vfs_littlefs_register(&conf);
    if (err != ESP_OK) {
        ESP_LOGE(esp_littlefs_tag, "Failed to mount filesystem. Error: %s", esp_err_to_name(err));
        return -1;
    }
        return 0;
}
#else
int esp_littlefs_mount_6(void){
    return -20;
}
#endif 


#if defined(esp_littlefs_mount_path_7)&&defined(esp_littlefs_Partition_name_7)
int __init esp_littlefs_mount_7(void)
{
    esp_err_t err;
    esp_vfs_littlefs_conf_t conf = {
       .base_path = esp_littlefs_mount_path_7,
       .partition_label = esp_littlefs_Partition_name_7,
       .format_if_mount_failed = true,
       .grow_on_mount = true,
    };
    err = esp_vfs_littlefs_register(&conf);
    if (err != ESP_OK) {
        ESP_LOGE(esp_littlefs_tag, "Failed to mount filesystem. Error: %s", esp_err_to_name(err));
        return -1;
    }
        return 0;
}
#else
int esp_littlefs_mount_7(void){
    return -20;
}
#endif 


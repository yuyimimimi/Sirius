#include "esp_fs/espfs.h"
#include "linux/errno.h"
#include "linux/printk.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <linux/vfs/vfs.h>

char *DEFAULT_MOUNT_PARTNER_TAG ="[DEFAULT_MOUNT_COMPONENT]:";

void default_mount_esp_spi_Partition(void)
{
    create_vfs_node_file("/etc","mount_point",0);

    #if defined(fatfs_Partition_name_0)&&defined(fatfs_mount_path_0)
        if(esp_spi_fatfs_mount_0()==0)
        {
            printk(DEFAULT_MOUNT_PARTNER_TAG,"mount %s  on %s",fatfs_Partition_name_0,fatfs_mount_path_0);
            create_vfs_node_file(fatfs_mount_path_0,"mount_point",0);
        }
    #endif
    #if defined(fatfs_Partition_name_1)&&defined(fatfs_mount_path_1)
        if(esp_spi_fatfs_mount_1()==0)
        {
            printk(DEFAULT_MOUNT_PARTNER_TAG,"mount %s  on %s",fatfs_Partition_name_1,fatfs_mount_path_1);
            create_vfs_node_file(fatfs_mount_path_1,"mount_point",0);
        }
    #endif
    #if defined(fatfs_Partition_name_2)&&defined(fatfs_mount_path_2)
        if(esp_spi_fatfs_mount_2()==0)
        {
            printk(DEFAULT_MOUNT_PARTNER_TAG,"mount %s  on %s",fatfs_Partition_name_2,fatfs_mount_path_2);
            create_vfs_node_file(fatfs_mount_path_2,"mount_point",0);
        }
    #endif
    #if defined(fatfs_Partition_name_3)&&defined(fatfs_mount_path_3)
        if(esp_spi_fatfs_mount_3()==0)
        {
            printk(DEFAULT_MOUNT_PARTNER_TAG,"mount %s  on %s",fatfs_Partition_name_3,fatfs_mount_path_3);
            create_vfs_node_file(fatfs_mount_path_3,"mount_point",0);
        }
    #endif
    #if defined(fatfs_Partition_name_4)&&defined(fatfs_mount_path_4)
        if(esp_spi_fatfs_mount_4()==0)
        {
            printk(DEFAULT_MOUNT_PARTNER_TAG,"mount %s  on %s",fatfs_Partition_name_4,fatfs_mount_path_4);
            create_vfs_node_file(fatfs_mount_path_4,"mount_point",0);
        }
    #endif
    #if defined(fatfs_Partition_name_5)&&defined(fatfs_mount_path_5)
        if(esp_spi_fatfs_mount_5()==0)
        {
            printk(DEFAULT_MOUNT_PARTNER_TAG,"mount %s  on %s",fatfs_Partition_name_5,fatfs_mount_path_5);
            create_vfs_node_file(fatfs_mount_path_5,"mount_point",0);
        }
    #endif
    #if defined(fatfs_Partition_name_6)&&defined(fatfs_mount_path_6)
        if(esp_spi_fatfs_mount_6()==0)
        {
            printk(DEFAULT_MOUNT_PARTNER_TAG,"mount %s  on %s",fatfs_Partition_name_6,fatfs_mount_path_6);
            create_vfs_node_file(fatfs_mount_path_6,"mount_point",0);
        }
    #endif
    #if defined(fatfs_Partition_name_7)&&defined(fatfs_mount_path_7)
        if(esp_spi_fatfs_mount_7()==0)
        {
            printk(DEFAULT_MOUNT_PARTNER_TAG,"mount %s  on %s",fatfs_Partition_name_7,fatfs_mount_path_7);
            create_vfs_node_file(fatfs_mount_path_7,"mount_point",0);
        }
    #endif
    #if defined(spiffs_Partition_name_0)&&defined(spiffs_mount_path_0)
        if(esp_spi_spiffs_mount_0()==0)
        {
            printk(DEFAULT_MOUNT_PARTNER_TAG,"mount %s on %s",spiffs_Partition_name_0,spiffs_mount_path_0);
            create_vfs_node_file(spiffs_mount_path_0,"mount_point",0);
        }
    #endif
    #if defined(spiffs_Partition_name_1)&&defined(spiffs_mount_path_1)
        if(esp_spi_spiffs_mount_1()==0)
        {
            printk(DEFAULT_MOUNT_PARTNER_TAG,"mount %s on %s",spiffs_Partition_name_1,spiffs_mount_path_1);
            create_vfs_node_file(spiffs_mount_path_1,"mount_point",0);
        }
    #endif
    #if defined(spiffs_Partition_name_2)&&defined(spiffs_mount_path_2)
        if(esp_spi_spiffs_mount_2()==0)
        {
            printk(DEFAULT_MOUNT_PARTNER_TAG,"mount %s on %s",spiffs_Partition_name_2,spiffs_mount_path_2);
            create_vfs_node_file(spiffs_mount_path_2,"mount_point",0);
        }
    #endif
    #if defined(spiffs_Partition_name_3)&&defined(spiffs_mount_path_3)
        if(esp_spi_spiffs_mount_3()==0)
        {
            printk(DEFAULT_MOUNT_PARTNER_TAG,"mount %s on %s",spiffs_Partition_name_3,spiffs_mount_path_3);
            create_vfs_node_file(spiffs_mount_path_3,"mount_point",0);
        }
    #endif
    #if defined(spiffs_Partition_name_4)&&defined(spiffs_mount_path_4)
        if(esp_spi_spiffs_mount_4()==0)
        {
            printk(DEFAULT_MOUNT_PARTNER_TAG,"mount %s on %s",spiffs_Partition_name_4,spiffs_mount_path_4);
            create_vfs_node_file(spiffs_mount_path_4,"mount_point",0);
        }
    #endif
    #if defined(spiffs_Partition_name_5)&&defined(spiffs_mount_path_5)
        if(esp_spi_spiffs_mount_5()==0)
        {
            printk(DEFAULT_MOUNT_PARTNER_TAG,"mount %s on %s",spiffs_Partition_name_5,spiffs_mount_path_5);
            create_vfs_node_file(spiffs_mount_path_5,"mount_point",0);
        }
    #endif
    #if defined(spiffs_Partition_name_6)&&defined(spiffs_mount_path_6)
        if(esp_spi_spiffs_mount_6()==0)
        {
            printk(DEFAULT_MOUNT_PARTNER_TAG,"mount %s on %s",spiffs_Partition_name_6,spiffs_mount_path_6);
            create_vfs_node_file(spiffs_mount_path_6,"mount_point",0);
        }
    #endif
    #if defined(spiffs_Partition_name_7)&&defined(spiffs_mount_path_7)
        if(esp_spi_spiffs_mount_7()==0)
        {
            printk(DEFAULT_MOUNT_PARTNER_TAG,"mount %s on %s",spiffs_Partition_name_7,spiffs_mount_path_7);
            create_vfs_node_file(spiffs_mount_path_7,"mount_point",0);
        }
    #endif
    #if defined(esp_littlefs_mount_path_0)&&defined(esp_littlefs_Partition_name_0)
        if(esp_littlefs_mount_0()==0)
        {            
            printk(DEFAULT_MOUNT_PARTNER_TAG,"mount %s on %s",esp_littlefs_Partition_name_0,esp_littlefs_mount_path_0);
            create_vfs_node_file(esp_littlefs_Partition_name_0,"mount_point",0);
        }
    #endif
    #if defined(esp_littlefs_mount_path_1)&&defined(esp_littlefs_Partition_name_1)
        if(esp_littlefs_mount_1()==0)
        {
            printk(DEFAULT_MOUNT_PARTNER_TAG,"mount %s on %s",esp_littlefs_Partition_name_1,esp_littlefs_mount_path_1);
            create_vfs_node_file(esp_littlefs_mount_path_1,"mount_point",0);
        }
    #endif
    #if defined(esp_littlefs_mount_path_2)&&defined(esp_littlefs_Partition_name_2)
        if(esp_littlefs_mount_2()==0)
        {   
            create_vfs_node_file(esp_littlefs_mount_path_2,"mount_point",0);
            printk(DEFAULT_MOUNT_PARTNER_TAG,"mount %s on %s",esp_littlefs_Partition_name_2,esp_littlefs_mount_path_2);
        }
    #endif
    #if defined(esp_littlefs_mount_path_3)&&defined(esp_littlefs_Partition_name_3)
        if(esp_littlefs_mount_3()==0)
        {
            printk(DEFAULT_MOUNT_PARTNER_TAG,"mount %s on %s",esp_littlefs_Partition_name_3,esp_littlefs_mount_path_3);
            create_vfs_node_file(esp_littlefs_mount_path_3,5,0);
        }
    #endif
    #if defined(esp_littlefs_mount_path_4)&&defined(esp_littlefs_Partition_name_4)
        if(esp_littlefs_mount_4()==0)
        {
            printk(DEFAULT_MOUNT_PARTNER_TAG,"mount %s on %s",esp_littlefs_Partition_name_4,esp_littlefs_mount_path_4);
            create_vfs_node_file(esp_littlefs_mount_path_4,"mount_point",0);
        }
    #endif
    #if defined(esp_littlefs_mount_path_5)&&defined(esp_littlefs_Partition_name_5)
        if(esp_littlefs_mount_5()==0)
        {
            printk(DEFAULT_MOUNT_PARTNER_TAG,"mount %s on %s",esp_littlefs_Partition_name_5,esp_littlefs_mount_path_5);
            create_vfs_node_file(esp_littlefs_mount_path_5,"mount_point",0);
        }
    #endif
    #if defined(esp_littlefs_mount_path_6)&&defined(esp_littlefs_Partition_name_6)
        if(esp_littlefs_mount_6()==0)
        {
            printk(DEFAULT_MOUNT_PARTNER_TAG,"mount %s on %s",esp_littlefs_Partition_name_6,esp_littlefs_mount_path_6);
            create_vfs_node_file(esp_littlefs_mount_path_6,"mount_point",0);
        }
    #endif
    #if defined(esp_littlefs_mount_path_7)&&defined(esp_littlefs_Partition_name_7)
        if(esp_littlefs_mount_7()==0)
        {
            printk(DEFAULT_MOUNT_PARTNER_TAG,"mount %s on %s",esp_littlefs_Partition_name_7,esp_littlefs_mount_path_7);
            create_vfs_node_file(esp_littlefs_mount_path_7,"mount_point",0);
        }
    #endif
}



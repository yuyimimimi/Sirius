/**
 * 本文件用于对接sepidf的虚拟文件系统，将vfs挂载到exp_vfs中，提供和linux系统的vfs接口一致的接口
 **/

//espidf接口
#include "esp_vfs.h"
//linux系统接口
#include <linux/kernel.h>
#include <linux/fs.h>




esp_vfs_t exp_vfs = {
   .flags = ESP_VFS_FLAG_DEFAULT,
};



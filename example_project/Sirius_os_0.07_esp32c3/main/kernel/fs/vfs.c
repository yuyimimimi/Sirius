#include <stdio.h>
#include <stdlib.h>
#include "esp_vfs.h"
#include "esp_spiffs.h"
#include "esp_partition.h"
#include "linux/fs.h"
#include "linux/errno.h"
#include "linux/printk.h"
#include "linux/slab.h"
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <string.h>
#include <pthread.h>
#include <sys/_default_fcntl.h>
#include <stdarg.h>
#include "cJSON.h"
#include <linux/vfs/vfs.h>


uint32_t MKDEV(uint16_t major, uint16_t minor );
uint32_t insert_major(uint32_t major);
ssize_t myfs_write(void *ctx, int fd, const void *data, size_t size);

pthread_mutex_t majors_mutex = PTHREAD_MUTEX_INITIALIZER;
const char * FS_TAG = "[FILE SYSTEM]:";
uint32_t *devce_number;
int length=0;
int used=0;

static uint32_t* get_place_by_device_number(uint32_t devicenumber)
{
    uint32_t *place = NULL;
    for (int i = 0; i < used; i++){
        if (devce_number[i] == devicenumber){
            place = &devce_number[i];
            break;
    }}
    return place;
} 

int get_boot_mode(); 

uint32_t register_chrdev(uint32_t dev_number,char* name,file_operations_t *fops, ...)
{  
    if(get_boot_mode() == 0) return 0; //恢复启动模式不提供注册驱动功能
    char buffer[128];
    va_list args;
    va_start(args, name);
    vsnprintf(buffer, sizeof(buffer), name, args);
    va_end(args);
    char new_name[128];
    {
        strcpy(new_name, "/dev/");
        strcat(new_name + 5, buffer);
    }
    pthread_mutex_lock(&majors_mutex);                   //加锁

    char* path = new_name;
    int device_number;
    if((dev_number & 0xffff0000) ==  0)         //如果只输入主设备号，则自动分配次设备号
    {
        device_number = (dev_number<<16) + 1; 
        if((used + 1 )>=length)
        {
            uint32_t *new_devce_number = (uint32_t*)vmalloc((length+10)*sizeof(uint32_t));
            if(new_devce_number == NULL)
            {
                printk(KERN_INFO "Failed to allocate memory for devce_number\n");
                return 0;
            }
            length+=10;
            for (size_t i = 0; i < used; i++)
            {
                new_devce_number[i]=devce_number[i];
            }
            vfree(devce_number);
            devce_number = new_devce_number;
        }
        if(device_number == 0)                                           
        {
            device_number = 0x00f00000;
        }
        device_number = MKDEV(device_number >> 16, device_number);   
        insert_major(device_number); 
    }
    else
    {
        device_number = dev_number;
    }

    fops->flags = ESP_VFS_FLAG_CONTEXT_PTR;

    // esp_vfs_t *vfs = (esp_vfs_t *)malloc(sizeof(esp_vfs_t));
    // vfs->flags    =  ESP_VFS_FLAG_CONTEXT_PTR;
    // vfs->open_p   =  fops->open;
    // vfs->ioctl_p  =  fops->ioctl;
    // vfs->read_p   =  fops->read;
    // vfs->close_p  =  fops->release;
    // vfs->write_p    =  fops->write;



    uint32_t *place = get_place_by_device_number(device_number);
    esp_err_t ret = esp_vfs_register(path, fops, place);

    if (ret != ESP_OK) {
        pr_err(FS_TAG,"Failed to register device: %s, err: %d\n", path, ret);
        return -1;
    }

    create_vfs_node_file(path,"device",device_number);
    printk(KERN_INFO "driver installed:dev_path:%s, device_num: %#lx\n",path, (long unsigned int)device_number);                                       

    pthread_mutex_unlock(&majors_mutex);                           
    return device_number;
}


uint32_t search_major(uint32_t major)
{
      int left = 0, right = used - 1;

    while (left <= right) 
    {
        int mid = (left + right) / 2;
        if (devce_number[mid] == major) 
        {
            return mid;
        }
         else if (devce_number[mid] < major) 
        {
            left = mid + 1;
        }
         else 
        {
            right = mid - 1;
        }
    }
    return left;  
}

uint32_t insert_major(uint32_t major)
{
    if(used == 0)
    {
        devce_number[0]=major;
        used++;
        return major;
    }
    int ma = search_major(major);
    for(int i=used;i>=ma;i--)
    {
        devce_number[i+1]=devce_number[i];
    }
    devce_number[ma]=major;
    used++;
    return major;
}




uint32_t MKDEV(uint16_t major, uint16_t minor )
{

    uint32_t dev_num = (major << 16) | minor;


        int ma = search_major(dev_num);    

        if(devce_number[ma] == dev_num)                         
        {
            int i = 1;
            while (devce_number[ma+i] == dev_num+i)             
            {
                i++;
            }
        return dev_num+i;
        }
        else                                                              
        {
            return dev_num;
        }
}

uint32_t MAJOR(uint32_t dev_num)
{
    return dev_num >> 16;
}
uint32_t MINOR(uint32_t dev_num)
{
    return dev_num & 0xffff;
}

void unregister_chrdev(uint32_t major,char* name,...)         
{
    char *buffer;
    va_list args;
    va_start(args, name);
    vasprintf(&buffer, name, args);
    va_end(args);
    name = buffer;
    int ma = search_major(major);
    if(ma >= 0 && devce_number[ma] == major)
    { 
        for(int i=ma;i<used-1;i++)
        {
            devce_number[i]=devce_number[i+1];
        }
        used--; 
    }   
    esp_vfs_unregister(strcat("/dev/", name));
    free(buffer);
}


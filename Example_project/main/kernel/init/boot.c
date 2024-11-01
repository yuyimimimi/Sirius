#include <console_cop.h>
#include <linux/init.h>
#include <shell.h>
#include <linux/gpio.h>
#include <registry.h>
#include <linux/vfs/vfs.h>
#include <freertos/FreeRTOS.h>
#include "linux/vfs/vfs.h"
#include "esp_fs/espfs.h"
#include "esp_console/console.h"
#include <stdio.h>
#include <freertos/task.h>
#include "freertos/FreeRTOS.h"
#include "env.h"
#include <kernelconfig>


int  mount_start_partition(char *paartition_name);

int __init int_display_system(); 
void __init init_drivers(void);
static int get_bootdata(){
    FILE *startconfig_file = fopen("/etc/boot.sh", "r");
    if (startconfig_file == NULL) {
        startconfig_file = fopen("/etc/boot.sh", "w"); // 创建启动配置文件
        fwrite("0", 1, 1, startconfig_file);
        fclose(startconfig_file);
        printf("No boot config found, booting in recovery mode.\n");
        return -1;
    }
    char startconfig;
    fseek(startconfig_file, 0, SEEK_END);
    int size = ftell(startconfig_file);
    fseek(startconfig_file, 0, SEEK_SET);
    if(size == 0){
        fclose(startconfig_file);
        startconfig_file = fopen("/etc/boot.sh", "w"); // 创建启动配置文件
        fwrite("0", 1, 1, startconfig_file);
        fclose(startconfig_file);
        printf("No boot config found, booting in recovery mode.\n");
        return -1;
    } 
    fread(&startconfig, 1, 1, startconfig_file);
    fclose(startconfig_file);
    int number = startconfig - '0';
    return number;
}

static void set_bootdata(int number){
    FILE *env_file = fopen("/etc/boot.sh", "w");
    if(env_file != NULL){
        char number_char = number + '0';
        fwrite(&number_char, 1, 1, env_file);
        fclose(env_file);
    }
}

static int boot_limit_count = 9;   //如果连续异常关机次数次超过这个值，则进入recovery模式
static void Addition_bootdata(){
    int number = get_bootdata();
    if(number < 0){
        set_bootdata(0);
    }
    else if(number < boot_limit_count ){
        number = number + 1;
        set_bootdata(number);        
    }
}

void reset_boot_time_count(){
    set_bootdata(0);
}

int get_boot_mode(){
    int num = get_bootdata();
    if(num < 0){
        return 0;
    }
    if(num >= boot_limit_count){
       return 0;
    }
    return 1;
}
void _set_memory_size(int size);


static void __init normal_mode_init(void){
    printf("Normal Mode Starting...\n");
    init_env();                         
    registry_init();                    
    init_vfs_registry();                
    default_mount_esp_spi_Partition();  
    gpio_subsystem_init();
    int_display_system();             
    init_normal_console();             
    shell_cmd_init();             
}

static void __init recovery_mode_init(void){
    registry_init();
    init_vfs_registry();
    default_mount_esp_spi_Partition();  
    int_display_system();   
    recovery_mode_shell_cmd_init();
    init_console_recovery_mode();     
}

void __init system_boot(void) {
    _set_memory_size(esp_get_minimum_free_heap_size());
    printf("Kernel Starting...\n");
    mount_start_partition(boot_partition_name);        // 挂载启动分区必须为little_fs分区
    if(get_boot_mode() == 1){
        Addition_bootdata();             // 增加启动次数,使用reboot指令可以重置启动次数。任何非正常关机都会导致计数增加，超过阈值强制进入recovery模式。
        normal_mode_init();        
    }
    else{
        recovery_mode_init();        
    }
}

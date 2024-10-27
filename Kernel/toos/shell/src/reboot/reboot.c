#include "esp_system.h"
#include "esp_log.h"

void reset_boot_time_count();
int reboot_main(int argc, char **argv)
{
    reset_boot_time_count();   //重置重启计数
    esp_restart(); 
    return 0;
}

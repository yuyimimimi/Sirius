#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "esp_system.h"
#include "esp_timer.h"

int uptime_command(int argc, char *argv[]) {
    // 获取当前时间
    time_t current_time;
    time(&current_time);

    // 获取系统启动时间（单位：微秒）
    uint64_t uptime_us = esp_timer_get_time();
    
    // 将系统运行时长转换为秒
    double uptime_seconds = uptime_us / 1000000.0;

    // 将运行时长转换为时分秒格式
    int hours = (int)(uptime_seconds / 3600);
    int minutes = (int)((uptime_seconds - hours * 3600) / 60);
    int seconds = (int)(uptime_seconds - hours * 3600 - minutes * 60);

    // 打印系统启动以来的运行时间
    printf("System uptime: %02d:%02d:%02d\n", hours, minutes, seconds);

    return 0;
}

int uptime(int argc, char *argv[]) {
    return uptime_command(argc, argv);
}

#include "esp_timer.h"
#include "stdio.h"
#include "stdarg.h"

void printk( const char *format, ...) {
    char buffer[1024];  // 用于存储格式化的输出
    va_list args;
    va_start(args, format);
    vsnprintf(buffer, sizeof(buffer), format, args);
    va_end(args);

    int64_t timestamp = esp_timer_get_time();
    double seconds = timestamp / 1000000.0;  // 转换为秒

    // 输出时间戳和日志级别
    printf("\n[%12.6f] %s   ", seconds, buffer);
}

#include <stdio.h>
#include <string.h>
#include "env.h"
#include <sys/stat.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>
#include <linux/mutex.h>
#include <kernelconfig>



#if defined(LOG_OUTPUT_TO_FILE)

static char  *log_file_path;

static char *log_file_path = NULL;
static struct mutex log_mutex;
static char *log_buffer = NULL;
static int log_buffer_size = LOG_BUFFER_SIZE;
static int log_buffer_index = 0;



void log_init(void)
{
    char *log_path = getenv_("LOG_PATH");
    if(log_path == NULL) {
         log_path = "/etc/var/log/logfile.log";
         setenv_("LOG_PATH", log_path, 1);
         
         struct stat st = {0};            
         if (stat("/etc/var", &st) == -1) {         
            if(mkdir("/etc/var", 0755)!= 0)
            {
                printf("Failed to create directory %s\n", log_path);
                perror("mkdir");
                return;
            }
         }
        if (stat("/etc/var/log", &st) == -1) {    
         if(mkdir("/etc/var/log", 0755)!= 0)
         {
            printf("Failed to create directory %s\n", log_path);
            perror("mkdir");
            return;
         }
        }

         FILE *fp = fopen(log_path, "w");
         if(fp == NULL) {
            printf("Failed to open file %s\n", log_path);
            perror("fopen");
            return;
         }
         fprintf(fp, "This is a log file\n");
         fclose(fp);
    }
    else
    {
     log_path = getenv_("LOG_PATH");
     FILE *fp = fopen(log_path, "a");
     if(fp == NULL) {
        fp = fopen(log_path, "w");
        if(fp == NULL) {
            printf("Failed to open file %s\n", log_path);
            perror("fopen");
            return;
        }
        fprintf(fp, "This is a log file\n");
        fclose(fp);
     }
     else
     {
         fclose(fp);        
     }
    }
    
    log_file_path =(char*)malloc(strlen(log_path)+1);
    strcpy(log_file_path, log_path);
}



void rotate_log_file() {
    if (log_file_path == NULL) return; // 确保 log_file_path 有效

    char backup_file_path[256];
    snprintf(backup_file_path, sizeof(backup_file_path), "%s.1", log_file_path);

    remove(backup_file_path);

    if (rename(log_file_path, backup_file_path) != 0) {
        perror("Failed to rotate log file");
    }
}

void log_save();
void log_write_buffer(char *msg) {
    int len = strlen(msg);
    if (len > LOG_BUFFER_SIZE) {
        printf("log_write: log message too long\n");
        return;
    }
    // 如果缓冲区不足，先保存当前日志内容
    if (log_buffer_index + len + 1 > log_buffer_size) {
   
        log_save();
    }
    // 将日志写入缓冲区
    memcpy(log_buffer + log_buffer_index, msg, len);
    log_buffer_index += len;
}

// 将缓冲区内容写入文件
void log_save() {
    if (log_file_path == NULL) return;
    if (log_buffer_index == 0) return; // 如果没有内容，不做任何操作
    // 检查日志文件大小
    struct stat st;
    if (stat(log_file_path, &st) == 0 && st.st_size >= MAX_LOG_FILE_SIZE) {
        rotate_log_file();
    }

    // 打开日志文件，追加模式
    FILE *fp = fopen(log_file_path, "a");
    if (fp == NULL) {
        printf("Failed to open file %s\n", log_file_path);
        perror("fopen");
        return;
    }

    // 写入缓冲区内容到日志文件
    fprintf(fp, "%s", log_buffer);
    
    // 清空缓冲区
    log_buffer_index = 0;
    memset(log_buffer, 0, log_buffer_size);

    fclose(fp);
}



int inited = 0;
void buffer_init()
{
    if(inited == 0)
    {
        mutex_init(log_mutex);
        log_buffer = (char*)malloc(LOG_BUFFER_SIZE); 
        inited = 1;
    }
} 


// 格式化日志写入
void log_write(const char *format, ...) {
    buffer_init();
    char msg[LOG_BUFFER_SIZE];
    va_list args;
    va_start(args, format);
    vsnprintf(msg, sizeof(msg), format, args);
    va_end(args);

    mutex_lock(log_mutex);
    log_write_buffer(msg); // 将格式化后的消息写入缓冲区
    mutex_unlock(log_mutex);
}
#endif
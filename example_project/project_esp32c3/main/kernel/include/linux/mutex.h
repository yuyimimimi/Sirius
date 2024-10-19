#ifndef _LINUX_MUTEX_H
#define _LINUX_MUTEX_H

#include <linux/printk.h>
#include<freertos/FreeRTOS.h>
#include<freertos/semphr.h>



struct device;


typedef struct mutex {
    SemaphoreHandle_t sem;
};


#define mutex_lock(lock)                  \
    do {                                   \
        if (xSemaphoreTake((lock).sem, portMAX_DELAY) != pdTRUE) { \
        }                                  \
    } while (0)

#define mutex_unlock(lock)                \
    do {                                   \
        if (xSemaphoreGive((lock).sem) != pdTRUE) { \
        }                                  \
    } while (0)

#define mutex_init(lock)                  \
    do {                                   \
        (lock).sem = xSemaphoreCreateMutex(); \
    } while (0)

#define mutex_destroy(lock)               \
    do {                                   \
        vSemaphoreDelete((lock).sem);     \
    } while (0)
#endif /* _LINUX_MUTEX_H */



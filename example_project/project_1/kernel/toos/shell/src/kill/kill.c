#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <stdio.h>
#include <string.h>

int kill_cmd(int argc, char **argv) 
{
    if (argc < 2) {
        printf("Usage: kill <task_name>\n");
        return -1;
    }

    TaskHandle_t taskToKill = NULL;
    // 获取系统中所有任务
    TaskStatus_t taskStatusArray[10];  // 根据需要调整大小
    UBaseType_t taskCount, x;

    taskCount = uxTaskGetSystemState(taskStatusArray, 10, NULL);

    // 查找指定名称的任务
    for (x = 0; x < taskCount; x++) {
        if (strcmp(taskStatusArray[x].pcTaskName, argv[1]) == 0) {
            taskToKill = taskStatusArray[x].xHandle;
            break;
        }
    }

    // 如果找到了任务，删除它
    if (taskToKill != NULL) {
        vTaskDelete(taskToKill);
        printf("Task '%s' has been killed.\n", argv[1]);
    } else {
        printf("Task '%s' not found.\n", argv[1]);
    }

    return 0;
}

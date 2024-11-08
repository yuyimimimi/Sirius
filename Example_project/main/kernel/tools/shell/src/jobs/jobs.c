#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <stdio.h>


int jobs_cmd(int argc, char **argv) 
{
    static char pcWriteBuffer[1024] = {0};
    TaskStatus_t taskStatusArray[10];  
    UBaseType_t taskCount, x;

    taskCount = uxTaskGetSystemState(taskStatusArray, 10, NULL);

    printf("Name               State        Priority     Stack      Num   Core\n");
    for (x = 0; x < taskCount; x++) {
        printf("%-18s %-12s %-12u %-10lu %-5u %u\n", 
               taskStatusArray[x].pcTaskName, 
               (taskStatusArray[x].eCurrentState == eRunning) ? "Running" : 
               (taskStatusArray[x].eCurrentState == eReady) ? "Ready" : 
               (taskStatusArray[x].eCurrentState == eBlocked) ? "Blocked" : "Suspended",
               taskStatusArray[x].uxCurrentPriority, 
               taskStatusArray[x].usStackHighWaterMark, 
               taskStatusArray[x].xTaskNumber, 
               taskStatusArray[x].xCoreID);  // 如果你的 FreeRTOS 版本支持 xCoreID
    }

    return 0;
}

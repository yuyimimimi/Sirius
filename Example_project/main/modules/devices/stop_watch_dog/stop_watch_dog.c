#include "esp_task_wdt.h"

void stop_watch_dog() {
    esp_task_wdt_delete(NULL);
}
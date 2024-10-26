#include <stdio.h>
#include <lwip/sockets.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <unistd.h>
int TEST_APP_LED(int argc, char *argv[])
{
    int times;
    if(argc > 1){
        times = atoi(argv[1]);
    }
    else{
        times = 1;
    }
    char *led_dev_name = "/dev/led-1";
    int led_file = open(led_dev_name, O_RDWR);
    if (led_file < 0){
        perror("led_open_failed");
    }    
    else{      
        while(times--){
         write(led_file,"1",1);
         usleep(300000);
         write(led_file,"0",1);
         usleep(300000);
         }
    }
    close(led_file);
    return 0;
}
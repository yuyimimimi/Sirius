#include <stdio.h>
#include <linux/i2c-dev.h>
#include <lwip/sockets.h>

int select_i2c_device(char *path,int addr);
int do_i2cdetect_cmd(int argc, char **argv)
{
    int cmd_of_y = 0;
    // int cmd_of_r = 0;
    // int cmd_of_a = 0;

    char *args = NULL;
      //解析命令行参数
    for(int i = 1; i < argc; i++)                     //遍历命令行参数
    {
        args = argv[i];
        if( args[0] == '-'){         //如果有命令  
            for(int j = 1; args[j]!= '\0'; j++){
                if(args[j] == 'y'){
                    cmd_of_y = 1;
                }
                // else if(args[j] == 'a'){
                //     cmd_of_a = 1;
                // }
                // else if(args[j] == 'r'){
                //     cmd_of_r = 1;
                // }
            }
        }
        else
        {
            if( args == NULL){
                args = argv[i];
            }
        }
    }

    if(args == NULL)
    {
        printf("Usage: i2cdetect [bus_number]\r\n");
        return -1;
    }

    int busnumber = atoi(args);
    char* path ;



    switch(busnumber)
    {
        case 1:
            path = "/dev/i2c-1";
            break;
        case 2:
            path = "/dev/i2c-2";
            break;
        case 3:
            path = "/dev/i2c-3";
            break;
        case 4:
            path = "/dev/i2c-4";
            break;
        default:
            printf("Error: Invalid bus number\r\n");
            return -1;
    }
    if(cmd_of_y == 1)
    {
       select_i2c_device(path,0x00);
    }

    
    return 0;
}



int select_i2c_device(char *path,int addr)
{   
    int fp = open(path, O_RDWR);     
    if (fp < 0) {
        printf("Error: cannot open %s\r\n", path);    
        return -1;
    }
    if(addr == 0x00)
    {
        printf("     0  1  2  3  4  5  6  7  8  9  a  b  c  d  e  f\r");
        int addr = 0x00;
        for(int i=0; i<8; i++)
        {
            printf("\r\n %02x: ",i);
            for(int j=0; j<16; j++)
            {
                if(i==0 && j == 0) {j=3;printf("         ");}
                if(i==7 && j == 8) break;
                addr = i*16 + j;
                ioctl(fp, I2C_SLAVE, (addr << 1));
                if(-EIO == write(fp,"1",1))
                {
                    printf("\033[36m");  
                    printf("-- ");
                    printf("\033[37m"); 
                }
                else 
                    printf("UU ");  
            }
        }
    }
    else
    {
        ioctl(fp, I2C_SLAVE, addr);
         if(-EIO == write(fp, "1", 1))
         printf("Device not found\r\n");
         else 
         printf("Device found at address 0x%02x\r\n", addr);
    }
    printf("\r\n");
    close(fp);
    return 0;
}




 #include "app_install.h"
void add_i2cdetect_console_app(void)
{
    char * help_msg = "i2cdetect [-y] [bus_number]\r\n";
    add_console_app("i2cdetect", do_i2cdetect_cmd, help_msg );
}


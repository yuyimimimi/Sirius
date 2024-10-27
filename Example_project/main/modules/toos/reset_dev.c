#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>

int reset_dev(int argc, char *argv[])
{
    printf("reset device\n");
    printf("this command will reset your device, all settings will be lost\n");
    printf("are you sure to reset the device? (y/n)\n");
    char c = getchar();
    if (c == 'n' || c == 'N') {
        printf("\n");
        return 0;
    }
    else 
    {
        mkdir("/etc/system", 0755);
        mkdir("/etc/system/data", 0755);
        mkdir("/etc/boot", 0755);

        printf("resetting device...\n");

        char *profile_data = " PATH = :\n\
[boot]\n\
 DTS_PATH       = /etc/boot/dev.dts\n\
[system_data]\n\
 username       = user\n\
 sysname        = SiriuOS\n\
 HOME           = /etc\n\
 system_data    = /etc/system/data\n\
 system_home    = /etc/system\n\
BOOTLOGO       = %system_data%/bootlogo.dat\n\
SYSTEM_VERSION = %system_data%/system_version.dat\n\
[shell]\n\
shell_home     = %system_home%/console.history\n\
 REGISTRY_PATH  = /etc/system\n\
";

        FILE *fp = fopen("/etc/profile", "w");
        if (fp == NULL) {
            printf("open file /etc/profile failed\n");
            return -1;
        }
        fwrite(profile_data, strlen(profile_data), 1, fp);
        fclose(fp);



char *dev_dts_data = "\
gpio_dev = {\n\
    gpio-controller = {\n\
        reg = <193>;\n\
        ngpios = <18>;\n\
        compatible = \"gpioexport\";\n\
    };\n\
};\n";

        FILE *fp2 = fopen("/etc/boot/dev.dts", "w");
        if (fp2 == NULL) {
            printf("open file /etc/boot/dev.dts failed\n");
            return -1;
        }
        fwrite(dev_dts_data, strlen(dev_dts_data), 1, fp2);
        fclose(fp2);

char *bootlogo_data = "\
  __\n"
  "  \\  \\    --------\n"
  "   \\  \\\n"
  "    \\  \\_________\n"
  "     \\ X _________\\\n"
  "     /  /\n"
  "   /  /       ---------\n"
  " /  /    ---------\n"
  " ---\n";

    FILE *fp3 = fopen("/etc/system/data/bootlogo.dat", "w");
    if (fp3 == NULL) {
        printf("open file /etc/system/data/bootlogo.dat failed\n");
        return -1;
    }
    fwrite(bootlogo_data, strlen(bootlogo_data), 1, fp3);
    fclose(fp3);

char *system_version_data = "Sirius 0.1.0\n";

    FILE *fp4 = fopen("/etc/system/data/system_version.dat", "w");
    if (fp4 == NULL) {
        printf("open file /etc/system/data/system_version.dat failed\n");
        return -1;
    }
    fwrite(system_version_data, strlen(system_version_data), 1, fp4);
    fclose(fp4);
    printf("reset device success!\n");
    sleep(1);
    printf("system will restart after many seconds...");
    sleep(5);
    exit(0);

    return 0;
    }  
}


#include "app_install.h"
void dev_reset_app_install()
{
    add_console_app("reset_device", reset_dev,"reset your device");
}
    

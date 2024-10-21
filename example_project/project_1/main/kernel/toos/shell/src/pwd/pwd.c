#include <stdio.h>
#include <console_cop.h>
int pwd_cmd(int argc, char **argv) 
{
    char *pwd;
    pwd =get_console_path();
    printf("%s\n", pwd);
    return 0;
}
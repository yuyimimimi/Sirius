#include <stdio.h>
int  clear_cmd(int argc, char **argv) 
{
    printf("\033[2J\033[H"); // clear screen (2J) and move cursor to top left corner (H)
    return 0;
}
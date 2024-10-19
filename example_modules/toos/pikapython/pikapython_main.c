#include "pikascript.h"
#include "stdio.h"
#include "env.h"
#include <console_cop.h>
#include "pikaVM.h"  // 需要根据实际头文件名称进行调整
#include "freeRTOS/FreeRTOS.h"
#include "freeRTOS/task.h"
#include <unistd.h>
#include "PikaMain.h"
#include <sys/stat.h>



char __platform_getchar(void){
    char buffer[1] = {0};
    buffer[0] = getchar();
    return buffer[0];
}
void pika_platform_sleep_ms(uint32_t ms){
    usleep(ms * 1000);
}
FILE* __platform_fopen(const char* filename, const char* modes){
    return fopen(filename, modes);
}
int __platform_fclose(FILE* stream){
    return fclose(stream);
}
size_t __platform_fwrite(const void* ptr,size_t size,size_t n,FILE* stream){
    return fwrite(ptr,size,n,stream);
}
size_t __platform_fread(void* ptr, size_t size,size_t n,FILE* stream){
    return fread(ptr,size,n,stream);
}
int __platform_fseek(FILE* stream, long offset, int whence){
    return fseek(stream, offset, whence);
}
long pika_platform_ftell(FILE* stream){
    return ftell(stream);
}





static struct input_data_t{
    int cmd_of_b ;
    int cmd_of_B ;
    int cmd_of_c ;
    int cmd_of_d ;
    int cmd_of_E ;
    int cmd_of_h ;
    int cmd_of_i ;
    int cmd_of_I ;
    int cmd_of_m ;
    int cmd_of_O ;
    int cmd_of_OO ;
    int cmd_of_q ;
    int cmd_of_s ;
    int cmd_of_S ;
    int cmd_of_u ;
    int cmd_of_v ;
    int cmd_of_V ;
    int cmd_of_W ;
    int cmd_of_x ;
    int cmd_of_X ;
    char *path;
    char *path1;
};

static int mymakdir()
{
    int needfree = 0;
    char *dirname = "pikascript-api";

    char *this_path = get_console_path();
    char *new_path = malloc(strlen(this_path) + strlen(dirname) + 2);
    strcpy(new_path, this_path);
    strcat(new_path, "/");
    strcat(new_path, dirname);

    struct stat statbuf;
    if (stat(new_path, &statbuf) != 0)      // 判断路径是否存在
    {
        mkdir(new_path, 0777);
    }
    free(new_path);
    return 0;
}



static int init_done = 0;
static PikaObj* pikaMain;
static void pikaMain_init(){
    if(init_done == 0){
        pikaMain = pikaScriptInit();
        init_done = 1;
    }
}
static void pikarun(void *arg);
static int pikapython_main(int argc, char **argv)
{
    struct input_data_t input_data;
    input_data.path = NULL;
    
    int need_free_path =0;
    for(int i = 1; i < argc; i++){                              //指令参数处理
        char* args = argv[i];
        if( args[0] == '-'){         //如果有命令  
             for(int j = 1; args[j]!= '\0'; j++){
                if(args[j] == 'b'){
                    input_data.cmd_of_b = 1;
                }
                else if(args[j] == 'B'){
                    input_data.cmd_of_B = 1;
                }
                else if(args[j] == 'c'){
                    input_data.cmd_of_c = 1;
                }
                else if(args[j] == 'd'){
                    input_data.cmd_of_d = 1;
                }
                else if(args[j] == 'E'){
                    input_data.cmd_of_E = 1;
                }
                else if(args[j] == 'h' || args[j] == '?'){
                    input_data.cmd_of_h = 1;
                }
                else if(args[j] == 'i'){
                    input_data.cmd_of_i = 1;
                }
                else if(args[j] == 'I'){
                    input_data.cmd_of_I = 1;
                }
                else if(args[j] =='m'){
                    input_data.cmd_of_m = 1;
                }
                else if(args[j] == 'O'){
                    input_data.cmd_of_O = 1;
                }
                else if(args[j] == 'q'){
                    input_data.cmd_of_q = 1;
                }
                else if(args[j] =='s'){
                    input_data.cmd_of_s = 1;
                }
                else if(args[j] == 'S'){
                    input_data.cmd_of_S = 1;
                }
                else if(args[j] == 'u'){
                    input_data.cmd_of_u = 1;
                }
                else if(args[j] == 'v'){
                    input_data.cmd_of_v = 1;
                }
                else if(args[j] == 'V'){
                    input_data.cmd_of_V = 1;
                }
                else if(args[j] == 'W'){
                     input_data.cmd_of_W = 1;
                }
                else if(args[j] == 'x'){
                     input_data.cmd_of_x = 1;
                }
                else if(args[j] == 'X'){
                     input_data.cmd_of_X = 1;
                }
            }
        }
        else
        {
            if(input_data.path == NULL){
                input_data.path = argv[i];
            }
        }
    }


    char *console_path = get_console_path();   
    if(input_data.path != NULL)                              //获取输入文件的绝对路径                     
    {
        if(input_data.path[0] != '/')
        {
            char *new_path = malloc(strlen(input_data.path) + strlen(console_path) + 2);
            strcpy(new_path, console_path);
            new_path[strlen(console_path)] = '/';
            strcpy(new_path + strlen(console_path) + 1, input_data.path);
            new_path[strlen(console_path) + strlen(input_data.path) + 1] = '\0';
            need_free_path = 1;
            input_data.path = new_path;
        }
    }

    input_data.path1 = getenv_("PYTHON_HOME");            //环境变量路径



    if(input_data.cmd_of_v == 1 || input_data.cmd_of_V == 1)    //只进行初始化，不进行运行打印版本信息
    {
        pika_printVersion();
    } 
    else if(input_data.path == NULL)                                  //没有输入文件，直接初始化
    {  
        pika_printVersion();
        printf("Type 'help', 'copyright', 'credits' or 'license' for more information.\n");
        pikaScriptShell(pikaMain);
      
    }
    else if(input_data.path != NULL)
    {
        mymakdir();
        VMParameters *vm_params = pikaVM_runFile(pikaMain, input_data.path);
    }

    if(need_free_path == 1){
        free(input_data.path);
    }
    return 0;
}




#include "app_install.h"
void add_pikapython_console_app(void)
{
   printf("python: version: pikapython");
   pikaMain_init();
   char *help = "usage: python [option] ... [-c cmd | -m mod | file | -] [arg] ...";
   add_console_app("python", pikapython_main, help);
}

#include <stdio.h>
#include <string.h>
#include "esp_system.h"
#include "esp_log.h"
#include "esp_console.h"
#include "esp_vfs_dev.h"
#include "esp_vfs_fat.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "linenoise/linenoise.h"
#include <linux/slab.h>
#include <sys/stat.h>
#include <stdarg.h> 
#include <linux/vfs/vfs.h>
#include "env.h"
#include <kernelconfig>

static char *console_path;
static int home_start = 1;


static void console_init(void *arg);
char *get_console_path();
void start_console(){ vTaskDelay(50);home_start = 0;}
void esp_console_hook_run(char *(*func)());


void init_normal_console(void)
{    
    char * home = getenv_("HOME");
    if(home == NULL){
        home = "/etc";
        setenv_("HOME",home,1);
        console_path = (char*)malloc(1024);
        strcpy(console_path,home);    
        xTaskCreate(console_init, "console_init", 1024*8, NULL, 7 , NULL);    
    }
    else{
        console_path = (char*)malloc(1024);
        strcpy(console_path,home);
        free(home);      
        xTaskCreate(console_init, "console_init", 1024*8, NULL, 7 , NULL);        
    }
}



void console_init_recovery_mode(void *arg)
{
    while (home_start == 1){vTaskDelay(1);}
    char* home = "/etc";
    console_path = (char*)malloc(1024);
    strcpy(console_path,home);    
    printf("\n\n");
    //printf("\033[2J\033[H");
    printf("\033[35m\n\n"); 
    printf("%60s","Sirius 9/09/2024\n");
    printf("%60s","Recovery boot mode\n");
    printf("%60s","Please gave me a star on GitHub: https://github.com/yuyimimimi/Sirius\n\n");
    printf("\033[35m"); 
    printf("\033[34m"); 
    printf("you can use 'reboot' command to make system next boot in normal mode\n");
    printf("if you want boot recovery mode again, please press reset button\n");
    printf("\033[37m");
    esp_console_repl_t *repl = NULL;
    esp_console_repl_config_t repl_config = ESP_CONSOLE_REPL_CONFIG_DEFAULT();
    repl_config.prompt =" ";  
    esp_console_dev_uart_config_t hw_config = ESP_CONSOLE_DEV_UART_CONFIG_DEFAULT();
    repl_config.max_cmdline_length = 1024*16;
    repl_config.history_save_path = "/etc/sonsole.hist.reco";  
    esp_console_register_help_command();                                                          
    ESP_ERROR_CHECK(esp_console_new_repl_uart(&hw_config, &repl_config, &repl));
    ESP_ERROR_CHECK(esp_console_start_repl(repl));  
    vTaskDelete(NULL);   
}

void init_console_recovery_mode(void)
{
    xTaskCreate(console_init_recovery_mode, "console_init", 1024*4, NULL, 7 , NULL);  
}



static char *printf_data;
char *print_prompt()
{  
    char *color_for_name = "\033[32m";
    char *username = getenv_("username"); 
    if(username == NULL){
        username = "user";
        setenv_("username",username,1);
    }
    char *sysname  = getenv_("sysname");
    if(sysname == NULL){
        sysname = "yuii";
        setenv_("sysname",sysname,1);
    }
    char *color_for_prompt = "\033[36m";
    char *printpath = get_console_path();
    char *color_of_foot = "\033[37m";
    char *footer = "~$:";
    strcpy(printf_data, color_for_name);
    strcpy(printf_data + strlen(printf_data), username);
    strcpy(printf_data + strlen(printf_data), "@");
    strcpy(printf_data + strlen(printf_data), sysname);
    strcpy(printf_data + strlen(printf_data), ":");
    strcpy(printf_data + strlen(printf_data), color_for_prompt);
    strcpy(printf_data + strlen(printf_data), printpath);
    strcpy(printf_data + strlen(printf_data), color_of_foot);
    strcpy(printf_data + strlen(printf_data), footer);
    free(username);
    free(sysname);
    return printf_data;
}


static void console_init(void *arg){

    while (home_start == 1){vTaskDelay(1);}
    printf_data = (char*)malloc(1024);
    esp_console_hook_run(print_prompt);

  
    char *bootlogo;
    FILE *fp ;
    char *file_path = getenv_("BOOTLOGO");
    if(file_path != NULL){
        printf("\033[2J\033[H\n\n\n");
        fp = fopen(file_path, "r");
        if(fp != NULL)
        {
            fseek(fp, 0, SEEK_END);
            long file_size = ftell(fp);
            fseek(fp, 0, SEEK_SET);
            bootlogo = (char*)malloc(file_size + 1);
            fread(bootlogo, 1, 1024, fp);
            bootlogo[file_size] = '\0';
            fclose(fp);
            printf("%s", bootlogo);   
            free(bootlogo);
        }
        free(file_path);
    }
    else{
        setenv_("BOOTLOGO","/please/set/in/there",1);
    }

    file_path = getenv_("SYSTEM_VERSION");
    if(file_path != NULL)
    {
        fp = fopen(file_path, "r");
        if(fp != NULL)
        {
            fseek(fp, 0, SEEK_END);
            long file_size = ftell(fp);
            fseek(fp, 0, SEEK_SET);
            bootlogo = (char*)malloc(file_size + 1);
            fread(bootlogo, 1, 1024, fp);
            bootlogo[file_size] = '\0';
            fclose(fp);
            printf("%60s", bootlogo);    
            free(bootlogo);
        }
        free(file_path);
    }
    else{
        setenv_("SYSTEM_VERSION","/please/set/in/there",1);
    }

    printf("%60s","09/09/2024\n");
    printf("%60s","GitHub: https://github.com/yuyimimimi/Sirius\n");
    file_path = getenv_("shell_home");
    esp_console_repl_t *repl = NULL;
    esp_console_repl_config_t repl_config = ESP_CONSOLE_REPL_CONFIG_DEFAULT();
    repl_config.prompt =" ";  
    esp_console_dev_uart_config_t hw_config = ESP_CONSOLE_DEV_UART_CONFIG_DEFAULT();
    repl_config.max_cmdline_length = console_mem ;
    if(file_path != NULL)
    {   
        repl_config.history_save_path = file_path;  
        esp_console_register_help_command();                                                          
        ESP_ERROR_CHECK(esp_console_new_repl_uart(&hw_config, &repl_config, &repl));
        ESP_ERROR_CHECK(esp_console_start_repl(repl));  
    }
    else
    {
        file_path = "/etc/shell.dat";
        setenv_("shell_home",file_path,1);
        repl_config.history_save_path = file_path;  
        esp_console_register_help_command();                                                          
        ESP_ERROR_CHECK(esp_console_new_repl_uart(&hw_config, &repl_config, &repl));
        ESP_ERROR_CHECK(esp_console_start_repl(repl));
    }    
    vTaskDelete(NULL) ;   
}



void add_console_app(char* name , esp_console_cmd_func_t func, char* help,...)
{
    char buffer[8192]; 
    va_list args;
    va_start(args, help);
    vsnprintf(buffer, sizeof(buffer), help, args);
    va_end(args);
    help = buffer;

    int length = strlen(help);
    char * new_help = (char*)malloc(length + 1);
    strcpy(new_help, help);
    new_help[length] = '\0';
    help = new_help;

    esp_console_cmd_t cmd = {
        .command = name,
        .help = help,
        .func = func,
    };
    esp_err_t err = esp_console_cmd_register(&cmd);
    if (err != ESP_OK) {
        printf("Failed to register%s",name);
    }
}


char *get_console_path(){
   return console_path;
}

void set_console_path(const char* path)
{
    if (console_path != NULL) {
        strncpy(console_path, path, 1024 - 1);
        console_path[1024 - 1] = '\0'; 
    }
}


char *get_console_file_prompt(char *file_path)
{
    char *new_path;
    if(file_path[0] != '/')
    {
        new_path = malloc(strlen(file_path) + strlen(console_path) + 2);
        strcpy(new_path, console_path);
        new_path[strlen(console_path)] = '/';
        strcpy(new_path + strlen(console_path) + 1, file_path);
        new_path[strlen(console_path) + strlen(file_path) + 1] = '\0';
        return new_path;
    }
    else
    {
        new_path = malloc(strlen(file_path) + 1);
        strcpy(new_path, file_path);
        new_path[strlen(file_path)] = '\0';
        return new_path;
    }
}


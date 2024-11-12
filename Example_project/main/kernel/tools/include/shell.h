 #ifndef _SHELL_TOOS_H_
 #define _SHELL_TOOS_H_
 #include <linux/init.h>
 #include <esp_console/console.h>


    int  cat_main(int arg,char **argv);
    int  echo_main(int arg,char ** argv);
    int  reboot_main(int argc, char **argv);
    int  ls_main(int arg,char **argv);
    int  clear_cmd(int argc, char **argv);
    int  pwd_cmd(int argc, char **argv);
    int  cd_cmd(int argc, char **argv);
    int  mkdir_cmd(int argc,char **argv);
    int  history_cmd(int argc, char **argv);
    int  uname_cmd(int argc, char **argv);
    int  rm_cmd(int argc, char **argv);
    int  rmdir_cmd(int argc, char **argv);
    int  free_cmd(int argv,char **argc);
    int  kilo_main(int argc, char **argv); 
    int  reset_dev(int argc, char **argv);
    int touch_cmd(int argc, char *argv[]);
    int jobs_cmd(int argc, char **argv);
    int kill_cmd(int argc, char **argv);

    int uptime(int argc, char *argv[]);
    int stat_command(int argc, char *argv[]);
    int sleep_command(int argc, char **argv);
    int printf_command(int argc, char *argv[]);
    int mv_command(int argc, char *argv[]);
    int cp_command(int argc, char *argv[]);
    int head_command(int argc, char *argv[]);
    int tail_command(int argc, char *argv[]);
    int date_command(int argc, char *argv[]);
    int whoami_command(int argc, char *argv[]);
    int run_script(int argc, char *argv[]);

    int getenv_command(int argc, char *argv[]);
    int setenv_command(int argc, char *argv[]);
    int unsetenv_command(int argc, char *argv[]);
    int env_command(int argc, char* argv[]);
    int dmesg(int argc, char **argv);

void __init shell_cmd_init(void) {
    // 命令格式: 命令 [选项] [参数]
    add_console_app("echo", echo_main, "echo [args]... - Write arguments to the standard output");
    add_console_app("cat", cat_main, "cat [path] - Display the contents of a file");
    add_console_app("reboot", reboot_main, "reboot - Reboot the system");
    add_console_app("ls", ls_main, "ls [path] [-l] [-a] [-R] [-d] - List directory contents");
    add_console_app("clear", clear_cmd, "clear - Clear the screen");
    add_console_app("pwd", pwd_cmd, "pwd - Print the name of the current working directory");
    add_console_app("cd", cd_cmd, "cd [path] - Change the current working directory");
    add_console_app("mkdir", mkdir_cmd, "mkdir [path] - Create a new directory");
    add_console_app("history", history_cmd, "history - Show the command history");
    add_console_app("uname", uname_cmd, "uname - Print system information");
    add_console_app("rm", rm_cmd, "rm [path] - Remove a file");
    add_console_app("rmdir", rmdir_cmd, "rmdir [path] - Remove an empty directory");
    add_console_app("free", free_cmd, "free - Display free and used memory");
    add_console_app("kilo", kilo_main, "kilo - File editor");
    add_console_app("vi", kilo_main, "vi - File editor");
    add_console_app("touch", touch_cmd, "touch [filename] - Create a new file");
    add_console_app("jobs", jobs_cmd, "jobs - List running tasks");
    add_console_app("ps", jobs_cmd, "ps - List running tasks");
    add_console_app("kill", kill_cmd, "kill [pid] - Kill a running task by its process ID");
    add_console_app("uptime", uptime, "uptime - Show system uptime");
    add_console_app("stat", stat_command, "stat [file] - Display file or file system status");
    add_console_app("sleep", sleep_command, "sleep [seconds] - Sleep for a specified number of seconds");
    add_console_app("printf", printf_command, "printf [format]... - Print formatted output");
    add_console_app("mv", mv_command, "mv [source] [destination] - Move or rename a file or directory");
    add_console_app("cp", cp_command, "cp [source] [destination] - Copy a file or directory");
    add_console_app("head", head_command, "head [file] - Output the first part of a file");
    add_console_app("tail", tail_command, "tail [file] - Output the last part of a file");
    add_console_app("date", date_command, "date [-u] [MMDDhhmm[[CC]YY][.ss]] - Display or set the system date and time");
    add_console_app("whoami", whoami_command, "whoami - Print the current user name");
    add_console_app("./", run_script, "run_script [script] - Run a shell script");
    add_console_app("sh", run_script, "sh [script] - Run a shell script");
    add_console_app("printenv", getenv_command, "printenv [variable] - Print the value of an environment variable");
    add_console_app("export", setenv_command, "export [variable=value] - Set an environment variable");
    add_console_app("unset", unsetenv_command, "unset [variable] - Remove an environment variable");
    add_console_app("env", env_command, "env - Display all environment variables");
    add_console_app("dmesg", dmesg, "dmesg - Display kernel messages");
}



   void __init recovery_mode_shell_cmd_init(void)
   {
    add_console_app("echo",echo_main,"Write arguments to the standard output");
    add_console_app("cat",cat_main,"print the contents of a file to the standard output");
    add_console_app("reboot",reboot_main,"reboot the system");
    add_console_app("ls",ls_main,"list directory contents");
    add_console_app("clear",clear_cmd,"clear the screen");
    add_console_app("pwd",pwd_cmd,"print the name of the current working directory");
    add_console_app("cd",cd_cmd,"change the current working directory");
    add_console_app("mkdir",mkdir_cmd,"create a new directory");
    add_console_app("rm",rm_cmd,"remove a file");
    add_console_app("rmdir",rmdir_cmd,"remove an empty directory");
    add_console_app("free",free_cmd,"display free and used memory"); 
    add_console_app("kilo",kilo_main,"file editor");
    add_console_app("vi",kilo_main,"file editor");
    add_console_app("reset_device",reset_dev,"reset device");
    add_console_app("touch",touch_cmd,"create a new file");
    add_console_app("jobs",jobs_cmd,"list running Tasks");
    add_console_app("kill",kill_cmd,"kill a running Task");
    add_console_app("uptime",uptime,"show system uptime");
    add_console_app("stat",stat_command,"display file or file system status");
    add_console_app("sleep",sleep_command,"sleep for a specified number of seconds");
    add_console_app("printf",printf_command,"print formatted output");
    add_console_app("mv",mv_command,"move or rename a file or directory");
    add_console_app("cp",cp_command,"copy a file or directory");
    add_console_app("head",head_command,"output the first part of a file");
    add_console_app("tail",tail_command,"output the last part of a file");
    add_console_app("date",date_command,"display or set the system date and time");
    add_console_app("./",run_script,"run a script");
    add_console_app("getenv", getenv_command, "getenv <variable_name> - print the value of an environment variable");
    add_console_app("setenv", setenv_command, "setenv <variable_name> <value> - set an environment variable");
    add_console_app("unsetenv", unsetenv_command, "unsetenv <variable_name> - remove an environment variable");
   }
#endif

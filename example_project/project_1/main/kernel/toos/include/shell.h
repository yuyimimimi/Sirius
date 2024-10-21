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
    int  helloworld(int argc, char *argv[]);
    int  kilo_main(int argc, char **argv); 
    int  reset_dev(int argc, char **argv);

   void __init shell_cmd_init(void)
   {
    add_console_app("helloworld",helloworld,"print 'hello world'");
    add_console_app("echo",echo_main,"Write arguments to the standard output");
    add_console_app("cat",cat_main,"print the contents of a file to the standard output");
    add_console_app("reboot",reboot_main,"reboot the system");
    add_console_app("ls",ls_main,"list directory contents");
    add_console_app("clear",clear_cmd,"clear the screen");
    add_console_app("pwd",pwd_cmd,"print the name of the current working directory");
    add_console_app("cd",cd_cmd,"change the current working directory");
    add_console_app("mkdir",mkdir_cmd,"create a new directory");
    add_console_app("history",history_cmd,"show command history");
    add_console_app("uname",uname_cmd,"print system information");
    add_console_app("rm",rm_cmd,"remove a file");
    add_console_app("rmdir",rmdir_cmd,"remove an empty directory");
    add_console_app("free",free_cmd,"display free and used memory"); 
    add_console_app("kilo",kilo_main,"file editor");
    add_console_app("vi",kilo_main,"file editor");
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
   }
#endif

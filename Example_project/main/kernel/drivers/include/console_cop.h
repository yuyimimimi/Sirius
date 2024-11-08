#define __CAT_H__
#ifdef  __CAT_H__    
    /* Function to get the console path */
    char *get_console_path();
    void set_console_path(const char* path);
    char *get_file_path(char *file_path);             //输入文件路径，返回绝对路径，需要释放内存

#endif

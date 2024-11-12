#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <console_cop.h>


//控制流规则：

//-1:警告
// 1:退出递归
// 0:继续递归
// 2:错误并继续执行
// 3:正确并继续执行

#define debug(fmt, args...) printf(fmt, ##args)

/*
 *
 * 变量栈结构：
 * 
*/


#define MAX_VAR_NAME_LEN 32
#define MAX_VAR_VALUE_LEN 64
#define MAX_TASK_LEN 64

//脚本的栈结构
static struct var_info {
    char    name [MAX_VAR_NAME_LEN];
    char    value[MAX_VAR_VALUE_LEN];
    int     value_i;
    double  value_d;
    uint8_t value_t;
    int  level;       
};


static struct var_info_stack
{
    struct var_info var_info[MAX_TASK_LEN];
    int top;         
    int leave_flag;    
    int line_num;    

    int AX;           
    int BX;                 
    int SI;         
};

static void init_var_stack(struct var_info_stack *stack) {
    stack->top = 1;
    stack->leave_flag = 0;
    stack->line_num = 1;
}







static int run_shell_of_line(struct var_info_stack *stack,char *data, int i);
static int skip_value(struct var_info_stack *stack,char *file_data, int *i,char *value);

//原子性操作：
static int print_error(char *file_data, int *i) {                                                                             // 打印错误信息
    printf("Error: syntax error\n");
    char err_line[128];
    int k = 0;
    while (file_data[*i] != '\n' && file_data[*i] != '\r' && file_data[*i] != '\0') {
        err_line[k] = file_data[*i];
        k++;
        (*i)++;
    }
    err_line[k] = '\0';
    printf("Error line: (%s)\n", err_line);
    printf("~~~~~~~~~~/\\~~~~~~~~~~\n");
    printf("please check the script file\n");
    return 1;
}



static int skip_comment(char *file_data, int *i) {                                                                            // 跳过注释直到行尾
    if(file_data[*i] == '#')
    {
        while (file_data[*i] != '\n' && file_data[*i] != '\r' && file_data[*i] != '\0') {
            (*i)++;
            if(file_data[*i] == '\0'){
                return 1;
            }
        }        
    }
    return 0;
} 



static int skip_space(char *file_data, int *i) {                                                                               //跳过空格换行符等
    while (file_data[*i] ==' ' || file_data[*i] == '\t' || file_data[*i] == '\n' || file_data[*i] == '\r'||file_data[*i] == '#') {
        if( skip_comment(file_data, i) == 1) {
            return 1;
        }
        (*i)++;
        if(file_data[*i] == '\0'){
            return 1;
        }
    }
    return 0;
}




static int get_value(char *file_data, int *i,char *value) {                                                                    //获取下一个值
    int j = 0;
    int value_len = strlen(value);
    
    if(value_len > 64) {
        return 1;
    }

    while (file_data[*i] == ' ') {
        (*i)++;
    }
    while (file_data[*i] != '\n' && file_data[*i] != '\r' && file_data[*i] != '\0' && file_data[*i] != ';'&& file_data[*i] != ' ')
    {
        value[j] = file_data[*i];
        j++;
        (*i)++;
    }
    value[j] = '\0';
    return 0;
}





static int run_command(char *file_data, int *i)                                                                                //执行一行命令
{

    char cmdline[256];
    int j = 0;
    while (file_data[*i] != '\n' && file_data[*i] != '\0' && file_data[*i] != ';')
    {
        cmdline[j] = file_data[*i];
        j++;
        (*i)++;
    }
    cmdline[j] = '\0';

    if(system(cmdline) != 0)
    {
        return -1;
    }
    if(file_data[*i] == '\0')
    {
        return 1;
    }
    return 0;
}







//进入新递归后，更新leave_flag
static void enter_new_scope(struct var_info_stack *stack) {
   stack->leave_flag++;
}
//退出递归后，删除当前作用域的变量，并更新leave_flag并释放空间
void leave_scope(struct var_info_stack *stack) {
    while(stack->var_info[stack->top].level == stack->leave_flag) {
        stack->top--;
        if(stack->top < 0){
            printf("Error: Variable stack underflow.\n");
            return;
        }
    }
    stack->leave_flag--;
}

//压入变量
static int push_variable(struct var_info_stack *stack, const char *name, const char *value) {       
    int name_length = strlen(name);

    if(name_length > MAX_VAR_NAME_LEN-1) {
        printf("Error:line: (%d) Variable name too long.\n", stack->line_num);
        return 1;
    }
    int value_length = strlen(value);
    if(value_length > MAX_VAR_VALUE_LEN-1) {
        printf("Error:line: (%d) Variable value too long.\n", stack->line_num);
        return 1;
    }
    if (stack->top >= MAX_TASK_LEN-1) {
        printf("Error:line: (%d) Variable stack overflow.\n", stack->line_num);
        return 1;
    }

    stack->top++;
    struct var_info *var = &stack->var_info[stack->top];
    snprintf(var->name, sizeof(var->name), "%s", name);
    snprintf(var->value, sizeof(var->value), "%s", value);
    var->level = stack->leave_flag;  // 设置变量的作用域层级
    return 0;
}

//获取变量值
static int get_variable(struct var_info_stack *stack, const char *name, char *value) {
    int i;
    for(i = stack->top; i >= 0; i--) {
        if(strcmp(stack->var_info[i].name, name) == 0) {
            snprintf(value, MAX_VAR_VALUE_LEN, "%s", stack->var_info[i].value);
            return 0;
        }
    }
    printf("Error line: (%d) variable %s not found.\n", stack->line_num, name);
    return 1;
}

//查询变量是否存在
static int variableselect(struct var_info_stack *stack,char *name)                                                                     //查询变量是否存在
{
    for(int i =0;i<(stack->top);i++){
        if(strcmp(stack->var_info[i].name, name) == 0){
            return 0;
        }
    }
    return 1;
}

// 存储变量
static int store_var(struct var_info_stack *stack,char *file_data, int *i)                                                             // 存储变量
{
    char var_name[128];
    char var_value[128];
    skip_value(stack,file_data, i, "var");                                                                                             //跳过var
    if(get_value(file_data, i, var_name)==1)
    {
        printf("Error:line: (%d) syntax error\n", stack->line_num);
        return 1;
    }
    if(skip_value(stack,file_data, i, "=")==1)                                                                                          //跳过=
    {
        printf("Error:line: (%d) syntax error\n", stack->line_num);
        return 1;
    }
    if(get_value(file_data, i, var_value)==1)                                                                                           //获取变量值
    {
        printf("Error:line: (%d) syntax error\n", stack->line_num);
        return 1;
    }
    if(push_variable(stack, var_name, var_value)==1)                                                                                    //压入变量栈
    {
        return 1;
    }
    return 0;
}

// 更新变量值
static int update_variable(struct var_info_stack *stack, const char *name, const char *new_value) {
    int name_length = strlen(name);
    int value_length = strlen(new_value);

    if (name_length > MAX_VAR_NAME_LEN - 1) {
        printf("Error:line: (%d) Variable name too long.\n", stack->line_num);
        return 1;
    }
    if (value_length > MAX_VAR_VALUE_LEN - 1) {
        printf("Error:line: (%d) Variable value too long.\n", stack->line_num);
        return 1;
    }

    // 从栈顶向下查找变量
    for (int i = stack->top; i >= 0; i--) {
        if (strcmp(stack->var_info[i].name, name) == 0) {
            // 找到变量，更新其值
            snprintf(stack->var_info[i].value, sizeof(stack->var_info[i].value), "%s", new_value);
            return 0;  // 成功更新变量值
        }
    }

    // 未找到变量
    printf("Error:line: (%d) Variable %s not found.\n", stack->line_num, name);
    return 1;
}




/// @brief 跳转到指值后的语句
/// @param stack 
/// @param file_data 
/// @param i 
/// @param value 
/// @return 
static int skip_value(struct var_info_stack *stack, char *file_data, int *i, char *value) {  
    int value_len = strlen(value);
    
    // 遍历文件数据，直到找到指定的值
    while (file_data[*i] != '\0') {  // 确保没有超过文件末尾
        if (strncmp(file_data + *i, value, value_len) == 0) {  // 找到匹配的值
            *i += value_len;  // 跳过找到的值
            return 0;  // 成功跳过
        }

        if (file_data[*i] == '\n') {
            stack->line_num++;  // 遇到换行符，行号加1
        }

        if (file_data[*i] == '\0') {
            return 1;  // 到达文件末尾，没找到值
        }

        (*i)++;  // 向后移动指针
    }
    return 1;  // 没有找到指定值
}


/// @brief 提取脚本直到遇到指定值
/// @param stack 
/// @param file_data 
/// @param i 
/// @param value 
/// @param new_script 
/// @return

static int get_script_until_value(struct var_info_stack *stack, char *file_data, int *i, char *value, char **new_script) {
    int lin_num = stack->line_num;
    int i_copy = *i;
    int j = 0;
    int value_len = strlen(value);

    // 1. 遍历文件直到找到目标值 `value`
    while (strncmp(file_data + *i, value, value_len) != 0) {
        if (file_data[*i] == '\0') {  
            printf("Error: line: (%d) syntax error: reached end of file without finding '%s'\n", lin_num, value);
            return 1;  
        }
        if (file_data[*i] == '\n') {  
            lin_num++;
        }
        j++;  
        (*i)++;  
    }

    if (*i == i_copy || file_data[*i] == ' ' || file_data[*i] == '\t' || file_data[*i] == '\n') {
        // 如果遇到空格、制表符或者换行，填充 "true"
        *new_script = (char *)malloc(5);  // "true"的长度为4 + '\0'结束符
        if (*new_script == NULL) {  
            printf("Error: memory allocation failed\n");
            return 1;
        }
        strcpy(*new_script, "true");  // 填充 "true"
        *i = i_copy;  // 保持指针位置不变
        return 0;  // 成功填充 "true"
    }

    // 3. 如果不为空或空格，正常提取字符直到目标值
    *new_script = (char *)malloc(j + 1);  // 分配内存存储提取的脚本
    if (*new_script == NULL) {  
        printf("Error: memory allocation failed\n");
        return 1;
    }
    strncpy(*new_script, file_data + i_copy, j);  // 复制脚本内容
    (*new_script)[j] = '\0';  // 确保以空字符结尾

    *i = i_copy;  // 恢复原指针位置

    return 0;  // 成功时返回 0
}

/// @brief 获取配对的值之间的脚本
/// @param stack 
/// @param file_data 
/// @param i 
/// @param value1 
/// @param value2 
/// @param new_script 
/// @return 
static int get_script_between_values(struct var_info_stack *stack, char *file_data, int *i, char *value1, char *value2, char **new_script)  //提取配对值之间的脚本
{
    int lin_num = stack->line_num;
    int i_copy = *i;
    int num_of_v1 = 1; // 记录value1出现的次数
    int num_of_v2 = 0; // 记录value2出现的次数
    int length = 0; // 记录脚本长度
    int length_v1 = strlen(value1);
    int length_v2 = strlen(value2);
    while (num_of_v1 != num_of_v2)
    {

        if (file_data[*i] == '\0') {  
            printf("Error: line: (%d) syntax error: reached end of file without finding '%s'\n", lin_num, value1);
            return 1;  
        }
        else if (file_data[*i] == '\n') {  
            lin_num++;
        }
    
        if(strncmp(file_data + *i, value1, length_v1)== 0){
            if(length_v1 < length_v2)                          //如果value1比value2短，则需要判断value1是否和value2在前几个字符中出现
            {
                if(strncmp(file_data + *i, value2, length_v2)!= 0)
                num_of_v1++;
            }     
            else
            {
                num_of_v1++;
            }     
        }
        if(strncmp(file_data + *i, value2, length_v2)== 0){
            if(length_v2 < length_v1)                          //如果value2比value1短，则需要判断value2是否和value1在前几个字符中出现
            {
                if(strncmp(file_data + *i, value1, length_v1)!= 0)
                num_of_v2++;
            }  
            else
            {
                num_of_v2++;
            }
        }
        length++;
        (*i)++;
    }

    length--; // 减去最后一个换,因为此时刚好指向value2的位置

    *new_script = (char *)malloc(length + 1);  // 分配内存存储提取的脚本
    if (*new_script == NULL) {  
        printf("Error: memory allocation failed\n");
        return 1;
    }
    strncpy(*new_script, file_data + i_copy, length);  // 复制脚本内容
    (*new_script)[length] = '\0';  // 确保以空字符结尾

    *i = i_copy + length;  // 恢复原指针位置

    return 0;  // 成功时返回 0
}



/// @brief 执行while语句
/// @param stack 
/// @param file_data 
/// @param i 
/// @return 

static int run_while(struct var_info_stack *stack, char *file_data, int *i) {

   //解析为：while <condition> do <body> done
    char *condition;
    if(get_script_until_value(stack, file_data, i, "do", &condition)== 1)   //获取条件语句
    {
        return 1;
    }

    skip_value(stack,file_data, i, "do");                         //跳过do
    
    char *body;

    if(get_script_between_values(stack, file_data, i,"do" ,"done", &body)==1) //获取循环体语句，要多对do多一个空格从而防止误判
    {
        return 1;
    }

    skip_value(stack,file_data, i, "done");                             //跳过end


    // 解析并执行条件，执行循环体
    while (run_shell_of_line(stack, condition, 0) == 0) {  // 检查条件
        run_shell_of_line(stack, body, 0);                               //循环体内作用域隔离，所以不需要验证返回值
    }
    
    free(body);  // 释放内存
    free(condition);

    return 0;
}



/// @brief 执行if语句
/// @param stack 
/// @param file_data 
/// @param i 
/// @return 

static int run_if(struct var_info_stack *stack,char *file_data, int *i)                                                                        //执行if语句
{
    
    char *condition;
    if(get_script_until_value(stack, file_data, i, "then", &condition)==1)   //获取条件语句
    {
        printf("Error:line: (%d) syntax error\n", stack->line_num);
        return 1;
    }

    skip_value(stack,file_data, i, "then");                         //跳过then

    char *new_script;
    if(get_script_between_values(stack, file_data, i, "then","fi", &new_script)==1)   //获取循环体语句
    {
        return 1;
    }
    skip_value(stack,file_data, i, "fi");                             //跳过fi


    // 解析并执行条件，执行循环体
    if (run_shell_of_line(stack, condition, 0) == 0) {               // 检查条件
        run_shell_of_line(stack, new_script, 0);                    //执行循环体,由于作用域不同，所以不需要验证返回值
    }
    free(new_script);  // 释放内存
    free(condition);
    
    return 0;
}


static int run_var(struct var_info_stack *stack,char *file_data, int *i)                                                                       //执行带运算符的变量赋值语句
{
    char value[128];                              //获取变量名
    get_value(file_data, i, &value);
    skip_value(stack,file_data, i, value);        //跳过变量名
    
    char operator[128];            //获取运算符
    get_value(file_data, i, &operator);
    skip_value(stack,file_data, i, operator);     //跳过运算符
    skip_space(file_data, i);                     //跳过空格

    if(file_data[*i] == '\0'){
        printf("Error:line: (%d) syntax error\n", stack->line_num);
        return 1;
    }

    char var_value[128];                           //获取变量值
    get_script_until_value(stack, file_data, i, "\n", &var_value);
    skip_value(stack,file_data, i, "\n");            //跳过换行符

    return  0;
}
//暂时不提供运算符的变量赋值语句。



static int recognize_keyword(struct var_info_stack *stack,char *file_data, int *i)                                                             //识别关键字
{
    int i_copy = *i;
    char keyword[64];

    if(get_value(file_data, i, keyword)==1){
        printf("Error:line: (%d) syntax error\n", stack->line_num);
        return 1;
    }


    else if (strcmp(keyword,"if") == 0){             
        if(run_if(stack,file_data, i)== 1)
        return 1;
    }
    else if (strcmp(keyword,"while") == 0){             
        if(run_while(stack,file_data, i)== 1)
        return 1;
    }


    else if (strcmp(keyword,"break") == 0){           
        return 1;
    } 

    //变量名识别
    else if (strcmp(keyword,"var") == 0)            
    {
        if(store_var(stack,file_data, i) == 1)
        return 1;
    }

    //常量识别
    else if (strcmp(keyword,"true") == 0)            
    {
        return 2;
    }
    else if (strcmp(keyword,"false") == 0)          
    {
        return 1;
    }

    //变量识别
    // else if(variableselect(stack, keyword) == 0)     //识别被定义的变量
    // {
    //     if(run_var(stack,file_data, i) == 1)
    //     return 1;
    // }
    else 
    {
        *i = i_copy;                                //如果关键字不在关键字列表中，恢复指针位置
        return 3;              
    }
    
    return 0;
}


static int run_shell_of_line(struct var_info_stack *stack,char *data, int i)//线性执行脚本
{

    enter_new_scope(stack);    //进入新作用域
    while (data[i] != '\0')
    {

        skip_space(data, &i);
        
        int value = recognize_keyword(stack, data, &i);

        if (value == 1) {                               //执行错误或返回false
            return 1;            
        }
        else if (value == 2)                            //执行成功并停止执行
        {
            return 0;          
        }
        else if(value == 3)                             //关键字不在关键字列表中
        {
            value = run_command(data, &i);
            if(value == -1)     //指令错误
            {
                return 1;
            }
            else if(value == 1) //运行到末尾退出
            {
                return 0;
            }
        } 
        stack->line_num++;  
    }
    leave_scope(stack);    //退出作用域
    return 0;
}


void script_preprocess(char *file_data,int length) //预处理脚本,在执行前执行,去除注释
{
    for(int i = 0; i < length; i++)
    {
        if(file_data[i] == '#')
        {
            while (file_data[i] != '\n' && file_data[i] != '\0')
            {
                file_data[i] = ' ';
                i++;
            }
        }
    }
}





int run_script(int argc, char *argv[])
{

    if(argc < 2) {
        printf("Usage: run_script <script_file>\n");
        return -1;
    }
    char *script_file = get_file_path(argv[1]);
    if(script_file == NULL) {
        printf("Error: failed to get script file path\n");
        return -1;
    }
 
    char *file_data;
    FILE *fp = fopen(script_file, "r");
    if(fp == NULL) {
        printf("Error: failed to open script file %s\n", script_file);
        return -1;
    }
    fseek(fp, 0, SEEK_END);
    long file_size = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    file_data = (char *)malloc(file_size + 1);
    if(file_data == NULL) {
        printf("Error: memory allocation failed\n");
        return -1;
    }
    
    fread(file_data, 1, file_size, fp);

    file_data[file_size] = '\0';

    fclose(fp);

    struct var_info_stack *var_stack;      //变量栈
    var_stack = (struct var_info_stack *)malloc(sizeof(struct var_info_stack));
    if(var_stack == NULL) {
        printf("Error: memory allocation failed\n");
        return -1;
    }

    script_preprocess(file_data, file_size);  //预处理脚本
    
    init_var_stack(var_stack);            //初始化变量栈

    run_shell_of_line(&var_stack,file_data, 0); 

    free(file_data);
    free(script_file);
    return 0;
}
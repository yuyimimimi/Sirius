#include <stdio.h>
#include <lwip/sockets.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <unistd.h>
#include <console_cop.h>
#include <linux/errno.h>
int echo_main(int arg,char **argv)
{
    char *data_1 = NULL;
    char *data_2 = NULL;
    int data1_path_mod = 0;
    int needfree_data1 = 0;
    int needfree_data2 = 0;

    if(arg == 2)
    {
        data_1 = argv[1];
        printf(data_1);
        printf("\n");
        return 0;
    }

    if(arg == 3)
    {
        return 0;  
    } 

    if(arg == 4)
    {
        data_1 = argv[1];

        data1_path_mod = 1;
        if(data_1[0] != '/' && data_1[0] != '\\')
        {
            char *this_path = get_console_path();
            char *new_path = malloc(strlen(this_path) + strlen(data_1) + 2);
            needfree_data1 = 1;
            strcpy(new_path, this_path);
            strcat(new_path, "/");
            strcat(new_path, argv[1]);
            data_1 = new_path;
        }
    
        if(strcmp(argv[2], ">") != 0)
        {
            if(needfree_data1)
            free(data_1);
            if (needfree_data2)
            free(data_2);
            return 0;  
        }

        data_2 = argv[3];
        if(data_2[0] != '/' && data_2[0] != '\\')
        {
            char *this_path = get_console_path();
            char *new_path = malloc(strlen(this_path) + strlen(data_2) + 2);
            needfree_data2 = 1;
            strcpy(new_path, this_path);
            strcat(new_path, "/");
            strcat(new_path, argv[3]);
            data_2 = new_path;
        }
    }

    char *data = NULL; 
    int needfree_data = 0;
    if(data1_path_mod == 1)
    {
        FILE *fp = fopen(data_1, "r");
        if(fp == NULL)
        {
           data = argv[1];
        }
        else
        {
        fseek(fp, 0, SEEK_END);
        int size = ftell(fp);
        fseek(fp, 0, SEEK_SET);
        data = (char*)malloc(1+size);
        needfree_data = 1;
        if (data == NULL) 
        {
            perror("Failed to allocate memory");
            fclose(fp);
            if(needfree_data1)
            free(data_1);
            if (needfree_data2)
            free(data_2);
            return 1;
        }
        fread(data, 1, size, fp);
        fclose(fp);
        data[size] = '\0';             
        }
    } 
    else
    {
        data = data_1;
    }

    FILE *fp = fopen(data_2, "w");
    if(fp == NULL)
    {
        if(needfree_data1)
        free(data_1);
        if (needfree_data2)
        free(data_2);
        if(needfree_data)
        free(data);

        if(-EBUSY == errno)
        {
            printf("Error: %s is busy\n", data_2);
            return 0;
        }
        printf("Error: %s not found\n", data_2);
        return 0;
    }
    fprintf(fp, "%s", data);
    fclose(fp);

    if(needfree_data1)
    free(data_1);
    if (needfree_data2)
    free(data_2);
    if(needfree_data)
    free(data);
    return 0;  
}
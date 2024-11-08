#include<linux/module.h>
#include<linux/init.h>
#include<linux/kernel.h>
#include<stdio.h>
#include <linux/fs.h>

//本文件用于接口转换



static int tty_dev_open(void * p ,const char *path, int flags, int mode) 
{
    return 0;
}
static int i2c_dev_release(void * p ,int fd) 
{
    return 0;  
}

static ssize_t   i2c_dev_write(void * p ,int fd, const void *buf, size_t count) 
{

    FILE *fp = fopen("/dev/uart/0", "w");
    if (fp == NULL) {
        printk(KERN_ERR "open uart failed\n");
        return -1;
    }
    int ret = fwrite(buf, count, 1, fp);
    if (ret != 1) {
        printk(KERN_ERR "write uart failed\n");
        return -1;
    }
    fclose(fp);
   
    return count;
}


static ssize_t i2c_dev_read(void * p ,int fd, void *buf, size_t count) 
{
    FILE *fp = fopen("/dev/uart/0", "r");
    if (fp == NULL) {
        printk(KERN_ERR "open uart failed\n");
        return -1;
    }
    int ret = fread(buf, count, 1, fp);
    if (ret != 1) {
        printk(KERN_ERR "read uart failed\n");
        return -1;
    }
    fclose(fp);
    return count;
}


file_operations_t tty_fops = {
    .open_p = tty_dev_open,
    .close_p = i2c_dev_release,
    .write_p = i2c_dev_write,
    .read_p = i2c_dev_read,
};

int __init tty1_init(void) 
{ 
    int major = 200;
    int ret = register_chrdev(major, "tty1", &tty_fops);
    if (ret < 0) {
        printk(KERN_ERR "register tty1 device failed\n");
        return ret;
    }
    printk(KERN_INFO "tty1 device is registered successfully, major number is %d\n", major);
    return 0;
}
void __exit tty1_exit(void) 
{
    unregister_chrdev(200, "tty1");
    printk(KERN_INFO "tty1 device is unregistered successfully\n");
}


//module_init(tty1_init);
module_exit(tty1_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("liuzheng");
MODULE_DESCRIPTION("tty1 device driver");
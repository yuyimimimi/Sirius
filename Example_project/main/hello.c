#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>

 static int open(void* ctx, const char * path, int flags, int mode)
 {
     return 0;
 }
 static  int close(void* ctx, int fd)
 {
     return 0;
 }
static ssize_t read_p(void* ctx, int fd, void * dst, size_t size)
 {
    printk(KERN_INFO "Hello, world!\n");
     return 0;
 }
 static  ssize_t write_p(void* p, int fd, const void * data, size_t size)
 {
     return 0;
 }
 static int ioctl_p(void* ctx, int fd, int cmd, va_list args)
 {
     return 0;
 }

 static file_operations_t fops = {
    .open_p = open,
    .close_p = close,
    .read_p = read_p,
    .write_p = write_p,
    .ioctl_p = ioctl_p,
};

int __init hello_init(void)
{
    int major = 200;
    int devnumber = register_chrdev(major, "hello", &fops);
     if (devnumber < 0) {
        pr_err("Failed to register device\n");
        return -1;
     }
     printk(KERN_INFO "Hello, world! Device number is %d\n", devnumber);
    return 0;  
}

void __exit hello_exit(void)
{
    printk(KERN_INFO "Goodbye, world!\n");
}

module_init(hello_init);
module_exit(hello_exit);

MODULE_LICENSE("GPL-2.0");
MODULE_AUTHOR("Sirius");
MODULE_DESCRIPTION("A simple hello world module");

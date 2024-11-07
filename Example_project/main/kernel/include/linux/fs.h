#define _LINUX_FS_H
#ifdef  _LINUX_FS_H

#include "esp_vfs.h"
#include "esp_vfs_dev.h"

#define file_operations_t esp_vfs_t


// struct inode {
//     int flags;
// };

// struct file {
//     void* ctx;
//     const char * path;
//     int mode;
//     int fd;
// };
// typedef struct loff{
//     int low;
//     int high;
// }loff_t;



// typedef struct file_operations {
//     int     (*open)(void* ctx, const char * path, int flags, int mode);  
//     int     (*release)(void* ctx, int fd); 
//     ssize_t (*read)(void* ctx, int fd, void * dst, size_t size); 
//     ssize_t (*write)(void* p, int fd, const void * data, size_t size);    
//     int     (*ioctl)(void* ctx, int fd, int cmd, va_list args);
// }file_operations_t;






uint32_t register_chrdev(uint32_t major,char* name,file_operations_t *fops,...);
void unregister_chrdev(uint32_t major,char* name,...);
uint32_t MKDEV(uint16_t major, uint16_t minor );
uint32_t MAJOR(uint32_t dev_num);
uint32_t MINOR(uint32_t dev_num);



// typedef struct file_operations {
//     int (*open)(struct inode *inode, struct file *file);
//     int (*release)(struct inode *inode, struct file *file);
//     ssize_t (*read)(struct file *file, char *buf, size_t len, loff_t *offset);
//     ssize_t (*write)(struct file *file, const char *buf, size_t len, loff_t *offset);
//     int (*ioctrl)(struct file *file, loff_t offset, int whence);
// };




#endif
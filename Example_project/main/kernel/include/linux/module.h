#ifndef _LINUX_MODULE_H
#define _LINUX_MODULE_H

#define __initdata
#define __exitdata
#define __initconst
#define __exitconst
#define __MODULE_LICENSE(str)
#define __MODULE_DESCRIPTION(str)
#define __MODULE_AUTHOR(str)
#define __MODULE_ALIAS(str)
#define __MODULE_VERSION(str)
#define __MODULE_INFO(str, ver)
#define __MODULE_FIRMWARE(str)
#define __MODULE_DEPEND(str)
#define __MODULE_ALIAS_OF(str)

typedef int  (*init_func_t)(void);

typedef void (*Add_func_t) (void);

#define module_init(var) \
    __attribute__((used)) static init_func_t __initvar_##var \
    __attribute__((section(".init_array"))) = var;

typedef void (*exit_func_t)(void);

#define module_exit(var) 

#define AppInit_init(var) \
    __attribute__((used)) static Add_func_t __initvar_##var \
    __attribute__((section(".init_array"))) = var;

#define MODULE_LICENSE(x)

#define MODULE_AUTHOR(x) 

#define MODULE_DESCRIPTION(x) 

#define MODULE_ALIAS(x) 

#define MODULE_VERSION(x) 

#define MODULE_INFO(x, y) 

#define MODULE_FIRMWARE(x) 

#define MODULE_DEPEND(x)

#endif /* _LINUX_MODULE_H */

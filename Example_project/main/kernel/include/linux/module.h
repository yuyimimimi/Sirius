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
typedef void (*exit_func_t)(void);
typedef void (*Add_func_t) (void);

#define module_init(var) \
    __attribute__((used)) static init_func_t __initvar_##var \
    __attribute__((section(".init_array"))) = var;


#define module_exit(var) //暂时不用exit_func_t
    // __attribute__((used)) static exit_func_t __exitvar_##var \
    // __attribute__((section(".exit_array"))) = var;


#define AppInit_init(var) \
    __attribute__((used)) static Add_func_t __initvar_##var \
    __attribute__((section(".init_array"))) = var;

#define MODULE_LICENSE(x) \
    static const char __module_license[] __attribute__((section("__mod_license"))) = (x)

#define MODULE_AUTHOR(x) \
    static const char __module_author[] __attribute__((section("__mod_author"))) = (x)

#define MODULE_DESCRIPTION(x) \
    static const char __module_description[] __attribute__((section("__mod_description"))) = (x)

#define MODULE_ALIAS(x) \
    static const char __module_alias[] __attribute__((section("__mod_alias"))) = (x)

#define MODULE_VERSION(x) \
    static const char __module_version[] __attribute__((section("__mod_version"))) = (x)

#define MODULE_INFO(x, y) \
    static const char __module_info_##x[] __attribute__((section("__mod_info"))) = (y)

#define MODULE_FIRMWARE(x) \
    static const char __module_firmware[] __attribute__((section("__mod_firmware"))) = (x)

#define MODULE_DEPEND(x) \
    static const char __module_depend[] __attribute__((section("__mod_depend"))) = (x)


#endif /* _LINUX_MODULE_H */

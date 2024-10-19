#ifndef _LINUX_OF_DEVICE_H
#define _LINUX_OF_DEVICE_H

struct  of_device_id
{
    char *name;
    char *type;
    char *compatible;
    void *data;
};

enum probe_type{
    PROBE_ANY,
    PROBE_PREFER_ASYNCHRONOUS,
    PROBE_PREFER_SYNCHRONOUS   
};


struct  driver_driver
{
    const char *name;
    struct bus_type *bus;
    struct module *owner;
    const char *mod_name;
    uint8_t suppress_bind_attrs;
    enum probe_type probe_type;
    const struct of_device_id *of_match_table;
};

typedef struct pm_message {
    int event;
} pm_message_t;


struct platform_driver
{
    int (*probe)(struct platform_device *pdev);
    int (*remove)(struct platform_device *pdev);
    void (*shutdown)(struct platform_device *pdev);
    int (*suspend)(struct platform_device *pdev, pm_message_t state);
    int (*resume)(struct platform_device *pdev);
    struct  driver_driver driver;
};
    


#endif /* _LINUX_OF_DEVICE_H */


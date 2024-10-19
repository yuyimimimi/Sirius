#ifndef _LINUX_OF_H
#define _LINUX_OF_H
#include <linux/types.h>
#include <linux/init.h>

    typedef __u32 phandle;
    typedef __u32 ihandle;

    struct property {
        char	*name;
        int	length;
        void	*value;
        struct property *next;
    #if defined(CONFIG_OF_DYNAMIC) || defined(CONFIG_SPARC)
        unsigned long _flags;
    #endif
    #if defined(CONFIG_OF_PROMTREE)
        unsigned int unique_id;
    #endif
    #if defined(CONFIG_OF_KOBJ)
        struct bin_attribute attr;
    #endif
    };

    #if defined(CONFIG_SPARC)
    struct of_irq_controller;
    #endif

    struct device_node {
        char* node_path;
        const char *name;
        
        phandle phandle;
        const char *full_name;
        //struct fwnode_handle fwnode;
        struct	property *properties;
        struct	property *deadprops;	/* removed properties */
        struct	device_node *parent;
        struct	device_node *child;
        struct	device_node *sibling;
    #if defined(CONFIG_OF_KOBJ)
        struct	kobject kobj;
    #endif
        unsigned long _flags;
        void	*data;
    #if defined(CONFIG_SPARC)
        unsigned int unique_id;
        struct of_irq_controller *irq_trans;
    #endif
};


// Function to find a device node by its path
struct device_node* of_find_node_by_path( char *path);

// Function to get a property value from a device node
void* of_get_property(struct device_node *dev_node, char *property_name, int *len);

// Function to release a device node reference
void of_node_put(struct device_node *dev_node);



#endif /* _LINUX_OF_H */
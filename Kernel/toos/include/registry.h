#ifndef __REGISTRY_H__
#define __REGISTRY_H__

#define REGISTRY_PATH  "/etc/"
int registry_init(void);

char *get_registry_path(void);

#endif /* __REGISTRY_H__ */
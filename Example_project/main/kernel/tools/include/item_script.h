#ifndef ITEM_SCRIPT_H
#define ITEM_SCRIPT_H
/**
 * @ file item_script.h
 * 
*/

/**
 * init data storage
 * @param path path to data storage
 * 
*/
void init_data_storage(char *path);
/**
 * get item value by name
 * @param path path to data storage
 * @param name item name
 * @return item value
 * 
 * you need to free the returned value after use
*/
char *getitem(const char *path,char *name) ;
/**
 * insert or update item value by name
 * @param name item name
 * @param value item value
 * @param overwrite  1: overwrite if item exists, 0: do not overwrite if item exists
 * @param path path to data storage
 * 
*/
int setitem(const char *name, const char *value, int overwrite,char *path) ;
/**
 * delete item by name
 * @param name item name
 * @param path path to data storage
 * @return 0: success, -1: failed
 * 
*/
int unsetitem(const char *name , char *path) ;


char* get_item_from_data(const char *__string,char *data);        //项目名称、文件内容


char* trim_braces(char* str); //删除字符串两端的{}


#endif
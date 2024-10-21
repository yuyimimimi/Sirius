#ifndef _ENV_H_
#define _ENV_H_

void init_env();
/**
 * @brief get path from /etc/profile
 * @param __string the path to be found
 * @return the path found or NULL if not found
*/

char* getenv_(const char *__string);

/**
 * @brief set or update environment variable
 * @param name the name of the environment variable
 * @param value the value of the environment variable
 * @param overwrite if 1, overwrite the existing value, otherwise, do not overwrite
 * @return 0 if success, -1 if failed
*/

int setenv_(const char *name, const char *value, int overwrite);

/**
 * @brief remove environment variable
 * @param name the name of the environment variable
 * @return 0 if success, -1 if failed   
 * 
*/
int unsetenv_(const char *name);



#endif /* _ENV_H_ */
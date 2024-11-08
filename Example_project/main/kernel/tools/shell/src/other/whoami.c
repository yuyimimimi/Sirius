#include <stdio.h>
#include <unistd.h>
#include "env.h"

int whoami_command(int argc, char *argv[]) {
    char *user =  getenv_("username"); 
    if (user == NULL) {
        user = "unknown";
    }
    printf("%s\n", user);
    free(user);
    return 0;
}

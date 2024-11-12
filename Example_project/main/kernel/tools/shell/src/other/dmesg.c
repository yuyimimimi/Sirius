#include <stdio.h>
#include "env.h"


int dmesg(int argc, char **argv)
{
 char *log_path = getenv_("LOG_PATH");
 if (log_path == NULL) {
  printf("LOG_PATH not set\n");
  return 1;
 }
 FILE *fp = fopen(log_path, "r");
 if (fp == NULL) {
  printf("Failed to open %s\n", log_path);
  return 1;
 }
 while (1) {
  char buf[1024];
  int n = fread(buf, 1, sizeof(buf), fp);
  if (n <= 0) {
   break;
  }
  fwrite(buf, 1, n, stdout);
 }
 fclose(fp);
 return 0;
}
#include <stdio.h>




int helloworld(int argc, char const *argv[])
{
  if(argc > 1)
  {
   system("echo Hello World!");    
  }
  else
  {
   printf("Hello World!\n");    
  }


   return 0;
}


#include <app_install.h>
void install_test()
{
    add_console_app("helloworld", helloworld, "test_main");
}

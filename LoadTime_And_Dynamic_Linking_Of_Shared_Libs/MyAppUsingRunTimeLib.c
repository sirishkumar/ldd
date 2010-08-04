#include <stdio.h>
#include <prog1.h>
#include <dlfcn.h>

int main()
{
   char *ptr;
   void *handle;

   handle = dlopen("./libmylib.so",RTLD_NOW);
   
   int (*fnptr)(int,int);

   fnptr = dlsym(handle,"findmax");

   printf("Max(12,45): %d",fnptr(12,45));

   dlclose(handle);
}

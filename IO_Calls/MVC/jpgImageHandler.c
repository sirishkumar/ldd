#include <stdio.h>
#include <config.h>
#include <string.h>

bool jpgCanHandle( char *path)
{
   char* ext = &path[strlen(path)-3];
   bool bResult = false;   

   if ( strcmp("jpg",ext) == 0 )
   {
      return true;
   }

   return bResult; 
}

void jpgdrawImage( char *filePath)
{
   printf("Draw Image %s",filePath);
}

void register_handler()
{
   struct imageHandler s={
       jpgCanHandle,
       jpgdrawImage
    };
   
   registerHandler("jpg",&s);
}


int _int()
{
   register_handler();
}

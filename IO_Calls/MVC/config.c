#include <stdio.h>
#include <config.h>

struct imageHandler * iHandlers[10];
static int i =0;

void registerHandler(char *imageType,struct imageHandler*poImageHandler)
{
   iHandlers[i++] = poImageHandler;
    
}

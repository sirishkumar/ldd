#include <stdio.h>
#include <string.h>
#include "viml.h"


void vdrawImage(char* path)
{
   printf("\nDrawing Image testi %d",strlen(path));

   char *pImageExt = &path[strlen(path)-3];

   printf("\nExtension is %s",pImageExt);
}


void vconvertImage(const char*path)
{

   printf("\nvconertImage");

   char *pImageExt = path[strlen(path)-3];

   printf("%s",pImageExt);

}

void vsaveImage(const char*path)
{

   printf("\n Image");

   char *pImageExt = path[strlen(path)-3];

   printf("%s",pImageExt);

}

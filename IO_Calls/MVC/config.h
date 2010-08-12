#include <stdio.h>

typedef bool (*canHandle)( char*);
typedef void (*drawImage)( char *);

struct imageHandler
{
   canHandle pcanHandler;
   drawImage pdrawImage;
};


void registerHandler(char *imageType,struct imageHandler*poImageHandler);

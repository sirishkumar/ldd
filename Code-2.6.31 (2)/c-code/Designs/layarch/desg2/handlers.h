
/* Prototypes of the functions that need to be implemented by each handler 
Version : 1.0
Author : Team -C
*/

# define TRUE 1
# define FALSE 0

typedef struct {
	int (*canHandle) (char *);
	int (*drawImage)(char *);
	int (*savefile)(char *);
}imageHandler;

extern imageHandler *imagehandlers[];
extern imageHandler tifhandler;
extern imageHandler gifhandler;
extern imageHandler jpghandler;
extern imageHandler bmphandler;
//extern imageHandler pcxhandler;

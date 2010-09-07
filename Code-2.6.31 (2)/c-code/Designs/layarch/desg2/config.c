
/* This is a very standard technique used to add multiple types of
handlers
Version : 1.0
Author : Team -C
*/
# include <stdio.h>
# include "handlers.h"

imageHandler *imagehandlers[]={
	&tifhandler,//exported by tifhandler
	&gifhandler,//exported by gifhandler
	&jpghandler,//exported by jpghandler
	&bmphandler,
	NULL
};

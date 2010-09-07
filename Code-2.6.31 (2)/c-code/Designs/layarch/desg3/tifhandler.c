

/* This module takes care of gif files 
Version : 1.0
Author : Team -C
*/
#include <stdio.h>
# include <string.h>
# include "handlers.h"


// function returns whether this can handle the file or not

int tif_canHandle(char *filename){
	int len;
	char *end;
	printf(" Checking whether I can handle %s or not \n",filename);
	len = strlen(filename);
	end = filename + (len -3);
	printf(" end = %s\n",end);
	// just for testing purpose, in the real code the file need to be
	// opened and we need to check for magic no's.
	if(strcmp(end,"tif") == 0)
		return TRUE;
	else
		return FALSE;
}

int tif_drawImage(char *filename){
	if( tif_canHandle(filename)){
		printf("(TIF) How is this image %s \n",filename);
		return TRUE;
	}
	else
		return FALSE;
}

int tif_savefile(char *newfilename ){
	printf(" file saved by TIF handler \n");
	return TRUE;
}

imageHandler tifhandler = {
	tif_canHandle,
	tif_drawImage,
	tif_savefile
};

int _init(){
	printf(" registering tif handler\n");
	reg_handler(&tifhandler);
	return 0;
}

int _fini(){
	printf(" Un registering tif handler \n");
}

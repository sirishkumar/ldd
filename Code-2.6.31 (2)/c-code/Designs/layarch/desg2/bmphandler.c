                                            
/* This module takes care of gif files 
Version : 1.0
Author : Team -C
*/

# include <string.h>
# include "handlers.h"


// function returns whether this can handle the file or not

int bmp_canHandle(char *filename){
	int len;
	char *end;
	printf(" Checking whether I can handle %s or not \n",filename);
	len = strlen(filename);
	end = filename + (len -3);
	printf(" end = %s\n",end);
	// just for testing purpose, in the real code the file need to be
	// opened and we need to check for magic no's.
	if(strcmp(end,"bmp") == 0)
		return TRUE;
	else
		return FALSE;
}

int bmp_drawImage(char *filename){
	if( bmp_canHandle(filename)){
		printf("(BMP) How is this image %s \n",filename);
		return TRUE;
	}
	else
		return FALSE;
}

int bmp_savefile(char *newfilename ){
	printf(" file saved by BMP handler \n");
	return TRUE;
}

imageHandler bmphandler = {
	bmp_canHandle,
	bmp_drawImage,
	bmp_savefile
};

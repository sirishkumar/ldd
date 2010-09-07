                                              
/* This module takes care of gif files 
Version : 1.0
Author : Team -C
*/

# include <string.h>
# include "handlers.h"


// function returns whether this can handle the file or not

int pcx_canHandle(char *filename){
	int len;
	char *end;
	printf(" Checking whether I can handle %s or not \n",filename);
	len = strlen(filename);
	end = filename + (len -3);
	printf(" end = %s\n",end);
	// just for testing purpose, in the real code the file need to be
	// opened and we need to check for magic no's.
	if(strcmp(end,"pcx") == 0)
		return TRUE;
	else
		return FALSE;
}

int pcx_drawImage(char *filename){
	if( pcx_canHandle(filename)){
		printf(" How is this image %s \n",filename);
		return TRUE;
	}
	else
		return FALSE;
}

int pcx_savefile(char *newfilename ){
	printf(" file saved by pcx handler \n");
	return TRUE;
}

imageHandler pcxhandler = {
	pcx_canHandle,
	pcx_drawImage,
	pcx_savefile
};

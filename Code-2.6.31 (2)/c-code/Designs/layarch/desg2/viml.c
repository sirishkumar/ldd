	
/* This  Layer delegates tasks to appropriate handler
Version : 1.0
Author : Team -C
Note : Try to remove redundant code from these functions.
*/

# include <stdio.h>
# include <string.h>
# include "handlers.h"

int find_handler(char * filename){
	imageHandler *ih;
	int handleno = 0;
	ih = imagehandlers[0];
	while(ih != NULL){
		printf(" viml handle no = %d ptr = %d\n",handleno,ih);
		if(ih ->canHandle(filename))
			return handleno;
		handleno++;
		ih = imagehandlers[handleno];
	}
		return -1;
}

int vdrawImage(char *filename){
	imageHandler *ih;
	int handleno = 0;
	handleno = find_handler(filename);
	printf(" handle no = %d\n", handleno);
	if( handleno == -1){
		printf(" We cannot handle this kind of files\n");
		return FALSE;
	}
	ih=imagehandlers[handleno];
	ih->drawImage(filename);	
    	return FALSE;		
}

int vsavefile(char *newfilename ){
	imageHandler *ih;
	int handleno = 0;
	handleno = find_handler(newfilename);
	if( handleno == -1){
		printf(" We cannot handle this kind of files\n");
		return FALSE;
	}
	ih=imagehandlers[handleno];
	ih->savefile(newfilename);	
	return FALSE;		
}


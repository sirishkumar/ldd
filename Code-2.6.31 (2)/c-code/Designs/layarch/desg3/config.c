
/*  Module to load the image handlers array with imagehandlers.
Version : 1.0
Author : Team -C
*/
# include <stdio.h>
# include <dlfcn.h>
# include "handlers.h"

 
imageHandler *imagehandlers[SIZE];

// max of 10 handlers you can change the code to accomidate any no of
// handlers
static int libs = 0;

int reg_handler(imageHandler *ih){
// we need to perform checks here.
	imagehandlers[libs] = ih;
	libs++;
	return TRUE;
}
void unreg_handler(int no){
	printf(" not yet implemented\n");
}

// This function dynamically fills the array with handlers.

int init_handlers(){
	FILE *fp;
	void *soptr;
	char so_name[300];
	fp=fopen("./config.txt","r");
	if(fp==NULL){
		printf(" config.txt not found \n");
		return FALSE;
	}
	fgets(so_name,300,fp);
	while(!feof(fp)){
		so_name[strlen(so_name) - 1] = '\0';
		printf(" Loading .. %s\n",so_name);
		soptr = dlopen(so_name,RTLD_NOW);
		if(soptr == NULL){
			printf("Failed to load library\n");
			return FALSE;
		}
		fgets(so_name,300,fp);
	}	
		return TRUE;
}

/* added this for testing purpose
main(){
	init_handlers();
}

*/

/* Shows how to use remap sys call
Version : 1.0
Author : Team -C
Note : All modern OS supports memory mapping of files.
*/

# include <unistd.h>
# include <sys/types.h>
# include <sys/mman.h>
# include <fcntl.h>
# include <stdio.h>
# include <errno.h>
#define _GNU_SOURCE

main(){
	int fd,i;
	unsigned char *filedata= NULL,*temp;
	fd = open("install.log",O_RDWR);
	filedata = (char *) mmap((void*)0,60,PROT_READ|PROT_WRITE,\
			 MAP_SHARED,fd,0);	
	if(filedata == NULL){
		perror("Maping Failed");
		exit(1);
	}
	// now we can access the content of the file as if it is part of
	// our process starting from the memory pointed by filedata.
	temp = filedata;
	for(i=0;i<60;i++,filedata++)
		*filedata = (char)(i+65);

	if(mremap((void *)temp,60,70, 1)==MAP_FAILED)
		perror("mreamp : ");
	for(i=1;i<=10;i++,filedata++)
		*filedata = '*';
	if(msync(temp,70,MS_SYNC)!=0)
		perror("msync : ");
	
	i = munmap(temp,60);
	if( i != 0)
		printf(" failed to unmap\n");
}

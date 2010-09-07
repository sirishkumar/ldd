/*
 * Team : IDST
 * Version : 1.0
*/


/* ToDo:
 * 	1. add code to caliberate system time spent on io calls
 * 	
*/
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>

main()
{
	char buf[30];
	int fd,rev;

	
	if( (fd = open("read.txt", O_RDWR | O_CREAT | O_EXCL)) < 0)
	{	
		printf("\n open to fail");
		exit(0);
	}
	else
		printf("\n Open sucessfully");


/*	posix_fadvise(fd, 0 , 20, POSIX_FADV_NORMAL);	 Ok with default read_ahead */
	
	rev = posix_fadvise(fd, 0 , 20, POSIX_FADV_SEQUENTIAL); // Enable full read_ahead 
	if(rev!=0)
		perror("posix_fadvise : ");

/*	posix_fadvise(fd, 0 , 20, POSIX_FADV_RANDOM);  Disable read_ahead */
	
	
	if( read(fd,buf,1000) < 0)
	{
		printf("\n read error");
		exit(0);
	}
	printf("\n The read  msg : %s", buf);
	close(fd);

}

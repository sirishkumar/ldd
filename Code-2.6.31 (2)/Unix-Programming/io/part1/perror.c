/* To demonstrate read sysytem call 
Team : IDST
Version : 1.0
*/


#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<errno.h>

main()
{
	char buf[30];
	int fd;

	
	if( (fd = open("read1txt", O_RDWR )) < 0)
	{	
		perror("open ");
		exit(1);
	}
	else
		printf("\n Open sucessfully");
	
	
	if( write(fd,"IDST",4) != 4)
	{
		perror("\nwrite error");
		exit(1);
	}
	//offset now = 4

	if( lseek(fd,0,0) == -1)
	{
		perror("\n lseek error");
		exit(1);
	}
	
	if( read(fd,buf,4) < 0)
	{
		perror("\n read error");
		exit(1);
	}
	printf("\n The read  msg : %s", buf);
	printf("\n");
	close(fd);

}

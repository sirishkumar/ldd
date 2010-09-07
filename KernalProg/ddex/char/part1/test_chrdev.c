/* test_char_driver.c
** Team: Veda
** Version: 1.0
*/

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <errno.h>

/**
* This program uses the device driver veda_chr_driver and opens a file on it.
* It performs the read, write and lseek operation apart from open() and close()
* Hence it checks the drivers functionality
*/
int main()
{
	int fd, i;
	ssize_t ret;
	char my_buf[4000];
	
	/* fill my buffer with *'s */
	for(i=0; i<4000; i++) my_buf[i] = '*';
	
	/* open the device for read/write/lseek */
	printf("[%d] - Opening device veda_chr_driver\n", getpid() );
	fd = open( "/dev/veda_cdrv", O_RDWR );
	printf("PID [%d]\n", getpid());
	getchar();
	
	/* write the contents of my buffer into the device */
	ret = write( fd, my_buf, 4000 );
	      lseek(fd,10,SEEK_SET);
	ret= read(fd,my_buf,3000);
	close(fd);
}
	

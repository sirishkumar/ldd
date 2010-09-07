/*

This program explains about create system call from creating a new file

Author	: Team Veda
Usage	: int creat (const char *filename, mode_t mode)
	  
Version	: 1.0

*/

#include<stdio.h>
#include<fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>


int main()
{
	int fd;
	char ch;
	fd = creat("Demo.txt",S_IRWXU|S_IRWXG);
	printf("\n New File Desp : %d",fd);
	getchar();
	close(fd);
}

/*

This program explains about Low Level Input

Author	: Team Veda
Usage 	: ssize_t read (int fd, void *buffer, size_t size);
Version	: 1.0

*/

#include<stdio.h> 
#include<unistd.h>
#include<fcntl.h>
int main()
{
	int fd;
	char ch;
	fd = open("Demo.txt",O_RDONLY);
	while(read(fd,&ch,1)!=0)	
		putchar(ch);
	close(fd);
	printf("\n");
}

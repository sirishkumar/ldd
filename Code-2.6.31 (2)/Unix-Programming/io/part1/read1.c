/*

This program explains about Low Level Input

Author  : Team Veda
Usage   : ssize_t read (int fd, void *buffer, size_t size);
Version : 1.0

*/

#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
typedef struct
{
	int roll,age;
	char name[30],gender;	
}student;

int main()
{
	student s;
	int fd;
	fd = open("Student.dat",O_RDONLY);
	printf("\n Student Details\n");
	while(read(fd,&s,sizeof(s))!=0)
	{
		printf("\n%5d  %-20s  %4d  %1c",s.roll,s.name,s.age,s.gender);
	}
	printf("\n");
	close(fd);
}

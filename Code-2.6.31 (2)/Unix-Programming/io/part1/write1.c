/*

This program explains about Low Level Outpu

Author  : Team Veda
Usage   : ssize_t write (int fd, void *buffer, size_t size);
Version : 1.0

*/

#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
typedef struct
{
	int roll,age;
	char name[30],gender;	
}student;

int main()
{
	char ch;
	student s;
	int fd;
	fd = open("Student.dat",O_RDWR|O_CREAT);
	printf("\n Enter Student Details\n");
	while(1)
	{
		printf("\n Enter Student Roll Number : ");
		 scanf("%d",&s.roll);
		printf("\n Enter Student Name : ");
		 scanf(" %[^\n]",s.name);
		printf("\n Enter Student Age : ");
		 scanf("%d",&s.age);
		printf("\n Enter Student Gender : ");
		 scanf(" %c",&s.gender);
		printf("\n Continue.......(Y/N) : ");
		scanf(" %c",&ch);
		write(fd,&s,sizeof(s));
		if(ch=='n' ||ch=='N')
			break;
	}
	close(fd);
}

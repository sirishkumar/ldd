/*

This program explains hoe to Setting the File Position of a Descriptor 

Author  : Team Veda
Usage   : off_t lseek (int filedes, off_t offset, int whence)
	  whence can be 
	  SEEK_SET 
		Specifies that whence is a count of characters from the beginning of the file. 
	  SEEK_CUR 
		Specifies that whence is a count of characters from the current file position.
	  SEEK_END
		Specifies that whence is a count of characters from the end of the file.
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
	lseek(fd,0,SEEK_SET);
	while(read(fd,&s,sizeof(s))!=0)
	{
		printf("\n%5d  %-20s  %4d  %1c",s.roll,s.name,s.age,s.gender);
	}
	printf("\n");
	close(fd);
}

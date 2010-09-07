#include <stdio.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main()
{
  int fd = open("/home/sirishkumar/projects/linux/IPC/1.txt",O_RDWR,O_CREAT);

   char *pszdata = (char*)mmap(0,1024,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
   
   int i=0;
   for(i =0 ;i<1024;i++){
     
       putchar(pszdata[i]);
       pszdata[i]=i;
       if( i == 512 )
       {
           sleep(30);
       }
     }
 
}

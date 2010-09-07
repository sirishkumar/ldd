#include <stdio.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main()
{
  int fd = shm_open("/shmtext",O_RDWR|O_CREAT,S_IRUSR | S_IWUSR);

  if( fd == -1 )
  {
     printf("%d",fd);
  }

  ftruncate(fd,1024);

   char *pszdata = (char*)mmap(0,1024,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
   
   int i=0;
   for(i =0 ;i<1024;i++){
     
       putchar(pszdata[i]);
       pszdata[i]='A';
       if( i == 512 )
       {
          sleep(20);
       }
     }
 
}

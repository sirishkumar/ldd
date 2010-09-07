#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/types.h>
#include <mqueue.h>
#define BUFSIZE  50
#define NAME "/my_mq"

size_t size = BUFSIZE;

struct mq_attr attr = {
    .mq_maxmsg = 10,
    .mq_msgsize = BUFSIZE,
};

main()
{
   mqd_t fd = mq_open(NAME,O_RDWR,0666,&attr);
   
   char msg[BUFSIZE];
   int prio = 1;
   mq_receive(fd,msg,BUFSIZE,&prio);
  
   printf("\n%s",msg);

 }

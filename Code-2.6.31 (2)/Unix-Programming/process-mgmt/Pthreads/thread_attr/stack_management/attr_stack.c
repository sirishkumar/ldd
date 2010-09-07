#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/mman.h>

void * thread_routine (void *p)
{
   printf("\n I am in thread \n");
   pthread_exit(NULL);	
}


int main(int argc, char *argv[])
{
        pthread_t      tid;
        pthread_attr_t attr;
        void          *getstackaddr;
        size_t         getstacksize;

        size_t setstacksize =  16900; // in Bytes minimum 16 KB
        void *setstackaddr;
	setstackaddr =(void *) malloc(setstacksize);

        pthread_attr_init(&attr);

	pthread_attr_getstack(&attr, &getstackaddr, &getstacksize);
        printf("Default: Stack Addr=%08x  Stacj Size=%d\n", getstackaddr, getstacksize);


        // Explicitily Sets Stack Address & Stack Size
	pthread_attr_setstack(&attr, setstackaddr, setstacksize);

	getstacksize=0;
	getstackaddr=NULL;

	pthread_attr_getstack(&attr, &getstackaddr, &getstacksize);
        printf("New Stack Addr=%08x  Size=%d\n",setstackaddr,setstacksize);

	
        pthread_create(&tid, &attr,thread_routine, NULL);

	pthread_exit(NULL);
        return (0);
}

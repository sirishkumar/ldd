		/*	Example for implementing mutex for locking resources */
#include <pthread.h>
#include <stdio.h>


#define MAX_LEN 100

struct critical_data {        /* Defines "structure" of shared memory */
        int len;
        char buf[MAX_LEN];
}data[2];


// pthread mutex object
pthread_mutex_t mutex;

// Threads created will execute the following routines
 
void * write_thread (void *p)
{
	printf("\n In Write thread\n");
	if(pthread_mutex_lock(&mutex)==0)
	{
		printf("\n\t Entering critical section in Write thread \n");
		strcpy(data[0].buf,"Veda Solutions");
                data[0].len=strlen("Veda Solutions");
                strcpy(data[1].buf,"Solutions");
                sleep(2);
		data[1].len=strlen("Solutions");
		pthread_mutex_unlock(&mutex);
		printf ("\t Leaving critical section in Write thread\n");
	}
	printf(" Write job is over\n");
	pthread_exit(NULL);	
}

void * read_thread(void *p)
{
	printf("\n In Read thread \n");
	if(pthread_mutex_trylock(&mutex)==0)
	{
		printf("\n\t Entering critical section in Read thread \n");
        	printf("\n\t %d %s \n",data[0].len,data[0].buf);
        	printf("\n\t %d %s \n",data[1].len,data[1].buf);
		pthread_mutex_unlock(&mutex);
		printf ("\t Leaving critical section in Read thread\n");
	}
	else
		printf ("\t Mutex not avalible for Read thread\n");
		
	printf(" Read job is over\n");
        pthread_exit(NULL);
}

int main ()
{
	// Object to hold thread ID
	pthread_t tid1,tid2;
	int rv;
	
	// initializing statically allocated mutex object 
	pthread_mutex_init(&mutex,NULL);
	
	// Routine shell create a new thread
	rv = pthread_create(&tid1, NULL, write_thread, NULL);
	if(rv)
		puts("Failed to create thread");

	rv = pthread_create(&tid2, NULL, read_thread, NULL);
        if(rv)
                puts("Failed to create thread");

	// suspend execution of the intial thread until the target threads terminates
	pthread_join(tid1,NULL);
	pthread_join(tid2,NULL);
	puts(" Exit Main");
	return 0;
}

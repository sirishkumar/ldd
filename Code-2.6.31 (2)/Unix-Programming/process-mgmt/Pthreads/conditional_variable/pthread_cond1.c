		/*	Example for implementing conditional variables for signaling b/n threads */
#include <pthread.h>
#include <stdio.h>

#define MAX_LEN 100

struct critical_data {        /* Defines "structure" of shared memory */
        int len;
        char buf[MAX_LEN];
}data[2];



typedef struct 
{
	// pthread mutex object
	pthread_mutex_t mutex;
	// pthread conditonal variable 
	pthread_cond_t cond;
	unsigned short conditionMet;
	unsigned short broadcast;
} my_lock_t;

my_lock_t lock = {PTHREAD_MUTEX_INITIALIZER,PTHREAD_COND_INITIALIZER,0,0}; 

// Threads created will execute the following routines
 
void * write_thread (void *p)
{
	sleep(1);
	printf("\n In Write thread\n");
	if(lock.conditionMet==0)
	{
		if(pthread_mutex_lock(&lock.mutex)==0)
		{
			printf("\n\t Entering critical section in Write thread \n");

	                strcpy(data[0].buf,"Veda Solutions");
	                data[0].len=strlen("Veda Solutions");
	                strcpy(data[1].buf,"Solutions");
	                data[1].len=strlen("Solutions");
			lock.broadcast = 1;
			pthread_cond_broadcast(&lock.cond);	
			pthread_mutex_unlock(&lock.mutex);
	                printf ("\t Leaving critical section in Write thread\n");
		}
	}
	pthread_exit(NULL);	
}

void * read_thread1(void *p)
{
       	printf("\n In Read thread1 \n");
	if(pthread_mutex_lock(&lock.mutex)==0)
	{
		while(lock.conditionMet!=1)
		{
			if(lock.broadcast == 1)
				break;
			pthread_cond_wait(&lock.cond,&lock.mutex);
		}
		printf("\n\t Entering critical section in Read thread1 \n");
                printf("\n\t %d %s \n",data[0].len,data[0].buf);
		pthread_mutex_unlock(&lock.mutex);
	}
		
		printf(" Read1 job is over\n");
        	pthread_exit(NULL);
	
}

void * read_thread2(void *p)
{
        printf("\n In Read thread2  \n");
        if(pthread_mutex_lock(&lock.mutex)==0)
        {
                while(lock.conditionMet!=1 )
                {
			if(lock.broadcast == 1)
				break;
                        pthread_cond_wait(&lock.cond,&lock.mutex);
                }
                printf("\n\t Entering critical section in Read2 thread \n");
                printf("\n\t %d %s \n",data[1].len,data[1].buf);
                pthread_mutex_unlock(&lock.mutex);
        }

                printf(" Read2 job is over\n");
                pthread_exit(NULL);

}

int main ()
{
	// Object to hold thread ID
	pthread_t tid1,tid2,tid3;
	int rv;
	// Routine shell create a new thread
	rv = pthread_create(&tid1, NULL, write_thread, NULL);
	if(rv)
		puts("Failed to create thread");

	rv = pthread_create(&tid2, NULL, read_thread1, NULL);
        if(rv)
                puts("Failed to create thread");

	rv = pthread_create(&tid3, NULL, read_thread2, NULL);
        if(rv)
                puts("Failed to create thread");

	// suspend execution of the intial thread until the target threads terminates
	pthread_join(tid1,NULL);
	pthread_join(tid2,NULL);
	pthread_join(tid3,NULL);
	puts(" Exit Main");
	return 0;
}

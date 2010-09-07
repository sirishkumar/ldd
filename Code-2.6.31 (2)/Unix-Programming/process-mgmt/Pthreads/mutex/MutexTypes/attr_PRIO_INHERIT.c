
					/* get and set scheduling policies & priority of a thread */


#include <pthread.h>
#include <stdio.h>

pthread_mutex_t mutex;

void *thread1(void *null)
{
	printf("\n In thread1 \n");
	getchar();
	if(pthread_mutex_lock(&mutex)==0)
	{
		getchar();
	}
	pthread_mutex_unlock(&mutex);
	getchar();
	printf("\n Exit thread1 \n");
	pthread_exit(NULL);
}



void *thread2(void *null)
{
	printf("\n In thread2 \n");
	sleep(1);
	getchar();
	if(pthread_mutex_lock(&mutex)==0)
	{
		sleep(5);
		pthread_mutex_unlock(&mutex);
	}
	
	printf("\n Exit thread2 \n");
        pthread_exit(NULL);
}



int main (int argc, char *argv[])
{
	pthread_mutexattr_t attrmutex;

	int inherit,policy,priority,rc;
        struct sched_param param;

	pthread_t tid1,tid2,tid3;
	pthread_attr_t attr;

	pthread_attr_init(&attr);
/* --------------------------------------------------------------------------- */
	pthread_mutexattr_init(&attrmutex);
	pthread_mutexattr_setprotocol(&attrmutex,PTHREAD_PRIO_INHERIT);
	pthread_mutex_init(&mutex,&attrmutex);
	//pthread_mutex_init(&mutex,NULL);
/* --------------------------------------------------------------------------- */

	
	// Sets inheritsched attribute 
	pthread_attr_setinheritsched(&attr,PTHREAD_EXPLICIT_SCHED);
	param.sched_priority=75;
	pthread_setschedparam(pthread_self(),SCHED_FIFO,&param);
	

	param.sched_priority=70;
	pthread_attr_setschedpolicy(&attr,SCHED_RR);
	pthread_attr_setschedparam(&attr,&param);

	pthread_create(&tid1, &attr, thread1, NULL);

	param.sched_priority=90;
        pthread_attr_setschedpolicy(&attr,SCHED_RR);
        pthread_attr_setschedparam(&attr,&param);
	
	pthread_create(&tid2, &attr, thread2, NULL);
	
	rc = pthread_join(tid1,NULL); 	
	rc = pthread_join(tid2,NULL); 	
	
	/* destroy attribute object */
	pthread_attr_destroy(&attr);

	printf("\n Exiting from main Thread\n");
	pthread_exit(NULL);

}



#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/mman.h>



/* Reads Stack attributes  */
void read_stack_attributes(pthread_attr_t *attr)
{
        void          *getStkAddr;
        size_t         getStkSize;
        pthread_attr_getstack(attr, &getStkAddr,&getStkSize);
        printf("\n Stack Attributes");
        printf("\n\tStack Addr=%p\tSize=%d\n", getStkAddr, getStkSize);
}

/* Reads Detach State attribute */
void read_detachstate_attribute(pthread_attr_t *attr)
{
        size_t         detachstate;
	pthread_attr_getdetachstate(attr,&detachstate);
        printf("\n Detach State attribute");
	if(detachstate == PTHREAD_CREATE_JOINABLE)
		printf("\n\tJoinable state\n");
	else
		printf("\n\tDetached state\n");
		
}

/* Reads guard size attribute */
void read_guard_attribute(pthread_attr_t *attr)
{
        size_t         guardsize;
	pthread_attr_getguardsize(attr,&guardsize);
        printf("\n Guard Attribute");
        printf("\n\tGuard Size=%u\n", guardsize);
}

/* Read  schedpolicy attribute */
void read_schedpolicy_attribute(pthread_attr_t *attr)
{
        size_t         policy;
        pthread_attr_getschedpolicy(attr,&policy);
        printf("\n Scheduling Policy Attribute");
	if(policy == SCHED_OTHER )
		printf("\n\tOther Scheduling Policy\n");
	else if(policy == SCHED_RR )
		printf("\n\tRound Robin Scheduling Policy\n");
	else if(policy == SCHED_FIFO )
		printf("\n\tFIFO Scheduling Policy\n");
}


void* thread(void* param)
{
	pthread_attr_t attr;
	printf("\n In thread\n" );
	pthread_getattr_np(pthread_self(), &attr);	
	read_stack_attributes(&attr);
	read_detachstate_attribute(&attr);
	read_guard_attribute(&attr);
	read_schedpolicy_attribute(&attr);
        return 0;
}




int main(int argc, char *argv[])
{
        pthread_t      tid1,tid2;

        pthread_create(&tid1, NULL, thread, NULL);

	pthread_join(tid1,NULL);
        return (0);
}

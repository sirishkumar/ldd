//#define _GNU_SOURCE
#include <sched.h>
#include <unistd.h>
int main()
{

	int i=0;
	int pid;
	int no_processors;
	
	no_processors = sysconf(_SC_NPROCESSORS_CONF);
        printf("System has %d processors.\n", no_processors);
	while(i< no_processors-1)
	{
		pid = fork();
		if(pid==0)
		{
			printf("\n child %d\n",i);
			break;
		}	
		else
			i++;
	}

	/* All childs execute the following code */
	cpu_set_t cset;
	CPU_ZERO( &cset );
	CPU_SET( i, &cset);
	
	if( sched_setaffinity( 0, sizeof(cset), &cset ) == -1 )
                perror("CPU Affinity...\n");
	
	
}


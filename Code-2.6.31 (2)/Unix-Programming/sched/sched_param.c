#include <sched.h>
#include <stdio.h>

int main()
{
	struct sched_param param;
	
	sched_getparam(0, &param);
	printf("\n Default Priority : %d",param.sched_priority);

	param.sched_priority = 70;
	sched_setscheduler(0, SCHED_RR,&param);	
	
	sched_getparam(0, &param);
	printf("\n New Priority : %d",param.sched_priority);

	param.sched_priority = 60;
        sched_setparam(0,&param);

	sched_getparam(0, &param);
	printf("\n New Priority : %d",param.sched_priority);
	

}

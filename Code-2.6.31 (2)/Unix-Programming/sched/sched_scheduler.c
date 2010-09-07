#include <sched.h>
#include <stdio.h>

void query_policy()
{
	int policy;
        policy = sched_getscheduler(0);

        switch(policy)
        {
                case SCHED_OTHER:
                        printf("\n Fare share schedulin......\n");
                        break;
                case SCHED_RR:
                        printf("\n Round Robin scheduling......\n");
                        break;
                case SCHED_FIFO:
                        printf("\n First In-First Out scheduling......\n");
                        break;
        }
}


int main()
{
	struct sched_param param;
	param.sched_priority=60;
	getchar();
	query_policy();
	sched_setscheduler(0, SCHED_RR,&param);
	getchar();
	query_policy();

}

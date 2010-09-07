#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <errno.h>

int main (int argc, char *argv[])
{
    pid_t mypid;
    int old_prio, new_prio, i=1, rc;



    while(i< 3)
        {
                mypid = fork();
                if(mypid==0)
                {
			mypid = getpid();
			old_prio = getpriority (PRIO_PROCESS, (int)mypid);
			getchar();
			printf ("\nExamining priorities for PID = %d \n", mypid);
                        printf ("%10s%10s\n", "Previous", "Assigned");
			new_prio = getpriority (PRIO_PROCESS, (int)mypid);
		        printf ("%10d%10d\n", old_prio, new_prio);
			exit(0);
                }
                else
                        i++;
        }

    mypid = getpid();
    printf ("\nExamining priorities for PID = %d \n", mypid);
    printf ("%10s%10s\n", "Previous", "Assigned");
    old_prio = getpriority (PRIO_PROCESS, (int)mypid);
    rc = setpriority (PRIO_PGRP, 0, 20);
    if (rc)
    	perror("setpriority.......\n ");

    new_prio = getpriority (PRIO_PROCESS, (int)mypid);
    printf ("%10d%10d\n", old_prio, new_prio);
    getchar();	
    exit (0);
}

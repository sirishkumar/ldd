#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <errno.h>

int main (int argc, char *argv[])
{
    pid_t mypid;
    int old_prio, new_prio, i, rc;

    mypid = getpid ();

    printf ("\nExamining priorities for PID = %d \n", mypid);
    printf ("%10s%10s\n", "Previous", "Assigned");

    for (i = -20; i < 20; i += 2) {

        old_prio = getpriority (PRIO_PROCESS, (int)mypid);
        rc = setpriority (PRIO_PROCESS, (int)mypid, i);
        if (rc)
            fprintf (stderr, "setpriority() failed ");

        errno = 0;

        new_prio = getpriority (PRIO_PROCESS, (int)mypid);
        printf ("%10d%10d\n", old_prio, new_prio);

    }
    exit (0);
}

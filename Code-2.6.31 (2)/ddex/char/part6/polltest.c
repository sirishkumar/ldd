
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <poll.h>

int main (int argc, char *argv[])
{
    struct pollfd fds[1];
    int timeout = 10000;        /* time out for poll */
    int fd, rc, nbytes = 32;
    char *buffer, *filename = "/dev/veda_cdrv";

    buffer = malloc (nbytes);

    fd = open (filename, O_RDONLY);
    printf ("opened file: %s,  with file descriptor = %d\n", filename, fd);

    fds[0].fd = fd;
    fds[0].events = POLLIN;

    for (;;) {

        if ((rc = poll (fds, 1, timeout)) < 0) {
            perror ("Failure in poll\n");
            exit (EXIT_FAILURE);
        }

        if (rc > 0) {

            printf (" poll returns %d, revents = 0x%03x", rc, fds[0].revents);

            if (fds[0].revents & POLLIN) {
                rc = read (fd, buffer, nbytes);
                printf ("reading %d bytes:%s\n", rc, buffer);
            } else {
                printf ("POLLIN not set!\n");
            }

        } else {
            printf ("poll timed out in %d milliseconds on %s.\n",
                    timeout, filename);
        }
    }
    close (fd);
    exit (EXIT_SUCCESS);
}

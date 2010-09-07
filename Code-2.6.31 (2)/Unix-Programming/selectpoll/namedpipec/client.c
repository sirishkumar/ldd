#include <stdio.h>
#include <errno.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <fullduplex.h> /* For name of the named-pipe */

int main(int argc, char *argv[])
{
    int wrfd, rdfd, numread;
    char rdbuf[MAX_BUF_SIZE];

    /* Check if an argument was specified. */

    if (argc != 2) {
        printf("Usage : %s <string to be sent to the server>n", argv[0]);
        exit (1);
    }

    /* Open the first named pipe for writing */
    wrfd = open(NP1, O_WRONLY);

    /* Open the second named pipe for reading */
    rdfd = open(NP2, O_RDONLY);

    /* Write to the pipe */
    write(wrfd, argv[1], strlen(argv[1]));

    /* Read from the pipe */
    numread = read(rdfd, rdbuf, MAX_BUF_SIZE);

    rdbuf[numread] = '0';

    printf("Full Duplex Client : Read From the Pipe : %sn", rdbuf);
}

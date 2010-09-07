#include <stdio.h>
#include <errno.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <fullduplex.h> /* For name of the named-pipe */

int main(int argc, char *argv[])
{
    int rdfd, wrfd, ret_val, count, numread;
    char buf[100];

    fd_set read_set;


    /* Create the first named - pipe */
    ret_val = mkfifo(NP1, 0666);

    if ((ret_val == -1) && (errno != EEXIST)) {
        perror("Error creating the named pipe");
        exit (1);
    }

    ret_val = mkfifo(NP2, 0666);

    if ((ret_val == -1) && (errno != EEXIST)) {
        perror("Error creating the named pipe");
        exit (1);
    }

    /* Open the first named pipe for reading */
    rdfd = open(NP1, O_RDONLY);

    /* Open the second named pipe for writing */
    wrfd = open(NP2, O_WRONLY);

    /* Read from the first pipe */
 //   numread = read(rdfd, buf, MAX_BUF_SIZE);

 //   buf[numread] = '0';
        
        int fd1 = open(NP1,O_RDWR);
        FD_ZERO(&read_set);
        FD_SET(fd1,&read_set);
        int n = select(FD_SETSIZE,&read_set,NULL,NULL,NULL);
        if (n <0 ){
                perror("select ");
                exit(1);
        }
        // test whether fd1 is ready or not
        if( FD_ISSET(fd1,&read_set)){
                printf(" reading from fd1 (pone)\n");
                n = read(fd1,buf,50);
                printf(" read  %s from pone \n",buf);
        }

    printf("Full Duplex Server : Read From the pipe : %sn", buf);

    /* Convert to the string to upper case */
    count = 0;
    while (count < numread) {
        buf[count] = toupper(buf[count]);
        count++;
    }

    /* 
     * Write the converted string back to the second 
     * pipe 
     */    
    write(wrfd, buf, strlen(buf));
}

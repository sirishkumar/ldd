
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <malloc.h>
#include <string.h>
#include "veda_char_device.h"
#define MY_IOW(type,nr,size) _IOC(_IOC_WRITE,(type),(nr),size)
#define MY_IOR(type,nr,size) _IOC(_IOC_READ, (type),(nr),size)

int main ()
{
    int fd, rc, i, lbuf;
    char *buffer, *nodename = "/dev/veda_cdrv";
    int MYIOC_X;

    /* open the device node */
    fd = open (nodename, O_RDWR);
    printf (" I opened the device node, file descriptor = %d\n", fd);

    /* how big should the buffer be? */
    lbuf = 1000;
    printf (" I am going to send back and forth a buffer of %d bytes\n", lbuf);

    /* malloc the buffer */
    buffer = malloc (lbuf);

    /* send the IOCTL and read the contents from the kernel */
    printf ("\n Getting data from the kernel:\n");

    MYIOC_X = (int)MY_IOR (VEDA_MAGIC, 1, lbuf);

    rc = ioctl (fd, MYIOC_X, buffer);

    printf ("\n rc from ioctl = %d \n\n", rc);

    printf (" buffer in user-space is =\n   ");
    for (i = 0; i < lbuf; i++)
        printf ("%c", buffer[i]);
    printf ("\n");

    /*  clear it and send it back */

    memset (buffer, '0', lbuf);

    printf ("\n Sending data to the kernel:\n");
    MYIOC_X = (int)MY_IOW (VEDA_MAGIC, 1, lbuf);
    rc = ioctl (fd, MYIOC_X, buffer);
    printf ("\n rc from ioctl = %d \n\n", rc);

    printf (" buffer in user-space is =\n   ");
    for (i = 0; i < lbuf; i++)
        printf ("%c", buffer[i]);
    printf ("\n");

    close (fd);
    exit (0);
}

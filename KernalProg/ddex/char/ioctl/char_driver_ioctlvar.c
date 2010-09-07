#include <linux/module.h>
#include <linux/fs.h>
#include <asm/uaccess.h>
#include <linux/init.h>
#include <linux/cdev.h>
#include <linux/sched.h>
#include <linux/errno.h>
#include <asm/current.h>
#include <linux/device.h>
#include "veda_char_device.h"

#define MAJORNO 300
#define MINORNO  0
#define CHAR_DEV_NAME "veda_cdrv"
#define MAX_LENGTH 4000
#define SUCCESS 0

static char *char_device_buf;
struct cdev *veda_cdev;
dev_t mydev;
int count=1;
static struct class *veda_class;

/**
 * This function is called when a user wants to use this device
 * and has called the open function. 
 *
 * The function will keep a count of how many people 
 * tried to open it and increments it each time
 * this function is called
 *
 * The function prints out two pieces of information
 * 1. Number of times open() was called on this device
 * 2. Number of processes accessing this device right now
 *
 * Return value
 * 	Always returns SUCCESS
 * */
static int char_dev_open(struct inode *inode,
			    struct file  *file)
{
	static int counter = 0;
	counter++;
	printk(KERN_INFO "Number of times open() was called: %d\n", counter);
	printk (KERN_INFO " MAJOR number = %d, MINOR number = %d\n",imajor (inode), iminor (inode));
	printk(KERN_INFO "Process id of the current process: %d\n",current->pid );
	printk (KERN_INFO "ref=%d\n", module_refcount(THIS_MODULE));
	return SUCCESS;
}

/**
 * This function is called when the user program uses close() function
 * 
 * The function decrements the number of processes currently
 * using this device. This should be done because if there are no
 * users of a driver for a long time, the kernel will unload 
 * the driver from the memory.
 *
 * Return value
 * 	Always returns SUCCESS
 * */
static int char_dev_release(struct inode *inode,
		            struct file *file)
{
	return SUCCESS;
}



/**
 * This function is called when the user calls read on this device
 * It reads from a 'file' some data into 'buf' which
 * is 'lbuf' long starting from 'ppos' (present position)
 * Understanding the parameters
 * 	buf  = buffer
 * 	ppos = present position
 * 	lbuf = length of the buffer
 * 	file = file to read
 * The function returns the number of bytes(characters) read.
 * */
static int char_dev_read(struct file *file, 
		            char *buf,
			    size_t lbuf,
			    loff_t *ppos)
{
	int maxbytes; /* number of bytes from ppos to MAX_LENGTH */
	int bytes_to_do; /* number of bytes to read */
	int nbytes; /* number of bytes actually read */

	maxbytes = MAX_LENGTH - *ppos;
	
	if( maxbytes > lbuf ) bytes_to_do = lbuf;
	else bytes_to_do = maxbytes;
	
	if( bytes_to_do == 0 ) {
		printk("Reached end of device\n");
		return -ENOSPC; /* Causes read() to return EOF */
	}
	
	nbytes = bytes_to_do - 
		 copy_to_user( buf, /* to */
			       char_device_buf + *ppos, /* from */
			       bytes_to_do ); /* how many bytes */

	*ppos += nbytes;
	return nbytes;	
}



/**
 * This function is called when the user calls write on this device
 * It writes into 'file' the contents of 'buf' starting from 'ppos'
 * up to 'lbuf' bytes.
 * Understanding the parameters
 * 	buf  = buffer
 * 	file = file to write into
 * 	lbuf = length of the buffer
 * 	ppos = present position pointer
 * The function returs the number of characters(bytes) written
 * */
static int char_dev_write(struct file *file,
		            const char *buf,
			    size_t lbuf,
			    loff_t *ppos)
{
	int nbytes; /* Number of bytes written */
	int bytes_to_do; /* Number of bytes to write */
	int maxbytes; /* Maximum number of bytes that can be written */

	maxbytes = MAX_LENGTH - *ppos;

	if( maxbytes > lbuf ) bytes_to_do = lbuf;
	else bytes_to_do = maxbytes;

	if( bytes_to_do == 0 ) {
		printk("Reached end of device\n");
		return -ENOSPC; /* Returns EOF at write() */
	}

	nbytes = bytes_to_do -
	         copy_from_user( char_device_buf + *ppos, /* to */
				 buf, /* from */
				 bytes_to_do ); /* how many bytes */
	*ppos += nbytes;
	return nbytes;
}

/**
 * This function is called when lseek() is called on the device
 * The function should place the ppos pointer of 'file'
 * at an offset of 'offset' from 'orig'
 *
 * if orig = SEEK_SET
 *      ppos = offset
 *
 * if orig = SEEK_END
 *      ppos = MAX_LENGTH +  offset
 *
 * if orig = SEEK_CUR
 *      ppos += offset
 *
 * returns the new position
 * */


static loff_t char_dev_lseek (struct file *file, loff_t offset, int orig)
{
    loff_t testpos;
    switch (orig) {

    case 0:                 /* SEEK_SET */
            testpos = offset;
            break;
    case 1:                 /* SEEK_CUR */
            testpos = file->f_pos + offset;
            break;
    case 2:                 /* SEEK_END */
           testpos = MAX_LENGTH + offset;
           break;
    default:
          return -EINVAL;
    }
   
    testpos = testpos < MAX_LENGTH ? testpos : MAX_LENGTH;
    testpos = testpos >= 0 ? testpos : 0;
    file->f_pos = testpos;
    printk (KERN_INFO "Seeking to pos=%ld\n", (long)testpos);
    return testpos;
}

static inline long chrdev_unlocked_ioctl (struct file *fp, unsigned int cmd, unsigned long arg)
{
    int i, rc, direction;
    int size;
    char *buffer;
    void __user *ioargp = (void __user *)arg;

    /* make sure it is a valid command */

    if (_IOC_TYPE (cmd) != VEDA_MAGIC) {
        printk (KERN_WARNING " got invalid case, CMD=%d\n", cmd);
        return -EINVAL;
    }

    /* get the size of the buffer and kmalloc it */

    size = _IOC_SIZE (cmd);
    buffer = kmalloc ((size_t) size, GFP_KERNEL);
    if (!buffer) {
        printk (KERN_ERR "Kmalloc failed for buffer\n");
        return -ENOMEM;
    }

    /* fill it with X */

    memset (buffer, 'X', size);

    direction = _IOC_DIR (cmd);

    switch (direction) {

    case _IOC_WRITE:
        printk
            (KERN_INFO " reading = %d bytes from user-space and writing to device\n", size);
        rc = copy_from_user (buffer, ioargp, size);
        printk (KERN_INFO "rc from copy_from_user = %d\n", rc);
        break;

    case _IOC_READ:
        printk (KERN_INFO
                " reading device and writing = %d bytes to user-space\n", size);
        rc = copy_to_user (ioargp, buffer, size);
        printk (KERN_INFO "rc from copy_to_user = %d\n", rc);

   default:
        printk (KERN_WARNING " got invalid case, CMD=%d\n", cmd);
        return -EINVAL;
    }
    for (i = 0; i < size; i++)
        printk (KERN_INFO "%c", buffer[i]);
    printk (KERN_INFO "\n");

    if (buffer)
        kfree (buffer);
    return rc;
}

static struct file_operations char_dev_fops = {
	.owner = THIS_MODULE,
	.unlocked_ioctl = chrdev_unlocked_ioctl,
	.read = char_dev_read,
	.write = char_dev_write,
	.open = char_dev_open,
	.release = char_dev_release,
	.llseek = char_dev_lseek
};

static __init int char_dev_init(void)
{
	int ret;

	if (alloc_chrdev_region (&mydev, 0, count, CHAR_DEV_NAME) < 0) {
            printk (KERN_ERR "failed to reserve major/minor range\n");
            return -1;
    }

        if (!(veda_cdev = cdev_alloc ())) {
            printk (KERN_ERR "cdev_alloc() failed\n");
            unregister_chrdev_region (mydev, count);
            return -1;
 	}
	cdev_init(veda_cdev,&char_dev_fops);

	ret=cdev_add(veda_cdev,mydev,count);
	if( ret < 0 ) {
		printk(KERN_INFO "Error registering device driver\n");
	        cdev_del (veda_cdev);
                unregister_chrdev_region (mydev, count); 	
		return -1;
	}

	veda_class = class_create (THIS_MODULE, "VIRTUAL");
        device_create (veda_class, NULL, mydev, NULL, "%s", "veda_cdrv");

	printk(KERN_INFO"\nDevice Registered: %s\n",CHAR_DEV_NAME);
	printk (KERN_INFO "Major number = %d, Minor number = %d\n", MAJOR (mydev),MINOR (mydev));

	char_device_buf =(char *)kmalloc(MAX_LENGTH,GFP_KERNEL);
	return 0;
}

static __exit void  char_dev_exit(void)
{
	 device_destroy (veda_class, mydev);
         class_destroy (veda_class);
	 cdev_del(veda_cdev);
	 unregister_chrdev_region(mydev,1);
	 kfree(char_device_buf);
	 printk(KERN_INFO "\n Driver unregistered \n");
}
module_init(char_dev_init);
module_exit(char_dev_exit);

MODULE_AUTHOR("VEDA");
MODULE_DESCRIPTION("Character Device Driver - Test");
MODULE_LICENSE("GPL");

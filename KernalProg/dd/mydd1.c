#include <linux/module.h> //KMOD interface
#include <linux/fs.h> //
#include <asm/uaccess.h>
#include <linux/init.h>
#include <linux/cdev.h>
#include <linux/slab.h>

#define MAJORNO 301
#define MINORNO 0
#define CHAR_DEV_NAME "sirish_test_cdrv"
#define SUCCESS 0



dev_t mydev;
int count=1;

struct cdev *veda_cdev;

static int char_dev_open(struct inode *inode,struct file *file)
{
   return SUCCESS;
}

static int char_dev_release(struct inode *inode,
                            struct file *file)
{

    return SUCCESS;
}

static int char_dev_read(struct file *file,
				char *buf,
				size_t lbuf,
				loff_t *ppos)
{
    return 0;
}

static int char_dev_write(struct file *file,
				const char *buf,
				size_t lbuf,
				loff_t *ppos)
{
   return 0;
}

static struct file_operations char_dev_fops = {

	.owner = THIS_MODULE,
	.read = char_dev_read,
	.write = char_dev_write,
	.open = char_dev_open,
	.release = char_dev_release
};

static int __init char_dev_init(void)
{
	 mydev = MKDEV(MAJORNO,MINORNO);
  	 register_chrdev_region(mydev,count,CHAR_DEV_NAME);
	
	veda_cdev = cdev_alloc();
	cdev_init(veda_cdev,&char_dev_fops);

        int ret = cdev_add(veda_cdev,mydev,count);
	
        return 0;
}

static void __exit char_dev_exit(void)
{
     cdev_del(veda_cdev);
     unregister_chrdev_region(mydev,1);
     printk(KERN_INFO,"\n Driver Unregistered \n");
}

module_init(char_dev_init);
module_exit(char_dev_exit);

MODULE_AUTHOR("SIRISH");
MODULE_DESCRIPTION("Test DD");
MODULE_LICENSE("GPL");


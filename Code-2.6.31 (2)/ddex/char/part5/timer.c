#include <linux/module.h>
#include <linux/init.h>
#include <linux/errno.h>
#include <linux/types.h>
#include <linux/timer.h>
#include <linux/sched.h>


static struct timer_list my_timer;

static void my_timer_function (unsigned long ptr)
{
    printk (KERN_INFO "In my_timer_fun, jiffies = %ld\n", jiffies);
    printk (KERN_INFO "current task pid is %d\n",(int)current->pid);
    printk (KERN_INFO "my data is: %d\n", (int)ptr);
}

static __init int myinit(void)
{
	static int len = 100;
	init_timer (&my_timer);     /* intialize */
        my_timer.function = my_timer_function;
        my_timer.expires = jiffies + HZ;    /* one second delay */
        my_timer.data = len;
        printk (KERN_INFO "Adding timer at jiffies = %ld\n", jiffies);
        add_timer (&my_timer);

	return 0;
}

static __exit void  myexit(void)
{
	printk (KERN_INFO "Deleted time,r rc = %d\n", del_timer_sync (&my_timer));
	printk(KERN_INFO "\n module removed  \n");
}
module_init(myinit);
module_exit(myexit);

MODULE_AUTHOR("VEDA");
MODULE_DESCRIPTION("Timer  - Test");
MODULE_LICENSE("GPL");

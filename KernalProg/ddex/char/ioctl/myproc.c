
#include <linux/module.h>
#include <linux/proc_fs.h>
#include <linux/uaccess.h>
#include <linux/init.h>

#define NODE "driver/my_proc"

static int param = 100;
static struct proc_dir_entry *my_proc;

static int
my_proc_read (char *page, char **start, off_t off, int count,
              int *eof, void *data)
{
    return sprintf (page, "%d\n", param);
}

static int
my_proc_write (struct file *file, const char __user * buffer,
               unsigned long count, void *data)
{
    char *str;
    str = kmalloc ((size_t) count, GFP_KERNEL);
    if (copy_from_user (str, buffer, count)) {
        kfree (str);
        return -EFAULT;
    }
    sscanf (str, "%d", &param);
    printk (KERN_INFO "param has been set to %d\n", param);
    kfree (str);
    return count;
}

static int __init my_init (void)
{
    my_proc = create_proc_entry (NODE, S_IRUGO | S_IWUSR, NULL);
    if (!my_proc) {
        printk (KERN_ERR "I failed to make %s\n", NODE);
        return -1;
    }
    printk (KERN_INFO "I created %s\n", NODE);
    my_proc->read_proc = my_proc_read;
    my_proc->write_proc = my_proc_write;
    return 0;
}

static void __exit my_exit (void)
{
    if (my_proc) {
        remove_proc_entry (NODE, NULL);
        printk (KERN_INFO "Removed %s\n", NODE);
    }
}

module_init (my_init);
module_exit (my_exit);

MODULE_AUTHOR ("Team Veda");
MODULE_DESCRIPTION ("proc files");
MODULE_LICENSE ("GPL");

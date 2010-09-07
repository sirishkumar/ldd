#include<linux/module.h>
#include<linux/version.h>
#include<linux/kernel.h>
#include<linux/init.h>
#include<linux/rcupdate.h>
#include<linux/rculist.h>
#include<linux/list.h>
#include<linux/spinlock.h>
#include "my_rcu.h"

static DEFINE_MUTEX(my_lock);
extern struct list_head head;
struct node *set;

void writer(int new_data_item1,int new_data_item2) 
{
	struct node *new,*old;
	unsigned long j = jiffies + 10*HZ;
	list_for_each_entry_rcu(set, &head, list) {	
		new = kmalloc(sizeof(*new),GFP_KERNEL);
		mutex_lock(&my_lock);
		old 	= set;
		*new 	= *old;
		new->data_item1	=   new_data_item1;
		if(old->data_item1==30)
		while( jiffies < j ) {

                }
		new->data_item2	=   new_data_item2;
		list_replace_rcu(&set->list, &new->list);
		printk(KERN_INFO "in write \n");
		mutex_unlock(&my_lock);
		synchronize_rcu();
		kfree(old);
	}
	printk(KERN_INFO "out write \n");
}

int __init init_rcu_writer(void) 
{
	printk(KERN_INFO "%s is module inserted\n", __func__);
	writer(777,888);

	return 0;	
}

void __exit cleanup_rcu_writer(void) 
{
        printk(KERN_INFO "%s is module removed\n", __func__);
}

module_init(init_rcu_writer);
module_exit(cleanup_rcu_writer);

MODULE_AUTHOR("TEAM VEDA");
MODULE_DESCRIPTION("RCU WRITER MODULE");
MODULE_LICENSE("GPL");


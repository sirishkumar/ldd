#include<linux/module.h>
#include<linux/version.h>
#include<linux/kernel.h>
#include<linux/init.h>
#include<linux/rcupdate.h>
#include<linux/rculist.h>
#include<linux/list.h>
#include<linux/delay.h>
#include "my_rcu.h"

extern struct list_head head;
struct node *get;

void reader1(void) 
{
	int a,b;
	rcu_read_lock();
	a = rcu_dereference(get)->data_item1;
	b = rcu_dereference(get)->data_item2;
	printk(KERN_INFO " reader 1 .......... data_item1 = %d\tdata_item2 = %d\n", a, b);
       	rcu_read_unlock();
}
		
int __init init_rcu_reader1(void) 
{
	printk(KERN_INFO "%s module is inserted\n", __func__);
	printk(KERN_INFO "\n data items in stack:\n");
        list_for_each_entry_rcu(get,&head,list) 
		reader1();
	return 0;
}

void __exit cleanup_rcu_reader1(void) 
{
	printk(KERN_INFO "%s module is removed\n", __func__);
}

module_init(init_rcu_reader1);
module_exit(cleanup_rcu_reader1);

MODULE_AUTHOR("TEAM VEDA");
MODULE_DESCRIPTION("RCU READER1 MODULE");
MODULE_LICENSE("GPL");
